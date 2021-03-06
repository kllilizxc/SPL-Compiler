//
// Created by 54179 on 2017/6/2.
//

#ifndef SPL_COMPILER_SEMANT_H
#define SPL_COMPILER_SEMANT_H

#include <memory>
#include <iostream>
#include <cstring>
#include "types.hpp"
#include "env.hpp"
#include "ir.hpp"
#include "absyn.h"

extern "C" {
#include "symbol.h"
#include "absyn.h"
#include "errormsg.h"
#include "util.h"
};


typedef IR *Expression;

class ExpressionAndType {
public:
    ExpressionAndType(std::shared_ptr<VarType> type = VarType::getNilType(), Expression
    expression = nullptr, bool isConst = false) : type(type),
                                                  expression(expression), isConst(isConst) {};

    std::shared_ptr<VarType> getType() {
        return type;
    }

    Expression &getExpression() {
        return expression;
    }

    void setExpression(Expression another) {
        expression = another;
    }

    bool isConst;

private:
    std::shared_ptr<VarType> type;

    Expression expression;
};

class Semant {
private:
    template<class
    T>
    static std::shared_ptr<T> *unpack(void *data) {
        return static_cast < std::shared_ptr<T> * > (data);
    }

    template<class
    T>
    static void *pack(T *data) {
        return new
                std::shared_ptr<T>(data);
    }

    static ExpressionAndType translateIf(S_table valueEnvironment, S_table typeEnvironment, _A_if_exp_ iff) {
        S_beginScope(valueEnvironment);
        S_beginScope(typeEnvironment);
        auto testExp = translateExpression(valueEnvironment, typeEnvironment, iff.test);
        ExpressionAndType thenExp, elseExp;
        if (testExp.getType() != VarType::getIntegerType()) {
            EM_error(iff.test->pos, "if expression test should return int type!");
        } else {
            thenExp = translateExpression(valueEnvironment, typeEnvironment, iff.then);
            if (iff.elsee != nullptr) {
                elseExp = translateExpression(valueEnvironment, typeEnvironment, iff.elsee);
            }
        }
        S_endScope(valueEnvironment);
        S_endScope(typeEnvironment);
        return ExpressionAndType(VarType::getVoidType(),
                                 new IfIR(testExp.getExpression(), thenExp.getExpression(), elseExp.getExpression()));
    }

    static bool isSmpleType(std::shared_ptr<VarType> type) {
        return type == VarType::getIntegerType() || type == VarType::getBooleanType() ||
               type == VarType::getRealType() || type == VarType::getCharType();
    }

    static bool isRealType(std::shared_ptr<VarType> type) {
        return type == VarType::getRealType();
    }

    static std::shared_ptr<VarType> &getBiggestType(std::shared_ptr<VarType> type1, std::shared_ptr<VarType> type2) {
        assert(isSmpleType(type1) && isSmpleType(type2));

        if (type1 == VarType::getRealType() || type2 == VarType::getRealType())
            return VarType::getRealType();
        else
            return VarType::getIntegerType();
    }

