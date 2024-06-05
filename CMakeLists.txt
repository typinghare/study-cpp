cmake_minimum_required(VERSION 3.28)
project(study_cpp)

set(CMAKE_CXX_STANDARD 20)

add_executable(bfs
        graph/graph.hpp
        graph/bfs.cpp
        vm/kernel/Microprogram.cpp
        vm/kernel/Microprogram.hpp
)

add_executable(converge math/converge.cpp)

# vm
add_executable(vm
        vm/main.cpp
        vm/kernel/Virtual.hpp
        vm/kernel/Word.hpp
        vm/kernel/Register.hpp
        vm/kernel/Instruction.hpp
        vm/kernel/RegisterFile.hpp
        vm/kernel/Memory.hpp
        vm/kernel/Cpu.hpp
        vm/mt/MinimalTuringComplete.hpp
)

# copy
add_executable(copy-problem copy/copy_problem.cpp)