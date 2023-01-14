#include "MachineCode.h"
#include "Type.h"
extern FILE* yyout;

//这里原来有个label是用在我没填满的那个函数里的！！！
MachineOperand::MachineOperand(int tp, int val)
{
    this->type = tp;
    if(tp == MachineOperand::IMM)
        this->val = val;
    else 
        this->reg_no = val;
}

MachineOperand::MachineOperand(std::string label)
{
    this->type = MachineOperand::LABEL;
    this->label = label;
}

bool MachineOperand::operator==(const MachineOperand&a) const
{
    if (this->type != a.type)
        return false;
    if (this->type == IMM)
        return this->val == a.val;
    return this->reg_no == a.reg_no;
}

bool MachineOperand::operator<(const MachineOperand&a) const
{
    if(this->type == a.type)
    {
        if(this->type == IMM)
            return this->val < a.val;
        return this->reg_no < a.reg_no;
    }
    return this->type < a.type;

    if (this->type != a.type)
        return false;
    if (this->type == IMM)
        return this->val == a.val;
    return this->reg_no == a.reg_no;

}

void MachineOperand::PrintReg()
{
    switch (reg_no)
    {
    case 11:
        fprintf(yyout, "fp");
        break;
    case 13:
        fprintf(yyout, "sp");
        break;
    case 14:
        fprintf(yyout, "lr");
        break;
    case 15:
        fprintf(yyout, "pc");
        break;
    default:
        fprintf(yyout, "r%d", reg_no);
        break;
    }
}

void MachineOperand::output() 
{
    /* HINT：print operand
    * Example:
    * immediate num 1 -> print #1;
    * register 1 -> print r1;
    * lable addr_a -> print addr_a; */
    switch (this->type)
    {
    case IMM:
        fprintf(yyout, "#%d", this->val);
        break;
    case VREG:
        fprintf(yyout, "v%d", this->reg_no);
        break;
    case REG:
        PrintReg();
        break;
    case LABEL:
        if (this->label.substr(0, 2) == ".L")
            fprintf(yyout, "%s", this->label.c_str());
        //不一样！！！！！
        else
            fprintf(yyout, "addr_%s", this->label.c_str());
    default:
        break;
    }
}

void MachineInstruction::PrintCond()
{
    // TODO
    switch (cond)
    {
    case LT:
        fprintf(yyout, "lt");
        break;
    case EQ:
		fprintf(yyout, "eq");
		break;
	case NE:
		fprintf(yyout, "ne");
		break;
	case LE:
		fprintf(yyout, "le");
		break;
	case GT:
		fprintf(yyout, "gt");
		break;
	case GE:
		fprintf(yyout, "ge");
		break;    
    default:
        break;
    }
}
//insert before && insert after
void MachineInstruction::insertBefore(MachineInstruction* inst) {
    auto& instructions = parent->getInsts();
    auto it = std::find(instructions.begin(), instructions.end(), this);
    instructions.insert(it, inst);
}

void MachineInstruction::insertAfter(MachineInstruction* inst) {
    auto& instructions = parent->getInsts();
    auto it = std::find(instructions.begin(), instructions.end(), this);
    instructions.insert(++it, inst);
}
BinaryMInstruction::BinaryMInstruction(
    MachineBlock* p, int op, 
    MachineOperand* dst, MachineOperand* src1, MachineOperand* src2, 
    int cond)
{
    this->parent = p;
    this->type = MachineInstruction::BINARY;
    this->op = op;
    this->cond = cond;
    this->def_list.push_back(dst);
    this->use_list.push_back(src1);
    this->use_list.push_back(src2);
    dst->setParent(this);
    src1->setParent(this);
    src2->setParent(this);
}

