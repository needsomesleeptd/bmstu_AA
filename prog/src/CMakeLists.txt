cmake_minimum_required(VERSION 3.27)
project(lab_01_AA)

set(CMAKE_CXX_STANDARD 14)

set(HEADERS measure.h sorts.h)
set(SOURCES time.cpp sorts.cpp)


ADD_LIBRARY(src ${HEADERS} ${SOURCES})
add_compile_options(-O0)
add_executable(lab_01_src ${HEADERS} ${SOURCES} main.cpp semaphore.h)