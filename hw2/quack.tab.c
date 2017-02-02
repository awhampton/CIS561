/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 13 "quack.y" /* yacc.c:339  */

#include <cstdio>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <list>
#include "quack.h"
using namespace std;

// the root of the abstract syntax tree
pgm_node *root;

// stuff from flex that bison needs to know about:
extern "C" int yylex();
extern "C" int yyparse();
extern "C" FILE *yyin;
extern int yylineno;

extern void yyerror(const char *s);
char* INFILE_NAME;

#line 88 "quack.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "quack.tab.h".  */
#ifndef YY_YY_QUACK_TAB_H_INCLUDED
# define YY_YY_QUACK_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    CLASS = 258,
    DEF = 259,
    EXTENDS = 260,
    IF = 261,
    ELIF = 262,
    ELSE = 263,
    WHILE = 264,
    RETURN = 265,
    LESS = 266,
    MORE = 267,
    ATLEAST = 268,
    ATMOST = 269,
    EQUALS = 270,
    AND = 271,
    OR = 272,
    NOT = 273,
    LPAREN = 274,
    RPAREN = 275,
    LBRACE = 276,
    RBRACE = 277,
    COLON = 278,
    SEMICOLON = 279,
    GETS = 280,
    COMMA = 281,
    PERIOD = 282,
    PLUS = 283,
    MINUS = 284,
    TIMES = 285,
    DIVIDE = 286,
    IDENT = 287,
    INT_LIT = 288,
    STRING_LIT = 289
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 37 "quack.y" /* yacc.c:355  */

	int   ival;
	char *sval;
	char  cval;
	char                     *opt_ident_type;
	method_node              *method_type;
	list<method_node *>      *methods_type;
	actual_arg_node          *actual_arg_type;
	list<actual_arg_node *>  *actual_args_type;
	formal_arg_node          *formal_arg_type;
	list<formal_arg_node *>  *formal_args_type;
	class_body_node          *class_body_type;
	class_signature_node     *class_signature_type;
	class_node               *class_type;
	expr_node                *expr_type;
	statement_node           *statement_type;
	condition_node           *conditional_type;
	list<condition_node *>   *conditionals_type;
	list<statement_node *>   *statements_type;
	list<class_node *>       *classes_type;
	pgm_node                 *prog_type;

#line 186 "quack.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_QUACK_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 203 "quack.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

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

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
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


#if ! defined yyoverflow || YYERROR_VERBOSE

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
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
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
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   235

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  35
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  28
/* YYNRULES -- Number of rules.  */
#define YYNRULES  62
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  116

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   289

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
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
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   139,   139,   143,   144,   148,   152,   153,   157,   161,
     165,   166,   170,   174,   175,   179,   183,   187,   188,   192,
     196,   200,   204,   208,   212,   216,   217,   221,   225,   226,
     230,   234,   235,   239,   243,   244,   248,   252,   256,   260,
     264,   268,   272,   276,   280,   284,   288,   292,   296,   300,
     304,   308,   312,   316,   320,   324,   328,   332,   333,   337,
     341,   342,   346
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "CLASS", "DEF", "EXTENDS", "IF", "ELIF",
  "ELSE", "WHILE", "RETURN", "LESS", "MORE", "ATLEAST", "ATMOST", "EQUALS",
  "AND", "OR", "NOT", "LPAREN", "RPAREN", "LBRACE", "RBRACE", "COLON",
  "SEMICOLON", "GETS", "COMMA", "PERIOD", "PLUS", "MINUS", "TIMES",
  "DIVIDE", "IDENT", "INT_LIT", "STRING_LIT", "$accept", "program",
  "classes", "class", "class_signature", "class_sig_extends",
  "class_sig_no_extends", "formal_args", "formal_arg",
  "formal_arg_repetitions", "formal_arg_repetition", "class_body",
  "statements", "statement", "methods", "method", "opt_ident",
  "statement_block", "elifs", "elif_rule", "opt_else", "else_rule",
  "l_expr", "r_expr", "actual_args", "actual_arg",
  "actual_arg_repetitions", "actual_arg_repetition", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289
};
# endif

