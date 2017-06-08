//
//  absyn.c
//  SPL-compiler
//
//  Created by cai on 2017/6/3.
//  Copyright © 2017年 cai. All rights reserved.
//

/*
 * absyn.c - Abstract Syntax Functions. Most functions create an instance of an
 *           abstract syntax rule.
 */

#include "util.h"
#include "symbol.h" /* symbol table data structures */
#include "absyn.h"  /* abstract syntax data structures */
#include <stdlib.h>
#include <stdio.h>

A_pro A_Pro(A_pos pos, S_symbol name, A_routine routine)
{
    A_pro p = checked_malloc(sizeof(*p));
    p->pos = pos;
    p->name = name;
    p->routine = routine;
    return p;
}

A_routine A_Routine(A_routineHead head, A_routineBody body)
{
    A_routine p = checked_malloc(sizeof(*p));
    p->head = head;
    p->body = body;
    return p;
}

A_routineHead A_RoutineHead(A_decPart labelPart, A_decPart constPart, A_decPart typePart, A_decPart varPart, A_decPart routinePart)
{
    A_routineHead p = checked_malloc(sizeof(*p));
    p->labelPart = labelPart;
    p->constPart = constPart;
    p->typePart = typePart;
    p->varPart = varPart;
    p->routinePart = routinePart;
    return p;
}

A_decPart A_DecPart(A_pos pos, A_decList head)
{
    A_decPart p = checked_malloc(sizeof(*p));
    p->head = head;
    p->pos = pos;
    return p;
}

A_decList A_DecList(A_dec head, A_decList tail)
{
    A_decList p = checked_malloc(sizeof(*p));
    p->head = head;
    p->tail = tail;
    return p;
}

A_dec A_ConstDec(A_pos pos, S_symbol name, A_const constValue)
{
    A_dec p = checked_malloc(sizeof(*p));
    p->kind = A_constDec;
    p->pos = pos;
    p->u.constt.name = name;
    p->u.constt.constValue = constValue;
    return p;
    
}

A_dec A_TypeDec(A_pos pos, S_symbol name, A_ty ty)
{
    A_dec p = checked_malloc(sizeof(*p));
    p->kind = A_typeDec;
    p->pos = pos;
    p->u.type.name = name;
    p->u.type.ty = ty;
    return p;
}

A_dec A_VarDec(A_pos pos, A_field var)
{
    A_dec p = checked_malloc(sizeof(*p));
    p->kind = A_varDec;
    p->pos = pos;
    p->u.var.var = var;
    return p;
}

A_dec A_RoutineDec(A_pos pos, S_symbol name, A_fieldList params, A_simpleTy simplety, A_routine subroutine)
{
    A_dec p = checked_malloc(sizeof(*p));
    p->kind = A_routineDec;
    p->pos = pos;
    p->u.routine.name = name;
    p->u.routine.params = params;
    p->u.routine.simplety = simplety;
    p->u.routine.subroutine = subroutine;
    return p;
}

A_const A_Int(A_pos pos, int i)
{
    A_const p = checked_malloc(sizeof(*p));
    p->kind = A_int;
    p->pos = pos;
    p->u.intt = i;
    return p;
}

A_const A_Real(A_pos pos, float f)
{
    A_const p = checked_malloc(sizeof(*p));
    p->kind = A_real;
    p->pos = pos;
    p->u.reall = f;
    return p;
}

A_const A_Char(A_pos pos, char c)
{
    A_const p = checked_malloc(sizeof(*p));
    p->kind = A_char;
    p->pos = pos;
    p->u.charr = c;
    return p;
}

A_const A_String(A_pos pos, string s)
{
    A_const p = checked_malloc(sizeof(*p));
    p->kind = A_string;
    p->pos = pos;
    p->u.stringg = s;
    return p;
}

A_const A_Syscon(A_pos pos, S_symbol sysc)
{
    A_const p = checked_malloc(sizeof(*p));
    p->kind = A_syscon;
    p->pos = pos;
    p->u.syscon = sysc;
    return p;
}

A_name A_Name(A_pos pos, S_symbol name)
{
    A_name p = checked_malloc(sizeof(*p));
    p->pos = pos;
    p->name = name;
    return p;
}

A_nameList A_NameList(A_name head, A_nameList tail)
{
    A_nameList p = checked_malloc(sizeof(*p));
    p->head = head;
    p->tail = tail;
    return p;
}

A_field A_Field(A_nameList head, A_ty ty)
{
    A_field p = checked_malloc(sizeof(*p));
    p->head = head;
    p->ty = ty;
    return p;
}

A_fieldList A_FieldList(A_field head, A_fieldList tail)
{
    A_fieldList p = checked_malloc(sizeof(*p));
    p->head = head;
    p->tail = tail;
    return p;
}

