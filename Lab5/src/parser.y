
%code top{
    #include <iostream>
    #include <vector>
    #include <assert.h>
    #include "parser.h"
    extern Ast ast;
    int yylex();
    int yyerror( char const * );
}

%code requires {
    #include "Ast.h"
    #include "SymbolTable.h"
    #include "Type.h"
}
%{
    int num = 0;
%}

%union {
    int itype;
    char* strtype;
    StmtNode* stmttype;
    ExprNode* exprtype;
    Type* type;
}
%start Program
%token <strtype> ID 
%token CONST
%token <itype> INTEGER
%token INT VOID CONSTINT
%token IF ELSE WHILE FOR RETURN BREAK CONTINUE
%token SCANF PRINTF 
%token ASSIGN
%token EQUAL NE LESS GREATER GE LE
%token ADD SUB
%token MUL DIV MOD
%token NOT AND OR
%token LPAREN RPAREN LBRACE RBRACE SEMICOLON COMMA

%nterm <stmttype> Stmts Stmt AssignStmt BlockStmt IfStmt ReturnStmt DeclStmt FuncDef WhileStmt EmptyStmt Params ExpStmt
%nterm <exprtype> Exp SingleExp MulExp AddExp RelExp LAndExp LOrExp PrimaryExp LVal Cond  FuncExp
%nterm <type> Type

%precedence THEN
%precedence ELSE

