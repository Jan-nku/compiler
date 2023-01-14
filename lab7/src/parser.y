%code top{
    #include <iostream>
    #include <stack>
    #include <string>
    #include <assert.h>
    #include "parser.h"
    extern Ast ast;
    int yylex();
    int yyerror( char const * );

    std::stack<WhileStmt*> whileStack;
    Type *nowType;

    ArrayType *currentArray;
    std::stack<ArrayInit*> arrayStack;
    unsigned int leftBraceCount=0;
    unsigned int arrayIndex=0;
    int *arrayValue;
}

%code requires {
    #include "Ast.h"
    #include "SymbolTable.h"
    #include "Type.h"
}

%union {
    int itype;
    float ftype;
    char* strtype;
    StmtNode* stmttype;
    ExprNode* exprtype;
    Type* type;
}

%start Program
%token <strtype> ID 
%token <itype> INTEGER
%token <ftype> FLOATING
%token IF ELSE WHILE
%token INT VOID FLOAT CONST
%token LPAREN RPAREN LBRACE RBRACE SEMICOLON LBRACKET RBRACKET
%token ADD SUB MUL DIV MOD OR AND NOT LESS GREATER EQUAL NOTEQUAL LESSEQUAL GREATEREQUAL ASSIGN  
%token RETURN BREAK CONTINUE
%token COMMA

%nterm <stmttype> Stmts Stmt ExprStmt AssignStmt BlockStmt EmptyStmt IfStmt ReturnStmt WhileStmt BreakStmt ContinueStmt DeclStmt 
ConstDeclStmt VarDeclStmt ConstDefList VarDef ConstDef VarDefList FuncDef FuncFParams FuncFParam 
%nterm <exprtype> Exp AddExp MulExp Cond LOrExp PrimaryExp LVal RelExp LAndExp EqExp UnaryExp ConstExp InitVal ConstInitVal 
ArrayIndices FuncRParams InitValList
%nterm <type> Type

%precedence THEN
%precedence ELSE
%%
Program
    : Stmts {
        ast.setRoot($1);
    }
    ;

Stmts
    : Stmt {$$=$1;}
    | Stmts Stmt{
        $$ = new SeqNode($1, $2);
    }
    ;
Stmt
    : AssignStmt {$$=$1;}
    | ExprStmt {$$=$1;}
    | BlockStmt {$$=$1;}
    | EmptyStmt {$$=$1;}
    | IfStmt {$$=$1;}
    | ReturnStmt {$$=$1;}
    | DeclStmt {$$=$1;}
    | WhileStmt{$$=$1;}
    | BreakStmt{$$=$1;}
    | ContinueStmt{$$=$1;}
    | FuncDef {$$=$1;}
    ;
LVal
    : ID {
        SymbolEntry *se;
        se = identifiers->lookup($1);
        if(se == nullptr){
            fprintf(stderr, "identifier \"%s\" is undefined\n", (char*)$1);
            delete [](char*)$1;
            assert(se != nullptr);
        }
        $$ = new Id(se);
        delete []$1;
    }
    | ID ArrayIndices{
        //增加数组作为lval
        SymbolEntry *se;
        se = identifiers->lookup($1);
        if(se == nullptr)
        {
            fprintf(stderr, "identifier \"%s\" is undefined\n", (char*)$1);
            delete [](char*)$1;
            assert(se != nullptr);
        }
        $$ = new Id(se,$2);
        delete []$1;
    }
    ;
ExprStmt
    : Exp SEMICOLON {
        $$ = new ExprStmt($1);
    }
    ;

AssignStmt
    :
    LVal ASSIGN Exp SEMICOLON {
        $$ = new AssignStmt($1, $3);
    }
    ;

BlockStmt
    : 
    LBRACE {
        identifiers = new SymbolTable(identifiers);
    } 
    Stmts RBRACE {
        $$ = new CompoundStmt($3);
        SymbolTable *top = identifiers;
        identifiers = identifiers->getPrev();
        delete top;
    }
    | LBRACE RBRACE {
        $$ = new CompoundStmt();
    }
    ;

EmptyStmt 
    : SEMICOLON {
        $$ = new EmptyStmt();
    }
    ;

