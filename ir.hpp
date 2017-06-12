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
#include "absyn.h"
#include <cstdio>
#include "symbol.h"
#include "semant.hpp"
#include <string>
#include <map>
#include <vector>

using namespace llvm;

class IR {
public:
  static Value *genIntConst(int val) {
    return ConstantInt::get(TheContext, APInt(32 ,val));
  }

  static Value *genRealConst(double val) {
    return ConstantFP::get(TheContext, APFloat(val));
  }

  static Value *genCharConst(char val) {
    return ConstantInt::get(TheContext, APInt(8, val));
  }

  static Value *genStringConst(char *val) {
    return ConstantInt::get(TheContext, APInt(32, (int) val));
  }

  static Value *genOp(_A_op_ op) {
    Value *L = genExpression(op.left);
    Value *R = genExpression(op.right);
    switch (op.oper) {
      case A_plusOp:
      return Builder.CreateAdd(L, R);
      case A_minusOp:
      return Builder.CreateSub(L, R);
      case A_timesOp:
      return Builder.CreateMul(L, R);
      case A_divideOp:
      return Builder.CreateDiv(L, R);
      case A_eqOp:
      return Builder.CreateICmpEQ(L, R);
      case A_neqOp:
      return Builder.CreateICmpNE(L, R);
      case A_ltOp:
      return Builder.CreateICmpULT(L, R);
      case A_leOp:
      return Builder.CreateICmpULE(L, R);
      case A_gtOp:
      return Builder.CreateICmpGT(L, R);
      case A_geOp:
      return Builder.CreateICmpGE(L, R);
      default:
      return nullptr;
    }
  }

  static Value *genFOp(_A_op_ op) {
    Value *L = genExpression(op.left);
    Value *R = genExpression(op.right);
    switch (op.oper) {
      case A_plusOp:
      return Builder.CreateFAdd(L, R);
      case A_minusOp:
      return Builder.CreateFSub(L, R);
      case A_timesOp:
      return Builder.CreateFMul(L, R);
      case A_divideOp:
      return Builder.CreateFDiv(L, R);
      case A_eqOp:
      return Builder.CreateFCmpEQ(L, R);
      case A_neqOp:
      return Builder.CreateFCmpNE(L, R);
      case A_ltOp:
      return Builder.CreateFCmpULT(L, R);
      case A_leOp:
      return Builder.CreateFCmpULE(L, R);
      case A_gtOp:
      return Builder.CreateFCmpGT(L, R);
      case A_geOp:
      return Builder.CreateFCmpGE(L, R);
      default:
      return nullptr;
    }
  }

  static Value *genSimpleVar(S_symbol name) {
    Value *var = NamedValues[name];

    return Builder.CreateLoad(var, S_name(name));
  }

  static Value *genSubscript(_A_subscript_ subscript) {

  }

  static Value *genFieldVar(_A_field_ field) {
    std::string recordName(S_name(field.var));
    std::string fieldName(S_name(field.sym));

    return NamedValues[S_Symbol((recordName + "_" + fieldName).data())];
  }

  static Value *genConstDec(S_symbol name, Value *value) {
    NamedValues[name] = value;
    return value;
  }

  static Value *genProc(A_proc proc) {
    S_symbol procName;
    if (proc->kind == A_sysProc) {
      procName = proc->u.proc;
    } else {
            //A_func
      procName = proc->u.func;
    }

    Function *callee = TheModule->getFunction(S_name(procName));

    std::vector<Value *> args;
    while (proc->args != nullptr) {
      args.push_back(genExpression(proc->args->head));
      proc->args = proc->args->tail;
    }

    return Builder.CreateCall(callee, args);
  }

  static Value *genAssignStatement(_A_assign_ assign) {
    Value *var = NamedValues[assign.var];
    Value *exp = genExpression(assign.exp);

    return Builder.CreateStore(exp, var);
  }

