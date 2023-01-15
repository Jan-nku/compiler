/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* "%code top" blocks.  */
#line 1 "src/parser.y"

    #include <iostream>
    #include <stack>
    #include <string>
    #include <assert.h>
    #include "parser.h"
    extern Ast ast;
    int yylex();
    int yyerror( char const * );

    std::stack<WhileStmt*> whileStack;
    Type *nowType;
    int paramNo = 0;
    ArrayType *currentArray;
    std::stack<ArrayInit*> arrayStack;
    unsigned int leftBraceCount=0;
    unsigned int arrayIndex=0;
    int *arrayValue;

#line 88 "src/parser.cpp"




# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "parser.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_ID = 3,                         /* ID  */
  YYSYMBOL_INTEGER = 4,                    /* INTEGER  */
  YYSYMBOL_FLOATING = 5,                   /* FLOATING  */
  YYSYMBOL_IF = 6,                         /* IF  */
  YYSYMBOL_ELSE = 7,                       /* ELSE  */
  YYSYMBOL_WHILE = 8,                      /* WHILE  */
  YYSYMBOL_INT = 9,                        /* INT  */
  YYSYMBOL_VOID = 10,                      /* VOID  */
  YYSYMBOL_FLOAT = 11,                     /* FLOAT  */
  YYSYMBOL_CONST = 12,                     /* CONST  */
  YYSYMBOL_LPAREN = 13,                    /* LPAREN  */
  YYSYMBOL_RPAREN = 14,                    /* RPAREN  */
  YYSYMBOL_LBRACE = 15,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 16,                    /* RBRACE  */
  YYSYMBOL_SEMICOLON = 17,                 /* SEMICOLON  */
  YYSYMBOL_LBRACKET = 18,                  /* LBRACKET  */
  YYSYMBOL_RBRACKET = 19,                  /* RBRACKET  */
  YYSYMBOL_ADD = 20,                       /* ADD  */
  YYSYMBOL_SUB = 21,                       /* SUB  */
  YYSYMBOL_MUL = 22,                       /* MUL  */
  YYSYMBOL_DIV = 23,                       /* DIV  */
  YYSYMBOL_MOD = 24,                       /* MOD  */
  YYSYMBOL_OR = 25,                        /* OR  */
  YYSYMBOL_AND = 26,                       /* AND  */
  YYSYMBOL_NOT = 27,                       /* NOT  */
  YYSYMBOL_LESS = 28,                      /* LESS  */
  YYSYMBOL_GREATER = 29,                   /* GREATER  */
  YYSYMBOL_EQUAL = 30,                     /* EQUAL  */
  YYSYMBOL_NOTEQUAL = 31,                  /* NOTEQUAL  */
  YYSYMBOL_LESSEQUAL = 32,                 /* LESSEQUAL  */
  YYSYMBOL_GREATEREQUAL = 33,              /* GREATEREQUAL  */
  YYSYMBOL_ASSIGN = 34,                    /* ASSIGN  */
  YYSYMBOL_RETURN = 35,                    /* RETURN  */
  YYSYMBOL_BREAK = 36,                     /* BREAK  */
  YYSYMBOL_CONTINUE = 37,                  /* CONTINUE  */
  YYSYMBOL_COMMA = 38,                     /* COMMA  */
  YYSYMBOL_THEN = 39,                      /* THEN  */
  YYSYMBOL_YYACCEPT = 40,                  /* $accept  */
  YYSYMBOL_Program = 41,                   /* Program  */
  YYSYMBOL_Stmts = 42,                     /* Stmts  */
  YYSYMBOL_Stmt = 43,                      /* Stmt  */
  YYSYMBOL_LVal = 44,                      /* LVal  */
  YYSYMBOL_ExprStmt = 45,                  /* ExprStmt  */
  YYSYMBOL_AssignStmt = 46,                /* AssignStmt  */
  YYSYMBOL_BlockStmt = 47,                 /* BlockStmt  */
  YYSYMBOL_48_1 = 48,                      /* $@1  */
  YYSYMBOL_EmptyStmt = 49,                 /* EmptyStmt  */
  YYSYMBOL_IfStmt = 50,                    /* IfStmt  */
  YYSYMBOL_WhileStmt = 51,                 /* WhileStmt  */
  YYSYMBOL_52_2 = 52,                      /* @2  */
  YYSYMBOL_BreakStmt = 53,                 /* BreakStmt  */
  YYSYMBOL_ContinueStmt = 54,              /* ContinueStmt  */
  YYSYMBOL_ReturnStmt = 55,                /* ReturnStmt  */
  YYSYMBOL_Exp = 56,                       /* Exp  */
  YYSYMBOL_Cond = 57,                      /* Cond  */
  YYSYMBOL_UnaryExp = 58,                  /* UnaryExp  */
  YYSYMBOL_PrimaryExp = 59,                /* PrimaryExp  */
  YYSYMBOL_AddExp = 60,                    /* AddExp  */
  YYSYMBOL_MulExp = 61,                    /* MulExp  */
  YYSYMBOL_RelExp = 62,                    /* RelExp  */
  YYSYMBOL_EqExp = 63,                     /* EqExp  */
  YYSYMBOL_LAndExp = 64,                   /* LAndExp  */
  YYSYMBOL_LOrExp = 65,                    /* LOrExp  */
  YYSYMBOL_Type = 66,                      /* Type  */
  YYSYMBOL_ArrayIndices = 67,              /* ArrayIndices  */
  YYSYMBOL_DeclStmt = 68,                  /* DeclStmt  */
  YYSYMBOL_VarDeclStmt = 69,               /* VarDeclStmt  */
  YYSYMBOL_ConstDeclStmt = 70,             /* ConstDeclStmt  */
  YYSYMBOL_VarDefList = 71,                /* VarDefList  */
  YYSYMBOL_ConstDefList = 72,              /* ConstDefList  */
  YYSYMBOL_VarDef = 73,                    /* VarDef  */
  YYSYMBOL_74_3 = 74,                      /* $@3  */
  YYSYMBOL_ConstDef = 75,                  /* ConstDef  */
  YYSYMBOL_76_4 = 76,                      /* $@4  */
  YYSYMBOL_InitValList = 77,               /* InitValList  */
  YYSYMBOL_InitVal = 78,                   /* InitVal  */
  YYSYMBOL_79_5 = 79,                      /* $@5  */
  YYSYMBOL_ConstInitVal = 80,              /* ConstInitVal  */
  YYSYMBOL_ConstExp = 81,                  /* ConstExp  */
  YYSYMBOL_FuncRParams = 82,               /* FuncRParams  */
  YYSYMBOL_FuncDef = 83,                   /* FuncDef  */
  YYSYMBOL_84_6 = 84,                      /* $@6  */
  YYSYMBOL_85_7 = 85,                      /* $@7  */
  YYSYMBOL_FuncFParams = 86,               /* FuncFParams  */
  YYSYMBOL_FuncFParam = 87                 /* FuncFParam  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  59
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   225

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  40
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  48
/* YYNRULES -- Number of rules.  */
#define YYNRULES  102
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  168

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   294


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    57,    57,    63,    64,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    82,    93,   108,   115,
     122,   122,   131,   137,   143,   152,   164,   164,   183,   193,
     204,   207,   213,   217,   221,   222,   269,   270,   278,   286,
     289,   293,   297,   304,   305,   315,   329,   332,   347,   362,
     381,   382,   386,   390,   394,   401,   402,   406,   414,   416,
     434,   435,   454,   458,   462,   469,   472,   476,   482,   483,
     487,   491,   495,   499,   503,   507,   511,   527,   545,   576,
     576,   609,   629,   629,   663,   666,   672,   678,   692,   692,
     713,   717,   721,   724,   728,   733,   737,   733,   766,   769,
     773,   778,   787
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "ID", "INTEGER",
  "FLOATING", "IF", "ELSE", "WHILE", "INT", "VOID", "FLOAT", "CONST",
  "LPAREN", "RPAREN", "LBRACE", "RBRACE", "SEMICOLON", "LBRACKET",
  "RBRACKET", "ADD", "SUB", "MUL", "DIV", "MOD", "OR", "AND", "NOT",
  "LESS", "GREATER", "EQUAL", "NOTEQUAL", "LESSEQUAL", "GREATEREQUAL",
  "ASSIGN", "RETURN", "BREAK", "CONTINUE", "COMMA", "THEN", "$accept",
  "Program", "Stmts", "Stmt", "LVal", "ExprStmt", "AssignStmt",
  "BlockStmt", "$@1", "EmptyStmt", "IfStmt", "WhileStmt", "@2",
  "BreakStmt", "ContinueStmt", "ReturnStmt", "Exp", "Cond", "UnaryExp",
  "PrimaryExp", "AddExp", "MulExp", "RelExp", "EqExp", "LAndExp", "LOrExp",
  "Type", "ArrayIndices", "DeclStmt", "VarDeclStmt", "ConstDeclStmt",
  "VarDefList", "ConstDefList", "VarDef", "$@3", "ConstDef", "$@4",
  "InitValList", "InitVal", "$@5", "ConstInitVal", "ConstExp",
  "FuncRParams", "FuncDef", "$@6", "$@7", "FuncFParams", "FuncFParam", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-50)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-96)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     188,    11,   -50,   -50,    -7,     4,   -50,   -50,   -50,   115,
      15,    16,   -50,    15,    15,    15,    10,    37,    85,    98,
     188,   -50,    74,   -50,   -50,   -50,   -50,   -50,   -50,   -50,
     -50,   -50,    92,   -50,   -50,    26,    57,   108,   -50,   -50,
     -50,   -50,    15,    36,    94,    15,    15,   111,   -50,   102,
     -50,   188,   -50,   -50,   -50,   -50,   100,   -50,   -50,   -50,
     -50,    15,   -50,    15,    15,    15,    15,    15,    30,   -13,
     -50,   -50,     7,   -50,   109,    15,   113,    26,    90,    28,
     103,   105,   117,    33,    27,   -50,   -50,   153,   -50,   118,
      57,    57,   -50,   -50,   -50,    80,    70,   119,   -50,   131,
     -50,    15,   -50,   120,   188,    15,    15,    15,    15,    15,
      15,    15,    15,   -50,    15,    76,   -50,   111,   -50,   -50,
     122,   -50,   -50,   -50,   115,    81,   -50,   -50,   -50,   134,
      26,    26,    26,    26,    90,    90,    28,   103,   188,   -50,
     -50,   -50,   -50,   -50,   -50,    80,    80,   139,    12,   -50,
     188,   -50,    80,     0,   -50,   -50,   126,   -50,   115,   -50,
     -50,   -50,    80,    94,   130,   -50,   -50,   -50
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,    16,    40,    41,     0,     0,    62,    63,    64,     0,
       0,    20,    23,     0,     0,     0,     0,     0,     0,     0,
       2,     3,    39,     6,     5,     7,     8,     9,    12,    13,
      14,    10,     0,    46,    34,    32,    43,     0,    11,    68,
      69,    15,    94,     0,    17,     0,     0,     0,    39,     0,
      22,     0,    36,    37,    38,    30,     0,    28,    29,     1,
       4,     0,    18,     0,     0,     0,     0,     0,    76,     0,
      73,    92,     0,    67,     0,     0,     0,    50,    55,    58,
      60,    33,     0,     0,     0,    75,    42,     0,    31,     0,
      44,    45,    47,    48,    49,     0,    78,     0,    70,     0,
      35,     0,    65,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    26,     0,     0,    71,     0,    21,    19,
      88,    86,    77,    79,   100,    76,    72,    93,    66,    24,
      51,    53,    52,    54,    56,    57,    59,    61,     0,    91,
      81,    90,    82,    74,    87,     0,     0,     0,     0,    98,
       0,    27,     0,     0,    85,    80,   101,    96,     0,    25,
      83,    89,     0,   102,     0,    99,    84,    97
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -50,   -50,    95,   -17,     2,   -50,   -50,   -16,   -50,   -50,
     -50,   -50,   -50,   -50,   -50,   -50,    -9,   101,    -5,   -50,
     -34,     5,   -19,    38,    39,   -50,    -4,    -1,   -50,   -50,
     -50,   -50,   -50,    51,   -50,    43,   -50,   -50,   -49,   -50,
     -50,   -50,   -50,   -50,   -50,   -50,   -50,     9
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,    19,    20,    21,    48,    23,    24,    25,    51,    26,
      27,    28,   138,    29,    30,    31,    32,    76,    33,    34,
      35,    36,    78,    79,    80,    81,    37,    96,    38,    39,
      40,    69,    84,    70,   146,    85,   152,   153,   122,   145,
     140,   141,    72,    41,    97,   164,   148,   149
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      44,    49,    22,    60,    98,    47,    45,    56,    52,    53,
      54,    77,    77,     1,     2,     3,   161,    46,     1,     2,
       3,   100,    22,    10,    42,    99,   157,    55,    10,    43,
      13,    14,    50,    71,    74,    13,    14,    15,   162,     1,
       2,     3,    15,   -95,   116,   101,    63,    64,    43,    10,
     158,    43,    89,    22,    57,    73,    13,    14,   109,   110,
      92,    93,    94,    15,    95,   117,   103,   114,    90,    91,
      60,   130,   131,   132,   133,    77,    77,    77,    77,    65,
      66,    67,   115,     1,     2,     3,   121,   129,    75,    22,
     134,   135,   127,    10,    75,   120,   154,   155,    59,    43,
      13,    14,    58,   160,   123,   139,    22,    15,    61,    62,
     142,    68,    75,   166,    83,    95,    86,    88,   105,   106,
     147,   151,   107,   108,     6,     7,     8,   104,   102,   111,
     112,   113,   124,   159,   125,   119,   121,   121,   144,   128,
      22,   150,   156,   121,    43,    11,    87,    82,   167,   136,
     126,   137,    22,   121,   147,   163,     1,     2,     3,     4,
     143,     5,     6,     7,     8,     9,    10,   165,    11,   118,
      12,     0,     0,    13,    14,     0,     0,     0,     0,     0,
      15,     0,     0,     0,     0,     0,     0,     0,    16,    17,
      18,     1,     2,     3,     4,     0,     5,     6,     7,     8,
       9,    10,     0,    11,     0,    12,     0,     0,    13,    14,
       0,     0,     0,     0,     0,    15,     0,     0,     0,     0,
       0,     0,     0,    16,    17,    18
};

