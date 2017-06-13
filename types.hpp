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

class VarType {
public:
    VarType(TypeKind kind = TypeKind::Nil, bool isConst = false) : kind(kind) {};

    static std::shared_ptr<VarType> &getNilType() {
        return NilType;
    }

    static std::shared_ptr<VarType> &getBooleanType() {
        return BooleanType;
    }

    static std::shared_ptr<VarType> &getCharType() {
        return CharType;
    }

    static std::shared_ptr<VarType> &getIntegerType() {
        return IntegerType;
    }

    static std::shared_ptr<VarType> &getRealType() {
        return RealType;
    }

    static std::shared_ptr<VarType> &getVoidType() {
        return VoidType;
    }

    static std::shared_ptr<VarType> &getStringType() {
        return StringType;
    }


    TypeKind getKind() const {
        return kind;
    }


private:
    TypeKind kind;


    static std::shared_ptr<VarType> NilType;
    static std::shared_ptr<VarType> BooleanType;
    static std::shared_ptr<VarType> CharType;
    static std::shared_ptr<VarType> IntegerType;
    static std::shared_ptr<VarType> RealType;
    static std::shared_ptr<VarType> VoidType;
    static std::shared_ptr<VarType> StringType;
};

std::shared_ptr<VarType> VarType::NilType(new VarType(TypeKind::Nil));
std::shared_ptr<VarType> VarType::BooleanType(new VarType(TypeKind::Boolean));
std::shared_ptr<VarType> VarType::CharType(new VarType(TypeKind::Char));
std::shared_ptr<VarType> VarType::IntegerType(new VarType(TypeKind::Integer));
std::shared_ptr<VarType> VarType::RealType(new VarType(TypeKind::Real));
std::shared_ptr<VarType> VarType::VoidType(new VarType(TypeKind::Void));
std::shared_ptr<VarType> VarType::StringType(new VarType(TypeKind::String));


class ArrayVarType : public VarType {
public:
    ArrayVarType(std::shared_ptr<VarType> type) : VarType(TypeKind::Array), type(type) {};

    std::shared_ptr<VarType> &getType() {
        return type;
    }

private:
    std::shared_ptr<VarType> type;
};

//class NameType : VarType {
//public:
//    NameType(std::shared_ptr<VarType> type = VarType::getNilType(), S_symbol symbol) : VarType(TypeKind::Name), type(type),
//                                                                                 symbol(symbol) {};
//
//    std::shared_ptr<VarType> &getType() const {
//        return type;
//    }
//
//    const S_symbol &getSymbol() const {
//        return symbol;
//    }
//
//private:
//    S_symbol symbol;
//    std::shared_ptr<VarType> type;
//};

class Field {
public:
    S_symbol getName() const {
        return name;
    }

    std::shared_ptr<VarType> &getType() {
        return type;
    }

    Field(S_symbol name, std::shared_ptr<VarType> type) : name(name), type(type) {};

private:
    S_symbol name;
    std::shared_ptr<VarType> type;
};

class RecordVarType : public VarType {
public:
    RecordVarType() : VarType(TypeKind::Record), fieldList() {};

    RecordVarType(std::list<Field> &filedList) : fieldList(fieldList), VarType(TypeKind::Record) {};

    std::list<Field> &getFieldList() {
        return fieldList;
    }

private:
    std::list<Field> fieldList;

};

class RangeType : public VarType {
public:
    RangeType(std::shared_ptr<VarType> type) : VarType(TypeKind::Range), type(type) {};

    std::shared_ptr<VarType> &getType() {
        return type;
    }

private:
    std::shared_ptr<VarType> type;
};

class EnumVarType : public VarType {
public:
    EnumVarType() : VarType(TypeKind::Enum) {};

    std::list<S_symbol> &getItems() {
        return items;
    }

private:
    std::list<S_symbol> items;
};

#endif //SPL_COMPILER_TYPES_H
