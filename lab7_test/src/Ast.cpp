#include "Ast.h"
#include "SymbolTable.h"
#include "Unit.h"
#include "Instruction.h"
#include "IRBuilder.h"
#include <string>
#include "Type.h"

#include <stack>
#include <vector>
#include <cassert>

extern Unit unit;
extern MachineUnit mUnit;
extern FILE *yyout;
int Node::counter = 0;
IRBuilder* Node::builder = nullptr;

Type* retType = nullptr;
bool ret = false;

Node::Node()
{
    seq = counter++;
}

void Node::backPatch(std::vector<Instruction*> &list, BasicBlock*bb)
{
    for(auto &inst:list)
    {
        if(inst->isCond())
            dynamic_cast<CondBrInstruction*>(inst)->setTrueBranch(bb);
        else if(inst->isUncond())
            dynamic_cast<UncondBrInstruction*>(inst)->setBranch(bb);
    }
}

std::vector<Instruction*> Node::merge(std::vector<Instruction*> &list1, std::vector<Instruction*> &list2)
{
    std::vector<Instruction*> res(list1);
    res.insert(res.end(), list2.begin(), list2.end());
    return res;
}

/*---------------中间代码生成---------------*/
void Ast::genCode(Unit *unit)
{
    IRBuilder *builder = new IRBuilder(unit);
    Node::setIRBuilder(builder);
    root->genCode();
}

void FunctionDef::deleteCon(BasicBlock* block){
        Instruction* i = (block)->begin();
        Instruction* last = (block)->rbegin();
        while (i != last) {
            if (i->isCond() || i->isUncond()) {
                (block)->remove(i);
            }
            i = i->getNext();
        }
}

//函数定义代码生成
/*
首先需要生成 PUSH 指令保存 FP 寄存器及一些 Callee Saved 寄存器，之后生成 MOV 指令令 FP 寄存器指向新的栈底，之后生成 SUB 指令为局部变量分配栈内空间。
分配栈空间时需要注意，一定要在完成寄存器分配后再确定实际的函数栈空间，因为有可能会有某些虚拟寄存器被溢出到栈中。
一种思路是不在目标代码生成时插入 SUB 指令，而是在后续调用 output() 函数打印目标代码时直接将该条指令打印出来，
因为在打印时已经可以获取到实际的栈内空间大小；另一种思路是先记录操作数还没有确定的指令，在指令的操作数确定后进行设置。
*/
void FunctionDef::genCode()
{
    Unit *unit = builder->getUnit();
    Function *func = new Function(unit, se);
    BasicBlock *entry = func->getEntry();
    // set the insert point to the entry basicblock of this function.
    builder->setInsertBB(entry);

    //stmt->genCode();
    if (this->decl!=nullptr){decl->genCode();}
    if (this->stmt!=nullptr){stmt->genCode();}

    /**
     * Construct control flow graph. You need do set successors and predecessors for each basic block.
     * Todo
    */
    for(auto block=func->begin();block!=func->end();block++){
        // jmp only happen at the end of a block
        Instruction* ins_begin=(*block)->begin();
        Instruction* ins_end=(*block)->rbegin();

        //删除基本块中的条件或无条件跳转语句
        Instruction* lastIns = (*block)->rbegin();
        deleteCon(*block);
        
        //针对函数的最后一条语句进行流程图绘制
        if(ins_end->isCond()){
            //如果是条件跳转语句
            BasicBlock* truebranch, *falsebranch;
            //设置好两个分支
            truebranch = dynamic_cast<CondBrInstruction*>(ins_end)->getTrueBranch();
            if(truebranch->empty()){
                //最后要做的工作就是在最后一个分支的位置要指定好ret语句
                if ((dynamic_cast<FunctionType*>(se->getType()))->getRetType() == TypeSystem::intType) {
                    new RetInstruction(new Operand(new ConstantSymbolEntry(TypeSystem::intType, 0)),truebranch);
                } else if ((dynamic_cast<FunctionType*>(se->getType()))->getRetType() == TypeSystem::floatType) {
                    new RetInstruction(new Operand(new ConstantSymbolEntry(TypeSystem::floatType, 0.0f)),truebranch);
                } else if ((dynamic_cast<FunctionType*>(se->getType()))->getRetType() == TypeSystem::voidType) {
                    new RetInstruction(nullptr, truebranch);
                }
            }
            falsebranch = dynamic_cast<CondBrInstruction*>(ins_end)->getFalseBranch();
            if(falsebranch->empty()){
                //保证无论函数是true还是false都有正确的ret语句
                if ((dynamic_cast<FunctionType*>(se->getType()))->getRetType() == TypeSystem::intType) {
                    new RetInstruction(new Operand(new ConstantSymbolEntry(TypeSystem::intType, 0)),falsebranch);
                } else if ((dynamic_cast<FunctionType*>(se->getType()))->getRetType() == TypeSystem::floatType) {
                    new RetInstruction(new Operand(new ConstantSymbolEntry(TypeSystem::floatType, 0.0f)),falsebranch);
                } else if ((dynamic_cast<FunctionType*>(se->getType()))->getRetType() == TypeSystem::voidType) {
                    new RetInstruction(nullptr, falsebranch);
                }
            }
            //框架代码，生成控制流图
            (*block)->addSucc(truebranch);
            (*block)->addSucc(falsebranch);
            truebranch->addPred((*block));
            falsebranch->addPred((*block));
        }
        else if(ins_end->isUncond()){
            BasicBlock* branch = dynamic_cast<UncondBrInstruction*>(ins_end)->getBranch();
            branch->addPred((*block));
            (*block)->addSucc(branch);
            //无条件跳转指令的生成代码
            if(branch->empty()){
                if ((dynamic_cast<FunctionType*>(se->getType()))->getRetType() == TypeSystem::intType) {
                    new RetInstruction(new Operand(new ConstantSymbolEntry(TypeSystem::intType, 0)),branch);
                } else if ((dynamic_cast<FunctionType*>(se->getType()))->getRetType() == TypeSystem::floatType) {
                    new RetInstruction(new Operand(new ConstantSymbolEntry(TypeSystem::floatType, 0.0f)),branch);
                } else if ((dynamic_cast<FunctionType*>(se->getType()))->getRetType() == TypeSystem::voidType) {
                    new RetInstruction(nullptr, branch);
                }
            }
        }
    }
}