IfStmt
    : IF LPAREN Cond RPAREN Stmt %prec THEN {
        //Cond不是bool的情况，涉及隐式类型转换
        if(!$3->getType()->isBool()){
            SymbolEntry *se_temp = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
            SymbolEntry *se_zero = new ConstantSymbolEntry(TypeSystem::intType, 0);
            $3 = new BinaryExpr(se_temp, BinaryExpr::NOTEQUAL, $3, new Constant(se_zero));
        }
        $$ = new IfStmt($3, $5);
    }
    | IF LPAREN Cond RPAREN Stmt ELSE Stmt {
        //Cond不是bool的情况，涉及隐式类型转换
        if(!$3->getType()->isBool()){
            SymbolEntry *se_temp = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
            SymbolEntry *se_zero = new ConstantSymbolEntry(TypeSystem::intType, 0);
            $3 = new BinaryExpr(se_temp, BinaryExpr::NOTEQUAL, $3, new Constant(se_zero));
        }
        $$ = new IfElseStmt($3, $5, $7);
    }
    ;

WhileStmt
    : WHILE LPAREN Cond RPAREN {
        if(!$3->getType()->isBool()){
            SymbolEntry *se_temp = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
            SymbolEntry *se_zero = new ConstantSymbolEntry(TypeSystem::intType, 0);
            $3 = new BinaryExpr(se_temp, BinaryExpr::NOTEQUAL, $3, new Constant(se_zero));
        }
        WhileStmt* whileStmt = new WhileStmt($3,nullptr);
        $<stmttype>$ = whileStmt;
        whileStack.push(whileStmt);
    }
    Stmt {
        StmtNode *whileStmt = $<stmttype>5; 
        ((WhileStmt*)whileStmt)->setStmt($6);
        $$=whileStmt;
        whileStack.pop();
    }
    ;

BreakStmt
    : BREAK SEMICOLON {
        //增加break语句检查
        if(whileStack.empty()){
            fprintf(stderr,"break stmt is not in a while stmt\n");
            assert(!whileStack.empty());
        }
        $$ = new BreakStmt(whileStack.top());
    }
    ;
ContinueStmt
    : CONTINUE SEMICOLON {
        //增加continue语句检查
        if(whileStack.empty()){
            fprintf(stderr,"continue stmt is not in a while stmt\n");
            assert(!whileStack.empty());
        }
        $$ = new ContinueStmt(whileStack.top());
    }
    ;

ReturnStmt
    : RETURN SEMICOLON {
        $$ = new ReturnStmt();
    }
    | RETURN Exp SEMICOLON{
        $$ = new ReturnStmt($2);
    }
    ;
Exp
    :
    AddExp {$$ = $1;}
    ;
Cond
    :
    LOrExp {$$ = $1;}
    ;

UnaryExp 
    : PrimaryExp {$$ = $1;}
    | ID LPAREN FuncRParams RPAREN {
        SymbolEntry* se;
        se = identifiers->lookup($1);
        //检查函数是否未定义
        if(se == nullptr){
            fprintf(stderr, "function \"%s\" is undefined\n", (char*)$1);
            delete [](char*)$1;
            assert(se != nullptr);
        }
        //检查函数参数数量、类型是否匹配
        ExprNode* callParamsType = $3;
        int paramCount = 0;
        while(callParamsType){
            paramCount++;
            callParamsType = (ExprNode*)callParamsType->getNext();
        }
        while(se){
            if(((FunctionType*)(se->getType()))->getParamsType().size() == paramCount){
                break;
            }
            se = se->getNext();
        }
        if(se == nullptr){
            fprintf(stderr, "function \"%s\" having %d params, is undefined\n", (char*)$1, paramCount);
            delete [](char*)$1;
            assert(se != nullptr);
        }
        std::vector<Type*> paramsType = ((FunctionType*)(se->getType()))->getParamsType();
        callParamsType = $3;

        for(auto &params:paramsType){
            if(params != callParamsType->getSymbolEntry()->getType()){
                 if(callParamsType->getSymbolEntry()->getType()->isArray() && params->isArray()){
                    callParamsType = (ExprNode*)callParamsType->getNext();
                    continue;
                }
                fprintf(stderr, "your param TYPE should be %s, but when you call func you use %s\n",
                        params->toStr().c_str(),callParamsType->getSymbolEntry()->getType()->toStr().c_str());
            }
            callParamsType = (ExprNode*)callParamsType->getNext();
        }
        $$ = new FuncExpr(se, $3);
    }
    | ADD UnaryExp {$$ = $2;}
    | SUB UnaryExp {
        SymbolEntry *se;
        if($2->getType()->isFloat())
            se = new TemporarySymbolEntry(TypeSystem::floatType, SymbolTable::getLabel());
        else
            se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        $$ = new UnaryExpr(se, UnaryExpr::SUB, $2);
    }
    | NOT UnaryExp {
        SymbolEntry* se = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
        $$ = new UnaryExpr(se, UnaryExpr::NOT, $2);
    }
    ;

