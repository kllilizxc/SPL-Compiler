//
// Created by 54179 on 2017/6/2.
//

#ifndef SPL_COMPILER_ENV_H
#define SPL_COMPILER_ENV_H

#include "types.hpp"

class EnvironmentEntry {
public:
    enum Kind {
        VariableEntry, FunctionEntry
    } kind;

    EnvironmentEntry(EnvironmentEntry::Kind kind) : kind(kind) {};

    //S_table enterBaseTypeEnvironment(); TODO
    //S_table enterBaseFunctionEnvironment(); TODO
};

class VariableEnvironmentEntry : EnvironmentEntry {
public:
    VariableEnvironmentEntry(Type &type) : EnvironmentEntry(EnvironmentEntry::VariableEntry), type(type) {};
private:
    Type type;
};

class FunctionEnvironmentEntry : EnvironmentEntry {
public:
    FunctionEnvironmentEntry() : EnvironmentEntry(EnvironmentEntry::FunctionEntry) {};

    FunctionEnvironmentEntry(std::list<Type> &formals, Type &result) : FunctionEnvironmentEntry(), formals(formals), result(result) {};

    std::list<Type> &getFormals() const {
        return formals;
    }

    Type &getResult() const {
        return result;
    }

private:
    std::list<Type> formals;

    Type result;
};


#endif //SPL_COMPILER_ENV_H
