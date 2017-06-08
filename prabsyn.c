//
//  prabsyn.c
//  SPL-compiler
//
//  Created by cai on 2017/6/3.
//  Copyright © 2017年 cai. All rights reserved.
//

/*
 * prabsyn.c - Print Abstract Syntax data structures. Most functions
 *           handle an instance of an abstract syntax rule.
 */

#include <stdio.h>
#include "util.h"
#include "symbol.h" /* symbol table data structures */
#include "absyn.h"  /* abstract syntax data structures */
#include "prabsyn.h" /* function prototype */

/* local function prototypes */
static void pr_routine(FILE *out, A_routine v, int d);
static void pr_routineHead(FILE *out, A_routineHead v, int d);
static void pr_decPart(FILE *out, A_decPart v, int d);
static void pr_decList(FILE *out, A_decList v, int d);
static void pr_dec(FILE *out, A_dec v, int d);
static void pr_const(FILE *out, A_const v, int d);
static void pr_name(FILE *out, A_name v, int d);
static void pr_nameList(FILE *out, A_nameList v, int d);
static void pr_field(FILE *out, A_field v, int d);
static void pr_fieldList(FILE *out, A_fieldList v, int d);
static void pr_ty(FILE *out, A_ty v, int d);
static void pr_simpleTy(FILE *out, A_simpleTy v, int d);
static void pr_routineBody(FILE *out, A_routineBody v, int d);
static void pr_stmtList(FILE *out, A_stmtList v, int d);
static void pr_var(FILE *out, A_var v, int d);
static void pr_stmt(FILE *out, A_stmt v, int d);
static void pr_proc(FILE *out, A_proc v, int d);
static void pr_caseList(FILE *out, A_caseList v, int d);
static void pr_case(FILE *out, A_case v, int d);
static void pr_exp(FILE *out, A_exp v, int d);
static void pr_expList(FILE *out, A_expList v, int d);


static void indent(FILE *out, int d) {
    int i;
    for (i = 0; i <= d; i++) fprintf(out, " ");
}

void pr_pro(FILE *out, A_pro v, int d)
{
    indent(out, d);
    fprintf(out, "pro(%s)", S_name(v->name));fprintf(out, "\n");
    pr_routine(out, v->routine, d+1);
}

static void pr_routine(FILE *out, A_routine v, int d)
{
    indent(out, d);
    fprintf(out, "routine : \n");
    pr_routineHead(out, v->head, d+1);fprintf(out, "\n");
    pr_routineBody(out, v->body, d+1);
    
}

static void pr_routineHead(FILE *out, A_routineHead v, int d)
{
    indent(out, d);
    fprintf(out, "routineHead : \n");
    indent(out, d+1);
    fprintf(out, "labelPart : \n");
    pr_decPart(out, v->labelPart, d+2);
    indent(out, d+1);
    fprintf(out, "constPart : \n");
    pr_decPart(out, v->constPart, d+2);
    indent(out, d+1);
    fprintf(out, "typePart : \n");
    pr_decPart(out, v->typePart, d+2);
    indent(out, d+1);
    fprintf(out, "varPart : \n");
    pr_decPart(out, v->varPart, d+2);
    indent(out, d+1);
    fprintf(out, "routinePart : \n");
    pr_decPart(out, v->routinePart, d+2);
}

static void pr_decPart(FILE *out, A_decPart v, int d)
{
    indent(out, d);
    if(v)
    {
        fprintf(out, "decList : \n");
        pr_decList(out, v->head, d+1);
    }
    else
        fprintf(out, "\n");
        

}

static void pr_decList(FILE *out, A_decList v, int d)
{
    if(v)
    {
        pr_dec(out, v->head, d+1); fprintf(out, "\n");
        pr_decList(out, v->tail, d+1);
    }
    else
        fprintf(out, "\n");
}