    static ExpressionAndType translateOp(S_table valueEnvironment, S_table typeEnvironment, _A_op_ op) {
        A_oper oper = op.oper;

        auto left = translateExpression(valueEnvironment, typeEnvironment, op.left);
        auto right = translateExpression(valueEnvironment, typeEnvironment, op.right);

        auto leftISReal = isRealType(left.getType());
        auto rightIsReal = isRealType(right.getType());

        if (oper == A_divideOp) {
            if (right.getType() != VarType::getIntegerType()) {
                EM_error(op.right->pos, "the divider should be an integer!");
                return ExpressionAndType(VarType::getNilType(), nullptr);
            } else if (right.isConst) {
                auto rightVal = static_cast<ConstIntIR *>(right.getExpression());
                if (!rightVal || rightVal->getVal() == 0) {
                    EM_error(op.right->pos, "the divider should be an integer and can not be 0!");
                    return ExpressionAndType(VarType::getNilType(), nullptr);
                }
            }
        }

        //optimize constant value
        if (right.isConst && left.isConst) {
            if (leftISReal && rightIsReal) {
                auto rightVal = static_cast<ConstRealIR *>(right.getExpression())->getVal();
                auto leftVal = static_cast<ConstRealIR *>(left.getExpression())->getVal();

                double result = 0;

                switch (op.oper) {
                    case A_plusOp:
                        result = leftVal + rightVal;
                        break;
                    case A_minusOp:
                        result = leftVal - rightVal;
                        break;
                    case A_timesOp:
                        result = leftVal * rightVal;
                        break;
                    case A_divideOp:
                        result = leftVal / rightVal;
                        break;
                    case A_eqOp:
                        return ExpressionAndType(VarType::getIntegerType(), new ConstIntIR(leftVal == rightVal), true);
                    case A_neqOp:
                        return ExpressionAndType(VarType::getIntegerType(), new ConstIntIR(leftVal != rightVal), true);
                    case A_ltOp:
                        return ExpressionAndType(VarType::getIntegerType(), new ConstIntIR(leftVal < rightVal), true);
                    case A_leOp:
                        return ExpressionAndType(VarType::getIntegerType(), new ConstIntIR(leftVal <= rightVal), true);
                    case A_gtOp:
                        return ExpressionAndType(VarType::getIntegerType(), new ConstIntIR(leftVal > rightVal), true);
                    case A_geOp:
                        return ExpressionAndType(VarType::getIntegerType(), new ConstIntIR(leftVal >= rightVal), true);
                    default:
                        EM_error(op.left->pos, "unrecognized operator!");
                        break;
                }

                return ExpressionAndType(right.getType(), new ConstRealIR(result), true);
            } else if (!leftISReal && !rightIsReal) {
                auto rightVal = static_cast<ConstIntIR *>(right.getExpression())->getVal();
                auto leftVal = static_cast<ConstIntIR *>(left.getExpression())->getVal();

                int result = 0;

                switch (op.oper) {
                    case A_plusOp:
                        result = leftVal + rightVal;
                        break;
                    case A_minusOp:
                        result = leftVal - rightVal;
                        break;
                    case A_timesOp:
                        result = leftVal * rightVal;
                        break;
                    case A_divideOp:
                        result = leftVal / rightVal;
                        break;
                    case A_eqOp:
                        return ExpressionAndType(VarType::getIntegerType(), new ConstIntIR(leftVal == rightVal), true);
                    case A_neqOp:
                        return ExpressionAndType(VarType::getIntegerType(), new ConstIntIR(leftVal != rightVal), true);
                    case A_ltOp:
                        return ExpressionAndType(VarType::getIntegerType(), new ConstIntIR(leftVal < rightVal), true);
                    case A_leOp:
                        return ExpressionAndType(VarType::getIntegerType(), new ConstIntIR(leftVal <= rightVal), true);
                    case A_gtOp:
                        return ExpressionAndType(VarType::getIntegerType(), new ConstIntIR(leftVal >= rightVal), true);
                    case A_geOp:
                        return ExpressionAndType(VarType::getIntegerType(), new ConstIntIR(leftVal > rightVal), true);
                    default:
                        EM_error(op.left->pos, "unrecognized operator!");
                        break;
                }

                return ExpressionAndType(right.getType(), new ConstIntIR(result), true);
            } else if (op.oper == A_minusOp && !leftISReal) {
                //check negtive
                auto leftVal = static_cast<ConstIntIR *>(left.getExpression())->getVal();
                if (leftVal == 0) {
                    auto rightVal = static_cast<ConstRealIR *>(right.getExpression())->getVal();
                    return ExpressionAndType(VarType::getRealType(), new ConstRealIR(-rightVal),
                                             true);
                }
            }
        }

        IR *ir = nullptr;
        if (leftISReal && rightIsReal) {
            switch (op.oper) {
                case A_plusOp:
                    ir = new FOpPlusIR(left.getExpression(), right.getExpression());
                    break;
                case A_minusOp:
                    ir = new FOpMinusIR(left.getExpression(), right.getExpression());
                    break;
                case A_timesOp:
                    ir = new FOpTimesIR(left.getExpression(), right.getExpression());
                    break;
                case A_divideOp:
                    ir = new FOpDivideIR(left.getExpression(), right.getExpression());
                    break;
                case A_eqOp:
                    ir = new FOpEqIR(left.getExpression(), right.getExpression());
                    break;
                case A_neqOp:
                    ir = new FOpNeqIR(left.getExpression(), right.getExpression());
                    break;
                case A_ltOp:
                    ir = new FOpLtIR(left.getExpression(), right.getExpression());
                    break;
                case A_leOp:
                    ir = new FOpLeIR(left.getExpression(), right.getExpression());
                    break;
                case A_gtOp:
                    ir = new FOpGtIR(left.getExpression(), right.getExpression());
                    break;
                case A_geOp:
                    ir = new FOpGeIR(left.getExpression(), right.getExpression());
                    break;
                default:
                    EM_error(op.left->pos, "unrecognized operator!");
                    break;
            }
        } else if (!leftISReal && !rightIsReal) {
            switch (op.oper) {
                case A_plusOp:
                    ir = new OpPlusIR(left.getExpression(), right.getExpression());
                    break;
                case A_minusOp:
                    ir = new OpMinusIR(left.getExpression(), right.getExpression());
                    break;
                case A_timesOp:
                    ir = new OpTimesIR(left.getExpression(), right.getExpression());
                    break;
                case A_divideOp:
                    ir = new OpDivideIR(left.getExpression(), right.getExpression());
                    break;
                case A_eqOp:
                    ir = new OpEqIR(left.getExpression(), right.getExpression());
                    break;
                case A_neqOp:
                    ir = new OpNeqIR(left.getExpression(), right.getExpression());
                    break;
                case A_ltOp:
                    ir = new OpLtIR(left.getExpression(), right.getExpression());
                    break;
                case A_leOp:
                    ir = new OpLeIR(left.getExpression(), right.getExpression());
                    break;
                case A_gtOp:
                    ir = new OpGtIR(left.getExpression(), right.getExpression());
                    break;
                case A_geOp:
                    ir = new OpGeIR(left.getExpression(), right.getExpression());
                    break;
                default:
                    EM_error(op.left->pos, "unrecognized operator!");
                    break;
            }
        } else {
            EM_error(op.right->pos, "two operands' type mismatch!");
            return ExpressionAndType(VarType::getNilType(), nullptr);
        }
        return ExpressionAndType(getBiggestType(left.getType(), right.getType()), ir);
    }

    static ExpressionAndType
    translateSimpleVar(S_table valueEnvironment, S_table typeEnvironment, S_symbol simple, A_pos pos) {
        if (simple == NULL) return ExpressionAndType(VarType::getVoidType());

        auto entry = unpack<VariableEnvironmentEntry>(S_look(valueEnvironment, simple));
        if (entry == nullptr || *entry == nullptr) {
            EM_error(pos, "undefined variable %s", S_name(simple));
            return ExpressionAndType(VarType::getNilType(), nullptr);
        } else if ((*entry)->getKind() == EntryKind::FunctionEntry) {
            EM_error(pos, "variable %s is a function rather than a variable", S_name(simple));
            return ExpressionAndType(VarType::getNilType(), nullptr);
        }
        return ExpressionAndType((*entry)->getType(), new SimpleVarIR(S_name(simple)), (*entry)->isConst);
    }

