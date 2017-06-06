//
// Created by 54179 on 2017/6/2.
//

#ifndef SPL_COMPILER_SEMANT_H
#define SPL_COMPILER_SEMANT_H

#include <memory>
#include <iostream>
#include <cstring>
#include "types.hpp"
#include "symbol.h"
#include "absyn.h"
#include "errormsg.h"
#include "env.hpp"
#include "util.h"

typedef std::unique_ptr<void> Expression;

class ExpressionAndType {
public:
    ExpressionAndType(std::shared_ptr<Type> type = Type::getNilType(), void *expression = nullptr) : type(type),
                                                                                                     expression(
                                                                                                             expression) {};

    std::shared_ptr<Type> getType() const {
        return type;
    }

    const Expression getExpression() const {
        return expression;
    }

private:
    std::shared_ptr<Type> type;

    Expression expression;
};

class Semant {
private:
    template<class T>
    static std::shared_ptr<T> *unpack(void *data) {
        return static_cast<std::shared_ptr<T> *>(data);
    }

    template<class T>
    static void *pack(T *data) {
        return new std::shared_ptr<T>(data);
    }

    static ExpressionAndType translateIf(S_table valueEnvironment, S_table typeEnvironment, _A_if_exp_ iff) {
        S_beginScope(valueEnvironment);
        S_beginScope(typeEnvironment);
        auto testExp = translateExpression(valueEnvironment, typeEnvironment, iff.test);
        if (testExp.getType() != Type::getIntegerType()) {
            EM_error(iff.test->pos, "if expression test should return int type!");
        } else {
            translateExpression(valueEnvironment, typeEnvironment, iff.then);
            if (iff.elsee != nullptr) {
                translateExpression(valueEnvironment, typeEnvironment, iff.elsee);
            }
        }
        S_endScope(valueEnvironment);
        S_endScope(typeEnvironment);
        return ExpressionAndType(Type::getVoidType(), nullptr);
    }

    static ExpressionAndType translateOp(S_table valueEnvironment, S_table typeEnvironment, _A_op_ op) {
        A_oper oper = op.oper;
        auto left = translateExpression(valueEnvironment, typeEnvironment, op.left);
        auto right = translateExpression(valueEnvironment, typeEnvironment, op.right);
        switch (oper) {
            case A_plusOp:
            case A_minusOp:
            case A_timesOp:
            case A_divideOp:
            case A_eqOp:
            case A_neqOp:
            case A_ltOp:
            case A_leOp:
            case A_gtOp:
            case A_geOp: {
                //TODO
            }
        }

        //the two operands' type should match TODO
        if (left.getType() != right.getType()) {
            EM_error(op.right->pos, "two operands' type mismatch!");
            return ExpressionAndType(Type::getNilType(), nullptr);
        }

        return ExpressionAndType(left.getType(), nullptr);
    }

    static ExpressionAndType
    translateSimpleVar(S_table valueEnvironment, S_table typeEnvironment, S_symbol simple, A_pos pos) {
        auto entry = unpack<VariableEnvironmentEntry>(S_look(valueEnvironment, simple));
        if (entry == nullptr) {
            EM_error(pos, "undefined variable %s", S_name(simple));
            return ExpressionAndType(Type::getNilType(), nullptr);
        } else if ((*entry)->getKind() == EnvironmentEntry::FunctionEntry) {
            EM_error(pos, "variable %s should not be a function", S_name(simple));
            return ExpressionAndType(Type::getNilType(), nullptr);
        }
        return ExpressionAndType((*entry)->getType(), nullptr);
    }

    static ExpressionAndType
    translateSubscriptVar(S_table valueEnvironment, S_table typeEnvironment, _A_subscript_ subscript) {
        auto entry = unpack<VariableEnvironmentEntry>(S_look(valueEnvironment, subscript.var));

        if (entry == nullptr) {
            EM_error(subscript.exp->pos, "undefined variable %s", S_name(subscript.var));
            return ExpressionAndType(Type::getNilType(), nullptr);
        }

        auto subExp = translateExpression(valueEnvironment, typeEnvironment, subscript.exp);

        if (subExp.getType() != (*entry)->getType()) {
            EM_error(subscript.exp->pos, "variable type and subscript type mismatch!");
            return ExpressionAndType(Type::getNilType(), nullptr);
        }

        return ExpressionAndType(subExp.getType(), nullptr);
    }

