%option noyywrap
%{
    #define YY_NO_UNPUT
    #define YY_NO_INPUT

    #include "parser.h"
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

DECIMIAL ([1-9][0-9]*|0)
OCTAL (0[0-7]+)
HEX (0[xX][0-9A-Fa-f]+)
ID [[:alpha:]_][[:alpha:][:digit:]_]*
EOL (\r\n|\n|\r)
WHITE [\t ]

/*注释*/
BLOCKCOMMENTBEGIN \/\*
BLOCKCOMMENTELEMENT .
BLOCKCOMMENTEND \*\/
%x BLOCKCOMMENT
LINECOMMENT \/\/[^\n]*

%%
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
};
"else" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("ELSE\telse");
    return ELSE;
};
"return" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("RETURN\treturn");
    return RETURN;
}
"while" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("WHILE\twhile");
    return WHILE;
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
"=" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("ASSIGN\t=");
    return ASSIGN;
}
"<" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("LESS\t<");
    return LESS;
}
"<=" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("LESSEQUAL\t<");
    return LESSEQUAL;
}
">" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("GREATER\t<");
    return GREATER;
}
">=" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("GREATEREQUAL\t<");
    return GREATEREQUAL;
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
        DEBUG_FOR_LAB4("RBRACKET\t}");
    return RBRACKET;
}
"," {
    if(dump_tokens)
        DEBUG_FOR_LAB4("COMMA\t,");
    return COMMA;
}

"putint" {
    if(dump_tokens)
        DEBUG_FOR_LAB4(yytext);
    char *temp;
    temp = new char[strlen(yytext) + 1];
    strcpy(temp, yytext);
    yylval.strtype = temp;
    std::vector<Type*> paramsType;
    std::vector<SymbolEntry*> paramsSe;
    paramsType.push_back(TypeSystem::intType);
    Type* funcType = new FunctionType(TypeSystem::voidType, paramsType, paramsSe);
    SymbolTable* st = identifiers;
    while(st->getPrev())
        st = st->getPrev();
    SymbolEntry* se = new IdentifierSymbolEntry(funcType, yytext, st->getLevel());
    st->install(yytext, se);
    return ID;
}

"getint" {
    if(dump_tokens)
        DEBUG_FOR_LAB4(yytext);
    char *temp;
    temp = new char[strlen(yytext) + 1];
    strcpy(temp, yytext);
    yylval.strtype = temp;
    std::vector<Type*> paramsType;
    std::vector<SymbolEntry*> paramsSe;
    paramsType.push_back(TypeSystem::intType);
    Type* funcType = new FunctionType(TypeSystem::voidType, paramsType, paramsSe);
    SymbolTable* st = identifiers;
    while(st->getPrev())
        st = st->getPrev();
    SymbolEntry* se = new IdentifierSymbolEntry(funcType, yytext, st->getLevel());
    st->install(yytext, se);
    return ID;
}

"getch" {
    if(dump_tokens)
        DEBUG_FOR_LAB4(yytext);
    char *temp;
    temp = new char[strlen(yytext) + 1];
    strcpy(temp, yytext);
    yylval.strtype = temp;
    std::vector<Type*> paramsType;
    std::vector<SymbolEntry*> paramsSe;
    paramsType.push_back(TypeSystem::intType);
    Type* funcType = new FunctionType(TypeSystem::voidType, paramsType, paramsSe);
    SymbolTable* st = identifiers;
    while(st->getPrev())
        st = st->getPrev();
    SymbolEntry* se = new IdentifierSymbolEntry(funcType, yytext, st->getLevel());
    st->install(yytext, se);
    return ID;
}

"putch" {
    if(dump_tokens)
        DEBUG_FOR_LAB4(yytext);
    char *temp;
    temp = new char[strlen(yytext) + 1];
    strcpy(temp, yytext);
    yylval.strtype = temp;
    std::vector<Type*> paramsType;
    std::vector<SymbolEntry*> paramsSe;
    paramsType.push_back(TypeSystem::intType);
    Type* funcType = new FunctionType(TypeSystem::voidType, paramsType, paramsSe);
    SymbolTable* st = identifiers;
    while(st->getPrev())
        st = st->getPrev();
    SymbolEntry* se = new IdentifierSymbolEntry(funcType, yytext, st->getLevel());
    st->install(yytext, se);
    return ID;
}

{DECIMIAL} {
    if(dump_tokens)
        DEBUG_FOR_LAB4(yytext);
    yylval.itype = atoi(yytext);
    return INTEGER;
}
{OCTAL} {
    int tmp;
    sscanf(yytext, "%o", &tmp);
    if(dump_tokens)
        DEBUG_FOR_LAB4(string("NUMBER\t") + to_string(tmp));
    yylval.itype = tmp;
    return INTEGER;
}
{HEX} {
    int tmp;
    sscanf(yytext, "%x", &tmp);
    if(dump_tokens)
        DEBUG_FOR_LAB4(string("NUMBER\t") + to_string(tmp));
    yylval.itype = tmp;
    return INTEGER;
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
{LINECOMMENT} {}
{BLOCKCOMMENTBEGIN} {BEGIN BLOCKCOMMENT;}
<BLOCKCOMMENT>{BLOCKCOMMENTELEMENT} {}
<BLOCKCOMMENT>{BLOCKCOMMENTEND} {BEGIN INITIAL;}

%%