    static ExpressionAndType
    translateSubscriptVar(S_table valueEnvironment, S_table typeEnvironment, _A_subscript_ subscript) {
        if (subscript.var == NULL) {
            if (subscript.exp == NULL)
                return ExpressionAndType(VarType::getVoidType());
            else
                return translateExpression(valueEnvironment, typeEnvironment, subscript.exp);
        }

        auto entry = unpack<VariableEnvironmentEntry>(S_look(valueEnvironment, subscript.var));

        if (entry == nullptr || *entry == nullptr) {
            EM_error(subscript.exp->pos, "undefined variable %s", S_name(subscript.var));
            return ExpressionAndType(VarType::getNilType(), nullptr);
        }

        if ((*entry)->getType()->getKind() != TypeKind::Array) {
            EM_error(subscript.exp->pos, "variable %s is not a array!", S_name(subscript.var));
            return ExpressionAndType(VarType::getNilType());
        }
        auto arrayType = std::static_pointer_cast<ArrayVarType>((*entry)->getType());

        auto subExp = translateExpression(valueEnvironment, typeEnvironment, subscript.exp);

        if (subExp.getType() != VarType::getIntegerType()) {
            EM_error(subscript.exp->pos, "subscript should be an integer!");
            return ExpressionAndType(VarType::getNilType());
        }

        if (subExp.isConst) {
            int val = 0;
            auto intValExp = static_cast<ConstIntIR *>(subExp.getExpression());
            if (intValExp) {
                val = intValExp->getVal();
                if (!arrayType->getRangeType()->inRange(val)) {
                    EM_error(subscript.exp->pos, "the subscript is not in the correct range!");
                    return ExpressionAndType(VarType::getNilType());
                }
                val -= arrayType->getRangeType()->getMin();
            }

            return ExpressionAndType(arrayType->getType(),
                                     new SubscriptVarIR(S_name(subscript.var), new ConstIntIR(val)));
        } else {
            auto minusMin = new OpMinusIR(subExp.getExpression(), new ConstIntIR(arrayType->getRangeType()->getMin()));
            return ExpressionAndType(arrayType->getType(), new SubscriptVarIR(S_name(subscript.var), minusMin));
        }

    }

    static ExpressionAndType
    translateFieldVar(S_table valueEnvironment, S_table typeEnvironment, _A_field_ field, A_pos pos) {
        if (field.var == NULL || field.sym == NULL) return ExpressionAndType(VarType::getVoidType());

        auto recordEnv = unpack<VariableEnvironmentEntry>(S_look(valueEnvironment, field.var));

        if (recordEnv == nullptr || *recordEnv == nullptr) {
            EM_error(pos, "undefined variable %s!", S_name(field.var));
            return ExpressionAndType(VarType::getNilType(), nullptr);
        }

        auto record = std::static_pointer_cast<RecordVarType>((*recordEnv)->getType());
        auto &fieldList = record->getFieldList();
        int index = 0;
        for (auto _field : fieldList) {
            if (S_compare(_field.getName(), field.sym)) {
                return ExpressionAndType(_field.getType(), new FieldVarIR(S_name(field.var), S_name(field.sym), index));
            }
            index++;
        }
        return ExpressionAndType(VarType::getNilType());
    }

    static ExpressionAndType
    translateConstDec(S_table valueEnvironment, S_table typeEnvironment, _A_const_ constt) {
        if (constt.name == NULL) return ExpressionAndType(VarType::getVoidType());

        auto constExp = translateConst(valueEnvironment, typeEnvironment, constt.constValue);

        if (constExp.getType() == VarType::getIntegerType()) {
            auto intExp = static_cast<ConstIntIR *>(constExp.getExpression());
            assert(intExp);
            S_enter(valueEnvironment, constt.name, pack(new ConstIntVariableEnvironnmentEntry(intExp->getVal())));
        } else if (constExp.getType() == VarType::getCharType()) {
            auto charExp = static_cast<ConstCharIR *>(constExp.getExpression());
            assert(charExp);
            S_enter(valueEnvironment, constt.name, pack(new ConstCharVariableEnvironnmentEntry(charExp->getVal())));
        } else if (constExp.getType() == VarType::getRealType()) {
            auto realExp = static_cast<ConstRealIR *>(constExp.getExpression());
            assert(realExp);
            S_enter(valueEnvironment, constt.name, pack(new ConstRealVariableEnvironnmentEntry(realExp->getVal())));
        } else if (constExp.getType() == VarType::getStringType()) {
            auto stringExp = static_cast<ConstStringIR *>(constExp.getExpression());
            assert(stringExp);
            S_enter(valueEnvironment, constt.name, pack(new ConstStringVariableEnvironnmentEntry(stringExp->getVal())));
        } else if (constExp.getType() == VarType::getBooleanType()) {
            auto boolExp = static_cast<ConstBoolIR *>(constExp.getExpression());
            assert(boolExp);
            S_enter(valueEnvironment, constt.name, pack(new ConstBoolVariableEnvironmentEntry(boolExp->getVal())));
        } else {
            EM_error(constt.constValue->pos, "the initial value of const variable %s is not const!",
                     S_name(constt.name));
        }

        constExp.setExpression(new ConstVarDecIR(S_name(constt.name), constExp.getExpression()));

        return constExp;
    }

    static ExpressionAndType translateTypeDec(S_table valueEnvironment, S_table typeEnvironment, _A_type_ type) {
        if (type.name == NULL) return ExpressionAndType(VarType::getVoidType());

        auto typeExp = translateType(valueEnvironment, typeEnvironment, type.ty);

        S_enter(typeEnvironment, type.name, pack(new VariableEnvironmentEntry(typeExp.getType())));

        if (typeExp.getType()->getKind() == TypeKind::Enum) {
            //register all enums as its type
            auto enumType = std::static_pointer_cast<EnumVarType>(typeExp.getType());
            auto nameList = enumType->getItems();

            for (auto name : nameList) {
                S_enter(valueEnvironment, name, pack(new VariableEnvironmentEntry(enumType)));
            }
        }

        return typeExp;
    }

