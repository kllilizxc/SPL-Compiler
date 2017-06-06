//
//  util.h
//  SPL-compiler
//
//  Created by cai on 2017/6/3.
//  Copyright © 2017年 cai. All rights reserved.
//

#ifndef util_h
#define util_h
#include <assert.h>

typedef char *string;
typedef char Bool;

#define TRUE 1
#define FALSE 0

void *checked_malloc(int);
string String(char *);

typedef struct U_boolList_ *U_boolList;
struct U_boolList_ {Bool head; U_boolList tail;};
U_boolList U_BoolList(Bool head, U_boolList tail);
#endif
