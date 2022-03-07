cmake_minimum_required(VERSION 3.21)
project(containers)

set(CMAKE_CXX_STANDARD 14)

include_directories(Vector/head)

add_executable(containers
    Vector/head/Vector.hpp
    Vector/src/Vector.cpp
    Vector/main.cpp)
