#ifndef __SYMBOLTABLE_H__
#define __SYMBOLTABLE_H__

#include <string>
#include <map>

class Type;
class Operand;

class SymbolTable;
//SymbolEntry
class SymbolEntry
{
private:
    int kind;
protected:
    //SymbolEntry's kind: CONSTINT(ConstantSymbolEntry)、VARIABLE(IdentifierSymbolEntry)、TEMPORARY(TemporarySymbolEntry)
    enum {CONSTANT, VARIABLE, TEMPORARY};
    //Type: INT、VOID、FUNC、PTR...
    Type *type;

    //增加一个next指针将相关SymbolEntry串联起来
    SymbolEntry* next;

public:
    SymbolEntry(Type *type, int kind);
    virtual ~SymbolEntry() {};
    bool isConstant() const {return kind == CONSTANT;};
    bool isTemporary() const {return kind == TEMPORARY;};
    bool isVariable() const {return kind == VARIABLE;};
    Type* getType() {return type;};
    void setType(Type *type) {this->type = type;};
    //SymbolEntry字符串打印函数
    virtual std::string toStr() = 0;
    /* You can add any function you need here.*/
    //增加setNext函数
    bool setNext(SymbolEntry *se);
    SymbolEntry *getNext() const {return next;};
};

//identifier symbol entries
// symbol table managing identifier symbol entries
class SymbolTable
{
private:
    std::map<std::string, SymbolEntry*> symbolTable;        //map<string, SymbolEntry>
    SymbolTable *prev;                                      //prev SymbolTable
    int level;                                              //current level
    static int counter;                                     //Label符号标签，counter记录符号个数
public:
    SymbolTable();
    SymbolTable(SymbolTable *prev);
    //修改install SymbolEntry，返回bool值
    bool install(std::string name, SymbolEntry* entry);
    //SymbolEntry lookup
    SymbolEntry* lookup(std::string name);
    SymbolTable* getPrev() {return prev;};
    int getLevel() {return level;};
    static int getLabel() {return counter++;};
};

/*  
    Symbol entry for literal constant. Example:

    int a = 1;

    Compiler should create constant symbol entry for literal constant '1'.
*/

//常量，存储value
class ConstantSymbolEntry : public SymbolEntry
{
private:
    /*need to be extended*/
    //暂时定义为int类型
    int value;
    //增加float类型、数组类型
    float fvalue;
    int* arrayValue;
    float* arrayFValue;

public:
    ConstantSymbolEntry(Type *type, int value);
    ConstantSymbolEntry(Type *type, float fvalue);
    ConstantSymbolEntry(Type *type) : SymbolEntry(type, SymbolEntry::CONSTANT){};
    virtual ~ConstantSymbolEntry() {};
    //getValue/getFvalue获取值
    int getValue() const {return value;};
    float getFvalue() const {return fvalue;};
    int* getArray(){return this->arrayValue;};
    float* getFArray(){return this->arrayFValue;};
    std::string toStr();
    // You can add any function you need here.
};


/* 
    Symbol entry for identifier. Example:

    int a;
    int b;
    void f(int c)
    {
        int d;
        {
            int e;
        }
    }

    Compiler should create identifier symbol entries for variables a, b, c, d and e:

    | variable | scope    |
    | a        | GLOBAL   |
    | b        | GLOBAL   |
    | c        | PARAM    |
    | d        | LOCAL    |
    | e        | LOCAL +1 |
*/

//标识符类型：name、scope(GLOBAL, PARAM, LOCAL)、addr
//需要加的东西比较多
class IdentifierSymbolEntry : public SymbolEntry
{
private:
    enum {GLOBAL, PARAM, LOCAL};
    std::string name;
    int scope;      //GLOBAL、PARAM、LOCAL
    Operand *addr;  // The address of the identifier.
    // You can add any field you need here.

    bool allZero;
    bool constant;

    //value
    int value;
    float fvalue;

    float* arrayFValue;
    int* arrayValue;

    //param:增加lable、funcParam
    int label;
    bool funcParam;
    bool sysy = false;

    //用于函数定义参数寄存器分配
    int paramNo;

public:
    IdentifierSymbolEntry(Type *type, std::string name, int scope, int paramNo = -1): SymbolEntry(type, SymbolEntry::VARIABLE), name(name), paramNo(paramNo)
    {
        this->scope = scope;
        this->allZero = false;
        this->label = -1;
        this->arrayValue = nullptr;
        this->arrayFValue = nullptr;
        addr = nullptr;
    }
    virtual ~IdentifierSymbolEntry() {};
    std::string toStr();
    bool isGlobal() const {return scope == GLOBAL;};
    bool isParam() const {return scope == PARAM;};
    bool isLocal() const {return scope >= LOCAL;};
    int getScope() const {return scope;};
    void setAddr(Operand *addr) {this->addr = addr;};
    void setAllZero(bool allZero = true){this->allZero = allZero;};
    bool isAllZero(){return allZero;};
    Operand* getAddr() {return addr;};
    bool setSysy() { sysy = true; };
    bool isSysy() const { return sysy; };
    // You can add any function you need here.
    int getValue(){return value;};
    float getFValue(){return fvalue;};
    void setValue(int v){value=v;};
    void setFValue(float v){fvalue=v;};

    int* getArrayValue(){return arrayValue;};
    float* getFArrayValue(){return arrayFValue;};
    void setArrayValue(int*v){this->arrayValue=v;};
    void setFArrayValue(float*v){this->arrayFValue=v;};
    void setConst() {constant = true; };
    bool getConst() const { return constant; };
    //暂时先这么用
    int getParamNo() const { return paramNo; };
    //void setLabel() { label = SymbolTable::getLabel(); };
    int getLabel() const {return label; };
    void setParam(){
        this->funcParam = true;
        this->label=SymbolTable::getLabel();
    };
};


/* 
    Symbol entry for temporary variable created by compiler. Example:

    int a;
    a = 1 + 2 + 3;

    The compiler would generate intermediate code like:

    t1 = 1 + 2
    t2 = t1 + 3
    a = t2

    So compiler should create temporary symbol entries for t1 and t2:

    | temporary variable | label |
    | t1                 | 1     |
    | t2                 | 2     |
*/
//临时变量:stack_offset、label
//stack_offset有什么用？
class TemporarySymbolEntry : public SymbolEntry
{
private:
    int stack_offset;
    //label标签
    int label;
public:
    TemporarySymbolEntry(Type *type, int label);
    virtual ~TemporarySymbolEntry() {};
    std::string toStr();
    int getLabel() const {return label;};
    //Offset Operating Functions
    void setOffset(int offset) { this->stack_offset = offset; };
    int getOffset() { return this->stack_offset; };
    // You can add any function you need here.
};

//identifiers、globals
extern SymbolTable *identifiers;
extern SymbolTable *globals;

#endif