static void pr_dec(FILE *out, A_dec v, int d)
{
    indent(out, d);
    switch (v->kind) {
        case A_constDec:
            fprintf(out, "constDec : \n");
            indent(out, d+1);
            fprintf(out, "%s\n", S_name(v->u.constt.name));
            pr_const(out, v->u.constt.constValue, d+1);
            break;
        case A_varDec:
            fprintf(out, "varDec : \n");
            pr_field(out, v->u.var.var, d+1);
            break;
        case A_typeDec:
            fprintf(out, "typeDec : \n");
            indent(out, d+1);
            fprintf(out, "%s\n", S_name(v->u.type.name));
            pr_ty(out, v->u.type.ty, d+1);
            break;
        case A_routineDec:
            fprintf(out, "routineDec : \n");
            indent(out, d+1);
            fprintf(out, "%s : \n", S_name(v->u.routine.name));
            indent(out, d+2);
            fprintf(out, "FieldList : \n");
            pr_fieldList(out, v->u.routine.params, d+3); fprintf(out, "\n");
            pr_simpleTy(out, v->u.routine.simplety, d+2); fprintf(out, "\n");
            pr_routine(out, v->u.routine.subroutine, d+2);
            break;
        default:
            break;
    }
    
}
static void pr_const(FILE *out, A_const v, int d)
{
    indent(out, d);
    switch (v->kind) {
        case A_int:
            fprintf(out, "Int : \n");
            indent(out, d+1);
            fprintf(out, "%d\n", v->u.intt);
            break;
        case A_real:
            fprintf(out, "Real : \n");
            indent(out, d+1);
            fprintf(out, "%f\n", v->u.reall);
            break;
        case A_char:
            fprintf(out, "Char : \n");
            indent(out, d+1);
            fprintf(out, "%c\n", v->u.charr);
            break;
        case A_string:
            fprintf(out, "String : \n");
            indent(out, d+1);
            fprintf(out, "%s\n", v->u.stringg);
            break;
        case A_syscon:
            fprintf(out, "Syscon : \n");
            indent(out, d+1);
            fprintf(out, "%s\n", S_name(v->u.syscon));
            break;
        default:
            break;
    }
}

