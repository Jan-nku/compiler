%option noyywrap
%{
    #define YY_NO_UNPUT
    #define YY_NO_INPUT

    #include "parser.h"
    #include "Unit.h"
    #include <iostream>
    #include <ostream>
    #include <fstream>
    using namespace std;

    extern FILE *yyin; 
    extern FILE *yyout;
    extern bool dump_tokens;

    void DEBUG_FOR_LAB4(std::string s){
        std::string DEBUG_INFO = "[DEBUG LAB4]: \t" + s + "\n";
        fputs(DEBUG_INFO.c_str(), yyout);
    }
%}

DECIMIAL_INT ([1-9][0-9]*|0)
DECIMIAL_FLOAT ((([0-9]*[.][0-9]*([eE][+-]?[0-9]+)?)|([0-9]+[eE][+-]?[0-9]+))[fFlL]?)
HEX (0[xX][0-9a-fA-F]+)
OCTAL (0[0-7]+)
ID [[:alpha:]_][[:alpha:][:digit:]_]*
EOL (\r\n|\n|\r)
WHITE [\t ]
LINECOMMENT \/\/[^\n]*
BLOCKCOMMENTBEGIN "/*"
BLOCKCOMMENTELEMENT (.|\n)
BLOCKCOMMENTEND "*/"
%x BLOCKCOMMENT

%%
{LINECOMMENT} {}
{BLOCKCOMMENTBEGIN} {BEGIN BLOCKCOMMENT;}
<BLOCKCOMMENT>{BLOCKCOMMENTELEMENT} {}
<BLOCKCOMMENT>{BLOCKCOMMENTEND} {BEGIN INITIAL;}
"int" {
    /*
    * Questions: 
    *   Q1: Why we need to return INT in further labs?
    *   Q2: What is "INT" actually?
    */
    if(dump_tokens)
        DEBUG_FOR_LAB4("INT\tint");
    return INT;
}
"float" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("FLOAT\tfloat");
    return FLOAT;
}
"void" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("VOID\tvoid");
    return VOID;
}
"const" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("CONST\tconst");
    return CONST;
}
"if" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("IF\tif");
    return IF;
}
"else" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("ELSE\telse");
    return ELSE;
}
"while" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("WHILE\twhile");
    return WHILE;
}
"return" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("RETURN\treturn");
    return RETURN;
}
"break" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("BREAK\tbreak");
    return BREAK;
}
"continue" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("CONTINUE\tcontinue");
    return CONTINUE;
}
"==" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("EQUAL\t==");
    return EQUAL;
}
"!=" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("NOTEQUAL\t!=");
    return NOTEQUAL;
}
"<" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("LESS\t<");
    return LESS;
}
"<=" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("LESSEQUAL\t<=");
    return LESSEQUAL;
}
">" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("GREATER\t>");
    return GREATER;
}
">=" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("GREATEREQUAL\t>=");
    return GREATEREQUAL;
}
"&&" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("AND\t&&");
    return AND;
}
"||" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("OR\t||");
    return OR;
}
"!" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("NOT\t!");
    return NOT;
}
"=" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("ASSIGN\t=");
    return ASSIGN;
}
"+" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("ADD\t+");
    return ADD;
}
"-" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("SUB\t-");
    return SUB;
}
"*" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("MUL\t*");
    return MUL;
}
"/" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("DIV\t/");
    return DIV;
}
"%" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("MOD\t%%");
    return MOD;
}
";" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("SEMICOLON\t;");
    return SEMICOLON;
}
"(" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("LPAREN\t(");
    return LPAREN;
}
")" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("RPAREN\t)");
    return RPAREN;
}
"{" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("LBRACE\t{");
    return LBRACE;
}
"}" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("RBRACE\t}");
    return RBRACE;
}
"[" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("LBRACKET\t[");
    return LBRACKET;
}
"]" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("RBRACKET\t]");
    return RBRACKET;
}
"," {
    if(dump_tokens)
        DEBUG_FOR_LAB4("COMMA\t,");
    return COMMA;
}
{DECIMIAL_INT} {
    if(dump_tokens)
        DEBUG_FOR_LAB4(string("DECIMIAL_INT\t")+string(yytext));
    yylval.itype = atoi(yytext);
    return INTEGER;
}
{DECIMIAL_FLOAT} {
    if(dump_tokens)
        DEBUG_FOR_LAB4(string("DECIMIAL_FLOAT\t")+string(yytext));
    float num=0.0;
    sscanf(yytext,"%f",&num);
    yylval.ftype = num;
    return FLOATING;
}
{HEX} {
    int num=0;
    sscanf(yytext, "%x", &num);
    if(dump_tokens)
        DEBUG_FOR_LAB4(string("NUMBER\t") + to_string(num));
    yylval.itype = num;
    return INTEGER;
}
{OCTAL} {
    int num=0;
    sscanf(yytext, "%o", &num);
    if(dump_tokens)
        DEBUG_FOR_LAB4(string("NUMBER\t") + to_string(num));
    yylval.itype = num;
    return INTEGER;
}