//二元表达式代码生成
void BinaryExpr::genCode() {
    BasicBlock* bb = builder->getInsertBB();
    Function* func = bb->getParent();
    if (op == AND) {
        BasicBlock* trueBB = new BasicBlock(
            func);  // if the result of lhs is true, jump to the trueBB.
        expr1->genCode();
        backPatch(expr1->trueList(), trueBB);
        builder->setInsertBB(
            trueBB);  // set the insert point to the trueBB so that intructions
                      // generated by expr2 will be inserted into it.
        expr2->genCode();
        true_list = expr2->trueList();
        false_list = merge(expr1->falseList(), expr2->falseList());
    } else if (op == OR) {
        // Todo
        BasicBlock* trueBB = new BasicBlock(func);
        expr1->genCode();
        backPatch(expr1->falseList(), trueBB);
        builder->setInsertBB(trueBB);
        expr2->genCode();
        true_list = merge(expr1->trueList(), expr2->trueList());
        false_list = expr2->falseList();
    } else if (op >= LESS && op <= NOTEQUAL) {
        // Todo
        expr1->genCode();
        expr2->genCode();
        Operand* src1 = expr1->getOperand();
        Operand* src2 = expr2->getOperand();
        if (src1->getType()->getSize() == 1) {
            Operand* dst = new Operand(new TemporarySymbolEntry(
                TypeSystem::intType, SymbolTable::getLabel()));
            new ZextInstruction(dst, src1, bb);
            src1 = dst;
        }
        if (src2->getType()->getSize() == 1) {
            Operand* dst = new Operand(new TemporarySymbolEntry(
                TypeSystem::intType, SymbolTable::getLabel()));
            new ZextInstruction(dst, src2, bb);
            src2 = dst;
        }
        int cmpopcode = -1;
        switch (op) {
            case LESS:
                cmpopcode = CmpInstruction::L;
                break;
            case LESSEQUAL:
                cmpopcode = CmpInstruction::LE;
                break;
            case GREATER:
                cmpopcode = CmpInstruction::G;
                break;
            case GREATEREQUAL:
                cmpopcode = CmpInstruction::GE;
                break;
            case EQUAL:
                cmpopcode = CmpInstruction::E;
                break;
            case NOTEQUAL:
                cmpopcode = CmpInstruction::NE;
                break;
        }
        new CmpInstruction(cmpopcode, dst, src1, src2, bb);
        BasicBlock *truebb, *falsebb, *tempbb;
        truebb = new BasicBlock(func);
        falsebb = new BasicBlock(func);
        tempbb = new BasicBlock(func);

        true_list.push_back(new CondBrInstruction(truebb, tempbb, dst, bb));

        false_list.push_back(new UncondBrInstruction(falsebb, tempbb));
    } else if (op >= ADD && op <= MOD) {
        expr1->genCode();
        expr2->genCode();
        Operand* src1 = expr1->getOperand();
        Operand* src2 = expr2->getOperand();
        int opcode = -1;
        switch (op) {
            case ADD:
                opcode = BinaryInstruction::ADD;
                break;
            case SUB:
                opcode = BinaryInstruction::SUB;
                break;
            case MUL:
                opcode = BinaryInstruction::MUL;
                break;
            case DIV:
                opcode = BinaryInstruction::DIV;
                break;
            case MOD:
                opcode = BinaryInstruction::MOD;
                break;
        }
        new BinaryInstruction(opcode, dst, src1, src2, bb);
    }
}

void Constant::genCode()
{
    // we don't need to generate code.
}

