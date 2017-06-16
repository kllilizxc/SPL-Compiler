#ifndef SPL_COMPILER_IR_H
#define SPL_COMPILER_IR_H

#include "llvm/ADT/STLExtras.h"
#include "llvm/Analysis/BasicAliasAnalysis.h"
#include "llvm/Analysis/Passes.h"
#include "llvm/IR/DIBuilder.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Verifier.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Transforms/Scalar.h"
#include "llvm/IR/TypeBuilder.h"
#include <cstdio>
#include <string>
#include <map>
#include <vector>

extern "C" {
#include "symbol.h"
};

using namespace llvm;

class IR {
public:
    static bool inTopFunc;

    static AllocaInst *CreateEntryBlockAlloca(Function *TheFunction,
                                              const std::string &VarName, Type *type) {
        IRBuilder<> TmpB(&TheFunction->getEntryBlock(),
                         TheFunction->getEntryBlock().begin());
        return TmpB.CreateAlloca(type, nullptr,
                                 VarName.c_str());
    }

    static Type *genType(std::shared_ptr<VarType> type) {
        if (type == nullptr)
            return Type::getVoidTy(TheContext);
        else if (type == VarType::getIntegerType())
            return Type::getInt32Ty(TheContext);
        else if (type == VarType::getBooleanType())
            return Type::getInt32Ty(TheContext);
        else if (type == VarType::getCharType())
            return Type::getInt8Ty(TheContext);
        else if (type == VarType::getStringType())
            return Type::getInt8PtrTy(TheContext);
        else if (type == VarType::getRealType())
            return Type::getDoubleTy(TheContext);
        else if (type->getKind() == TypeKind::Record) {
            auto recordType = std::static_pointer_cast<RecordVarType>(type);
            assert(recordType != nullptr);

            std::vector<Type *> types;
            for (auto field : recordType->getFieldList()) {
                types.push_back(genType(field.getType()));
            }
            ArrayRef<Type *> fields(types);

            return StructType::get(TheContext, fields);
        } else if (type->getKind() == TypeKind::Array) {
            auto arrayType = std::static_pointer_cast<ArrayVarType>(type);
            assert(arrayType != nullptr);

            return ArrayType::get(genType(arrayType->getType()), arrayType->getRangeType()->getSize());
        }
        if (type->getKind() == TypeKind::Enum) {
            auto enumType = std::static_pointer_cast<EnumVarType>(type);
            assert(enumType != nullptr);

            int index = 0;
            for (auto name : enumType->getItems()) {
                NamedValues[S_name(name)] = ConstantInt::get(TheContext, APInt(32, index++));
            }

            return Type::getInt32Ty(TheContext); //Enum seen as integer
        } else if (type->getKind() == TypeKind::Range) {
            return Type::getInt32Ty(TheContext);
        } else
            return Type::getInt32Ty(TheContext);
    }

    static bool isConst(Value *value) {
        return !NamedValues[value->getName()];
    }

    static bool isPtrType(Type *type) {
        return type != Type::getDoubleTy(TheContext)
               && type != Type::getInt32Ty(TheContext)
               && type != Type::getInt8Ty(TheContext);
    }


    Value *loadIfIsConst(Value *value) {
        return isConst(value) ? value : Builder.CreateLoad(value, value->getType());
    }

    static void genBaseNamedValues() {
        NamedValues["true"] = ConstantInt::get(Type::getInt32Ty(TheContext), APInt(32, 1));
        NamedValues["false"] = ConstantInt::get(Type::getInt32Ty(TheContext), APInt(32, 0));
        NamedValues["maxint"] = ConstantInt::get(Type::getInt32Ty(TheContext), APInt(32, INT32_MAX));
    }

    template<class T>
    static void linkExternFunction(std::string name) {
        FunctionType *type = TypeBuilder<T, false>::get(TheContext);
        auto function = Function::Create(type, Function::ExternalLinkage, name, TheModule.get());
        function->setCallingConv(CallingConv::C);
    }

    static void linkBaseFunctions() {
        linkExternFunction<int(char *, ...)>("printf");
    }

    static std::map<std::string, Value *> backUpNamedValues() {
        std::map<std::string, Value *> backup;
        backup.insert(NamedValues.begin(), NamedValues.end());
        return backup;
    };