    static ExpressionAndType translateVarDec(S_table valueEnvironment, S_table typeEnvironment, A_field var) {
        if (var == NULL) return ExpressionAndType(VarType::getVoidType());

        auto varExp = translateType(valueEnvironment, typeEnvironment, var->ty);

        auto nameList = var->head;
        std::vector<std::string> names;
        while (nameList != nullptr) {

            S_enter(valueEnvironment, nameList->head->name, pack(new VariableEnvironmentEntry(varExp.getType())));

            names.push_back(S_name(nameList->head->name));
            nameList = nameList->tail;
        }

        varExp.setExpression(new VarDecIR(names, IR::genType(varExp.getType())));
        return varExp;
    }

    static ExpressionAndType
    translateRoutineDec(S_table valueEnvironment, S_table typeEnvironment, _A_routine_ routinee) {
        if (routinee.name == NULL) return ExpressionAndType(VarType::getVoidType());
        S_beginScope(valueEnvironment);
        S_beginScope(typeEnvironment);

        auto routineEnv = new FunctionEnvironmentEntry();

        auto params = routinee.params;
        std::vector<std::string> fieldNames;
        std::vector<Type *> fieldTypes;
        while (params != nullptr) {
            auto param = params->head;
            auto names = param->head;

            while (names != nullptr) {
                auto typeExp = translateType(valueEnvironment, typeEnvironment, param->ty);
                routineEnv->getFormals().push_back(typeExp.getType());
                S_enter(valueEnvironment, names->head->name,
                        pack<VariableEnvironmentEntry>(new VariableEnvironmentEntry(typeExp.getType())));

                fieldNames.push_back(S_name(names->head->name));
                fieldTypes.push_back(IR::genType(typeExp.getType()));
                names = names->tail;
            }

            params = params->tail;
        }

        if (routinee.simplety) {
            auto resultExp = translateSimpleType(valueEnvironment, typeEnvironment, routinee.simplety);
            routineEnv->getResult() = resultExp.getType();
        } else {
            routineEnv->getResult() = nullptr;
        }

        S_enter(typeEnvironment, routinee.name, pack<FunctionEnvironmentEntry>(routineEnv));
        S_enter(valueEnvironment, routinee.name,
                pack<VariableEnvironmentEntry>(new VariableEnvironmentEntry(routineEnv->getResult())));

        std::string funcName = S_name(routinee.name);
        auto subroutineExp = translateRoutine(valueEnvironment, typeEnvironment, routinee.subroutine,
                                              funcName);
        RoutineDecIR *theFunc = new RoutineDecIR(funcName, fieldNames, fieldTypes,
                                                 IR::genType(routineEnv->getResult()), subroutineExp.getExpression());

        S_endScope(typeEnvironment);
        S_endScope(valueEnvironment);

        S_enter(typeEnvironment, routinee.name, pack<FunctionEnvironmentEntry>(routineEnv));

        return ExpressionAndType(VarType::getVoidType(), theFunc);
    }

    static ExpressionAndType
    translateRecordType(S_table valueEnvironment, S_table typeEnvironment, A_fieldList fieldList) {
        auto recordType = std::shared_ptr<RecordVarType>(new
                                                                 RecordVarType);

        while (fieldList != nullptr) {
            auto field = fieldList->head;

            auto typeExp = translateType(valueEnvironment, typeEnvironment, field->ty);
            auto nameList = field->head;
            while (nameList != nullptr) {
                auto name = nameList->head;

                recordType->getFieldList().push_back(Field(name->name, typeExp.getType()));

                nameList = nameList->tail;
            }

            fieldList = fieldList->tail;
        }

        return ExpressionAndType(std::static_pointer_cast<VarType>(recordType));
    }

    static ExpressionAndType translateArrayType(S_table valueEnvironment, S_table typeEnvironment, _A_array_ array) {
        auto typeExp = translateType(valueEnvironment, typeEnvironment, array.ty);
        auto simpleTypeExp = translateSimpleType(valueEnvironment, typeEnvironment, array.simple);

        auto rangeType = std::static_pointer_cast<RangeVarType>(simpleTypeExp.getType());
        if (!rangeType) {
            EM_error(array.simple->pos, "there should be a range type!");
        }
        auto arrayType = std::shared_ptr<ArrayVarType>(new ArrayVarType(typeExp.getType(), rangeType));

        return ExpressionAndType(std::static_pointer_cast<VarType>(arrayType));
    }

    static ExpressionAndType translateProc(S_table valueEnvironment, S_table typeEnvironment, A_proc proc) {
        if (proc == NULL) return ExpressionAndType(VarType::getVoidType());

        S_symbol procName;
        if (proc->kind == A_sysProc) {
            procName = proc->u.proc;
        } else {
            //A_func
            procName = proc->u.func;
        }

        if (procName == NULL) return ExpressionAndType(VarType::getVoidType());

        auto env = unpack<FunctionEnvironmentEntry>(S_look(typeEnvironment, procName));
        if (env == nullptr) {
            EM_error(proc->pos, "can not find a function or procedure named %s!", S_name(procName));
            return ExpressionAndType(VarType::getNilType(), nullptr);
        }

        auto &formals = (*env)->getFormals();
        auto &args = proc->args;

        auto iter = formals.begin();
        std::vector<IR *> argExps;
        while (args != nullptr) {
            auto argExp = translateExpression(valueEnvironment, typeEnvironment, args->head);
            if (*iter != VarType::getNilType()) { //Nil means any number of args
                if (argExp.getType() != *iter) {
                    EM_error(proc->args->head->pos, "arguments type mismatch!");
                    break;
                }
                iter++;
            }
            argExps.push_back(argExp.getExpression());
            args = args->tail;
        }
        if (*iter != VarType::getNilType() && iter != formals.end()) {
            EM_error(proc->args->head->pos, "arguments number mismatch!");
        }


        auto result = (*env)->getResult();

        if (result)
            return ExpressionAndType(result, new ProcIR(S_name(procName), argExps));
        else
            return ExpressionAndType(VarType::getVoidType(), new ProcIR(S_name(procName), argExps));
    }

