%{
    #include<stdio.h>
    #include<stdlib.h>
    #include<string.h>
    #ifndef YYSTYPE
    #define YYSTYPE char*
    #endif
    char idStr[50];
    char numStr[50];
    int yylex();
    extern int yyparse();
    FILE* yyin;
    void yyerror(const char *s);
%}

%token NUMBER ADD SUB MUL DIV ID LB RB
%left ADD SUB
%left MUL DIV
%right UMINUS

%%
lines   : lines expr ';' {printf("%s\n", $2);}
        | lines ';'
        |
        ;

expr    : expr ADD expr {$$ = (char *)malloc(50*sizeof(char));strcpy($$,$1);strcat($$,$3);strcat($$,"+ ");}
        | expr SUB expr {$$ = (char *)malloc(50*sizeof(char));strcpy($$,$1);strcat($$,$3);strcat($$,"- ");}
        | expr MUL expr {$$ = (char *)malloc(50*sizeof(char));strcpy($$,$1);strcat($$,$3);strcat($$,"* ");}
        | expr DIV expr {$$ = (char *)malloc(50*sizeof(char));strcpy($$,$1);strcat($$,$3);strcat($$,"/ ");}
        | LB expr RB {$$ = (char *)malloc(50*sizeof(char));strcpy($$,$2);}
        | SUB expr %prec UMINUS {$$ = (char *)malloc(50*sizeof(char));strcpy($$,"-");strcat($$,$2);}
        | NUMBER {$$ = (char *)malloc(50*sizeof(char));strcpy($$,$1);strcat($$," ");}
        | ID {$$ = (char *)malloc(50*sizeof(char));strcpy($$,$1);strcat($$," ");}
        ;
%%
int yylex(){
    char t;
    while(1){
        t = getchar();
        if(t == ' ' || t == '\t' || t == '\n');
        else if(t >= '0' && t <= '9'){
            int i = 0;
            while(t >= '0' && t <= '9'){
                numStr[i] = t;
                t = getchar();
                i++;
            }
            numStr[i] = '\0';
            yylval = numStr;
            ungetc(t, stdin);
            return NUMBER;
        }
        else if((t >= 'a' && t <= 'z') || (t >= 'A' && t <= 'Z') || (t == '_')){
            int i = 0;
            while(isdigit(t)||(t>='a'&&t<='z')||(t>='A'&&t<='Z')||t=='_'){
                idStr[i] = t;
                i++;
                t = getchar();
            }
            idStr[i] = '\0';
            yylval = idStr;
            ungetc(t, stdin);
            return ID;
        }
        else if(t == '+')return ADD;
        else if(t == '-')return SUB;
        else if(t == '*')return MUL;
        else if(t == '/')return DIV;
        else if(t == '(')return LB;
        else if(t == ')')return RB;
        else{return t;}
   }
}
void yyerror(const char *s){
    fprintf(stderr, "Parse error: %s\n", s);
    exit(1);
}

int main(void){
    yyin = stdin;
    do{
        yyparse();
    }while(!feof(yyin));
    return 0;
}