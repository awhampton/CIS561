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
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <list>
#include <map>
#include <set>
#include <iterator>
#include <algorithm>
#include <vector>
#include "quack.h"
using namespace std;

// the root of the abstract syntax tree
pgm_node *root = NULL;

// helpful globals for class structure errors
string CLASS_CYCLE_SUPERCLASS;
string CLASS_CYCLE_SUBCLASS;
string MULTIPLE_SUBCLASS;
set<string> BUILTIN_CLASSES;
set<string> CLASSES_FOUND;
set<string> CONSTRUCTOR_CALLS;

// globals for type checking
typedef vector< pair< string, list<string> > > VTable;
map<string, VTable> VTABLE_MAP;
map<string, map<string, string> > RT_MAP;

// stuff from flex that bison needs to know about:
extern "C" int yylex();
extern "C" int yyparse();
extern "C" FILE *yyin;
extern int yylineno;
extern int num_errors;

extern void yyerror(const char *s);
char* INFILE_NAME;

#line 108 "quack.tab.c" /* yacc.c:339  */

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
    STRING_LIT = 289,
    NEG = 290
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 57 "quack.y" /* yacc.c:355  */

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

#line 207 "quack.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_QUACK_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 224 "quack.tab.c" /* yacc.c:358  */

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
#define YYLAST   274

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  37
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  28
/* YYNRULES -- Number of rules.  */
#define YYNRULES  65
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  122

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   290

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      36,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
      35
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   154,   154,   158,   159,   163,   167,   168,   172,   176,
     180,   181,   185,   189,   190,   191,   195,   199,   203,   204,
     205,   209,   213,   217,   221,   225,   229,   233,   234,   238,
     242,   243,   247,   251,   252,   256,   260,   261,   265,   269,
     273,   277,   281,   285,   289,   293,   297,   301,   305,   309,
     313,   317,   321,   325,   329,   333,   337,   341,   345,   349,
     353,   354,   358,   362,   363,   367
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
  "DIVIDE", "IDENT", "INT_LIT", "STRING_LIT", "NEG", "'\\n'", "$accept",
  "program", "classes", "class", "class_signature", "class_sig_extends",
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
     285,   286,   287,   288,   289,   290,    10
};
# endif

#define YYPACT_NINF -32

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-32)))

#define YYTABLE_NINF -32

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -32,    14,    19,   -32,   -15,   -32,     5,   -32,   -32,    40,
      16,   -32,   -32,     8,    84,    84,   240,    84,    84,    84,
      28,   -32,   -32,   -32,    20,   114,    23,    61,   -32,   -32,
     135,   135,   -32,   156,   226,   177,    24,    84,    25,    27,
      84,    84,    84,    84,    84,    84,    84,   -32,    29,    84,
      84,    84,    84,    33,    43,   -32,    12,   -32,   -32,   -32,
     -32,   -32,   219,    46,   -32,   -32,    84,   -18,   -18,   -18,
     -18,   -18,   226,   226,    41,   -12,   -12,    24,    24,    36,
      72,    52,   -32,   -32,    90,    13,    59,   -32,   198,    84,
     -32,    55,    70,   -32,    84,    57,   -32,   -32,   -32,    84,
     -32,   -32,    77,    22,   -32,    23,   135,   -32,   219,   -32,
      66,    69,   -32,    78,   -32,   -32,    81,    82,    74,    57,
     -32,   -32
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       4,     0,    20,     1,     0,     3,     0,     6,     7,     0,
       0,    20,     5,     0,     0,     0,     0,     0,     0,     0,
      39,    42,    41,    18,    43,     0,    11,     0,    19,    43,
       0,     0,    26,     0,    57,     0,    46,    61,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    24,     0,     0,
       0,     0,     0,     0,     0,    10,     0,    20,    34,    22,
      25,    49,    64,     0,    60,    30,     0,    52,    54,    53,
      51,    50,    55,    56,    40,    44,    45,    47,    48,     0,
       9,     0,    17,    27,     0,    37,    62,    59,     0,    61,
      15,     0,     0,    32,     0,     0,    33,    21,    36,     0,
      63,    23,     0,     0,     8,    11,     0,    38,    65,    58,
       0,     0,    13,     0,    35,    14,     0,    31,     0,     0,
      16,    29
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -32,   -32,   -32,   -32,   -32,   -32,   -32,     2,   -32,   -32,
     -32,   -32,    -3,   -32,   -32,   -32,    -7,   -31,   -32,   -32,
     -32,   -32,    -2,   -13,    26,   -32,   -32,   -32
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     1,     2,     5,     6,     7,     8,    54,    55,   103,
     112,    12,     9,    23,    56,    83,    39,    58,    85,    96,
      97,    98,    29,    25,    63,    64,    86,   100
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      59,    30,    31,    33,    34,    35,    36,    24,    27,    48,
      49,    50,    51,    52,     3,    48,    81,    10,    51,    52,
      94,    95,     4,   110,    62,    24,    11,    67,    68,    69,
      70,    71,    72,    73,    82,    26,    75,    76,    77,    78,
      -2,    13,   -12,    38,    28,   -31,    14,    37,   111,    15,
      16,    48,    66,    88,    84,    53,    79,    65,    17,    18,
      89,    74,    13,    80,   107,   -28,    87,    14,    90,    19,
      15,    16,    20,    21,    22,   114,    62,    91,    57,    17,
      18,   106,    24,   -28,    92,    99,   108,   104,   121,   105,
      19,    13,   115,    20,    21,    22,    14,   109,   117,    15,
      16,   116,    17,    18,   118,    38,   120,   113,    17,    18,
     119,     0,    93,    19,     0,   102,    20,    21,    22,    19,
       0,     0,    20,    21,    22,    40,    41,    42,    43,    44,
      45,    46,     0,     0,     0,     0,     0,     0,    47,     0,
       0,    48,    49,    50,    51,    52,    40,    41,    42,    43,
      44,    45,    46,     0,     0,     0,    57,     0,     0,     0,
       0,     0,    48,    49,    50,    51,    52,    40,    41,    42,
      43,    44,    45,    46,     0,     0,     0,     0,     0,     0,
      60,     0,     0,    48,    49,    50,    51,    52,    40,    41,
      42,    43,    44,    45,    46,     0,     0,    61,     0,     0,
       0,     0,     0,     0,    48,    49,    50,    51,    52,    40,
      41,    42,    43,    44,    45,    46,     0,     0,     0,     0,
       0,     0,   101,     0,     0,    48,    49,    50,    51,    52,
      40,    41,    42,    43,    44,    45,    46,    40,    41,    42,
      43,    44,     0,     0,     0,     0,    48,    49,    50,    51,
      52,     0,     0,    48,    49,    50,    51,    52,    17,    18,
       0,     0,     0,     0,    32,     0,     0,     0,     0,    19,
       0,     0,    20,    21,    22
};

