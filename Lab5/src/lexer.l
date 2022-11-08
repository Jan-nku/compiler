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
    char lineno[10];

    void DEBUG_FOR_LAB4(std::string s,std::string s2 = "",std::string s3 = ""){
        sprintf(lineno,"%d",yylineno);
        std::string DEBUG_INFO = "\t" + s + "\t" + s2 + "\t" + s3 + lineno + "\n";
        fputs(DEBUG_INFO.c_str(), yyout);
    }
%}


HEX  (0x[1-9A-Fa-f][0-9A-Fa-f]*|0)
OCTAL  (0[1-7][0-7]*|0)
DECIMIAL ([1-9][0-9]*|0)
ID [[:alpha:]_][[:alpha:][:digit:]_]*
EOL (\r\n|\n|\r)
WHITE [\t ]

commentbegin "/*"
commentelement [^\n"*/"]*
commentline \n
commentend "*/"

linecomment \/\/[^\n]*

%x BLOCKCOMMENT

%%

{linecomment} {}

{commentbegin} {BEGIN BLOCKCOMMENT;}
<BLOCKCOMMENT>{commentelement} {}
<BLOCKCOMMENT>{commentline} {yylineno++;}
<BLOCKCOMMENT>{commentend} {yylineno++;BEGIN INITIAL;}

"const int" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("CONSTINT\t\tconstint");
    return CONSTINT;
};
"const" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("CONST\t\tconst");
    return CONST;
};
"int" {
    /*
    * Questions: 
    *   Q1: Why we need to return INT in further labs?
    *   Q2: What is "INT" actually?
    */
    if(dump_tokens)
        DEBUG_FOR_LAB4("INT\t\tint");
    return INT;
}
"void" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("VOID\t\tvoid");
    return VOID;
}
"if" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("IF\t\tif");
    return IF;
};
"else" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("ELSE\t\telse");
    return ELSE;
};

"break" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("BREAK\t\tbreak");
    return BREAK;
}

"continue" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("CONTINUE\t\tcontinue");
    return CONTINUE;
}

"return" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("RETURN\t\treturn");
    return RETURN;
}

"!" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("NOT\t\t!");
    return NOT;
};

"+" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("ADD\t\t+");
    return ADD;
};
"-" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("SUB\t\t-");
    return SUB;
};
"*" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("MUL\t\t*");
    return MUL;
};
"/" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("DIV\t\t/");
    return DIV;
};

"=" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("ASSIGN\t\t=");
    return ASSIGN;
};
"<" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("LESS\t\t<");
    return LESS;
};
">" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("GREATRER\t\t>");
    return GREATER;
};
"%" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("MOD\t\t%");
    return MOD;
};
"==" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("EQUAL\t\t==");
    return EQUAL;
};
"<=" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("LE\t\t<=");
    return LE;
};
">=" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("GE\t\t>=");
    return GE;
};
"!=" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("NE\t\t!=");
    return NE;
};
"&&" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("AND\t\t&&");
    return AND;
};
"||" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("OR\t\t||");
    return OR;
}

";" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("SEMICOLON\t;");
    return SEMICOLON;
};
"(" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("LPAREN\t\t(");
    return LPAREN;
};
")" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("RPAREN\t\t)");
    return RPAREN;
};
"{" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("LBRACE\t\t{");
    return LBRACE;
};
"}" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("RBRACE\t\t}");
    return RBRACE;
};

"while" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("WHILE\t\twhile");
    return WHILE;
};
"for" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("FOR\t\tfor");
    return FOR;
};
"scanf" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("SCANF\t\tscanf");
    return SCANF;
};
"printf" {
    if(dump_tokens)
        DEBUG_FOR_LAB4("PRINTF\t\tprintf");
    return PRINTF;
};
"," {
    if(dump_tokens)
        DEBUG_FOR_LAB4("COMMA\t\t,");
    return COMMA;
};

{DECIMIAL} {
    if(dump_tokens)
        DEBUG_FOR_LAB4(yytext);
    yylval.itype = atoi(yytext);
    return INTEGER;
};
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
};
{EOL} {}
{WHITE}
%%
