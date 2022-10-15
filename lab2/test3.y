%{
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<map>
#include<string>
#include<cstring>
using namespace std;
struct var{
    double value;
    string name;
};
#ifndef YYSTYPE
#define YYSTYPE var
#endif
int yylex();
extern int yyparse();
FILE* yyin;
void yyerror(const char* s);
map<string,double> stable;
%}

%token ADD 
%token SUB
%token MUL
%token DIV
%token LB
%token RB
%token <value> NUMBER
%token EQUAL
%token <name> ID

%left EQUAL
%left ADD SUB
%left MUL DIV
%right UMINUS

%type <value> expr

%%


lines   : lines statement ';' 
        | lines ';'
        |
        ;

statement   : ID EQUAL expr { stable[$1]=$3;}
            | expr { printf("%f\n", $1); }
            ;

expr    : expr ADD expr { $$ = $1 + $3; }
        | expr SUB expr { $$ = $1 - $3; }
        | expr MUL expr { $$ = $1 * $3; }
        | expr DIV expr { $$ = $1 / $3; }
        | LB expr RB { $$ = $2; }
        | SUB expr %prec UMINUS { $$ = -$2; }
        | NUMBER {$$=$1;}
        | ID {$$=stable[$1];}
        ;
 
%%

// programs section

int yylex()
{
    int t;
    while(1){
        t=getchar();
        if(t==' '||t=='\t'||t=='\n'){
            ;
        }
        else if(isdigit(t)){
            yylval.value=0;
            while(isdigit(t)){
                yylval.value=yylval.value*10+t-'0';
                t=getchar();
            }
            ungetc(t,stdin);
            return NUMBER;
        }
        else if((t>='a'&&t<='z')||(t>='A'&&t<='Z')||t=='_')
        {
            string temp;
            temp+=t;
            t=getchar();
            while(isdigit(t)||(t>='a'&&t<='z')||(t>='A'&&t<='Z')||t=='_'){
                temp+=t;
                t=getchar();
            }
            yylval.name=temp;
            ungetc(t,stdin);
            return ID;
        }
        else if(t=='+')
            return ADD;
        else if(t=='-')
            return SUB;
        else if(t=='*')
            return MUL;
        else if(t=='/')
            return DIV;
        else if(t=='(')
            return LB;
        else if(t==')')
            return RB;
        else if(t=='=')
            return EQUAL;
        else
            return t;
    }
}

int main(void)
{
    yyin = stdin ;
    do {
            yyparse();
    } while (! feof (yyin));
    return 0;
}
void yyerror(const char* s) {
    fprintf (stderr , "Parse error : %s\n", s );
    exit (1);
}