#define YYPACT_NINF -29

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-29)))

#define YYTABLE_NINF -30

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -29,    19,    17,   -29,    -9,   -29,    11,   -29,   -29,    38,
      18,   -29,   -29,    27,    27,   201,    27,    27,    22,   -29,
     -29,   -29,    15,    75,    21,    38,   -29,    96,    96,   -29,
     117,   187,   138,    27,    26,    29,    27,    27,    27,    27,
      27,    27,    27,   -29,    30,    27,    27,    27,    27,    41,
      48,   -29,     9,   -29,   -29,   -29,   -29,   -29,   180,    49,
     -29,   -29,    27,   -19,   -19,   -19,   -19,   -19,   187,   187,
      56,   -13,   -13,    52,    52,    44,    76,    50,   -29,   -29,
      33,     8,    54,   -29,   159,    27,   -29,    61,    65,   -29,
      27,    73,   -29,   -29,   -29,    27,   -29,   -29,    77,    69,
     -29,    21,    96,   -29,   180,   -29,    64,   -29,    78,   -29,
      91,    92,    68,    73,   -29,   -29
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       4,     0,    18,     1,     0,     3,     0,     6,     7,     2,
       0,    18,     5,     0,     0,     0,     0,     0,    37,    40,
      39,    17,    41,     0,    11,    26,    41,     0,     0,    24,
       0,    54,     0,    58,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    22,     0,     0,     0,     0,     0,     0,
       0,    10,     0,    18,    32,    20,    23,    46,    61,     0,
      57,    28,     0,    49,    51,    50,    48,    47,    52,    53,
      38,    42,    43,    44,    45,     0,     9,     0,    16,    25,
       0,    35,    59,    56,     0,    58,    14,     0,     0,    30,
       0,     0,    31,    19,    34,     0,    60,    21,     0,    12,
       8,    11,     0,    36,    62,    55,     0,    13,     0,    33,
       0,    29,     0,     0,    15,    27
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -29,   -29,   -29,   -29,   -29,   -29,   -29,     0,   -29,   -29,
     -29,   -29,    -4,   -29,   -29,   -29,     5,   -28,   -29,   -29,
     -29,   -29,    -3,   -12,    34,   -29,   -29,   -29
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     1,     2,     5,     6,     7,     8,    50,    51,    99,
     107,    12,     9,    21,    52,    79,    35,    54,    81,    92,
      93,    94,    26,    23,    59,    60,    82,    96
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      55,    27,    28,    30,    31,    32,    22,    25,    44,    45,
      46,    47,    48,    77,    44,    90,    91,    47,    48,     3,
       4,    58,    22,    10,    63,    64,    65,    66,    67,    68,
      69,    78,    11,    71,    72,    73,    74,    24,    34,    13,
     -29,    33,    14,    15,    13,    16,    17,    14,    15,    80,
      84,    16,    17,    49,    62,    89,    16,    17,    61,    18,
      19,    20,    70,   103,    75,    18,    19,    20,    76,    83,
      18,    19,    20,    58,   109,    85,    86,    22,   102,    44,
      95,    87,    88,   104,   101,   115,    36,    37,    38,    39,
      40,    41,    42,   100,    53,   106,   110,   105,   111,    43,
     114,   108,    44,    45,    46,    47,    48,    36,    37,    38,
      39,    40,    41,    42,   112,    34,   113,    53,     0,    98,
       0,     0,     0,    44,    45,    46,    47,    48,    36,    37,
      38,    39,    40,    41,    42,     0,     0,     0,     0,     0,
       0,    56,     0,     0,    44,    45,    46,    47,    48,    36,
      37,    38,    39,    40,    41,    42,     0,     0,    57,     0,
       0,     0,     0,     0,     0,    44,    45,    46,    47,    48,
      36,    37,    38,    39,    40,    41,    42,     0,     0,     0,
       0,     0,     0,    97,     0,     0,    44,    45,    46,    47,
      48,    36,    37,    38,    39,    40,    41,    42,    36,    37,
      38,    39,    40,     0,     0,     0,     0,    44,    45,    46,
      47,    48,     0,     0,    44,    45,    46,    47,    48,    16,
      17,     0,     0,     0,     0,    29,     0,     0,     0,     0,
       0,     0,     0,    18,    19,    20
};