    static ExpressionAndType
    translateAssignStatement(S_table valueEnvironment, S_table typeEnvironment, _A_assign_ assign) {
        auto variable = translateVariable(valueEnvironment, typeEnvironment, assign.var);
        auto expression = translateExpression(valueEnvironment, typeEnvironment, assign.exp);

        if (variable.isConst) {
            EM_error(assign.var->pos, "variable is const and can not be assigned!");
            return ExpressionAndType(variable.getType(), nullptr, true);
        }

        if (variable.getType() == nullptr || expression.getType() == nullptr) {
            EM_error(assign.var->pos, "variable type or expression has unrecognized type!");
            return ExpressionAndType(VarType::getVoidType());
        }

        TypeKind kind = variable.getType()->getKind();
        if (expression.getType() == VarType::getIntegerType() && (kind == TypeKind::Enum || kind == TypeKind::Range)) {

        } else if (variable.getType() != expression.getType()) {
            EM_error(assign.var->pos, "variable type and expression type mismatch!");
            return ExpressionAndType(VarType::getVoidType());
        }

        if ((kind == TypeKind::Enum || kind == TypeKind::Range) && expression.isConst &&
            expression.getType() == VarType::getIntegerType()) {
            auto rangeType = std::static_pointer_cast<RangeVarType>(variable.getType());
            auto constIntVal = static_cast<ConstIntIR *>(expression.getExpression())->getVal();
            if (rangeType && constIntVal && (constIntVal > rangeType->getMax() || constIntVal < rangeType->getMin())) {
                EM_error(assign.var->pos, "the const value is not in the range!");
            }
        }

        return ExpressionAndType(variable.getType(),
                                 new AssignIR(variable.getExpression(), expression.getExpression()));
    }

    static ExpressionAndType translateIfStatement(S_table valueEnvironment, S_table typeEnvironment, _A_if_stm_ iff) {
        S_beginScope(valueEnvironment);
        S_beginScope(typeEnvironment);

        auto testExp = translateExpression(valueEnvironment, typeEnvironment, iff.test);
        ExpressionAndType thenExp, elseExp;
        if (testExp.getType() != VarType::getIntegerType()) {
            EM_error(iff.test->pos, "if expression test should return int type!");
        } else {
            thenExp = translateStatement(valueEnvironment, typeEnvironment, iff.then);
            if (iff.elsee != nullptr) {
                elseExp = translateStatement(valueEnvironment, typeEnvironment, iff.elsee);
            }
        }
        S_endScope(valueEnvironment);
        S_endScope(typeEnvironment);
        return ExpressionAndType(VarType::getVoidType(),
                                 new IfIR(testExp.getExpression(), thenExp.getExpression(), elseExp.getExpression()));
    }

    static ExpressionAndType
    translateRepeatStatement(S_table valueEnvironment, S_table typeEnvironment, _A_repeat_ repeat) {
        S_beginScope(valueEnvironment);
        S_beginScope(typeEnvironment);

        auto testExp = translateExpression(valueEnvironment, typeEnvironment, repeat.test);
        std::vector<IR *> statementIRs;
        if (testExp.getType() != VarType::getIntegerType()) {
            EM_error(repeat.test->pos, "repeat expression test should return int type!");
        } else {
            auto &statementList = repeat.repeat;
            while (statementList != nullptr) {
                statementIRs.push_back(
                        translateStatement(valueEnvironment, typeEnvironment, statementList->head).getExpression());
                statementList = statementList->tail;
            }
        }

        S_endScope(valueEnvironment);
        S_endScope(typeEnvironment);
        return ExpressionAndType(VarType::getVoidType(), new RepeatIR(testExp.getExpression(), statementIRs));
    }

    static ExpressionAndType
    translateWhileStatement(S_table valueEnvironment, S_table typeEnvironment, _A_while_ whilee) {
        S_beginScope(valueEnvironment);
        S_beginScope(typeEnvironment);

        auto testExp = translateExpression(valueEnvironment, typeEnvironment, whilee.test);
        IR *statementIR = nullptr;
        if (testExp.getType() != VarType::getIntegerType())
            EM_error(whilee.test->pos, "while expression test should return int type!");
        else
            statementIR = translateStatement(valueEnvironment, typeEnvironment, whilee.whilee).getExpression();

        S_endScope(valueEnvironment);
        S_endScope(typeEnvironment);
        return ExpressionAndType(VarType::getVoidType(), new WhileIR(testExp.getExpression(), statementIR));
    }

    static ExpressionAndType translateForStatement(S_table valueEnvironment, S_table typeEnvironment, _A_for_ forr) {
        S_beginScope(valueEnvironment);
        S_beginScope(typeEnvironment);

        if (forr.var == NULL) return ExpressionAndType(VarType::getVoidType());

        auto initExp = translateExpression(valueEnvironment, typeEnvironment, forr.init);

        auto changeExp = translateExpression(valueEnvironment, typeEnvironment, forr.change);


        if (initExp.getType() != changeExp.getType())
            EM_error(forr.change->pos, "variable init value type mismatch its change type!");

        S_enter(valueEnvironment, forr.var, pack(new VariableEnvironmentEntry(initExp.getType())));
        auto doExp = translateStatement(valueEnvironment, typeEnvironment, forr.fordo);

        S_endScope(valueEnvironment);
        S_endScope(typeEnvironment);
        return ExpressionAndType(VarType::getVoidType(),
                                 new ForIR(S_name(forr.var), initExp.getExpression(), changeExp.getExpression(),
                                           doExp.getExpression()));
    }

