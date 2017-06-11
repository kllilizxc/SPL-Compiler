class IR {
public:
  static Value *genIntConst(int value) {

  }
  static Value *genRealConst(double val) {
    return ConstantFP::get(getGlobalContext(), APFloat(val));
  }
  static Value *genCharConst(char val) {}
  static Value *genStringConst(char *val) {}
  static Value *genIf(_A_if_exp_ iff) {}
  static Value *genOp(_A_op_ op) {
    Value *left = genExpression(op.left);
    Value *right = genExpression(op.right);
    switch (op.oper) {
      case A_plusOp:
        return Builder::CreateFAdd(L, R, "addtmp"); //TODO
      case A_minusOp:
        return Builder::CreateFSub(L, R, "subtmp");
      case A_timesOp:
        return Builder::CreateFMul(L, R, "multmp");
      case A_divideOp:
      case A_eqOp:
      case A_neqOp:
      case A_ltOp:
        return Builder::CreateFCmpULT(L, R, "lttmp");
      case A_leOp:
      case A_gtOp:
      case A_geOp: {
      }
    }
  }
  static Value *genSimpleVar(S_symbol name) {
    return NamedValues[name];
  }
  static Value *genSubscript(_A_subscript_ subscript) {}
  static Value *genFieldVar(_A_field_ field) {
    std::string recordName(field.var->name);
    std::string fieldName(field.sym->name);

    return NamedValues[S_Symbol((recordName + "_" + fieldName).data())];
  }
  static Value *genConstDec(_A_const_ constt) {
    NamedValues[constt.name] = 
  }

private:
  static Module *TheModule;
  static IRBuilder Builder;
  static std::map<S_symbol, Value *> NamedValues;
}

IRBuilder IR::Builder(getGlobalContext());