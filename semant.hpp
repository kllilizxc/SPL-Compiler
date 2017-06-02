//
// Created by 54179 on 2017/6/2.
//

#ifndef SPL_COMPILER_SEMANT_H
#define SPL_COMPILER_SEMANT_H

#include <bits/unique_ptr.h>
#include <iostream>
#include "types.hpp"
#include "symbol.h"
#include "absyn.h"

typedef std::unique_ptr<void> Expression;

class ExpressionAndType {
public:
    ExpressionAndType(Type type, void *expression) : type(type), expression(expression) {};

    const Type &getType() const {
        return type;
    }

    const Expression getExpression() const {
        return expression;
    }

private:
    Type type;

    Expression expression;
};

class Semant {
public:
    static ExpressionAndType translateExpression(S_table valueEnvironment, S_table typeEnvironment, A_exp expression) {
        switch (expression->kind) {
            case A_varExp:
            case A_nilExp:
            case A_intExp:
            case A_callExp:
            case A_opExp:
            case A_recordExp:
            case A_seqExp:
            case A_assignExp:
            case A_ifExp:
            case A_whileExp:
            case A_forExp:
            case A_breakExp:
            case A_letExp:
            case A_arrayExp:
                break;
            default:
                throw "Error when translating expressions!";
        }
    }

    static ExpressionAndType translateVariable(S_table valueEnvironment, S_table typeEnvironment, A_var variable) {
        switch (variable->kind) {
            //TODO
        }
    }

    static ExpressionAndType translateDeclaration(S_table valueEnvironment, S_table typeEnvironment, A_dec declaration) {
        switch (declaration->kind) {
            //TODO
        }
    }
};

#endif //SPL_COMPILER_SEMANT_H