    static ExpressionAndType translateCaseStatement(S_table valueEnvironment, S_table typeEnvironment, _A_case_ casee) {
        S_beginScope(valueEnvironment);
        S_beginScope(typeEnvironment);

        auto testExp = translateExpression(valueEnvironment, typeEnvironment, casee.test);

        if (testExp.getType() != VarType::getIntegerType()) {
            EM_error(casee.test->pos, "the test expression should be an integer");
            return ExpressionAndType(VarType::getVoidType());
        }

        auto caseList = casee.caselist;
        std::vector<int> caseTests;
        std::vector<IR *> statements;
        while (caseList != nullptr) {
            std::shared_ptr<VarType> constType = nullptr;
            if (caseList->head->name) {
                auto varEnv = unpack<VariableEnvironmentEntry>(S_look(valueEnvironment, caseList->head->name));
                if (varEnv == nullptr) {
                    EM_error(caseList->head->pos, "undefined variable %s!", S_name(caseList->head->name));
                    break;
                } else if (!(*varEnv)->isConst) {
                    EM_error(caseList->head->pos, "the variable %s is not a constant!", S_name(caseList->head->name));
                    break;
                }

                auto caseVal = std::static_pointer_cast<ConstIntVariableEnvironnmentEntry>(*varEnv);
                if (!caseVal) {
                    EM_error(caseList->head->pos, "the variable %s is not a integer!", S_name(caseList->head->name));
                    break;
                }

                caseTests.push_back(caseVal->getVal());
            } else if (caseList->head->constValue) {
                auto constExp = translateConst(valueEnvironment, typeEnvironment, caseList->head->constValue);
                constType = constExp.getType();

                ConstIntIR *ir = static_cast<ConstIntIR *>(constExp.getExpression());

                if (!ir) {
                    EM_error(caseList->head->pos, "type of const value must be integer!");
                    break;
                }

                caseTests.push_back(ir->getVal());
            }

            statements.push_back(
                    translateStatement(valueEnvironment, typeEnvironment, caseList->head->casee).getExpression());

            caseList = caseList->tail;
        }

        S_endScope(valueEnvironment);
        S_endScope(typeEnvironment);
        return ExpressionAndType(VarType::getVoidType(), new CaseIR(testExp.getExpression(), caseTests, statements));
    }

    static ExpressionAndType translateGotoStatement(S_table valueEnvironment, S_table typeEnvironment, _A_goto_ gotoo) {
        std::string name;
        if (gotoo.des->kind == A_string) {
            name = gotoo.des->u.stringg;
        } else if (gotoo.des->kind == A_int) {
            name = std::to_string(gotoo.des->u.intt);
        } else {
            EM_error(gotoo.des->pos, "the label is either a string or a integer!");
            return ExpressionAndType(VarType::getVoidType());
        }

        return ExpressionAndType(VarType::getVoidType(), new GotoIR(name));
    }

    static ExpressionAndType
    translateCompoundStatement(S_table valueEnvironment, S_table typeEnvironment, _A_compound_ compound) {
        S_beginScope(valueEnvironment);
        S_beginScope(typeEnvironment);

        auto statementList = compound.substmtList;
        std::vector<IR *> statementIRs;
        while (statementList != nullptr) {
            auto exp = translateStatement(valueEnvironment, typeEnvironment, statementList->head);
            statementList = statementList->tail;
            statementIRs.push_back(exp.getExpression());
        }

        S_endScope(valueEnvironment);
        S_endScope(typeEnvironment);
        return ExpressionAndType(VarType::getVoidType(), new CompoundIR(statementIRs));
    }

    static ExpressionAndType
    translateSyscon(S_table valueEnvironment, S_table typeEnvironment, S_symbol syscon, A_pos pos) {
        if (syscon == NULL) return ExpressionAndType(VarType::getVoidType());

        auto sysconExp = unpack<VariableEnvironmentEntry>(S_look(valueEnvironment, syscon));
        if (!sysconExp) {
            EM_error(pos, "Can not find a const variable named %s!", S_name(syscon));
            return ExpressionAndType(VarType::getNilType());
        }

        return ExpressionAndType((*sysconExp)->getType(), new SimpleVarIR(S_name(syscon)), (*sysconExp)->isConst);
    }

    static ExpressionAndType translateString(S_table valueEnvironment, S_table typeEnvironment, string _string) {
        return ExpressionAndType(VarType::getStringType(), new ConstStringIR(_string));
    }

    static ExpressionAndType
    translateSysType(S_table valueEnvironment, S_table typeEnvironment, S_symbol systy, A_pos pos) {
        if (systy == NULL) return ExpressionAndType(VarType::getVoidType());

        auto typeEnv = unpack<VariableEnvironmentEntry>(S_look(typeEnvironment, systy));

        if (typeEnv == nullptr || *typeEnv == nullptr) {
            EM_error(pos, "undefined type: %s!", S_name(systy));
            return ExpressionAndType(VarType::getNilType());
        }

        return ExpressionAndType((*typeEnv)->getType());
    }


    static ExpressionAndType
    translateSingleType(S_table valueEnvironment, S_table typeEnvironment, S_symbol single, A_pos pos) {
        auto maxEnv = unpack<VariableEnvironmentEntry>(S_look(valueEnvironment, single));

        if (!maxEnv) {
            EM_error(pos, "undefined variable %s!", S_name(single));
        }

        auto maxExp = std::static_pointer_cast<ConstIntVariableEnvironnmentEntry>(*maxEnv);
        if (!maxExp) {
            EM_error(pos, "the variable %s should be a const integer!", S_name(single));
        }

        return ExpressionAndType(std::shared_ptr<VarType>(new RangeVarType(0, maxExp->getVal())));
    }

