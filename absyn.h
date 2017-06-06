//
//  absyn.h - Abstract Syntax Header (Chapter 4)
//  All types and functions declared in this header file begin with "A_" Linked list types end with "..list"
//  SPL-compiler
//
//  Created by cai on 2017/6/3.
//  Copyright © 2017年 cai. All rights reserved.
//

#ifndef absyn_h
#define absyn_h

#include "symbol.h"


typedef int A_pos;
typedef struct A_pro_ *A_pro;
typedef struct A_routine_ *A_routine;
typedef struct A_routineHead_ *A_routineHead;
typedef struct A_routineBody_ *A_routineBody;

typedef struct A_var_ *A_var;
typedef struct A_const_ *A_const;
typedef struct A_exp_ *A_exp;
typedef struct A_stmt_ *A_stmt;
typedef struct A_dec_ *A_dec;
typedef struct A_ty_ *A_ty;
typedef struct A_simpleTy_ *A_simpleTy;
typedef struct A_decPart_ *A_decPart;
typedef struct A_decList_ *A_decList;
typedef struct A_expList_ *A_expList;
typedef struct A_stmtList_ *A_stmtList;
typedef struct A_field_ *A_field;
typedef struct A_fieldList_ *A_fieldList;
typedef struct A_name_ *A_name;
typedef struct A_nameList_ *A_nameList;
typedef struct A_case_ *A_case;
typedef struct A_caseList_ *A_caseList;
typedef struct A_proc_ *A_proc;


typedef enum {A_plusOp, A_minusOp, A_timesOp, A_modOp, A_divideOp,
    A_eqOp, A_neqOp, A_ltOp, A_leOp, A_gtOp, A_geOp} A_oper;
//typedef enum {A_falseSysCon, A_maxintSysCon, A_trueSysCon} A_sysCon;
//
//typedef enum {A_absSysFunct, A_chrSysFunct, A_oddSysFunct, A_ordSysFunct, A_predSysFunct, A_sqrSysFunct, A_sqrtSysFunct, A_succSysFunct} A_sysFunct;
//
//typedef enum {A_writeSysProc, A_writelnSysProc, A_readSysProc} A_sysProc;
//
//typedef enum {A_boolean, A_char, A_integer, A_real, A_string} A_sysType;

struct A_pro_ {A_pos pos; S_symbol name; A_routine routine;};
struct A_routine_ {A_routineHead head; A_routineBody body;};

struct A_routineHead_{
    A_decPart labelPart;
    A_decPart constPart;
    A_decPart typePart;
    A_decPart varPart;
    A_decPart routinePart;
};

struct A_decPart_ {A_pos pos; A_decList head;};
struct A_decList_ {A_dec head; A_decList tail;};

enum A_dec_Kind {A_constDec, A_typeDec, A_varDec, A_routineDec};
typedef struct {S_symbol name; A_fieldList params; A_simpleTy simplety; A_routine subroutine;} _A_routine_;
typedef struct {S_symbol name; A_const constValue;} _A_const_;
typedef struct {S_symbol name; A_ty ty;} _A_type_;
struct A_dec_ { enum A_dec_Kind kind;
    A_pos pos;
    union {
        _A_const_ constt;
        _A_type_ type;
        struct {A_field var;} var;
        _A_routine_ routine;
    } u;
};

enum A_const_Kind {A_int, A_real, A_char, A_string, A_syscon};
struct A_const_ {enum A_const_Kind kind;
    A_pos pos;
    union{
        int intt;
        float reall;
        char charr;
        string stringg;
        S_symbol syscon;
    } u;
};

struct A_name_ {A_pos pos; S_symbol name;};
struct A_nameList_ {A_name head; A_nameList tail;};

struct A_field_ {A_nameList head; A_ty ty;};
struct A_fieldList_ {A_field head; A_fieldList tail;};

