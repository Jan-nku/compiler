
FuncDef//函数定义
    :
    Type ID LPAREN RPAREN BlockStmt{
		Type *funcType;
        funcType = new FunctionType($1,{});
        SymbolEntry *se = new IdentifierSymbolEntry(funcType, $2, identifiers->getLevel());
        identifiers->install($2, se);
        identifiers = new SymbolTable(identifiers);
        se = identifiers->lookup($2);
        assert(se != nullptr);
        $$ = new FuncDef(se, $5);
        SymbolTable *top = identifiers;
        identifiers = identifiers->getPrev();
        delete top;
        delete []$2;
    }
    |
    Type ID LPAREN{
        Type *funcType;
        funcType = new FunctionType($1,{});
        SymbolEntry *se = new IdentifierSymbolEntry(funcType, $2, identifiers->getLevel());
        identifiers->install($2, se);
        identifiers = new SymbolTable(identifiers);
    }
    FuncFParams RPAREN
    BlockStmt{
        SymbolEntry *se;
        se = identifiers->lookup($2);
        assert(se != nullptr);
        $$ = new FuncDef(se, $7,$5);
        SymbolTable *top = identifiers;
        identifiers = identifiers->getPrev();
        delete top;
        delete []$2;
    }
    ;
FuncFParams//函数形参列表
    :
    FuncFParam {$$ = $1;}
    | 
	FuncFParams COMMA FuncFParam{
        SymbolEntry *sg = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        FuncFParams(sg,$1,$3);
    }
    ;
FuncFParam//函数形参
    :
    Type ID{
        SymbolEntry *se;
        SymbolEntry *sg = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        se = new IdentifierSymbolEntry($1, $2, identifiers->getLevel());
        identifiers->install($2, se);
        $$=new FuncFParam(sg,new Id(se));
    }
    |
    Type ID FuncArrayList{
        SymbolEntry *se;
        SymbolEntry *sg = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        se = new IdentifierSymbolEntry($1, $2, identifiers->getLevel());
        identifiers->install($2, se);
        $$=new FuncFParam(sg,new Id(se),$3);
    }
    ;

FuncArrayList://函数传递数组
    LBRACKET RBRACKET{
        SymbolEntry *sg = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        $$=new FuncArrayList(sg);
    }
    |
    FuncArrayList LBRACKET Exp RBRACKET{
        SymbolEntry *sg = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        $$=new FuncArrayList(sg,$1,$3);
    }
    ;
FuncCall//函数调用
    :
    ID LPAREN RPAREN{
        SymbolEntry *se;
        se = identifiers->lookup($1);
        SymbolEntry *sg = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        $$ = new FuncCall(sg,se);
    }
    |
    ID LPAREN Arguments RPAREN{
        SymbolEntry *se;
        se = identifiers->lookup($1);
        SymbolEntry *sg = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        $$ = new FuncCall(sg,se,$3);
    }
    ;

Arguments//实参列表
    :
    Exp{
        SymbolEntry *sg = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        $$= new Arguments(sg,$1);
    }
    |
    Arguments COMMA Exp{
        SymbolEntry *sg = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        $$=new Arguments(sg,$1,$3);
    }
    ;
