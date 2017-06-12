cmake_minimum_required(VERSION 3.7)
project(SPL_Compiler)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
    absyn.c
    absyn.h
    env.hpp
    errormsg.c
    errormsg.h
    frame.hpp
    ir.hpp
    lex.yy.c
    main.c
    main.cpp
    mipsframe.hpp
    prabsyn.c
    prabsyn.h
    semant.hpp
    symbol.c
    symbol.h
    table.c
    table.h
    temp.hpp
    types.hpp
    util.c
    util.h
    y.tab.c
    y.tab.h)

add_executable(SPL_Compiler ${SOURCE_FILES})