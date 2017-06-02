//
// Created by 54179 on 2017/6/2.
//

#ifndef SPL_COMPILER_UTIL_H
#define SPL_COMPILER_UTIL_H
#include <assert.h>

typedef char *string;
typedef char bool;

#define TRUE 1
#define FALSE 0

void *checked_malloc(int);
string String(char *);

typedef struct U_boolList_ *U_boolList;
struct U_boolList_ {bool head; U_boolList tail;};
U_boolList U_BoolList(bool head, U_boolList tail);
#endif //SPL_COMPILER_UTIL_H