void Id::genCode() {
    BasicBlock* bb = builder->getInsertBB();
    Operand* addr =
        dynamic_cast<IdentifierSymbolEntry*>(symbolEntry)->getAddr();
    if(this->getType()->isInt()||this->getType()->isFloat()||this->getType()->isBool())
        new LoadInstruction(dst, addr, bb);
    //针对数组
    //主要思想就是多维的 先把上一维度的地址找到 然后根据下标找下一个维度
    else if (this->getType()->isArray()) 
    {
        //遍历维度
        if (arrayIndices) 
        {
            //获取当前类型和元素类型
            Type* type = ((ArrayType*)(this->getType()))->getElementType();
            Type* type1 = type;
            
            Operand* tempSrc = addr;//中间目标地址
            Operand* tempDst = dst;//中间目标值
            
            ExprNode* idx = arrayIndices;
            //标识GepInstruction的paramFirst
            //主要是用于区分函数参数a[][3]的情况
            bool flag = false;
            
            bool pointer = false;
            bool firstFlag = true;
            
            while (true) 
            {
               //针对参数是数组的情况  a[][3]
               //把基址加载到tempSrc
                if (((ArrayType*)type1)->getLength() == -1) 
                {
                    Operand* dst1 = new Operand(new TemporarySymbolEntry(
                        new PointerType(type), SymbolTable::getLabel()));
                    tempSrc = dst1;//中间变量
                    new LoadInstruction(dst1, addr, bb);
                    
                    
                    flag = true;
                    firstFlag = false;
                }
                //如果维度遍历结束 将对应数组值传递到dst 然后退出
                if (!idx) {
                    Operand* dst1 = new Operand(new TemporarySymbolEntry(
                        new PointerType(type), SymbolTable::getLabel()));
                    Operand* idx = new Operand(
                        new ConstantSymbolEntry(TypeSystem::intType, 0));
                    new GepInstruction(dst1, tempSrc, idx, bb);
                    tempDst = dst1;
                    pointer = true;
                    break;
                }
                //生成维度
                idx->genCode();
                //用于维度寻址 将tempSrc[idx]的值加载到tempDst
                auto gep = new GepInstruction(tempDst, tempSrc,
                                              idx->getOperand(), bb, flag);
                //如果当前不是a[][3]这种情况
                //并且是第一个维度寻址
                if (!flag && firstFlag) 
                {
                    gep->setFirst();
                    firstFlag = false;
                }
                //flag每个参数都要重置
                if (flag)
                    flag = false;
                //维度要全部换成整数的维度    
                if (type == TypeSystem::intType ||
                    type == TypeSystem::constIntType)
                    break;
                type = ((ArrayType*)type)->getElementType();
                type1 = ((ArrayType*)type1)->getElementType();
                tempSrc = tempDst;
                tempDst = new Operand(new TemporarySymbolEntry(
                    new PointerType(type), SymbolTable::getLabel()));
                idx = (ExprNode*)(idx->getNext());
            }
            dst = tempDst;
            
            
            // 如果此ID是右值 需要再次load
            if (!left && !pointer) 
            {
                Operand* dst1 = new Operand(new TemporarySymbolEntry(
                    TypeSystem::intType, SymbolTable::getLabel()));
                new LoadInstruction(dst1, dst, bb);
                dst = dst1;
            }
        } 
        //针对声明数组的情况 和上面类似
        else 
        {
            if (((ArrayType*)(this->getType()))->getLength() == -1) 
            {
                Operand* dst1 = new Operand(new TemporarySymbolEntry(
                    new PointerType(
                        ((ArrayType*)(this->getType()))->getElementType()),
                    SymbolTable::getLabel()));
                new LoadInstruction(dst1, addr, bb);
                dst = dst1;
            } 
            else 
            {
                Operand* idx = new Operand(
                    new ConstantSymbolEntry(TypeSystem::intType, 0));
                auto gep = new GepInstruction(dst, addr, idx, bb);
                gep->setFirst();
            }
        }
    }
}


void IfStmt::genCode()
{
    Function *func;
    BasicBlock *then_bb, *end_bb;

    func = builder->getInsertBB()->getParent();
    then_bb = new BasicBlock(func);
    end_bb = new BasicBlock(func);

    cond->genCode();
    backPatch(cond->trueList(), then_bb);
    backPatch(cond->falseList(), end_bb);

    builder->setInsertBB(then_bb);
    thenStmt->genCode();
    //因为生成thenStmt 结点中间代码的过程中可能改变指令的插入点，因此更新插入点
    then_bb = builder->getInsertBB();
    new UncondBrInstruction(end_bb, then_bb);

    builder->setInsertBB(end_bb);
}

//IfElse语句代码生成
void IfElseStmt::genCode()
{
    // Todo
    Function *func;
    BasicBlock *then_bb, *else_bb, *end_bb;
    func = builder->getInsertBB()->getParent();

    then_bb = new BasicBlock(func);
    else_bb = new BasicBlock(func);
    end_bb = new BasicBlock(func);

    cond->genCode();
    backPatch(cond->trueList(), then_bb);
    backPatch(cond->falseList(), else_bb);

    builder->setInsertBB(then_bb);
    thenStmt->genCode();
    then_bb = builder->getInsertBB();
    new UncondBrInstruction(end_bb, then_bb);
    builder->setInsertBB(else_bb);
    elseStmt->genCode();
    else_bb = builder->getInsertBB();
    new UncondBrInstruction(end_bb, else_bb);

    builder->setInsertBB(end_bb);
}

void EmptyStmt::genCode()
{
    //空语句不用生成代码
}

void ExprStmt::genCode()
{
    if(this->expr)
        this->expr->genCode();
}