  static Value *genIf(_A_if_exp_ iff) {
    Value *condition = genExpression(iff.test);
    condition = Builder.CreateICmpNE(condition, ConstantInt::get(TheContext, APInt(32, 0)));

    Function *theFunction = Builder.GetInsertBlock()->getParent();

    BasicBlock *thenBlock = BasicBlock::Create(TheContext, "then", theFunction);
    BasicBlock *elseBlock = BasicBlock::Create(TheContext, "else");
    BasicBlock *mergeBlock = BasicBlock::Create(TheContext, "ifcont");

    Builder.CreateCondBr(condition, thenBlock, elseBlock);

    Builder.SetInsertPoint(thenBlock);

    Value *thenValue = genExpression(iff.then);
    if(!thenValue) return nullptr;

    Builder.CreateBr(mergeBlock);
    thenBlock = Builder.GetInsertBlock();

    theFunction->getBasicBlockList().push_back(elseBlock);
    Builder.SetInsertPoint(elseBlock);

    Value *elseValue = genExpression(iff.elsee);
    if(!elseValue) return nullptr;

    Builder.CreateBr(mergeBlock);
    thenBlock = Builder.GetInsertBlock();

    theFunction->getBasicBlockList().push_back(mergeBlock);
    Builder.SetInsertPoint(mergeBlock);

    PHINode *PN = Builder.CreatePHI(Type::getDoubleTy(TheContext), 2, "iftmp"); //TODO
    PN->addIncoming(thenValue, thenBlock);
    PN->addIncoming(elseValue, elseBlock);
    return PN;
  }

  static Value *genIfStatement(_A_if_stm_ iff) {
    Value *condition = genExpression(iff.test);
    condition = Builder.CreateICmpNE(condition, ConstantInt::get(TheContext, APInt(32, 0)));

    Function *theFunction = Builder.GetInsertBlock()->getParent();

    BasicBlock *thenBlock = BasicBlock::Create(TheContext, "then", theFunction);
    BasicBlock *elseBlock = BasicBlock::Create(TheContext, "else");
    BasicBlock *mergeBlock = BasicBlock::Create(TheContext, "ifcont");

    Builder.CreateCondBr(condition, thenBlock, elseBlock);

    Builder.SetInsertPoint(thenBlock);

    Value *thenValue = genStatement(iff.then);
    if(!thenValue) return nullptr;

    Builder.CreateBr(mergeBlock);
    thenBlock = Builder.GetInsertBlock();

    theFunction->getBasicBlockList().push_back(elseBlock);
    Builder.SetInsertPoint(elseBlock);

    Value *elseValue = genStatement(iff.elsee);
    if(!elseValue) return nullptr;

    Builder.CreateBr(mergeBlock);
    thenBlock = Builder.GetInsertBlock();

    theFunction->getBasicBlockList().push_back(mergeBlock);
    Builder.SetInsertPoint(mergeBlock);

    PHINode *PN = Builder.CreatePHI(Type::getDoubleTy(TheContext), 2, "iftmp"); //TODO
    PN->addIncoming(thenValue, thenBlock);
    PN->addIncoming(elseValue, elseBlock);
    return PN;
  }

  static Value *genForStatement(_A_for_ forr) {
    Function *TheFunction = Builder.GetInsertBlock()->getParent();

        // Create an alloca for the variable in the entry block.
    AllocaInst *Alloca = CreateEntryBlockAlloca(TheFunction, S_name(forr.var));

        // Emit the start code first, without 'variable' in scope.
    Value *StartVal = genExpression(forr.init);
    if (!StartVal)
      return nullptr;

        // Store the value into the alloca.
    Builder.CreateStore(StartVal, Alloca);

        // Make the new basic block for the loop header, inserting after current
        // block.
    BasicBlock *LoopBB = BasicBlock::Create(TheContext, "loop", TheFunction);

        // Insert an explicit fall through from the current block to the LoopBB.
    Builder.CreateBr(LoopBB);

        // Start insertion in LoopBB.
    Builder.SetInsertPoint(LoopBB);

        // Within the loop, the variable is defined equal to the PHI node.  If it
        // shadows an existing variable, we have to restore it, so save it now.
    AllocaInst *OldVal = NamedValues[forr.var];
    NamedValues[forr.var] = Alloca;

        // Emit the body of the loop.  This, like any other expr, can change the
        // current BB.  Note that we ignore the value computed by the body, but don't
        // allow an error.
    if (!genStatement(forr.fordo))
      return nullptr;

    Value *StepVal = ConstantInt::get(TheContext, APInt(32, 1));

        // Compute the end condition.
    Value *EndVal = genExpression(forr.change);
    if (!EndVal)
      return nullptr;

        // Reload, increment, and restore the alloca.  This handles the case where
        // the body of the loop mutates the variable.
    Value *CurVar = Builder.CreateLoad(Alloca, S_name(forr.var));
    Value *NextVar = Builder.CreateFAdd(CurVar, StepVal, "nextvar");
    Builder.CreateStore(NextVar, Alloca);

    Value *EndCond = Builder.CreateFCmpONE(
      EndVal, CurVar, "loopcond");

        // Create the "after loop" block and insert it.
    BasicBlock *AfterBB =
    BasicBlock::Create(TheContext, "afterloop", TheFunction);

        // Insert the conditional branch into the end of LoopEndBB.
    Builder.CreateCondBr(EndCond, LoopBB, AfterBB);

        // Any new code will be inserted in AfterBB.
    Builder.SetInsertPoint(AfterBB);

        // Restore the unshadowed variable.
    if (OldVal)
      NamedValues[forr.var] = OldVal;
    else
      NamedValues.erase(forr.var);

        // for expr always returns 0.0.
    return Constant::getNullValue(Type::getDoubleTy(TheContext));
  }

