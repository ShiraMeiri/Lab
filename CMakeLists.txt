cmake_minimum_required(VERSION 3.28)
project(lab)

set(CMAKE_CXX_STANDARD 11)

add_executable(lab main.cpp
        uf.cpp
        segment.cpp
        fenwick.cpp
        Leetcode.cpp
        LeetcodeStorage.cpp
        LeetcodeStorage.h
)
