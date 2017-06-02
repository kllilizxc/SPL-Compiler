//
// Created by 54179 on 2017/6/2.
//

#ifndef SPL_COMPILER_TYPES_H
#define SPL_COMPILER_TYPES_H

#include <list>
#include <bits/shared_ptr.h>

struct S_symbol {
};

class Type {
public:
    enum Kind {
        Nil, Boolean, Char, Integer, Real, Array, Record, Name, Void
    } kind;

    Type(Type::Kind kind = Type::Nil) : kind(kind) {};

    static const Type &getNilType() {
        return NilType;
    }

    static const Type &getBooleanType() {
        return BooleanType;
    }

    static const Type &getCharType() {
        return CharType;
    }

    static const Type &getIntegerType() {
        return IntegerType;
    }

    static const Type &getRealType() {
        return RealType;
    }

    static const Type &getVoidType() {
        return VoidType;
    }

private:
    const static Type NilType{Type::Nil};
    const static Type BooleanType{Type::Boolean};
    const static Type CharType{Type::Char};
    const static Type IntegerType{Type::Integer};
    const static Type RealType{Type::Real};
    const static Type VoidType{Type::Void};
};

class ArrayType : Type {
public:
    ArrayType(Type type = Type()) : Type(Type::Array), type(type) {};

    const Type &getType() const {
        return type;
    }

private:
    Type type;
};

class NameType : Type {
public:
    NameType(Type type = Type(), S_symbol symbol) : Type(Type::Name), type(type), symbol(symbol) {};

    const Type &getType() const {
        return type;
    }

    const S_symbol &getSymbol() const {
        return symbol;
    }

private:
    S_symbol symbol;
    Type type;
};

#endif //SPL_COMPILER_TYPES_H
