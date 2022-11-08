
void FuncDef::output(int level)
{
    std::string name, type;
    name = se->toStr();
    type = se->getType()->toStr();
    fprintf(yyout, "%*cFunctionDefine function name: %s, type: %s\n", level, ' ', 
            name.c_str(), type.c_str());
    if(funcFParams!=nullptr)
        funcFParams->output(level+4);
    stmt->output(level + 4);
}

void FuncFParams::output(int level){
    fprintf(yyout,"%*cfuncParams\n", level, ' ');
    lastParam->output(level+4);
    prevParam->output(level+4);
}

void FuncFParam::output(int level){
    fprintf(yyout,"%*cfuncParam\n", level, ' ');
    Param->output(level+4);
}

void FuncArrayList::output(int level){
    fprintf(yyout,"%*cFuncArraylist\n", level, ' ');
    if(empty==nullptr)
        fprintf(yyout,"%*cEmpty[ ]\n", level+4, ' ');
    else
        empty->output(level+4);
    Expr1->output(level+4);
}

void FuncCallStmt::output(int level){
    fprintf(yyout, "%*cFuncCallStmt\n", level, ' ');
    funccall->output(level+4);
}

void FuncCall::output(int level)
{
    std::string name, type;
    name = se->toStr();
    type = se->getType()->toStr();
    fprintf(yyout, "%*cFunctionCall function name: %s, type: %s\n", level, ' ', 
            name.c_str(), type.c_str());
    if(parms!=nullptr)
        parms->output(level + 4);
}

void Arguments::output(int level){
    fprintf(yyout,"%*cArgument\n", level, ' ');
    lastParam->output(level+4);
    prevParam->output(level+4);
}

void Argument::output(int level){
    fprintf(yyout,"%*cArguments\n", level, ' ');
    Param->output(level+4);
}