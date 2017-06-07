//
// Created by 54179 on 2017/6/2.
//

#ifndef SPL_COMPILER_TYPES_H
#define SPL_COMPILER_TYPES_H

#include <list>
#include <memory>
extern "C" {
#include "symbol.h"
};

//type class, represent variable types, used for semant analysing

enum class TypeKind {
    Nil, Boolean, Char, Integer, Real, Array, Record, Name, String, Range, Enum, Void
};

class Type {
public:
    Type(TypeKind kind = TypeKind::Nil, bool isConst = false) : kind(kind) {};

    static std::shared_ptr<Type> &getNilType() {
        return NilType;
    }

    static std::shared_ptr<Type> &getBooleanType() {
        return BooleanType;
    }

    static std::shared_ptr<Type> &getCharType() {
        return CharType;
    }

    static std::shared_ptr<Type> &getIntegerType() {
        return IntegerType;
    }

    static std::shared_ptr<Type> &getRealType() {
        return RealType;
    }

    static std::shared_ptr<Type> &getVoidType() {
        return VoidType;
    }

    static std::shared_ptr<Type> &getStringType() {
        return StringType;
    }


    TypeKind getKind() const {
        return kind;
    }


private:
    TypeKind kind;


    static std::shared_ptr<Type> NilType;
    static std::shared_ptr<Type> BooleanType;
    static std::shared_ptr<Type> CharType;
    static std::shared_ptr<Type> IntegerType;
    static std::shared_ptr<Type> RealType;
    static std::shared_ptr<Type> VoidType;
    static std::shared_ptr<Type> StringType;
};

std::shared_ptr<Type> Type::NilType(new Type(TypeKind::Nil));
std::shared_ptr<Type> Type::BooleanType(new Type(TypeKind::Boolean));
std::shared_ptr<Type> Type::CharType(new Type(TypeKind::Char));
std::shared_ptr<Type> Type::IntegerType(new Type(TypeKind::Integer));
std::shared_ptr<Type> Type::RealType(new Type(TypeKind::Real));
std::shared_ptr<Type> Type::VoidType(new Type(TypeKind::Void));
std::shared_ptr<Type> Type::StringType(new Type(TypeKind::String));


class ArrayType : public Type {
public:
    ArrayType(std::shared_ptr<Type> type) : Type(TypeKind::Array), type(type) {};

    std::shared_ptr<Type> &getType() {
        return type;
    }

private:
    std::shared_ptr<Type> type;
};

//class NameType : Type {
//public:
//    NameType(std::shared_ptr<Type> type = Type::getNilType(), S_symbol symbol) : Type(TypeKind::Name), type(type),
//                                                                                 symbol(symbol) {};
//
//    std::shared_ptr<Type> &getType() const {
//        return type;
//    }
//
//    const S_symbol &getSymbol() const {
//        return symbol;
//    }
//
//private:
//    S_symbol symbol;
//    std::shared_ptr<Type> type;
//};

class Field {
public:
    S_symbol getName() const {
        return name;
    }

    std::shared_ptr<Type> &getType() {
        return type;
    }

    Field(S_symbol name, std::shared_ptr<Type> type) : name(name), type(type) {};

private:
    S_symbol name;
    std::shared_ptr<Type> type;
};

class RecordType : public Type {
public:
    RecordType() : Type(TypeKind::Record) {};

    RecordType(std::list<Field> &filedList) : fieldList(fieldList), Type(TypeKind::Record) {};

    std::list<Field> &getFieldList() {
        return fieldList;
    }

private:
    std::list<Field> fieldList;

};

class RangeType : public Type {
public:
    RangeType(std::shared_ptr<Type> type) : Type(TypeKind::Range), type(type) {};

    std::shared_ptr<Type> &getType() {
        return type;
    }

private:
    std::shared_ptr<Type> type;
};

class EnumType : public Type {
public:
    EnumType() : Type(TypeKind::Enum) {};

    std::list<S_symbol> &getItems() {
        return items;
    }

private:
    std::list<S_symbol> items;
};

#endif //SPL_COMPILER_TYPES_H
