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
    static AllocaInst *CreateEntryBlockAlloca(Function *TheFunction,
                                              const std::string &VarName, Type *type) {
        IRBuilder<> TmpB(&TheFunction->getEntryBlock(),
                         TheFunction->getEntryBlock().begin());
        return TmpB.CreateAlloca(type, nullptr,
                                 VarName.c_str());
    }
    
    static Type *genSingleType(std::string type) {
        return NamedTypes[type];
    }
    
    static void genTypeDec(std::string name, Type *type) {
        NamedTypes[name] = type;
    }
    
    static Type *genType(std::shared_ptr<VarType> type) {
        if(type == VarType::getIntegerType())
            return Type::getInt32Ty(TheContext);
        else if(type == VarType::getIntegerType())
            return Type::getInt32Ty(TheContext);
        else if(type == VarType::getIntegerType())
            return Type::getInt32Ty(TheContext);
        else if(type == VarType::getIntegerType())
            return Type::getInt32Ty(TheContext);
        else
            return Type::getVoidTy(TheContext);
    }
    
    static void initSysTypes() {
        genTypeDec("integer", Type::getInt32Ty(TheContext));
        genTypeDec("char", Type::getInt32Ty(TheContext));
        genTypeDec("bool", Type::getInt32Ty(TheContext));
        genTypeDec("real", Type::getFloatTy(TheContext));
    }
    
    virtual Value *genCode() = 0;
    
    static LLVMContext TheContext;
    static Module *TheModule;
    static IRBuilder<> Builder;
    static std::map<std::string, Value *> NamedValues;
    static std::map<std::string, Type *> NamedTypes;
};

class ConstIntIR : public IR{
private:
    int val;
public:
    ConstIntIR(int val) : val(val) {}
    
    Value *genCode() {
        return ConstantInt::get(TheContext, APInt(32, val));
    }
};

class ConstRealIR : public IR{
private:
    double val;
public:
    ConstRealIR(double val) : val(val) {}
    
    Value *genCode() {
        return ConstantFP::get(TheContext, APFloat(val));
    }
};

class ConstBoolIR : public IR{
private:
    int val;
public:
    ConstBoolIR(int val) : val(val) {}
    
    Value *genCode() {
        return ConstantInt::get(TheContext, APInt(32, val));
    }
};

class ConstCharIR : public IR{
private:
    char val;
public:
    ConstCharIR(char val) : val(val) {}
    
    Value *genCode() {
        return ConstantInt::get(TheContext, APInt(8, val));
    }
};

class ConstStringIR : public IR{
private:
    char *val;
public:
    ConstStringIR(char *val) : val(val) {}
    
    Value *genCode() {
        return ConstantInt::get(TheContext, APInt(32, (uint64_t)(val)));
    }
};

class OpPlusIR : public IR {
private:
    IR *L;
    IR *R;
public:
    OpPlusIR(IR *L, IR *R) : L(L), R(R) {}
    
    Value *genCode() {
        return Builder.CreateAdd(L->genCode(), R->genCode());
    }
};

class OpMinusIR : public IR {
private:
    IR *L;
    IR *R;
public:
    OpMinusIR(IR *L, IR *R) : L(L), R(R) {}
    
    Value *genCode() {
        return Builder.CreateSub(L->genCode(), R->genCode());
    }
};

class OpTimesIR : public IR {
private:
    IR *L;
    IR *R;
public:
    OpTimesIR(IR *L, IR *R) : L(L), R(R) {}
    
    Value *genCode() {
        return Builder.CreateMul(L->genCode(), R->genCode());
    }
};

class OpDivideIR : public IR {
private:
    IR *L;
    IR *R;
public:
    OpDivideIR(IR *L, IR *R) : L(L), R(R) {}
    
    Value *genCode() {
        return Builder.CreateUDiv(L->genCode(), R->genCode());
    }
};

