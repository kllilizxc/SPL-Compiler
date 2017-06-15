cmake_minimum_required(VERSION 3.7)
project(SPL_Compiler)

set(CMAKE_CXX_STANDARD 11)

find_package(LLVM REQUIRED CONFIG)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

# Set your project compile flags.
# E.g. if using the C++ header files
# you will need to enable C++11 support
# for your compiler.

include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

set(SOURCE_FILES
        absyn.c
        absyn.h
        env.hpp
        errormsg.c
        errormsg.h
        ir.hpp
        lex.yy.c
        main.cpp
        prabsyn.c
        prabsyn.h
        semant.hpp
        symbol.c
        symbol.h
        table.c
        table.h
        types.hpp
        util.c
        util.h
        y.tab.c
        y.tab.h)

add_executable(SPL_Compiler ${SOURCE_FILES})

# Find the libraries that correspond to the LLVM components
# that we wish to use
llvm_map_components_to_libnames(llvm_libs support core irreader executionengine mcjit
        x86 x86asmparser x86asmprinter x86codegen x86desc x86disassembler x86info x86utils)

# Link against LLVM libraries
target_link_libraries(SPL_Compiler ${llvm_libs})