A_ty A_SimpleTy(A_pos pos, A_simpleTy simplety)
{
    A_ty p = checked_malloc(sizeof(*p));
    p->kind = A_simTy;
    p->pos = pos;
    p->u.simple = simplety;
    return p;
}

A_ty A_RecordTy(A_pos pos, A_fieldList record)
{
    A_ty p = checked_malloc(sizeof(*p));
    p->kind = A_recordTy;
    p->pos = pos;
    p->u.record = record;
    return p;
}

A_ty A_ArrayTy(A_pos pos, A_simpleTy simplety, A_ty ty)
{
    A_ty p = checked_malloc(sizeof(*p));
    p->kind = A_arrayTy;
    p->pos = pos;
    p->u.array.simple = simplety;
    p->u.array.ty = ty;
    return p;
}

A_simpleTy A_SysTy(A_pos pos, S_symbol systy)
{
    A_simpleTy p = checked_malloc(sizeof(*p));
    p->kind = A_sysTy;
    p->pos = pos;
    p->u.systy = systy;
    return p;
}

A_simpleTy A_SingleTy(A_pos pos, S_symbol single)
{
    A_simpleTy p = checked_malloc(sizeof(*p));
    p->kind = A_singleTy;
    p->pos = pos;
    p->u.single = single;
    return p;
}

A_simpleTy A_DoubleCTy(A_pos pos, A_exp left, A_exp right)
{
    A_simpleTy p = checked_malloc(sizeof(*p));
    p->kind = A_doubleCTy;
    p->pos = pos;
    p->u.doubleC.left = left;
    p->u.doubleC.right = right;
    return p;
}

A_simpleTy A_DoubleNTy(A_pos pos, S_symbol left, S_symbol right)
{
    A_simpleTy p = checked_malloc(sizeof(*p));
    p->kind = A_doubleNTy;
    p->pos = pos;
    p->u.doubleN.left = left;
    p->u.doubleN.right = right;
    return p;
}

A_simpleTy A_ListTy(A_pos pos, A_nameList nameList)
{
    A_simpleTy p = checked_malloc(sizeof(*p));
    p->kind = A_listTy;
    p->pos = pos;
    p->u.nameList = nameList;
    return p;
}



A_routineBody A_RoutineBody(A_stmt head)
{
    A_routineBody p = checked_malloc(sizeof(*p));
    p->head = head;
    return p;
}

A_stmtList A_StmtList(A_stmt head, A_stmtList tail)
{
    A_stmtList p = checked_malloc(sizeof(*p));
    p->head = head;
    p->tail = tail;
    return p;
}

A_var A_ConstVar(A_pos pos, A_const constValue)
{
    A_var p = checked_malloc(sizeof(*p));
    p->kind = A_constVar;
    p->pos = pos;
    p->u.constValue = constValue;
    return p;
}

A_var A_SimpleVar(A_pos pos, S_symbol sym)
{
    A_var p = checked_malloc(sizeof(*p));
    p->kind = A_simpleVar;
    p->pos = pos;
    p->u.simple = sym;
    return p;
}

A_var A_FieldVar(A_pos pos, S_symbol var, S_symbol sym)
{
    A_var p = checked_malloc(sizeof(*p));
    p->kind = A_fieldVar;
    p->pos = pos;
    p->u.field.var = var;
    p->u.field.sym = sym;
    return p;
}

A_var A_SubscriptVar(A_pos pos, S_symbol var, A_exp exp)
{
    A_var p = checked_malloc(sizeof(*p));
    p->kind = A_subscriptVar;
    p->pos = pos;
    p->u.subscript.var = var;
    p->u.subscript.exp = exp;
    return p;
}


A_stmt A_Stmt(A_pos pos, A_const label, A_stmt stmt)
{
    A_stmt p = checked_malloc(sizeof(*p));
    p->kind = A_labelStmt;
    p->pos = pos;
    p->u.label.label = label;
    p->u.label.stmt = stmt;
    return p;
}
A_stmt A_AssignStmt(A_pos pos, A_var var, A_exp exp)
{
    A_stmt p = checked_malloc(sizeof(*p));
    p->kind = A_assignStmt;
    p->pos = pos;
    p->u.assign.var = var;
    p->u.assign.exp = exp;
    return p;
}

A_stmt A_ProcStmt(A_pos pos, A_proc proc)
{
    A_stmt p = checked_malloc(sizeof(*p));
    p->kind = A_procStmt;
    p->pos = pos;
    p->u.proc = proc;
    return p;
}

A_stmt A_IfStmt(A_pos pos, A_exp test, A_stmt then, A_stmt elsee)
{
    A_stmt p = checked_malloc(sizeof(*p));
    p->kind = A_ifStmt;
    p->pos = pos;
    p->u.iff.test = test;
    p->u.iff.then = then;
    p->u.iff.elsee = elsee;
    return p;
}