    static void restoreNamedValues(std::map<std::string, Value *> backup) {
        NamedValues.clear();
        NamedValues = backup;
    }

    static std::map<std::string, Type *> backUpNamedTypes() {
        std::map<std::string, Type *> backup;
        backup.insert(NamedTypes.begin(), NamedTypes.end());
        return backup;
    };

    static void restoreNamedTypes(std::map<std::string, Type *> backup) {
        NamedTypes.clear();
        NamedTypes = backup;
    }

    virtual Value *genCode() = 0;

    virtual Value *genCodeGlobal() {
        return genCode();
    }

    static LLVMContext TheContext;
    static std::unique_ptr<Module> TheModule;
    static IRBuilder<> Builder;
    static std::map<std::string, Value *> NamedValues;
    static std::map<std::string, Type *> NamedTypes;
    static std::map<std::string, BasicBlock *> NamedLabels;
};

class ConstIntIR : public IR {
private:
    int val;
public:
    ConstIntIR(int val) : val(val) {}

    int getVal() const {
        return val;
    }

    Value *genCode() {
        return ConstantInt::get(TheContext, APInt(32, val));
    }
};

class ConstBoolIR : public IR {
private:
    bool val;
public:
    ConstBoolIR(bool val) : val(val) {}

    bool getVal() const {
        return val;
    }

    Value *genCode() {
        return ConstantInt::get(TheContext, APInt(32, val));
    }
};

class ConstRealIR : public IR {
private:
    double val;
public:
    ConstRealIR(double val) : val(val) {}

    double getVal() const {
        return val;
    }

    Value *genCode() {
        return ConstantFP::get(TheContext, APFloat(val));
    }
};

class ConstCharIR : public IR {
private:
    char val;
public:
    ConstCharIR(char val) : val(val) {}

    char getVal() const {
        return val;
    }

    Value *genCode() {
        return ConstantInt::get(TheContext, APInt(8, val));
    }
};

class ConstStringIR : public IR {
private:
    std::string val;
public:
    ConstStringIR(std::string val) : val(val) {}

    std::string getVal() const {
        return val;
    }

    Value *genCode() {
        ArrayType *type = ArrayType::get(Type::getInt8Ty(TheContext), val.size() + 1);
        auto theString = Builder.CreateAlloca(type);
        Builder.CreateStore(ConstantDataArray::getString(TheContext, val, true), theString);

        return Builder.CreateBitCast(theString, Type::getInt8PtrTy(TheContext));
    }
};

class OpPlusIR : public IR {
private:
    IR *L;
    IR *R;
public:
    OpPlusIR(IR *L, IR *R) : L(L), R(R) {}

    Value *genCode() {
        return Builder.CreateAdd(loadIfIsConst(L->genCode()), loadIfIsConst(R->genCode()));
    }
};

class OpMinusIR : public IR {
private:
    IR *L;
    IR *R;
public:
    OpMinusIR(IR *L, IR *R) : L(L), R(R) {}

    Value *genCode() {
        return Builder.CreateSub(loadIfIsConst(L->genCode()), loadIfIsConst(R->genCode()));
    }
};

class OpTimesIR : public IR {
private:
    IR *L;
    IR *R;
public:
    OpTimesIR(IR *L, IR *R) : L(L), R(R) {}

    Value *genCode() {
        return Builder.CreateMul(loadIfIsConst(L->genCode()), loadIfIsConst(R->genCode()));
    }
};

class OpDivideIR : public IR {
private:
    IR *L;
    IR *R;
public:
    OpDivideIR(IR *L, IR *R) : L(L), R(R) {}

    Value *genCode() {
        return Builder.CreateUDiv(loadIfIsConst(L->genCode()), loadIfIsConst(R->genCode()));
    }
};

class OpEqIR : public IR {
private:
    IR *L;
    IR *R;
public:
    OpEqIR(IR *L, IR *R) : L(L), R(R) {}

    Value *genCode() {
        return Builder.CreateICmpEQ(loadIfIsConst(L->genCode()), loadIfIsConst(R->genCode()));
    }
};