PrimaryExp
    :
    LVal {
        $$ = $1;
    }
    | INTEGER {
        SymbolEntry *se = new ConstantSymbolEntry(TypeSystem::intType, $1);
        $$ = new Constant(se);
    }
    | FLOATING {
        SymbolEntry *se = new ConstantSymbolEntry(TypeSystem::floatType, $1);
        $$ = new Constant(se);
    }
    | LPAREN Exp RPAREN {
        $$ = $2;
    }
    ;

AddExp
    :
    MulExp {$$ = $1;}
    | AddExp ADD MulExp{
        SymbolEntry* se;
        if ($1->getType()->isFloat() || $3->getType()->isFloat()) {
            se = new TemporarySymbolEntry(TypeSystem::floatType, SymbolTable::getLabel());
            $$ = new BinaryExpr(se, BinaryExpr::ADD, $1, $3);
        } else {
            se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
            $$ = new BinaryExpr(se, BinaryExpr::ADD, $1, $3);
        }
    }
    | AddExp SUB MulExp{
        SymbolEntry* se;
        if ($1->getType()->isFloat() || $3->getType()->isFloat()) {
            se = new TemporarySymbolEntry(TypeSystem::floatType, SymbolTable::getLabel());
            $$ = new BinaryExpr(se, BinaryExpr::SUB, $1, $3);
        } else {
            se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
            $$ = new BinaryExpr(se, BinaryExpr::SUB, $1, $3);
        }
    }
    ;

MulExp
    :
    UnaryExp {
        $$=$1;
    }
    | MulExp MUL UnaryExp {
        SymbolEntry* se;
        if ($1->getType()->isBool() || $3->getType()->isBool()) {
            fprintf(stderr,"bool cannot use in MUL\n");
            assert(!$1->getType()->isBool());
            assert(!$3->getType()->isBool());
        }
        if ($1->getType()->isFloat() || $3->getType()->isFloat()) {
            se = new TemporarySymbolEntry(TypeSystem::floatType, SymbolTable::getLabel());
            $$ = new BinaryExpr(se, BinaryExpr::MUL, $1, $3);
        } else {
            se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
            $$ = new BinaryExpr(se, BinaryExpr::MUL, $1, $3);
        }
    }
    | MulExp DIV UnaryExp {
        SymbolEntry* se;
        if ($1->getType()->isBool() || $3->getType()->isBool()) {
            fprintf(stderr,"bool cannot use in DIV\n");
            assert(!$1->getType()->isBool());
            assert(!$3->getType()->isBool());
        }
        if ($1->getType()->isFloat() || $3->getType()->isFloat()) {
            se = new TemporarySymbolEntry(TypeSystem::floatType, SymbolTable::getLabel());
            $$ = new BinaryExpr(se, BinaryExpr::DIV, $1, $3);
        } else {
            se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
            $$ = new BinaryExpr(se, BinaryExpr::DIV, $1, $3);
        }
    }
    | MulExp MOD UnaryExp {
        SymbolEntry* se;
        if ($1->getType()->isBool() || $3->getType()->isBool()) {
            fprintf(stderr,"bool cannot use in MOD\n");
            assert(!$1->getType()->isBool());
            assert(!$3->getType()->isBool());
        }
        if ($1->getType()->isFloat() || $3->getType()->isFloat()) {
            se = new TemporarySymbolEntry(TypeSystem::floatType, SymbolTable::getLabel());
            $$ = new BinaryExpr(se, BinaryExpr::MOD, $1, $3);
        } else {
            se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
            $$ = new BinaryExpr(se, BinaryExpr::MOD, $1, $3);
        }      
    }
    ;

RelExp
    :
    AddExp {$$ = $1;}
    | RelExp LESS AddExp{
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
        $$ = new BinaryExpr(se, BinaryExpr::LESS, $1, $3);
    }
    | RelExp LESSEQUAL AddExp{
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
        $$ = new BinaryExpr(se, BinaryExpr::LESSEQUAL, $1, $3);
    }
    | RelExp GREATER AddExp{
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
        $$ = new BinaryExpr(se, BinaryExpr::GREATER, $1, $3);
    }
    | RelExp GREATEREQUAL AddExp{
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
        $$ = new BinaryExpr(se, BinaryExpr::GREATEREQUAL, $1, $3);
    }        
    ;

