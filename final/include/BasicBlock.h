#ifndef __BASIC_BLOCK_H__
#define __BASIC_BLOCK_H__
#include <vector>
#include <set>
#include "Instruction.h"
#include "AsmBuilder.h"

class Function;

//基本块，基本块包含有中间代码的指令列表
//因为我们可能频繁向基本块中插入和删除指令，还有可能反向遍历指令列表，因此基本块中的指令列表适合用双向循环链表来表示
//基本块中的指令顺序执行，跳转指令只能跳转到基本块中的第一条指令，基本块中的最后一条指令只能是跳转指令或函数返回指令
//基本块中间不包含控制流指令，基本块之间形成了流图
class BasicBlock
{
    typedef std::vector<BasicBlock *>::iterator bb_iterator;

private:
    //前驱基本块列表pred和后继基本块列表succ
    std::vector<BasicBlock *> pred, succ;
    Instruction *head;
    Function *parent;
    int no;

public:
    BasicBlock(Function *);
    ~BasicBlock();
    void insertFront(Instruction *);
    void insertBack(Instruction *);
    void insertBefore(Instruction *, Instruction *);
    void remove(Instruction *);
    bool empty() const { return head->getNext() == head;}
    void output() const;
    bool succEmpty() const { return succ.empty(); };
    bool predEmpty() const { return pred.empty(); };
    void addSucc(BasicBlock *);
    void removeSucc(BasicBlock *);
    void addPred(BasicBlock *);
    void removePred(BasicBlock *);
    int getNo() { return no; };
    Function *getParent() { return parent; };
    Instruction* begin() { return head->getNext();};
    Instruction* end() { return head;};
    Instruction* rbegin() { return head->getPrev();};
    Instruction* rend() { return head;};
    bb_iterator succ_begin() { return succ.begin(); };
    bb_iterator succ_end() { return succ.end(); };
    bb_iterator pred_begin() { return pred.begin(); };
    bb_iterator pred_end() { return pred.end(); };
    int getNumOfPred() const { return pred.size(); };
    int getNumOfSucc() const { return succ.size(); };
    void genMachineCode(AsmBuilder*);
};

#endif