%option noyywrap
%{
    /*
    * You will need to comment this line in lab5.
    */
    #define ONLY_FOR_LEX
    
    #ifdef ONLY_FOR_LEX
    #else
    #define YYSTYPE void *
    #include "parser.h"
    #endif

    #define YY_NO_UNPUT
    #define YY_NO_INPUT
    #include<map>

    #ifdef ONLY_FOR_LEX
    #include <ostream>
    #include <fstream>
    #include<string>
    #include<vector>
    using namespace std;
    extern FILE *yyin; 
    extern FILE *yyout;
    char lineno[10];

    void DEBUG_FOR_LAB4(std::string s,std::string s2 = "",std::string s3 = ""){
        sprintf(lineno,"%d",yylineno);
        std::string DEBUG_INFO;
        DEBUG_INFO += lineno;
        for(;DEBUG_INFO.length()<=6;)
            DEBUG_INFO+=" ";
        DEBUG_INFO+= s;
        for(;DEBUG_INFO.length()<=26;)
            DEBUG_INFO+=" ";
        DEBUG_INFO+= s2;
        for(;DEBUG_INFO.length()<=36;)
            DEBUG_INFO+=" ";
        DEBUG_INFO+= s3;
        DEBUG_INFO+= "\n";
        fputs(DEBUG_INFO.c_str(), yyout);
    }

    int htoi(const char* str){
        int n = 0;
        if (str == NULL) return -1;
        if (*str == '0' && (*(str + 1) == 'x' || *(str + 1) == 'X'))
        {
            str += 2;
        }
        while (1)
        {
            if (*str >= '0' && *str <= '9')
            {
                n = 16 * n + (*str - '0');
            }
            else if (*str >= 'A' && *str <= 'F')//十六进制还要判断字符是不是在A-F或者a-f之间
            {
                n = 16 * n + (*str - 'A' + 10);
            }
            else if (*str >= 'a' && *str <= 'f')
            {
                n = 16 * n + (*str - 'a' + 10);
            }
            else
            {
                break;
            }
            str++;
        }
        return n;
    }

    int otoi(const char* str){
        int n=0; //初始化n=0
        str++;
        while(*str >='0' && *str <='7'){ //判断八进制数的字符串是否结束，并指向下一个数字字符
            n= n*8 + (*str - '0');
            str++;
        }
        return n;
    }

    #endif
%}
%{
   map<std::string,int> map_keyword;
   map<std::string,int> map_id;
   vector<int> scope{0};
   int i=0,j=0;
%}

DIGIT [0-9]
LETTER [a-zA-Z]
ID ({LETTER}|_)({LETTER}|_|{DIGIT})*
KEYWORD  "auto"|"break"|"continue"|"case"|"char"|"const"|"default"|"do"|"double"|"else"|"enum"|"extern"|"float"|"for"|"goto"|"if"|"int"|"long"|"register"|"return"|"short"|"signed"|"sizeof"|"static"|"struct"|"switch"|"typedef"|"union"|"unsigned"|"void"|"volatile"|"while"|"define"
NUM (-)?[1-9]{DIGIT}*|0
EOL (\r\n|\n|\r)
WHITE [\t ]

LOGICOP "&&"|"||"|"!"
BITOP "&"|"|"|"~"|"^"|"<<"|">>"
FLOAT {NUM}"."[0-9]+
HEX 0[xX][0-9a-fA-F]+
OCTAL 0[0-7]+


linecomment_begin "//"
linecomment_element .
linecomment_end \n|\r\n|\r
blockcomment_begin "/*"
blockcomment_element1 .
blockcomment_element2 \n|\r\n|\r
blockcomment_end "*/"

%x BLOCKCOMMENT
%x LINECOMMENT

%%
{blockcomment_begin} {BEGIN BLOCKCOMMENT;}
<BLOCKCOMMENT>{blockcomment_element1} {}
<BLOCKCOMMENT>{blockcomment_element2} {yylineno++;}
<BLOCKCOMMENT>{blockcomment_end} {BEGIN INITIAL;}

{linecomment_begin} {BEGIN LINECOMMENT;}
<LINECOMMENT>{linecomment_element} {}
<LINECOMMENT>{linecomment_end} {yylineno++;BEGIN INITIAL;}

"int" {
    /*
    * Questions: 
    *   Q1: Why we need to return INT in further labs?
    *   Q2: What is "INT" actually?
    */
    #ifdef ONLY_FOR_LEX
        DEBUG_FOR_LAB4("INT\t\tint");
    #else
        return INT;
    #endif
}
"float" {
    /*
    * Questions: 
    *   Q1: Why we need to return INT in further labs?
    *   Q2: What is "INT" actually?
    */
    #ifdef ONLY_FOR_LEX
        DEBUG_FOR_LAB4("FLOAT\t\tfloat");
    #else
        return FLOAT;
    #endif
}
"void" {
    #ifdef ONLY_FOR_LEX
        DEBUG_FOR_LAB4("VOID\t\tvoid");
    #else
        return VOID;
    #endif 
}
"if" {
    #ifdef ONLY_FOR_LEX
        DEBUG_FOR_LAB4("IF\t\tif");
    #else
        return IF;
    #endif
};
"else" {
    #ifdef ONLY_FOR_LEX
        DEBUG_FOR_LAB4("ELSE\t\telse");
    #else
        return ELSE;
    #endif
};
"return" {
    #ifdef ONLY_FOR_LEX
        DEBUG_FOR_LAB4("RETURN\t\treturn");
    #else
        return RETURN;
    #endif
}