EqExp
    : RelExp {$$ = $1;}
    | EqExp EQUAL RelExp {
        SymbolEntry* se = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
        $$ = new BinaryExpr(se, BinaryExpr::EQUAL, $1, $3);
    }
    | EqExp NOTEQUAL RelExp {
        SymbolEntry* se = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
        $$ = new BinaryExpr(se, BinaryExpr::NOTEQUAL, $1, $3);
    }
    ;

LAndExp
    :
    EqExp {$$ = $1;}
    |
    LAndExp AND EqExp
    {
        SymbolEntry *boolSe;
        if(!$1->getType()->isBool()){
            boolSe = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
            $1 = new BinaryExpr(boolSe, BinaryExpr::NOTEQUAL, $1, new Constant(new ConstantSymbolEntry(TypeSystem::intType, 0))); 
        }
        if(!$3->getType()->isBool()){
            boolSe = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
            $3 = new BinaryExpr(boolSe, BinaryExpr::NOTEQUAL, $3, new Constant(new ConstantSymbolEntry(TypeSystem::intType, 0)));
        }
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
        $$ = new BinaryExpr(se, BinaryExpr::AND, $1, $3);
    }
    ;

LOrExp
    :
    LAndExp {$$ = $1;}
    |
    LOrExp OR LAndExp
    {
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        $$ = new BinaryExpr(se, BinaryExpr::OR, $1, $3);
    }
    ;

//nowType记录当前type类型，用于区分float、int、void
Type
    : INT {
        $$ = TypeSystem::intType;
        nowType = TypeSystem::intType;
    }
    | VOID {
        $$ = TypeSystem::voidType;
        nowType = TypeSystem::voidType;
    }
    | FLOAT {
        $$ = TypeSystem::floatType;
        nowType = TypeSystem::floatType;
    }
    ;

ArrayIndices
    : LBRACKET Exp RBRACKET {
        $$=$2;
    }
    | ArrayIndices LBRACKET Exp RBRACKET {
        $$=$1;
        $1->setNext($3);
    }
    | LBRACKET RBRACKET{
        SymbolEntry *se = new ConstantSymbolEntry(TypeSystem::intType, 0);
        $$ = new Constant(se);
    }

DeclStmt
    : VarDeclStmt {$$ = $1;}
    | ConstDeclStmt {$$ = $1;}
    ;

VarDeclStmt
    : Type VarDefList SEMICOLON {$$ = $2;}
    ;

ConstDeclStmt
    : CONST Type ConstDefList SEMICOLON {$$ = $3;}
    ;

VarDefList
    : VarDefList COMMA VarDef {
        $$ = $1;
        $1->setNext($3);
    } 
    | VarDef {$$ = $1;}
    ;

ConstDefList
    : ConstDefList COMMA ConstDef {
        $$ = $1;
        $1->setNext($3);
    }
    | ConstDef {$$ = $1;}
    ;