    static ExpressionAndType translateFieldVar(S_table valueEnvironment, S_table typeEnvironment, _A_field_ field, A_pos pos) {
        auto recordEnv = unpack<VariableEnvironmentEntry>(S_look(valueEnvironment, field.var));

        if(recordEnv == nullptr) {
            EM_error(pos, "undefined variable %s!", S_name(field.var));
            return ExpressionAndType(Type::getNilType(), nullptr);
        }

        auto record = std::static_pointer_cast<RecordType>((*recordEnv)->getType());
        auto &fieldList = record->getFieldList();
        for(auto _field : fieldList) {
            if(S_compare(_field.getName(), field.sym)) {
                return ExpressionAndType(_field.getType(), nullptr);
            }
        }
        return ExpressionAndType(Type::getNilType(), nullptr);
    }

    static ExpressionAndType
    translateRoutineDeclaration(S_table valueEnvironment, S_table typeEnvironment, _A_routine_ routinee) {
        auto resultExp = unpack()
        auto entry = new FunctionEnvironmentEntry()
    }

    static ExpressionAndType
    translateConstDec(S_table valueEnvironment, S_table typeEnvironment, _A_const_ constt) { //TODO const attr
        auto constExp = translateConst(valueEnvironment, typeEnvironment, constt.constValue);

        S_enter(valueEnvironment, constt.name, pack(new VariableEnvironmentEntry(constExp.getType())));

        return constExp;
    }

    static ExpressionAndType translateTypeDec(S_table valueEnvironment, S_table typeEnvironment, _A_type_ type) {
        auto typeExp = translateType(valueEnvironment, typeEnvironment, type.ty);

        S_enter(typeEnvironment, type.name, pack(new VariableEnvironmentEntry(typeExp.getType())));

        return typeExp;
    }

    static ExpressionAndType translateVarDec(S_table valueEnvironment, S_table typeEnvironment, A_field var) {
        auto varExp = translateType(valueEnvironment, typeEnvironment, var->ty);

        auto nameList = var->head;

        while (nameList != nullptr) {

            S_enter(valueEnvironment, nameList->head->name, pack(new VariableEnvironmentEntry(varExp.getType())));

            nameList = nameList->tail;
        }

        return varExp;
    }

    static ExpressionAndType
    translateRoutineDec(S_table valueEnvironment, S_table typeEnvironment, _A_routine_ routinee) {
        //TODO
    }

    static ExpressionAndType
    translateRecordType(S_table valueEnvironment, S_table typeEnvironment, A_fieldList fieldList) {
        auto recordType = std::shared_ptr<RecordType>();

        while (fieldList != nullptr) {
            auto field = fieldList->head;

            auto typeExp = translateType(valueEnvironment, typeEnvironment, field->ty);
            auto nameList = field->head;
            while(nameList != nullptr) {
                auto name = nameList->head;

                recordType->getFieldList().push_back(Field(name->name, typeExp.getType()));

                nameList = nameList->tail;
            }

            fieldList = fieldList->tail;
        }

        return ExpressionAndType(recordType, nullptr);
    }

    static ExpressionAndType translateArrayType(S_table valueEnvironment, S_table typeEnvironment, _A_array_ array) {
        auto typeExp = translateType(valueEnvironment, typeEnvironment, array.ty);
        auto arrayType = std::shared_ptr<ArrayType>();
        arrayType->getType() = typeExp.getType();

        return ExpressionAndType(arrayType, nullptr);
    }

    static ExpressionAndType translateProc(S_table valueEnvironment, S_table typeEnvironment, A_proc proc) {
        S_symbol procName;
        if (proc->kind == A_sysProc) {
            procName = proc->u.proc;
        } else {
            //A_func
            procName = proc->u.func;
        }

        auto env = unpack<FunctionEnvironmentEntry>(S_look(typeEnvironment, procName));
        if (env == nullptr) {
            EM_error(proc->pos, "can not find a function or procedure named %s!", S_name(procName));
            return ExpressionAndType(Type::getNilType(), nullptr);
        }

        auto &formals = (*env)->getFormals();
        auto &args = proc->args;

        auto iter = formals.begin();
        while (iter != formals.end()) {
            auto argEnv = translateExpression(valueEnvironment, typeEnvironment, args->head);
            if (argEnv.getType() != &(*iter)) {
                EM_error(proc->pos, "arguments type mismatch!");
                break;
            }
            iter++;
            args = args->tail;
        }
        if (args != nullptr) {
            EM_error(proc->pos, "arguments number mismatch!");
        }

        auto result = (*env)->getResult();
        return ExpressionAndType(result, nullptr);
    }

