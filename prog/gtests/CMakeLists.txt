cmake_minimum_required(VERSION 3.5)

project(lab_01_AA)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")

add_subdirectory(lib/googletest)
include_directories(lib/googletest/googletest/include)
include_directories(lib/googletest/googlemock/include)

set(SOURCE_FILES main.cpp tests/sortTests.cpp)
add_executable(gtestset ${SOURCE_FILES} tests/sortTests.cpp)

target_link_libraries(gtestset gtest gtest_main src)