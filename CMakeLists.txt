project(interview_preparation)
cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -Wall")


add_executable(sort basic/origin_array_sort.cpp basic/origin_array_sort.h)
add_executable(list leetcode/list.cpp leetcode/test_constants.h)
add_executable(search basic/search.cpp)