static void pr_name(FILE *out, A_name v, int d)
{
    indent(out, d);
    fprintf(out, "Name : ");
    fprintf(out, "%s\n", S_name(v->name));
    
}
static void pr_nameList(FILE *out, A_nameList v, int d)
{
    if(v)
    {
        pr_name(out, v->head, d+1); fprintf(out, "\n");
        pr_nameList(out, v->tail, d+1);
    }
    else
        fprintf(out, "\n");
}
static void pr_field(FILE *out, A_field v, int d)
{
    indent(out, d);
    fprintf(out, "Field : \n");
    indent(out, d+1);
    fprintf(out, "NameList : \n");
    pr_nameList(out, v->head, d+1);
    indent(out, d+1);
    fprintf(out, "Type : \n");
    pr_ty(out, v->ty, d+2);
    
}
static void pr_fieldList(FILE *out, A_fieldList v, int d)
{
    if(v)
    {
        pr_field(out, v->head, d+1);fprintf(out, "\n");
        pr_fieldList(out, v->tail, d+1);
    }
    else
        fprintf(out, "\n");
}
static void pr_ty(FILE *out, A_ty v, int d)
{
    indent(out, d);
    switch (v->kind) {
        case A_simTy:
            fprintf(out, "SimpleTy : \n");
            pr_simpleTy(out, v->u.simple, d+1);
            break;
        case A_recordTy:
            fprintf(out, "RecordTy : \n");
            indent(out, d+1);
            fprintf(out, "Fieldlist : \n");
            pr_fieldList(out, v->u.record, d+1);
            break;
        case A_arrayTy:
            fprintf(out, "ArrayTy : \n");
            pr_simpleTy(out, v->u.array.simple, d+1);fprintf(out, "\n");
            pr_ty(out, v->u.array.ty, d+1);
            break;
        default:
            break;
    }
    
}
static void pr_simpleTy(FILE *out, A_simpleTy v, int d)
{
    if(v)
    {
        indent(out, d);
        switch (v->kind) {
            case A_sysTy:
            fprintf(out, "SysTy : \n");
            indent(out, d+1);
            fprintf(out, "%s\n", S_name(v->u.systy));
            break;
            case A_singleTy:
            fprintf(out, "SingleTy : \n");
            indent(out, d+1);
            fprintf(out, "%s\n", S_name(v->u.single));
            break;
            case A_doubleCTy:
            fprintf(out, "doubleCTy : \n");
            pr_exp(out, v->u.doubleC.left, d+1); fprintf(out, "\n");
            pr_exp(out, v->u.doubleC.right, d+1);
            break;
            case A_doubleNTy:
            fprintf(out, "doubleNTy : \n");
            indent(out, d+1);
            fprintf(out, "%s\n", S_name(v->u.doubleN.left));fprintf(out, "\n");
            indent(out, d+1);
            fprintf(out, "%s\n", S_name(v->u.doubleN.right));
            break;
            case A_listTy:
            fprintf(out, "ListTy : \n");
            indent(out, d+1);
            fprintf(out, "NameList : \n");
            pr_nameList(out, v->u.nameList, d+1);
            break;
            default:
            break;
        }
    }
    else
        fprintf(out, "\n");
}
static void pr_routineBody(FILE *out, A_routineBody v, int d)
{
    indent(out, d);
    fprintf(out, "routineBody : \n");
    pr_stmt(out, v->head, d+1);
}
static void pr_stmtList(FILE *out, A_stmtList v, int d)
{
    if(v)
    {
        pr_stmt(out, v->head, d+1); fprintf(out, "\n");
        pr_stmtList(out, v->tail, d+1);
    }
    else
        fprintf(out, "\n");
}
static void pr_var(FILE *out, A_var v, int d)
{
    indent(out, d);
    switch (v->kind) {
        case A_constVar:
            fprintf(out, "ConstVar : \n");
            pr_const(out, v->u.constValue, d+1);
            break;
        case A_simpleVar:
            fprintf(out, "simpleVar : \n");
            indent(out, d+1);
            fprintf(out, "%s\n", S_name(v->u.simple));
            break;
        case A_fieldVar:
            fprintf(out, "FieldVar : \n");
            indent(out, d+1);
            fprintf(out, "%s\n", S_name(v->u.field.var));
            indent(out, d+1);
            fprintf(out, "%s\n", S_name(v->u.field.sym));
            break;
        case A_subscriptVar:
            fprintf(out, "Subscriptvar : \n");
            indent(out, d+1);
            fprintf(out, "%s\n", S_name(v->u.subscript.var));
            pr_exp(out, v->u.subscript.exp, d+1);
            break;
        default:
            break;
    }
    
}
static void pr_stmt(FILE *out, A_stmt v, int d)
{
    if(v)
    {
        indent(out, d);
        switch (v->kind) {
            case A_labelStmt:
            fprintf(out, "LabelStmt : \n");
            pr_const(out, v->u.label.label, d+1); fprintf(out, "\n");
            pr_stmt(out, v->u.label.stmt, d+1);
            break;
            case A_assignStmt:
            fprintf(out, "AssignStmt : \n");
            pr_var(out, v->u.assign.var, d+1); fprintf(out, "\n");
            pr_exp(out, v->u.assign.exp, d+1);
            break;
            case A_procStmt:
            fprintf(out, "ProcStmt : \n");
            pr_proc(out, v->u.proc, d+1);
            break;
            case A_ifStmt:
            fprintf(out, "IfStmt : \n");
            pr_exp(out, v->u.iff.test, d+1); fprintf(out, "\n");
            pr_stmt(out, v->u.iff.then, d+1); fprintf(out, "\n");
            pr_stmt(out, v->u.iff.elsee, d+1);
            break;
            case A_whileStmt:
            fprintf(out, "WhileStmt : \n");
            pr_exp(out, v->u.whilee.test, d+1); fprintf(out, "\n");
            pr_stmt(out, v->u.whilee.whilee, d+1);
            break;
            case A_repeatStmt:
            fprintf(out, "RepeatStmt : \n");
            pr_exp(out, v->u.repeat.test, d+1); fprintf(out, "\n");
            fprintf(out, "StmtList : \n");
            pr_stmtList(out, v->u.repeat.repeat, d+1);
            break;
            case A_forStmt:
            fprintf(out, "forStmt : \n");
            indent(out, d+1);
            fprintf(out, "%s\n", S_name(v->u.forr.var));
            pr_exp(out, v->u.forr.init, d+1); fprintf(out, "\n");
            pr_exp(out, v->u.forr.change, d+1); fprintf(out, "\n");
            pr_stmt(out, v->u.forr.fordo, d+1);
            break;
            case A_caseStmt:
            fprintf(out, "caseStmt : \n");
            pr_exp(out, v->u.casee.test, d+1); fprintf(out, "\n");
            indent(out, d);
            fprintf(out, "CaseList : \n");
            pr_caseList(out, v->u.casee.caselist, d+1);
            break;
            case A_gotoStmt:
            fprintf(out, "GotoStmt : \n");
            pr_const(out, v->u.gotoo.des, d+1);
            break;
            case A_compoundStmt:
            fprintf(out, "CompoundStmt : \n");
            indent(out, d+1);
            fprintf(out, "StmtList : \n");
            pr_stmtList(out, v->u.compound.substmtList, d+1);
            break;
            default:
            break;
        }
    }
    else
        fprintf(out, "\n");
    
}
static void pr_proc(FILE *out, A_proc v, int d)
{
    indent(out, d+1);
    switch (v->kind) {
        case A_sysProc:
            fprintf(out, "SysProc : \n");
            indent(out, d+1);
            fprintf(out, "%s\n", S_name(v->u.proc));
            indent(out, d+1);
            fprintf(out, "ArgsList : \n");
            pr_expList(out, v->args, d+1);
            break;
        case A_func:
            fprintf(out, "Func : \n");
            indent(out, d+1);
            fprintf(out, "%s\n", S_name(v->u.func));
            indent(out, d+1);
            fprintf(out, "ArgsList : \n");
            pr_expList(out, v->args, d+1);
            break;
        default:
            break;
    }
    
}
static void pr_caseList(FILE *out, A_caseList v, int d)
{
    if(v)
    {
        pr_case(out, v->head, d+1);fprintf(out, "\n");
        pr_caseList(out, v->tail, d+1);
    }
    else
        fprintf(out, "\n");
}
static void pr_case(FILE *out, A_case v, int d)
{
    indent(out, d);
    fprintf(out, "Case : \n");
    if(v->name)
    {
        indent(out, d);
        fprintf(out, "%s\n", S_name(v->name));
    }
    else
        pr_const(out, v->constValue, d+1); fprintf(out, "\n");
    pr_stmt(out, v->casee, d+1);
}

