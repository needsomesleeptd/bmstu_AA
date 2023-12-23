cmake_minimum_required(VERSION 3.27)
project(lab_01_AA)

set(CMAKE_CXX_STANDARD 14)

set(HEADERS conveyor.hpp timings.h sorts.h atomic_queue.h)
set(SOURCES conveyor.cpp timings.cpp sorts.cpp)


ADD_LIBRARY(src ${HEADERS} ${SOURCES})
add_compile_options(-O0)
add_executable(lab_01_src ${HEADERS} ${SOURCES} main.cpp)