class OpNeqIR : public IR {
private:
    IR *L;
    IR *R;
public:
    OpNeqIR(IR *L, IR *R) : L(L), R(R) {}

    Value *genCode() {
        return Builder.CreateICmpNE(loadIfIsConst(L->genCode()), loadIfIsConst(R->genCode()));
    }
};

class OpLtIR : public IR {
private:
    IR *L;
    IR *R;
public:
    OpLtIR(IR *L, IR *R) : L(L), R(R) {}

    Value *genCode() {
        return Builder.CreateICmpULT(loadIfIsConst(L->genCode()), loadIfIsConst(R->genCode()));
    }
};

class OpLeIR : public IR {
private:
    IR *L;
    IR *R;
public:
    OpLeIR(IR *L, IR *R) : L(L), R(R) {}

    Value *genCode() {
        return Builder.CreateICmpULE(loadIfIsConst(L->genCode()), loadIfIsConst(R->genCode()));
    }
};

class OpGtIR : public IR {
private:
    IR *L;
    IR *R;
public:
    OpGtIR(IR *L, IR *R) : L(L), R(R) {}

    Value *genCode() {
        return Builder.CreateICmpUGT(loadIfIsConst(L->genCode()), loadIfIsConst(R->genCode()));
    }
};

class OpGeIR : public IR {
private:
    IR *L;
    IR *R;
public:
    OpGeIR(IR *L, IR *R) : L(L), R(R) {}

    Value *genCode() {
        return Builder.CreateICmpUGE(loadIfIsConst(L->genCode()), loadIfIsConst(R->genCode()));
    }
};


class FOpPlusIR : public IR {
private:
    IR *L;
    IR *R;
public:
    FOpPlusIR(IR *L, IR *R) : L(L), R(R) {}

    Value *genCode() {
        return Builder.CreateFAdd(loadIfIsConst(L->genCode()), loadIfIsConst(R->genCode()));
    }
};

class FOpMinusIR : public IR {
private:
    IR *L;
    IR *R;
public:
    FOpMinusIR(IR *L, IR *R) : L(L), R(R) {}

    Value *genCode() {
        return Builder.CreateFSub(loadIfIsConst(L->genCode()), loadIfIsConst(R->genCode()));
    }
};

class FOpTimesIR : public IR {
private:
    IR *L;
    IR *R;
public:
    FOpTimesIR(IR *L, IR *R) : L(L), R(R) {}

    Value *genCode() {
        return Builder.CreateFMul(loadIfIsConst(L->genCode()), loadIfIsConst(R->genCode()));
    }
};

class FOpDivideIR : public IR {
private:
    IR *L;
    IR *R;
public:
    FOpDivideIR(IR *L, IR *R) : L(L), R(R) {}

    Value *genCode() {
        return Builder.CreateFDiv(loadIfIsConst(L->genCode()), loadIfIsConst(R->genCode()));
    }
};

class FOpEqIR : public IR {
private:
    IR *L;
    IR *R;
public:
    FOpEqIR(IR *L, IR *R) : L(L), R(R) {}

    Value *genCode() {
        return Builder.CreateFCmpUEQ(loadIfIsConst(L->genCode()), loadIfIsConst(R->genCode()));
    }
};

class FOpNeqIR : public IR {
private:
    IR *L;
    IR *R;
public:
    FOpNeqIR(IR *L, IR *R) : L(L), R(R) {}

    Value *genCode() {
        return Builder.CreateFCmpUNE(loadIfIsConst(L->genCode()), loadIfIsConst(R->genCode()));
    }
};

class FOpLtIR : public IR {
private:
    IR *L;
    IR *R;
public:
    FOpLtIR(IR *L, IR *R) : L(L), R(R) {}

    Value *genCode() {
        return Builder.CreateFCmpULT(loadIfIsConst(L->genCode()), loadIfIsConst(R->genCode()));
    }
};

class FOpLeIR : public IR {
private:
    IR *L;
    IR *R;
public:
    FOpLeIR(IR *L, IR *R) : L(L), R(R) {}

    Value *genCode() {
        return Builder.CreateFCmpULE(loadIfIsConst(L->genCode()), loadIfIsConst(R->genCode()));
    }
};