    static ExpressionAndType
    translateAssignStatement(S_table valueEnvironment, S_table typeEnvironment, _A_assign_ assign) {
        auto variable = translateVariable(valueEnvironment, typeEnvironment, assign.var);
        auto expression = translateExpression(valueEnvironment, typeEnvironment, assign.exp);
        if (variable.getType() == nullptr || expression.getType() == nullptr ||
            variable.getType() != expression.getType()) {
            EM_error(assign.var->pos, "variable type and expression type mismatch!");
        }
        return ExpressionAndType(variable.getType(), nullptr);
    }

    static ExpressionAndType translateIfStatement(S_table valueEnvironment, S_table typeEnvironment, _A_if_stm_ iff) {
        S_beginScope(valueEnvironment);
        S_beginScope(typeEnvironment);
        auto testExp = translateExpression(valueEnvironment, typeEnvironment, iff.test);
        if (testExp.getType() != Type::getIntegerType()) {
            EM_error(iff.test->pos, "if expression test should return int type!");
        } else {
            translateStatement(valueEnvironment, typeEnvironment, iff.then);
            if (iff.elsee != nullptr) {
                translateStatement(valueEnvironment, typeEnvironment, iff.elsee);
            }
        }
        S_endScope(valueEnvironment);
        S_endScope(typeEnvironment);
        return ExpressionAndType(Type::getVoidType(), nullptr);
    }

    static ExpressionAndType
    translateRepeatStatement(S_table valueEnvironment, S_table typeEnvironment, _A_repeat_ repeat) {
        S_beginScope(valueEnvironment);
        S_beginScope(typeEnvironment);
        auto testExp = translateExpression(valueEnvironment, typeEnvironment, repeat.test);
        if (testExp.getType() != Type::getIntegerType()) {
            EM_error(repeat.test->pos, "repeat expression test should return int type!");
        } else {
            auto &statementList = repeat.repeat;
            while (statementList != nullptr) {
                translateStatement(valueEnvironment, typeEnvironment, statementList->head);
                statementList = statementList->tail;
            }
        }

        S_endScope(valueEnvironment);
        S_endScope(typeEnvironment);
        return ExpressionAndType(Type::getVoidType(), nullptr);
    }

    static ExpressionAndType
    translateWhileStatement(S_table valueEnvironment, S_table typeEnvironment, _A_while_ whilee) {
        S_beginScope(valueEnvironment);
        S_beginScope(typeEnvironment);

        auto testExp = translateExpression(valueEnvironment, typeEnvironment, whilee.test);
        if (testExp.getType() != Type::getIntegerType())
            EM_error(whilee.test->pos, "while expression test should return int type!");
        else
            translateStatement(valueEnvironment, typeEnvironment, whilee.whilee);

        S_endScope(valueEnvironment);
        S_endScope(typeEnvironment);
        return ExpressionAndType(Type::getVoidType(), nullptr);
    }

    static ExpressionAndType translateForStatement(S_table valueEnvironment, S_table typeEnvironment, _A_for_ forr) {
        S_beginScope(valueEnvironment);
        S_beginScope(typeEnvironment);

        auto initExp = translateExpression(valueEnvironment, typeEnvironment, forr.init);
        S_enter(valueEnvironment, forr.var, pack(new VariableEnvironmentEntry(initExp.getType())));

        auto changeExp = translateExpression(valueEnvironment, typeEnvironment, forr.change);

        if (initExp.getType() != changeExp.getType())
            EM_error(forr.change->pos, "variable init value type mismatch its change type!");

        S_endScope(valueEnvironment);
        S_endScope(typeEnvironment);
        return ExpressionAndType(Type::getVoidType(), nullptr);
    }

