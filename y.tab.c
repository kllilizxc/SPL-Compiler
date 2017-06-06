/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     ID = 258,
     SYS_CON = 259,
     SYS_FUNCT = 260,
     SYS_PROC = 261,
     SYS_TYPE = 262,
     STRING = 263,
     INTEGER = 264,
     REAL = 265,
     CHAR = 266,
     COMMA = 267,
     COLON = 268,
     SEMI = 269,
     LP = 270,
     RP = 271,
     LB = 272,
     RB = 273,
     DOT = 274,
     DOTDOT = 275,
     PLUS = 276,
     MINUS = 277,
     MUL = 278,
     DIV = 279,
     MOD = 280,
     EQUEL = 281,
     UNEQUAL = 282,
     LT = 283,
     LE = 284,
     GT = 285,
     GE = 286,
     AND = 287,
     OR = 288,
     NOT = 289,
     ASSIGN = 290,
     ARRAY = 291,
     BEGINN = 292,
     CASE = 293,
     IF = 294,
     THEN = 295,
     ELSE = 296,
     WHILE = 297,
     FOR = 298,
     TO = 299,
     DOWNTO = 300,
     GOTO = 301,
     DO = 302,
     LET = 303,
     IN = 304,
     END = 305,
     OF = 306,
     WITH = 307,
     PACKED = 308,
     PROCEDURE = 309,
     PROGRAM = 310,
     RECORD = 311,
     REPEAT = 312,
     SET = 313,
     UNTIL = 314,
     BREAK = 315,
     FUNCTION = 316,
     VAR = 317,
     TYPE = 318,
     CONST = 319,
     LOWEST = 320,
     EQUAL = 321,
     UMINUS = 322
   };
#endif
/* Tokens.  */
#define ID 258
#define SYS_CON 259
#define SYS_FUNCT 260
#define SYS_PROC 261
#define SYS_TYPE 262
#define STRING 263
#define INTEGER 264
#define REAL 265
#define CHAR 266
#define COMMA 267
#define COLON 268
#define SEMI 269
#define LP 270
#define RP 271
#define LB 272
#define RB 273
#define DOT 274
#define DOTDOT 275
#define PLUS 276
#define MINUS 277
#define MUL 278
#define DIV 279
#define MOD 280
#define EQUEL 281
#define UNEQUAL 282
#define LT 283
#define LE 284
#define GT 285
#define GE 286
#define AND 287
#define OR 288
#define NOT 289
#define ASSIGN 290
#define ARRAY 291
#define BEGINN 292
#define CASE 293
#define IF 294
#define THEN 295
#define ELSE 296
#define WHILE 297
#define FOR 298
#define TO 299
#define DOWNTO 300
#define GOTO 301
#define DO 302
#define LET 303
#define IN 304
#define END 305
#define OF 306
#define WITH 307
#define PACKED 308
#define PROCEDURE 309
#define PROGRAM 310
#define RECORD 311
#define REPEAT 312
#define SET 313
#define UNTIL 314
#define BREAK 315
#define FUNCTION 316
#define VAR 317
#define TYPE 318
#define CONST 319
#define LOWEST 320
#define EQUAL 321
#define UMINUS 322




/* Copy the first part of user declarations.  */
#line 1 "spl.y"

#include <stdio.h>
#include <stdlib.h>
#include "util.h"
#include "symbol.h" 
#include "errormsg.h"
#include "absyn.h"

int yylex(void); /* function prototype */

A_pro absyn_root;

void yyerror(char *s)
{
 EM_error(EM_tokPos, "%s", s);
 exit(1);
}