"putint" {
    //void putint(int)
    if(dump_tokens)
        DEBUG_FOR_LAB4(yytext);
    char *lexeme = new char[strlen(yytext) + 1];
    strcpy(lexeme, yytext);
    yylval.strtype = lexeme;
    //构造funcType
    std::vector<Type*> vec;
    vec.push_back(TypeSystem::intType);
    Type* funcType = new FunctionType(TypeSystem::voidType, vec);
    //构造SymbolEntry，插入符号表中
    SymbolTable* st = identifiers;
    while(st->getPrev())
        st = st->getPrev();
    SymbolEntry* se = new IdentifierSymbolEntry(funcType, yytext, st->getLevel());
    st->install(yytext, se);
    return ID;
}
"getint" {
    //int getint()
    if(dump_tokens)
        DEBUG_FOR_LAB4(yytext);
    char *lexeme = new char [strlen(yytext)+1];
    strcpy(lexeme, yytext);
    yylval.strtype = lexeme;
    //构造funcType
    std::vector<Type*> vec;
    Type* funcType = new FunctionType(TypeSystem::intType, vec);
    //构造SymbolEntry，插入符号表中
    SymbolTable* st = identifiers;
    while(st->getPrev()){
        st = st->getPrev();
    }
    SymbolEntry* se = new IdentifierSymbolEntry(funcType, yytext, st->getLevel());
    st->install(yytext, se);
    return ID;
}
"putch" {
    //void putch(int)
    if(dump_tokens)
        DEBUG_FOR_LAB4(yytext);
    char *lexeme = new char [strlen(yytext)+1];
    strcpy(lexeme, yytext);
    yylval.strtype = lexeme;
    //构造funcType
    std::vector<Type*> vec;
    vec.push_back(TypeSystem::intType);
    Type* funcType = new FunctionType(TypeSystem::voidType, vec);
    //构造SymbolEntry，插入符号表中
    SymbolTable* st = identifiers;
    while(st->getPrev()){
        st = st->getPrev();
    }
    SymbolEntry* se = new IdentifierSymbolEntry(funcType, yytext, st->getLevel());
    st->install(yytext, se);
    return ID;
}
"getch" {
    //int getch()
    if(dump_tokens)
        DEBUG_FOR_LAB4(yytext);
    char *lexeme = new char [strlen(yytext)+1];
    strcpy(lexeme, yytext);
    yylval.strtype = lexeme;
    //构造funcType
    std::vector<Type*> vec;
    Type* funcType = new FunctionType(TypeSystem::intType, vec);
    //构造SymbolEntry，插入符号表中
    SymbolTable* st = identifiers;
    while(st->getPrev()){
        st = st->getPrev();
    }
    SymbolEntry* se = new IdentifierSymbolEntry(funcType, yytext, st->getLevel());
    st->install(yytext, se);
    return ID;
}
"getfloat" {
    //float getfloat()
    if(dump_tokens)
        DEBUG_FOR_LAB4(yytext);
    char *lexeme = new char[strlen(yytext) + 1];
    strcpy(lexeme, yytext);
    yylval.strtype = lexeme;
    //构造funcType
    std::vector<Type*> vec;
    Type* funcType = new FunctionType(TypeSystem::floatType, vec);
    //构造SymbolEntry，插入符号表中
    SymbolTable* st = identifiers;
    while(st->getPrev())
        st = st->getPrev();
    SymbolEntry* se = new IdentifierSymbolEntry(funcType, yytext, st->getLevel());
    st->install(yytext, se);
    return ID;
}
"putfloat" {
    //void putfloat(float)
    if(dump_tokens)
        DEBUG_FOR_LAB4(yytext);
    char *lexeme = new char [strlen(yytext)+1];
    strcpy(lexeme, yytext);
    yylval.strtype = lexeme;
    //构造funcType
    std::vector<Type*> vec;
    vec.push_back(TypeSystem::floatType);
    Type* funcType = new FunctionType(TypeSystem::voidType, vec);
    //构造SymbolEntry，插入符号表中
    SymbolTable* st = identifiers;
    while(st->getPrev()){
        st = st->getPrev();
    }
    SymbolEntry* se = new IdentifierSymbolEntry(funcType, yytext, st->getLevel());
    st->install(yytext, se);
    return ID;
}
"putarray" {
    //void putarray(int,int[])
    if(dump_tokens)
        DEBUG_FOR_LAB4(yytext);
    char *lexeme = new char[strlen(yytext) + 1];
    strcpy(lexeme, yytext);
    yylval.strtype = lexeme;
    //构造funcType
    std::vector<Type*> vec;
    vec.push_back(TypeSystem::intType);
    vec.push_back(new ArrayType(TypeSystem::intType, -1));
    Type* funcType = new FunctionType(TypeSystem::voidType, vec);
    //构造SymbolEntry，插入符号表中
    SymbolTable* st = identifiers;
    while(st->getPrev())
        st = st->getPrev();
    SymbolEntry* se = new IdentifierSymbolEntry(funcType, yytext, st->getLevel());
    st->install(yytext, se);
    return ID;
}
"getarray" {
    //int getarray(int[])
    if(dump_tokens)
        DEBUG_FOR_LAB4(yytext);
    char *lexeme = new char[strlen(yytext) + 1];
    strcpy(lexeme, yytext);
    yylval.strtype = lexeme;
    //构造funcType
    std::vector<Type*> vec;
    vec.push_back(new ArrayType(TypeSystem::intType, -1));
    Type* funcType = new FunctionType(TypeSystem::intType, vec);
    //构造SymbolEntry，插入符号表中
    SymbolTable* st = identifiers;
    while(st->getPrev())
        st = st->getPrev();
    SymbolEntry* se = new IdentifierSymbolEntry(funcType, yytext, st->getLevel());
    st->install(yytext, se);
    return ID;
}
"putfarray" {
    //void putfarray(int,float[])
    if(dump_tokens)
        DEBUG_FOR_LAB4(yytext);
    char *lexeme = new char[strlen(yytext) + 1];
    strcpy(lexeme, yytext);
    yylval.strtype = lexeme;
    //构造funcType
    std::vector<Type*> vec;
    vec.push_back(TypeSystem::intType);
    vec.push_back(new ArrayType(TypeSystem::floatType, -1));
    Type* funcType = new FunctionType(TypeSystem::voidType, vec);
    //构造SymbolEntry，插入符号表中
    SymbolTable* st = identifiers;
    while(st->getPrev())
        st = st->getPrev();
    SymbolEntry* se = new IdentifierSymbolEntry(funcType, yytext, st->getLevel());
    st->install(yytext, se);
    return ID;
}
"getfarray" {
    //int getfarray(float[])
    if(dump_tokens)
        DEBUG_FOR_LAB4(yytext);
    char *lexeme = new char[strlen(yytext) + 1];
    strcpy(lexeme, yytext);
    yylval.strtype = lexeme;
    //构造funcType
    std::vector<Type*> vec;
    vec.push_back(new ArrayType(TypeSystem::floatType, -1));
    Type* funcType = new FunctionType(TypeSystem::intType, vec);
    //构造SymbolEntry，插入符号表中
    SymbolTable* st = identifiers;
    while(st->getPrev())
        st = st->getPrev();
    SymbolEntry* se = new IdentifierSymbolEntry(funcType, yytext, st->getLevel());
    st->install(yytext, se);
    return ID;
}
"starttime" {
    //void starttime()
    if(dump_tokens)
        DEBUG_FOR_LAB4(yytext);
    char *lexeme = new char[6 + strlen(yytext) + 1];
    char* sysy = (char *)"_sysy_";
    strcpy(lexeme, sysy);
    strcpy(lexeme + 6, yytext);
    yylval.strtype = lexeme;
    //构造funcType
    std::vector<Type*> vec;
    Type* funcType = new FunctionType(TypeSystem::voidType, vec);
    //构造SymbolEntry，插入符号表中
    SymbolTable* st = identifiers;
    while(st->getPrev())
        st = st->getPrev();
    char *temp = new char[6+strlen(yytext)];
    memcpy(temp, lexeme, 6+strlen(yytext));
    SymbolEntry* se = new IdentifierSymbolEntry(funcType, temp, st->getLevel());
    st->install(temp, se);
    return ID;
}
"stoptime" {
    //void stoptime()
    if(dump_tokens)
        DEBUG_FOR_LAB4(yytext);
    char *lexeme = new char[6 + strlen(yytext) + 1];
    char* sysy = (char *)"_sysy_";
    strcpy(lexeme, sysy);
    strcpy(lexeme + 6, yytext);
    yylval.strtype = lexeme;
    //构造funcType
    std::vector<Type*> vec;
    Type* funcType = new FunctionType(TypeSystem::voidType, vec);
    //构造SymbolEntry，插入符号表中
    SymbolTable* st = identifiers;
    while(st->getPrev())
        st = st->getPrev();
    char *temp = new char[6+strlen(yytext)];
    memcpy(temp, lexeme, 6+strlen(yytext));
    SymbolEntry* se = new IdentifierSymbolEntry(funcType, temp, st->getLevel());
    st->install(temp, se);
    return ID;
}
"putf" {
    //void putf(<格式串>, int, ...)
    return ID;
}

{ID} {
    if(dump_tokens)
        DEBUG_FOR_LAB4(yytext);
    char *lexeme;
    lexeme = new char[strlen(yytext) + 1];
    strcpy(lexeme, yytext);
    yylval.strtype = lexeme;
    return ID;
}

<*>{EOL} yylineno++;
{WHITE}
%%