void BinaryMInstruction::output() 
{
    // TODO: 
    // Complete other instructions
    switch (this->op)
    {
    case BinaryMInstruction::ADD:
        fprintf(yyout, "\tadd ");
        this->PrintCond();
        this->def_list[0]->output();
        fprintf(yyout, ", ");
        this->use_list[0]->output();
        fprintf(yyout, ", ");
        this->use_list[1]->output();
        fprintf(yyout, "\n");
        break;
    case BinaryMInstruction::SUB:
        fprintf(yyout, "\tsub ");
        this->PrintCond();
        this->def_list[0]->output();
        fprintf(yyout, ", ");
        this->use_list[0]->output();
        fprintf(yyout, ", ");
        this->use_list[1]->output();
        fprintf(yyout, "\n");
        break;
    case BinaryMInstruction::MUL:
        fprintf(yyout, "\tmul ");
        this->PrintCond();
        this->def_list[0]->output();
        fprintf(yyout, ", ");
        this->use_list[0]->output();
        fprintf(yyout, ", ");
        this->use_list[1]->output();
        fprintf(yyout, "\n");
        break;
    case BinaryMInstruction::DIV:
        fprintf(yyout, "\tsdiv ");
        this->PrintCond();
        this->def_list[0]->output();
        fprintf(yyout, ", ");
        this->use_list[0]->output();
        fprintf(yyout, ", ");
        this->use_list[1]->output();
        fprintf(yyout, "\n");
        break;
	case BinaryMInstruction::AND:
		fprintf(yyout, "\tand ");
		this->PrintCond();
		this->def_list[0]->output();
		fprintf(yyout, ", ");
		this->use_list[0]->output();
		fprintf(yyout, ", ");
		this->use_list[1]->output();
		fprintf(yyout, "\n");
		break;
	case BinaryMInstruction::OR:
		fprintf(yyout, "\torr ");
		this->PrintCond();
		this->def_list[0]->output();
		fprintf(yyout, ", ");
		this->use_list[0]->output();
		fprintf(yyout, ", ");
		this->use_list[1]->output();
		fprintf(yyout, "\n");
		break;
    default:
        break;
    }
}

LoadMInstruction::LoadMInstruction(MachineBlock* p,
    MachineOperand* dst, MachineOperand* src1, MachineOperand* src2,
    int cond)
{
    this->parent = p;
    this->type = MachineInstruction::LOAD;
    this->op = -1;
    this->cond = cond;
    this->def_list.push_back(dst);
    this->use_list.push_back(src1);
    if (src2)
        this->use_list.push_back(src2);
    dst->setParent(this);
    src1->setParent(this);
    if (src2)
        src2->setParent(this);
}

void LoadMInstruction::output()
{
    fprintf(yyout, "\tldr ");
    this->def_list[0]->output();
    fprintf(yyout, ", ");

    // Load immediate num, eg: ldr r1, =8
    if(this->use_list[0]->isImm())
    {
        fprintf(yyout, "=%d\n", this->use_list[0]->getVal());
        return;
    }
    
    // Load address
    if(this->use_list[0]->isReg()||this->use_list[0]->isVReg())
        fprintf(yyout, "[");
    
    this->use_list[0]->output();
    if( this->use_list.size() > 1 )
    {
        fprintf(yyout, ", ");
        this->use_list[1]->output();
    }
    
    if(this->use_list[0]->isReg()||this->use_list[0]->isVReg())
        fprintf(yyout, "]");
    fprintf(yyout, "\n");

}

StoreMInstruction::StoreMInstruction(MachineBlock* p,
    MachineOperand* src1, MachineOperand* src2, MachineOperand* src3, 
    int cond)
{
    // TODO
    this->parent = p;
    this->type = MachineInstruction::STORE;
    this->op = -1;
    this->cond = cond;
    this->use_list.push_back(src1);
    this->use_list.push_back(src2);
    if (src3)
        this->use_list.push_back(src3);
    src1->setParent(this);
    src2->setParent(this);
    if (src3)
        src3->setParent(this);
}

void StoreMInstruction::output()
{
    // TODO
    fprintf(yyout, "\tstr ");
    this->use_list[0]->output();
    fprintf(yyout, ", ");
    //这个if是我多加的
    if(this->use_list[1]->isImm())
    {
        fprintf(yyout, "=%d\n", this->use_list[0]->getVal());
        return;
    }

    // Store address
    if(this->use_list[1]->isReg()||this->use_list[1]->isVReg())
        fprintf(yyout, "[");
    
    this->use_list[1]->output();
    if( this->use_list.size() > 2 )
    {
        fprintf(yyout, ", ");
        this->use_list[2]->output();
    }
    
    if(this->use_list[1]->isReg()||this->use_list[1]->isVReg())
        fprintf(yyout, "]");
    fprintf(yyout, "\n");

}

MovMInstruction::MovMInstruction(MachineBlock* p, int op, 
    MachineOperand* dst, MachineOperand* src,
    int cond)
{
    // TODO
    this->parent = p;
    this->type = MachineInstruction::MOV;
    this->op = op;
    this->cond = cond;
    this->def_list.push_back(dst);
    this->use_list.push_back(src);
    dst->setParent(this);
    src->setParent(this);
}

void MovMInstruction::output() 
{
    // TODO
    fprintf(yyout, "\tmov");
    PrintCond();
    fprintf(yyout, " ");
    this->def_list[0]->output();
    fprintf(yyout, ", ");
    this->use_list[0]->output();
    fprintf(yyout, "\n");

}

