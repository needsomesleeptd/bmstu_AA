cmake_minimum_required(VERSION 3.27)
project(lab_01_AA)

set(CMAKE_CXX_STANDARD 14)

set(HEADERS sort.hpp timings.h)
set(SOURCES sort.cpp timings.cpp)


ADD_LIBRARY(src ${HEADERS} ${SOURCES})
add_compile_options(-O0)
add_executable(lab_01_src ${HEADERS} ${SOURCES} main.cpp)