cmake_minimum_required(VERSION 3.7)
project(SPL_Compiler)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp)
add_executable(SPL_Compiler ${SOURCE_FILES})