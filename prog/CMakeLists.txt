cmake_minimum_required(VERSION 3.27)
project(comp_analysis)

set(CMAKE_CXX_STANDARD 14)

add_executable(comp_analysis main.cpp table.hpp table.cpp)
