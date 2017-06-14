//
// Created by 54179 on 2017/6/2.
//

#ifndef SPL_COMPILER_ENV_H
#define SPL_COMPILER_ENV_H

#include "types.hpp"
#include <string>
extern "C" {
#include "symbol.h"
};

//used to store in the symbol table, used for variable environment

enum class EntryKind {
    VariableEntry, FunctionEntry
};


char *toCharString(const std::string s) {
    return (char *)s.c_str();
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

class   VariableEnvironmentEntry : public EnvironmentEntry {
public:
    VariableEnvironmentEntry(std::shared_ptr<VarType> type, bool isConst = false) : EnvironmentEntry(EntryKind::VariableEntry),
                                                           type(type), isConst(isConst) {};

    std::shared_ptr<VarType> &getType() {
        return type;
    }

    bool isConst;

private:
    std::shared_ptr<VarType> type;
};

class ConstIntVariableEnvironnmentEntry : public VariableEnvironmentEntry {
public:
    ConstIntVariableEnvironnmentEntry(int val) : val(val), VariableEnvironmentEntry(VarType::getIntegerType(), true) {}

    int getVal() const {
        return val;
    };
private:
    int val;
};

class ConstRealVariableEnvironnmentEntry : public VariableEnvironmentEntry {
public:
    ConstRealVariableEnvironnmentEntry(double val) : val(val), VariableEnvironmentEntry(VarType::getRealType(), true) {}

    double getVal() const {
        return val;
    };
private:
    double val;
};

class ConstCharVariableEnvironnmentEntry : public VariableEnvironmentEntry {
public:
    ConstCharVariableEnvironnmentEntry(char val) : val(val), VariableEnvironmentEntry(VarType::getCharType(), true) {}

    char getVal() const {
        return val;
    };
private:
    char val;
};

class ConstStringVariableEnvironnmentEntry : public VariableEnvironmentEntry {
public:
    ConstStringVariableEnvironnmentEntry(std::string val) : val(val), VariableEnvironmentEntry(VarType::getStringType(), true) {}

    std::string getVal() const {
        return val;
    };
private:
    std::string val;
};

class FunctionEnvironmentEntry : public EnvironmentEntry {
public:
    FunctionEnvironmentEntry() : EnvironmentEntry(EntryKind::FunctionEntry) {};

    FunctionEnvironmentEntry(std::list<std::shared_ptr<VarType>> &&formals, std::shared_ptr<VarType> result)
            : EnvironmentEntry(EntryKind::FunctionEntry), formals(formals), result(result) {};

    FunctionEnvironmentEntry(std::shared_ptr<VarType> result) : EnvironmentEntry(EntryKind::FunctionEntry), result(result) {};

    std::list<std::shared_ptr<VarType>> &getFormals() {
        return formals;
    }

    std::shared_ptr<VarType> &getResult() {
        return result;
    }

private:
    std::list<std::shared_ptr<VarType>> formals;

    std::shared_ptr<VarType> result;
};

S_table EnvironmentEntry::enterBaseTypeEnvironment() {
    S_table environment = S_empty();
    S_enter(environment, S_Symbol(toCharString("boolean")), pack(new VariableEnvironmentEntry(VarType::getBooleanType())));
    S_enter(environment, S_Symbol(toCharString("char")), pack(new VariableEnvironmentEntry(VarType::getCharType())));
    S_enter(environment, S_Symbol(toCharString("integer")),  pack(new VariableEnvironmentEntry(VarType::getIntegerType())));
    S_enter(environment, S_Symbol(toCharString("real")), pack(new VariableEnvironmentEntry(VarType::getRealType())));
    S_enter(environment, S_Symbol(toCharString("string")), pack(new VariableEnvironmentEntry(VarType::getStringType())));

    //system functions
    S_enter(environment, S_Symbol(toCharString("writeln")), pack(new FunctionEnvironmentEntry({VarType::getIntegerType()}, VarType::getVoidType())));
    S_enter(environment, S_Symbol(toCharString("write")), pack(new FunctionEnvironmentEntry({VarType::getIntegerType()}, VarType::getVoidType())));
    S_enter(environment, S_Symbol(toCharString("read")), pack(new FunctionEnvironmentEntry({VarType::getIntegerType()}, VarType::getVoidType())));
    return environment;
}

S_table EnvironmentEntry::enterBaseValueEnvironment() {
    S_table environment = S_empty();
    S_enter(environment, S_Symbol(toCharString("true")), pack(new ConstIntVariableEnvironnmentEntry(1)));
    S_enter(environment, S_Symbol(toCharString("false")), pack(new ConstIntVariableEnvironnmentEntry(0)));
    S_enter(environment, S_Symbol(toCharString("maxint")), pack(new VariableEnvironmentEntry(VarType::getIntegerType(), true)));
    return environment;
}


#endif //SPL_COMPILER_ENV_H
