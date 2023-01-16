#ifndef __AST_H__
#define __AST_H__

#include <fstream>
#include "Operand.h"
#include "Type.h"

class SymbolEntry;
class Unit;
class Function;
class BasicBlock;
class Instruction;
class IRBuilder;

class Node
{
private:
    static int counter;
    int seq;

    //增加指针域next，将关联节点串起来
    Node* next = nullptr;

protected:
    //通过回填技术来完成控制流的翻译
    //为每个结点设置两个综合属性 true_list 和 false_list, 它们是跳转目标未确定的跳转指令的列表
    //回填是指当跳转的目标基本块确定时，设置列表中跳转指令的跳转目标为该基本块。
    std::vector<Instruction*> true_list;
    std::vector<Instruction*> false_list;

    //builder是IRBuilder类对象，用于传递继承属性，辅助我们进行中间代码生成
    static IRBuilder *builder;

    //backPatch、merge操作
    void backPatch(std::vector<Instruction*> &list, BasicBlock*bb);
    std::vector<Instruction*> merge(std::vector<Instruction*> &list1, std::vector<Instruction*> &list2);

public:
    Node();
    int getSeq() const {return seq;};
    Node* getNext(){return next;};
    void setNext(Node* node) {
        Node* n = this;
        while (n->getNext()) {
            n = n->getNext();
        }
        if (n == this) {
            this->next = node;
        } else {
            n->setNext(node);
        }
    }
    static void setIRBuilder(IRBuilder*ib) {builder = ib;};
    virtual void output(int level) = 0;
    virtual void typeCheck() = 0;
    virtual void genCode() = 0;
    std::vector<Instruction*>& trueList() {return true_list;}
    std::vector<Instruction*>& falseList() {return false_list;}
};

class ExprNode : public Node
{
private:
    int kind;
protected:
    enum { EXPR, INITVALUELISTEXPR};
    SymbolEntry *symbolEntry;
    Operand *dst;   // The result of the subtree is stored into dst.
public:
    ExprNode(SymbolEntry *symbolEntry, int kind = EXPR) : symbolEntry(symbolEntry){};
    Operand* getOperand() {return dst;};
    SymbolEntry* getSymPtr() {return symbolEntry;};
    SymbolEntry *getSymbolEntry(){return symbolEntry;}
    Type* getType();
    bool isExpr() const { return kind == EXPR; };
    bool isInitValueListExpr() const { return kind == INITVALUELISTEXPR; };
    virtual int getIValue(){return -1;};
    virtual float getFValue(){return -1.0;};
    //纯虚函数
    void output(int level){};
    void typeCheck(){};
    void genCode(){};
};

//增加UnaryExp类
class UnaryExpr : public ExprNode
{
private:
    int op;
    ExprNode *expr;
public:
    enum {SUB,ADD,NOT};
    UnaryExpr(SymbolEntry *se, int op, ExprNode *expr) : ExprNode(se), op(op), expr(expr){
        dst=new Operand(se);
    };
    void output(int level);
    int getIValue();
    float getFValue();
    void typeCheck();
    void genCode();
};

class FuncExpr : public ExprNode {
private:
    ExprNode* param;
public:
    FuncExpr(SymbolEntry* se, ExprNode* param = nullptr);
    void output(int level);
    int getIValue(){return 0;};
    float getFValue(){return 0.0;};
    void typeCheck();
    void genCode();
};

class BinaryExpr : public ExprNode
{
private:
    int op;
    ExprNode *expr1, *expr2;
public:
    enum {ADD, SUB, MUL, DIV, MOD, AND, OR, LESS, LESSEQUAL, GREATER, GREATEREQUAL, EQUAL, NOTEQUAL};
    BinaryExpr(SymbolEntry *se, int op, ExprNode*expr1, ExprNode*expr2) : ExprNode(se), op(op), expr1(expr1), expr2(expr2){dst = new Operand(se);};
    void output(int level);
    int getIValue();
    float getFValue();
    void typeCheck();
    void genCode();
};