enum A_ty_Kind {A_simTy, A_recordTy, A_arrayTy};
typedef struct {A_simpleTy simple; A_ty ty;} _A_array_;
struct A_ty_ {enum A_ty_Kind kind;
    A_pos pos;
    union {
        A_simpleTy simple;
        A_fieldList record;
        _A_array_ array;
    } u;
};

enum A_simpleTy_Kind {A_sysTy, A_singleTy, A_doubleCTy, A_doubleNTy, A_listTy};
typedef struct {A_exp left; A_exp right;} _A_doubleC_;
typedef struct {S_symbol left; S_symbol right;} _A_doubleN_;
struct A_simpleTy_ { enum A_simpleTy_Kind kind;
    A_pos pos;
    union{
        S_symbol systy;
        S_symbol single;
        _A_doubleC_ doubleC;
        _A_doubleN_ doubleN;
        A_nameList nameList;
    } u;
    
};


struct A_routineBody_ {A_stmt head;};
struct A_stmtList_ {A_stmt head; A_stmtList tail;};

enum A_var_Kind {A_constVar, A_simpleVar, A_fieldVar, A_subscriptVar};
typedef struct {S_symbol var; A_exp exp;} _A_subscript_;
typedef struct {S_symbol var; S_symbol sym;} _A_field_;
struct A_var_{enum A_var_Kind kind;
    A_pos pos;
    union {
        A_const constValue;
        S_symbol simple;
        _A_field_ field;
        _A_subscript_ subscript;
    } u;
};

enum A_stmt_Kind {A_labelStmt, A_assignStmt, A_procStmt, A_ifStmt, A_repeatStmt, A_whileStmt, A_forStmt, A_caseStmt, A_gotoStmt, A_compoundStmt};
typedef struct {A_const label; A_stmt stmt;} _A_label_;
typedef struct {A_var var; A_exp exp;} _A_assign_;
typedef struct {A_exp test; A_stmt then, elsee;} _A_if_stm_;
typedef struct {A_exp test; A_stmtList repeat;} _A_repeat_;
typedef struct {A_exp test; A_stmt whilee;} _A_while_;
typedef struct {S_symbol var; A_exp init; A_exp change; A_stmt fordo;} _A_for_;
typedef struct {A_exp test; A_caseList caselist;} _A_case_;
typedef struct {A_const des;} _A_goto_;
typedef struct {A_stmtList substmtList;} _A_compound_;
struct A_stmt_ { enum A_stmt_Kind kind;
    A_pos pos;
    union{
        _A_label_ label;
        _A_assign_ assign;
        A_proc proc;
        _A_if_stm_ iff;
        _A_repeat_ repeat;
        _A_while_ whilee;
        _A_for_ forr;
        _A_case_ casee;
        _A_goto_ gotoo;
        _A_compound_ compound;
    } u;
};

enum A_proc_Kind {A_sysProc, A_func};
struct A_proc_{ enum A_proc_Kind kind;
    A_pos pos;
    A_expList args;
    union{
        S_symbol proc;
        S_symbol func;
    }u;
};

struct A_caseList_ {A_case head; A_caseList tail;};
struct A_case_ {A_pos pos; A_const constValue; S_symbol name; A_stmt casee;};

enum A_exp_Kind {A_funcExp, A_varExp, A_constExp, A_opExp, A_ifExp};
typedef struct {A_exp test; A_exp then; A_exp elsee;} _A_if_exp_;
typedef struct {A_oper oper; A_exp left; A_exp right;} _A_op_;
struct A_exp_ { enum A_exp_Kind kind;
    A_pos pos;
    union{
        A_proc func;
        A_var var;
        A_const constValue;
        _A_op_ op;
        _A_if_exp_ iff;
    }u;
};
struct A_expList_ {A_exp head; A_expList tail;};


/* Function Prototypes */
A_pro A_Pro(A_pos pos, S_symbol name, A_routine routine);
A_routine A_Routine(A_routineHead head, A_routineBody body);
A_routineHead A_RoutineHead(A_decPart labelPart, A_decPart constPart, A_decPart typePart, A_decPart varPart, A_decPart routinePart);

