class FuncDef : public StmtNode
{
private:
    SymbolEntry *se;
    StmtNode *stmt;
    ExprNode* funcFParams;
public:
    FuncDef(SymbolEntry *se, StmtNode *stmt,ExprNode* funcFParams=nullptr):se(se), stmt(stmt),funcFParams(funcFParams){};
    void output(int level);
};

class FuncFParams: public ExprNode
{
private:
    ExprNode* prevParam;
    ExprNode* lastParam;
public:
    FuncFParams(SymbolEntry *se,ExprNode *lastParam,ExprNode* prevParam=nullptr):ExprNode(se),prevParam(prevParam),lastParam(lastParam){};
    void output(int level);
};

class FuncFParam: public ExprNode
{
private:
    Id* Param;
    ExprNode* arry;
public:
    FuncFParam(SymbolEntry *se,Id *Param=nullptr,ExprNode* arry=nullptr):ExprNode(se),Param(Param){};
    void output(int level);
};

class FuncArrayList:public ExprNode
{
private:
    ExprNode* empty;
    ExprNode* Expr1;
public:
    FuncArrayList(SymbolEntry *se,ExprNode *empty=nullptr,ExprNode* Expr1=nullptr):ExprNode(se),empty(empty),Expr1(Expr1){};
    void output(int level);
};

class FuncCallStmt: public StmtNode
{
private: 
    ExprNode* funccall;
public:
    FuncCallStmt(ExprNode* funccall):funccall(funccall){};
    void output(int level);
};

class FuncCall : public ExprNode
{
private:
    SymbolEntry *se;
    ExprNode * parms;
public:
    FuncCall(SymbolEntry *sp,SymbolEntry *se,ExprNode *parms=nullptr):ExprNode(sp),se(se),parms(parms){};
    void output(int level);
};

class Arguments: public ExprNode
{
private:
    ExprNode* prevParam;
    ExprNode* lastParam;
public:
    Arguments(SymbolEntry *se,ExprNode *lastParam,ExprNode* prevParam=nullptr):ExprNode(se),prevParam(prevParam),lastParam(lastParam){};
    void output(int level);   
};

class Argument: public ExprNode
{
private:
    ExprNode* Param;
public:
    Argument(SymbolEntry *se,ExprNode *Param):ExprNode(se),Param(Param){};
    void output(int level);
};