static const yytype_int8 yycheck[] =
{
      28,    13,    14,    15,    16,    17,     9,    11,    27,    28,
      29,    30,    31,     4,    27,     7,     8,    30,    31,     0,
       3,    33,    25,    32,    36,    37,    38,    39,    40,    41,
      42,    22,    21,    45,    46,    47,    48,    19,    23,     6,
      25,    19,     9,    10,     6,    18,    19,     9,    10,    53,
      62,    18,    19,    32,    25,    22,    18,    19,    32,    32,
      33,    34,    32,    91,    23,    32,    33,    34,    20,    20,
      32,    33,    34,    85,   102,    19,    32,    80,    90,    27,
      26,     5,    32,    95,    19,   113,    11,    12,    13,    14,
      15,    16,    17,    32,    21,    26,    32,    20,    20,    24,
      32,   101,    27,    28,    29,    30,    31,    11,    12,    13,
      14,    15,    16,    17,    23,    23,   111,    21,    -1,    85,
      -1,    -1,    -1,    27,    28,    29,    30,    31,    11,    12,
      13,    14,    15,    16,    17,    -1,    -1,    -1,    -1,    -1,
      -1,    24,    -1,    -1,    27,    28,    29,    30,    31,    11,
      12,    13,    14,    15,    16,    17,    -1,    -1,    20,    -1,
      -1,    -1,    -1,    -1,    -1,    27,    28,    29,    30,    31,
      11,    12,    13,    14,    15,    16,    17,    -1,    -1,    -1,
      -1,    -1,    -1,    24,    -1,    -1,    27,    28,    29,    30,
      31,    11,    12,    13,    14,    15,    16,    17,    11,    12,
      13,    14,    15,    -1,    -1,    -1,    -1,    27,    28,    29,
      30,    31,    -1,    -1,    27,    28,    29,    30,    31,    18,
      19,    -1,    -1,    -1,    -1,    24,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    32,    33,    34
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    36,    37,     0,     3,    38,    39,    40,    41,    47,
      32,    21,    46,     6,     9,    10,    18,    19,    32,    33,
      34,    48,    57,    58,    19,    47,    57,    58,    58,    24,
      58,    58,    58,    19,    23,    51,    11,    12,    13,    14,
      15,    16,    17,    24,    27,    28,    29,    30,    31,    32,
      42,    43,    49,    21,    52,    52,    24,    20,    58,    59,
      60,    32,    25,    58,    58,    58,    58,    58,    58,    58,
      32,    58,    58,    58,    58,    23,    20,     4,    22,    50,
      47,    53,    61,    20,    58,    19,    32,     5,    32,    22,
       7,     8,    54,    55,    56,    26,    62,    24,    59,    44,
      32,    19,    58,    52,    58,    20,    26,    45,    42,    52,
      32,    20,    23,    51,    32,    52
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    35,    36,    37,    37,    38,    39,    39,    40,    41,
      42,    42,    43,    44,    44,    45,    46,    47,    47,    48,
      48,    48,    48,    48,    48,    49,    49,    50,    51,    51,
      52,    53,    53,    54,    55,    55,    56,    57,    57,    58,
      58,    58,    58,    58,    58,    58,    58,    58,    58,    58,
      58,    58,    58,    58,    58,    58,    58,    59,    59,    60,
      61,    61,    62
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     2,     0,     2,     1,     1,     7,     5,
       1,     0,     4,     2,     0,     4,     4,     2,     0,     5,
       3,     5,     2,     3,     2,     2,     0,     7,     2,     0,
       3,     2,     0,     3,     1,     0,     2,     1,     3,     1,
       1,     1,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     2,     6,     4,     1,     0,     2,
       2,     0,     2
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
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

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



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

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
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
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
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


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
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
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

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

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
| yyreduce -- Do a reduction.  |
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
        case 2:
#line 139 "quack.y" /* yacc.c:1646  */
    { cout << "done with a quack file!" << endl; (yyval.prog_type) = new pgm_node((yyvsp[-1].classes_type), (yyvsp[0].statements_type)); root = (yyval.prog_type); }
#line 1385 "quack.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 143 "quack.y" /* yacc.c:1646  */
    { cout << "got more classes" << endl; (yyval.classes_type) = (yyvsp[-1].classes_type); (yyvsp[-1].classes_type)->push_back((yyvsp[0].class_type)); }
#line 1391 "quack.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 144 "quack.y" /* yacc.c:1646  */
    { cout << "done with classes" << endl; (yyval.classes_type) = new list<class_node *>(); }
#line 1397 "quack.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 148 "quack.y" /* yacc.c:1646  */
    { cout << "got class" << endl; (yyval.class_type) = new class_node((yyvsp[-1].class_signature_type), (yyvsp[0].class_body_type)); }
#line 1403 "quack.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 152 "quack.y" /* yacc.c:1646  */
    {cout << "got class signature extends" << endl; (yyval.class_signature_type) = (yyvsp[0].class_signature_type); }
#line 1409 "quack.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 153 "quack.y" /* yacc.c:1646  */
    {cout << "got class signature no extends" << endl; (yyval.class_signature_type) = (yyvsp[0].class_signature_type); }
#line 1415 "quack.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 157 "quack.y" /* yacc.c:1646  */
    { cout << "got class sig with extends:: " << (yyvsp[-5].sval) << endl; (yyval.class_signature_type) = new class_signature_node((yyvsp[-5].sval), (yyvsp[0].sval), (yyvsp[-3].formal_args_type)); }
#line 1421 "quack.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 161 "quack.y" /* yacc.c:1646  */
    { cout << "got class sig without extends:: " << (yyvsp[-3].sval) << endl; (yyval.class_signature_type) = new class_signature_node((yyvsp[-3].sval), (yyvsp[-1].formal_args_type)); }
#line 1427 "quack.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 165 "quack.y" /* yacc.c:1646  */
    { cout << "got formal args" << endl; (yyval.formal_args_type) = (yyvsp[0].formal_args_type); }
#line 1433 "quack.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 166 "quack.y" /* yacc.c:1646  */
    { (yyval.formal_args_type) = new list<formal_arg_node *>(); }
#line 1439 "quack.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 170 "quack.y" /* yacc.c:1646  */
    { cout << "got formal arg:: " << (yyvsp[-3].sval) << " : " << (yyvsp[-1].sval) << endl; (yyvsp[0].formal_args_type)->push_front( new formal_arg_node((yyvsp[-3].sval), (yyvsp[-1].sval)) ); (yyval.formal_args_type) = (yyvsp[0].formal_args_type); }
#line 1445 "quack.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 174 "quack.y" /* yacc.c:1646  */
    { cout << "got formal arg repetitions" << endl; (yyval.formal_args_type) = (yyvsp[-1].formal_args_type); (yyvsp[-1].formal_args_type)->push_back((yyvsp[0].formal_arg_type)); }
#line 1451 "quack.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 175 "quack.y" /* yacc.c:1646  */
    { cout << "done with formal arg repetitions" << endl; (yyval.formal_args_type) = new list<formal_arg_node *>(); }
#line 1457 "quack.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 179 "quack.y" /* yacc.c:1646  */
    { cout << "got formal arg repetition:: " << (yyvsp[-2].sval) << " : " << (yyvsp[0].sval) << endl; (yyval.formal_arg_type) = new formal_arg_node((yyvsp[-2].sval), (yyvsp[0].sval)); }
#line 1463 "quack.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 183 "quack.y" /* yacc.c:1646  */
    { cout << "got class body" << endl; (yyval.class_body_type) = new class_body_node((yyvsp[-2].statements_type), (yyvsp[-1].methods_type)); }
#line 1469 "quack.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 187 "quack.y" /* yacc.c:1646  */
    { cout << "got more statements" << endl; (yyval.statements_type) = (yyvsp[-1].statements_type); (yyvsp[-1].statements_type)->push_back((yyvsp[0].statement_type)); }
#line 1475 "quack.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 188 "quack.y" /* yacc.c:1646  */
    { cout << "done with statements" << endl; (yyval.statements_type) = new list<statement_node *>(); }
#line 1481 "quack.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 192 "quack.y" /* yacc.c:1646  */
    { cout << "statement if" << endl; (yyval.statement_type) = new if_elifs_else_node(new condition_node((yyvsp[-3].expr_type),(yyvsp[-2].statements_type)), (yyvsp[-1].conditionals_type), (yyvsp[0].statements_type)); }
#line 1487 "quack.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 196 "quack.y" /* yacc.c:1646  */
    { cout << "statement while" << endl; (yyval.statement_type) = new while_node(new while_condition_node((yyvsp[-1].expr_type), (yyvsp[0].statements_type))); }
#line 1493 "quack.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 200 "quack.y" /* yacc.c:1646  */
    { cout << "statement assignment" << endl; (yyval.statement_type) = new assignment_node((yyvsp[-4].expr_type), (yyvsp[-3].opt_ident_type), (yyvsp[-1].expr_type)); }
#line 1499 "quack.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 204 "quack.y" /* yacc.c:1646  */
    { cout << "statement r_expr" << endl; (yyval.statement_type) = new bare_expr_node((yyvsp[-1].expr_type)); }
#line 1505 "quack.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 208 "quack.y" /* yacc.c:1646  */
    { cout << "statement return r_expr" << endl; (yyval.statement_type) = new return_node((yyvsp[-1].expr_type)); }
#line 1511 "quack.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 212 "quack.y" /* yacc.c:1646  */
    { cout << "statement return empty" << endl; (yyval.statement_type) = new return_node(); }
#line 1517 "quack.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 216 "quack.y" /* yacc.c:1646  */
    { cout << "got methods" << endl; (yyval.methods_type) = (yyvsp[-1].methods_type); (yyvsp[-1].methods_type)->push_back((yyvsp[0].method_type)); }
#line 1523 "quack.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 217 "quack.y" /* yacc.c:1646  */
    { cout << "done with methods" << endl; (yyval.methods_type) = new list<method_node *>(); }
#line 1529 "quack.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 221 "quack.y" /* yacc.c:1646  */
    {cout << "got method:: " << (yyvsp[-5].sval) << endl; (yyval.method_type) = new method_node((yyvsp[-5].sval), (yyvsp[-1].opt_ident_type), (yyvsp[-3].formal_args_type), (yyvsp[0].statements_type)); }
#line 1535 "quack.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 225 "quack.y" /* yacc.c:1646  */
    {cout << "got optional identifier:: " << (yyvsp[0].sval) << endl; (yyval.opt_ident_type) = (yyvsp[0].sval); }
#line 1541 "quack.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 226 "quack.y" /* yacc.c:1646  */
    { (yyval.opt_ident_type) = (char *) "Obj"; }
#line 1547 "quack.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 230 "quack.y" /* yacc.c:1646  */
    {cout << "got statement block" << endl; (yyval.statements_type) = (yyvsp[-1].statements_type); }
#line 1553 "quack.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 234 "quack.y" /* yacc.c:1646  */
    { cout << "got an elif rule" << endl; (yyval.conditionals_type) = (yyvsp[-1].conditionals_type); (yyvsp[-1].conditionals_type)->push_back((yyvsp[0].conditional_type)); }
#line 1559 "quack.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 235 "quack.y" /* yacc.c:1646  */
    { cout << "done with elifs" << endl; (yyval.conditionals_type) = new list<condition_node *>(); }
#line 1565 "quack.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 239 "quack.y" /* yacc.c:1646  */
    { cout << "got an elif" << endl; (yyval.conditional_type) = new condition_node((yyvsp[-1].expr_type), (yyvsp[0].statements_type)); }
#line 1571 "quack.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 243 "quack.y" /* yacc.c:1646  */
    { cout << "got an else rule" << endl; (yyval.statements_type) = (yyvsp[0].statements_type); }
#line 1577 "quack.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 244 "quack.y" /* yacc.c:1646  */
    { (yyval.statements_type) = (yyval.statements_type) = new list<statement_node *>(); }
#line 1583 "quack.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 248 "quack.y" /* yacc.c:1646  */
    { cout << "got an else" << endl; (yyval.statements_type) = (yyvsp[0].statements_type); }
#line 1589 "quack.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 252 "quack.y" /* yacc.c:1646  */
    { cout << "got left expression ident:: " << (yyvsp[0].sval) << endl; (yyval.expr_type) = new ident_node((yyvsp[0].sval)); }
#line 1595 "quack.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 256 "quack.y" /* yacc.c:1646  */
    { cout << "got left expression r_expr.ident:: " << (yyvsp[0].sval) << endl; (yyval.expr_type) = new access_node((yyvsp[-2].expr_type), (yyvsp[0].sval)); }
#line 1601 "quack.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 260 "quack.y" /* yacc.c:1646  */
    { cout << "right expression string lit:: " << (yyvsp[0].sval) << endl; (yyval.expr_type) = new strlit_node((yyvsp[0].sval)); }
#line 1607 "quack.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 264 "quack.y" /* yacc.c:1646  */
    { cout << "right expression int lit:: " << (yyvsp[0].ival) << endl; (yyval.expr_type) = new intlit_node((yyvsp[0].ival)); }
#line 1613 "quack.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 268 "quack.y" /* yacc.c:1646  */
    { cout << "right expression l_expr" << endl; (yyval.expr_type) = (yyvsp[0].expr_type); }
#line 1619 "quack.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 272 "quack.y" /* yacc.c:1646  */
    { cout << "right expression r_expr + r_expr" << endl; (yyval.expr_type) = new method_call_node((yyvsp[-2].expr_type), "PLUS", (yyvsp[0].expr_type)); }
#line 1625 "quack.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 276 "quack.y" /* yacc.c:1646  */
    { cout << "right expression r_expr - r_expr" << endl; (yyval.expr_type) = new method_call_node((yyvsp[-2].expr_type), "MINUS", (yyvsp[0].expr_type)); }
#line 1631 "quack.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 280 "quack.y" /* yacc.c:1646  */
    { cout << "right expression r_expr * r_expr" << endl; (yyval.expr_type) = new method_call_node((yyvsp[-2].expr_type), "TIMES", (yyvsp[0].expr_type)); }
#line 1637 "quack.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 284 "quack.y" /* yacc.c:1646  */
    { cout << "right expression r_expr / r_expr" << endl; (yyval.expr_type) = new method_call_node((yyvsp[-2].expr_type), "DIVIDE", (yyvsp[0].expr_type)); }
#line 1643 "quack.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 288 "quack.y" /* yacc.c:1646  */
    { cout << "right expression (r_expr)" << endl; (yyval.expr_type) = (yyvsp[-1].expr_type); }
#line 1649 "quack.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 292 "quack.y" /* yacc.c:1646  */
    { cout << "right expression r_expr == r_expr" << endl; (yyval.expr_type) = new method_call_node((yyvsp[-2].expr_type), "EQUALS", (yyvsp[0].expr_type)); }
#line 1655 "quack.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 296 "quack.y" /* yacc.c:1646  */
    { cout << "right expression r_expr <= r_expr" << endl; (yyval.expr_type) = new method_call_node((yyvsp[-2].expr_type), "ATMOST", (yyvsp[0].expr_type)); }
#line 1661 "quack.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 300 "quack.y" /* yacc.c:1646  */
    { cout << "right expression r_expr < r_expr" << endl; (yyval.expr_type) = new method_call_node((yyvsp[-2].expr_type), "LESS", (yyvsp[0].expr_type)); }
#line 1667 "quack.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 304 "quack.y" /* yacc.c:1646  */
    { cout << "right expression r_expr >= r_expr" << endl; (yyval.expr_type) = new method_call_node((yyvsp[-2].expr_type), "ATLEAST", (yyvsp[0].expr_type)); }
#line 1673 "quack.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 308 "quack.y" /* yacc.c:1646  */
    { cout << "right expression r_expr > r_expr" << endl; (yyval.expr_type) = new method_call_node((yyvsp[-2].expr_type), "MORE", (yyvsp[0].expr_type)); }
#line 1679 "quack.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 312 "quack.y" /* yacc.c:1646  */
    { cout << "right expression r_expr and r_expr" << endl; (yyval.expr_type) = new and_node((yyvsp[-2].expr_type), (yyvsp[0].expr_type)); }
#line 1685 "quack.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 316 "quack.y" /* yacc.c:1646  */
    { cout << "right expression r_expr or r_expr" << endl; (yyval.expr_type) = new or_node((yyvsp[-2].expr_type), (yyvsp[0].expr_type)); }
#line 1691 "quack.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 320 "quack.y" /* yacc.c:1646  */
    { cout << "right expression not r_expr" << endl; (yyval.expr_type) = new not_node((yyvsp[0].expr_type)); }
#line 1697 "quack.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 324 "quack.y" /* yacc.c:1646  */
    { cout << "right expression method call" << endl; (yyval.expr_type) = new method_call_node((yyvsp[-5].expr_type), (yyvsp[-3].sval), (yyvsp[-1].actual_args_type)); }
#line 1703 "quack.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 328 "quack.y" /* yacc.c:1646  */
    { cout << "right expression class instance" << endl; (yyval.expr_type) = new class_instantiation_node((yyvsp[-3].sval), (yyvsp[-1].actual_args_type)); }
#line 1709 "quack.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 332 "quack.y" /* yacc.c:1646  */
    { cout << "got actual args" << endl; (yyval.actual_args_type) = (yyvsp[0].actual_args_type); }
#line 1715 "quack.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 333 "quack.y" /* yacc.c:1646  */
    { (yyval.actual_args_type) = new list<actual_arg_node *>(); }
#line 1721 "quack.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 337 "quack.y" /* yacc.c:1646  */
    { cout << "got actual arg" << endl; (yyvsp[0].actual_args_type)->push_front( new actual_arg_node((yyvsp[-1].expr_type)) ); (yyval.actual_args_type) = (yyvsp[0].actual_args_type); }
#line 1727 "quack.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 341 "quack.y" /* yacc.c:1646  */
    { cout << "got actual arg repetitions" << endl; (yyval.actual_args_type) = (yyvsp[-1].actual_args_type); (yyvsp[-1].actual_args_type)->push_back((yyvsp[0].actual_arg_type)); }
#line 1733 "quack.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 342 "quack.y" /* yacc.c:1646  */
    { cout << "done with actual arg repetitions" << endl; (yyval.actual_args_type) = new list<actual_arg_node *>(); }
#line 1739 "quack.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 346 "quack.y" /* yacc.c:1646  */
    { cout << "got actual arg repetition" << endl; (yyval.actual_arg_type) = new actual_arg_node((yyvsp[0].expr_type)); }
#line 1745 "quack.tab.c" /* yacc.c:1646  */
    break;


#line 1749 "quack.tab.c" /* yacc.c:1646  */
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
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

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

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
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
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
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
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 350 "quack.y" /* yacc.c:1906  */



// pre-order traversal calling generic node methods
void recursive_crawl(node *n){
	n->speak();
	list<node *> children = n->get_children();

	for(list<node *>::iterator itr = children.begin(); itr != children.end(); ++itr){
		recursive_crawl(*itr);
	}

	return;
}

// crawl the AST
void crawl_ast(pgm_node *r){
	recursive_crawl((node*) r);
}


int main(int argc, char **argv) {

	// see if there is a file, otherwise take input from stdin
	FILE *infile;
	INFILE_NAME = (char *) "stdin";
    if (argc > 1) {
    	if( !(infile = fopen(argv[1], "r"))){
  			perror(argv[1]);
  			exit(1);
        }
		INFILE_NAME = argv[1];
        yyin = infile;
    }

	// parse through the input until there is no more:
	do {
		yyparse();
	} while (!feof(yyin));

	// if we made it here, everything is OK
	cout << "Finished parse with no errors" << endl;

	// crawl the AST
	cout << endl;
	crawl_ast(root);
	cout << endl;

}

/*
void yyerror(const char *s) {
	cout << "parse error on line " << yylineno << endl;
	cout << "message: " <<  s << endl;
	cout << "stopping!" << endl;
	exit(1);
}
*/