class FOpGtIR : public IR {
private:
    IR *L;
    IR *R;
public:
    FOpGtIR(IR *L, IR *R) : L(L), R(R) {}

    Value *genCode() {
        return Builder.CreateFCmpUGT(loadIfIsConst(L->genCode()), loadIfIsConst(R->genCode()));
    }
};

class FOpGeIR : public IR {
private:
    IR *L;
    IR *R;
public:
    FOpGeIR(IR *L, IR *R) : L(L), R(R) {}

    Value *genCode() {
        return Builder.CreateFCmpUGE(loadIfIsConst(L->genCode()), loadIfIsConst(R->genCode()));
    }
};

class SimpleVarIR : public IR {
private:
    std::string name;
public:
    SimpleVarIR(std::string name) : name(name) {}

    Value *genCode() {
//        return Builder.CreateLoad(NamedValues[name], name.c_str());
        return NamedValues[name];
    }
};

class SubscriptVarIR : public IR {
private:
    std::string name;
    IR *subscript;
public:
    SubscriptVarIR(const std::string &name, IR *subscript) : name(name), subscript(subscript) {}

    Value *genCode() {
        Value *array = NamedValues[name];
        ArrayType *type = static_cast<ArrayType *>(NamedTypes[name]);

        assert(type && "No such array!");
        Value *subscriptVal = subscript->genCode();

        return Builder.CreateInBoundsGEP(type, array, ArrayRef<Value *>({ConstantInt::get(TheContext, APInt(32, 0)),
                                                                         subscriptVal}));
    }
};

class FieldVarIR : public IR {
private:
    std::string recordName;
    std::string fieldName;
    int fieldIndex;
public:
    FieldVarIR(std::string recordName, std::string fieldName, int fieldIndex) : recordName(recordName),
                                                                                fieldName(fieldName),
                                                                                fieldIndex(fieldIndex) {}

    Value *genCode() {
        Value *record = NamedValues[recordName];
        StructType *type = static_cast<StructType *>(NamedTypes[recordName]);

        assert(type && "No such record!");

        return Builder.CreateStructGEP(type, record, fieldIndex, recordName + "_" + fieldName);
    }
};

class ConstVarDecIR : public IR {
private:
    std::string name;
    IR *value;
public:
    ConstVarDecIR(std::string name, IR *value) : name(name), value(value) {}

    Value *genCode() {
        NamedValues[name] = value->genCode();
        return NamedValues[name];
    }
};

class ProcIR : public IR {
private:
    std::string name;
    std::vector<IR *> args;
public:
    ProcIR(std::string name, std::vector<IR *> args) : name(name), args(args) {}

    Value *genCode() {
        Function *callee = TheModule->getFunction(name.c_str());
        assert(callee && "Undefined Function!");

        std::vector<Value *> argValues;

        for (auto arg : args) {
            Value *argVal = arg->genCode();
            assert(argVal);
            argValues.push_back(loadIfIsConst(argVal));
        }

        return Builder.CreateCall(callee, argValues);
    }
};

class AssignIR : public IR {
private:
    IR *var;
    IR *exp;
public:
    AssignIR(IR *var, IR *exp) : var(var), exp(exp) {}

    Value *genCode() {
        return Builder.CreateStore(loadIfIsConst(exp->genCode()), var->genCode());
    }
};

class IfIR : public IR {
private:
    IR *condition;
    IR *thenIR;
    IR *elseIR;
public:
    IfIR(IR *condition, IR *thenIR, IR *elseIR) : condition(condition), thenIR(thenIR), elseIR(elseIR) {}

