//
// Created by 54179 on 2017/6/2.
//

#ifndef SPL_COMPILER_ENV_H
#define SPL_COMPILER_ENV_H

#include "types.hpp"
#include "symbol.h"

//used to store in the symbol table, used for variable environment

enum class EntryKind {
    VariableEntry, FunctionEntry
};

class EnvironmentEntry {
public:
    EnvironmentEntry(EntryKind entryKind) : entryKind(entryKind) {};

    EntryKind getKind() const {
        return entryKind;
    }

private:

    EntryKind entryKind;
};

char *toCharString(const std::string s) {
    return const_cast<char *>(s.data());
}

class VariableEnvironmentEntry : public EnvironmentEntry {
public:
    VariableEnvironmentEntry(std::shared_ptr<Type> type) : EnvironmentEntry(EntryKind::VariableEntry),
                                                           type(type) {};

    std::shared_ptr<Type> &getType() {
        return type;
    }

    static S_table enterBaseValueEnvironment() {
        S_table environment = S_empty();
        //TODO
        return environment;
    }

private:
    std::shared_ptr<Type> type;
};

class FunctionEnvironmentEntry : public EnvironmentEntry {
public:
    FunctionEnvironmentEntry() : EnvironmentEntry(EntryKind::FunctionEntry) {};

    FunctionEnvironmentEntry(std::list<std::shared_ptr<Type>> &formals, std::shared_ptr<Type> result)
            : EnvironmentEntry(EntryKind::FunctionEntry), formals(formals), result(result) {};

    FunctionEnvironmentEntry(std::shared_ptr<Type> result) : EnvironmentEntry(EntryKind::FunctionEntry), result(result) {};

    std::list<std::shared_ptr<Type>> &getFormals() {
        return formals;
    }

    std::shared_ptr<Type> getResult() {
        return result;
    }

    static S_table enterBaseTypeEnvironment() {
        S_table environment = S_empty();
        S_enter(environment, S_Symbol(toCharString("boolean")), new VariableEnvironmentEntry(std::shared_ptr<Type>(new Type(TypeKind::Boolean))));
        S_enter(environment, S_Symbol(toCharString("char")), new VariableEnvironmentEntry(std::shared_ptr<Type>(new Type(TypeKind::Char))));
        S_enter(environment, S_Symbol(toCharString("integer")), new VariableEnvironmentEntry(std::shared_ptr<Type>(new Type(TypeKind::Integer))));
        S_enter(environment, S_Symbol(toCharString("real")), new VariableEnvironmentEntry(std::shared_ptr<Type>(new Type(TypeKind::Real))));
        return environment;
    }

private:
    std::list<std::shared_ptr<Type>> formals;

    std::shared_ptr<Type> result;
};


#endif //SPL_COMPILER_ENV_H