VarDef
    : ID {
        SymbolEntry* se;
        if(nowType->isInt()){
            se = new IdentifierSymbolEntry(TypeSystem::intType, $1, identifiers->getLevel());
        }else{
            if(nowType->isFloat()){
                se = new IdentifierSymbolEntry(TypeSystem::floatType, $1, identifiers->getLevel()); 
            }
        }
        if (!identifiers->install($1, se)){
            fprintf(stderr, "identifier \"%s\" is already defined\n", (char*)$1);
            assert(false);
        }
        $$ = new DeclStmt(new Id(se));
        delete []$1;
    }
    | ID ASSIGN InitVal {
        SymbolEntry*se;
            if(nowType->isInt()){
                se=new IdentifierSymbolEntry(TypeSystem::intType,$1,identifiers->getLevel());
                ((IdentifierSymbolEntry*)se)->setValue($3->getIValue());
        }else{
            if(nowType->isFloat()){
                se = new IdentifierSymbolEntry(TypeSystem::floatType, $1, identifiers->getLevel());
                ((IdentifierSymbolEntry*)se)->setFValue($3->getFValue());
            }
        }
        if (!identifiers->install($1, se)){
            fprintf(stderr, "identifier \"%s\" is already defined\n", (char*)$1);
            assert(false);
        }
        $$ = new DeclStmt(new Id(se),$3);
        delete []$1;
    }
    | ID ArrayIndices {
        ExprNode* t=$2;
        std::vector<int> v;
        while(t!=nullptr){
            v.push_back(t->getIValue());
            t=(ExprNode*)(t->getNext());
        }
        Type*arrayType=nowType->isInt()?TypeSystem::intType:TypeSystem::floatType;
        
        Type*tempType;
        while(!v.empty()){       
            tempType=new ArrayType(arrayType,v.back());
            if(arrayType->isArray()){
                ((ArrayType*)arrayType)->setArrayType(tempType);
            }
            arrayType=tempType;
            v.pop_back();
        }
        SymbolEntry*se;
        se = new IdentifierSymbolEntry(arrayType, $1, identifiers->getLevel());
        //全局变量，初始化为全0
        if(dynamic_cast<IdentifierSymbolEntry*>(se)->isGlobal()){
            dynamic_cast<IdentifierSymbolEntry*>(se)->setAllZero(true);
        }
        if (!identifiers->install($1, se)){
            fprintf(stderr, "identifier \"%s\" is already defined\n", (char*)$1);
            assert(false);
        }
        $$ = new DeclStmt(new Id(se));
        delete []$1;
    }
    | ID ArrayIndices ASSIGN{
        ExprNode* t=$2;
        std::vector<int> v;
        while(t!=nullptr){
            v.push_back(t->getIValue());
            t=(ExprNode*)(t->getNext());
        }
        Type*arrayType=nowType->isInt()?TypeSystem::intType:TypeSystem::floatType;
        Type*tempType;
        while(!v.empty()){
            tempType=new ArrayType(arrayType,v.back());
            if(arrayType->isArray()){
                ((ArrayType*)arrayType)->setArrayType(tempType);
            }
            arrayType=tempType;
            v.pop_back();
        }
        currentArray=(ArrayType*)arrayType;
        leftBraceCount=0;
    }
    InitVal{
        SymbolEntry*se;
        se = new IdentifierSymbolEntry(currentArray, $1, identifiers->getLevel());
        if (!identifiers->install($1, se)){
            fprintf(stderr, "identifier \"%s\" is already defined\n", (char*)$1);
            assert(false);
        }
        $$ = new DeclStmt(new Id(se), $5);
        delete []$1;
    }
    ;

ConstDef
    : ID ASSIGN ConstInitVal {
        //int/float、是否重定义
        SymbolEntry* se;
        if(nowType->isInt()){
            se = new IdentifierSymbolEntry(TypeSystem::constIntType, $1, identifiers->getLevel());
            ((IdentifierSymbolEntry*)se)->setValue($3->getIValue());
        }else{
            if(nowType->isFloat()){
                se = new IdentifierSymbolEntry(TypeSystem::constFloatType, $1, identifiers->getLevel());
                ((IdentifierSymbolEntry*)se)->setFValue($3->getFValue());
            }
        }
        if (!identifiers->install($1, se)){
            fprintf(stderr, "identifier \"%s\" is already defined\n", (char*)$1);
            assert(false);
        }
        $$ = new DeclStmt(new Id(se), $3);
        delete []$1;
    }
    | ID ArrayIndices ASSIGN{
        ExprNode* t=$2;
        std::vector<int> v;
        while(t!=nullptr){
            v.push_back(t->getIValue());
            t=(ExprNode*)(t->getNext());
        }
        Type*arrayType=nowType->isInt()?TypeSystem::constIntType:TypeSystem::constFloatType;
        Type*tempType;
        while(!v.empty()){
            tempType=new ArrayType(arrayType,v.back());
            if(arrayType->isArray()){
                ((ArrayType*)arrayType)->setArrayType(tempType);
            }
            arrayType=tempType;
            v.pop_back();
        }
        currentArray=(ArrayType*)arrayType;
        leftBraceCount=0;
    }
    InitVal{
        SymbolEntry*se;
        se = new IdentifierSymbolEntry(currentArray, $1, identifiers->getLevel());
        if (!identifiers->install($1, se)){
            fprintf(stderr, "identifier \"%s\" is already defined\n", (char*)$1);
            assert(false);
        }
        $$ = new DeclStmt(new Id(se), $5);
        delete []$1;
    }
    ;
    

InitValList
    : InitValList COMMA InitVal{
        $$ = $1;
    }
    | InitVal{
        $$ = $1;
    }
    ;