BranchMInstruction::BranchMInstruction(MachineBlock* p, int op, 
    MachineOperand* dst, 
    int cond)
{
    // TODO
    this->parent = p;
    this->type = MachineInstruction::BRANCH;
    this->op = op;
    this->cond = cond;
    this->def_list.push_back(dst);//这地我改了！！！,注意下一个对应函数
    dst->setParent(this);
}

void BranchMInstruction::output()
{
    // TODO
    if (this->op == B) {
		fprintf(yyout, "\tb");
		PrintCond();
		fprintf(yyout, " ");
		this->def_list[0]->output();
		fprintf(yyout, "\n");
	}
	if (this->op == BL) {
		fprintf(yyout, "\tbl");
		PrintCond();
		fprintf(yyout, " ");
		this->def_list[0]->output();
		fprintf(yyout, "\n");
	}
	if (this->op == BX) {
		fprintf(yyout, "\tbx");
		PrintCond();
		fprintf(yyout, " ");
		this->def_list[0]->output();
		fprintf(yyout, "\n");
	}
}

CmpMInstruction::CmpMInstruction(MachineBlock* p, 
    MachineOperand* src1, MachineOperand* src2, 
    int cond)
{
    // TODO
     this->parent = p;
    this->type = MachineInstruction::CMP;
    this->op = -1;
    this->cond = cond;
    //p->setCmpCond(cond);//这地我先注释掉！！！
    this->use_list.push_back(src1);
    this->use_list.push_back(src2);
    src1->setParent(this);
    src2->setParent(this);
}

void CmpMInstruction::output()
{
    // TODO
    // Jsut for reg alloca test
    // delete it after test
    fprintf(yyout, "\tcmp ");
    this->use_list[0]->output();
    fprintf(yyout, ", ");
    this->use_list[1]->output();
    fprintf(yyout, "\n");
}
//先抄上，到时候看着改改
StackMInstrcuton::StackMInstrcuton(MachineBlock* p, int op, 
                std::vector<MachineOperand*> src, MachineOperand* src1,MachineOperand* src2,
                int cond)
{
    // TODO
    this->parent = p;
    this->type = MachineInstruction::STACK;
    this->op = op;
    this->cond = cond;
    if(!src.empty())
    {
        for(auto i=src.begin() ; i!=src.end();i++)
            this->use_list.push_back(*i);
    }
    this->use_list.push_back(src1);
    src1->setParent(this);
    if(src2)
    {
        this->use_list.push_back(src2);
        src2->setParent(this);
    }
}

void StackMInstrcuton::output()
{
    // TODO
    switch (op) {
        case PUSH:
            fprintf(yyout, "\tpush ");
            break;
        case POP:
            fprintf(yyout, "\tpop ");
            break;
    }
    fprintf(yyout, "{");
    this->use_list[0]->output();
    for (int i = 1; i < use_list.size(); i++) {//改了个大小
        fprintf(yyout, ", ");
        this->use_list[i]->output();
    }
    fprintf(yyout, "}\n");
}

MachineFunction::MachineFunction(MachineUnit* p, SymbolEntry* sym_ptr) 
{ 
    this->parent = p; 
    this->sym_ptr = sym_ptr; 
    this->stack_size = 0;
    //少了个paramsnum
};

void MachineBlock::output()
{
    fprintf(yyout, ".L%d:\n", this->no);
    for(auto iter : inst_list)
        iter->output();
    //他们代码上补了一堆，先暂时这么跑
}

void MachineFunction::output()
{
    const char *func_name = this->sym_ptr->toStr().c_str() + 1;
    fprintf(yyout, "\t.global %s\n", func_name);
    fprintf(yyout, "\t.type %s , %%function\n", func_name);
    fprintf(yyout, "%s:\n", func_name);
    // TODO
    /* Hint:
    *  1. Save fp
    *  2. fp = sp
    *  3. Save callee saved register
    *  4. Allocate stack space for local variable */
    

    // Traverse all the block in block_list to print assembly code.
    auto fp = new MachineOperand(MachineOperand::REG, 11);
    auto sp = new MachineOperand(MachineOperand::REG, 13);
    auto lr = new MachineOperand(MachineOperand::REG, 14);
    (new StackMInstrcuton(nullptr, StackMInstrcuton::PUSH, get_saved_regs(), fp,lr))->output();
    (new MovMInstruction(nullptr, MovMInstruction::MOV, fp, sp))->output();
    int off = AllocSpace(0);
    auto size = new MachineOperand(MachineOperand::IMM, off);
    if (off < -255 || off > 255) {
        auto r4 = new MachineOperand(MachineOperand::REG, 4);
        (new LoadMInstruction(nullptr, r4, size))->output();
        (new BinaryMInstruction(nullptr, BinaryMInstruction::SUB, sp, sp, r4))
            ->output();
    } else {
        (new BinaryMInstruction(nullptr, BinaryMInstruction::SUB, sp, sp, size))
            ->output();
    }
    int count = 0;
    for (auto iter : block_list) {
        iter->output();
        count += iter->getSize();
        if(count > 160){
            fprintf(yyout, "\tb .F%d\n", parent->getnum());
            fprintf(yyout, ".LTORG\n");
            //parent->printGlobal();这部分相当于把他的内联了
            for(auto i : parent->getglobs())
            {
                IdentifierSymbolEntry* temp = (IdentifierSymbolEntry*)i;
                fprintf(yyout, "addr_%s%d:\n", temp->toStr().c_str(), parent->incnum());
                fprintf(yyout, "\t.word %s\n", temp->toStr().c_str());
            }
            fprintf(yyout, ".F%d:\n", parent->getnum()-1);
            count = 0;
        }
    }
    fprintf(yyout, "\n");

}