    static ExpressionAndType
    translateDoubleConstSimpleType(S_table valueEnvironment, S_table typeEnvironment, _A_doubleC_ doubleC) {
        if (doubleC.left == NULL || doubleC.right == NULL) return ExpressionAndType(VarType::getVoidType());

        auto leftExp = translateExpression(valueEnvironment, typeEnvironment, doubleC.left);
        auto rightExp = translateExpression(valueEnvironment, typeEnvironment, doubleC.right);

        if (leftExp.getType() != rightExp.getType()) {
            EM_error(doubleC.left->pos, "type of left expression mismatch that of right!");
        }

        ConstIntIR *min, *max;
        if (!leftExp.isConst || !(min = static_cast<ConstIntIR *>(leftExp.getExpression()))) {
            EM_error(doubleC.left->pos, "left expression must be a const integer value!");
            return ExpressionAndType(VarType::getVoidType());
        }

        if (!rightExp.isConst || !(max = static_cast<ConstIntIR *>(rightExp.getExpression()))) {
            EM_error(doubleC.right->pos, "right expression must be a const integer value!");
            return ExpressionAndType(VarType::getVoidType());
        }

        int minVal = min->getVal();
        int maxVal = max->getVal();
        if (minVal > maxVal) {
            int temp = minVal;
            minVal = maxVal;
            maxVal = temp;
        }

        return ExpressionAndType(std::shared_ptr<VarType>(new RangeVarType(minVal, maxVal)));
    }

    static ExpressionAndType
    translateDoubleNameSimpleType(S_table valueEnvironment, S_table typeEnvironment, _A_doubleN_ doubleN, A_pos pos) {
        if (doubleN.left == NULL || doubleN.right == NULL) return ExpressionAndType(VarType::getVoidType());

        auto leftEnv = unpack<VariableEnvironmentEntry>(S_look(valueEnvironment, doubleN.left));
        auto rightEnv = unpack<VariableEnvironmentEntry>(S_look(valueEnvironment, doubleN.right));

        if ((*leftEnv)->getType() != (*rightEnv)->getType()) {
            EM_error(pos, "type of left variable mismatch that of right!");
        }

        auto leftExp = std::static_pointer_cast<ConstIntVariableEnvironnmentEntry>(*leftEnv);
        if (!leftExp) {
            EM_error(pos, "left variable %s is not a const int variable!", S_name(doubleN.left));
        }

        auto rightExp = std::static_pointer_cast<ConstIntVariableEnvironnmentEntry>(*rightEnv);
        if (!rightExp) {
            EM_error(pos, "right variable %s is not a const int variable!", S_name(doubleN.right));
        }

        int minVal = leftExp->getVal();
        int maxVal = rightExp->getVal();
        if (minVal > maxVal) {
            int temp = minVal;
            minVal = maxVal;
            maxVal = temp;
        }

        return ExpressionAndType(std::shared_ptr<VarType>(new RangeVarType(minVal, maxVal)));
    }

    static ExpressionAndType
    translateListSimpleType(S_table valueEnvironment, S_table typeEnvironment, A_nameList nameList) {
        if (nameList == NULL) return ExpressionAndType(VarType::getVoidType());

        std::list<S_symbol> names;
        while (nameList != nullptr) {
            auto name = nameList->head;

            names.push_back(name->name);

            nameList = nameList->tail;
        }

        auto type = std::shared_ptr<EnumVarType>(new EnumVarType(names));

        return ExpressionAndType(std::static_pointer_cast<VarType>(type));
    }

    static ExpressionAndType translateDecPart(S_table valueEnvironment, S_table typeEnvironment, A_decPart decPart) {
        if (decPart == NULL) return ExpressionAndType(VarType::getVoidType());

        auto decList = decPart->head;

        std::vector<IR *> declareIRs;
        while (decList != nullptr) {
            auto dec = decList->head;

            declareIRs.push_back(translateDeclaration(valueEnvironment, typeEnvironment, dec).getExpression());

            decList = decList->tail;
        }

        return ExpressionAndType(VarType::getVoidType(), new CompoundIR(declareIRs));
    }

public:

    static ExpressionAndType
    translateType(S_table valueEnvironment, S_table typeEnvironment, A_ty type) {
        switch (type->kind) {
            case A_simTy:
                return translateSimpleType(valueEnvironment, typeEnvironment, type->u.simple);
            case A_recordTy:
                return translateRecordType(valueEnvironment, typeEnvironment, type->u.record);
            case A_arrayTy:
                return translateArrayType(valueEnvironment, typeEnvironment, type->u.array);
            default:
                EM_error(type->pos, "Not recognized type! type kind: %d", type->kind);
                return ExpressionAndType(VarType::getNilType(), nullptr);
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
                EM_error(declaration->pos, "Not recognized declaration type! VarType id: %d", declaration->kind);
                return ExpressionAndType(VarType::getNilType(), nullptr);
        }
    }

    static ExpressionAndType translateConst(S_table valueEnvironment, S_table typeEnvironment, A_const constValue) {
        switch (constValue->kind) {
            case A_int:
                return ExpressionAndType(VarType::getIntegerType(), new ConstIntIR(constValue->u.intt), true);
            case A_real:
                return ExpressionAndType(VarType::getRealType(), new ConstRealIR(constValue->u.reall), true);
            case A_char:
                return ExpressionAndType(VarType::getCharType(), new ConstCharIR(constValue->u.charr), true);
            case A_string:
                return ExpressionAndType(VarType::getStringType(), new ConstStringIR(constValue->u.stringg), true);
//            case A_syscon:
//                return translateSyscon(valueEnvironment, typeEnvironment, constValue->u.syscon, constValue->pos);
            case A_bool:
				return ExpressionAndType(VarType::getBooleanType(), new ConstBoolIR(constValue->u.booll), true);
            default:
                EM_error(constValue->pos, "Not recognized const value!");
                return ExpressionAndType(VarType::getNilType(), nullptr);
        }
    }