    Value *genCode() {
        auto backupValues = backUpNamedValues();
        auto backupTypes = backUpNamedTypes();

        Function *theFunction = Builder.GetInsertBlock()->getParent();

        BasicBlock *thenBlock = BasicBlock::Create(TheContext, "then", theFunction);
        BasicBlock *elseBlock = BasicBlock::Create(TheContext, "else");
        BasicBlock *mergeBlock = BasicBlock::Create(TheContext, "final");

        Builder.CreateCondBr(condition->genCode(), thenBlock, elseBlock);

        Builder.SetInsertPoint(thenBlock);

        if (!thenIR) return nullptr;
        thenIR->genCode();

        Builder.CreateBr(mergeBlock);
        thenBlock = Builder.GetInsertBlock();

        theFunction->getBasicBlockList().push_back(elseBlock);
        Builder.SetInsertPoint(elseBlock);

        if (!elseIR) return nullptr;
        elseIR->genCode();

        Builder.CreateBr(mergeBlock);
        thenBlock = Builder.GetInsertBlock();

        theFunction->getBasicBlockList().push_back(mergeBlock);
        Builder.SetInsertPoint(mergeBlock);

        restoreNamedValues(backupValues);
        restoreNamedTypes(backupTypes);

        // if expr always returns 0.0.
        return Constant::getNullValue(Type::getDoubleTy(TheContext));
    }
};

class ForIR : public IR {
private:
    std::string var;
    IR *startIR;
    IR *endIR;
    IR *doIR;
public:
    ForIR(std::string var, IR *startIR, IR *endIR, IR *doIR) : var(var), startIR(startIR), endIR(endIR), doIR(doIR) {}

    Value *genCode() {
        auto backupValues = backUpNamedValues();
        auto backupTypes = backUpNamedTypes();

        Function *TheFunction = Builder.GetInsertBlock()->getParent();

        // Create an alloca for the variable in the entry block.
        AllocaInst *Alloca = CreateEntryBlockAlloca(TheFunction, var.c_str(), Type::getInt32Ty(TheContext));

        // Store the value into the alloca.
        Builder.CreateStore(startIR->genCode(), Alloca);

        BasicBlock *entryBB = BasicBlock::Create(TheContext, "entry", TheFunction);
        BasicBlock *LoopBB = BasicBlock::Create(TheContext, "loop");
        // Create the "after loop" block and insert it.
        BasicBlock *AfterBB = BasicBlock::Create(TheContext, "afterloop");

        // Insert an explicit fall through from the current block to the EntryBB.
        Builder.CreateBr(entryBB);

        Builder.SetInsertPoint(entryBB);

        // the body of the loop mutates the variable.
        Value *CurVar = Builder.CreateLoad(Alloca, var.c_str());

        Value *EndCond = Builder.CreateICmpUGE(endIR->genCode(), CurVar, "loopcond");

        // Insert the conditional branch into the end of LoopEndBB.
        Builder.CreateCondBr(EndCond, LoopBB, AfterBB);

        // Make the new basic block for the loop header, inserting after current
        // block.
        TheFunction->getBasicBlockList().push_back(LoopBB);

        // Start insertion in LoopBB.
        Builder.SetInsertPoint(LoopBB);

        // Within the loop, the variable is defined equal to the PHI node.  If it
        // shadows an existing variable, we have to restore it, so save it now.
        AllocaInst *OldVal = (AllocaInst *) NamedValues[var];
        NamedValues[var] = Alloca;

        doIR->genCode();

        Value *StepVal = ConstantInt::get(TheContext, APInt(32, 1));

        Value *NextVar = Builder.CreateAdd(CurVar, StepVal, "nextvar");
        Builder.CreateStore(NextVar, Alloca);

        Builder.CreateBr(entryBB);

        TheFunction->getBasicBlockList().push_back(AfterBB);
        // Any new code will be inserted in AfterBB.
        Builder.SetInsertPoint(AfterBB);

        // Restore the unshadowed variable.
        if (OldVal)
            NamedValues[var] = OldVal;
        else
            NamedValues.erase(var);

        restoreNamedValues(backupValues);
        restoreNamedTypes(backupTypes);

        // for expr always returns 0
        return Constant::getNullValue(Type::getInt32PtrTy(TheContext));
    }
};

class RepeatIR : public IR {
private:
    IR *condition;
    std::vector<IR *> statements;
public:
    RepeatIR(IR *condition, const std::vector<IR *, std::allocator<IR *>> &statements) : condition(condition),
                                                                                         statements(statements) {}