class OpEqIR : public IR {
private:
    IR *L;
    IR *R;
public:
    OpEqIR(IR *L, IR *R) : L(L), R(R) {}
    
    Value *genCode() {
        return Builder.CreateICmpEQ(L->genCode(), R->genCode());
    }
};

class OpNeqIR : public IR {
private:
    IR *L;
    IR *R;
public:
    OpNeqIR(IR *L, IR *R) : L(L), R(R) {}
    
    Value *genCode() {
        return Builder.CreateICmpNE(L->genCode(), R->genCode());
    }
};

class OpLtIR : public IR {
private:
    IR *L;
    IR *R;
public:
    OpLtIR(IR *L, IR *R) : L(L), R(R) {}
    
    Value *genCode() {
        return Builder.CreateICmpULT(L->genCode(), R->genCode());
    }
};

class OpLeIR : public IR {
private:
    IR *L;
    IR *R;
public:
    OpLeIR(IR *L, IR *R) : L(L), R(R) {}
    
    Value *genCode() {
        return Builder.CreateICmpULE(L->genCode(), R->genCode());
    }
};

class OpGtIR : public IR {
private:
    IR *L;
    IR *R;
public:
    OpGtIR(IR *L, IR *R) : L(L), R(R) {}
    
    Value *genCode() {
        return Builder.CreateICmpUGT(L->genCode(), R->genCode());
    }
};

class OpGeIR : public IR {
private:
    IR *L;
    IR *R;
public:
    OpGeIR(IR *L, IR *R) : L(L), R(R) {}
    
    Value *genCode() {
        return Builder.CreateICmpUGE(L->genCode(), R->genCode());
    }
};


class FOpPlusIR : public IR {
private:
    IR *L;
    IR *R;
public:
    FOpPlusIR(IR *L, IR *R) : L(L), R(R) {}
    
    Value *genCode() {
        return Builder.CreateFAdd(L->genCode(), R->genCode());
    }
};

class FOpMinusIR : public IR {
private:
    IR *L;
    IR *R;
public:
    FOpMinusIR(IR *L, IR *R) : L(L), R(R) {}
    
    Value *genCode() {
        return Builder.CreateFSub(L->genCode(), R->genCode());
    }
};

class FOpTimesIR : public IR {
private:
    IR *L;
    IR *R;
public:
    FOpTimesIR(IR *L, IR *R) : L(L), R(R) {}
    
    Value *genCode() {
        return Builder.CreateFMul(L->genCode(), R->genCode());
    }
};

class FOpDivideIR : public IR {
private:
    IR *L;
    IR *R;
public:
    FOpDivideIR(IR *L, IR *R) : L(L), R(R) {}
    
    Value *genCode() {
        return Builder.CreateFDiv(L->genCode(), R->genCode());
    }
};

class FOpEqIR : public IR {
private:
    IR *L;
    IR *R;
public:
    FOpEqIR(IR *L, IR *R) : L(L), R(R) {}
    
    Value *genCode() {
        return Builder.CreateFCmpUEQ(L->genCode(), R->genCode());
    }
};

class FOpNeqIR : public IR {
private:
    IR *L;
    IR *R;
public:
    FOpNeqIR(IR *L, IR *R) : L(L), R(R) {}
    
    Value *genCode() {
        return Builder.CreateFCmpUNE(L->genCode(), R->genCode());
    }
};

class FOpLtIR : public IR {
private:
    IR *L;
    IR *R;
public:
    FOpLtIR(IR *L, IR *R) : L(L), R(R) {}
    
    Value *genCode() {
        return Builder.CreateFCmpULT(L->genCode(), R->genCode());
    }
};

class FOpLeIR : public IR {
private:
    IR *L;
    IR *R;
public:
    FOpLeIR(IR *L, IR *R) : L(L), R(R) {}
    
    Value *genCode() {
        return Builder.CreateFCmpULE(L->genCode(), R->genCode());
    }
};