void ContinueStmt::genCode()
{
    Function* func = builder->getInsertBB()->getParent();
    BasicBlock* bb = builder->getInsertBB();
    new UncondBrInstruction(((WhileStmt*)whileStmt)->getCond(), bb);
    BasicBlock* continue_next_bb = new BasicBlock(func);
    builder->setInsertBB(continue_next_bb);
}

void BreakStmt::genCode() {
    Function* func = builder->getInsertBB()->getParent();
    BasicBlock* bb = builder->getInsertBB();
    new UncondBrInstruction(((WhileStmt*)whileStmt)->getFinal(), bb);
    BasicBlock* break_next_bb = new BasicBlock(func);
    builder->setInsertBB(break_next_bb);
}

void WhileStmt::genCode()
{
    Function* func;
    BasicBlock *condbb, *truebb, *finalbb, *nowbb;
    nowbb = builder->getInsertBB();
    func = builder->getInsertBB()->getParent();
    condbb = new BasicBlock(func);
    truebb = new BasicBlock(func);
    finalbb = new BasicBlock(func);
    setCondbb(condbb);
    setFinalbb(finalbb);

    //增加无条件跳转语句，随后生成条件的中间代码
    new UncondBrInstruction(condbb, nowbb);
    builder->setInsertBB(condbb);
    cond->genCode();
    backPatch(cond->trueList(), truebb);
    backPatch(cond->falseList(), finalbb);
    builder->setInsertBB(truebb);
    stmt->genCode();
    truebb = builder->getInsertBB();

    //同理，在truebb加入条件判断，每执行一回合就要去cond
    new UncondBrInstruction(condbb, truebb);
    builder->setInsertBB(finalbb);
}

void CompoundStmt::genCode()
{
    // Todo
    if(this->stmt){
        this->stmt->genCode();
    }
}

void SeqNode::genCode()
{
    // Todo
    if(this->stmt1){
        this->stmt1->genCode();
    }
    if(this->stmt2){
        this->stmt2->genCode();
    }
}


void DeclStmt::genCode() {
    IdentifierSymbolEntry* se =
        dynamic_cast<IdentifierSymbolEntry*>(id->getSymbolEntry());
    if (se->isGlobal()) {
        Operand* addr;
        SymbolEntry* addr_se;
        addr_se = new IdentifierSymbolEntry(*se);
        addr_se->setType(new PointerType(se->getType()));
        addr = new Operand(addr_se);
        se->setAddr(addr);
        unit.insertGlobal(se);
        mUnit.insertGlobal(se);
    } else if (se->isLocal() || se->isParam()) {
        Function* func = builder->getInsertBB()->getParent();
        BasicBlock* entry = func->getEntry();
        Instruction* alloca;
        Operand* addr;
        SymbolEntry* addr_se;
        Type* type;
        // if (se->isParam() && se->getType()->isArray())
        //     type = new PointerType(TypeSystem::intType);
        // else
        type = new PointerType(se->getType());
        addr_se = new TemporarySymbolEntry(type, SymbolTable::getLabel());
        addr = new Operand(addr_se);
        alloca = new AllocaInstruction(addr, se);
        // allocate space for local id in function stack.
        entry->insertFront(alloca);  // allocate instructions should be inserted
                                     // into the begin of the entry block.
        Operand* temp = nullptr;
        if (se->isParam())
            temp = se->getAddr();
        se->setAddr(addr);  // set the addr operand in symbol entry so that
                            // we can use it in subsequent code generation.
                            // can use it in subsequent code generation.
        if (expr) {
            if (expr->isInitValueListExpr()) {
                Operand* init = nullptr;
                BasicBlock* bb = builder->getInsertBB();
                ExprNode* temp = expr;
                std::stack<ExprNode*> stk;
                std::vector<int> idx;
                idx.push_back(0);
                while (temp) {
                    if (temp->isInitValueListExpr()) {
                        stk.push(temp);
                        idx.push_back(0);
                        temp = ((ArrayInit*)temp)->getExpr();
                        continue;
                    } else {
                        temp->genCode();
                        Type* type =
                            ((ArrayType*)(se->getType()))->getElementType();
                        Operand* tempSrc = addr;
                        Operand* tempDst;
                        Operand* index;
                        bool flag = true;
                        int i = 1;
                        while (true) {
                            tempDst = new Operand(new TemporarySymbolEntry(
                                new PointerType(type),
                                SymbolTable::getLabel()));
                            index = (new Constant(new ConstantSymbolEntry(
                                         TypeSystem::intType, idx[i++])))
                                        ->getOperand();
                            auto gep =
                                new GepInstruction(tempDst, tempSrc, index, bb);
                            gep->setInit(init);
                            if (flag) {
                                gep->setFirst();
                                flag = false;
                            }
                            if (type == TypeSystem::intType ||
                                type == TypeSystem::constIntType) {
                                gep->setLast();
                                init = tempDst;
                                break;
                            }
                            type = ((ArrayType*)type)->getElementType();
                            tempSrc = tempDst;
                        }
                        new StoreInstruction(tempDst, temp->getOperand(), bb);
                    }
                    while (true) {
                        if (temp->getNext()) {
                            temp = (ExprNode*)(temp->getNext());
                            idx[idx.size() - 1]++;
                            break;
                        } else {
                            temp = stk.top();
                            stk.pop();
                            idx.pop_back();
                            if (stk.empty())
                                break;
                        }
                    }
                    if (stk.empty())
                        break;
                }
            } else {
                BasicBlock* bb = builder->getInsertBB();
                expr->genCode();
                Operand* src = expr->getOperand();
                new StoreInstruction(addr, src, bb);
            }
        }
        if (se->isParam()) {
            BasicBlock* bb = builder->getInsertBB();
            new StoreInstruction(addr, temp, bb);
        }
    }
    if (this->getNext()) {
        this->getNext()->genCode();
    }
}


