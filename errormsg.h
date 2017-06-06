//
//  errormsg.h
//  SPL-compiler
//
//  Created by cai on 2017/6/3.
//  Copyright © 2017年 cai. All rights reserved.
//

#ifndef errormsg_h
#define errormsg_h

extern bool EM_anyErrors;

void EM_newline(void);

extern int EM_tokPos;

void EM_error(int, const char *, ...);
void EM_impossible(string,...);
void EM_reset(string filename);


#endif /* errormsg_h */