static char str_oper[][12] = {
    "PLUS", "MINUS", "TIMES", "MOD", "DIVIDE",
    "EQUAL", "NOTEQUAL", "LESSTHAN", "LESSEQ", "GREAT", "GREATEQ"};
static void pr_oper(FILE *out, A_oper d) {
    fprintf(out, "%s", str_oper[d]);
}

static void pr_exp(FILE *out, A_exp v, int d)
{
    indent(out, d);
    switch (v->kind) {
        case A_funcExp:
            fprintf(out, "FuncExp : \n");
            pr_proc(out, v->u.func, d+1);
            break;
        case A_varExp:
            fprintf(out, "VarExp : \n");
            pr_var(out, v->u.var, d+1);
            break;
        case A_constExp:
            fprintf(out, "ConstExp : \n");
            pr_const(out, v->u.constValue, d+1);
            break;
        case A_opExp:
            fprintf(out, "OpExp : \n");
            indent(out, d+1); pr_oper(out, v->u.op.oper); fprintf(out, "\n");
            pr_exp(out, v->u.op.left, d+1); fprintf(out, "\n");
            pr_exp(out, v->u.op.right, d+1);
            break;
        case A_ifExp:
            fprintf(out, "IfExp : \n");
            pr_exp(out, v->u.iff.test, d+1);fprintf(out, "\n");
            pr_exp(out, v->u.iff.then, d+1);fprintf(out, "\n");
            pr_exp(out, v->u.iff.elsee, d+1);
            break;
        case A_parenExp:
            fprintf(out, "parenExp : \n");
            pr_exp(out, v->u.paren, d+1);
            break;
        default:
            break;
    }
    
}
static void pr_expList(FILE *out, A_expList v, int d)
{
    if(v)
    {
        pr_exp(out, v->head, d+1);
        pr_expList(out, v->tail, d+1);
    }
    else
        fprintf(out, "\n");
}