A_stmt A_RepeatStmt(A_pos pos, A_exp test, A_stmtList repeat)
{
    A_stmt p = checked_malloc(sizeof(*p));
    p->kind = A_repeatStmt;
    p->pos = pos;
    p->u.repeat.test = test;
    p->u.repeat.repeat = repeat;
    return p;
}

A_stmt A_WhileStmt(A_pos pos, A_exp test, A_stmt whilee)
{
    A_stmt p = checked_malloc(sizeof(*p));
    p->kind = A_whileStmt;
    p->pos = pos;
    p->u.whilee.test = test;
    p->u.whilee.whilee = whilee;
    return p;
}

A_stmt A_ForStmt(A_pos pos, S_symbol var, A_exp init, A_exp change, A_stmt fordo)
{
    A_stmt p = checked_malloc(sizeof(*p));
    p->kind = A_forStmt;
    p->pos = pos;
    p->u.forr.var = var;
    p->u.forr.init = init;
    p->u.forr.change = change;
    p->u.forr.fordo = fordo;
    return p;
}

A_stmt A_CaseStmt(A_pos pos, A_exp test, A_caseList caselist)
{
    A_stmt p = checked_malloc(sizeof(*p));
    p->kind = A_caseStmt;
    p->pos = pos;
    p->u.casee.test = test;
    p->u.casee.caselist = caselist;
    return p;
}

A_stmt A_GotoStmt(A_pos pos, A_const des)
{
    A_stmt p = checked_malloc(sizeof(*p));
    p->kind = A_gotoStmt;
    p->pos = pos;
    p->u.gotoo.des = des;
    return p;
}

A_stmt A_CompoundStmt(A_pos pos, A_stmtList substmtList)
{
    A_stmt p = checked_malloc(sizeof(*p));
    p->kind = A_compoundStmt;
    p->pos = pos;
    p->u.compound.substmtList = substmtList;
    return p;
}

A_proc A_SysProc(A_pos pos, S_symbol proc, A_expList expList)
{
    A_proc p = checked_malloc(sizeof(*p));
    p->kind = A_sysProc;
    p->args = expList;
    p->u.proc = proc;
    return p;
}

A_proc A_Func(A_pos pos, S_symbol func, A_expList expList)
{
    A_proc p = checked_malloc(sizeof(*p));
    p->kind = A_func;
    p->args = expList;
    p->u.func = func;
    return p;
}

A_caseList A_CaseList(A_case head, A_caseList tail)
{
    A_caseList p = checked_malloc(sizeof(*p));
    p->head = head;
    p->tail = tail;
    return p;
}

A_case A_Case(A_pos pos, A_const constValue, S_symbol name, A_stmt casee)
{
    A_case p = checked_malloc(sizeof(*p));
    p->pos = pos;
    p->constValue = constValue;
    p->name = name;
    p->casee = casee;
    return p;
}

A_exp A_FuncExp(A_pos pos, A_proc func)
{
    A_exp p = checked_malloc(sizeof(*p));
    p->kind = A_funcExp;
    p->pos = pos;
    p->u.func = func;
    return p;
}

A_exp A_VarExp(A_pos pos, A_var var)
{
    A_exp p = checked_malloc(sizeof(*p));
    p->kind = A_varExp;
    p->pos = pos;
    p->u.var = var;
    return p;
}

A_exp A_ConstExp(A_pos pos, A_const constValue)
{
    A_exp p = checked_malloc(sizeof(*p));
    p->kind = A_constExp;
    p->pos = pos;
    p->u.constValue = constValue;
    return p;
}

A_exp A_OpExp(A_pos pos, A_oper oper, A_exp left, A_exp right)
{
    A_exp p = checked_malloc(sizeof(*p));
    p->kind = A_opExp;
    p->pos = pos;
    p->u.op.oper = oper;
    p->u.op.left = left;
    p->u.op.right = right;
    return p;
}

A_exp A_IfExp(A_pos pos, A_exp test, A_exp then, A_exp elsee)
{
    A_exp p = checked_malloc(sizeof(*p));
    p->kind = A_ifExp;
    p->pos = pos;
    p->u.iff.test = test;
    p->u.iff.then = then;
    p->u.iff.elsee = elsee;
    return p;
}

A_exp A_ParenExp(A_pos pos, A_exp paren)
{
    A_exp p = checked_malloc(sizeof(*p));
    p->kind = A_parenExp;
    p->pos = pos;
    p->u.paren = paren;
    return p;
}

A_expList A_ExpList(A_exp head, A_expList tail)
{
    A_expList p = checked_malloc(sizeof(*p));
    p->head = head;
    p->tail = tail;
    return p;
}




