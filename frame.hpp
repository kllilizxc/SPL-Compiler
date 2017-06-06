//
// Created by 54179 on 2017/6/3.
//

#ifndef SPL_COMPILER_FRAME_HPP
#define SPL_COMPILER_FRAME_HPP

#include <list>

class FrameAccess {
public:
    enum Kind {InFrame, InReg} kind;
    FrameAccess() {};
    FrameAccess(FrameAccess::Kind kind) : kind(kind) {};
};

class Frame {
public:
    virtual FrameAccess& allocLocals(bool escape) = 0;
};


#endif //SPL_COMPILER_FRAME_H