    Value *genCode() {
        auto backupValues = backUpNamedValues();
        auto backupTypes = backUpNamedTypes();

        Function *TheFunction = Builder.GetInsertBlock()->getParent();

        // Make the new basic block for the loop header, inserting after current
        // block.
        BasicBlock *LoopBB = BasicBlock::Create(TheContext, "loop", TheFunction);

        // Insert an explicit fall through from the current block to the LoopBB.
        Builder.CreateBr(LoopBB);

        // Start insertion in LoopBB.
        Builder.SetInsertPoint(LoopBB);

        for (auto statement : statements) {
            statement->genCode();
        }

        // Create the "after loop" block and insert it.
        BasicBlock *AfterBB =
                BasicBlock::Create(TheContext, "afterloop", TheFunction);

        // Insert the conditional branch into the end of LoopEndBB.
        Builder.CreateCondBr(condition->genCode(), AfterBB, LoopBB);

        // Any new code will be inserted in AfterBB.
        Builder.SetInsertPoint(AfterBB);

        restoreNamedValues(backupValues);
        restoreNamedTypes(backupTypes);

        // for expr always returns 0
        return Constant::getNullValue(Type::getInt32PtrTy(TheContext));
    }
};

class WhileIR : public IR {
private:
    IR *condition;
    IR *statement;
public:
    WhileIR(IR *condition, IR *statement) : condition(condition), statement(statement) {}

    Value *genCode() {
        auto backupValues = backUpNamedValues();
        auto backupTypes = backUpNamedTypes();

        Function *TheFunction = Builder.GetInsertBlock()->getParent();

        BasicBlock *entryBB = BasicBlock::Create(TheContext, "entry", TheFunction);

        // Insert an explicit fall through from the current block to the EntryBB.
        Builder.CreateBr(entryBB);

        Builder.SetInsertPoint(entryBB);

        // Make the new basic block for the loop header, inserting after current
        // block.
        BasicBlock *LoopBB = BasicBlock::Create(TheContext, "loop");
        // Create the "after loop" block and insert it.
        BasicBlock *AfterBB = BasicBlock::Create(TheContext, "afterloop");

        // Insert the conditional branch into the end of LoopEndBB.
        Builder.CreateCondBr(condition->genCode(), LoopBB, AfterBB);

        TheFunction->getBasicBlockList().push_back(LoopBB);
        // Start insertion in LoopBB.
        Builder.SetInsertPoint(LoopBB);

        statement->genCode();

        // Insert an explicit fall through from the current block to the LoopBB.
        Builder.CreateBr(entryBB);

        TheFunction->getBasicBlockList().push_back(AfterBB);
        // Any new code will be inserted in AfterBB.
        Builder.SetInsertPoint(AfterBB);

        restoreNamedValues(backupValues);
        restoreNamedTypes(backupTypes);

        // for expr always returns 0
        return Constant::getNullValue(Type::getInt32PtrTy(TheContext));
    }
};

class CaseIR : public IR {
private:
    IR *condition;
    std::vector<int> testCases;
    std::vector<IR *> statements;
public:
    CaseIR(IR *condition, const std::vector<int, std::allocator<int>> &testCases,
           const std::vector<IR *, std::allocator<IR *>> &statements) : condition(condition),
                                                                        testCases(testCases),
                                                                        statements(statements) {}

    Value *genCode() {
        auto backupValues = backUpNamedValues();
        auto backupTypes = backUpNamedTypes();

        Function *TheFunction = Builder.GetInsertBlock()->getParent();

        BasicBlock *exitBB = BasicBlock::Create(TheContext, "exit");

        SwitchInst *switchInst = Builder.CreateSwitch(loadIfIsConst(condition->genCode()), exitBB, testCases.size());
        int index = 0;
        for (auto testCase : testCases) {
            // Make the new basic block for the loop header, inserting after current
            // block.
            BasicBlock *caseBB = BasicBlock::Create(TheContext, "case", TheFunction);

            Builder.SetInsertPoint(caseBB);

            statements[index++]->genCode();

            Builder.CreateBr(exitBB);

            switchInst->addCase(ConstantInt::get(Type::getInt32Ty(TheContext), testCase), caseBB);
        }

        TheFunction->getBasicBlockList().push_back(exitBB);
        Builder.SetInsertPoint(exitBB);

        restoreNamedValues(backupValues);
        restoreNamedTypes(backupTypes);

        return nullptr;
    }
};