std::vector<MachineOperand*> MachineFunction::get_saved_regs() {
    std::vector<MachineOperand*> regs;
    for (auto it = saved_regs.begin(); it != saved_regs.end(); it++) {
        auto reg = new MachineOperand(MachineOperand::REG, *it);
        regs.push_back(reg);
    }
    return regs;
}

void MachineUnit::PrintGlobalDecl()
{
    // TODO:
    // You need to print global variable/const declarition code;
    std::vector<IdentifierSymbolEntry*> const_list;
    std::vector<IdentifierSymbolEntry*> zero_list;
    if(global_list.size()>0)
    {
        fprintf(yyout,"\t.data\n");
        //下面不再push下标，而是push元素
        for(auto i:global_list)//注意数据大小
        {
            IdentifierSymbolEntry* temp=(IdentifierSymbolEntry*)i;
            if(temp->getConst())
            {
                const_list.push_back(temp);
            }
            else if(temp->isAllZero())
            {
                zero_list.push_back(temp);
            }
            else
            {
                fprintf(yyout, "\t.global %s\n", temp->toStr().c_str());
                fprintf(yyout, "\t.align 4\n");
                fprintf(yyout, "\t.size %s, %d\n", temp->toStr().c_str(),
                    temp->getType()->getSize() / 8);
                fprintf(yyout,"%s:\n",temp->toStr().c_str());
                if(temp->getType()->isArray())
                {
                    int* start_of_array=temp->getArrayValue();
                    for(int i=0;i<temp->getType()->getSize()/32;i++)
                        fprintf(yyout,"\t.word %d\n",start_of_array[i]);
                }
                else
                {
                    fprintf(yyout,"\t.word %d\n",temp->getValue());
                }
            }
        }
    }
    if(!const_list.empty())
    {
        fprintf(yyout,"\t.section .rodata\n");
        for(auto i:const_list)
        {
            fprintf(yyout, "\t.global %s\n", i->toStr().c_str());
            fprintf(yyout, "\t.align 4\n");
            fprintf(yyout, "\t.size %s, %d\n", i->toStr().c_str(),
                    i->getType()->getSize() / 8);
            fprintf(yyout, "%s:\n", i->toStr().c_str());
            if(i->getType()->isArray())
            {
                int* start_of_array=i->getArrayValue();
                for(int j=0;j<i->getType()->getSize()/32;j++)
                    fprintf(yyout,"\t.word %d\n",start_of_array[j]);
            }
            else
            {
                fprintf(yyout,"\t.word %d\n",i->getValue());
            }
        }
    }
    if(!zero_list.empty())
    {
        for(auto i : zero_list)
            if(i->getType()->isArray())
            {
                fprintf(yyout, "\t.comm %s, %d, 4\n", i->toStr().c_str(),
                        i->getType()->getSize() / 8);
            }
    }
}

void MachineUnit::output()
{
    // TODO
    /* Hint:
    * 1. You need to print global variable/const declarition code;
    * 2. Traverse all the function in func_list to print assembly code;
    * 3. Don't forget print bridge label at the end of assembly code!! */
    fprintf(yyout, "\t.arch armv8-a\n");
    fprintf(yyout, "\t.arch_extension crc\n");
    fprintf(yyout, "\t.arm\n");
    PrintGlobalDecl();
    fprintf(yyout, "\t.text\n");
    for(auto iter : func_list)
        iter->output();
    //print bridge label
    for(auto i : global_list){
        IdentifierSymbolEntry* temp=(IdentifierSymbolEntry*)i;
        fprintf(yyout, "addr_%s%d:\n",temp->toStr().c_str(),uniquenum++);//原来是函数结束前n++！！！
        fprintf(yyout,"\t.word %s\n",temp->toStr().c_str());
    }
}