/*
void DeclStmt::genCode()
{
 IdentifierSymbolEntry* se = dynamic_cast<IdentifierSymbolEntry*>(id->getSymbolEntry());
    if (se->isGlobal()) {
        //全局变量的填写
        Operand* addr;
        SymbolEntry* addr_se;
        addr_se = new IdentifierSymbolEntry(*se);
        addr_se->setType(new PointerType(se->getType()));
        addr = new Operand(addr_se);
        se->setAddr(addr);
        unit.insertGlobal(se);
        mUnit.insertGlobal(se);
    } else if (se->isLocal() || se->isParam()) {
        //局部变量的填写
        Function* func = builder->getInsertBB()->getParent();
        BasicBlock* entry = func->getEntry();
        Instruction* alloca;
        Operand* addr;
        SymbolEntry* addr_se;
        Type* type;
        type = new PointerType(se->getType());
        addr_se = new TemporarySymbolEntry(type, SymbolTable::getLabel());
        addr = new Operand(addr_se);
        alloca = new AllocaInstruction(addr, se);
                                                              // allocate space for local id in function stack.
        entry->insertFront(alloca);                           // allocate instructions should be inserted
                                                              // into the begin of the entry block.
        Operand* temp;
        if (se->isParam()){
            temp = se->getAddr();
        }
        se->setAddr(addr);  

        //有初始化的情况
        if (expr) {
            //先计算值，再把值写入内存
                BasicBlock* bb = builder->getInsertBB();
                expr->genCode();
                Operand* src = expr->getOperand();
                new StoreInstruction(addr, src, bb);
        }
        if (se->isParam()) {
            //如果是参数，直接store
            BasicBlock* bb = builder->getInsertBB();
            new StoreInstruction(addr, temp, bb);
        }
    }
    //可能一次声明很多id
    if (this->getNext()) {
        this->getNext()->genCode();
    }
}
*/


//返回语句代码生成
void ReturnStmt::genCode()
{
    // Todo
    Operand* ret;
    if(retValue !=nullptr){
        retValue->genCode();
        ret = retValue->getOperand();
    }
    else{
        ret = nullptr;
    }
    BasicBlock* bb = builder->getInsertBB();
    new RetInstruction(ret, bb);
}

//赋值语句代码生成
void AssignStmt::genCode()
{
    BasicBlock *bb = builder->getInsertBB();
    expr->genCode();
    Operand *addr;
    if(lval->getType()->isInt()||lval->getType()->isFloat()){
        addr = dynamic_cast<IdentifierSymbolEntry*>(lval->getSymPtr())->getAddr();
    }
    else if(lval->getType()->isArray()){
        ((Id*)lval)->setLeft();
        lval->genCode();
        addr = lval->getOperand();
    }
    Operand *src = expr->getOperand();
    /***
     * We haven't implemented array yet, the lval can only be ID. So we just store the result of the `expr` to the addr of the id.
     * If you want to implement array, you have to caculate the address first and then store the result into it.
     */
    new StoreInstruction(addr, src, bb);
}

//数组代码生成
void ArrayInit::genCode()
{

}

FuncExpr::FuncExpr(SymbolEntry* se, ExprNode* param): ExprNode(se), param(param){
    if(se){
        if(dynamic_cast<FunctionType*>(se->getType())->getRetType()->isInt()){
            SymbolEntry* temp = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
            dst = new Operand(temp);
        }
        else if(dynamic_cast<FunctionType*>(se->getType())->getRetType()->isFloat()){
            SymbolEntry* temp = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
            dst = new Operand(temp);
        }
    }
};
void FuncExpr::genCode()
{
    std::vector<Operand*> operands;
    ExprNode* paramTemp = param;
    while (paramTemp) {
        //把需要的参数压进去
        paramTemp->genCode();
        operands.push_back(paramTemp->getOperand());
        paramTemp = (ExprNode*)paramTemp->getNext();
    }
    BasicBlock* bb = builder->getInsertBB();
    new CallInstruction(dst, symbolEntry, operands, bb);
}

void UnaryExpr::genCode()
{
    BasicBlock* bb = builder->getInsertBB();
    expr->genCode();
    Type* unaryExprType = expr->getType();
    Operand* src = expr->getOperand();
    Operand* zero = nullptr;
    switch (op)
    {
    case SUB:
        if(unaryExprType->isFloat())
            zero = new Operand(new ConstantSymbolEntry(TypeSystem::floatType,0.0f));
        else if(unaryExprType->isBool()){
            zero = new Operand(new ConstantSymbolEntry(TypeSystem::intType,0));
            src = new Operand(new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel()));
            new ZextInstruction(src, expr->getOperand(), bb);
        }
        else{
            zero = new Operand(new ConstantSymbolEntry(TypeSystem::intType,0));
        }
        new BinaryInstruction(BinaryInstruction::SUB, dst, zero, src, bb);
        break;
    case NOT:
        if(unaryExprType->isInt() || unaryExprType->isFloat()){
            Operand* temp = new Operand(new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel()));
            new CmpInstruction(CmpInstruction::NE, temp, src, new Operand(new ConstantSymbolEntry(TypeSystem::intType, 0)),bb);
            src = temp;
        }
        new XorInstruction(dst, src, bb);
    }
}


