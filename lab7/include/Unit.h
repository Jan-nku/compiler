#ifndef __UNIT_H__
#define __UNIT_H__

#include <vector>
#include "Function.h"
#include "AsmBuilder.h"

//编译单元，中间代码顶层模块Unit
//包含中间代码生成时创建的函数
class Unit
{
    typedef std::vector<Function *>::iterator iterator;
    typedef std::vector<Function *>::reverse_iterator reverse_iterator;

private:
    //func_list
    std::vector<Function *> func_list;

    //新增加list
    std::vector<SymbolEntry*> global_list;
    std::vector<SymbolEntry*> declare_list;
public:
    Unit() = default;
    ~Unit() ;
    void insertFunc(Function *);
    void removeFunc(Function *);
    void output() const;
    iterator begin() { return func_list.begin(); };
    iterator end() { return func_list.end(); };
    reverse_iterator rbegin() { return func_list.rbegin(); };
    reverse_iterator rend() { return func_list.rend(); };
    void genMachineCode(MachineUnit* munit);

    void insertGlobal(SymbolEntry*);
    void insertDeclare(SymbolEntry*);
};

#endif