static const yytype_int8 yycheck[] =
{
      31,    14,    15,    16,    17,    18,    19,     9,    11,    27,
      28,    29,    30,    31,     0,    27,     4,    32,    30,    31,
       7,     8,     3,     1,    37,    27,    21,    40,    41,    42,
      43,    44,    45,    46,    22,    19,    49,    50,    51,    52,
       0,     1,    20,    23,    36,    25,     6,    19,    26,     9,
      10,    27,    25,    66,    57,    32,    23,    32,    18,    19,
      19,    32,     1,    20,    95,     4,    20,     6,    32,    29,
       9,    10,    32,    33,    34,   106,    89,     5,    21,    18,
      19,    94,    84,    22,    32,    26,    99,    32,   119,    19,
      29,     1,    26,    32,    33,    34,     6,    20,    20,     9,
      10,    32,    18,    19,    23,    23,    32,   105,    18,    19,
     117,    -1,    22,    29,    -1,    89,    32,    33,    34,    29,
      -1,    -1,    32,    33,    34,    11,    12,    13,    14,    15,
      16,    17,    -1,    -1,    -1,    -1,    -1,    -1,    24,    -1,
      -1,    27,    28,    29,    30,    31,    11,    12,    13,    14,
      15,    16,    17,    -1,    -1,    -1,    21,    -1,    -1,    -1,
      -1,    -1,    27,    28,    29,    30,    31,    11,    12,    13,
      14,    15,    16,    17,    -1,    -1,    -1,    -1,    -1,    -1,
      24,    -1,    -1,    27,    28,    29,    30,    31,    11,    12,
      13,    14,    15,    16,    17,    -1,    -1,    20,    -1,    -1,
      -1,    -1,    -1,    -1,    27,    28,    29,    30,    31,    11,
      12,    13,    14,    15,    16,    17,    -1,    -1,    -1,    -1,
      -1,    -1,    24,    -1,    -1,    27,    28,    29,    30,    31,
      11,    12,    13,    14,    15,    16,    17,    11,    12,    13,
      14,    15,    -1,    -1,    -1,    -1,    27,    28,    29,    30,
      31,    -1,    -1,    27,    28,    29,    30,    31,    18,    19,
      -1,    -1,    -1,    -1,    24,    -1,    -1,    -1,    -1,    29,
      -1,    -1,    32,    33,    34
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    38,    39,     0,     3,    40,    41,    42,    43,    49,
      32,    21,    48,     1,     6,     9,    10,    18,    19,    29,
      32,    33,    34,    50,    59,    60,    19,    49,    36,    59,
      60,    60,    24,    60,    60,    60,    60,    19,    23,    53,
      11,    12,    13,    14,    15,    16,    17,    24,    27,    28,
      29,    30,    31,    32,    44,    45,    51,    21,    54,    54,
      24,    20,    60,    61,    62,    32,    25,    60,    60,    60,
      60,    60,    60,    60,    32,    60,    60,    60,    60,    23,
      20,     4,    22,    52,    49,    55,    63,    20,    60,    19,
      32,     5,    32,    22,     7,     8,    56,    57,    58,    26,
      64,    24,    61,    46,    32,    19,    60,    54,    60,    20,
       1,    26,    47,    44,    54,    26,    32,    20,    23,    53,
      32,    54
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    37,    38,    39,    39,    40,    41,    41,    42,    43,
      44,    44,    45,    46,    46,    46,    47,    48,    49,    49,
      49,    50,    50,    50,    50,    50,    50,    51,    51,    52,
      53,    53,    54,    55,    55,    56,    57,    57,    58,    59,
      59,    60,    60,    60,    60,    60,    60,    60,    60,    60,
      60,    60,    60,    60,    60,    60,    60,    60,    60,    60,
      61,    61,    62,    63,    63,    64
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     2,     0,     2,     1,     1,     7,     5,
       1,     0,     4,     2,     3,     0,     4,     4,     2,     3,
       0,     5,     3,     5,     2,     3,     2,     2,     0,     7,
       2,     0,     3,     2,     0,     3,     1,     0,     2,     1,
       3,     1,     1,     1,     3,     3,     2,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     2,     6,     4,
       1,     0,     2,     2,     0,     2
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
#line 154 "quack.y" /* yacc.c:1646  */
    { (yyval.prog_type) = new pgm_node((yyvsp[-1].classes_type), (yyvsp[0].statements_type)); root = (yyval.prog_type); }
#line 1418 "quack.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 158 "quack.y" /* yacc.c:1646  */
    { (yyval.classes_type) = (yyvsp[-1].classes_type); (yyvsp[-1].classes_type)->push_back((yyvsp[0].class_type)); }
#line 1424 "quack.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 159 "quack.y" /* yacc.c:1646  */
    { (yyval.classes_type) = new list<class_node *>(); }
#line 1430 "quack.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 163 "quack.y" /* yacc.c:1646  */
    { (yyval.class_type) = new class_node((yyvsp[-1].class_signature_type), (yyvsp[0].class_body_type)); }
#line 1436 "quack.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 167 "quack.y" /* yacc.c:1646  */
    { (yyval.class_signature_type) = (yyvsp[0].class_signature_type); }
#line 1442 "quack.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 168 "quack.y" /* yacc.c:1646  */
    { (yyval.class_signature_type) = (yyvsp[0].class_signature_type); }
#line 1448 "quack.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 172 "quack.y" /* yacc.c:1646  */
    { (yyval.class_signature_type) = new class_signature_node((yyvsp[-5].sval), (yyvsp[0].sval), (yyvsp[-3].formal_args_type)); free((yyvsp[-5].sval)); free((yyvsp[0].sval)); }
#line 1454 "quack.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 176 "quack.y" /* yacc.c:1646  */
    { (yyval.class_signature_type) = new class_signature_node((yyvsp[-3].sval), (yyvsp[-1].formal_args_type)); free((yyvsp[-3].sval)); }
#line 1460 "quack.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 180 "quack.y" /* yacc.c:1646  */
    { (yyval.formal_args_type) = (yyvsp[0].formal_args_type); }
#line 1466 "quack.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 181 "quack.y" /* yacc.c:1646  */
    { (yyval.formal_args_type) = new list<formal_arg_node *>(); }
#line 1472 "quack.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 185 "quack.y" /* yacc.c:1646  */
    { (yyvsp[0].formal_args_type)->push_front( new formal_arg_node((yyvsp[-3].sval), (yyvsp[-1].sval)) ); (yyval.formal_args_type) = (yyvsp[0].formal_args_type); free((yyvsp[-3].sval)); }
#line 1478 "quack.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 189 "quack.y" /* yacc.c:1646  */
    { (yyval.formal_args_type) = (yyvsp[-1].formal_args_type); (yyvsp[-1].formal_args_type)->push_back((yyvsp[0].formal_arg_type)); }
#line 1484 "quack.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 190 "quack.y" /* yacc.c:1646  */
    { }
#line 1490 "quack.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 191 "quack.y" /* yacc.c:1646  */
    { (yyval.formal_args_type) = new list<formal_arg_node *>(); }
#line 1496 "quack.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 195 "quack.y" /* yacc.c:1646  */
    { (yyval.formal_arg_type) = new formal_arg_node((yyvsp[-2].sval), (yyvsp[0].sval)); free((yyvsp[-2].sval)); free((yyvsp[0].sval)); }
#line 1502 "quack.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 199 "quack.y" /* yacc.c:1646  */
    { (yyval.class_body_type) = new class_body_node((yyvsp[-2].statements_type), (yyvsp[-1].methods_type)); }
#line 1508 "quack.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 203 "quack.y" /* yacc.c:1646  */
    { (yyval.statements_type) = (yyvsp[-1].statements_type); (yyvsp[-1].statements_type)->push_back((yyvsp[0].statement_type)); }
#line 1514 "quack.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 204 "quack.y" /* yacc.c:1646  */
    { }
#line 1520 "quack.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 205 "quack.y" /* yacc.c:1646  */
    { (yyval.statements_type) = new list<statement_node *>(); }
#line 1526 "quack.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 209 "quack.y" /* yacc.c:1646  */
    { (yyval.statement_type) = new if_elifs_else_node(new condition_node((yyvsp[-3].expr_type),(yyvsp[-2].statements_type)), (yyvsp[-1].conditionals_type), (yyvsp[0].statements_type)); }
#line 1532 "quack.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 213 "quack.y" /* yacc.c:1646  */
    { (yyval.statement_type) = new while_node(new while_condition_node((yyvsp[-1].expr_type), (yyvsp[0].statements_type))); }
#line 1538 "quack.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 217 "quack.y" /* yacc.c:1646  */
    { (yyval.statement_type) = new assignment_node((yyvsp[-4].expr_type), (yyvsp[-3].opt_ident_type), (yyvsp[-1].expr_type)); }
#line 1544 "quack.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 221 "quack.y" /* yacc.c:1646  */
    { (yyval.statement_type) = new bare_expr_node((yyvsp[-1].expr_type)); }
#line 1550 "quack.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 225 "quack.y" /* yacc.c:1646  */
    { (yyval.statement_type) = new return_node((yyvsp[-1].expr_type)); }
#line 1556 "quack.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 229 "quack.y" /* yacc.c:1646  */
    { (yyval.statement_type) = new return_node(); }
#line 1562 "quack.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 233 "quack.y" /* yacc.c:1646  */
    { (yyval.methods_type) = (yyvsp[-1].methods_type); (yyvsp[-1].methods_type)->push_back((yyvsp[0].method_type)); }
#line 1568 "quack.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 234 "quack.y" /* yacc.c:1646  */
    { (yyval.methods_type) = new list<method_node *>(); }
#line 1574 "quack.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 238 "quack.y" /* yacc.c:1646  */
    { (yyval.method_type) = new method_node((yyvsp[-5].sval), (yyvsp[-1].opt_ident_type), (yyvsp[-3].formal_args_type), (yyvsp[0].statements_type)); free((yyvsp[-5].sval)); }
#line 1580 "quack.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 242 "quack.y" /* yacc.c:1646  */
    { (yyval.opt_ident_type) = (yyvsp[0].sval); }
#line 1586 "quack.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 243 "quack.y" /* yacc.c:1646  */
    { char nothing[8] = "Nothing"; (yyval.opt_ident_type) = nothing; }
#line 1592 "quack.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 247 "quack.y" /* yacc.c:1646  */
    { (yyval.statements_type) = (yyvsp[-1].statements_type); }
#line 1598 "quack.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 251 "quack.y" /* yacc.c:1646  */
    { (yyval.conditionals_type) = (yyvsp[-1].conditionals_type); (yyvsp[-1].conditionals_type)->push_back((yyvsp[0].conditional_type)); }
#line 1604 "quack.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 252 "quack.y" /* yacc.c:1646  */
    { (yyval.conditionals_type) = new list<condition_node *>(); }
#line 1610 "quack.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 256 "quack.y" /* yacc.c:1646  */
    { (yyval.conditional_type) = new condition_node((yyvsp[-1].expr_type), (yyvsp[0].statements_type)); }
#line 1616 "quack.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 260 "quack.y" /* yacc.c:1646  */
    { (yyval.statements_type) = (yyvsp[0].statements_type); }
#line 1622 "quack.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 261 "quack.y" /* yacc.c:1646  */
    { (yyval.statements_type) = (yyval.statements_type) = new list<statement_node *>(); }
#line 1628 "quack.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 265 "quack.y" /* yacc.c:1646  */
    { (yyval.statements_type) = (yyvsp[0].statements_type); }
#line 1634 "quack.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 269 "quack.y" /* yacc.c:1646  */
    { (yyval.expr_type) = new ident_node((yyvsp[0].sval)); free((yyvsp[0].sval)); }
#line 1640 "quack.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 273 "quack.y" /* yacc.c:1646  */
    { (yyval.expr_type) = new access_node((yyvsp[-2].expr_type), (yyvsp[0].sval)); free((yyvsp[0].sval)); }
#line 1646 "quack.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 277 "quack.y" /* yacc.c:1646  */
    { (yyval.expr_type) = new strlit_node((yyvsp[0].sval)); free((yyvsp[0].sval)); }
#line 1652 "quack.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 281 "quack.y" /* yacc.c:1646  */
    { (yyval.expr_type) = new intlit_node((yyvsp[0].ival)); }
#line 1658 "quack.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 285 "quack.y" /* yacc.c:1646  */
    { (yyval.expr_type) = (yyvsp[0].expr_type); }
#line 1664 "quack.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 289 "quack.y" /* yacc.c:1646  */
    { (yyval.expr_type) = new method_call_node((yyvsp[-2].expr_type), "PLUS", (yyvsp[0].expr_type)); }
#line 1670 "quack.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 293 "quack.y" /* yacc.c:1646  */
    { (yyval.expr_type) = new method_call_node((yyvsp[-2].expr_type), "MINUS", (yyvsp[0].expr_type)); }
#line 1676 "quack.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 297 "quack.y" /* yacc.c:1646  */
    { (yyval.expr_type) = new method_call_node(new intlit_node(0), "MINUS", (yyvsp[0].expr_type)); }
#line 1682 "quack.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 301 "quack.y" /* yacc.c:1646  */
    { (yyval.expr_type) = new method_call_node((yyvsp[-2].expr_type), "TIMES", (yyvsp[0].expr_type)); }
#line 1688 "quack.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 305 "quack.y" /* yacc.c:1646  */
    { (yyval.expr_type) = new method_call_node((yyvsp[-2].expr_type), "DIVIDE", (yyvsp[0].expr_type)); }
#line 1694 "quack.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 309 "quack.y" /* yacc.c:1646  */
    { (yyval.expr_type) = (yyvsp[-1].expr_type); }
#line 1700 "quack.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 313 "quack.y" /* yacc.c:1646  */
    { (yyval.expr_type) = new method_call_node((yyvsp[-2].expr_type), "EQUALS", (yyvsp[0].expr_type)); }
#line 1706 "quack.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 317 "quack.y" /* yacc.c:1646  */
    { (yyval.expr_type) = new method_call_node((yyvsp[-2].expr_type), "ATMOST", (yyvsp[0].expr_type)); }
#line 1712 "quack.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 321 "quack.y" /* yacc.c:1646  */
    { (yyval.expr_type) = new method_call_node((yyvsp[-2].expr_type), "LESS", (yyvsp[0].expr_type)); }
#line 1718 "quack.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 325 "quack.y" /* yacc.c:1646  */
    { (yyval.expr_type) = new method_call_node((yyvsp[-2].expr_type), "ATLEAST", (yyvsp[0].expr_type)); }
#line 1724 "quack.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 329 "quack.y" /* yacc.c:1646  */
    { (yyval.expr_type) = new method_call_node((yyvsp[-2].expr_type), "MORE", (yyvsp[0].expr_type)); }
#line 1730 "quack.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 333 "quack.y" /* yacc.c:1646  */
    { (yyval.expr_type) = new and_node((yyvsp[-2].expr_type), (yyvsp[0].expr_type)); }
#line 1736 "quack.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 337 "quack.y" /* yacc.c:1646  */
    { (yyval.expr_type) = new or_node((yyvsp[-2].expr_type), (yyvsp[0].expr_type)); }
#line 1742 "quack.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 341 "quack.y" /* yacc.c:1646  */
    { (yyval.expr_type) = new not_node((yyvsp[0].expr_type)); }
#line 1748 "quack.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 345 "quack.y" /* yacc.c:1646  */
    { (yyval.expr_type) = new method_call_node((yyvsp[-5].expr_type), (yyvsp[-3].sval), (yyvsp[-1].actual_args_type)); free((yyvsp[-3].sval)); }
#line 1754 "quack.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 349 "quack.y" /* yacc.c:1646  */
    { (yyval.expr_type) = new class_instantiation_node((yyvsp[-3].sval), (yyvsp[-1].actual_args_type)); free((yyvsp[-3].sval)); }
#line 1760 "quack.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 353 "quack.y" /* yacc.c:1646  */
    { (yyval.actual_args_type) = (yyvsp[0].actual_args_type); }
#line 1766 "quack.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 354 "quack.y" /* yacc.c:1646  */
    { (yyval.actual_args_type) = new list<actual_arg_node *>(); }
#line 1772 "quack.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 358 "quack.y" /* yacc.c:1646  */
    { (yyvsp[0].actual_args_type)->push_front( new actual_arg_node((yyvsp[-1].expr_type)) ); (yyval.actual_args_type) = (yyvsp[0].actual_args_type); }
#line 1778 "quack.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 362 "quack.y" /* yacc.c:1646  */
    { (yyval.actual_args_type) = (yyvsp[-1].actual_args_type); (yyvsp[-1].actual_args_type)->push_back((yyvsp[0].actual_arg_type)); }
#line 1784 "quack.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 363 "quack.y" /* yacc.c:1646  */
    { (yyval.actual_args_type) = new list<actual_arg_node *>(); }
#line 1790 "quack.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 367 "quack.y" /* yacc.c:1646  */
    { (yyval.actual_arg_type) = new actual_arg_node((yyvsp[0].expr_type)); }
#line 1796 "quack.tab.c" /* yacc.c:1646  */
    break;


#line 1800 "quack.tab.c" /* yacc.c:1646  */
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
#line 371 "quack.y" /* yacc.c:1906  */


// LCA functions

// builds a path of inheritance from r to t
//   returns true on success, else false
bool make_path(string r, string t, vector<string> &path, map< string, list<string> > cg){

	// put r on the path
	path.push_back(r);

	// check if we're done
	if(r == t){
		return true;
	}

	// try to find r in the class graph
	map< string, list<string> >::iterator itr_f = cg.find(r);
	if(itr_f == cg.end()){
		path.pop_back();
		return false;
	}

	// search down the graph
	bool found_it = false;
	for(list<string>::iterator itr = cg[r].begin(); itr != cg[r].end(); ++itr){
		found_it = make_path(*itr, t, path, cg) || found_it;
	}

	if(found_it){
		return true;
	}

	// didn't find it
	path.pop_back();
	return false;

}

string find_lca(string s1, string s2, map< string, list<string> > cg){

	// find paths from Obj to s1 and s2
	vector<string> path1, path2;
	bool res1 = make_path("Obj", s1, path1, cg);
	bool res2 = make_path("Obj", s2, path2, cg);

	// cout << endl;
	// cout << "here is path1: " << endl;
	// for(int i=0; i < path1.size(); i++){
	// 	cout << path1[i] << endl;
	// }
	//
	// cout << endl;
	// cout << "here is path2: " << endl;
	// for(int i=0; i < path2.size(); i++){
	// 	cout << path2[i] << endl;
	// }

	if( !res1 ){
		return "ERROR! s1 not in class graph";
	}
	if( !res2 ){
		return "ERROR! s2 not in class graph";
	}

	// the lca is where the paths differ
	int idx;
	for(idx = 0; idx < path1.size() && idx < path2.size(); idx++){
		if(path1[idx] != path2[idx]){
			break;
		}
	}

	return path1[idx-1];
}


// build the map from class name to vtable
// result goes into global variable VTABLE_MAP
VTable build_vtable(string c, VTable parent_vt){
	VTable res = parent_vt;
	int table_size = res.size();
	list<class_node *> classes = *(root->classes);
	for(list<class_node *>::iterator itr = classes.begin(); itr != classes.end(); ++itr){
		string class_name = (*itr)->signature->class_name;
		if(class_name == c){
			for(list<method_node *>::iterator itr2 = ((*itr)->body->mthds)->begin(); itr2 != ((*itr)->body->mthds)->end(); ++itr2){
				list<string> arg_types;
				for(list<formal_arg_node *>::iterator itr3 = ((*itr2)->args)->begin(); itr3 != ((*itr2)->args)->end(); ++itr3){
					arg_types.push_back((*itr3)->value);
				}
				string method_name = (*itr2)->name;
				bool inserted = false;
				for(int i=0; i < table_size; i++){
					if(method_name == res[i].first){
						res[i] = make_pair(method_name, arg_types);
						inserted = true;
						break;
					}
				}
				if(!inserted){
					res.push_back(make_pair(method_name, arg_types));
				}
				RT_MAP[class_name][method_name] = (*itr2)->return_type;
			}
		}
	}
	return res;
}

void build_vtable_map_recursive(map<string, list<string> > cg, string r, VTable parent_vt, string parent){
	RT_MAP[r] = RT_MAP[parent];
	VTable r_vtable = build_vtable(r, parent_vt);
	VTABLE_MAP[r] = r_vtable;
	for(list<string>::iterator itr = cg[r].begin(); itr != cg[r].end(); ++itr){
		build_vtable_map_recursive(cg, *itr, r_vtable, r);
	}
	return;
}

void build_vtable_map(map<string, list<string> > cg){
	VTable obj_vtable;
	list<string> obj_equals_types;
	obj_equals_types.push_back("Obj");
	// obj_equals_types.push_back("Obj");  /* I think the first argument type is implied */
	list<string> obj_print_types;
	// obj_print_types.push_back("Obj");  /* I think the first argument type is implied */
	obj_vtable.push_back(make_pair("EQUALS", obj_equals_types));
	obj_vtable.push_back(make_pair("PRINT", obj_print_types));
	VTABLE_MAP["Obj"] = obj_vtable;
	RT_MAP["Obj"]["EQUALS"] = "Boolean";
	RT_MAP["Obj"]["PRINT"] = "Nothing";
	for(list<string>::iterator itr = cg["Obj"].begin(); itr != cg["Obj"].end(); ++itr){
		build_vtable_map_recursive(cg, *itr, obj_vtable, "Obj");
	}
	return;
}

void print_vtable(string c){
	VTable vt = VTABLE_MAP[c];
	for(vector< pair< string, list<string> > >::iterator itr = vt.begin(); itr != vt.end(); ++itr){
		cout << "  " << itr->first << ": ";
		for(list<string>::iterator itr2 = (itr->second).begin(); itr2 != (itr->second).end(); ++itr2){
			cout << *itr2 << "  ";
		}
		cout << endl;
	}
}


// check VTABLE_MAP
void check_vtable_map(void){
	cout << endl;
	cout << "CHECKING VTABLE MAP!" << endl;
	for(set<string>::iterator itr = CLASSES_FOUND.begin(); itr != CLASSES_FOUND.end(); ++itr){
		cout << *itr << ": " << endl;
		print_vtable(*itr);
	}
}

// check RT_MAP
void check_rt_map(void){
	cout << endl;
	cout << "CHECKING RETURN TYPE MAP!" << endl;
	for(set<string>::iterator itr = CLASSES_FOUND.begin(); itr != CLASSES_FOUND.end(); ++itr){
		map<string, string> rtm = RT_MAP[*itr];
		cout << *itr << ":" << endl;
		for(map<string, string>::iterator itr2 = rtm.begin(); itr2 != rtm.end(); ++itr2){
			cout << "  " << (*itr2).first << ": " << (*itr2).second << endl;
		}
	}
}




// build the class hierarchy tree (represented as an adjacency list)
//   note: we imagine the class hierarchy as a directed tree rooted at "Obj", with
//         edges pointing from the superclass to the sublcass
map<string, list<string> > build_class_graph(pgm_node *r){
	list<class_node *> classes = *(r->classes);
	map<string, list<string> > res;
	for(set<string>::iterator itr = BUILTIN_CLASSES.begin(); itr != BUILTIN_CLASSES.end(); ++itr){
		if(*itr != "Obj"){
			res["Obj"].push_back(*itr);
		}
	}
	for(list<class_node *>::iterator itr = classes.begin(); itr != classes.end(); ++itr){
		string class_name = (*itr)->signature->class_name;
		string class_extends = (*itr)->signature->class_extends;
		res[class_extends].push_back(class_name);
	}
	return res;
}


// get a set containing all the class names
set<string> get_class_names(pgm_node *r){
	list<class_node *> classes = *(r->classes);
	set<string> res;
	for(list<class_node *>::iterator itr = classes.begin(); itr != classes.end(); ++itr){
		string class_name = (*itr)->signature->class_name;
		res.insert(class_name);
	}
	return res;
}


// get a set containing all the class extends
set<string> get_class_extends(pgm_node *r){
	list<class_node *> classes = *(r->classes);
	set<string> res;
	for(list<class_node *>::iterator itr = classes.begin(); itr != classes.end(); ++itr){
		string class_extends = (*itr)->signature->class_extends;
		res.insert(class_extends);
	}
	return res;
}


// crawl the class graph
void crawl_class_graph(map<string, list<string> > cg, string r){
	cout << r << endl;
	for(list<string>::iterator itr = cg[r].begin(); itr != cg[r].end(); ++itr){
		crawl_class_graph(cg, *itr);
	}
	return;
}


// check that the class graph is a tree with one component
// return: 0 - good; 1 - has cycle; 2 - multiple components; 3 - multiple inheritance
int check_class_graph(map<string, list<string> > cg, string r){
	set<string> closed_set;
	list<string> stack;
	stack.push_back(r);
	while(!stack.empty()){
		string current = stack.back();
		// cout << "current: " << current << endl;
		stack.pop_back();

		if(closed_set.find(current) != closed_set.end()){
			MULTIPLE_SUBCLASS = current;
			return 3;  // class has two superclasses
		}

		for(list<string>::iterator itr = cg[current].begin(); itr != cg[current].end(); ++itr){
			// cout << "  neighbor: " << *itr << endl;

			if(closed_set.find(*itr) == closed_set.end()){
				stack.push_back(*itr);
			}
			else{
				list<string>::iterator f = find(stack.begin(), stack.end(), *itr);
				if(f == stack.end()){
					MULTIPLE_SUBCLASS = *itr;
					return 3;  // class has two superclasses
				}
				else{
					CLASS_CYCLE_SUPERCLASS = current;
					CLASS_CYCLE_SUBCLASS = *itr;
					return 1;  // we have found a cycle
				}
			}
		}
		closed_set.insert(current);
	}

	// set the global containing the classes we found in the search
	CLASSES_FOUND = closed_set;

	if(closed_set.size() < cg.size()){
		return 2;  // the search didn't find all the classes
	}

	// if we made it here, everything looks good!
	return 0;
}


// pre-order traversal calling generic node methods
//   note: this just calls the debug method speak
void recursive_crawl(node *n){
	n->speak();
	list<node *> children = n->get_children();

	for(list<node *>::iterator itr = children.begin(); itr != children.end(); ++itr){
		recursive_crawl(*itr);
	}

	return;
}


// crawl the AST, printing debug statements
void crawl_ast(pgm_node *r){
	recursive_crawl((node*) r);
}


// check for class constructor call
void recursive_crawl_constructors(node *n){
	if( n->type_of_node == "expr" && ((expr_node *) n)->type_of_expression == "class_instantiation"){
		CONSTRUCTOR_CALLS.insert(((class_instantiation_node *) n)->class_name);
	}

	list<node *> children = n->get_children();
	for(list<node *>::iterator itr = children.begin(); itr != children.end(); ++itr){
		recursive_crawl_constructors(*itr);
	}

	return;
}


// crawl the AST, looking for class instantiations
void get_constructor_names(pgm_node *r){
	recursive_crawl_constructors((node*) r);
}


// populate the builtin class set
void populate_builtin_classes(void){
	BUILTIN_CLASSES.insert("Obj");
	BUILTIN_CLASSES.insert("String");
	BUILTIN_CLASSES.insert("Int");
	BUILTIN_CLASSES.insert("Boolean");
	BUILTIN_CLASSES.insert("Nothing");
}


int main(int argc, char **argv) {

	// populate the builtin class set
	populate_builtin_classes();

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

	// if everything is OK continue processing with AST
	if(num_errors == 0){
		cout << "Finished parse with no errors" << endl;

		// make the class hierarchy graph
		map<string, list<string> > class_graph = build_class_graph(root);

		// check that the class graph is a tree with one connected component
		int class_res = check_class_graph(class_graph, "Obj");
		if(class_res == 0){
			cout << "Class structure good" << endl;
		}
		else if(class_res == 1){
			cout << "cycle detected in class structure!" << endl;
			cerr << "  (" << CLASS_CYCLE_SUPERCLASS << " -> " << CLASS_CYCLE_SUBCLASS << " is on the cycle)" << endl;
		}
		else if(class_res == 2){
			set<string> class_extends = get_class_extends(root);
			set<string> missing;
			set_difference(class_extends.begin(), class_extends.end(), CLASSES_FOUND.begin(), CLASSES_FOUND.end(), inserter(missing, missing.end()));
			cout << "class definition missing or unreachable from Obj!" << endl;
			cerr << "the following classes are undefined or unreachable: " << endl;
			for(set<string>::iterator itr = missing.begin(); itr != missing.end(); ++itr){
				cerr << "  " << *itr << endl;
			}
		}
		else if(class_res == 3){
			cout << "multiple inheritance! (or class defined twice?)" << endl;
			cerr << "  (" << MULTIPLE_SUBCLASS << " inherits or is defined twice)" << endl;
		}

		// check that constructor calls are valid
		get_constructor_names(root);  // stored in global CONSTRUCTOR_CALLS

		set<string> missing;
		set_difference(CONSTRUCTOR_CALLS.begin(), CONSTRUCTOR_CALLS.end(), CLASSES_FOUND.begin(), CLASSES_FOUND.end(), inserter(missing, missing.end()));
		if(!missing.empty()){
			cout << "class definition missing!" << endl;
			cerr << "tried to construct the following undefined classes: " << endl;
			for(set<string>::iterator itr = missing.begin(); itr != missing.end(); ++itr){
				cerr << "  " << *itr << endl;
			}
		}
		else{
			cout << "Constructor calls good" << endl;
		}

		// test the lca function
		// crawl_class_graph(class_graph, "Obj");
		// string lca = find_lca("C2", "C4", class_graph);
		// cout << "LCA: " << lca << endl;

		// type checking stuff
		build_vtable_map(class_graph);
		// check_vtable_map();
		// check_rt_map();

		root->type_check();





	}
	// else print the number of errors on stdout
	else{
		cout << "Found " << num_errors << " parse errors!" << endl;
	}

	// delete the root of the AST (which should delete the entire thing)
	if(root != NULL){
		delete root;
	}
}
