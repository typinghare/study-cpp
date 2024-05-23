cmake_minimum_required(VERSION 3.28)
project(study_cpp)

set(CMAKE_CXX_STANDARD 20)

add_executable(bfs
        graph/graph.hpp
        graph/bfs.cpp
)
