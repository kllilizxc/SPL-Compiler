//
// Created by 54179 on 2017/6/2.
//

#ifndef SPL_COMPILER_TYPES_H
#define SPL_COMPILER_TYPES_H

#include <list>
#include <bits/shared_ptr.h>
#include "symbol.h"

class Type {
public:
    Type(Type::Kind kind = Type::Nil) : kind(kind) {};

    static std::shared_ptr<Type> getNilType() {
        return std::shared_ptr<Type>(&NilType);
    }

    static std::shared_ptr<Type> getBooleanType() {
        return std::shared_ptr<Type>(&BooleanType);
    }

    static std::shared_ptr<Type> getCharType() {
        return std::shared_ptr<Type>(&CharType);
    }

    static std::shared_ptr<Type> getIntegerType() {
        return std::shared_ptr<Type>(&IntegerType);
    }

    static std::shared_ptr<Type> getRealType() {
        return std::shared_ptr<Type>(&RealType);
    }

    static std::shared_ptr<Type> getVoidType() {
        return std::shared_ptr<Type>(&VoidType);
    }

    Kind getKind() const {
        return kind;
    }

private:
    enum Kind {
        Nil, Boolean, Char, Integer, Real, Array, Record, Name, Void
    } kind;

    const static Type NilType{Type::Nil};
    const static Type BooleanType{Type::Boolean};
    const static Type CharType{Type::Char};
    const static Type IntegerType{Type::Integer};
    const static Type RealType{Type::Real};
    const static Type VoidType{Type::Void};
};

class ArrayType : Type {
public:
    ArrayType(std::shared_ptr<Type> type) : Type(Type::Array), type(type) {};

    std::shared_ptr<Type> &getType() const {
        return type;
    }

private:
    std::shared_ptr<Type> type;
};

class NameType : Type {
public:
    NameType(std::shared_ptr<Type> type = Type::getNilType(), S_symbol symbol) : Type(Type::Name), type(type), symbol(symbol) {};

    std::shared_ptr<Type> &getType() const {
        return type;
    }

    const S_symbol &getSymbol() const {
        return symbol;
    }

private:
    S_symbol symbol;
    std::shared_ptr<Type> type;
};

class Field {
public:
    S_symbol getName() const {
        return name;
    }

    std::shared_ptr<Type> &getType() const {
        return type;
    }

    Field(S_symbol name, std::shared_ptr<Type> type) : name(name), type(type) {};

private:
    S_symbol name;
    std::shared_ptr<Type> type;
};

class RecordType : Type {
public:
    RecordType() : Type(Type::Record) {};

    RecordType(std::list<Field> &filedList) : RecordType(), fieldList(fieldList) {};

    std::list<Field> &getFieldList() const {
        return fieldList;
    }

private:
    std::list<Field> fieldList;

};

#endif //SPL_COMPILER_TYPES_H