/*---------------类型检查---------------*/

void Ast::typeCheck()
{
    if(root != nullptr)
        root->typeCheck();
}

void FunctionDef::typeCheck()
{
    // Todo
    ret = false;

    Type* funcRetType=((FunctionType*)(this->se->getType()))->getRetType();
    if(this->stmt==nullptr && funcRetType!=TypeSystem::voidType){
        fprintf(stderr, "function %s must return a vaild value\n",this->se->toStr().c_str());
        return;
    }
    
    retType = funcRetType;
    if(this->stmt != nullptr)
        this->stmt->typeCheck();

    if(!funcRetType->isVoid() && !ret){
        fprintf(stderr, "function \"%s\" shoule return a vaild type\n",this->se->toStr().c_str());

        assert(!funcRetType->isVoid() && !ret == false);
    }
}

void BinaryExpr::typeCheck()
{
    // Todo
    if(this->expr1->getType()->isVoid() || this->expr2->getType()->isVoid()){
        fprintf(stderr, "void expr cannot in a BinaryExpr\n");
        assert(false);
    }
}

void Constant::typeCheck()
{
    // Todo
}

void Id::typeCheck()
{
    // Todo
}

void IfStmt::typeCheck()
{
    // Todo
    if(this->cond)
        this->cond->typeCheck();
    if(this->thenStmt!=nullptr)
        this->thenStmt->typeCheck();
}

void IfElseStmt::typeCheck()
{
    // Todo
    if(this->thenStmt)
        this->thenStmt->typeCheck();
    if(this->elseStmt)
        this->elseStmt->typeCheck();
}

void CompoundStmt::typeCheck()
{
    // Todo
    if(this->stmt)
        this->stmt->typeCheck();
}

void SeqNode::typeCheck()
{
    // Todo
    if(this->stmt1)
        this->stmt1->typeCheck();
    if(this->stmt2)
        this->stmt2->typeCheck();
}

void DeclStmt::typeCheck()
{
    // Todo
    if(this->expr)
        expr->typeCheck();
    
    if(this->getNext())
        this->getNext()->typeCheck();
}

void ReturnStmt::typeCheck()
{
    // Todo
    Type* funcRetType;
    if(!this->retValue && !retType->isVoid()){
        fprintf(stderr, "you should return %s, but return void\n",retType->toStr().c_str());
        //assert(!this->retValue && !retType->isVoid() == false);
    }
    if(!this->retValue && retType->isVoid()){
        goto Out;
    }
    if(this->retValue && retType->isVoid()){
        fprintf(stderr, "you should return void, but return %s\n",this->retValue->getSymbolEntry()->getType()->toStr().c_str());
        //assert(this->retValue && retType->isVoid() == false);
    }
    funcRetType = this->retValue->getSymbolEntry()->getType();
    if(funcRetType->isFunc())
        funcRetType = dynamic_cast<FunctionType*>(funcRetType)->getRetType();
    if(this->retValue && funcRetType!=retType){
        if((retType->isInt() && funcRetType->isInt())||(retType->isFloat() && funcRetType->isFloat()))
            goto Out;
        if(this->retValue->getSymbolEntry()->getType()->isFunc())
        fprintf(stderr, "you should return:%s, but return %s\n",retType->toStr().c_str(),
                this->retValue->getSymbolEntry()->getType()->toStr().c_str());
        //assert(this->retValue->getSymbolEntry()->getType() ==retType);
    }
Out:
    ret = true;
}

void AssignStmt::typeCheck()
{
    // Todo
    if(this->lval)
        this->lval->typeCheck();
    if(this->expr)
        this->expr->typeCheck();
}

void EmptyStmt::typeCheck()
{
    //to nothing
}

void ExprStmt::typeCheck()
{
    if(expr)
        expr->typeCheck();
}

void ContinueStmt::typeCheck()
{
    if(this->whileStmt==nullptr)
        fprintf(stderr, "\"continue\" should be included in a while stmt ");
}

void BreakStmt::typeCheck()
{
    if(this->whileStmt==nullptr)
        fprintf(stderr, "\"break\" should be included in a while stmt ");
}

void WhileStmt::typeCheck()
{
    if(this->stmt)
        this->stmt->typeCheck();
}

void ArrayInit::typeCheck()
{

}

void FuncExpr::typeCheck()
{

}

void UnaryExpr::typeCheck()
{
    if(this->expr->getType()->isVoid()){
        fprintf(stderr, "void expr cannot in a unaryExpr\n");
        assert(false);
    }
}


/*---------------中间代码打印---------------*/
void Ast::output()
{
    fprintf(yyout, "program\n");
    if(root != nullptr)
        root->output(4);
}