class GotoIR : public IR {
private:
    std::string name;
public:
    GotoIR(std::string name) : name(name) {}

    Value *genCode() {
        BasicBlock *des = NamedLabels[name];
        assert(des);
        Builder.CreateBr(des);

        return nullptr;
    }
};

class LabelDecIR : public IR {
private:
    std::string name;
public:
    LabelDecIR(std::string name) : name(name) {}

    Value *genCode() {
        Function *TheFunction = Builder.GetInsertBlock()->getParent();
        if (!TheFunction || name.size() == 0)
            return nullptr;

        // Create a new basic block to start insertion into.
        BasicBlock *BB = BasicBlock::Create(TheContext, name, TheFunction);
        Builder.CreateBr(BB);
        Builder.SetInsertPoint(BB);
        assert(BB);

        NamedLabels[name] = BB;

        return nullptr;
    }
};

class CompoundIR : public IR {
private:
    std::vector<IR *> statements;
public:
    CompoundIR(std::vector<IR *> statements) : statements(statements) {}

    std::vector<IR *> &getStatements() {
        return statements;
    }

    Value *genCode() {

        Value *returnVal = nullptr;
        for (auto statement : statements) {
            assert(statement);
            returnVal = statement->genCode();
        }

        return returnVal;
    }

    Value *genCodeGlobal() {
        Value *returnVal = nullptr;
        for (auto statement : statements) {
            assert(statement);
            returnVal = statement->genCodeGlobal();
        }

        return returnVal;
    }
};

class VarDecIR : public IR {
protected:
    std::vector<std::string> names;
    Type *type;
public:
    VarDecIR(std::vector<std::string> names, Type *type) : names(names), type(type) {}

    void decVar(Function *TheFunction, std::string name) {
        AllocaInst *Alloca = CreateEntryBlockAlloca(TheFunction, name.c_str(), type);
        NamedValues[name] = Alloca;
        NamedTypes[name] = type;
    }

    virtual Value *genCode() {
        Function *TheFunction = Builder.GetInsertBlock()->getParent();

        // Register all variables and emit their initializer.
        for (auto name : names) {
            decVar(TheFunction, name);
        }

        return nullptr;
    }

    Value *genCodeGlobal() {
        Function *TheFunction = Builder.GetInsertBlock()->getParent();

        // Register all variables and emit their initializer.
        for (auto name : names) {
            TheModule->getOrInsertGlobal(name, type);
            auto globalVar = TheModule->getNamedGlobal(name);
            globalVar->setInitializer(ConstantAggregateZero::get(type));
            globalVar->setLinkage(GlobalVariable::InternalLinkage);
            globalVar->setAlignment(4);
            NamedValues[name] = globalVar;
            NamedTypes[name] = type;
        }

        return nullptr;
    }
};

class RoutineDecIR : public IR {
private:
    std::string name;
    std::vector<std::string> fieldNames;
    std::vector<Type *> fieldTypes;
    Type *returnType;
    IR *body;
public:
    RoutineDecIR(std::string name, std::vector<std::string> fieldNames, std::vector<Type *> fieldTypes,
                 Type *returnType, IR *body) : name(name), fieldNames(fieldNames), fieldTypes(fieldTypes),
                                               returnType(returnType), body(body) {}

    std::string getName() {
        return name;
    }

    Value *genCode() {
        FunctionType *FT =
                FunctionType::get(returnType ? returnType : Type::getVoidTy(TheContext), fieldTypes, false);

        Function *TheFunction =
                Function::Create(FT, Function::ExternalLinkage, name.c_str(), TheModule.get());

        // Set names for all arguments.
        int index = 0;
        for (auto &Arg : TheFunction->args())
            Arg.setName(fieldNames[index++]);

        if (body)
            return body->genCode();
        else
            return TheFunction;
    }
};

class RoutineBodyIR : public IR {
public:
    std::string functionName;
    IR *labelDecIR;
    IR *constDecIR;
    IR *typeDecIR;
    IR *varDecIR;
    IR *routineDecIR;
    IR *funcBodyIR;
public:
    RoutineBodyIR(std::string functionName, IR *labelDecIR, IR *constDecIR, IR *typeDecIR, IR *varDecIR,
                  IR *routineDecIR,
                  IR *funcBodyIR) : functionName(functionName), labelDecIR(labelDecIR), constDecIR(constDecIR),
                                    typeDecIR(typeDecIR), varDecIR(varDecIR), routineDecIR(routineDecIR),
                                    funcBodyIR(funcBodyIR) {}

