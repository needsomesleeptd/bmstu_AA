cmake_minimum_required(VERSION 3.27)
project(lab_01_AA)

set(CMAKE_CXX_STANDARD 14)

set(HEADERS  table.hpp )
set(SOURCES   table.cpp )


ADD_LIBRARY(src ${HEADERS} ${SOURCES})
add_compile_options(-O0)
add_executable(lab_01_src ${HEADERS} ${SOURCES} main.cpp table.cpp table.hpp)