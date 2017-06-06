//
// Created by 54179 on 2017/6/2.
//

#ifndef SPL_COMPILER_ENV_H
#define SPL_COMPILER_ENV_H

#include "types.hpp"
#include "symbol.h"

class EnvironmentEntry {
public:
    Kind getKind() const {
        return kind;
    }

    EnvironmentEntry(EnvironmentEntry::Kind kind) : kind(kind) {};

    S_table enterBaseTypeEnvironment() {
        S_table environment = S_empty();
        S_enter(environment, S_Symbol("boolean"), new VariableEnvironmentEntry(new Type(Type::Boolean)));
        S_enter(environment, S_Symbol("char"), new VariableEnvironmentEntry(new Type(Type::Char)));
        S_enter(environment, S_Symbol("integer"), new VariableEnvironmentEntry(new Type(Type::Integer)));
        S_enter(environment, S_Symbol("real"), new VariableEnvironmentEntry(new Type(Type::Real)));
        return environment;
    }

    S_table enterBaseValueEnvironment() {
        S_table environment = S_empty();
        //TODO
        return environment;
    }

private:
    enum Kind {
        VariableEntry, FunctionEntry
    } kind;
};

class VariableEnvironmentEntry : public EnvironmentEntry {
public:
    VariableEnvironmentEntry(std::shared_ptr<Type> type) : EnvironmentEntry(EnvironmentEntry::VariableEntry),
                                                           type(type) {};

    std::shared_ptr<Type> &getType() const {
        return type;
    }

private:
    std::shared_ptr<Type> type;
};

class FunctionEnvironmentEntry : public EnvironmentEntry {
public:
    FunctionEnvironmentEntry() : EnvironmentEntry(EnvironmentEntry::FunctionEntry) {};

    FunctionEnvironmentEntry(std::list<Type> &formals, std::shared_ptr<Type> result)
            : FunctionEnvironmentEntry(), formals(formals), result(result) {};

    FunctionEnvironmentEntry(std::shared_ptr<Type> result) : FunctionEnvironmentEntry(), result(result) {};

    std::list<Type> &getFormals() const {
        return formals;
    }

    std::shared_ptr<Type> getResult() const {
        return result;
    }

private:
    std::list<Type> formals;

    std::shared_ptr<Type> result;
};


#endif //SPL_COMPILER_ENV_H
