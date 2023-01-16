#ifndef __TYPE_H__
#define __TYPE_H__
#include <vector>
#include <string>
#include "SymbolTable.h"

//函数或操作数的类型
class Type
{
private:
    int kind;
protected:
    //INT、VOID、FUNC、PTR...
    //FLOAT、ARRAY
    enum {INT, VOID, FUNC, PTR, FLOAT, ARRAY};
    //基类增加属性size
    int size;
public:
    //重写构造函数，增加size = 0
    Type(int kind, int size = 0) : kind(kind), size(size){};
    virtual ~Type() {};
    virtual std::string toStr() = 0;
    int getSize() const {return this->size;};
    bool isInt() const {return kind == INT && size == 32;};
    bool isBool() const {return kind == INT && size == 1;};
    bool isVoid() const {return kind == VOID;};
    bool isFunc() const {return kind == FUNC;};
    bool isFloat() const {return kind == FLOAT;};
    bool isPtr() const {return kind == PTR;};
    bool isArray() const {return kind == ARRAY;};
};

class IntType : public Type
{
private:
    //int size;
    //判断是否是const类型
    bool constant;
public:
    IntType(int size, bool constant = false) : Type(Type::INT, size), constant(constant){};
    std::string toStr();
    bool isConst() const {return constant; };
};

//增加float类型
class FloatType : public Type
{
private:
    //判断是否是const类型
    bool constant;
public:
    FloatType(int size, bool constant = false) : Type(Type::FLOAT, size), constant(constant){};
    std::string toStr();
    bool isConst() const {return constant; };
};

class VoidType : public Type
{
public:
    VoidType() : Type(Type::VOID){};
    std::string toStr();
};

class FunctionType : public Type
{
private:
    //返回值类型
    Type *returnType;
    //paramsType存储参数的类型
    std::vector<Type*> paramsType;

    //暂时先这么设计，FunctionType增加参数符号地址
    //paramsSe存储参数的SymbolEntry
    std::vector<SymbolEntry*> paramsSe;
public:
    FunctionType(Type* returnType, std::vector<Type*> paramsType) : 
    Type(Type::FUNC), returnType(returnType), paramsType(paramsType){};
    
    //增加构造函数FunctionType(Type* returnType, std::vector<SymbolEntry*> paramsSe);
    FunctionType(Type* returnType, std::vector<SymbolEntry*> paramsSe) :
    Type(Type::FUNC), returnType(returnType), paramsSe(paramsSe){
        for(auto it = paramsSe.begin(); it!=paramsSe.end(); it++){
            paramsType.push_back((*it)->getType());
        }
    };
    void setParamsType(std::vector<Type*> paramsType) {
        this->paramsType = paramsType;
    };
    Type* getRetType() {return returnType;};
    std::vector<Type*> getParamsType(){return this->paramsType;};
    std::vector<SymbolEntry*> getParamsSe(){return this->paramsSe;};
    std::string toStr();
};

//数组类型
class ArrayType : public Type {
private:
    bool constant;                  //判断是否是const类型
    int length;                     //数组长度
    Type* elementType;              //嵌套定义数组
    Type* arrayType = nullptr;      //不知道干什么    

public:
    ArrayType(Type* elementType, int length, bool constant = false) :
    Type(Type::ARRAY, elementType->getSize()*length), elementType(elementType), length(length), constant(constant){};
    
    std::string toStr();
    int getLength() const {return length; };
    Type* getElementType() const { return elementType; };
    Type* getArrayType() const { return arrayType; };
    void setArrayType(Type* arrayType) { this->arrayType = arrayType; };
    bool isConst() const {return constant; };
};

class PointerType : public Type
{
private:
    //指针指向value类型
    Type *valueType;
public:
    PointerType(Type* valueType) : Type(Type::PTR) {this->valueType = valueType;};
    std::string toStr();
    Type* getType() const { return valueType; };
};

//TypeSystem
//Static variable、PTR
class TypeSystem
{
private:
    static IntType commonInt;
    static IntType commonBool;          //Bool类型
    static VoidType commonVoid;
    static FloatType commonFloat;       //float类型
    static IntType commonConstInt;      //const int类型
    static FloatType commonConstFloat;  //const float类型
    
    //所有类型只需要一个存储入口地址的指针，public
public:
    static Type *intType;
    static Type *voidType;
    static Type *boolType;
    static Type *floatType;
    static Type *constIntType;
    static Type *constFloatType;
};

#endif
