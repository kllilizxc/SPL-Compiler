/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

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
/* Line 1529 of yacc.c.  */
#line 213 "y.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif


int yyparse(void);
extern YYSTYPE yylval;

