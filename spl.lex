%{
#include <string.h>
#include "util.h"
#include "symbol.h"
#include "absyn.h"
#include "errormsg.h"
#include "y.tab.h"

int charPos=1;
int startComment = 0;
int yywrap(void)
{
 charPos=1;
 return 1;
}

void adjust(void)
{
 EM_tokPos = charPos;
 charPos += yyleng;
}
/*
* Please don't modify the lines above.
* You can add C declarations of your own below.
*/

%}
  /* You can add lex definitions here. */
digits [0-9]+ 
reserverSYSCON false|maxint|true
reserverSYSFUNCT abs|chr|odd|ord|pred|sqr|sqrt|succ
reserverSYSPROC write|writeln|read
reserverSYSTYPE boolean|char|integer|real|string
%Start INITINAL COMMENT
%%
  /* 
  * Below are some examples, which you can wipe out
  * and write reguler expressions and actions of your own.
  */  
<INITINAL>"/*" {adjust();BEGIN COMMENT;}  // comment
<COMMENT>"*/" {adjust();BEGIN INITINAL;}  // comment
<COMMENT>.    {adjust();}
<COMMENT>"\n"    {adjust();}
<INITINAL>for  { adjust(); return FOR;}     /* key word*/
<INITINAL>while  { adjust(); return WHILE;}
<INITINAL>to  { adjust(); return TO;}
<INITINAL>break  { adjust(); return BREAK;}
<INITINAL>let  { adjust(); return LET;}
<INITINAL>in  { adjust(); return IN;}
<INITINAL>end  { adjust(); return END;}
<INITINAL>function  { adjust(); return FUNCTION;}
<INITINAL>var  { adjust(); return VAR;}
<INITINAL>type  { adjust(); return TYPE;}
<INITINAL>array  { adjust(); return ARRAY;}
<INITINAL>if  { adjust(); return IF;}
<INITINAL>then  { adjust(); return THEN;}
<INITINAL>else  { adjust(); return ELSE;}
<INITINAL>do  { adjust(); return DO;}
<INITINAL>of  { adjust(); return OF;}
<INITINAL>and  { adjust(); return AND;}
<INITINAL>begin { adjust(); return BEGINN;}
<INITINAL>case { adjust(); return CASE;}
<INITINAL>const { adjust(); return CONST;}
<INITINAL>downto { adjust(); return DOWNTO;}
<INITINAL>goto { adjust(); return GOTO;}
<INITINAL>mod { adjust(); return MOD;}
<INITINAL>not { adjust(); return NOT;}
<INITINAL>or { adjust(); return OR;}
<INITINAL>packed { adjust(); return PACKED;}
<INITINAL>procedure { adjust(); return PROCEDURE;}
<INITINAL>program { adjust(); return PROGRAM;}
<INITINAL>record { adjust(); return RECORD;}
<INITINAL>repeat { adjust(); return REPEAT;}
<INITINAL>set { adjust(); return SET;}
<INITINAL>until { adjust(); return UNTIL;}
<INITINAL>with { adjust(); return WITH;}
<INITINAL>","	 {adjust(); return COMMA;}    //symbol
<INITINAL>":"  {adjust(); return COLON;}
<INITINAL>";"  {adjust(); return SEMI;}
<INITINAL>"("  {adjust(); return LP;}
<INITINAL>")"  {adjust(); return RP;}
<INITINAL>"["  {adjust(); return LB;}
<INITINAL>"]"  {adjust(); return RB;}
<INITINAL>"."  {adjust(); return DOT;}
<INITINAL>".."  {adjust(); return DOTDOT;}
<INITINAL>"+"  {adjust(); return PLUS;}
<INITINAL>"-"  {adjust(); return MINUS;}
<INITINAL>"*"  {adjust(); return MUL;}
<INITINAL>"/"  {adjust(); return DIV;}
<INITINAL>"="  {adjust(); return EQUAL;}
<INITINAL>"<>"  {adjust(); return UNEQUAL;}
<INITINAL>"<"  {adjust(); return LT;}
<INITINAL>"<="  {adjust(); return LE;}
<INITINAL>">"  {adjust(); return GT;}
<INITINAL>">="  {adjust(); return GE;}
<INITINAL>":="  {adjust(); return ASSIGN;}
<INITINAL>{reserverSYSCON} {
  adjust(); 
  int size = strlen(yytext);
  yylval.sval = checked_malloc(sizeof(char)*size);
  strcpy(yylval.sval, yytext);
  return SYS_CON;
}
<INITINAL>{reserverSYSFUNCT} {
  adjust(); 
  int size = strlen(yytext);
  yylval.sval = checked_malloc(sizeof(char)*size);
  strcpy(yylval.sval, yytext);
  return SYS_FUNCT;
}
<INITINAL>{reserverSYSPROC} {
  adjust(); 
  int size = strlen(yytext);
  yylval.sval = checked_malloc(sizeof(char)*size);
  strcpy(yylval.sval, yytext);
  //printf("string:strlen:%s\n", yylval.sval);
  return SYS_PROC;
}

<INITINAL>{reserverSYSTYPE} {
  adjust();
  int size = strlen(yytext);
  yylval.sval = checked_malloc(sizeof(char)*size);
  strcpy(yylval.sval, yytext);
  //printf("string:strlen:%s\n", yylval.sval);
  return SYS_TYPE;
}

<INITINAL>[a-zA-Z]["_"|a-zA-Z0-9]* {// identifier
  adjust(); 
  int size = strlen(yytext);
  yylval.sval = checked_malloc(sizeof(char)*size);
  strcpy(yylval.sval, yytext);
  //printf("string:strlen:%s\n", yylval.sval);
  return ID;
} 



<INITINAL>"\""([a-zA-Z0-9]|"/"|" "|"\\n"|"."|"_"|"-"|"\\t")*"\"" {// string
  adjust(); 
  int size = strlen(yytext), i, p = 0;
  if(size == 2) {
    yylval.sval = "(null)";
    return STRING;
  }
  yylval.sval = checked_malloc(sizeof(char)*size);
  for(i = 1; i < size - 1; ++i) {
    if(yytext[i] == '\\') {
      if(yytext[i+1] == 'n') {
        yylval.sval[p] = '\n';  
      } else if(yytext[i+1] == 't') {
        yylval.sval[p] = '\t';  
      } else if(yytext[i+1] == '0') { 
        yylval.sval[p] = '\0';  
      }
      i++;
    } else {
      yylval.sval[p] = yytext[i];  
    }
    p++;
  }
  //printf("string:strlen:%s\n", yylval.sval);
  return STRING;
}  

<INITINAL>"\'"([a-zA-Z0-9]|"/"|" "|"\\n"|"."|"_"|"-"|"\\t")"\'" {// char
  adjust();
  int size = strlen(yytext);
  if(size > 2) {
  yylval.cval = yytext[1];
  return CHAR;
  }
}       
<INITINAL>{digits} {adjust(); yylval.ival=atoi(yytext); return INTEGER;}
<INITINAL>[0-9]*\.?[0-9]+ {adjust(); yylval.fval=atof(yytext); return REAL;}

<INITINAL>(" "|"\t")+  {adjust(); continue;} 
<INITINAL>"\n"  {adjust(); EM_newline(); continue;}
<INITINAL>.	 {adjust(); EM_error(EM_tokPos,"illegal token");}
.           {yyless(0);BEGIN INITINAL;}