    static ExpressionAndType translateCaseStatement(S_table valueEnvironment, S_table typeEnvironment, _A_case_ casee) {
        S_beginScope(valueEnvironment);
        S_beginScope(typeEnvironment);

        auto testExp = translateExpression(valueEnvironment, typeEnvironment, casee.test);

        auto caseList = casee.caselist;
        while (caseList != nullptr) {
            auto constExp = translateConst(valueEnvironment, typeEnvironment, caseList->head->constValue);
            auto varExp = unpack<VariableEnvironmentEntry>(S_look(valueEnvironment, caseList->head->name));

            if ((varExp && (*varExp)->getType() != testExp.getType()) ||
                constExp.getType() != testExp.getType()) {
                EM_error(caseList->head->pos, "const value type mismatch type of test of case expression!");
                break;
            } else {
                translateStatement(valueEnvironment, typeEnvironment, caseList->head->casee);
            }

            caseList = caseList->tail;
        }

        S_endScope(valueEnvironment);
        S_endScope(typeEnvironment);
        return ExpressionAndType(Type::getVoidType(), nullptr);
    }

    static ExpressionAndType translateGotoType(S_table valueEnvironment, S_table typeEnvironment, _A_goto_ gotoo) {
        //TODO check if label exists
        return ExpressionAndType(Type::getVoidType(), nullptr);
    }

    static ExpressionAndType
    translateCompoundStatement(S_table valueEnvironment, S_table typeEnvironment, _A_compound_ compound) {
        S_beginScope(valueEnvironment);
        S_beginScope(typeEnvironment);

        auto statementList = compound.substmtList;
        while (statementList != nullptr) {
            translateStatement(valueEnvironment, typeEnvironment, statementList->head);
            statementList = statementList->tail;
        }

        S_endScope(valueEnvironment);
        S_endScope(typeEnvironment);
        return ExpressionAndType(Type::getVoidType(), nullptr);
    }

    static ExpressionAndType
    translateSyscon(S_table valueEnvironment, S_table typeEnvironment, S_symbol syscon, A_pos pos) {
        auto sysconExp = unpack<VariableEnvironmentEntry>(S_look(valueEnvironment, syscon));
        if (!sysconExp) {
            EM_error(pos, "Can not find a const variable named %s!", S_name(syscon));
            return ExpressionAndType(Type::getNilType(), nullptr);
        }
        return ExpressionAndType((*sysconExp)->getType(), nullptr);
    }

    static ExpressionAndType translateString(S_table valueEnvironment, S_table typeEnvironment, string string) {
        //TODO
        return ExpressionAndType(Type::getCharType(), nullptr);
    }

public:
    static ExpressionAndType translateConst(S_table valueEnvironment, S_table typeEnvironment, A_const constValue) {
        switch (constValue->kind) {
            case A_int:
                return ExpressionAndType(Type::getIntegerType(), nullptr);
            case A_real:
                return ExpressionAndType(Type::getRealType(), nullptr);
            case A_char:
                return ExpressionAndType(Type::getCharType(), nullptr);
            case A_string:
                return translateString(valueEnvironment, typeEnvironment, constValue->u.stringg);
            case A_syscon:
                return translateSyscon(valueEnvironment, typeEnvironment, constValue->u.syscon, constValue->pos);
            default:
                EM_error(constValue->pos, "Not recognized const value!");
                return ExpressionAndType(Type::getNilType(), nullptr);
        }
    }

    static ExpressionAndType translateStatement(S_table valueEnvironment, S_table typeEnvironment, A_stmt statement) {
        switch (statement->kind) {
            case A_labelStmt:
                return translateStatement(valueEnvironment, typeEnvironment, statement->u.label.stmt);
            case A_assignStmt:
                return translateAssignStatement(valueEnvironment, typeEnvironment, statement->u.assign);
            case A_procStmt:
                return translateProc(valueEnvironment, typeEnvironment, statement->u.proc);
            case A_ifStmt:
                return translateIfStatement(valueEnvironment, typeEnvironment, statement->u.iff);
            case A_repeatStmt:
                return translateRepeatStatement(valueEnvironment, typeEnvironment, statement->u.repeat);
            case A_whileStmt:
                return translateWhileStatement(valueEnvironment, typeEnvironment, statement->u.whilee);
            case A_forStmt:
                return translateForStatement(valueEnvironment, typeEnvironment, statement->u.forr);
            case A_caseStmt:
                return translateCaseStatement(valueEnvironment, typeEnvironment, statement->u.casee);
            case A_gotoStmt:
                return translateGotoType(valueEnvironment, typeEnvironment, statement->u.gotoo);
            case A_compoundStmt:
                return translateCompoundStatement(valueEnvironment, typeEnvironment, statement->u.compound);
            default:
                EM_error(statement->pos, "Not recognized statement type! Type id: %d", statement->kind);
                return ExpressionAndType(Type::getNilType(), nullptr);
        }
    }