class FOpGtIR : public IR {
private:
    IR *L;
    IR *R;
public:
    FOpGtIR(IR *L, IR *R) : L(L), R(R) {}
    
    Value *genCode() {
        return Builder.CreateFCmpUGT(L->genCode(), R->genCode());
    }
};

class FOpGeIR : public IR {
private:
    IR *L;
    IR *R;
public:
    FOpGeIR(IR *L, IR *R) : L(L), R(R) {}
    
    Value *genCode() {
        return Builder.CreateFCmpUGE(L->genCode(), R->genCode());
    }
};

class SimpleVarIR : public IR {
private:
    std::string name;
public:
    SimpleVarIR(std::string name) : name(name) {}
    
    Value *genCode() {
        return NamedValues[name];
    }
};

class SubscriptVarIR : public IR { //TODO
private:
public:
    Value *genCode() {
        return nullptr;
    }
};

class FieldVarIR : public IR { //TODO
private:
    std::string name;
public:
    FieldVarIR(std::string recordName, std::string fieldName) {
        name = recordName + "_" + fieldName;
    }
    
    Value *genCode() {
        return NamedValues[name];
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
        
        std::vector<Value *> argValues;
        
        for(auto arg : args) {
            argValues.push_back(arg->genCode());
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
        return Builder.CreateStore(exp->genCode(), var->genCode());
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
        Function *theFunction = Builder.GetInsertBlock()->getParent();
        
        BasicBlock *thenBlock = BasicBlock::Create(TheContext, "then", theFunction);
        BasicBlock *elseBlock = BasicBlock::Create(TheContext, "else");
        BasicBlock *mergeBlock = BasicBlock::Create(TheContext, "final");
        
        Builder.CreateCondBr(condition->genCode(), thenBlock, elseBlock);
        
        Builder.SetInsertPoint(thenBlock);
        
        if(!thenIR) return nullptr;
        thenIR->genCode();
        
        Builder.CreateBr(mergeBlock);
        thenBlock = Builder.GetInsertBlock();
        
        theFunction->getBasicBlockList().push_back(elseBlock);
        Builder.SetInsertPoint(elseBlock);
        
        if(!elseIR) return nullptr;
        elseIR->genCode();
        
        Builder.CreateBr(mergeBlock);
        thenBlock = Builder.GetInsertBlock();
        
        theFunction->getBasicBlockList().push_back(mergeBlock);
        Builder.SetInsertPoint(mergeBlock);
        
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
        Function *TheFunction = Builder.GetInsertBlock()->getParent();
        
        // Create an alloca for the variable in the entry block.
        AllocaInst *Alloca = CreateEntryBlockAlloca(TheFunction, var.c_str(), Type::getInt32Ty(TheContext));
        
        // Store the value into the alloca.
        Builder.CreateStore(startIR->genCode(), Alloca);
        
        // Make the new basic block for the loop header, inserting after current
        // block.
        BasicBlock *LoopBB = BasicBlock::Create(TheContext, "loop", TheFunction);
        
        // Insert an explicit fall through from the current block to the LoopBB.
        Builder.CreateBr(LoopBB);
        
        // Start insertion in LoopBB.
        Builder.SetInsertPoint(LoopBB);
        
        // Within the loop, the variable is defined equal to the PHI node.  If it
        // shadows an existing variable, we have to restore it, so save it now.
        AllocaInst *OldVal = (AllocaInst *)NamedValues[var];
        NamedValues[var] = Alloca;
        
        //TODO where is the body?
        doIR->genCode();
        
        Value *StepVal = ConstantInt::get(TheContext, APInt(32, 1));
        
        // Reload, increment, and restore the alloca.  This handles the case where
        // the body of the loop mutates the variable.
        Value *CurVar = Builder.CreateLoad(Alloca, var.c_str());
        Value *NextVar = Builder.CreateFAdd(CurVar, StepVal, "nextvar");
        Builder.CreateStore(NextVar, Alloca);
        
        Value *EndCond = Builder.CreateFCmpONE(
                                               endIR->genCode(), CurVar, "loopcond");
        
        // Create the "after loop" block and insert it.
        BasicBlock *AfterBB =
        BasicBlock::Create(TheContext, "afterloop", TheFunction);
        
        // Insert the conditional branch into the end of LoopEndBB.
        Builder.CreateCondBr(EndCond, LoopBB, AfterBB);
        
        // Any new code will be inserted in AfterBB.
        Builder.SetInsertPoint(AfterBB);
        
        // Restore the unshadowed variable.
        if (OldVal)
            NamedValues[var] = OldVal;
        else
            NamedValues.erase(var);
        
        // for expr always returns 0.0.
        return Constant::getNullValue(Type::getDoubleTy(TheContext));
    }
};

class CompoundIR : public IR {
private:
    std::vector<IR *> statements;
public:
    CompoundIR(std::vector<IR *> statements) : statements(statements) {}
    