    virtual Value *genCode() {
        auto backupValues = backUpNamedValues();
        auto backupTypes = backUpNamedTypes();

        Function *TheFunction = TheModule->getFunction(functionName);
        if (!TheFunction)
            return nullptr;

        // Create a new basic block to start insertion into.
        BasicBlock *BB = BasicBlock::Create(TheContext, functionName, TheFunction);
        Builder.SetInsertPoint(BB);

        if (TheFunction->getReturnType() != Type::getVoidTy(TheContext)) {
            VarDecIR returnVar({TheFunction->getName()}, TheFunction->getReturnType());
            returnVar.genCode();
        }

        for (auto &Arg : TheFunction->args()) {
            // Create an alloca for this variable.
            AllocaInst *Alloca = CreateEntryBlockAlloca(TheFunction, Arg.getName().data(), Arg.getType());

            // Store the initial value into the alloca.
            Builder.CreateStore(&Arg, Alloca);

            // Add arguments to variable symbol table.
            NamedValues[Arg.getName()] = Alloca;
        }

        if (labelDecIR) labelDecIR->genCode();
        if (constDecIR) constDecIR->genCode();
//        if (typeDecIR) typeDecIR->genCode();
        if (varDecIR) varDecIR->genCode();
        if (routineDecIR) routineDecIR->genCode();

        Builder.SetInsertPoint(&TheFunction->getEntryBlock());
        if (funcBodyIR) funcBodyIR->genCode();

        Value *RetVal;
        if (TheFunction->getReturnType() != Type::getVoidTy(TheContext) &&
            (RetVal = NamedValues[TheFunction->getName()])) {
            // Finish off the function.
            Builder.CreateRet(Builder.CreateLoad(RetVal, RetVal->getName()));
        } else {
            Builder.CreateRet(nullptr);
        }

        // Validate the generated code, checking for consistency.
        verifyFunction(*TheFunction);

        restoreNamedValues(backupValues);
        restoreNamedTypes(backupTypes);

        return TheFunction;
    }
};

class ProgramIR : public RoutineBodyIR {
    friend class RoutineBodyIR;

public:
    ProgramIR(std::string name, RoutineBodyIR *body) :
            RoutineBodyIR(name, body->labelDecIR, body->constDecIR, body->typeDecIR, body->varDecIR, body->routineDecIR,
                          body->funcBodyIR) {}

    virtual Value *genCode() {
        FunctionType *FT =
                FunctionType::get(Type::getVoidTy(TheContext), std::vector<Type *>(), false);

        Function *TheFunction =
                Function::Create(FT, Function::ExternalLinkage, "main", TheModule.get());

        BasicBlock *BB = BasicBlock::Create(TheContext, functionName, TheFunction);
        Builder.SetInsertPoint(BB);

        if (labelDecIR) labelDecIR->genCodeGlobal();
        if (constDecIR) constDecIR->genCodeGlobal();
//        if (typeDecIR) typeDecIR->genCode();
        if (varDecIR) varDecIR->genCodeGlobal();
        if (routineDecIR) routineDecIR->genCode();

        BasicBlock *bodyBlock = &TheFunction->getEntryBlock();
        Builder.SetInsertPoint(bodyBlock);
        if (funcBodyIR) funcBodyIR->genCodeGlobal();

        Builder.CreateRet(nullptr);

        // Validate the generated code, checking for consistency.
        verifyFunction(*TheFunction);

        return TheFunction;
    }

};

LLVMContext IR::TheContext;
IRBuilder<> IR::Builder(TheContext);
std::unique_ptr<Module> IR::TheModule = llvm::make_unique<Module>("Mine", IR::TheContext);
std::map<std::string, Value *> IR::NamedValues;
std::map<std::string, Type *> IR::NamedTypes;
std::map<std::string, BasicBlock *> IR::NamedLabels;
#endif