#include "Type.h"
#include <sstream>

IntType TypeSystem::commonInt = IntType(4);
VoidType TypeSystem::commonVoid = VoidType();
ConstIntType TypeSystem::commonconstInt = ConstIntType(4);

Type* TypeSystem::intType = &commonInt;
Type* TypeSystem::voidType = &commonVoid;
Type* TypeSystem::cintType = &commonconstInt;

std::string IntType::toStr()
{
    return "int";
}

std::string VoidType::toStr()
{
    return "void";
}

std::string ConstIntType::toStr()
{
    return "const int";
}

std::string FunctionType::toStr()
{
    std::ostringstream buffer;
    buffer << returnType->toStr() << "(";
    if(paramsType.size()!=0)
    {
        for(unsigned long i=0;i<paramsType.size() - 1;i++)
        {
            buffer << paramsType[i]->toStr() << ", ";
        }
        buffer << paramsType.back()->toStr() << ")";
    }
    else
        buffer << ")";
    return buffer.str();
}
