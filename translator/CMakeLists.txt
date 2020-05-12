cmake_minimum_required(VERSION 3.15)
project(translator)

set(CMAKE_CXX_STANDARD 14)

include_directories(inc)
add_executable(Compiler main.cpp inc/Compiler.h inc/Generate_elf.h)