Type* ExprNode::getType(){
    if(!symbolEntry){
        return nullptr;
    }
    if(this->symbolEntry->getType()->isFunc())
        return ((FunctionType*)this->symbolEntry->getType())->getRetType();
    return this->symbolEntry->getType();
}

void UnaryExpr::output(int level) {
    std::string op_str;
    switch (op) {
        case NOT:
            op_str = "not";
            break;
        case SUB:
            op_str = "minus";
            break;
        case ADD:
            op_str = "add";    
    }
    fprintf(yyout, "%*cUnaryExpr\top: %s\n", level, ' ', op_str.c_str());
    expr->output(level + 4);
}

int UnaryExpr::getIValue() {
    int value;
    switch(op) {
        case NOT :
            value=!(expr->getIValue());
            break;
        case SUB:
            value=-(expr->getIValue());
            break;
        case ADD:
            value=+(expr->getIValue());
            break;
    }
    return value;
}

float UnaryExpr::getFValue() {
    float fvalue;
    switch(op) {
        case NOT :
            fvalue=!(expr->getFValue());
            break;
        case SUB:
            fvalue=-(expr->getFValue());
            break;
        case ADD:
            fvalue=+(expr->getFValue());
            break;
    }
    return fvalue;
}

void FuncExpr::output(int level) {
    std::string name, type;
    int scope;
    name = symbolEntry->toStr();
    type = symbolEntry->getType()->toStr();
    scope = dynamic_cast<IdentifierSymbolEntry*>(symbolEntry)->getScope();
    fprintf(yyout, "%*cCallExpr\tfunction name: %s\tscope: %d\ttype: %s\n",
            level, ' ', name.c_str(), scope, type.c_str());
    Node* temp = param;
    while (temp) {
        temp->output(level + 4);
        temp = temp->getNext();
    }
}

void BinaryExpr::output(int level) {
    std::string op_str;
    switch (op) {
        case ADD:
            op_str = "add";
            break;
        case SUB:
            op_str = "sub";
            break;
        case MUL:
            op_str = "mul";
            break;
        case DIV:
            op_str = "div";
            break;
        case MOD:
            op_str = "mod";
            break;
        case AND:
            op_str = "and";
            break;
        case OR:
            op_str = "or";
            break;
        case LESS:
            op_str = "less";
            break;
        case LESSEQUAL:
            op_str = "lessequal";
            break;
        case GREATER:
            op_str = "greater";
            break;
        case GREATEREQUAL:
            op_str = "greaterequal";
            break;
        case EQUAL:
            op_str = "equal";
            break;
        case NOTEQUAL:
            op_str = "notequal";
            break;
    }
    fprintf(yyout, "%*cBinaryExpr\top: %s\n", level, ' ', op_str.c_str());
    expr1->output(level + 4);
    expr2->output(level + 4);
}

int BinaryExpr::getIValue(){
    int v;
    switch(op){
        case ADD:
            v=expr1->getIValue() + expr2->getIValue();
            break;
        case SUB:
            v=expr1->getIValue() - expr2->getIValue();
            break;
        case MUL:
            v=expr1->getIValue() * expr2->getIValue();
            break;
        case DIV:
            v=expr1->getIValue() / expr2->getIValue();
            break;
        case MOD:
            v=expr1->getIValue() % expr2->getIValue();
            break;
        case AND:
            v=expr1->getIValue() && expr2->getIValue();
            break;
        case OR:
            v=expr1->getIValue() || expr2->getIValue();
            break;
        case LESS:
            v=expr1->getIValue() < expr2->getIValue();
            break;
        case LESSEQUAL:
            v=expr1->getIValue() <= expr2->getIValue();
            break;
        case GREATER:
            v=expr1->getIValue() > expr2->getIValue();
            break;
        case GREATEREQUAL:
            v=expr1->getIValue() >= expr2->getIValue();
            break;
        case EQUAL:
            v=expr1->getIValue() == expr2->getIValue();
            break;
        case NOTEQUAL:
            v=expr1->getIValue() != expr2->getIValue();
            break;
    }
    return v;
}

float BinaryExpr::getFValue(){
    float v;
    switch(op){
        case ADD:
            v=expr1->getFValue() + expr2->getFValue();
            break;
        case SUB:
            v=expr1->getFValue() - expr2->getFValue();
            break;
        case MUL:
            v=expr1->getFValue() * expr2->getFValue();
            break;
        case DIV:
            v=expr1->getFValue() / expr2->getFValue();
            break;
        case MOD:
            //c++要求MOD只能是整数，这里强行取整
            v=expr1->getIValue() % expr2->getIValue();
            break;
        case AND:
            v=expr1->getFValue() && expr2->getFValue();
            break;
        case OR:
            v=expr1->getFValue() || expr2->getFValue();
            break;
        case LESS:
            v=expr1->getFValue() < expr2->getFValue();
            break;
        case LESSEQUAL:
            v=expr1->getFValue() <= expr2->getFValue();
            break;
        case GREATER:
            v=expr1->getFValue() > expr2->getFValue();
            break;
        case GREATEREQUAL:
            v=expr1->getFValue() >= expr2->getFValue();
            break;
        case EQUAL:
            v=expr1->getFValue() == expr2->getFValue();
            break;
        case NOTEQUAL:
            v=expr1->getFValue() != expr2->getFValue();
            break;
    }
    return v;
}

