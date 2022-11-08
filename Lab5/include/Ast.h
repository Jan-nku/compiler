#ifndef __AST_H__
#define __AST_H__

#include <fstream>
#include <vector>
#include "Type.h"

class SymbolEntry;

class Node
{
private:
    static int counter;
    int seq;
public:
    Node();
    int getSeq() const {return seq;};
    virtual void output(int level) = 0;
};

class ExprNode : public Node
{
protected:
    SymbolEntry *symbolEntry;
public:
    ExprNode(SymbolEntry *symbolEntry) : symbolEntry(symbolEntry){};
};

//一元表达式
class SingleExpr : public ExprNode
{
private:
    int op;
    ExprNode *expr;
public:
    enum {ADD, SUB, NOT};
    SingleExpr(SymbolEntry *se, int op, ExprNode*expr) : ExprNode(se), op(op), expr(expr){};
    void output(int level);
};

class BinaryExpr : public ExprNode
{
private:
    int op;
    ExprNode *expr1, *expr2;
public:
    enum {ADD, SUB, AND, OR, LESS, MUL, DIV, MOD, EQUAL, GREATER, GE, LE, NE};
    BinaryExpr(SymbolEntry *se, int op, ExprNode*expr1, ExprNode*expr2) : ExprNode(se), op(op), expr1(expr1), expr2(expr2){};
    void output(int level);
};

class Constant : public ExprNode
{
public:
    Constant(SymbolEntry *se) : ExprNode(se){};
    void output(int level);
};

class Id : public ExprNode
{
public:
    Id(SymbolEntry *se) : ExprNode(se){};
    void output(int level);
};


class FuncExp : public ExprNode
{
public:
    FuncExp(SymbolEntry* se):ExprNode(se){};
    void output(int level);

};

class StmtNode : public Node
{
};

class CompoundStmt : public StmtNode
{
private:
    StmtNode *stmt;
public:
    CompoundStmt(StmtNode *stmt) : stmt(stmt) {};
    void output(int level);
};

class SeqNode : public StmtNode
{
private:
    StmtNode *stmt1, *stmt2;
public:
    SeqNode(StmtNode *stmt1, StmtNode *stmt2) : stmt1(stmt1), stmt2(stmt2){};
    void output(int level);
};

class DeclStmt : public StmtNode
{
private:
    std::vector<Id*> ids;
public:
    DeclStmt(std::vector<Id*> ids) : ids(ids){};
    void output(int level);
      
};

//参数
class ParaStmt : public StmtNode
{
private:
    std::vector<Type*>* paramsTypes;
    std::vector<std::string>* paramsIds;
public:
    ParaStmt(Type *type, std::string id)
    {
        paramsTypes = new std::vector<Type*>;
        paramsIds = new std::vector<std::string>;
        paramsTypes->push_back(type);
        paramsIds->push_back(id);
    }
    ParaStmt(StmtNode *node, Type *type, std::string id)
    {
        ParaStmt* pnode = dynamic_cast<ParaStmt*>(node);
        std::vector<Type*>* ppts = pnode->getParamsTypes();
        ppts -> push_back(type);
        paramsTypes = ppts;
        std::vector<std::string>* pids = pnode->getParamsIds();
        pids -> push_back(id);
        paramsIds = pids;
    }
    std::vector<Type*>* getParamsTypes()
    {
        return paramsTypes;
    }
    std::vector<std::string>* getParamsIds()
    {
        return paramsIds;
    }
    void output(int level){}
};

class EmptyStmt : public StmtNode
{
public:
    EmptyStmt(){};
    void output(int level){};
};

class ExpStmt : public StmtNode
{
private:
    ExprNode *exp;
public:
    ExpStmt(ExprNode *exp) : exp(exp){};
    void output(int level);
};

class IfStmt : public StmtNode
{
private:
    ExprNode *cond;
    StmtNode *thenStmt;
public:
    IfStmt(ExprNode *cond, StmtNode *thenStmt) : cond(cond), thenStmt(thenStmt){};
    void output(int level);
};

class IfElseStmt : public StmtNode
{
private:
    ExprNode *cond;
    StmtNode *thenStmt;
    StmtNode *elseStmt;
public:
    IfElseStmt(ExprNode *cond, StmtNode *thenStmt, StmtNode *elseStmt) : cond(cond), thenStmt(thenStmt), elseStmt(elseStmt) {};
    void output(int level);
};

class WhileStmt : public StmtNode
{
private:
    ExprNode *cond;
    StmtNode *Stmt;
public:
    WhileStmt(ExprNode *cond, StmtNode *Stmt) : cond(cond), Stmt(Stmt) {};
    void output(int level);
};

class BreakStmt : public StmtNode
{
public:
    BreakStmt(){};
    void output(int level);
};

class ContinueStmt : public StmtNode
{
public:
    ContinueStmt(){};
    void output(int level);
};


class ReturnStmt : public StmtNode
{
private:
    ExprNode *retValue;
public:
    ReturnStmt(ExprNode*retValue) : retValue(retValue) {};
    void output(int level);
};

class AssignStmt : public StmtNode
{
private:
    ExprNode *lval;
    ExprNode *expr;
public:
    AssignStmt(ExprNode *lval, ExprNode *expr) : lval(lval), expr(expr) {};
    void output(int level);
};

class FunctionDef : public StmtNode
{
private:
    SymbolEntry *se;
    StmtNode *stmt;
public:
    FunctionDef(SymbolEntry *se, StmtNode *stmt) : se(se), stmt(stmt){};
    void output(int level);
};

class Ast
{
private:
    Node* root;
public:
    Ast() {root = nullptr;}
    void setRoot(Node*n) {root = n;}
    void output();
};

#endif