class Constant : public ExprNode
{
public:
    Constant(SymbolEntry *se) : ExprNode(se){dst=new Operand(se);};
    int getvalue(){return ((ConstantSymbolEntry*)symbolEntry)->getValue(); }
    void output(int level);
    int getIValue();
    float getFValue();
    void typeCheck();
    void genCode();
};

class Id : public ExprNode
{
private:
    bool left = false;
    ExprNode *arrayIndices;
public:
    Id(SymbolEntry *se ,ExprNode *arrayIndices=nullptr) : ExprNode(se),arrayIndices(arrayIndices){
        left=false;
        if(se){
            if(getType()->isInt()){
                SymbolEntry* temp = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
                dst = new Operand(temp);
            }else if(getType()->isFloat()){
                SymbolEntry* temp = new TemporarySymbolEntry(TypeSystem::floatType,SymbolTable::getLabel());
                dst = new Operand(temp);
            }else if(getType()->isArray()){
                SymbolEntry* temp = new TemporarySymbolEntry(new PointerType(dynamic_cast<ArrayType*>(getType())->getElementType()),SymbolTable::getLabel());
                dst = new Operand(temp);
            }
        }
    };
    SymbolEntry* getSymbolEntry(){return symbolEntry;};
    void output(int level);
    std::string getValue(){return symbolEntry->toStr();}
    int getIValue(){return (int)getFValue();};
    float getFValue(){
        SymbolTable* nowTable=identifiers;
        while(nowTable){
            if(nowTable->lookup(getValue())){
                return ((IdentifierSymbolEntry*)(identifiers->lookup(getValue())))->getValue();
            }
            else{
                nowTable=nowTable->getPrev();
            }
        }
        return 0.0;
    }
    void typeCheck();
    void genCode();
    void setLeft(){left=true;};
};

class ArrayInit : public ExprNode
{
private:
    ExprNode* expr;
    int childExprCount;
    bool fullZero;
public:
    ArrayInit(SymbolEntry* se, bool fullZero = false):ExprNode(se, INITVALUELISTEXPR),fullZero(fullZero) {
            childExprCount=0;
            expr=nullptr;
            dst=new Operand(se);
    };
    void output(int level);
    ExprNode* getExpr() const { return expr; };
    void addExpr(ExprNode* expr);
    bool isEmpty() { return childExprCount == 0; };
    bool isFull();
    int getIValue(){return 0;};
    float getFValue(){return 0;};
    void typeCheck();
    void genCode();
    bool isFullZero() {return fullZero;};
    void setFullZero() {fullZero =true;};
    void fill();
};

class StmtNode : public Node
{};

class CompoundStmt : public StmtNode
{
private:
    StmtNode *stmt;
public:
    CompoundStmt(StmtNode *stmt = nullptr) : stmt(stmt) {};
    void output(int level);
    void typeCheck();
    void genCode();
};

class SeqNode : public StmtNode
{
private:
    StmtNode *stmt1, *stmt2;
public:
    SeqNode(StmtNode *stmt1, StmtNode *stmt2) : stmt1(stmt1), stmt2(stmt2){};
    void output(int level);
    void typeCheck();
    void genCode();
};

class DeclStmt : public StmtNode
{
private:
    Id *id;
    ExprNode *expr;  
public:
    DeclStmt(Id* id, ExprNode* expr = nullptr) : id(id) {
        if (expr) {
            this->expr = expr;
            if (expr->isInitValueListExpr())
                ((ArrayInit*)(this->expr))->fill();
        }
    };
    Id* getId(){return id;}
    void output(int level);
    void typeCheck();
    void genCode();
};

class IfStmt : public StmtNode
{
private:
    ExprNode *cond;
    StmtNode *thenStmt;
public:
    IfStmt(ExprNode *cond, StmtNode *thenStmt) : cond(cond), thenStmt(thenStmt){};
    void output(int level);
    void typeCheck();
    void genCode();
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
    void typeCheck();
    void genCode();
};