  Value *genVarDec(A_field var) {
    std::vector<AllocaInst *> OldBindings;

    Function *TheFunction = Builder.GetInsertBlock()->getParent();

        // Register all variables and emit their initializer.
    for (auto i = var->head; i != nullptr; i = i->tail) {
      S_symbol VarName = i->head->name;

            //TODO only support simple type now
      AllocaInst *Alloca = CreateEntryBlockAlloca(TheFunction, S_name(VarName));
      NamedValues[VarName] = Alloca;
    }
    return nullptr;
  }

  Value *genRoutineDec(_A_routine_ routinee) {
    std::vector<Type *> argTypes;
    for(auto i = routinee.params; i != nullptr; i = i->tail) {
      for(auto j = i->head->head; j != nullptr; j = j->tail) {
        argTypes.push_back(genType(i->head->ty));
      }
    }
    FunctionType *FT =
    FunctionType::get(Type::getDoubleTy(TheContext), argTypes, false);

    Function *F =
    Function::Create(FT, Function::ExternalLinkage, S_name(routinee.name), TheModule.get());

        // Set names for all arguments.
    auto arg = F->arg_begin();
    for(auto i = routinee.params; i != nullptr; i = i->tail) {
      for(auto j = i->head->head; j != nullptr; j = j->tail) {
        arg->setName(S_name(j->head->name));
      }
    }

    return F;
  }

  static Type *genSingleType(S_symbol type) {

  }

  static Type *genSimpleType(A_simpleTy simple) {
    switch(type.u.simple->kind) {
      case A_sysTy:
      return genSingleType(simple.u.simple);
      case A_singleTy:
      return genSingleType(simple.u.single);
      case A_doubleCTy:
      case A_doubleNTy:
      return Type::getDoubleTy(TheContext);
      case A_listTy:
      return Type::getInt32Ty(TheContext);
    }
  }

  static Type *genType(A_ty type) {
    switch(type.kind) {
      case A_simTy:
      return genSimpleType(type.u.simple);
      case A_recordTy:
      case A_arraryTy:
      return Type::getInt32PtrTy(TheContext);
    }
  }

  static Value *genExpression(A_exp exp) {
        //TODO
  }
private:
  Function *getFunction(std::string Name) {
        // First, see if the function has already been added to the current module.
    if (auto *F = TheModule->getFunction(Name))
      return F;

        // If not, check whether we can codegen the declaration from some existing
        // prototype.
    auto FI = FunctionProtos.find(Name);
    if (FI != FunctionProtos.end())
      return FI->second->codegen();

        // If no existing prototype exists, return null.
    return nullptr;
  }

  static LLVMContext TheContext;
  static Module *TheModule;
  static IRBuilder<> Builder;
  static std::map<S_symbol, Value *> NamedValues;
  static std::map<std::string, std::unique_ptr<PrototypeAST>> FunctionProtos;
}

IRBuilder<> IR::Builder (TheContext);