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
#include "absyn.h"
#include "ir.hpp"

extern "C" {
#include "symbol.h"
#include "absyn.h"
#include "errormsg.h"
#include "util.h"
};


typedef Value *Expression;

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
        return ExpressionAndType(VarType::getVoidType(), IR::genIf(testExp.getExpression(), thenExp.getExpression(), elseExp.getExpression()));
    }
    
    static bool isIntorBoolorRealorChar(std::shared_ptr<VarType> type) {
        return type == VarType::getIntegerType() || type == VarType::getBooleanType() || type == VarType::getRealType() || type == VarType::getCharType();
    }
    
    static std::shared_ptr<VarType> &getBiggestType(std::shared_ptr<VarType> type1, std::shared_ptr<VarType> type2) {
        assert(isIntorBoolorRealorChar(type1) && isIntorBoolorRealorChar(type2));
        
        if(type1 == VarType::getRealType() || type2 == VarType::getRealType())
            return VarType::getRealType();
        else
            return VarType::getIntegerType();
    }
    
    static ExpressionAndType translateOp(S_table valueEnvironment, S_table typeEnvironment, _A_op_ op) {
        A_oper oper = op.oper;
        
        auto left = translateExpression(valueEnvironment, typeEnvironment, op.left);
        auto right = translateExpression(valueEnvironment, typeEnvironment, op.right);
        
        //the two operands' type should match TODO
        if(oper == A_divideOp && right.getType() != VarType::getIntegerType()) {
            EM_error(op.right->pos, "the divider should be an integer!");
            return ExpressionAndType(VarType::getNilType(), nullptr);
        }
        
        auto leftISReal = !isIntorBoolorRealorChar(left.getType());
        auto rightIsReal = !isIntorBoolorRealorChar(right.getType());
        if (leftISReal && rightIsReal) {
            return ExpressionAndType(getBiggestType(left.getType(), right.getType()), IR::genFOp(op, left.getExpression(), right.getExpression()));
        } else if (!leftISReal && !rightIsReal) {
            return ExpressionAndType(getBiggestType(left.getType(), right.getType()), IR::genOp(op, left.getExpression(), right.getExpression()));
        } else {
            EM_error(op.right->pos, "two operands' type mismatch!");
            return ExpressionAndType(VarType::getNilType(), nullptr);
        }
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
        return ExpressionAndType((*entry)->getType(), IR::genSimpleVar(simple), (*entry)->isConst);
    }
    
    static ExpressionAndType
    translateSubscriptVar(S_table valueEnvironment, S_table typeEnvironment, _A_subscript_ subscript) {
        if (subscript.var == NULL) {
            if (subscript.exp == NULL)
                return ExpressionAndType(VarType::getVoidType());
        }
        else
            return translateExpression(valueEnvironment, typeEnvironment, subscript.exp);
        
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
        
        if (subExp.getType() != arrayType->getType()) {
            EM_error(subscript.exp->pos, "variable type and subscript type mismatch!");
            return ExpressionAndType(VarType::getNilType(), nullptr);
        }
        
        return ExpressionAndType(arrayType->getType(), nullptr); //TODO
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
        for (auto _field : fieldList) {
            if (S_compare(_field.getName(), field.sym)) {
                return ExpressionAndType(_field.getType(), nullptr);
            }
        }
        return ExpressionAndType(VarType::getNilType(), nullptr); //TODO
    }
    
    static ExpressionAndType
    translateConstDec(S_table valueEnvironment, S_table typeEnvironment, _A_const_ constt) {
        if (constt.name == NULL) return ExpressionAndType(VarType::getVoidType());
        
        auto constExp = translateConst(valueEnvironment, typeEnvironment, constt.constValue);
        
        S_enter(valueEnvironment, constt.name, pack(new VariableEnvironmentEntry(constExp.getType(), true)));
        
        IR::genConstDec(constt.name, constExp.getExpression());
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
        
        while (nameList != nullptr) {
            
            S_enter(valueEnvironment, nameList->head->name, pack(new VariableEnvironmentEntry(varExp.getType())));
            
            nameList = nameList->tail;
        }
        
        IR::genVarDec(var);
        return varExp;
    }
    
    static ExpressionAndType
    translateRoutineDec(S_table valueEnvironment, S_table typeEnvironment, _A_routine_ routinee) {
        if (routinee.name == NULL) return ExpressionAndType(VarType::getVoidType());
        S_beginScope(valueEnvironment);
        S_beginScope(typeEnvironment);
        
        auto routineEnv = new FunctionEnvironmentEntry();
        
        auto params = routinee.params;
        while (params != nullptr) {
            auto param = params->head;
            auto names = param->head;
            
            while (names != nullptr) {
                auto typeExp = translateType(valueEnvironment, typeEnvironment, param->ty);
                routineEnv->getFormals().push_back(typeExp.getType());
                S_enter(valueEnvironment, names->head->name, pack<VariableEnvironmentEntry>(new VariableEnvironmentEntry(typeExp.getType())));
                
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
        S_enter(valueEnvironment, routinee.name, pack<VariableEnvironmentEntry>(new VariableEnvironmentEntry(routineEnv->getResult())));
        
        auto subroutineExp = translateRoutine(valueEnvironment, typeEnvironment, routinee.subroutine);
        
        S_endScope(typeEnvironment);
        S_endScope(valueEnvironment);
        
        S_enter(typeEnvironment, routinee.name, pack<FunctionEnvironmentEntry>(routineEnv));
        
        return ExpressionAndType(VarType::getVoidType(), IR::genRoutineDec(routinee.name, routinee.params, routinee.simplety, subroutineExp.getExpression()));
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
        auto arrayType = std::shared_ptr<ArrayVarType>(new
                                                       ArrayVarType(typeExp.getType()));
        
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
        std::vector<Value *> argExps;
        while (iter != formals.end()) {
            auto argExp = translateExpression(valueEnvironment, typeEnvironment, args->head);
            if (argExp.getType() != *iter) {
                EM_error(proc->args->head->pos, "arguments type mismatch!");
                break;
            }
            iter++;
            argExps.push_back(argExp.getExpression());
            args = args->tail;
        }
        if (args != nullptr) {
            EM_error(proc->args->head->pos, "arguments number mismatch!");
        }
        
        auto result = (*env)->getResult();
        
        if (result)
            return ExpressionAndType(result, IR::genProc(proc, argExps));
        else
            return ExpressionAndType(VarType::getVoidType(), IR::genProc(proc, argExps));
    }
    
    static ExpressionAndType
    translateAssignStatement(S_table valueEnvironment, S_table typeEnvironment, _A_assign_ assign) {
        auto variable = translateVariable(valueEnvironment, typeEnvironment, assign.var);
        auto expression = translateExpression(valueEnvironment, typeEnvironment, assign.exp);
        
        if(variable.isConst) {
            EM_error(assign.var->pos, "variable is const and can not be assigned!");
            return ExpressionAndType(variable.getType(), nullptr, true);
        }
        
        if (variable.getType() == nullptr || expression.getType() == nullptr ||
            variable.getType() != expression.getType()) {
            EM_error(assign.var->pos, "variable type and expression type mismatch!");
        }
        return ExpressionAndType(variable.getType(), IR::genAssignStatement(variable.getExpression(), expression.getExpression()));
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
        return ExpressionAndType(VarType::getVoidType(), IR::genIf(testExp.getExpression(), thenExp.getExpression(), elseExp.getExpression()));
    }
    
    static ExpressionAndType
    translateRepeatStatement(S_table valueEnvironment, S_table typeEnvironment, _A_repeat_ repeat) {
        S_beginScope(valueEnvironment);
        S_beginScope(typeEnvironment);
        
        auto testExp = translateExpression(valueEnvironment, typeEnvironment, repeat.test);
        if (testExp.getType() != VarType::getIntegerType()) {
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
        return ExpressionAndType(VarType::getVoidType(), nullptr); //TODO
    }
    
    static ExpressionAndType
    translateWhileStatement(S_table valueEnvironment, S_table typeEnvironment, _A_while_ whilee) {
        S_beginScope(valueEnvironment);
        S_beginScope(typeEnvironment);
        
        auto testExp = translateExpression(valueEnvironment, typeEnvironment, whilee.test);
        if (testExp.getType() != VarType::getIntegerType())
            EM_error(whilee.test->pos, "while expression test should return int type!");
        else
            translateStatement(valueEnvironment, typeEnvironment, whilee.whilee);
        
        S_endScope(valueEnvironment);
        S_endScope(typeEnvironment);
        return ExpressionAndType(VarType::getVoidType(), nullptr); //TODO
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
        return ExpressionAndType(VarType::getVoidType(), IR::genForStatement(forr.var, initExp.getExpression(), changeExp.getExpression(), doExp.getExpression()));
    }
    
    static ExpressionAndType translateCaseStatement(S_table valueEnvironment, S_table typeEnvironment, _A_case_ casee) {
        S_beginScope(valueEnvironment);
        S_beginScope(typeEnvironment);
        
        auto testExp = translateExpression(valueEnvironment, typeEnvironment, casee.test);
        
        auto caseList = casee.caselist;
        while (caseList != nullptr) {
            std::shared_ptr<VarType> &&constType = nullptr;
            if (caseList->head->name) {
                auto varEnv = unpack<VariableEnvironmentEntry>(S_look(valueEnvironment, caseList->head->name));
                if (varEnv == nullptr) {
                    EM_error(caseList->head->pos, "undefined variable %s!", S_name(caseList->head->name));
                    break;
                }
                
                constType = (*varEnv)->getType();
            } else if (caseList->head->constValue) {
                auto constExp = translateConst(valueEnvironment, typeEnvironment, caseList->head->constValue);
                constType = constExp.getType();
            }
            
            if (constType != testExp.getType()) {
                EM_error(caseList->head->pos, "type of const value mismatch that of test expression!");
                break;
            } else {
                translateStatement(valueEnvironment, typeEnvironment, caseList->head->casee);
            }
            
            caseList = caseList->tail;
        }
        
        S_endScope(valueEnvironment);
        S_endScope(typeEnvironment);
        return ExpressionAndType(VarType::getVoidType(), nullptr); //TODO
    }
    
    static ExpressionAndType translateGotoType(S_table valueEnvironment, S_table typeEnvironment, _A_goto_ gotoo) {
        return ExpressionAndType(VarType::getVoidType(), nullptr); //TODO
    }
    
    static ExpressionAndType
    translateCompoundStatement(S_table valueEnvironment, S_table typeEnvironment, _A_compound_ compound) {
        S_beginScope(valueEnvironment);
        S_beginScope(typeEnvironment);
        
        auto statementList = compound.substmtList;
        std::vector<Value *> statementVals;
        while (statementList != nullptr) {
            auto exp = translateStatement(valueEnvironment, typeEnvironment, statementList->head);
            statementList = statementList->tail;
            statementVals.push_back(exp.getExpression());
        }
        
        S_endScope(valueEnvironment);
        S_endScope(typeEnvironment);
        return ExpressionAndType(VarType::getVoidType(), nullptr); //TODO
    }
    
    static ExpressionAndType
    translateSyscon(S_table valueEnvironment, S_table typeEnvironment, S_symbol syscon, A_pos pos) {
        if (syscon == NULL) return ExpressionAndType(VarType::getVoidType());
        
        auto sysconExp = unpack<VariableEnvironmentEntry>(S_look(valueEnvironment, syscon));
        if (!sysconExp) {
            EM_error(pos, "Can not find a const variable named %s!", S_name(syscon));
            return ExpressionAndType(VarType::getNilType());
        }
        
        return ExpressionAndType((*sysconExp)->getType(), IR::genSimpleVar(syscon), (*sysconExp)->isConst);
    }
    
    static ExpressionAndType translateString(S_table valueEnvironment, S_table typeEnvironment, string _string) {
        return ExpressionAndType(VarType::getStringType(), IR::genStringConst(_string));
    }
    
    static ExpressionAndType
    translateSysType(S_table valueEnvironment, S_table typeEnvironment, S_symbol systy, A_pos pos) {
        if (systy == NULL) return ExpressionAndType(VarType::getVoidType());
        
        auto typeEnv = unpack<VariableEnvironmentEntry>(S_look(typeEnvironment, systy));
        
        if (typeEnv == nullptr || *typeEnv == nullptr) {
            EM_error(pos, "undefined type: %s!", S_name(systy));
            return ExpressionAndType(VarType::getNilType(), nullptr);
        }
        
        return ExpressionAndType((*typeEnv)->getType());
    }
    
    static ExpressionAndType
    translateDoubleConstSimpleType(S_table valueEnvironment, S_table typeEnvironment, _A_doubleC_ doubleC) {
        if (doubleC.left == NULL || doubleC.right == NULL) return ExpressionAndType(VarType::getVoidType());
        
        auto leftExp = translateExpression(valueEnvironment, typeEnvironment, doubleC.left);
        auto rightExp = translateExpression(valueEnvironment, typeEnvironment, doubleC.right);
        
        if (leftExp.getType() != rightExp.getType()) {
            EM_error(doubleC.left->pos, "type of left expression mismatch that of right!");
        }
        
        return ExpressionAndType(leftExp.getType(), nullptr);
    }
    
    static ExpressionAndType
    translateDoubleNameSimpleType(S_table valueEnvironment, S_table typeEnvironment, _A_doubleN_ doubleN, A_pos pos) {
        if (doubleN.left == NULL || doubleN.right == NULL) return ExpressionAndType(VarType::getVoidType());
        
        auto leftEnv = unpack<VariableEnvironmentEntry>(S_look(valueEnvironment, doubleN.left));
        auto rightEnv = unpack<VariableEnvironmentEntry>(S_look(valueEnvironment, doubleN.right));
        
        if ((*leftEnv)->getType() != (*rightEnv)->getType()) {
            EM_error(pos, "type of left variable mismatch that of right!");
        }
        
        return ExpressionAndType((*leftEnv)->getType(), nullptr);
    }
    
    static ExpressionAndType
    translateListSimpleType(S_table valueEnvironment, S_table typeEnvironment, A_nameList nameList) {
        if (nameList == NULL) return ExpressionAndType(VarType::getVoidType());
        
        auto type = std::shared_ptr<EnumVarType>(new EnumVarType);
        
        while (nameList != nullptr) {
            auto name = nameList->head;
            
            type->getItems().push_back(name->name);
            
            nameList = nameList->tail;
        }
        
        return ExpressionAndType(std::static_pointer_cast<VarType>(type));
    }
    
    static ExpressionAndType translateDecPart(S_table valueEnvironment, S_table typeEnvironment, A_decPart decPart) {
        if (decPart == NULL) return ExpressionAndType(VarType::getVoidType());
        
        auto decList = decPart->head;
        
        while (decList != nullptr) {
            auto dec = decList->head;
            
            translateDeclaration(valueEnvironment, typeEnvironment, dec);
            
            decList = decList->tail;
        }
        
        return ExpressionAndType(VarType::getVoidType(), nullptr);
    }
    
public:
    
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
                return ExpressionAndType(VarType::getIntegerType(), IR::genIntConst(constValue->u.intt), true);
            case A_real:
                return ExpressionAndType(VarType::getRealType(), IR::genRealConst(constValue->u.reall), true);
            case A_char:
                return ExpressionAndType(VarType::getCharType(), IR::genCharConst(constValue->u.charr), true);
            case A_string:
                return ExpressionAndType(VarType::getStringType(), IR::genStringConst(constValue->u.stringg), true);
            case A_syscon:
                return translateSyscon(valueEnvironment, typeEnvironment, constValue->u.syscon, constValue->pos);
            default:
                EM_error(constValue->pos, "Not recognized const value!");
                return ExpressionAndType(VarType::getNilType(), nullptr);
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
                EM_error(statement->pos, "Not recognized statement type! VarType id: %d", statement->kind);
                return ExpressionAndType(VarType::getNilType(), nullptr);
        }
    }
    
    static ExpressionAndType
    translateSimpleType(S_table valueEnvironment, S_table typeEnvironment, A_simpleTy simpleType) {
        switch (simpleType->kind) {
            case A_sysTy:
                return translateSysType(valueEnvironment, typeEnvironment, simpleType->u.systy, simpleType->pos);
            case A_singleTy:
                return translateSysType(valueEnvironment, typeEnvironment, simpleType->u.single, simpleType->pos);
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
    
    static ExpressionAndType translateRoutine(S_table valueEnvironment, S_table typeEnvironment, A_routine routine) {
        auto routineHead = routine->head;
        auto routineBody = routine->body;
        
        //head
        translateDecPart(valueEnvironment, typeEnvironment, routineHead->labelPart);
        translateDecPart(valueEnvironment, typeEnvironment, routineHead->constPart);
        translateDecPart(valueEnvironment, typeEnvironment, routineHead->typePart);
        translateDecPart(valueEnvironment, typeEnvironment, routineHead->varPart);
        translateDecPart(valueEnvironment, typeEnvironment, routineHead->routinePart);
        
        //body
        return translateStatement(valueEnvironment, typeEnvironment, routineBody->head);
    }
    
    static ExpressionAndType translateProgram(S_table valueEnvironment, S_table typeEnvironment, A_pro program) {
        auto routine = program->routine;
        auto mainFunc = translateRoutine(valueEnvironment, typeEnvironment, routine);
        IR::genRoutineDec(S_Symbol(toCharString("main")), nullptr, nullptr, mainFunc.getExpression());
        return mainFunc;
    }
};

#endif //SPL_COMPILER_SEMANT_H
