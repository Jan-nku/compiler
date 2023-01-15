#ifndef __FUNCTION_H__
#define __FUNCTION_H__

#include <vector>
#include <map>
#include <set>
#include <stack>
#include <algorithm>
#include <iostream>
#include "Ast.h"
#include "BasicBlock.h"
#include "SymbolTable.h"
#include "AsmBuilder.h"

class Unit;

//函数模块，函数由多个基本块构成
//每个函数都有一个entry基本块，它是函数的入口节点；exit基本块作为函数的出口节点
class Function
{
    typedef std::vector<BasicBlock *>::iterator iterator;
    typedef std::vector<BasicBlock *>::reverse_iterator reverse_iterator;

private:
    std::vector<BasicBlock *> block_list;
    SymbolEntry *sym_ptr;
    BasicBlock *entry;
    Unit *parent;

public:
    Function(Unit *, SymbolEntry *);
    ~Function();
    void insertBlock(BasicBlock *bb) { block_list.push_back(bb); };
    BasicBlock *getEntry() { return entry; };
    void remove(BasicBlock *bb);
    void output() const;
    std::vector<BasicBlock *> &getBlockList(){return block_list;};
    iterator begin() { return block_list.begin(); };
    iterator end() { return block_list.end(); };
    reverse_iterator rbegin() { return block_list.rbegin(); };
    reverse_iterator rend() { return block_list.rend(); };
    SymbolEntry *getSymPtr() { return sym_ptr; };
    void genMachineCode(AsmBuilder*);
};

#endif
