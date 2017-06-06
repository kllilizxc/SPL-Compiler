#ifndef SPL_COMPILER_MIPSFRAME_HPP
#define SPL_COMPILER_MIPSFRAME_HPP

#include "frame.hpp"

class InFrameAccess : public FrameAccess {
public:
    InFrameAccess(int offset = 0) : FrameAccess(FrameAccess::InFrame), offset(offset) {};
private:
    int offset;
};

class InRegAccess : public FrameAccess {
public:
    InRegAccess() : FrameAccess(FrameAccess::InReg) {};
private:
    //Temp_temp reg TODO
};

class MIPSFrame : public Frame {
public:
    MIPSFrame(std::list<bool> formalsAreEscape) : stackPointer(wordSize) {
        for (auto iter = formalsAreEscape.begin(); iter != formalsAreEscape.end(); iter++) {
            if(*iter) {
                accessList.push_back(InFrameAccess(stackPointer));
            } else {
                accessList.push_back(InRegAccess(/*TODO*/));
            }
            stackPointer += wordSize;
        }
    };

    FrameAccess& allocLocals(bool escape) {
        FrameAccess access;
        if(escape) {
            access = InFrameAccess(stackPointer);
            stackPointer += wordSize;
        } else {
            access = InRegAccess(/*TODO*/);
        }
        accessList.push_back(access);
        return access;
    }

    const std::list<FrameAccess> &getAccessCist() const {
        return accessList;
    }

private:
    static const int wordSize = 4;
    int stackPointer;
    std::list<FrameAccess> accessList;
    //Temp_Label label; TODO
};

#endif