static const yytype_int16 yycheck[] =
{
       1,    10,     0,    20,    17,     9,    13,    16,    13,    14,
      15,    45,    46,     3,     4,     5,    16,    13,     3,     4,
       5,    14,    20,    13,    13,    38,    14,    17,    13,    18,
      20,    21,    16,    42,    43,    20,    21,    27,    38,     3,
       4,     5,    27,    13,    17,    38,    20,    21,    18,    13,
      38,    18,    61,    51,    17,    19,    20,    21,    30,    31,
      65,    66,    67,    27,    34,    38,    75,    34,    63,    64,
      87,   105,   106,   107,   108,   109,   110,   111,   112,    22,
      23,    24,    83,     3,     4,     5,    95,   104,    18,    87,
     109,   110,   101,    13,    18,    15,   145,   146,     0,    18,
      20,    21,    17,   152,    34,   114,   104,    27,    34,    17,
      34,     3,    18,   162,     3,    34,    14,    17,    28,    29,
     124,   138,    32,    33,     9,    10,    11,    14,    19,    26,
      25,    14,    13,   150,     3,    17,   145,   146,    16,    19,
     138,     7,     3,   152,    18,    15,    51,    46,   164,   111,
      99,   112,   150,   162,   158,   156,     3,     4,     5,     6,
     117,     8,     9,    10,    11,    12,    13,   158,    15,    16,
      17,    -1,    -1,    20,    21,    -1,    -1,    -1,    -1,    -1,
      27,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    35,    36,
      37,     3,     4,     5,     6,    -1,     8,     9,    10,    11,
      12,    13,    -1,    15,    -1,    17,    -1,    -1,    20,    21,
      -1,    -1,    -1,    -1,    -1,    27,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    35,    36,    37
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     4,     5,     6,     8,     9,    10,    11,    12,
      13,    15,    17,    20,    21,    27,    35,    36,    37,    41,
      42,    43,    44,    45,    46,    47,    49,    50,    51,    53,
      54,    55,    56,    58,    59,    60,    61,    66,    68,    69,
      70,    83,    13,    18,    67,    13,    13,    66,    44,    56,
      16,    48,    58,    58,    58,    17,    56,    17,    17,     0,
      43,    34,    17,    20,    21,    22,    23,    24,     3,    71,
      73,    56,    82,    19,    56,    18,    57,    60,    62,    63,
      64,    65,    57,     3,    72,    75,    14,    42,    17,    56,
      61,    61,    58,    58,    58,    34,    67,    84,    17,    38,
      14,    38,    19,    56,    14,    28,    29,    32,    33,    30,
      31,    26,    25,    14,    34,    67,    17,    38,    16,    17,
      15,    56,    78,    34,    13,     3,    73,    56,    19,    43,
      60,    60,    60,    60,    62,    62,    63,    64,    52,    56,
      80,    81,    34,    75,    16,    79,    74,    66,    86,    87,
       7,    43,    76,    77,    78,    78,     3,    14,    38,    43,
      78,    16,    38,    67,    85,    87,    78,    47
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    40,    41,    42,    42,    43,    43,    43,    43,    43,
      43,    43,    43,    43,    43,    43,    44,    44,    45,    46,
      48,    47,    47,    49,    50,    50,    52,    51,    53,    54,
      55,    55,    56,    57,    58,    58,    58,    58,    58,    59,
      59,    59,    59,    60,    60,    60,    61,    61,    61,    61,
      62,    62,    62,    62,    62,    63,    63,    63,    64,    64,
      65,    65,    66,    66,    66,    67,    67,    67,    68,    68,
      69,    70,    71,    71,    72,    72,    73,    73,    73,    74,
      73,    75,    76,    75,    77,    77,    78,    78,    79,    78,
      80,    81,    82,    82,    82,    84,    85,    83,    86,    86,
      86,    87,    87
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     2,     2,     4,
       0,     4,     2,     1,     5,     7,     0,     6,     2,     2,
       2,     3,     1,     1,     1,     4,     2,     2,     2,     1,
       1,     1,     3,     1,     3,     3,     1,     3,     3,     3,
       1,     3,     3,     3,     3,     1,     3,     3,     1,     3,
       1,     3,     1,     1,     1,     3,     4,     2,     1,     1,
       3,     4,     3,     1,     3,     1,     1,     3,     2,     0,
       5,     3,     0,     5,     3,     1,     1,     2,     0,     4,
       1,     1,     1,     3,     0,     0,     0,     8,     1,     3,
       0,     2,     3
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* Program: Stmts  */
#line 57 "src/parser.y"
            {
        ast.setRoot((yyvsp[0].stmttype));
    }
#line 1299 "src/parser.cpp"
    break;

  case 3: /* Stmts: Stmt  */
#line 63 "src/parser.y"
           {(yyval.stmttype)=(yyvsp[0].stmttype);}
#line 1305 "src/parser.cpp"
    break;

  case 4: /* Stmts: Stmts Stmt  */
#line 64 "src/parser.y"
                {
        (yyval.stmttype) = new SeqNode((yyvsp[-1].stmttype), (yyvsp[0].stmttype));
    }
#line 1313 "src/parser.cpp"
    break;

  case 5: /* Stmt: AssignStmt  */
#line 69 "src/parser.y"
                 {(yyval.stmttype)=(yyvsp[0].stmttype);}
#line 1319 "src/parser.cpp"
    break;

  case 6: /* Stmt: ExprStmt  */
#line 70 "src/parser.y"
               {(yyval.stmttype)=(yyvsp[0].stmttype);}
#line 1325 "src/parser.cpp"
    break;

  case 7: /* Stmt: BlockStmt  */
#line 71 "src/parser.y"
                {(yyval.stmttype)=(yyvsp[0].stmttype);}
#line 1331 "src/parser.cpp"
    break;

  case 8: /* Stmt: EmptyStmt  */
#line 72 "src/parser.y"
                {(yyval.stmttype)=(yyvsp[0].stmttype);}
#line 1337 "src/parser.cpp"
    break;

  case 9: /* Stmt: IfStmt  */
#line 73 "src/parser.y"
             {(yyval.stmttype)=(yyvsp[0].stmttype);}
#line 1343 "src/parser.cpp"
    break;

  case 10: /* Stmt: ReturnStmt  */
#line 74 "src/parser.y"
                 {(yyval.stmttype)=(yyvsp[0].stmttype);}
#line 1349 "src/parser.cpp"
    break;

  case 11: /* Stmt: DeclStmt  */
#line 75 "src/parser.y"
               {(yyval.stmttype)=(yyvsp[0].stmttype);}
#line 1355 "src/parser.cpp"
    break;

  case 12: /* Stmt: WhileStmt  */
#line 76 "src/parser.y"
               {(yyval.stmttype)=(yyvsp[0].stmttype);}
#line 1361 "src/parser.cpp"
    break;

  case 13: /* Stmt: BreakStmt  */
#line 77 "src/parser.y"
               {(yyval.stmttype)=(yyvsp[0].stmttype);}
#line 1367 "src/parser.cpp"
    break;

  case 14: /* Stmt: ContinueStmt  */
#line 78 "src/parser.y"
                  {(yyval.stmttype)=(yyvsp[0].stmttype);}
#line 1373 "src/parser.cpp"
    break;

  case 15: /* Stmt: FuncDef  */
#line 79 "src/parser.y"
              {(yyval.stmttype)=(yyvsp[0].stmttype);}
#line 1379 "src/parser.cpp"
    break;

  case 16: /* LVal: ID  */
#line 82 "src/parser.y"
         {
        SymbolEntry *se;
        se = identifiers->lookup((yyvsp[0].strtype));
        if(se == nullptr){
            fprintf(stderr, "identifier \"%s\" is undefined\n", (char*)(yyvsp[0].strtype));
            delete [](char*)(yyvsp[0].strtype);
            assert(se != nullptr);
        }
        (yyval.exprtype) = new Id(se);
        delete [](yyvsp[0].strtype);
    }
#line 1395 "src/parser.cpp"
    break;

  case 17: /* LVal: ID ArrayIndices  */
#line 93 "src/parser.y"
                     {
        //增加数组作为lval
        SymbolEntry *se;
        se = identifiers->lookup((yyvsp[-1].strtype));
        if(se == nullptr)
        {
            fprintf(stderr, "identifier \"%s\" is undefined\n", (char*)(yyvsp[-1].strtype));
            delete [](char*)(yyvsp[-1].strtype);
            assert(se != nullptr);
        }
        (yyval.exprtype) = new Id(se,(yyvsp[0].exprtype));
        delete [](yyvsp[-1].strtype);
    }
#line 1413 "src/parser.cpp"
    break;

  case 18: /* ExprStmt: Exp SEMICOLON  */
#line 108 "src/parser.y"
                    {
        (yyval.stmttype) = new ExprStmt((yyvsp[-1].exprtype));
    }
#line 1421 "src/parser.cpp"
    break;

  case 19: /* AssignStmt: LVal ASSIGN Exp SEMICOLON  */
#line 115 "src/parser.y"
                              {
        (yyval.stmttype) = new AssignStmt((yyvsp[-3].exprtype), (yyvsp[-1].exprtype));
    }
#line 1429 "src/parser.cpp"
    break;

  case 20: /* $@1: %empty  */
#line 122 "src/parser.y"
           {
        identifiers = new SymbolTable(identifiers);
    }
#line 1437 "src/parser.cpp"
    break;

  case 21: /* BlockStmt: LBRACE $@1 Stmts RBRACE  */
#line 125 "src/parser.y"
                 {
        (yyval.stmttype) = new CompoundStmt((yyvsp[-1].stmttype));
        SymbolTable *top = identifiers;
        identifiers = identifiers->getPrev();
        delete top;
    }
#line 1448 "src/parser.cpp"
    break;

  case 22: /* BlockStmt: LBRACE RBRACE  */
#line 131 "src/parser.y"
                    {
        (yyval.stmttype) = new CompoundStmt();
    }
#line 1456 "src/parser.cpp"
    break;

  case 23: /* EmptyStmt: SEMICOLON  */
#line 137 "src/parser.y"
                {
        (yyval.stmttype) = new EmptyStmt();
    }
#line 1464 "src/parser.cpp"
    break;

  case 24: /* IfStmt: IF LPAREN Cond RPAREN Stmt  */
#line 143 "src/parser.y"
                                            {
        //Cond不是bool的情况，涉及隐式类型转换
        if(!(yyvsp[-2].exprtype)->getType()->isBool()){
            SymbolEntry *se_temp = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
            SymbolEntry *se_zero = new ConstantSymbolEntry(TypeSystem::intType, 0);
            (yyvsp[-2].exprtype) = new BinaryExpr(se_temp, BinaryExpr::NOTEQUAL, (yyvsp[-2].exprtype), new Constant(se_zero));
        }
        (yyval.stmttype) = new IfStmt((yyvsp[-2].exprtype), (yyvsp[0].stmttype));
    }
#line 1478 "src/parser.cpp"
    break;

  case 25: /* IfStmt: IF LPAREN Cond RPAREN Stmt ELSE Stmt  */
#line 152 "src/parser.y"
                                           {
        //Cond不是bool的情况，涉及隐式类型转换
        if(!(yyvsp[-4].exprtype)->getType()->isBool()){
            SymbolEntry *se_temp = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
            SymbolEntry *se_zero = new ConstantSymbolEntry(TypeSystem::intType, 0);
            (yyvsp[-4].exprtype) = new BinaryExpr(se_temp, BinaryExpr::NOTEQUAL, (yyvsp[-4].exprtype), new Constant(se_zero));
        }
        (yyval.stmttype) = new IfElseStmt((yyvsp[-4].exprtype), (yyvsp[-2].stmttype), (yyvsp[0].stmttype));
    }
#line 1492 "src/parser.cpp"
    break;

  case 26: /* @2: %empty  */
#line 164 "src/parser.y"
                               {
        if(!(yyvsp[-1].exprtype)->getType()->isBool()){
            SymbolEntry *se_temp = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
            SymbolEntry *se_zero = new ConstantSymbolEntry(TypeSystem::intType, 0);
            (yyvsp[-1].exprtype) = new BinaryExpr(se_temp, BinaryExpr::NOTEQUAL, (yyvsp[-1].exprtype), new Constant(se_zero));
        }
        WhileStmt* whileStmt = new WhileStmt((yyvsp[-1].exprtype),nullptr);
        (yyval.stmttype) = whileStmt;
        whileStack.push(whileStmt);
    }
#line 1507 "src/parser.cpp"
    break;

  case 27: /* WhileStmt: WHILE LPAREN Cond RPAREN @2 Stmt  */
#line 174 "src/parser.y"
         {
        StmtNode *whileStmt = (yyvsp[-1].stmttype); 
        ((WhileStmt*)whileStmt)->setStmt((yyvsp[0].stmttype));
        (yyval.stmttype)=whileStmt;
        whileStack.pop();
    }
#line 1518 "src/parser.cpp"
    break;

  case 28: /* BreakStmt: BREAK SEMICOLON  */
#line 183 "src/parser.y"
                      {
        //增加break语句检查
        if(whileStack.empty()){
            fprintf(stderr,"break stmt is not in a while stmt\n");
            assert(!whileStack.empty());
        }
        (yyval.stmttype) = new BreakStmt(whileStack.top());
    }
#line 1531 "src/parser.cpp"
    break;

  case 29: /* ContinueStmt: CONTINUE SEMICOLON  */
#line 193 "src/parser.y"
                         {
        //增加continue语句检查
        if(whileStack.empty()){
            fprintf(stderr,"continue stmt is not in a while stmt\n");
            assert(!whileStack.empty());
        }
        (yyval.stmttype) = new ContinueStmt(whileStack.top());
    }
#line 1544 "src/parser.cpp"
    break;

  case 30: /* ReturnStmt: RETURN SEMICOLON  */
#line 204 "src/parser.y"
                       {
        (yyval.stmttype) = new ReturnStmt();
    }
#line 1552 "src/parser.cpp"
    break;

  case 31: /* ReturnStmt: RETURN Exp SEMICOLON  */
#line 207 "src/parser.y"
                          {
        (yyval.stmttype) = new ReturnStmt((yyvsp[-1].exprtype));
    }
#line 1560 "src/parser.cpp"
    break;

  case 32: /* Exp: AddExp  */
#line 213 "src/parser.y"
           {(yyval.exprtype) = (yyvsp[0].exprtype);}
#line 1566 "src/parser.cpp"
    break;

  case 33: /* Cond: LOrExp  */
#line 217 "src/parser.y"
           {(yyval.exprtype) = (yyvsp[0].exprtype);}
#line 1572 "src/parser.cpp"
    break;

  case 34: /* UnaryExp: PrimaryExp  */
#line 221 "src/parser.y"
                 {(yyval.exprtype) = (yyvsp[0].exprtype);}
#line 1578 "src/parser.cpp"
    break;

  case 35: /* UnaryExp: ID LPAREN FuncRParams RPAREN  */
#line 222 "src/parser.y"
                                   {
        SymbolEntry* se;
        se = identifiers->lookup((yyvsp[-3].strtype));
        //检查函数是否未定义
        if(se == nullptr){
            fprintf(stderr, "function \"%s\" is undefined\n", (char*)(yyvsp[-3].strtype));
            delete [](char*)(yyvsp[-3].strtype);
            assert(se != nullptr);
        }
        //检查函数参数数量、类型是否匹配
        
        ExprNode* callParamsType = (yyvsp[-1].exprtype);
        int paramCount = 0;
        while(callParamsType){
            paramCount++;
            callParamsType = (ExprNode*)callParamsType->getNext();
        }
        while(se){
            if(((FunctionType*)(se->getType()))->getParamsType().size() == paramCount){
                break;
            }
            se = se->getNext();
        }
        if(se == nullptr){
            fprintf(stderr, "function \"%s\" having %d params, is undefined\n", (char*)(yyvsp[-3].strtype), paramCount);
            delete [](char*)(yyvsp[-3].strtype);
            assert(se != nullptr);
        }
        
        std::vector<Type*> paramsType = ((FunctionType*)(se->getType()))->getParamsType();
        callParamsType = (yyvsp[-1].exprtype);

        for(auto &params:paramsType){
            
            if(params != callParamsType->getSymbolEntry()->getType()){
                 if(callParamsType->getSymbolEntry()->getType()->isArray() && params->isArray()){
                    callParamsType = (ExprNode*)callParamsType->getNext();
                    continue;
                }
                fprintf(stderr, "your param TYPE should be %s, but when you call func you use %s\n",
                        params->toStr().c_str(),callParamsType->getSymbolEntry()->getType()->toStr().c_str());
            }
            callParamsType = (ExprNode*)callParamsType->getNext();
        }
        
        (yyval.exprtype) = new FuncExpr(se, (yyvsp[-1].exprtype));
    }
#line 1630 "src/parser.cpp"
    break;

  case 36: /* UnaryExp: ADD UnaryExp  */
#line 269 "src/parser.y"
                   {(yyval.exprtype) = (yyvsp[0].exprtype);}
#line 1636 "src/parser.cpp"
    break;

  case 37: /* UnaryExp: SUB UnaryExp  */
#line 270 "src/parser.y"
                   {
        SymbolEntry *se;
        if((yyvsp[0].exprtype)->getType()->isFloat())
            se = new TemporarySymbolEntry(TypeSystem::floatType, SymbolTable::getLabel());
        else
            se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        (yyval.exprtype) = new UnaryExpr(se, UnaryExpr::SUB, (yyvsp[0].exprtype));
    }
#line 1649 "src/parser.cpp"
    break;

  case 38: /* UnaryExp: NOT UnaryExp  */
#line 278 "src/parser.y"
                   {
        SymbolEntry* se = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
        (yyval.exprtype) = new UnaryExpr(se, UnaryExpr::NOT, (yyvsp[0].exprtype));
    }
#line 1658 "src/parser.cpp"
    break;

  case 39: /* PrimaryExp: LVal  */
#line 286 "src/parser.y"
         {
        (yyval.exprtype) = (yyvsp[0].exprtype);
    }
#line 1666 "src/parser.cpp"
    break;

  case 40: /* PrimaryExp: INTEGER  */
#line 289 "src/parser.y"
              {
        SymbolEntry *se = new ConstantSymbolEntry(TypeSystem::intType, (yyvsp[0].itype));
        (yyval.exprtype) = new Constant(se);
    }
#line 1675 "src/parser.cpp"
    break;

  case 41: /* PrimaryExp: FLOATING  */
#line 293 "src/parser.y"
               {
        SymbolEntry *se = new ConstantSymbolEntry(TypeSystem::floatType, (yyvsp[0].ftype));
        (yyval.exprtype) = new Constant(se);
    }
#line 1684 "src/parser.cpp"
    break;

  case 42: /* PrimaryExp: LPAREN Exp RPAREN  */
#line 297 "src/parser.y"
                        {
        (yyval.exprtype) = (yyvsp[-1].exprtype);
    }
#line 1692 "src/parser.cpp"
    break;

  case 43: /* AddExp: MulExp  */
#line 304 "src/parser.y"
           {(yyval.exprtype) = (yyvsp[0].exprtype);}
#line 1698 "src/parser.cpp"
    break;

  case 44: /* AddExp: AddExp ADD MulExp  */
#line 305 "src/parser.y"
                       {
        SymbolEntry* se;
        if ((yyvsp[-2].exprtype)->getType()->isFloat() || (yyvsp[0].exprtype)->getType()->isFloat()) {
            se = new TemporarySymbolEntry(TypeSystem::floatType, SymbolTable::getLabel());
            (yyval.exprtype) = new BinaryExpr(se, BinaryExpr::ADD, (yyvsp[-2].exprtype), (yyvsp[0].exprtype));
        } else {
            se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
            (yyval.exprtype) = new BinaryExpr(se, BinaryExpr::ADD, (yyvsp[-2].exprtype), (yyvsp[0].exprtype));
        }
    }
#line 1713 "src/parser.cpp"
    break;

  case 45: /* AddExp: AddExp SUB MulExp  */
#line 315 "src/parser.y"
                       {
        SymbolEntry* se;
        if ((yyvsp[-2].exprtype)->getType()->isFloat() || (yyvsp[0].exprtype)->getType()->isFloat()) {
            se = new TemporarySymbolEntry(TypeSystem::floatType, SymbolTable::getLabel());
            (yyval.exprtype) = new BinaryExpr(se, BinaryExpr::SUB, (yyvsp[-2].exprtype), (yyvsp[0].exprtype));
        } else {
            se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
            (yyval.exprtype) = new BinaryExpr(se, BinaryExpr::SUB, (yyvsp[-2].exprtype), (yyvsp[0].exprtype));
        }
    }
#line 1728 "src/parser.cpp"
    break;

  case 46: /* MulExp: UnaryExp  */
#line 329 "src/parser.y"
             {
        (yyval.exprtype)=(yyvsp[0].exprtype);
    }
#line 1736 "src/parser.cpp"
    break;

  case 47: /* MulExp: MulExp MUL UnaryExp  */
#line 332 "src/parser.y"
                          {
        SymbolEntry* se;
        if ((yyvsp[-2].exprtype)->getType()->isBool() || (yyvsp[0].exprtype)->getType()->isBool()) {
            fprintf(stderr,"bool cannot use in MUL\n");
            assert(!(yyvsp[-2].exprtype)->getType()->isBool());
            assert(!(yyvsp[0].exprtype)->getType()->isBool());
        }
        if ((yyvsp[-2].exprtype)->getType()->isFloat() || (yyvsp[0].exprtype)->getType()->isFloat()) {
            se = new TemporarySymbolEntry(TypeSystem::floatType, SymbolTable::getLabel());
            (yyval.exprtype) = new BinaryExpr(se, BinaryExpr::MUL, (yyvsp[-2].exprtype), (yyvsp[0].exprtype));
        } else {
            se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
            (yyval.exprtype) = new BinaryExpr(se, BinaryExpr::MUL, (yyvsp[-2].exprtype), (yyvsp[0].exprtype));
        }
    }
#line 1756 "src/parser.cpp"
    break;

  case 48: /* MulExp: MulExp DIV UnaryExp  */
#line 347 "src/parser.y"
                          {
        SymbolEntry* se;
        if ((yyvsp[-2].exprtype)->getType()->isBool() || (yyvsp[0].exprtype)->getType()->isBool()) {
            fprintf(stderr,"bool cannot use in DIV\n");
            assert(!(yyvsp[-2].exprtype)->getType()->isBool());
            assert(!(yyvsp[0].exprtype)->getType()->isBool());
        }
        if ((yyvsp[-2].exprtype)->getType()->isFloat() || (yyvsp[0].exprtype)->getType()->isFloat()) {
            se = new TemporarySymbolEntry(TypeSystem::floatType, SymbolTable::getLabel());
            (yyval.exprtype) = new BinaryExpr(se, BinaryExpr::DIV, (yyvsp[-2].exprtype), (yyvsp[0].exprtype));
        } else {
            se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
            (yyval.exprtype) = new BinaryExpr(se, BinaryExpr::DIV, (yyvsp[-2].exprtype), (yyvsp[0].exprtype));
        }
    }
#line 1776 "src/parser.cpp"
    break;

  case 49: /* MulExp: MulExp MOD UnaryExp  */
#line 362 "src/parser.y"
                          {
        SymbolEntry* se;
        if ((yyvsp[-2].exprtype)->getType()->isBool() || (yyvsp[0].exprtype)->getType()->isBool()) {
            fprintf(stderr,"bool cannot use in MOD\n");
            assert(!(yyvsp[-2].exprtype)->getType()->isBool());
            assert(!(yyvsp[0].exprtype)->getType()->isBool());
        }
        if ((yyvsp[-2].exprtype)->getType()->isFloat() || (yyvsp[0].exprtype)->getType()->isFloat()) {
            se = new TemporarySymbolEntry(TypeSystem::floatType, SymbolTable::getLabel());
            (yyval.exprtype) = new BinaryExpr(se, BinaryExpr::MOD, (yyvsp[-2].exprtype), (yyvsp[0].exprtype));
        } else {
            se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
            (yyval.exprtype) = new BinaryExpr(se, BinaryExpr::MOD, (yyvsp[-2].exprtype), (yyvsp[0].exprtype));
        }      
    }
#line 1796 "src/parser.cpp"
    break;

  case 50: /* RelExp: AddExp  */
#line 381 "src/parser.y"
           {(yyval.exprtype) = (yyvsp[0].exprtype);}
#line 1802 "src/parser.cpp"
    break;

  case 51: /* RelExp: RelExp LESS AddExp  */
#line 382 "src/parser.y"
                        {
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
        (yyval.exprtype) = new BinaryExpr(se, BinaryExpr::LESS, (yyvsp[-2].exprtype), (yyvsp[0].exprtype));
    }
#line 1811 "src/parser.cpp"
    break;

  case 52: /* RelExp: RelExp LESSEQUAL AddExp  */
#line 386 "src/parser.y"
                             {
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
        (yyval.exprtype) = new BinaryExpr(se, BinaryExpr::LESSEQUAL, (yyvsp[-2].exprtype), (yyvsp[0].exprtype));
    }
#line 1820 "src/parser.cpp"
    break;

  case 53: /* RelExp: RelExp GREATER AddExp  */
#line 390 "src/parser.y"
                           {
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
        (yyval.exprtype) = new BinaryExpr(se, BinaryExpr::GREATER, (yyvsp[-2].exprtype), (yyvsp[0].exprtype));
    }
#line 1829 "src/parser.cpp"
    break;

  case 54: /* RelExp: RelExp GREATEREQUAL AddExp  */
#line 394 "src/parser.y"
                                {
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
        (yyval.exprtype) = new BinaryExpr(se, BinaryExpr::GREATEREQUAL, (yyvsp[-2].exprtype), (yyvsp[0].exprtype));
    }
#line 1838 "src/parser.cpp"
    break;

  case 55: /* EqExp: RelExp  */
#line 401 "src/parser.y"
             {(yyval.exprtype) = (yyvsp[0].exprtype);}
#line 1844 "src/parser.cpp"
    break;

  case 56: /* EqExp: EqExp EQUAL RelExp  */
#line 402 "src/parser.y"
                         {
        SymbolEntry* se = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
        (yyval.exprtype) = new BinaryExpr(se, BinaryExpr::EQUAL, (yyvsp[-2].exprtype), (yyvsp[0].exprtype));
    }
#line 1853 "src/parser.cpp"
    break;

  case 57: /* EqExp: EqExp NOTEQUAL RelExp  */
#line 406 "src/parser.y"
                            {
        SymbolEntry* se = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
        (yyval.exprtype) = new BinaryExpr(se, BinaryExpr::NOTEQUAL, (yyvsp[-2].exprtype), (yyvsp[0].exprtype));
    }
#line 1862 "src/parser.cpp"
    break;

  case 58: /* LAndExp: EqExp  */
#line 414 "src/parser.y"
          {(yyval.exprtype) = (yyvsp[0].exprtype);}
#line 1868 "src/parser.cpp"
    break;

  case 59: /* LAndExp: LAndExp AND EqExp  */
#line 417 "src/parser.y"
    {
        SymbolEntry *boolSe;
        if(!(yyvsp[-2].exprtype)->getType()->isBool()){
            boolSe = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
            (yyvsp[-2].exprtype) = new BinaryExpr(boolSe, BinaryExpr::NOTEQUAL, (yyvsp[-2].exprtype), new Constant(new ConstantSymbolEntry(TypeSystem::intType, 0))); 
        }
        if(!(yyvsp[0].exprtype)->getType()->isBool()){
            boolSe = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
            (yyvsp[0].exprtype) = new BinaryExpr(boolSe, BinaryExpr::NOTEQUAL, (yyvsp[0].exprtype), new Constant(new ConstantSymbolEntry(TypeSystem::intType, 0)));
        }
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
        (yyval.exprtype) = new BinaryExpr(se, BinaryExpr::AND, (yyvsp[-2].exprtype), (yyvsp[0].exprtype));
    }
#line 1886 "src/parser.cpp"
    break;

  case 60: /* LOrExp: LAndExp  */
#line 434 "src/parser.y"
            {(yyval.exprtype) = (yyvsp[0].exprtype);}
#line 1892 "src/parser.cpp"
    break;

  case 61: /* LOrExp: LOrExp OR LAndExp  */
#line 436 "src/parser.y"
    {
        SymbolEntry *boolSe;
        if(!(yyvsp[-2].exprtype)->getType()->isBool()){
            boolSe = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
            (yyvsp[-2].exprtype) = new BinaryExpr(boolSe, BinaryExpr::NOTEQUAL, (yyvsp[-2].exprtype), new Constant(new ConstantSymbolEntry(TypeSystem::intType, 0))); 
        }
        if(!(yyvsp[0].exprtype)->getType()->isBool()){
            boolSe = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
            (yyvsp[0].exprtype) = new BinaryExpr(boolSe, BinaryExpr::NOTEQUAL, (yyvsp[0].exprtype), new Constant(new ConstantSymbolEntry(TypeSystem::intType, 0))); 
        }

        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
        (yyval.exprtype) = new BinaryExpr(se, BinaryExpr::OR, (yyvsp[-2].exprtype), (yyvsp[0].exprtype));
    }
#line 1911 "src/parser.cpp"
    break;

  case 62: /* Type: INT  */
#line 454 "src/parser.y"
          {
        (yyval.type) = TypeSystem::intType;
        nowType = TypeSystem::intType;
    }
#line 1920 "src/parser.cpp"
    break;

  case 63: /* Type: VOID  */
#line 458 "src/parser.y"
           {
        (yyval.type) = TypeSystem::voidType;
        nowType = TypeSystem::voidType;
    }
#line 1929 "src/parser.cpp"
    break;

  case 64: /* Type: FLOAT  */
#line 462 "src/parser.y"
            {
        (yyval.type) = TypeSystem::floatType;
        nowType = TypeSystem::floatType;
    }
#line 1938 "src/parser.cpp"
    break;

  case 65: /* ArrayIndices: LBRACKET Exp RBRACKET  */
#line 469 "src/parser.y"
                            {
        (yyval.exprtype)=(yyvsp[-1].exprtype);
    }
#line 1946 "src/parser.cpp"
    break;

  case 66: /* ArrayIndices: ArrayIndices LBRACKET Exp RBRACKET  */
#line 472 "src/parser.y"
                                         {
        (yyval.exprtype)=(yyvsp[-3].exprtype);
        (yyvsp[-3].exprtype)->setNext((yyvsp[-1].exprtype));
    }
#line 1955 "src/parser.cpp"
    break;

  case 67: /* ArrayIndices: LBRACKET RBRACKET  */
#line 476 "src/parser.y"
                       {
        SymbolEntry *se = new ConstantSymbolEntry(TypeSystem::intType, 0);
        (yyval.exprtype) = new Constant(se);
    }
#line 1964 "src/parser.cpp"
    break;

  case 68: /* DeclStmt: VarDeclStmt  */
#line 482 "src/parser.y"
                  {(yyval.stmttype) = (yyvsp[0].stmttype);}
#line 1970 "src/parser.cpp"
    break;

  case 69: /* DeclStmt: ConstDeclStmt  */
#line 483 "src/parser.y"
                    {(yyval.stmttype) = (yyvsp[0].stmttype);}
#line 1976 "src/parser.cpp"
    break;

  case 70: /* VarDeclStmt: Type VarDefList SEMICOLON  */
#line 487 "src/parser.y"
                                {(yyval.stmttype) = (yyvsp[-1].stmttype);}
#line 1982 "src/parser.cpp"
    break;

  case 71: /* ConstDeclStmt: CONST Type ConstDefList SEMICOLON  */
#line 491 "src/parser.y"
                                        {(yyval.stmttype) = (yyvsp[-1].stmttype);}
#line 1988 "src/parser.cpp"
    break;

  case 72: /* VarDefList: VarDefList COMMA VarDef  */
#line 495 "src/parser.y"
                              {
        (yyval.stmttype) = (yyvsp[-2].stmttype);
        (yyvsp[-2].stmttype)->setNext((yyvsp[0].stmttype));
    }
#line 1997 "src/parser.cpp"
    break;

  case 73: /* VarDefList: VarDef  */
#line 499 "src/parser.y"
             {(yyval.stmttype) = (yyvsp[0].stmttype);}
#line 2003 "src/parser.cpp"
    break;

  case 74: /* ConstDefList: ConstDefList COMMA ConstDef  */
#line 503 "src/parser.y"
                                  {
        (yyval.stmttype) = (yyvsp[-2].stmttype);
        (yyvsp[-2].stmttype)->setNext((yyvsp[0].stmttype));
    }
#line 2012 "src/parser.cpp"
    break;

  case 75: /* ConstDefList: ConstDef  */
#line 507 "src/parser.y"
               {(yyval.stmttype) = (yyvsp[0].stmttype);}
#line 2018 "src/parser.cpp"
    break;

  case 76: /* VarDef: ID  */
#line 511 "src/parser.y"
         {
        SymbolEntry* se;
        if(nowType->isInt()){
            se = new IdentifierSymbolEntry(TypeSystem::intType, (yyvsp[0].strtype), identifiers->getLevel());
        }else{
            if(nowType->isFloat()){
                se = new IdentifierSymbolEntry(TypeSystem::floatType, (yyvsp[0].strtype), identifiers->getLevel()); 
            }
        }
        if (!identifiers->install((yyvsp[0].strtype), se)){
            fprintf(stderr, "identifier \"%s\" is already defined\n", (char*)(yyvsp[0].strtype));
            assert(false);
        }
        (yyval.stmttype) = new DeclStmt(new Id(se));
        delete [](yyvsp[0].strtype);
    }
#line 2039 "src/parser.cpp"
    break;

  case 77: /* VarDef: ID ASSIGN InitVal  */
#line 527 "src/parser.y"
                        {
        SymbolEntry*se;
            if(nowType->isInt()){
                se=new IdentifierSymbolEntry(TypeSystem::intType,(yyvsp[-2].strtype),identifiers->getLevel());
                ((IdentifierSymbolEntry*)se)->setValue((yyvsp[0].exprtype)->getIValue());
        }else{
            if(nowType->isFloat()){
                se = new IdentifierSymbolEntry(TypeSystem::floatType, (yyvsp[-2].strtype), identifiers->getLevel());
                ((IdentifierSymbolEntry*)se)->setFValue((yyvsp[0].exprtype)->getFValue());
            }
        }
        if (!identifiers->install((yyvsp[-2].strtype), se)){
            fprintf(stderr, "identifier \"%s\" is already defined\n", (char*)(yyvsp[-2].strtype));
            assert(false);
        }
        (yyval.stmttype) = new DeclStmt(new Id(se),(yyvsp[0].exprtype));
        delete [](yyvsp[-2].strtype);
    }
#line 2062 "src/parser.cpp"
    break;

  case 78: /* VarDef: ID ArrayIndices  */
#line 545 "src/parser.y"
                      {
        ExprNode* t=(yyvsp[0].exprtype);
        std::vector<int> v;
        while(t!=nullptr){
            v.push_back(t->getIValue());
            t=(ExprNode*)(t->getNext());
        }
        Type*arrayType=nowType->isInt()?TypeSystem::intType:TypeSystem::floatType;
        
        Type*tempType;
        while(!v.empty()){       
            tempType=new ArrayType(arrayType,v.back());
            if(arrayType->isArray()){
                ((ArrayType*)arrayType)->setArrayType(tempType);
            }
            arrayType=tempType;
            v.pop_back();
        }
        SymbolEntry*se;
        se = new IdentifierSymbolEntry(arrayType, (yyvsp[-1].strtype), identifiers->getLevel());
        //全局变量，初始化为全0
        if(dynamic_cast<IdentifierSymbolEntry*>(se)->isGlobal()){
            dynamic_cast<IdentifierSymbolEntry*>(se)->setAllZero(true);
        }
        if (!identifiers->install((yyvsp[-1].strtype), se)){
            fprintf(stderr, "identifier \"%s\" is already defined\n", (char*)(yyvsp[-1].strtype));
            assert(false);
        }
        (yyval.stmttype) = new DeclStmt(new Id(se));
        delete [](yyvsp[-1].strtype);
    }
#line 2098 "src/parser.cpp"
    break;

  case 79: /* $@3: %empty  */
#line 576 "src/parser.y"
                            {
        ExprNode* t=(yyvsp[-1].exprtype);
        std::vector<int> v;
        while(t!=nullptr){
            v.push_back(t->getIValue());
            t=(ExprNode*)(t->getNext());
        }
        Type*arrayType=nowType->isInt()?TypeSystem::intType:TypeSystem::floatType;
        Type*tempType;
        while(!v.empty()){
            tempType=new ArrayType(arrayType,v.back());
            if(arrayType->isArray()){
                ((ArrayType*)arrayType)->setArrayType(tempType);
            }
            arrayType=tempType;
            v.pop_back();
        }
        currentArray=(ArrayType*)arrayType;
        leftBraceCount=0;
    }
#line 2123 "src/parser.cpp"
    break;

  case 80: /* VarDef: ID ArrayIndices ASSIGN $@3 InitVal  */
#line 596 "src/parser.y"
           {
        SymbolEntry*se;
        se = new IdentifierSymbolEntry(currentArray, (yyvsp[-4].strtype), identifiers->getLevel());
        if (!identifiers->install((yyvsp[-4].strtype), se)){
            fprintf(stderr, "identifier \"%s\" is already defined\n", (char*)(yyvsp[-4].strtype));
            assert(false);
        }
        (yyval.stmttype) = new DeclStmt(new Id(se), (yyvsp[0].exprtype));
        delete [](yyvsp[-4].strtype);
    }
#line 2138 "src/parser.cpp"
    break;

  case 81: /* ConstDef: ID ASSIGN ConstInitVal  */
#line 609 "src/parser.y"
                             {
        //int/float、是否重定义
        SymbolEntry* se;
        if(nowType->isInt()){
            se = new IdentifierSymbolEntry(TypeSystem::constIntType, (yyvsp[-2].strtype), identifiers->getLevel());
            ((IdentifierSymbolEntry*)se)->setConst();
            ((IdentifierSymbolEntry*)se)->setValue((yyvsp[0].exprtype)->getIValue());
        }else{
            if(nowType->isFloat()){
                se = new IdentifierSymbolEntry(TypeSystem::constFloatType, (yyvsp[-2].strtype), identifiers->getLevel());
                ((IdentifierSymbolEntry*)se)->setFValue((yyvsp[0].exprtype)->getFValue());
            }
        }
        if (!identifiers->install((yyvsp[-2].strtype), se)){
            fprintf(stderr, "identifier \"%s\" is already defined\n", (char*)(yyvsp[-2].strtype));
            assert(false);
        }
        (yyval.stmttype) = new DeclStmt(new Id(se), (yyvsp[0].exprtype));
        delete [](yyvsp[-2].strtype);
    }
#line 2163 "src/parser.cpp"
    break;

  case 82: /* $@4: %empty  */
#line 629 "src/parser.y"
                            {
        ExprNode* t=(yyvsp[-1].exprtype);
        std::vector<int> v;
        while(t!=nullptr){
            v.push_back(t->getIValue());
            t=(ExprNode*)(t->getNext());
        }
        Type*arrayType=nowType->isInt()?TypeSystem::constIntType:TypeSystem::constFloatType;
        Type*tempType;
        while(!v.empty()){
            tempType=new ArrayType(arrayType,v.back());
            if(arrayType->isArray()){
                ((ArrayType*)arrayType)->setArrayType(tempType);
            }
            arrayType=tempType;
            v.pop_back();
        }
        currentArray=(ArrayType*)arrayType;
        leftBraceCount=0;
    }
#line 2188 "src/parser.cpp"
    break;

  case 83: /* ConstDef: ID ArrayIndices ASSIGN $@4 InitVal  */
#line 649 "src/parser.y"
           {
        SymbolEntry*se;
        se = new IdentifierSymbolEntry(currentArray, (yyvsp[-4].strtype), identifiers->getLevel());
        ((IdentifierSymbolEntry*)se)->setConst();
        if (!identifiers->install((yyvsp[-4].strtype), se)){
            fprintf(stderr, "identifier \"%s\" is already defined\n", (char*)(yyvsp[-4].strtype));
            assert(false);
        }
        (yyval.stmttype) = new DeclStmt(new Id(se), (yyvsp[0].exprtype));
        delete [](yyvsp[-4].strtype);
    }
#line 2204 "src/parser.cpp"
    break;

  case 84: /* InitValList: InitValList COMMA InitVal  */
#line 663 "src/parser.y"
                               {
        (yyval.exprtype) = (yyvsp[-2].exprtype);
    }
#line 2212 "src/parser.cpp"
    break;

  case 85: /* InitValList: InitVal  */
#line 666 "src/parser.y"
             {
        (yyval.exprtype) = (yyvsp[0].exprtype);
    }
#line 2220 "src/parser.cpp"
    break;

  case 86: /* InitVal: Exp  */
#line 672 "src/parser.y"
          {
        (yyval.exprtype) = (yyvsp[0].exprtype);
        if(!arrayStack.empty()){
            arrayStack.top()->addExpr((yyvsp[0].exprtype));
        }  
    }
#line 2231 "src/parser.cpp"
    break;

  case 87: /* InitVal: LBRACE RBRACE  */
#line 678 "src/parser.y"
                   {
        SymbolEntry* se;
        if(!arrayStack.empty()){
            currentArray = (ArrayType*)(((ArrayType*)(arrayStack.top()->getSymbolEntry()->getType()))->getElementType());
        }
        se = new ConstantSymbolEntry(currentArray);
        ArrayInit *arrayNode = new ArrayInit(se,true);
        if(!arrayStack.empty())
            arrayStack.top()->addExpr(arrayNode);

        if(!arrayStack.empty())
            currentArray=(ArrayType*)(((ArrayType*)(arrayStack.top()->getSymbolEntry()->getType()))->getElementType());
        (yyval.exprtype)=arrayNode;
    }
#line 2250 "src/parser.cpp"
    break;

  case 88: /* $@5: %empty  */
#line 692 "src/parser.y"
             {
        SymbolEntry* se;
        if(!arrayStack.empty()){
            currentArray = (ArrayType*)(((ArrayType*)(arrayStack.top()->getSymbolEntry()->getType()))->getElementType());
        }
        se = new ConstantSymbolEntry(currentArray);
        ArrayInit *arrayNode = new ArrayInit(se);
        if(!arrayStack.empty())
            arrayStack.top()->addExpr(arrayNode);
        
        arrayStack.push(arrayNode);
    }
#line 2267 "src/parser.cpp"
    break;

  case 89: /* InitVal: LBRACE $@5 InitValList RBRACE  */
#line 704 "src/parser.y"
                      {
        (yyval.exprtype) = arrayStack.top();
        arrayStack.pop();
        if(!arrayStack.empty())
            currentArray=((ArrayType*)(arrayStack.top()->getSymbolEntry()->getType()));
    }
#line 2278 "src/parser.cpp"
    break;

  case 90: /* ConstInitVal: ConstExp  */
#line 713 "src/parser.y"
               {(yyval.exprtype) = (yyvsp[0].exprtype);}
#line 2284 "src/parser.cpp"
    break;

  case 91: /* ConstExp: Exp  */
#line 717 "src/parser.y"
         {(yyval.exprtype) = (yyvsp[0].exprtype);}
#line 2290 "src/parser.cpp"
    break;

  case 92: /* FuncRParams: Exp  */
#line 721 "src/parser.y"
          {
        (yyval.exprtype) = (yyvsp[0].exprtype);
    }
#line 2298 "src/parser.cpp"
    break;

  case 93: /* FuncRParams: FuncRParams COMMA Exp  */
#line 724 "src/parser.y"
                            {
        (yyval.exprtype) = (yyvsp[-2].exprtype);
        (yyval.exprtype)->setNext((yyvsp[0].exprtype));
    }
#line 2307 "src/parser.cpp"
    break;

  case 94: /* FuncRParams: %empty  */
#line 728 "src/parser.y"
             {(yyval.exprtype)=nullptr;}
#line 2313 "src/parser.cpp"
    break;

  case 95: /* $@6: %empty  */
#line 733 "src/parser.y"
            {
        identifiers = new SymbolTable(identifiers);
        paramNo = 0;
    }
#line 2322 "src/parser.cpp"
    break;

  case 96: /* $@7: %empty  */
#line 737 "src/parser.y"
                              {
        Type* funcType;
        std::vector<SymbolEntry*> vec;
        DeclStmt* temp = (DeclStmt*)(yyvsp[-1].stmttype);
        while(temp){
            vec.push_back(temp->getId()->getSymbolEntry());
            temp = (DeclStmt*)(temp->getNext());
        }
        funcType = new FunctionType((yyvsp[-5].type), vec);
        SymbolEntry* se = new IdentifierSymbolEntry(funcType, (yyvsp[-4].strtype), identifiers->getPrev()->getLevel());
        if(!identifiers->getPrev()->install((yyvsp[-4].strtype), se)){
            fprintf(stderr, "redefinition of \'%s %s\'\n", (yyvsp[-4].strtype), se->getType()->toStr().c_str());
        }
        //assert(identifiers->getPrev()->install($2, se));
    }
#line 2342 "src/parser.cpp"
    break;

  case 97: /* FuncDef: Type ID $@6 LPAREN FuncFParams RPAREN $@7 BlockStmt  */
#line 753 "src/parser.y"
    {
        SymbolEntry *se;
        se = identifiers->lookup((yyvsp[-6].strtype));
        assert(se != nullptr);
        (yyval.stmttype) = new FunctionDef(se, (DeclStmt*)(yyvsp[-3].stmttype),(yyvsp[0].stmttype));
        SymbolTable *top = identifiers;
        identifiers = identifiers->getPrev();
        delete top;
        delete [](yyvsp[-6].strtype);
    }
#line 2357 "src/parser.cpp"
    break;

  case 98: /* FuncFParams: FuncFParam  */
#line 766 "src/parser.y"
                {
        (yyval.stmttype)=(yyvsp[0].stmttype);
    }
#line 2365 "src/parser.cpp"
    break;

  case 99: /* FuncFParams: FuncFParams COMMA FuncFParam  */
#line 769 "src/parser.y"
                                  {
        (yyval.stmttype)=(yyvsp[-2].stmttype);
        (yyval.stmttype)->setNext((yyvsp[0].stmttype));
    }
#line 2374 "src/parser.cpp"
    break;

  case 100: /* FuncFParams: %empty  */
#line 773 "src/parser.y"
             {(yyval.stmttype)=nullptr;}
#line 2380 "src/parser.cpp"
    break;

  case 101: /* FuncFParam: Type ID  */
#line 778 "src/parser.y"
           {
        SymbolEntry*se;
        se=new IdentifierSymbolEntry((yyvsp[-1].type),(yyvsp[0].strtype),identifiers->getLevel(), paramNo++);
        dynamic_cast<IdentifierSymbolEntry*>(se)->setParam();
        dynamic_cast<IdentifierSymbolEntry*>(se)->setAddr(new Operand(se));
        identifiers->install((yyvsp[0].strtype),se);
        (yyval.stmttype)=new DeclStmt(new Id(se));
        delete[](yyvsp[0].strtype);
    }
#line 2394 "src/parser.cpp"
    break;

  case 102: /* FuncFParam: Type ID ArrayIndices  */
#line 787 "src/parser.y"
                          {
        ExprNode* t=(yyvsp[0].exprtype);
        std::vector<int> v;
        while(t!=nullptr){
            v.push_back(t->getIValue());
            t=(ExprNode*)(t->getNext());
        }
        Type*arrayType=(yyvsp[-2].type)->isInt()?TypeSystem::intType:TypeSystem::floatType;
        Type*tempType;
        while(!v.empty()){
            tempType=new ArrayType(arrayType,v.back());
            if(arrayType->isArray()){
                ((ArrayType*)arrayType)->setArrayType(tempType);
            }
            arrayType=tempType;
            v.pop_back();
        }
        SymbolEntry*se;
        se = new IdentifierSymbolEntry(arrayType, (yyvsp[-1].strtype), identifiers->getLevel(), paramNo++);
        dynamic_cast<IdentifierSymbolEntry*>(se)->setParam();
        dynamic_cast<IdentifierSymbolEntry*>(se)->setAddr(new Operand(se));
        identifiers->install((yyvsp[-1].strtype), se);
        (yyval.stmttype) = new DeclStmt(new Id(se));
        delete [](yyvsp[-1].strtype);
    }
#line 2424 "src/parser.cpp"
    break;


#line 2428 "src/parser.cpp"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 815 "src/parser.y"


int yyerror(char const* message)
{
    std::cerr<<message<<std::endl;
    return -1;
}