class WhileStmt : public StmtNode
{
private:
    ExprNode *cond;
    StmtNode *stmt;
    BasicBlock* condBB, *endBB;

public:
    WhileStmt(ExprNode *cond, StmtNode *stmt) : cond(cond), stmt(stmt){condBB=endBB=nullptr;};
    void setStmt(StmtNode* stmt){this->stmt=stmt;};
    void output(int level);
    void typeCheck();
    void genCode();
    BasicBlock* getCond(){return condBB;};
    BasicBlock* getFinal(){return endBB;};
    void setCondbb(BasicBlock*cond_bb){this->condBB=cond_bb;};
    void setFinalbb(BasicBlock*end_bb){this->endBB=end_bb;};
};

class BreakStmt : public StmtNode 
{
private:
    WhileStmt* whileStmt;
public:
    BreakStmt(WhileStmt* whileStmt){this->whileStmt=whileStmt;};
    void output(int level);
    void typeCheck();
    void genCode();
};

class ContinueStmt : public StmtNode 
{
private:
    WhileStmt* whileStmt;
public:
    ContinueStmt(WhileStmt* whileStmt){this->whileStmt=whileStmt;};
    void output(int level);
    void typeCheck();
    void genCode();
};

class ReturnStmt : public StmtNode
{
private:
    ExprNode *retValue;
public:
    ReturnStmt(ExprNode*retValue = nullptr) : retValue(retValue) {};
    void output(int level);
    void typeCheck();
    void genCode();
};

class AssignStmt : public StmtNode
{
private:
    ExprNode *lval;
    ExprNode *expr;
public:
    AssignStmt(ExprNode *lval, ExprNode *expr) : lval(lval), expr(expr) {};
    void output(int level);
    void typeCheck();
    void genCode();
};

class ExprStmt : public StmtNode
{
private:
    ExprNode* expr;
public:
    ExprStmt(ExprNode* expr) : expr(expr){};
    void output(int level);
    void typeCheck();
    void genCode();
};

class EmptyStmt : public StmtNode
{
public:
    EmptyStmt(){};
    void output(int level);
    void typeCheck();
    void genCode();
};

class FunctionDef : public StmtNode
{
private:
    SymbolEntry* se;
    DeclStmt* decl;
    StmtNode* stmt;

public:
    FunctionDef(SymbolEntry* se, DeclStmt* decl, StmtNode* stmt)
        : se(se), decl(decl), stmt(stmt){};
    void output(int level);
    void deleteCon(BasicBlock*block);
    void typeCheck();
    void genCode();
};

//抽象语法树
class Ast
{
private:
    Node* root;
public:
    Ast() {root = nullptr;}
    void setRoot(Node*n) {root = n;}
    //AST输出
    void output();
    //类型检查
    void typeCheck();
    //中间代码生成
    void genCode(Unit *unit);
};

#endif

/*typecheck*/
//变量未声明，及在同一作用域下重复声明
//条件判断表达式 int 至 bool 类型隐式转换
//数值运算表达式运算数类型是否正确 (可能导致此错误的情况有返回值为 void 的函数调用结果参与了某表达式计算)
//函数未声明，及不符合重载要求的函数重复声明
//函数调用时形参及实参类型或数目的不一致
//return 语句操作数和函数声明的返回值类型是否匹配
//实现了数组要求的同学，还可以对数组维度进行相应的类型检查
//实现了 break、continue 语句要求的同学，还可以对 break、continue 语句进行静态检查，判断是否仅出现在 while 语句中

/*类型检查最简单的实现方式是在建立语法树的过程中进行相应的识别和处理，也可以在建树完成后，自底向上遍历语法树进行类型检查。*/
/*类型检查过程中，父结点需要检查孩子结点的类型，并根据孩子结点类型确定自身类型*/

/*中间代码生成*/
//词法分析和语法分析是编译器的前端，中间代码是编译器的中端，目标代码是编译器的后端
//中间代码生成的总体思路是对抽象语法树作一次遍历，遍历的过程中需要根据综合属性和继承属性来生成各结点的中间代码，在生成完根结点的中间代码后便得到了最终结果。