void Constant::output(int level)
{
    std::string type, value;
    type = symbolEntry->getType()->toStr();
    value = symbolEntry->toStr();
    fprintf(yyout, "%*cIntegerLiteral\tvalue: %s\ttype: %s\n", level, ' ',
            value.c_str(), type.c_str());
}

int Constant::getIValue(){
    int v;
    v=((ConstantSymbolEntry*)symbolEntry)->getValue();
    return v;
}
float Constant::getFValue(){
    float v;
    v=((ConstantSymbolEntry*)symbolEntry)->getFvalue();
    return v;
}

void Id::output(int level)
{
    std::string name, type;
    int scope;
    name = symbolEntry->toStr();
    type = symbolEntry->getType()->toStr();
    scope = dynamic_cast<IdentifierSymbolEntry*>(symbolEntry)->getScope();
    fprintf(yyout, "%*cId\tname: %s\tscope: %d\ttype: %s\n", level, ' ',
            name.c_str(), scope, type.c_str());
}

void ArrayInit::output(int level)
{
    std::string type;
    if (symbolEntry->getType())
        type = symbolEntry->getType()->toStr();
    fprintf(yyout, "%*cArrayInit\ttype: %s\n", level, ' ',
            type.c_str());
    Node* temp = expr;
    while (temp) {
        temp->output(level + 4);
        temp = temp->getNext();
    }
    /*
    std::string type;
    type = symbolEntry->getType()->toStr();
    if(!fullZero){
        fprintf(yyout, "%*ctype: %s\n", level, ' ',type.c_str());
        ExprNode*temp=expr;
        while (temp){
            temp->output(level + 4);
            temp=(ExprNode*)temp->getNext();
        }
    }
    else{
        fprintf(yyout, "%*ctype: %s\tzero array\n", level, ' ',type.c_str());
    }
    */
}

void ArrayInit::addExpr(ExprNode* expr){
    fullZero=false;
    childExprCount++;
    if(this->expr==nullptr){
        this->expr=expr;
        return;
    }
    this->expr->setNext(expr);
}

bool ArrayInit::isFull(){
    ArrayType* type = (ArrayType*)(this->symbolEntry->getType());
    return childExprCount == type->getLength();
}

void ArrayInit::fill() {
    Type* type = ((ArrayType*)(this->getType()))->getElementType();
    if (type->isArray()) {
        while (!this->isFull())
            this->addExpr(new ArrayInit(new ConstantSymbolEntry(type)));
        ExprNode* temp = expr;
        while (temp) {
            ((ArrayInit*)temp)->fill();
            temp = (ExprNode*)(temp->getNext());
        }
    }
    if (type->isInt()) {
        while (!this->isFull())
            this->addExpr(new Constant(new ConstantSymbolEntry(type, 0)));
        return;
    }
}

void CompoundStmt::output(int level)
{
    fprintf(yyout, "%*cCompoundStmt\n", level, ' ');
    if(stmt){
        stmt->output(level + 4);
    }
}

void SeqNode::output(int level)
{
    stmt1->output(level);
    stmt2->output(level);
}

void DeclStmt::output(int level)
{
    fprintf(yyout, "%*cDeclStmt\n", level, ' ');
    id->output(level + 4);
    if (expr)
        expr->output(level + 4);
    if (this->getNext()) {
        this->getNext()->output(level);
    }
}

void IfStmt::output(int level)
{
    fprintf(yyout, "%*cIfStmt\n", level, ' ');
    cond->output(level + 4);
    thenStmt->output(level + 4);
}

void IfElseStmt::output(int level)
{
    fprintf(yyout, "%*cIfElseStmt\n", level, ' ');
    cond->output(level + 4);
    thenStmt->output(level + 4);
    elseStmt->output(level + 4);
}

void WhileStmt::output(int level) {
    fprintf(yyout, "%*cWhileStmt\n", level, ' ');
    cond->output(level + 4);
    stmt->output(level + 4);
}

void BreakStmt::output(int level) {
    fprintf(yyout, "%*cBreakStmt\n", level, ' ');
}

void ContinueStmt::output(int level) {
    fprintf(yyout, "%*cContinueStmt\n", level, ' ');
}

void ReturnStmt::output(int level)
{
    fprintf(yyout, "%*cReturnStmt\n", level, ' ');
    if(retValue!=nullptr)
        retValue->output(level + 4);
}

void AssignStmt::output(int level)
{
    fprintf(yyout, "%*cAssignStmt\n", level, ' ');
    lval->output(level + 4);
    expr->output(level + 4);
}

void FunctionDef::output(int level)
{
    std::string name, type;
    name = se->toStr();
    type = se->getType()->toStr();
    fprintf(yyout, "%*cFunctionDefine\tfunction name: %s\ttype: %s\n", level,
            ' ', name.c_str(), type.c_str());
    if (decl) {
        decl->output(level + 4);
    }
    stmt->output(level + 4);
}

void ExprStmt::output(int level) {
    fprintf(yyout, "%*cExprStmt\n", level, ' ');
    expr->output(level + 4);
}

void EmptyStmt::output(int level) {
    fprintf(yyout, "%*cExprStmt\n", level, ' ');
}
