cmake_minimum_required(VERSION 3.7)
project(SPL_Compiler)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp types.hpp env.hpp semant.hpp table.h table.c util.h util.c symbol.h symbol.c absyn.h absyn.c errormsg.h errormsg.c
        prabsyn.h prabsyn.c frame.hpp mipsframe.hpp temp.hpp)
add_executable(SPL_Compiler ${SOURCE_FILES})