"=" {
    #ifdef ONLY_FOR_LEX
        DEBUG_FOR_LAB4("ASSIGN\t\t=");
    #else
        return ASSIGN;
    #endif
}
"<" {
    #ifdef ONLY_FOR_LEX
        DEBUG_FOR_LAB4("LESS\t\t<");
    #else
        return LESS;
    #endif
}
"+" {
    #ifdef ONLY_FOR_LEX
        DEBUG_FOR_LAB4("ADD\t\t+");
    #else
        return ADD;
    #endif
}
"-" {
    #ifdef ONLY_FOR_LEX
        DEBUG_FOR_LAB4("SUB\t\t-");
    #else
        return SUB;
    #endif
}
"*" {
    #ifdef ONLY_FOR_LEX
        DEBUG_FOR_LAB4("MUL\t\t*");
    #else
        return MUL;
    #endif
}
"/" {
    #ifdef ONLY_FOR_LEX
        DEBUG_FOR_LAB4("DIV\t\t/");
    #else
        return DIV;
    #endif
}
"%" {
    #ifdef ONLY_FOR_LEX
        DEBUG_FOR_LAB4("MOD\t\t/");
    #else
        return MOD;
    #endif
}
";" {
    #ifdef ONLY_FOR_LEX
        DEBUG_FOR_LAB4("SEMICOLON\t;");
    #else
        return SEMICOLON;
    #endif
}
"(" {
    #ifdef ONLY_FOR_LEX
        DEBUG_FOR_LAB4("LPAREN\t\t(");
    #else
        return LPAREN;
    #endif
}
")" {
    #ifdef ONLY_FOR_LEX
        DEBUG_FOR_LAB4("RPAREN\t\t)");
    #else
    return RPAREN;
    #endif
}
"{" {
    scope.push_back(yylineno);
    #ifdef ONLY_FOR_LEX
        DEBUG_FOR_LAB4("LBRACE\t\t{");
    #else
        return LBRACE;
    #endif
}
"}" {
    scope.pop_back();
    #ifdef ONLY_FOR_LEX
        DEBUG_FOR_LAB4("RBRACE\t\t}");
    #else
        return RBRACE;
    #endif
}
"!" {
    #ifdef ONLY_FOR_LEX
        DEBUG_FOR_LAB4("NOT\t\t!");
    #else
        return NOT;
    #endif
}
"<" {
    #ifdef ONLY_FOR_LEX
        DEBUG_FOR_LAB4("LESS\t\t<");
    #else
        return LESS;
    #endif
}
">" {
    #ifdef ONLY_FOR_LEX
        DEBUG_FOR_LAB4("GREATER\t\t>");
    #else
        return GREATER;
    #endif
}
"==" {
    #ifdef ONLY_FOR_LEX
        DEBUG_FOR_LAB4("EQUAL\t\t==");
    #else
        return GREATER;
    #endif
}
"<=" {
    #ifdef ONLY_FOR_LEX
        DEBUG_FOR_LAB4("LE\t\t<=");
    #else
        return LE;
    #endif
}
">=" {
    #ifdef ONLY_FOR_LEX
        DEBUG_FOR_LAB4("GE\t\t>=");
    #else
        return GE;
    #endif
}
"!=" {
    #ifdef ONLY_FOR_LEX
        DEBUG_FOR_LAB4("NE\t\t!=");
    #else
        return NE;
    #endif
}
"&&" {
    #ifdef ONLY_FOR_LEX
        DEBUG_FOR_LAB4("AND\t\t&&");
    #else
        return AND;
    #endif
}
"||" {
    #ifdef ONLY_FOR_LEX
        DEBUG_FOR_LAB4("OR\t\t||");
    #else
        return OR;
    #endif
}

{KEYWORD} {
   auto it=map_keyword.find(yytext);
   if(it!=map_keyword.end()){
   	DEBUG_FOR_LAB4("KEYWORD",yytext,"\t");
   }
   else{
   	map_keyword[yytext]=i;	
   	DEBUG_FOR_LAB4("KEYWORD",yytext,"\t");
   	i++;
   }
}

{ID} {
   auto iter=map_id.find(yytext);
   if(iter!=map_id.end()){
   	DEBUG_FOR_LAB4("ID\t",yytext,to_string(scope[scope.size()-1])+"\t\t");
   }
   else{
   	map_id[yytext]=j;
   	DEBUG_FOR_LAB4("ID\t",yytext,to_string(scope[scope.size()-1])+"\t\t");
   	j++;
   }
}

{BITOP} {
    DEBUG_FOR_LAB4("BITOP\t",yytext,"\t");
}

{FLOAT} {
    DEBUG_FOR_LAB4("FLOAT\t",yytext,"\t");
}

{NUM} {
    DEBUG_FOR_LAB4("NUMBER\t",yytext,"\t");
}

{OCTAL} {
    char str[20];
    sprintf(str,"%d",otoi(yytext));
    DEBUG_FOR_LAB4("OCTAL\t",str,"\t");
}

{HEX} {
    char str[20];
    sprintf(str,"%d",htoi(yytext));
    DEBUG_FOR_LAB4("HEX\t",str,"\t");
}

{EOL} yylineno++;
{WHITE}
%%



#ifdef ONLY_FOR_LEX
int main(int argc, char **argv){
    if(argc != 5){
        fprintf(stderr, "Argument Not Enough");
        exit(EXIT_FAILURE);
    }

    if(!(yyin = fopen(argv[1], "r"))){
        fprintf(stderr, "No such file or directory: %s", argv[1]);
        exit(EXIT_FAILURE);
    }

    if(!(yyout = fopen(argv[3], "w"))){
        fprintf(stderr, "No such file or directory: %s", argv[3]);
        exit(EXIT_FAILURE);
    }

    yylex();
    return 0;
}
#endif
