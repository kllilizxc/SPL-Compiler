%{
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
%}


%union {
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

%token <sval> ID SYS_CON SYS_FUNCT SYS_PROC SYS_TYPE STRING
%token <ival> INTEGER
%token <fval> REAL
%token <cval> CHAR

%token 
  COMMA COLON SEMI LP RP LB RB DOT DOTDOT
  PLUS MINUS MUL DIV MOD EQUEL UNEQUAL LT LE GT GE
  AND OR NOT ASSIGN
  ARRAY BEGINN CASE IF THEN ELSE WHILE FOR TO DOWNTO GOTO DO LET IN END OF WITH
  PACKED PROCEDURE PROGRAM RECORD REPEAT SET UNTIL BREAK
  FUNCTION VAR TYPE CONST

%left LOWEST
%nonassoc OF IF THEN DO WHILE FOR TO DOWNTO GOTO WITH ASSIGN REPEAT UNTIL
%left ELSE
%nonassoc EQUAL UNEQUAL GT LT GE LE
%left PLUS MINUS OR
%left MUL DIV MOD AND
%left UMINUS
%left NOT
%right LB
%nonassoc TYPE FUNCTION VAR CONST



%type <pro> program
%type <routine> routine
%type <routineHead> routine_head
%type <decPart> label_part const_part type_part var_part routine_part
%type <decList> const_expr_list type_decl_list var_decl_list routine_decl_list
%type <dec> const_expr type_definition var_decl function_decl procedure_decl
%type <ty> type_decl array_type_decl record_type_decl
%type <simpleTy> simple_type_decl
%type <constt> const_value
%type <fieldList> field_decl_list parameters para_decl_list
%type <field> field_decl para_type_list
%type <nameList> name_list var_para_list varE_para_list
%type <name> names
%type <routineBody> routine_body
%type <stmtList> stmt_list 
%type <stmt> non_label_stmt assign_stmt if_stmt repeat_stmt while_stmt for_stmt case_stmt goto_stmt compound_stmt stmt
%type <proc> proc_stmt funcExp
%type <caseList> case_exp_list
%type <casee> case_exp
%type <expList> exp_list args_list
%type <exp> exp lvalueExp literalExp arithmeticExp comparisonExp booleanExp
%type <var> lvalue

%start program

%%

program : PROGRAM ID SEMI routine DOT {absyn_root = A_Pro(EM_tokPos, S_Symbol($2), $4);}

routine : routine_head routine_body {$$ = A_Routine($1, $2);}

routine_head : label_part const_part type_part var_part routine_part {$$ = A_RoutineHead($1, $2, $3, $4, $5);}

label_part : %prec LOWEST {$$ = NULL;}

const_part : %prec LOWEST {$$ = NULL;}
           | CONST const_expr_list {$$ = A_DecPart(EM_tokPos, $2);}

const_expr_list : const_expr %prec LOWEST {$$ = A_DecList($1, NULL);}
                | const_expr const_expr_list {$$ = A_DecList($1, $2);}

const_expr : ID  EQUAL  const_value  SEMI {$$ = A_ConstDec(EM_tokPos, S_Symbol($1), $3);}

const_value : INTEGER  {$$ = A_Int(EM_tokPos, $1);}
            | REAL  {$$ = A_Real(EM_tokPos, $1);}
            | CHAR  {$$ = A_Char(EM_tokPos, $1);}
            | STRING  {$$ = A_String(EM_tokPos, $1);}
            | SYS_CON {$$ = A_Syscon(EM_tokPos, S_Symbol($1));}
//TYPE
type_part : %prec LOWEST {$$ = NULL;}
          | TYPE type_decl_list {$$ = A_DecPart(EM_tokPos, $2);}

type_decl_list : type_definition %prec LOWEST {$$ = A_DecList($1, NULL);}
               | type_definition type_decl_list {$$ = A_DecList($1, $2);}

type_definition : ID  EQUAL  type_decl  SEMI {$$ = A_TypeDec(EM_tokPos, S_Symbol($1), $3);}

type_decl : simple_type_decl  {$$ = A_SimpleTy(EM_tokPos, $1);}
          | array_type_decl  {$$ = $1;}
          | record_type_decl {$$ = $1;}

simple_type_decl : SYS_TYPE  {$$ = A_SysTy(EM_tokPos, S_Symbol($1));}
                 | ID {$$ = A_SingleTy(EM_tokPos, S_Symbol($1));}
                 | LP name_list RP  {$$ = A_ListTy(EM_tokPos, $2);}
                 | literalExp DOTDOT literalExp  {$$ = A_DoubleCTy(EM_tokPos, $1, $3);}
                 | MINUS literalExp DOTDOT literalExp  {$$ = A_DoubleCTy(EM_tokPos, A_OpExp(EM_tokPos, A_minusOp, A_ConstExp(EM_tokPos, A_Int(EM_tokPos,0)), $2), $4);}
                 | MINUS literalExp DOTDOT MINUS literalExp  {$$ = A_DoubleCTy(EM_tokPos, A_OpExp(EM_tokPos, A_minusOp, A_ConstExp(EM_tokPos, A_Int(EM_tokPos,0)), $2), A_OpExp(EM_tokPos, A_minusOp, A_ConstExp(EM_tokPos, A_Int(EM_tokPos,0)), $5));}
                 | ID DOTDOT ID {$$ = A_DoubleNTy(EM_tokPos, S_Symbol($1), S_Symbol($3));}

array_type_decl : ARRAY  LB  simple_type_decl  RB  OF  type_decl {$$ = A_ArrayTy(EM_tokPos, $3, $6);}

record_type_decl : RECORD  field_decl_list  END {$$ = A_RecordTy(EM_tokPos, $2);}

field_decl_list : field_decl %prec LOWEST {$$ = A_FieldList($1, NULL);}
                | field_decl field_decl_list {$$ = A_FieldList($1, $2);}

field_decl : name_list  COLON  type_decl  SEMI {$$ = A_Field($1, $3);}

name_list : names {$$ = A_NameList($1, NULL);}
          | names COMMA name_list {$$ = A_NameList($1, $3);}

names : ID {$$ = A_Name(EM_tokPos, S_Symbol($1));}

//VAR

var_part : %prec LOWEST {$$ = NULL;}
         | VAR var_decl_list {$$ = A_DecPart(EM_tokPos, $2);}

var_decl_list : var_decl %prec LOWEST {$$ = A_DecList($1, NULL);}
              | var_decl var_decl_list {$$ = A_DecList($1, $2);}

var_decl : name_list COLON type_decl SEMI {$$ = A_VarDec(EM_tokPos, A_Field($1, $3));}

//ROUTINE

routine_part : %prec LOWEST {$$ = NULL;}
             | routine_decl_list {$$ = A_DecPart(EM_tokPos, $1);}

routine_decl_list : function_decl %prec LOWEST {$$ = A_DecList($1, NULL);}
                  | procedure_decl %prec LOWEST {$$ = A_DecList($1, NULL);}
                  | function_decl routine_decl_list {$$ = A_DecList($1, $2);}                  
                  | procedure_decl routine_decl_list {$$ = A_DecList($1, $2);}

function_decl : FUNCTION ID parameters COLON simple_type_decl SEMI routine SEMI {$$ = A_RoutineDec(EM_tokPos, S_Symbol($2), $3, $5, $7);}


procedure_decl : PROCEDURE ID parameters SEMI routine SEMI {$$ = A_RoutineDec(EM_tokPos, S_Symbol($2), $3, NULL, $5);}


parameters : %prec LOWEST {$$ = NULL;}
           | LP para_decl_list RP {$$ = $2;}

para_decl_list : para_type_list %prec LOWEST {$$ = A_FieldList($1, NULL);}
               | para_type_list SEMI para_decl_list {$$ = A_FieldList($1, $3);}

para_type_list : var_para_list COLON simple_type_decl {$$ = A_Field($1, A_SimpleTy(EM_tokPos, $3));}
               | varE_para_list COLON simple_type_decl {$$ = A_Field($1, A_SimpleTy(EM_tokPos, $3));}

var_para_list : VAR name_list {$$ = $2;}

varE_para_list : name_list {$$ = $1;}

routine_body : compound_stmt {$$ = A_RoutineBody($1);}

compound_stmt : BEGINN stmt_list END {$$ = A_CompoundStmt(EM_tokPos, $2);}

stmt_list : %prec LOWEST {$$ = NULL;}
          | stmt SEMI stmt_list {$$ = A_StmtList($1, $3);}

stmt : non_label_stmt {$$ = A_Stmt(EM_tokPos, A_Int(EM_tokPos, -1), $1);}
     | INTEGER COLON non_label_stmt {$$ = A_Stmt(EM_tokPos, A_Int(EM_tokPos, $1), $3);}

non_label_stmt : assign_stmt {$$ = $1;}
               | proc_stmt {$$ = A_ProcStmt(EM_tokPos, $1);}
               | compound_stmt {$$ = $1;}
               | if_stmt {$$ = $1;}
               | repeat_stmt {$$ = $1;}
               | while_stmt {$$ = $1;}
               | for_stmt {$$ = $1;}
               | case_stmt {$$ = $1;}
               | goto_stmt {$$ = $1;}

assign_stmt : ID ASSIGN exp {$$ = A_AssignStmt(EM_tokPos, A_SimpleVar(EM_tokPos, S_Symbol($1)), $3);}
            | ID LB exp RB ASSIGN exp {$$ = A_AssignStmt(EM_tokPos, A_SubscriptVar(EM_tokPos, S_Symbol($1), $3), $6);}
            | ID DOT ID ASSIGN exp {$$ = A_AssignStmt(EM_tokPos, A_FieldVar(EM_tokPos, S_Symbol($1), S_Symbol($3)), $5);}

proc_stmt : ID {$$ = A_Func(EM_tokPos, S_Symbol($1), NULL);}
          | ID LP args_list RP {$$ = A_Func(EM_tokPos, S_Symbol($1), $3);}
          | SYS_PROC {$$ = A_SysProc(EM_tokPos, S_Symbol($1), NULL);}
          | SYS_PROC LP exp_list RP {$$ = A_SysProc(EM_tokPos, S_Symbol($1), $3);}

if_stmt : IF exp THEN stmt ELSE stmt {$$ = A_IfStmt(EM_tokPos, $2, $4, $6);}
        | IF exp THEN stmt {$$ = A_IfStmt(EM_tokPos, $2, $4, NULL);}

repeat_stmt : REPEAT stmt_list UNTIL exp {$$ = A_RepeatStmt(EM_tokPos, $4, $2);}

while_stmt : WHILE exp DO stmt {$$ = A_WhileStmt(EM_tokPos, $2, $4);}

for_stmt : FOR ID ASSIGN exp TO exp DO stmt {$$ = A_ForStmt(EM_tokPos, S_Symbol($2), $4, $6, $8);}
         | FOR ID ASSIGN exp DOWNTO exp DO stmt {$$ = A_ForStmt(EM_tokPos, S_Symbol($2), $4, $6, $8);}

case_stmt : CASE exp OF case_exp_list END {$$ = A_CaseStmt(EM_tokPos, $2, $4);}

case_exp_list : case_exp %prec LOWEST {$$ = A_CaseList($1, NULL);}
              | case_exp case_exp_list {$$ = A_CaseList($1, $2);}

case_exp : const_value COLON stmt SEMI {$$ = A_Case(EM_tokPos, $1, NULL, $3);}
         | ID COLON stmt SEMI {$$ = A_Case(EM_tokPos, A_Int(EM_tokPos, -1), S_Symbol($1), $3);}

goto_stmt : GOTO INTEGER {$$ = A_GotoStmt(EM_tokPos, A_Int(EM_tokPos, $2));}

args_list : exp_list {$$ = $1;}

exp_list : exp {$$ = A_ExpList($1, NULL);}
         | exp COMMA exp_list {$$ = A_ExpList($1, $3);}

exp : lvalueExp {$$ = $1;}                  
    | literalExp {$$ = $1;}                 
    | arithmeticExp {$$ = $1;}      
    | comparisonExp {$$ = $1;}
    | booleanExp {$$ = $1;}
    | funcExp {$$ = A_FuncExp(EM_tokPos, $1);}


lvalueExp : lvalue {$$ = A_VarExp(EM_tokPos, $1);}

lvalue : ID {$$ = A_SimpleVar(EM_tokPos, S_Symbol($1));}
       | LP exp RP {$$ = A_SubscriptVar(EM_tokPos, NULL, $2);}
       | ID LB exp RB {$$ = A_SubscriptVar(EM_tokPos, S_Symbol($1), $3);}
       | ID DOT ID {$$ = A_FieldVar(EM_tokPos, S_Symbol($1), S_Symbol($3));}

literalExp : const_value {$$ = A_ConstExp(EM_tokPos, $1);}

arithmeticExp : exp PLUS exp {$$ = A_OpExp(EM_tokPos, A_plusOp, $1, $3);}
              | exp MINUS exp {$$ = A_OpExp(EM_tokPos, A_minusOp, $1, $3);}
              | exp MOD exp {$$ = A_OpExp(EM_tokPos, A_modOp, $1, $3);}
              | exp MUL exp {$$ = A_OpExp(EM_tokPos, A_timesOp, $1, $3);}
              | exp DIV exp {$$ = A_OpExp(EM_tokPos, A_divideOp, $1, $3);}
              | MINUS exp %prec UMINUS {$$ = A_OpExp(EM_tokPos, A_minusOp, A_ConstExp(EM_tokPos, A_Int(EM_tokPos,0)), $2);}


comparisonExp : exp EQUAL exp {$$ = A_OpExp(EM_tokPos, A_eqOp, $1, $3);}
              | exp UNEQUAL exp {$$ = A_OpExp(EM_tokPos, A_neqOp, $1, $3);}
              | exp GT exp {$$ = A_OpExp(EM_tokPos, A_gtOp, $1, $3);}
              | exp GE exp {$$ = A_OpExp(EM_tokPos, A_geOp, $1, $3);}
              | exp LE exp {$$ = A_OpExp(EM_tokPos, A_leOp, $1, $3);}
              | exp LT exp {$$ = A_OpExp(EM_tokPos, A_ltOp, $1, $3);}


booleanExp : NOT exp {$$ = A_IfExp(EM_tokPos, $2, A_ConstExp(EM_tokPos,A_Int(EM_tokPos, 0)), A_ConstExp(EM_tokPos, A_Int(EM_tokPos, 1)));}
           | exp AND exp {$$ = A_IfExp(EM_tokPos, $1, $3, A_ConstExp(EM_tokPos,A_Int(EM_tokPos, 0)));}
           | exp OR exp {$$ = A_IfExp(EM_tokPos, $1, A_ConstExp(EM_tokPos,A_Int(EM_tokPos, 1)), $3);}

funcExp : SYS_FUNCT LP args_list RP {$$ = A_Func(EM_tokPos, S_Symbol($1), $3);}
        | ID LP args_list RP {$$ = A_Func(EM_tokPos, S_Symbol($1), $3);}




















  
