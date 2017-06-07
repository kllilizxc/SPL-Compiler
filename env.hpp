//
// Created by 54179 on 2017/6/2.
//

#ifndef SPL_COMPILER_ENV_H
#define SPL_COMPILER_ENV_H

#include "types.hpp"
extern "C" {
#include "symbol.h"
};

//used to store in the symbol table, used for variable environment

enum class EntryKind {
    VariableEntry, FunctionEntry
};


char *toCharString(const std::string s) {
    return const_cast<char *>(s.data());
}


class EnvironmentEntry {
public:
    EnvironmentEntry(EntryKind entryKind) : entryKind(entryKind) {};

    EntryKind getKind() const {
        return entryKind;
    }

    static S_table enterBaseValueEnvironment();

    static S_table enterBaseTypeEnvironment();

private:
    template<class
    T>
    static void *pack(T *data) {
        return new
                std::shared_ptr<T>(data);
    }

    EntryKind entryKind;
};

class VariableEnvironmentEntry : public EnvironmentEntry {
public:
    VariableEnvironmentEntry(std::shared_ptr<Type> type, bool isConst = false) : EnvironmentEntry(EntryKind::VariableEntry),
                                                           type(type), isConst(isConst) {};

    std::shared_ptr<Type> &getType() {
        return type;
    }

    bool isConst;

private:
    std::shared_ptr<Type> type;
};

class FunctionEnvironmentEntry : public EnvironmentEntry {
public:
    FunctionEnvironmentEntry() : EnvironmentEntry(EntryKind::FunctionEntry) {};

    FunctionEnvironmentEntry(std::list<std::shared_ptr<Type>> &&formals, std::shared_ptr<Type> result)
            : EnvironmentEntry(EntryKind::FunctionEntry), formals(formals), result(result) {};

    FunctionEnvironmentEntry(std::shared_ptr<Type> result) : EnvironmentEntry(EntryKind::FunctionEntry), result(result) {};

    std::list<std::shared_ptr<Type>> &getFormals() {
        return formals;
    }

    std::shared_ptr<Type> &getResult() {
        return result;
    }

private:
    std::list<std::shared_ptr<Type>> formals;

    std::shared_ptr<Type> result;
};

S_table EnvironmentEntry::enterBaseTypeEnvironment() {
    S_table environment = S_empty();
    S_enter(environment, S_Symbol(toCharString("boolean")), pack(new VariableEnvironmentEntry(Type::getBooleanType())));
    S_enter(environment, S_Symbol(toCharString("char")), pack(new VariableEnvironmentEntry(Type::getCharType())));
    S_enter(environment, S_Symbol(toCharString("integer")),  pack(new VariableEnvironmentEntry(Type::getIntegerType())));
    S_enter(environment, S_Symbol(toCharString("real")), pack(new VariableEnvironmentEntry(Type::getRealType())));
    S_enter(environment, S_Symbol(toCharString("string")), pack(new VariableEnvironmentEntry(Type::getStringType())));
    return environment;
}

S_table EnvironmentEntry::enterBaseValueEnvironment() {
    S_table environment = S_empty();
    S_enter(environment, S_Symbol(toCharString("writeln")), pack(new FunctionEnvironmentEntry({Type::getIntegerType()}, Type::getVoidType())));
    S_enter(environment, S_Symbol(toCharString("write")), pack(new FunctionEnvironmentEntry({Type::getIntegerType()}, Type::getVoidType())));
    S_enter(environment, S_Symbol(toCharString("read")), pack(new FunctionEnvironmentEntry({Type::getIntegerType()}, Type::getVoidType())));
    S_enter(environment, S_Symbol(toCharString("true")), pack(new VariableEnvironmentEntry(Type::getBooleanType(), true)));
    S_enter(environment, S_Symbol(toCharString("false")), pack(new VariableEnvironmentEntry(Type::getBooleanType(), true)));
    S_enter(environment, S_Symbol(toCharString("maxint")), pack(new VariableEnvironmentEntry(Type::getIntegerType(), true)));
    return environment;
}


#endif //SPL_COMPILER_ENV_H
