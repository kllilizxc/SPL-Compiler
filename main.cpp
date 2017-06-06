#include <stdio.h>
#include "util.h"
#include "absyn.h"
#include "errormsg.h"
#include "prabsyn.h"
#include "semant.hpp"

extern int yyparse(void);
extern A_pro absyn_root;

/* parse source file fname;
 return abstract syntax data structure */
A_pro parse(string fname)
{EM_reset(fname);
    if (yyparse() == 0) /* parsing worked */
        return absyn_root;
    else return NULL;
}

int main(){
    char fname[20];
    S_table valueTable = VariableEnvironmentEntry::enterBaseValueEnvironment();
    S_table typeTable = FunctionEnvironmentEntry::enterBaseTypeEnvironment();

    scanf("%s", fname);
    parse(fname);
    pr_pro(stderr,absyn_root,0);
    Semant::translateProgram(valueTable, typeTable, absyn_root);
    fprintf(stderr,"\n");
    return 0;
}