InitVal
    : Exp {
        $$ = $1;
        if(!arrayStack.empty()){
            arrayStack.top()->addExpr($1);
        }  
    }
    | LBRACE RBRACE{
        SymbolEntry* se;
        if(!arrayStack.empty()){
            currentArray = (ArrayType*)(((ArrayType*)(arrayStack.top()->getSymbolEntry()->getType()))->getElementType());
        }
        se = new ConstantSymbolEntry(currentArray);
        ArrayInit *arrayNode = new ArrayInit(se,true);
        if(!arrayStack.empty())
            arrayStack.top()->addExpr(arrayNode);

        if(!arrayStack.empty())
            currentArray=(ArrayType*)(((ArrayType*)(arrayStack.top()->getSymbolEntry()->getType()))->getElementType());
        $$=arrayNode;
    }
    | LBRACE {
        SymbolEntry* se;
        if(!arrayStack.empty()){
            currentArray = (ArrayType*)(((ArrayType*)(arrayStack.top()->getSymbolEntry()->getType()))->getElementType());
        }
        se = new ConstantSymbolEntry(currentArray);
        ArrayInit *arrayNode = new ArrayInit(se);
        if(!arrayStack.empty())
            arrayStack.top()->addExpr(arrayNode);
        
        arrayStack.push(arrayNode);
    }
    InitValList RBRACE{
        $$ = arrayStack.top();
        arrayStack.pop();
        if(!arrayStack.empty())
            currentArray=((ArrayType*)(arrayStack.top()->getSymbolEntry()->getType()));
    }
    ;

ConstInitVal
    : ConstExp {$$ = $1;}
    ;

ConstExp
    : Exp{$$ = $1;}
    ;

FuncDef
    : Type ID {
        identifiers = new SymbolTable(identifiers);
    }
    LPAREN FuncFParams RPAREN {
        Type* funcType;
        std::vector<SymbolEntry*> vec;
        DeclStmt* temp = (DeclStmt*)$5;
        while(temp){
            vec.push_back(temp->getId()->getSymbolEntry());
            temp = (DeclStmt*)(temp->getNext());
        }
        funcType = new FunctionType($1, vec);
        SymbolEntry* se = new IdentifierSymbolEntry(funcType, $2, identifiers->getPrev()->getLevel());
        assert(identifiers->getPrev()->install($2, se));
    }
    BlockStmt
    {
        SymbolEntry *se;
        se = identifiers->lookup($2);
        assert(se != nullptr);
        $$ = new FunctionDef(se, (DeclStmt*)$5,$8);
        SymbolTable *top = identifiers;
        identifiers = identifiers->getPrev();
        delete top;
        delete []$2;
    }
    ;

FuncFParams
    : FuncFParam{
        $$=$1;
    }
    | FuncFParams COMMA FuncFParam{
        $$=$1;
        $$->setNext($3);
    }
    | %empty {$$=nullptr;}
    ;

FuncFParam
    :
    Type ID{
        SymbolEntry*se;
        se=new IdentifierSymbolEntry($1,$2,identifiers->getLevel());
        dynamic_cast<IdentifierSymbolEntry*>(se)->setParam();
        dynamic_cast<IdentifierSymbolEntry*>(se)->setAddr(new Operand(se));
        identifiers->install($2,se);
        $$=new DeclStmt(new Id(se));
        delete[]$2;
    }
    | Type ID ArrayIndices{
        ExprNode* t=$3;
        std::vector<int> v;
        while(t!=nullptr){
            v.push_back(t->getIValue());
            t=(ExprNode*)(t->getNext());
        }
        Type*arrayType=$1->isInt()?TypeSystem::intType:TypeSystem::floatType;
        Type*tempType;
        while(!v.empty()){
            tempType=new ArrayType(arrayType,v.back());
            if(arrayType->isArray()){
                ((ArrayType*)arrayType)->setArrayType(tempType);
            }
            arrayType=tempType;
            v.pop_back();
        }
        SymbolEntry*se;
        se = new IdentifierSymbolEntry(arrayType, $2, identifiers->getLevel());
        dynamic_cast<IdentifierSymbolEntry*>(se)->setParam();
        dynamic_cast<IdentifierSymbolEntry*>(se)->setAddr(new Operand(se));
        identifiers->install($2, se);
        $$ = new DeclStmt(new Id(se));
        delete []$2;
    }
    //允许最后几个参数有默认值
    ;

FuncRParams 
    : Exp {$$ = $1;}
    | FuncRParams COMMA Exp {
        $$ = $1;
        $$->setNext($3);
    }
    | %empty {$$=nullptr;}
    ;

%%

int yyerror(char const* message)
{
    std::cerr<<message<<std::endl;
    return -1;
}
