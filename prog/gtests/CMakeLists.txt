cmake_minimum_required(VERSION 3.5)

project(lab_01_AA)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

add_subdirectory(lib/googletest-main)
include_directories(lib/googletest-main/googletest/include)
include_directories(lib/googletest-main/googlemock/include)

set(SOURCE_FILES main.cpp tests/testsForLength.cpp)
add_executable(gtestset ${SOURCE_FILES} tests/testsForLength.cpp)

target_link_libraries(gtestset gtest gtest_main src)