#include "Type.h"
#include <sstream>
#include <assert.h>

//Static Variable & PTR init
IntType TypeSystem::commonInt = IntType(32);
FloatType TypeSystem::commonFloat = FloatType(32);
IntType TypeSystem::commonBool = IntType(1);
VoidType TypeSystem::commonVoid = VoidType();
IntType TypeSystem::commonConstInt = IntType(32,true);
FloatType TypeSystem::commonConstFloat = FloatType(32,true);

Type* TypeSystem::intType = &commonInt;
Type* TypeSystem::floatType=&commonFloat;
Type* TypeSystem::voidType = &commonVoid;
Type* TypeSystem::boolType = &commonBool;
Type* TypeSystem::constIntType=&commonConstInt;
Type* TypeSystem::constFloatType=&commonConstFloat;

/*toStr()函数*/
//IntType:i32/i1
std::string IntType::toStr()
{
    std::ostringstream buffer;
    buffer << "i" << size;
    return buffer.str();
}

//FloatType，暂时先float
std::string FloatType::toStr()
{
    return "float";
}

std::string VoidType::toStr()
{
    return "void";
}

/*need to be extended*/
//FunctionType:returnType (params...)
std::string FunctionType::toStr()
{
    std::ostringstream buffer;
    buffer << returnType->toStr() << "(";
    for (auto it = paramsType.begin(); it != paramsType.end(); it++) {
        buffer << (*it)->toStr();
        if (it + 1 != paramsType.end())
            buffer << ", ";
    }
    buffer << ')';
    return buffer.str();
}

//数组
//int a[3][5]-->[3 x [5 x i32]]
//int a[][3][5]-->[3 x [5 x i32]]*
std::string ArrayType::toStr() {
    std::vector<std::string> vec;
    Type* temp = this;
    int count = 0;
    bool flag = false;
    while (temp && temp->isArray()) {
        std::ostringstream buffer;
        if (((ArrayType*)temp)->getLength() == -1) {
            flag = true;
        } else {
            //getLength()获取外层数组length
            buffer << "[" << ((ArrayType*)temp)->getLength() << " x ";
            count++;
            vec.push_back(buffer.str());
        }
        //getElementType()内层数组
        temp = ((ArrayType*)temp)->getElementType();
    }
    assert(temp->isInt() || temp->isFloat());
    std::ostringstream buffer;
    for (auto it = vec.begin(); it != vec.end(); it++)
        buffer << *it;
    //暂时先写i32，需要增加float数组
    buffer << "i32";

    //填充']'和'*'
    while (count--)
        buffer << ']';
    //flag->[]
    if (flag)
        buffer << '*';
    return buffer.str();
}


//PointerType:valueType *
std::string PointerType::toStr()
{
    std::ostringstream buffer;
    buffer << valueType->toStr() << "*";
    return buffer.str();
}