A_decPart A_DecPart(A_pos pos, A_decList head);
A_decList A_DecList(A_dec head, A_decList tail);
A_dec A_ConstDec(A_pos pos, S_symbol name, A_const constValue);
A_dec A_TypeDec(A_pos pos, S_symbol name, A_ty ty);
A_dec A_VarDec(A_pos pos, A_field var);
A_dec A_RoutineDec(A_pos pos, S_symbol name, A_fieldList params, A_simpleTy simplety, A_routine subroutine);

A_const A_Int(A_pos pos, int i);
A_const A_Real(A_pos pos, float f);
A_const A_Char(A_pos pos, char c);
A_const A_String(A_pos pos, string s);
A_const A_Syscon(A_pos pos, S_symbol sysc);


A_name A_Name(A_pos pos, S_symbol name);
A_nameList A_NameList(A_name head, A_nameList tail);

A_field A_Field(A_nameList head, A_ty ty);
A_fieldList A_FieldList(A_field head, A_fieldList tail);

A_ty A_SimpleTy(A_pos pos, A_simpleTy simplety);
A_ty A_RecordTy(A_pos pos, A_fieldList record);
A_ty A_ArrayTy(A_pos pos, A_simpleTy simplety, A_ty ty);

A_simpleTy A_SysTy(A_pos pos, S_symbol systy);
A_simpleTy A_SingleTy(A_pos pos, S_symbol single);
A_simpleTy A_DoubleCTy(A_pos pos, A_exp left, A_exp right);
A_simpleTy A_DoubleNTy(A_pos pos, S_symbol left, S_symbol right);
A_simpleTy A_ListTy(A_pos pos, A_nameList nameList);

A_routineBody A_RoutineBody(A_stmt head);
A_stmtList A_StmtList(A_stmt head, A_stmtList tail);

A_var A_ConstVar(A_pos pos, A_const constValue);
A_var A_SimpleVar(A_pos pos, S_symbol sym);
A_var A_FieldVar(A_pos pos, S_symbol var, S_symbol sym);
A_var A_SubscriptVar(A_pos pos, S_symbol var, A_exp exp);

A_stmt A_Stmt(A_pos pos, A_const label, A_stmt stmt);
A_stmt A_AssignStmt(A_pos pos, A_var var, A_exp exp);
A_stmt A_ProcStmt(A_pos pos, A_proc proc);
A_stmt A_IfStmt(A_pos pos, A_exp test, A_stmt then, A_stmt elsee);
A_stmt A_RepeatStmt(A_pos pos, A_exp test, A_stmtList repeat);
A_stmt A_WhileStmt(A_pos pos, A_exp test, A_stmt whilee);
A_stmt A_ForStmt(A_pos pos, S_symbol var, A_exp init, A_exp change, A_stmt fordo);
A_stmt A_CaseStmt(A_pos pos, A_exp test, A_caseList caselist);
A_stmt A_GotoStmt(A_pos pos, A_const des);
A_stmt A_CompoundStmt(A_pos pos, A_stmtList substmtList);

A_proc A_SysProc(A_pos pos, S_symbol proc, A_expList expList);
A_proc A_Func(A_pos pos,S_symbol func, A_expList expList);

A_caseList A_CaseList(A_case head, A_caseList tail);
A_case A_Case(A_pos pos, A_const constValue, S_symbol name, A_stmt casee);

A_exp A_FuncExp(A_pos pos, A_proc func);
A_exp A_VarExp(A_pos pos, A_var var);
A_exp A_ConstExp(A_pos pos, A_const constValue);
A_exp A_OpExp(A_pos pos, A_oper oper, A_exp left, A_exp right);
A_exp A_IfExp(A_pos pos, A_exp test, A_exp then, A_exp elsee);

A_expList A_ExpList(A_exp head, A_expList tail);

#endif

