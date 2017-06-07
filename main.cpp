#include <stdio.h>
#include "env.hpp"
#include "semant.hpp"
#include <string>
#include <cstring>

extern "C" {
#include "util.h"
#include "absyn.h"
#include "errormsg.h"
#include "prabsyn.h"
#include "y.tab.h"
}

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
    int i;
    FILE *out;
    std::string fnamepart[31]=
    {
        "sample1",
        "sample2",
        "sample3",
        "test1",
        "test1_error1",
        "test1_error2",
        "test2",
        "test2_error1",
        "test2_error2",
        "test2_error3",
        "test2_error4",
        "test3",
        "test3_error1",
        "test3_error2",
        "test3_error3",
        "test3_error4",
        "test4",
        "test4_error1",
        "test4_error2",
        "test5",
        "test5_error1",
        "test6",
        "test7",
        "test8",
        "test8_error1",
        "test8_error2",
        "test9",
        "test9_error1",
        "test10",
        "test10_error1",
        "test10_error2"
    };
    
    for(i = 0; i < 31; ++i)
    {
        char fname[30] = "../testcase/", fout[30] = "../refs/";
        strcat(fname, fnamepart[i].data());
        strcat(fname, ".spl");
        parse(fname);
        
        strcat(fout, fnamepart[i].data());
        strcat(fout, ".out");
        out = fopen(fout, "w");
        pr_pro(out,absyn_root,0);
        fprintf(out,"\n");
        fclose(out);
        //semant
        S_table vEnv = EnvironmentEntry::enterBaseValueEnvironment();
        S_table tEnv = EnvironmentEntry::enterBaseTypeEnvironment();
        printf("analysing %s\n", fname);
        Semant::translateProgram(vEnv, tEnv, absyn_root);

        absyn_root = NULL;
    }
    
    return 0;
}