    static ExpressionAndType
    translateLabelStatemennt(S_table valueEnvironment, S_table typeEnvironmrnt, _A_label_ label) {
        auto statement = translateStatement(valueEnvironment, typeEnvironmrnt, label.stmt);

        std::string name;
        if (label.label->kind == A_int) {
            if (label.label->u.intt == -1)
                return statement;
            name = std::to_string(label.label->u.intt);
        } else if (label.label->kind == A_string) {
            name = label.label->u.stringg;
        } else {
            EM_error(label.label->pos, "the label is either a string or a integer!");
            return ExpressionAndType(VarType::getVoidType());
        }

        std::vector<IR *> irs;
        irs.push_back(new LabelDecIR(name));
        irs.push_back(statement.getExpression());

        return ExpressionAndType(VarType::getVoidType(), new CompoundIR(irs));
    }

    static ExpressionAndType translateStatement(S_table valueEnvironment, S_table typeEnvironment, A_stmt statement) {
        switch (statement->kind) {
            case A_labelStmt:
                return translateLabelStatemennt(valueEnvironment, typeEnvironment, statement->u.label);
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
                return translateGotoStatement(valueEnvironment, typeEnvironment, statement->u.gotoo);
            case A_compoundStmt:
                return translateCompoundStatement(valueEnvironment, typeEnvironment, statement->u.compound);
            default:
                EM_error(statement->pos, "Not recognized statement type! VarType id: %d", statement->kind);
                return ExpressionAndType(VarType::getNilType(), nullptr);
        }
    }

    static ExpressionAndType
    translateSimpleType(S_table valueEnvironment, S_table typeEnvironment, A_simpleTy simpleType) {
        switch (simpleType->kind) {
            case A_sysTy:
            case A_singleTy:
                return translateSysType(valueEnvironment, typeEnvironment, simpleType->u.systy, simpleType->pos);
//                return translateSingleType(valueEnvironment, typeEnvironment, simpleType->u.single, simpleType->pos);
            case A_doubleCTy:
                return translateDoubleConstSimpleType(valueEnvironment, typeEnvironment, simpleType->u.doubleC);
            case A_doubleNTy:
                return translateDoubleNameSimpleType(valueEnvironment, typeEnvironment, simpleType->u.doubleN,
                                                     simpleType->pos);
            case A_listTy:
                return translateListSimpleType(valueEnvironment, typeEnvironment, simpleType->u.nameList);
            default:
                EM_error(simpleType->pos, "Not recognized simple type kind: %d", simpleType->kind);
                return ExpressionAndType(VarType::getNilType(), nullptr);
        }
    }

    static ExpressionAndType translateVariable(S_table valueEnvironment, S_table typeEnvironment, A_var variable) {
        switch (variable->kind) {
            case A_constVar:
                return translateConst(valueEnvironment, typeEnvironment, variable->u.constValue);
            case A_simpleVar:
                return translateSimpleVar(valueEnvironment, typeEnvironment, variable->u.simple, variable->pos);
            case A_fieldVar:
                return translateFieldVar(valueEnvironment, typeEnvironment, variable->u.field, variable->pos);
            case A_subscriptVar:
                return translateSubscriptVar(valueEnvironment, typeEnvironment, variable->u.subscript);
            default:
                EM_error(variable->pos, "Not recognized variable type! VarType id: %d", variable->kind);
                return ExpressionAndType(VarType::getNilType(), nullptr);
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
            case A_parenExp:
                return translateExpression(valueEnvironment, typeEnvironment, expression->u.paren);
            default:
                EM_error(expression->pos, "Not recognized expression type! VarType id: %d", expression->kind);
                return ExpressionAndType(VarType::getNilType(), nullptr);
        }
    }

    static ExpressionAndType
    translateRoutine(S_table valueEnvironment, S_table typeEnvironment, A_routine routine, std::string functionName) {
        auto routineHead = routine->head;
        auto routineBody = routine->body;

        std::vector<IR *> declaresIRs;
        //head
        IR *labelDecIR = translateDecPart(valueEnvironment, typeEnvironment, routineHead->labelPart).getExpression();
        IR *constDecIR = translateDecPart(valueEnvironment, typeEnvironment, routineHead->constPart).getExpression();
        IR *typeDecIR = translateDecPart(valueEnvironment, typeEnvironment, routineHead->typePart).getExpression();
        IR *varDecIR = translateDecPart(valueEnvironment, typeEnvironment, routineHead->varPart).getExpression();
        IR *routineDecIR = translateDecPart(valueEnvironment, typeEnvironment,
                                            routineHead->routinePart).getExpression();

        //body
        auto bodyExp = translateStatement(valueEnvironment, typeEnvironment, routineBody->head);
        IR *funcBodyIR = bodyExp.getExpression();

        bodyExp.setExpression(
                new RoutineBodyIR(functionName, labelDecIR, constDecIR, typeDecIR, varDecIR, routineDecIR, funcBodyIR));
        return bodyExp;
    }

    static ExpressionAndType translateProgram(S_table valueEnvironment, S_table typeEnvironment, A_pro program) {
        std::string programName = S_name(program->name);

        auto bodyExp = translateRoutine(valueEnvironment, typeEnvironment, program->routine, programName);
        bodyExp.setExpression(new ProgramIR(programName, (RoutineBodyIR *) bodyExp.getExpression()));

        return bodyExp;
    }
};

#endif //SPL_COMPILER_SEMANT_H
