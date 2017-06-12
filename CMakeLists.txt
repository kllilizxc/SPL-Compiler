cmake_minimum_required(VERSION 3.2)
project(SPL_Compiler)

#find_package(LLVM REQUIRED CONFIG)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

# Set your project compile flags.
# E.g. if using the C++ header files
# you will need to enable C++11 support
# for your compiler.

#include_directories(${LLVM_INCLUDE_DIRS})
#add_definitions(${LLVM_DEFINITIONS})`

# Now build our tools
set(CMAKE_CXX_STANDARD 14)

include_directories(C:/Users/54179/Downloads/llvm/llvm/include)

set(SOURCE_FILES main.cpp y.tab.h y.tab.c table.h table.c util.h util.c symbol.h symbol.c absyn.h absyn.c errormsg.h errormsg.c
        prabsyn.h prabsyn.c lex.yy.c types.hpp env.hpp semant.hpp frame.hpp mipsframe.hpp temp.hpp ir.hpp)
add_executable(SPL_Compiler ${SOURCE_FILES})

# Find the libraries that correspond to the LLVM components
# that we wish to use
#llvm_map_components_to_libnames(llvm_libs support core irreader)

# Link against LLVM libraries
#target_link_libraries(simple-tool ${llvm_libs})

