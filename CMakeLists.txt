project(interview_preparation)
cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -O2 -Wall")

add_executable(sort basic/origin_array_sort.cpp)