/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 21 "spl.y"
{
  int pos;
  int ival;
  float fval;
  char cval;
  string sval;
  A_pro pro;
  A_routine routine;
  A_routineHead routineHead;
  A_decPart decPart;
  A_decList decList;
  A_dec dec;
  A_const constt;
  A_name name;
  A_nameList nameList;
  A_field field;
  A_fieldList fieldList;
  A_ty ty;
  A_simpleTy simpleTy;
  A_routineBody routineBody;
  A_stmtList stmtList;
  A_var var;
  A_stmt stmt;
  A_proc proc;
  A_caseList caseList;
  A_case casee;
  A_exp exp;
  A_expList expList;
}
/* Line 193 of yacc.c.  */
#line 279 "y.tab.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 292 "y.tab.c"

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
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
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
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
}
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
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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
  yytype_int16 yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   455

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  68
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  57
/* YYNRULES -- Number of rules.  */
#define YYNRULES  125
/* YYNRULES -- Number of states.  */
#define YYNSTATES  256

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   322

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
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
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     9,    12,    18,    19,    20,    23,    25,
      28,    33,    35,    37,    39,    41,    43,    44,    47,    49,
      52,    57,    59,    61,    63,    65,    67,    71,    75,    80,
      86,    90,    97,   101,   103,   106,   111,   113,   117,   119,
     120,   123,   125,   128,   133,   134,   136,   138,   140,   143,
     146,   155,   162,   163,   167,   169,   173,   177,   181,   184,
     186,   188,   192,   193,   197,   199,   203,   205,   207,   209,
     211,   213,   215,   217,   219,   221,   225,   232,   238,   240,
     245,   247,   252,   257,   264,   269,   274,   283,   292,   298,
     300,   303,   308,   313,   316,   318,   320,   324,   326,   328,
     330,   332,   334,   336,   338,   340,   344,   349,   353,   355,
     359,   363,   367,   371,   375,   378,   382,   386,   390,   394,
     398,   402,   405,   409,   413,   418
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      69,     0,    -1,    55,     3,    14,    70,    19,    -1,    71,
     100,    -1,    72,    73,    77,    88,    91,    -1,    -1,    -1,
      64,    74,    -1,    75,    -1,    75,    74,    -1,     3,    66,
      76,    14,    -1,     9,    -1,    10,    -1,    11,    -1,     8,
      -1,     4,    -1,    -1,    63,    78,    -1,    79,    -1,    79,
      78,    -1,     3,    66,    80,    14,    -1,    81,    -1,    82,
      -1,    83,    -1,     7,    -1,     3,    -1,    15,    86,    16,
      -1,   120,    20,   120,    -1,    22,   120,    20,   120,    -1,
      22,   120,    20,    22,   120,    -1,     3,    20,     3,    -1,
      36,    17,    81,    18,    51,    80,    -1,    56,    84,    50,
      -1,    85,    -1,    85,    84,    -1,    86,    13,    80,    14,
      -1,    87,    -1,    87,    12,    86,    -1,     3,    -1,    -1,
      62,    89,    -1,    90,    -1,    90,    89,    -1,    86,    13,
      80,    14,    -1,    -1,    92,    -1,    93,    -1,    94,    -1,
      93,    92,    -1,    94,    92,    -1,    61,     3,    95,    13,
      81,    14,    70,    14,    -1,    54,     3,    95,    14,    70,
      14,    -1,    -1,    15,    96,    16,    -1,    97,    -1,    97,
      14,    96,    -1,    98,    13,    81,    -1,    99,    13,    81,
      -1,    62,    86,    -1,    86,    -1,   101,    -1,    37,   102,
      50,    -1,    -1,   103,    14,   102,    -1,   104,    -1,     9,
      13,   104,    -1,   105,    -1,   106,    -1,   101,    -1,   107,
      -1,   108,    -1,   109,    -1,   110,    -1,   111,    -1,   114,
      -1,     3,    35,   117,    -1,     3,    17,   117,    18,    35,
     117,    -1,     3,    19,     3,    35,   117,    -1,     3,    -1,
       3,    15,   115,    16,    -1,     6,    -1,     6,    15,   116,
      16,    -1,    39,   117,    40,   103,    -1,    39,   117,    40,
     103,    41,   103,    -1,    57,   102,    59,   117,    -1,    42,
     117,    47,   103,    -1,    43,     3,    35,   117,    44,   117,
      47,   103,    -1,    43,     3,    35,   117,    45,   117,    47,
     103,    -1,    38,   117,    51,   112,    50,    -1,   113,    -1,
     113,   112,    -1,    76,    13,   103,    14,    -1,     3,    13,
     103,    14,    -1,    46,     9,    -1,   116,    -1,   117,    -1,
     117,    12,   116,    -1,   118,    -1,   120,    -1,   121,    -1,
     122,    -1,   123,    -1,   124,    -1,   119,    -1,     3,    -1,
      15,   117,    16,    -1,     3,    17,   117,    18,    -1,     3,
      19,     3,    -1,    76,    -1,   117,    21,   117,    -1,   117,
      22,   117,    -1,   117,    25,   117,    -1,   117,    23,   117,
      -1,   117,    24,   117,    -1,    22,   117,    -1,   117,    66,
     117,    -1,   117,    27,   117,    -1,   117,    30,   117,    -1,
     117,    31,   117,    -1,   117,    29,   117,    -1,   117,    28,
     117,    -1,    34,   117,    -1,   117,    32,   117,    -1,   117,
      33,   117,    -1,     5,    15,   115,    16,    -1,     3,    15,
     115,    16,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   104,   104,   106,   108,   110,   112,   113,   115,   116,
     118,   120,   121,   122,   123,   124,   126,   127,   129,   130,
     132,   134,   135,   136,   138,   139,   140,   141,   142,   143,
     144,   146,   148,   150,   151,   153,   155,   156,   158,   162,
     163,   165,   166,   168,   172,   173,   175,   176,   177,   178,
     180,   183,   186,   187,   189,   190,   192,   193,   195,   197,
     199,   201,   203,   204,   206,   207,   209,   210,   211,   212,
     213,   214,   215,   216,   217,   219,   220,   221,   223,   224,
     225,   226,   228,   229,   231,   233,   235,   236,   238,   240,
     241,   243,   244,   246,   248,   250,   251,   253,   254,   255,
     256,   257,   258,   261,   263,   264,   265,   266,   268,   270,
     271,   272,   273,   274,   275,   278,   279,   280,   281,   282,
     283,   286,   287,   288,   290,   291
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "ID", "SYS_CON", "SYS_FUNCT", "SYS_PROC",
  "SYS_TYPE", "STRING", "INTEGER", "REAL", "CHAR", "COMMA", "COLON",
  "SEMI", "LP", "RP", "LB", "RB", "DOT", "DOTDOT", "PLUS", "MINUS", "MUL",
  "DIV", "MOD", "EQUEL", "UNEQUAL", "LT", "LE", "GT", "GE", "AND", "OR",
  "NOT", "ASSIGN", "ARRAY", "BEGINN", "CASE", "IF", "THEN", "ELSE",
  "WHILE", "FOR", "TO", "DOWNTO", "GOTO", "DO", "LET", "IN", "END", "OF",
  "WITH", "PACKED", "PROCEDURE", "PROGRAM", "RECORD", "REPEAT", "SET",
  "UNTIL", "BREAK", "FUNCTION", "VAR", "TYPE", "CONST", "LOWEST", "EQUAL",
  "UMINUS", "$accept", "program", "routine", "routine_head", "label_part",
  "const_part", "const_expr_list", "const_expr", "const_value",
  "type_part", "type_decl_list", "type_definition", "type_decl",
  "simple_type_decl", "array_type_decl", "record_type_decl",
  "field_decl_list", "field_decl", "name_list", "names", "var_part",
  "var_decl_list", "var_decl", "routine_part", "routine_decl_list",
  "function_decl", "procedure_decl", "parameters", "para_decl_list",
  "para_type_list", "var_para_list", "varE_para_list", "routine_body",
  "compound_stmt", "stmt_list", "stmt", "non_label_stmt", "assign_stmt",
  "proc_stmt", "if_stmt", "repeat_stmt", "while_stmt", "for_stmt",
  "case_stmt", "case_exp_list", "case_exp", "goto_stmt", "args_list",
  "exp_list", "exp", "lvalueExp", "lvalue", "literalExp", "arithmeticExp",
  "comparisonExp", "booleanExp", "funcExp", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    68,    69,    70,    71,    72,    73,    73,    74,    74,
      75,    76,    76,    76,    76,    76,    77,    77,    78,    78,
      79,    80,    80,    80,    81,    81,    81,    81,    81,    81,
      81,    82,    83,    84,    84,    85,    86,    86,    87,    88,
      88,    89,    89,    90,    91,    91,    92,    92,    92,    92,
      93,    94,    95,    95,    96,    96,    97,    97,    98,    99,
     100,   101,   102,   102,   103,   103,   104,   104,   104,   104,
     104,   104,   104,   104,   104,   105,   105,   105,   106,   106,
     106,   106,   107,   107,   108,   109,   110,   110,   111,   112,
     112,   113,   113,   114,   115,   116,   116,   117,   117,   117,
     117,   117,   117,   118,   119,   119,   119,   119,   120,   121,
     121,   121,   121,   121,   121,   122,   122,   122,   122,   122,
     122,   123,   123,   123,   124,   124
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     5,     2,     5,     0,     0,     2,     1,     2,
       4,     1,     1,     1,     1,     1,     0,     2,     1,     2,
       4,     1,     1,     1,     1,     1,     3,     3,     4,     5,
       3,     6,     3,     1,     2,     4,     1,     3,     1,     0,
       2,     1,     2,     4,     0,     1,     1,     1,     2,     2,
       8,     6,     0,     3,     1,     3,     3,     3,     2,     1,
       1,     3,     0,     3,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     3,     6,     5,     1,     4,
       1,     4,     4,     6,     4,     4,     8,     8,     5,     1,
       2,     4,     4,     2,     1,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     3,     4,     3,     1,     3,
       3,     3,     3,     3,     2,     3,     3,     3,     3,     3,
       3,     2,     3,     3,     4,     4
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     1,     5,     0,     0,     6,     2,
      62,     3,    60,     0,    16,    78,    80,     0,     0,     0,
       0,     0,     0,    62,    68,     0,     0,    64,    66,    67,
      69,    70,    71,    72,    73,    74,     0,     7,     8,     0,
      39,     0,     0,     0,     0,     0,     0,   104,    15,     0,
      14,    11,    12,    13,     0,     0,     0,   108,     0,    97,
     103,    98,    99,   100,   101,   102,     0,     0,     0,    93,
       0,    61,    62,     0,     9,     0,    17,    18,     0,    44,
       0,    94,    95,     0,     0,    75,     0,    65,     0,     0,
       0,     0,     0,   114,   121,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    63,     0,     0,    19,    38,     0,    36,
      40,    41,     0,     0,     4,    45,    46,    47,    79,     0,
       0,     0,    81,     0,     0,   107,     0,   105,   109,   110,
     112,   113,   111,   116,   120,   119,   117,   118,   122,   123,
       0,     0,     0,    89,   115,    82,    85,     0,    84,    10,
      25,    24,     0,     0,     0,     0,     0,    21,    22,    23,
       0,     0,     0,    42,    52,    52,    48,    49,    96,     0,
      77,   125,   106,   124,     0,     0,    88,    90,     0,     0,
       0,     0,     0,     0,     0,     0,    33,     0,    20,     0,
       0,    37,     0,     0,     0,    76,     0,     0,    83,     0,
       0,    30,    26,     0,     0,    32,    34,     0,    27,    43,
       0,    59,     0,    54,     0,     0,     5,     0,    92,    91,
       0,     0,     0,    28,     0,     0,    58,    53,     0,     0,
       0,     0,     0,    86,    87,    29,     0,    35,    55,    56,
      57,    51,     5,    31,     0,    50
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     6,     7,     8,    14,    37,    38,    57,    40,
      76,    77,   166,   167,   168,   169,   195,   196,   118,   119,
      79,   120,   121,   124,   125,   126,   127,   203,   222,   223,
     224,   225,    11,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,   152,   153,    35,    80,    81,    82,
      59,    60,    61,    62,    63,    64,    65
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -219
static const yytype_int16 yypact[] =
{
     -44,    20,    30,    21,  -219,  -219,    25,     3,   -16,  -219,
       4,  -219,  -219,    42,    -9,    40,    41,    45,   421,   421,
     421,    66,    61,     4,  -219,    22,    59,  -219,  -219,  -219,
    -219,  -219,  -219,  -219,  -219,  -219,    31,  -219,    42,    73,
      43,   421,   421,   104,   421,   421,   136,    14,  -219,    94,
    -219,  -219,  -219,  -219,   421,   421,   421,  -219,   273,  -219,
    -219,  -219,  -219,  -219,  -219,  -219,   287,   313,    96,  -219,
      74,  -219,     4,   142,  -219,    68,  -219,    73,   129,   -45,
     119,  -219,   135,   207,   103,   374,   125,  -219,   421,   421,
     141,   421,   187,  -219,  -219,   421,   421,   421,   421,   421,
     421,   421,   421,   421,   421,   421,   421,   117,   421,     4,
       4,   421,   421,  -219,   131,   177,  -219,  -219,   156,   143,
    -219,   129,   151,   167,  -219,  -219,   -45,   -45,  -219,   421,
     148,   421,  -219,   160,   227,  -219,   161,  -219,    76,    76,
    -219,  -219,  -219,   388,   388,   388,   388,   388,  -219,    76,
     176,   178,   140,   117,   388,   153,  -219,   247,   374,  -219,
     175,  -219,   129,   142,   179,   129,   183,  -219,  -219,  -219,
     180,   177,   129,  -219,   189,   189,  -219,  -219,  -219,   421,
     374,  -219,  -219,  -219,     4,     4,  -219,  -219,     4,   421,
     421,   195,   186,   185,   108,   157,   129,   193,  -219,   142,
     208,  -219,     0,   209,   211,   374,   212,   213,  -219,   334,
     361,  -219,  -219,    10,   203,  -219,  -219,   177,  -219,  -219,
     129,  -219,   225,   228,   230,   231,  -219,   108,  -219,  -219,
       4,     4,   142,  -219,   196,   232,  -219,  -219,     0,   108,
     108,   248,   249,  -219,  -219,  -219,   177,  -219,  -219,  -219,
    -219,  -219,  -219,  -219,   250,  -219
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -219,  -219,  -218,  -219,  -219,  -219,   223,  -219,   -58,  -219,
     188,  -219,  -154,  -188,  -219,  -219,    70,  -219,   -98,  -219,
    -219,   146,  -219,  -219,   -61,  -219,  -219,   106,    44,  -219,
    -219,  -219,  -219,   276,   -19,   -82,   238,  -219,  -219,  -219,
    -219,  -219,  -219,  -219,   132,  -219,  -219,   -66,   -40,   -18,
    -219,  -219,  -103,  -219,  -219,  -219,  -219
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_int16 yytable[] =
{
      58,    66,    67,   117,    70,    86,   214,    15,   241,   122,
      16,     1,   170,    17,    48,   114,   123,   200,    50,    51,
      52,    53,   133,     3,    83,   136,    85,   155,   156,    88,
       4,    89,   232,    90,   254,     5,    92,    93,    94,   242,
      10,    10,    18,    19,     9,    36,    20,    21,    13,   151,
      22,   249,   250,   113,    39,    41,    45,    42,    46,    43,
     193,    23,   220,   235,   192,   176,   177,   197,   170,    68,
      69,   134,    71,    72,   201,    44,    75,   138,   139,   140,
     141,   142,   143,   144,   145,   146,   147,   148,   149,   178,
     154,   170,   253,   157,   158,   151,   218,    73,   197,    97,
      98,    99,   206,   207,   221,    78,   208,    84,   105,    91,
     233,   160,    48,   180,   170,   161,    50,    51,    52,    53,
     150,    48,   236,   162,   170,    50,    51,    52,    53,   245,
     163,   111,   117,   112,   115,   128,   170,   170,   131,    15,
     221,   132,    16,   170,   135,   159,    48,   129,   243,   244,
      50,    51,    52,    53,   174,   172,    95,    96,    97,    98,
      99,   205,   100,   101,   102,   103,   104,   105,   106,   171,
     175,   209,   210,    10,    18,    19,   181,   183,    20,    21,
     160,    48,    22,   179,   161,    50,    51,    52,    53,   184,
     186,   185,   162,    23,   188,   191,   194,   198,   211,   163,
     199,   108,   212,   137,   202,   213,   217,   215,    95,    96,
      97,    98,    99,   164,   100,   101,   102,   103,   104,   105,
     106,   234,   219,   226,   227,   130,   228,   229,    95,    96,
      97,    98,    99,   165,   100,   101,   102,   103,   104,   105,
     106,   237,   238,   239,   240,   182,   247,   246,    95,    96,
      97,    98,    99,   108,   100,   101,   102,   103,   104,   105,
     106,    74,   251,   252,   255,   116,   216,   173,    95,    96,
      97,    98,    99,   108,   100,   101,   102,   103,   104,   105,
     106,   204,   248,    12,    87,   187,     0,     0,     0,     0,
       0,   189,   190,   108,    95,    96,    97,    98,    99,     0,
     100,   101,   102,   103,   104,   105,   106,     0,    95,    96,
      97,    98,    99,   108,   100,   101,   102,   103,   104,   105,
     106,     0,     0,     0,   107,     0,     0,   109,     0,     0,
       0,     0,     0,     0,    95,    96,    97,    98,    99,   108,
     100,   101,   102,   103,   104,   105,   106,     0,     0,     0,
       0,     0,     0,   108,     0,    95,    96,    97,    98,    99,
     110,   100,   101,   102,   103,   104,   105,   106,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   108,
       0,   230,    95,    96,    97,    98,    99,     0,   100,   101,
     102,   103,   104,   105,   106,    95,    96,    97,    98,    99,
     108,   100,   101,   102,   103,   104,   105,   106,   231,    95,
      96,    97,    98,    99,     0,    -1,    -1,    -1,    -1,    -1,
     105,   106,     0,     0,    47,    48,    49,   108,     0,    50,
      51,    52,    53,     0,     0,     0,    54,     0,     0,     0,
     108,     0,     0,    55,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    -1,    56
};

static const yytype_int16 yycheck[] =
{
      18,    19,    20,     3,    23,    45,   194,     3,   226,    54,
       6,    55,   115,     9,     4,    73,    61,   171,     8,     9,
      10,    11,    88,     3,    42,    91,    44,   109,   110,    15,
       0,    17,    22,    19,   252,    14,    54,    55,    56,   227,
      37,    37,    38,    39,    19,     3,    42,    43,    64,   107,
      46,   239,   240,    72,    63,    15,    15,    17,    13,    19,
     163,    57,    62,   217,   162,   126,   127,   165,   171,     3,
       9,    89,    50,    14,   172,    35,     3,    95,    96,    97,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   129,
     108,   194,   246,   111,   112,   153,   199,    66,   196,    23,
      24,    25,   184,   185,   202,    62,   188,     3,    32,    15,
     213,     3,     4,   131,   217,     7,     8,     9,    10,    11,
       3,     4,   220,    15,   227,     8,     9,    10,    11,   232,
      22,    35,     3,    59,    66,    16,   239,   240,    35,     3,
     238,    16,     6,   246,     3,    14,     4,    12,   230,   231,
       8,     9,    10,    11,     3,    12,    21,    22,    23,    24,
      25,   179,    27,    28,    29,    30,    31,    32,    33,    13,
       3,   189,   190,    37,    38,    39,    16,    16,    42,    43,
       3,     4,    46,    35,     7,     8,     9,    10,    11,    13,
      50,    13,    15,    57,    41,    20,    17,    14,     3,    22,
      20,    66,    16,    16,    15,    20,    13,    50,    21,    22,
      23,    24,    25,    36,    27,    28,    29,    30,    31,    32,
      33,    18,    14,    14,    13,    18,    14,    14,    21,    22,
      23,    24,    25,    56,    27,    28,    29,    30,    31,    32,
      33,    16,    14,    13,    13,    18,    14,    51,    21,    22,
      23,    24,    25,    66,    27,    28,    29,    30,    31,    32,
      33,    38,    14,    14,    14,    77,   196,   121,    21,    22,
      23,    24,    25,    66,    27,    28,    29,    30,    31,    32,
      33,   175,   238,     7,    46,   153,    -1,    -1,    -1,    -1,
      -1,    44,    45,    66,    21,    22,    23,    24,    25,    -1,
      27,    28,    29,    30,    31,    32,    33,    -1,    21,    22,
      23,    24,    25,    66,    27,    28,    29,    30,    31,    32,
      33,    -1,    -1,    -1,    51,    -1,    -1,    40,    -1,    -1,
      -1,    -1,    -1,    -1,    21,    22,    23,    24,    25,    66,
      27,    28,    29,    30,    31,    32,    33,    -1,    -1,    -1,
      -1,    -1,    -1,    66,    -1,    21,    22,    23,    24,    25,
      47,    27,    28,    29,    30,    31,    32,    33,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    66,
      -1,    47,    21,    22,    23,    24,    25,    -1,    27,    28,
      29,    30,    31,    32,    33,    21,    22,    23,    24,    25,
      66,    27,    28,    29,    30,    31,    32,    33,    47,    21,
      22,    23,    24,    25,    -1,    27,    28,    29,    30,    31,
      32,    33,    -1,    -1,     3,     4,     5,    66,    -1,     8,
       9,    10,    11,    -1,    -1,    -1,    15,    -1,    -1,    -1,
      66,    -1,    -1,    22,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    66,    34
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    55,    69,     3,     0,    14,    70,    71,    72,    19,
      37,   100,   101,    64,    73,     3,     6,     9,    38,    39,
      42,    43,    46,    57,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   114,     3,    74,    75,    63,
      77,    15,    17,    19,    35,    15,    13,     3,     4,     5,
       8,     9,    10,    11,    15,    22,    34,    76,   117,   118,
     119,   120,   121,   122,   123,   124,   117,   117,     3,     9,
     102,    50,    14,    66,    74,     3,    78,    79,    62,    88,
     115,   116,   117,   117,     3,   117,   116,   104,    15,    17,
      19,    15,   117,   117,   117,    21,    22,    23,    24,    25,
      27,    28,    29,    30,    31,    32,    33,    51,    66,    40,
      47,    35,    59,   102,    76,    66,    78,     3,    86,    87,
      89,    90,    54,    61,    91,    92,    93,    94,    16,    12,
      18,    35,    16,   115,   117,     3,   115,    16,   117,   117,
     117,   117,   117,   117,   117,   117,   117,   117,   117,   117,
       3,    76,   112,   113,   117,   103,   103,   117,   117,    14,
       3,     7,    15,    22,    36,    56,    80,    81,    82,    83,
     120,    13,    12,    89,     3,     3,    92,    92,   116,    35,
     117,    16,    18,    16,    13,    13,    50,   112,    41,    44,
      45,    20,    86,   120,    17,    84,    85,    86,    14,    20,
      80,    86,    15,    95,    95,   117,   103,   103,   103,   117,
     117,     3,    16,    20,    81,    50,    84,    13,   120,    14,
      62,    86,    96,    97,    98,    99,    14,    13,    14,    14,
      47,    47,    22,   120,    18,    80,    86,    16,    14,    13,
      13,    70,    81,   103,   103,   120,    51,    14,    96,    81,
      81,    14,    14,    80,    70,    14
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      fprintf (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

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
#ifndef	YYINITDEPTH
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
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

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  int yystate;
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;

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
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

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

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
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
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

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
     `$$ = $1'.

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
#line 104 "spl.y"
    {absyn_root = A_Pro(EM_tokPos, S_Symbol((yyvsp[(2) - (5)].sval)), (yyvsp[(4) - (5)].routine));}
    break;

  case 3:
#line 106 "spl.y"
    {(yyval.routine) = A_Routine((yyvsp[(1) - (2)].routineHead), (yyvsp[(2) - (2)].routineBody));}
    break;

  case 4:
#line 108 "spl.y"
    {(yyval.routineHead) = A_RoutineHead((yyvsp[(1) - (5)].decPart), (yyvsp[(2) - (5)].decPart), (yyvsp[(3) - (5)].decPart), (yyvsp[(4) - (5)].decPart), (yyvsp[(5) - (5)].decPart));}
    break;

  case 5:
#line 110 "spl.y"
    {(yyval.decPart) = NULL;}
    break;

  case 6:
#line 112 "spl.y"
    {(yyval.decPart) = NULL;}
    break;

  case 7:
#line 113 "spl.y"
    {(yyval.decPart) = A_DecPart(EM_tokPos, (yyvsp[(2) - (2)].decList));}
    break;

  case 8:
#line 115 "spl.y"
    {(yyval.decList) = A_DecList((yyvsp[(1) - (1)].dec), NULL);}
    break;

  case 9:
#line 116 "spl.y"
    {(yyval.decList) = A_DecList((yyvsp[(1) - (2)].dec), (yyvsp[(2) - (2)].decList));}
    break;

  case 10:
#line 118 "spl.y"
    {(yyval.dec) = A_ConstDec(EM_tokPos, S_Symbol((yyvsp[(1) - (4)].sval)), (yyvsp[(3) - (4)].constt));}
    break;

  case 11:
#line 120 "spl.y"
    {(yyval.constt) = A_Int(EM_tokPos, (yyvsp[(1) - (1)].ival));}
    break;

  case 12:
#line 121 "spl.y"
    {(yyval.constt) = A_Real(EM_tokPos, (yyvsp[(1) - (1)].fval));}
    break;

  case 13:
#line 122 "spl.y"
    {(yyval.constt) = A_Char(EM_tokPos, (yyvsp[(1) - (1)].cval));}
    break;

  case 14:
#line 123 "spl.y"
    {(yyval.constt) = A_String(EM_tokPos, (yyvsp[(1) - (1)].sval));}
    break;

  case 15:
#line 124 "spl.y"
    {(yyval.constt) = A_Syscon(EM_tokPos, S_Symbol((yyvsp[(1) - (1)].sval)));}
    break;

  case 16:
#line 126 "spl.y"
    {(yyval.decPart) = NULL;}
    break;

  case 17:
#line 127 "spl.y"
    {(yyval.decPart) = A_DecPart(EM_tokPos, (yyvsp[(2) - (2)].decList));}
    break;

  case 18:
#line 129 "spl.y"
    {(yyval.decList) = A_DecList((yyvsp[(1) - (1)].dec), NULL);}
    break;

  case 19:
#line 130 "spl.y"
    {(yyval.decList) = A_DecList((yyvsp[(1) - (2)].dec), (yyvsp[(2) - (2)].decList));}
    break;

  case 20:
#line 132 "spl.y"
    {(yyval.dec) = A_TypeDec(EM_tokPos, S_Symbol((yyvsp[(1) - (4)].sval)), (yyvsp[(3) - (4)].ty));}
    break;

  case 21:
#line 134 "spl.y"
    {(yyval.ty) = A_SimpleTy(EM_tokPos, (yyvsp[(1) - (1)].simpleTy));}
    break;

  case 22:
#line 135 "spl.y"
    {(yyval.ty) = (yyvsp[(1) - (1)].ty);}
    break;

  case 23:
#line 136 "spl.y"
    {(yyval.ty) = (yyvsp[(1) - (1)].ty);}
    break;

  case 24:
#line 138 "spl.y"
    {(yyval.simpleTy) = A_SysTy(EM_tokPos, S_Symbol((yyvsp[(1) - (1)].sval)));}
    break;

  case 25:
#line 139 "spl.y"
    {(yyval.simpleTy) = A_SingleTy(EM_tokPos, S_Symbol((yyvsp[(1) - (1)].sval)));}
    break;

  case 26:
#line 140 "spl.y"
    {(yyval.simpleTy) = A_ListTy(EM_tokPos, (yyvsp[(2) - (3)].nameList));}
    break;

  case 27:
#line 141 "spl.y"
    {(yyval.simpleTy) = A_DoubleCTy(EM_tokPos, (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp));}
    break;

  case 28:
#line 142 "spl.y"
    {(yyval.simpleTy) = A_DoubleCTy(EM_tokPos, A_OpExp(EM_tokPos, A_minusOp, A_ConstExp(EM_tokPos, 0), (yyvsp[(2) - (4)].exp)), (yyvsp[(4) - (4)].exp));}
    break;

  case 29:
#line 143 "spl.y"
    {(yyval.simpleTy) = A_DoubleCTy(EM_tokPos, A_OpExp(EM_tokPos, A_minusOp, A_ConstExp(EM_tokPos, 0), (yyvsp[(2) - (5)].exp)), A_OpExp(EM_tokPos, A_minusOp, A_ConstExp(EM_tokPos, 0), (yyvsp[(5) - (5)].exp)));}
    break;

  case 30:
#line 144 "spl.y"
    {(yyval.simpleTy) = A_DoubleNTy(EM_tokPos, S_Symbol((yyvsp[(1) - (3)].sval)), S_Symbol((yyvsp[(3) - (3)].sval)));}
    break;

  case 31:
#line 146 "spl.y"
    {(yyval.ty) = A_ArrayTy(EM_tokPos, (yyvsp[(3) - (6)].simpleTy), (yyvsp[(6) - (6)].ty));}
    break;

  case 32:
#line 148 "spl.y"
    {(yyval.ty) = A_RecordTy(EM_tokPos, (yyvsp[(2) - (3)].fieldList));}
    break;

  case 33:
#line 150 "spl.y"
    {(yyval.fieldList) = A_FieldList((yyvsp[(1) - (1)].field), NULL);}
    break;

  case 34:
#line 151 "spl.y"
    {(yyval.fieldList) = A_FieldList((yyvsp[(1) - (2)].field), (yyvsp[(2) - (2)].fieldList));}
    break;

  case 35:
#line 153 "spl.y"
    {(yyval.field) = A_Field((yyvsp[(1) - (4)].nameList), (yyvsp[(3) - (4)].ty));}
    break;

  case 36:
#line 155 "spl.y"
    {(yyval.nameList) = A_NameList((yyvsp[(1) - (1)].name), NULL);}
    break;

  case 37:
#line 156 "spl.y"
    {(yyval.nameList) = A_NameList((yyvsp[(1) - (3)].name), (yyvsp[(3) - (3)].nameList));}
    break;

  case 38:
#line 158 "spl.y"
    {(yyval.name) = A_Name(EM_tokPos, S_Symbol((yyvsp[(1) - (1)].sval)));}
    break;

  case 39:
#line 162 "spl.y"
    {(yyval.decPart) = NULL;}
    break;

  case 40:
#line 163 "spl.y"
    {(yyval.decPart) = A_DecPart(EM_tokPos, (yyvsp[(2) - (2)].decList));}
    break;

  case 41:
#line 165 "spl.y"
    {(yyval.decList) = A_DecList((yyvsp[(1) - (1)].dec), NULL);}
    break;

  case 42:
#line 166 "spl.y"
    {(yyval.decList) = A_DecList((yyvsp[(1) - (2)].dec), (yyvsp[(2) - (2)].decList));}
    break;

  case 43:
#line 168 "spl.y"
    {(yyval.dec) = A_VarDec(EM_tokPos, A_Field((yyvsp[(1) - (4)].nameList), (yyvsp[(3) - (4)].ty)));}
    break;

  case 44:
#line 172 "spl.y"
    {(yyval.decPart) = NULL;}
    break;

  case 45:
#line 173 "spl.y"
    {(yyval.decPart) = A_DecPart(EM_tokPos, (yyvsp[(1) - (1)].decList));}
    break;

  case 46:
#line 175 "spl.y"
    {(yyval.decList) = A_DecList((yyvsp[(1) - (1)].dec), NULL);}
    break;

  case 47:
#line 176 "spl.y"
    {(yyval.decList) = A_DecList((yyvsp[(1) - (1)].dec), NULL);}
    break;

  case 48:
#line 177 "spl.y"
    {(yyval.decList) = A_DecList((yyvsp[(1) - (2)].dec), (yyvsp[(2) - (2)].decList));}
    break;

  case 49:
#line 178 "spl.y"
    {(yyval.decList) = A_DecList((yyvsp[(1) - (2)].dec), (yyvsp[(2) - (2)].decList));}
    break;

  case 50:
#line 180 "spl.y"
    {(yyval.dec) = A_RoutineDec(EM_tokPos, S_Symbol((yyvsp[(2) - (8)].sval)), (yyvsp[(3) - (8)].fieldList), (yyvsp[(5) - (8)].simpleTy), (yyvsp[(7) - (8)].routine));}
    break;

  case 51:
#line 183 "spl.y"
    {(yyval.dec) = A_RoutineDec(EM_tokPos, S_Symbol((yyvsp[(2) - (6)].sval)), (yyvsp[(3) - (6)].fieldList), NULL, (yyvsp[(5) - (6)].routine));}
    break;

  case 52:
#line 186 "spl.y"
    {(yyval.fieldList) = NULL;}
    break;

  case 53:
#line 187 "spl.y"
    {(yyval.fieldList) = (yyvsp[(2) - (3)].fieldList);}
    break;

  case 54:
#line 189 "spl.y"
    {(yyval.fieldList) = A_FieldList((yyvsp[(1) - (1)].field), NULL);}
    break;

  case 55:
#line 190 "spl.y"
    {(yyval.fieldList) = A_FieldList((yyvsp[(1) - (3)].field), (yyvsp[(3) - (3)].fieldList));}
    break;

  case 56:
#line 192 "spl.y"
    {(yyval.field) = A_Field((yyvsp[(1) - (3)].nameList), A_SimpleTy(EM_tokPos, (yyvsp[(3) - (3)].simpleTy)));}
    break;

  case 57:
#line 193 "spl.y"
    {(yyval.field) = A_Field((yyvsp[(1) - (3)].nameList), A_SimpleTy(EM_tokPos, (yyvsp[(3) - (3)].simpleTy)));}
    break;

  case 58:
#line 195 "spl.y"
    {(yyval.nameList) = (yyvsp[(2) - (2)].nameList);}
    break;

  case 59:
#line 197 "spl.y"
    {(yyval.nameList) = (yyvsp[(1) - (1)].nameList);}
    break;

  case 60:
#line 199 "spl.y"
    {(yyval.routineBody) = A_RoutineBody((yyvsp[(1) - (1)].stmt));}
    break;

  case 61:
#line 201 "spl.y"
    {(yyval.stmt) = A_CompoundStmt(EM_tokPos, (yyvsp[(2) - (3)].stmtList));}
    break;

  case 62:
#line 203 "spl.y"
    {(yyval.stmtList) = NULL;}
    break;

  case 63:
#line 204 "spl.y"
    {(yyval.stmtList) = A_StmtList((yyvsp[(1) - (3)].stmt), (yyvsp[(3) - (3)].stmtList));}
    break;

  case 64:
#line 206 "spl.y"
    {(yyval.stmt) = A_Stmt(EM_tokPos, A_Int(EM_tokPos, -1), (yyvsp[(1) - (1)].stmt));}
    break;

  case 65:
#line 207 "spl.y"
    {(yyval.stmt) = A_Stmt(EM_tokPos, A_Int(EM_tokPos, (yyvsp[(1) - (3)].ival)), (yyvsp[(3) - (3)].stmt));}
    break;

  case 66:
#line 209 "spl.y"
    {(yyval.stmt) = (yyvsp[(1) - (1)].stmt);}
    break;

  case 67:
#line 210 "spl.y"
    {(yyval.stmt) = A_ProcStmt(EM_tokPos, (yyvsp[(1) - (1)].proc));}
    break;

  case 68:
#line 211 "spl.y"
    {(yyval.stmt) = (yyvsp[(1) - (1)].stmt);}
    break;

  case 69:
#line 212 "spl.y"
    {(yyval.stmt) = (yyvsp[(1) - (1)].stmt);}
    break;

  case 70:
#line 213 "spl.y"
    {(yyval.stmt) = (yyvsp[(1) - (1)].stmt);}
    break;

  case 71:
#line 214 "spl.y"
    {(yyval.stmt) = (yyvsp[(1) - (1)].stmt);}
    break;

  case 72:
#line 215 "spl.y"
    {(yyval.stmt) = (yyvsp[(1) - (1)].stmt);}
    break;

  case 73:
#line 216 "spl.y"
    {(yyval.stmt) = (yyvsp[(1) - (1)].stmt);}
    break;

  case 74:
#line 217 "spl.y"
    {(yyval.stmt) = (yyvsp[(1) - (1)].stmt);}
    break;

  case 75:
#line 219 "spl.y"
    {(yyval.stmt) = A_AssignStmt(EM_tokPos, A_SimpleVar(EM_tokPos, S_Symbol((yyvsp[(1) - (3)].sval))), (yyvsp[(3) - (3)].exp));}
    break;

  case 76:
#line 220 "spl.y"
    {(yyval.stmt) = A_AssignStmt(EM_tokPos, A_SubscriptVar(EM_tokPos, S_Symbol((yyvsp[(1) - (6)].sval)), (yyvsp[(3) - (6)].exp)), (yyvsp[(6) - (6)].exp));}
    break;

  case 77:
#line 221 "spl.y"
    {(yyval.stmt) = A_AssignStmt(EM_tokPos, A_FieldVar(EM_tokPos, S_Symbol((yyvsp[(1) - (5)].sval)), S_Symbol((yyvsp[(3) - (5)].sval))), (yyvsp[(5) - (5)].exp));}
    break;

  case 78:
#line 223 "spl.y"
    {(yyval.proc) = A_Func(EM_tokPos, S_Symbol((yyvsp[(1) - (1)].sval)), NULL);}
    break;

  case 79:
#line 224 "spl.y"
    {(yyval.proc) = A_Func(EM_tokPos, S_Symbol((yyvsp[(1) - (4)].sval)), (yyvsp[(3) - (4)].expList));}
    break;

  case 80:
#line 225 "spl.y"
    {(yyval.proc) = A_SysProc(EM_tokPos, S_Symbol((yyvsp[(1) - (1)].sval)), NULL);}
    break;

  case 81:
#line 226 "spl.y"
    {(yyval.proc) = A_SysProc(EM_tokPos, S_Symbol((yyvsp[(1) - (4)].sval)), (yyvsp[(3) - (4)].expList));}
    break;

  case 82:
#line 228 "spl.y"
    {(yyval.stmt) = A_IfStmt(EM_tokPos, (yyvsp[(2) - (4)].exp), (yyvsp[(4) - (4)].stmt), NULL);}
    break;

  case 83:
#line 229 "spl.y"
    {(yyval.stmt) = A_IfStmt(EM_tokPos, (yyvsp[(2) - (6)].exp), (yyvsp[(4) - (6)].stmt), (yyvsp[(6) - (6)].stmt));}
    break;

  case 84:
#line 231 "spl.y"
    {(yyval.stmt) = A_RepeatStmt(EM_tokPos, (yyvsp[(4) - (4)].exp), (yyvsp[(2) - (4)].stmtList));}
    break;

  case 85:
#line 233 "spl.y"
    {(yyval.stmt) = A_WhileStmt(EM_tokPos, (yyvsp[(2) - (4)].exp), (yyvsp[(4) - (4)].stmt));}
    break;

  case 86:
#line 235 "spl.y"
    {(yyval.stmt) = A_ForStmt(EM_tokPos, S_Symbol((yyvsp[(2) - (8)].sval)), (yyvsp[(4) - (8)].exp), (yyvsp[(6) - (8)].exp), (yyvsp[(8) - (8)].stmt));}
    break;

  case 87:
#line 236 "spl.y"
    {(yyval.stmt) = A_ForStmt(EM_tokPos, S_Symbol((yyvsp[(2) - (8)].sval)), (yyvsp[(4) - (8)].exp), (yyvsp[(6) - (8)].exp), (yyvsp[(8) - (8)].stmt));}
    break;

  case 88:
#line 238 "spl.y"
    {(yyval.stmt) = A_CaseStmt(EM_tokPos, (yyvsp[(2) - (5)].exp), (yyvsp[(4) - (5)].caseList));}
    break;

  case 89:
#line 240 "spl.y"
    {(yyval.caseList) = A_CaseList((yyvsp[(1) - (1)].casee), NULL);}
    break;

  case 90:
#line 241 "spl.y"
    {(yyval.caseList) = A_CaseList((yyvsp[(1) - (2)].casee), (yyvsp[(2) - (2)].caseList));}
    break;

  case 91:
#line 243 "spl.y"
    {(yyval.casee) = A_Case(EM_tokPos, (yyvsp[(1) - (4)].constt), NULL, (yyvsp[(3) - (4)].stmt));}
    break;

  case 92:
#line 244 "spl.y"
    {(yyval.casee) = A_Case(EM_tokPos, A_Int(EM_tokPos, -1), S_Symbol((yyvsp[(1) - (4)].sval)), (yyvsp[(3) - (4)].stmt));}
    break;

  case 93:
#line 246 "spl.y"
    {(yyval.stmt) = A_GotoStmt(EM_tokPos, A_Int(EM_tokPos, (yyvsp[(2) - (2)].ival)));}
    break;

  case 94:
#line 248 "spl.y"
    {(yyval.expList) = (yyvsp[(1) - (1)].expList);}
    break;

  case 95:
#line 250 "spl.y"
    {(yyval.expList) = A_ExpList((yyvsp[(1) - (1)].exp), NULL);}
    break;

  case 96:
#line 251 "spl.y"
    {(yyval.expList) = A_ExpList((yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].expList));}
    break;

  case 97:
#line 253 "spl.y"
    {(yyval.exp) = (yyvsp[(1) - (1)].exp);}
    break;

  case 98:
#line 254 "spl.y"
    {(yyval.exp) = (yyvsp[(1) - (1)].exp);}
    break;

  case 99:
#line 255 "spl.y"
    {(yyval.exp) = (yyvsp[(1) - (1)].exp);}
    break;

  case 100:
#line 256 "spl.y"
    {(yyval.exp) = (yyvsp[(1) - (1)].exp);}
    break;

  case 101:
#line 257 "spl.y"
    {(yyval.exp) = (yyvsp[(1) - (1)].exp);}
    break;

  case 102:
#line 258 "spl.y"
    {(yyval.exp) = A_FuncExp(EM_tokPos, (yyvsp[(1) - (1)].proc));}
    break;

  case 103:
#line 261 "spl.y"
    {(yyval.exp) = A_VarExp(EM_tokPos, (yyvsp[(1) - (1)].var));}
    break;

  case 104:
#line 263 "spl.y"
    {(yyval.var) = A_SimpleVar(EM_tokPos, S_Symbol((yyvsp[(1) - (1)].sval)));}
    break;

  case 105:
#line 264 "spl.y"
    {(yyval.var) = A_SubscriptVar(EM_tokPos, NULL, (yyvsp[(2) - (3)].exp));}
    break;

  case 106:
#line 265 "spl.y"
    {(yyval.var) = A_SubscriptVar(EM_tokPos, S_Symbol((yyvsp[(1) - (4)].sval)), (yyvsp[(3) - (4)].exp));}
    break;

  case 107:
#line 266 "spl.y"
    {(yyval.var) = A_FieldVar(EM_tokPos, S_Symbol((yyvsp[(1) - (3)].sval)), S_Symbol((yyvsp[(3) - (3)].sval)));}
    break;

  case 108:
#line 268 "spl.y"
    {(yyval.exp) = A_ConstExp(EM_tokPos, (yyvsp[(1) - (1)].constt));}
    break;

  case 109:
#line 270 "spl.y"
    {(yyval.exp) = A_OpExp(EM_tokPos, A_plusOp, (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp));}
    break;

  case 110:
#line 271 "spl.y"
    {(yyval.exp) = A_OpExp(EM_tokPos, A_minusOp, (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp));}
    break;

  case 111:
#line 272 "spl.y"
    {(yyval.exp) = A_OpExp(EM_tokPos, A_timesOp, (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp));}
    break;

  case 112:
#line 273 "spl.y"
    {(yyval.exp) = A_OpExp(EM_tokPos, A_timesOp, (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp));}
    break;

  case 113:
#line 274 "spl.y"
    {(yyval.exp) = A_OpExp(EM_tokPos, A_divideOp, (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp));}
    break;

  case 114:
#line 275 "spl.y"
    {(yyval.exp) = A_OpExp(EM_tokPos, A_minusOp, A_ConstExp(EM_tokPos, 0), (yyvsp[(2) - (2)].exp));}
    break;

  case 115:
#line 278 "spl.y"
    {(yyval.exp) = A_OpExp(EM_tokPos, A_eqOp, (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp));}
    break;

  case 116:
#line 279 "spl.y"
    {(yyval.exp) = A_OpExp(EM_tokPos, A_neqOp, (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp));}
    break;

  case 117:
#line 280 "spl.y"
    {(yyval.exp) = A_OpExp(EM_tokPos, A_gtOp, (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp));}
    break;

  case 118:
#line 281 "spl.y"
    {(yyval.exp) = A_OpExp(EM_tokPos, A_geOp, (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp));}
    break;

  case 119:
#line 282 "spl.y"
    {(yyval.exp) = A_OpExp(EM_tokPos, A_leOp, (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp));}
    break;

  case 120:
#line 283 "spl.y"
    {(yyval.exp) = A_OpExp(EM_tokPos, A_ltOp, (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp));}
    break;

  case 121:
#line 286 "spl.y"
    {(yyval.exp) = A_IfExp(EM_tokPos, (yyvsp[(2) - (2)].exp), A_ConstExp(EM_tokPos,A_Int(EM_tokPos, 0)), A_ConstExp(EM_tokPos, A_Int(EM_tokPos, 1)));}
    break;

  case 122:
#line 287 "spl.y"
    {(yyval.exp) = A_IfExp(EM_tokPos, (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp), A_ConstExp(EM_tokPos,A_Int(EM_tokPos, 0)));}
    break;

  case 123:
#line 288 "spl.y"
    {(yyval.exp) = A_IfExp(EM_tokPos, (yyvsp[(1) - (3)].exp), A_ConstExp(EM_tokPos,A_Int(EM_tokPos, 1)), (yyvsp[(3) - (3)].exp));}
    break;

  case 124:
#line 290 "spl.y"
    {(yyval.proc) = A_Func(EM_tokPos, S_Symbol((yyvsp[(1) - (4)].sval)), (yyvsp[(3) - (4)].expList));}
    break;

  case 125:
#line 291 "spl.y"
    {(yyval.proc) = A_Func(EM_tokPos, S_Symbol((yyvsp[(1) - (4)].sval)), (yyvsp[(3) - (4)].expList));}
    break;


/* Line 1267 of yacc.c.  */
#line 2388 "y.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;


  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
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

  /* Else will try to reuse look-ahead token after shifting the error
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

  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
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

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;


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

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
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
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