    Value *genCode() {
        Value *returnVal = nullptr;
        for(auto statement : statements) {
            returnVal = statement->genCode();
        }
        return returnVal;
    }
};

class VarDecIR : public IR {
private:
    std::vector<std::string> names;
    Type *type;
public:
    VarDecIR(std::vector<std::string> names, Type *type) : names(names), type(type) {}
    
    Value *genCode() {
        std::vector<AllocaInst *> OldBindings;
        
        Function *TheFunction = Builder.GetInsertBlock()->getParent();
        
        // Register all variables and emit their initializer.
        for(auto name : names) {
            //TODO only support simple type now
            AllocaInst *Alloca = CreateEntryBlockAlloca(TheFunction, name.c_str(), type);
            NamedValues[name] = Alloca;
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
public:
    RoutineDecIR(std::string name, std::vector<std::string> fieldNames, std::vector<Type *> fieldTypes, Type * returnType) : name(name), fieldNames(fieldNames), fieldTypes(fieldTypes), returnType(returnType) {}
    
    Value *genCode() {
        FunctionType *FT =
        FunctionType::get(returnType ? returnType : Type::getVoidTy(TheContext), fieldTypes, false);
        
        Function *TheFunction =
        Function::Create(FT, Function::ExternalLinkage, name.c_str(), TheModule);
        
        // Set names for all arguments.
        auto argIter = TheFunction->getArgumentList().begin();
        auto nameIter = fieldNames.begin();
        while(argIter != TheFunction->getArgumentList().end() && nameIter != fieldNames.end()) {
            (*argIter).setName((*nameIter).c_str());
            NamedValues[*nameIter] = &(*argIter);
        }
        
        return TheFunction;
    }
};

class RoutineBodyIR : public IR {
private:
    Function *TheFunction;
    IR *subroutine;
public:
    RoutineBodyIR(Function *TheFunction, IR *subroutine) : TheFunction(TheFunction), subroutine(subroutine) {}
    
    Value *genCode() {
        // Create a new basic block to start insertion into.
        BasicBlock *BB = BasicBlock::Create(TheContext, "entry", TheFunction);
        Builder.SetInsertPoint(BB);
        
        VarDecIR returnVar({TheFunction->getName()}, TheFunction->getReturnType());
        returnVar.genCode();
        if(subroutine)
            subroutine->genCode();
        if (Value *RetVal = NamedValues[TheFunction->getName()]) {
            // Finish off the function.
            Builder.CreateRet(RetVal);
            
            // Validate the generated code, checking for consistency.
            verifyFunction(*TheFunction);
            
        }
        
        return TheFunction;
    }
};


LLVMContext IR::TheContext;
IRBuilder<> IR::Builder (TheContext);
Module *IR::TheModule = new Module("Mine", IR::TheContext);
std::map<std::string, Value *> IR::NamedValues;
std::map<std::string, Type *> IR::NamedTypes;

#endif