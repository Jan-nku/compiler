#include <iostream>
#include <string.h>
#include <unistd.h>
#include "Ast.h"
#include "Unit.h"
#include "MachineCode.h"
#include "LinearScan.h"
using namespace std;

Ast ast;                //抽象语法树
Unit unit;              //顶层模块unit
MachineUnit mUnit;      //MachineUnit

//Lex中本身已定义的输入和输出文件指针
//通过预定义的全局变量 yyin 与 yyout 来进行 IO 重定向
extern FILE *yyin;
extern FILE *yyout;

int yyparse();

char outfile[256] = "a.out";
bool dump_tokens;
bool dump_ast;
bool dump_ir;
bool dump_asm;

int main(int argc, char *argv[])
{
    int opt;
    //getopt函数:命令行参数解析函数
    while ((opt = getopt(argc, argv, "Siato:")) != -1)
    {
        switch (opt)
        {
        case 'o':
            strcpy(outfile, optarg);
            break;
        case 'a':
        //print abstract syntax tree
            dump_ast = true;
            break;
        //print tokens
        case 't':
            dump_tokens = true;
            break;
        //print intermediate code
        case 'i':
            dump_ir = true;
            break;
        //print assembly code
        case 'S':
            dump_asm = true;
            break;
        default:
            fprintf(stderr, "Usage: %s [-o outfile] infile\n", argv[0]);
            exit(EXIT_FAILURE);
            break;
        }
    }
    if (optind >= argc)
    {
        fprintf(stderr, "no input file\n");
        exit(EXIT_FAILURE);
    }
    if (!(yyin = fopen(argv[optind], "r")))
    {
        fprintf(stderr, "%s: No such file or directory\nno input file\n", argv[optind]);
        exit(EXIT_FAILURE);
    }
    if (!(yyout = fopen(outfile, "w")))
    {
        fprintf(stderr, "%s: fail to open output file\n", outfile);
        exit(EXIT_FAILURE);
    }
    
    yyparse();//语法分析

    dump_ast = true;
    if(dump_ast)
        ast.output();//打印抽象语法树

    //类型检查
    ast.typeCheck();
    //中间代码生成
    ast.genCode(&unit);
    dump_ir = true;
    if(dump_ir)
        unit.output();//打印中间代码

    //实现IR指令到汇编指令的翻译
    unit.genMachineCode(&mUnit);
    //线性扫描寄存器分配算法
    LinearScan linearScan(&mUnit);
    linearScan.allocateRegisters();
    if(dump_asm)
        mUnit.output();//打印汇编代码
    return 0;
}