%%
Program
    :
    Stmts {
        
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
    | BlockStmt {$$=$1;}
    | IfStmt {$$=$1;}
    | ReturnStmt {$$=$1;}
    | DeclStmt {$$=$1;}
    | FuncDef {$$=$1;}
    | WhileStmt {$$=$1;}
    | EmptyStmt {$$=$1;}
    | ExpStmt {$$=$1;}
    ;

LVal
    : ID {
        SymbolEntry *se;
        se = identifiers->lookup($1);
        if(se == nullptr)
        {
            fprintf(stderr, "identifier \"%s\" is undefined\n", (char*)$1);
            delete [](char*)$1;
            assert(se != nullptr);
        }
        $$ = new Id(se);
        delete []$1;
    }
    ;

AssignStmt
    :
    LVal ASSIGN Exp SEMICOLON {
        $$ = new AssignStmt($1, $3);
    }
    ;

BlockStmt
    :   LBRACE 
        {identifiers = new SymbolTable(identifiers);} 
        Stmts RBRACE 
        {
            $$ = new CompoundStmt($3);
            SymbolTable *top = identifiers;
            identifiers = identifiers->getPrev();
            delete top;
        }
    ;

IfStmt
    : IF LPAREN Cond RPAREN Stmt %prec THEN {
        $$ = new IfStmt($3, $5);
    }
    | IF LPAREN Cond RPAREN Stmt ELSE Stmt {
        $$ = new IfElseStmt($3, $5, $7);
    }
    ;

WhileStmt
    : WHILE LPAREN Cond RPAREN Stmt{
        $$ = new WhileStmt($3, $5);
    }
    ;


ReturnStmt
    :
    RETURN Exp SEMICOLON{
        $$ = new ReturnStmt($2);
    }
    ;

ExpStmt
    :
    Exp SEMICOLON{
        $$ = new ExpStmt($1);
    }
    ;

Exp
    : AddExp {$$ = $1;}
    ;



Cond
    :
    LOrExp {$$ = $1;}
    ;
    
FuncExp
    :
    ID LPAREN Cond RPAREN{//只识别未实现传参
        SymbolEntry* se = nullptr;
        se = identifiers->lookup($1);
        if(se == nullptr)
        {
            fprintf(stderr, "identifier \"%s\" is undefined\n", (char*)$1);
            delete [](char*)$1;
            assert(se != nullptr);
        }
        $$ = new FuncExp(se);
    }
    | ID LPAREN RPAREN{
        SymbolEntry* se = nullptr;
        se = identifiers->lookup($1);
        if(se == nullptr)
        {
            fprintf(stderr, "identifier \"%s\" is undefined\n", (char*)$1);
            delete [](char*)$1;
            assert(se != nullptr);
        }
        $$ = new FuncExp(se);
    }
    ;
    
    
PrimaryExp
    :
    LVal {$$ = $1;}
    | 
    INTEGER 
    {
        SymbolEntry *se = new ConstantSymbolEntry(TypeSystem::intType, $1);
        $$ = new Constant(se);
    }
    | LPAREN Exp RPAREN {$$ = $2;}
    | FuncExp {$$ = $1;}
    ;

SingleExp//单目
    :
    PrimaryExp {$$ = $1;}
    |
    ADD SingleExp %prec NOT
    {
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        $$ = new SingleExpr(se, SingleExpr::ADD, $2);     
    }
    |
    SUB SingleExp %prec NOT
    {
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        $$ = new SingleExpr(se, SingleExpr::SUB, $2);     
    }
    |
    NOT SingleExp
    {
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        $$ = new SingleExpr(se, SingleExpr::NOT, $2);     
    }
    ;

MulExp
    :
    SingleExp {$$ = $1;}
    |
    MulExp MUL SingleExp
    {
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        $$ = new BinaryExpr(se, BinaryExpr::MUL, $1, $3);
    }
    |
    MulExp DIV SingleExp
    {
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        $$ = new BinaryExpr(se, BinaryExpr::DIV, $1, $3);
    }
    |
    MulExp MOD SingleExp
    {
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        $$ = new BinaryExpr(se, BinaryExpr::MOD, $1, $3);
    }
    ;

AddExp
    :
    MulExp {$$ = $1;}
    |
    AddExp ADD MulExp
    {
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        $$ = new BinaryExpr(se, BinaryExpr::ADD, $1, $3);
    }
    |
    AddExp SUB MulExp
    {
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        $$ = new BinaryExpr(se, BinaryExpr::SUB, $1, $3);
    }
    ;

RelExp
    :
    AddExp {$$ = $1;}
    |
    RelExp LESS AddExp
    {
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        $$ = new BinaryExpr(se, BinaryExpr::LESS, $1, $3);
    }
    |
    RelExp GREATER AddExp
    {
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        $$ = new BinaryExpr(se, BinaryExpr::GREATER, $1, $3);
    }
    |
    RelExp GE AddExp
    {
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        $$ = new BinaryExpr(se, BinaryExpr::GE, $1, $3);
    }
    |
    RelExp LE AddExp
    {
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        $$ = new BinaryExpr(se, BinaryExpr::LE, $1, $3);
    }
    |
    RelExp EQUAL AddExp
    {
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        $$ = new BinaryExpr(se, BinaryExpr::EQUAL, $1, $3);
    }
    |
    RelExp NE AddExp
    {
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        $$ = new BinaryExpr(se, BinaryExpr::NE, $1, $3);
    }
    ;
    

LAndExp
    :
    RelExp {$$ = $1;}
    |
    LAndExp AND RelExp
    {
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
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
    
Type
    : INT {
        $$ = TypeSystem::intType;
    }
    | VOID {
        $$ = TypeSystem::voidType;
    }
    | CONSTINT {
        $$ = TypeSystem::cintType;
    }    
    ;

EmptyStmt
    :
    SEMICOLON{
        $$ = new EmptyStmt();
    }
    | LBRACE RBRACE {$$ = new EmptyStmt();}
    ;

Params
    :
    Type ID {$$ = new ParaStmt($1,$2);}
    | 
    Type ID ASSIGN Exp{$$ = new ParaStmt($1,$2);}
    |
    Params COMMA Type ID { $$ = new ParaStmt($1,$3,$4);}
    | 
    Params COMMA Type ID ASSIGN Exp{$$ = new ParaStmt($1,$3,$4);}
    |      
    Params COMMA ID{
        ParaStmt* node = dynamic_cast<ParaStmt*>($1);
        std::vector<Type*> pts = *(node->getParamsTypes());
        $$ = new ParaStmt($1, pts.back(), $3);
    }
    | 
    Params COMMA ID ASSIGN Exp{
        ParaStmt* node = dynamic_cast<ParaStmt*>($1);
        std::vector<Type*> pts = *(node->getParamsTypes());
        $$ = new ParaStmt($1, pts.back(), $3);
    }
    ;

DeclStmt
    :
    Params SEMICOLON {
        ParaStmt* node = dynamic_cast<ParaStmt*>($1);
        std::vector<Type*> pts = *(node->getParamsTypes());
        std::vector<std::string> ids = *(node->getParamsIds());
        SymbolEntry *se;
        std::vector<Id*> id;
        for(unsigned long i=0;i<pts.size();i++)
        {
            Type* type = pts[i];
            std::string name = ids[i];
            se = new IdentifierSymbolEntry(type, name, identifiers->getLevel());
            identifiers->install(name, se);
            id.push_back(new Id(se));
        }
        $$ = new DeclStmt(id);
    }
 
    ;

FuncDef
    :

    Type ID LPAREN RPAREN {
        Type *funcType;
        funcType = new FunctionType($1,{});
        SymbolEntry *se = new IdentifierSymbolEntry(funcType, $2, identifiers->getLevel());
        identifiers->install($2, se);
        identifiers = new SymbolTable(identifiers);
    }
    BlockStmt
    {
        SymbolEntry *se;
        se = identifiers->lookup($2);
        assert(se != nullptr);
        $$ = new FunctionDef(se, $6);
        SymbolTable *top = identifiers;
        identifiers = identifiers->getPrev();
        delete top;
        delete []$2;
    }
    |
    Type ID LPAREN Params RPAREN {
        Type *funcType;
        ParaStmt* node = dynamic_cast<ParaStmt*>($4);
        std::vector<Type*> pts = *(node->getParamsTypes());
        std::vector<std::string> ids = *(node->getParamsIds());
        funcType = new FunctionType($1,pts);
        SymbolEntry *se = new IdentifierSymbolEntry(funcType, $2, identifiers->getLevel());
        identifiers->install($2, se);
        identifiers = new SymbolTable(identifiers);
        for(unsigned long i=0;i<pts.size();i++)
        {
            Type* type = pts[i];
            std::string name = ids[i];
            se = new IdentifierSymbolEntry(type, name, identifiers->getLevel());
            identifiers->install(name, se);
        }
     } BlockStmt {
        SymbolEntry *se;
        se = identifiers->lookup($2);
        assert(se != nullptr);
        $$ = new FunctionDef(se, $7);
        SymbolTable *top = identifiers;
        identifiers = identifiers->getPrev();
        delete top;
        delete []$2;
    }
    ;
%%

int yyerror(char const* message)
{
    std::cerr<<message<<std::endl;
    return -1;
}