    static ExpressionAndType translateType(S_table valueEnvironment, S_table typeEnvironment, A_ty type) {
        switch (type->kind) {
            case A_simTy:
                return translateSimpleType(valueEnvironment, typeEnvironment, type->u.simple);
            case A_recordTy:
                return translateRecordType(valueEnvironment, typeEnvironment, type->u.record);
            case A_arrayTy:
                return translateArrayType(valueEnvironment, typeEnvironment, type->u.array);
            default:
                EM_error(type->pos, "Not recognized type! type kind: %d", type->kind);
                return ExpressionAndType(Type::getNilType(), nullptr);
        }
    }

    static ExpressionAndType
    translateDeclaration(S_table valueEnvironment, S_table typeEnvironment, A_dec declaration) {
        switch (declaration->kind) {
            case A_constDec:
                return translateConstDec(valueEnvironment, typeEnvironment, declaration->u.constt);
            case A_typeDec:
                return translateTypeDec(valueEnvironment, typeEnvironment, declaration->u.type);
            case A_varDec:
                return translateVarDec(valueEnvironment, typeEnvironment, declaration->u.var.var);
            case A_routineDec:
                return translateRoutineDec(valueEnvironment, typeEnvironment, declaration->u.routine);
            default:
                EM_error(declaration->pos, "Not recognized declaration type! Type id: %d", declaration->kind);
                return ExpressionAndType(Type::getNilType(), nullptr);
        }
    }

    static ExpressionAndType
    translateSimpleType(S_table valueEnvironment, S_table typeEnvironment, A_simpleTy simpleType) {
        switch (simpleType->kind) {
            case A_sysTy:
            case A_singleTy:
            case A_doubleCTy:
            case A_doubleNTy:
            case A_listTy:
            default:
                EM_error(simpleType->pos, "Not recognized simple type kind: %d", simpleType->kind);
                return ExpressionAndType(Type::getNilType(), nullptr);
        }
    }

    static ExpressionAndType translateVariable(S_table valueEnvironment, S_table typeEnvironment, A_var variable) {
        switch (variable->kind) {
            case A_constVar:
                //TODO const attr
            case A_simpleVar:
                return translateSimpleVar(valueEnvironment, typeEnvironment, variable->u.simple, variable->pos);
            case A_fieldVar:
                return translateFieldVar(valueEnvironment, typeEnvironment, variable->u.field);
            case A_subscriptVar:
                return translateSubscriptVar(valueEnvironment, typeEnvironment, variable->u.subscript);
            default:
                EM_error(variable->pos, "Not recognized variable type! Type id: %d", variable->kind);
                return ExpressionAndType(Type::getNilType(), nullptr);
        }
    }

    static ExpressionAndType translateExpression(S_table valueEnvironment, S_table typeEnvironment, A_exp expression) {
        switch (expression->kind) {
            case A_funcExp:
                return translateProc(valueEnvironment, typeEnvironment, expression->u.func);
            case A_varExp:
                return translateVariable(valueEnvironment, typeEnvironment, expression->u.var);
            case A_constExp:
                return translateConst(valueEnvironment, typeEnvironment, expression->u.constValue);
            case A_opExp:
                return translateOp(valueEnvironment, typeEnvironment, expression->u.op);
            case A_ifExp:
                return translateIf(valueEnvironment, typeEnvironment, expression->u.iff);
            default:
                EM_error(expression->pos, "Not recognized expression type! Type id: %d", expression->kind);
                return ExpressionAndType(Type::getNilType(), nullptr);
        }
    }
};

#endif //SPL_COMPILER_SEMANT_H
