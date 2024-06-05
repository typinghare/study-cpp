cmake_minimum_required(VERSION 3.28)
project(study_cpp)

set(CMAKE_CXX_STANDARD 20)

add_executable(bfs
        graph/graph.hpp
        graph/bfs.cpp
        vm/kernel/Memory.cpp
        vm/kernel/Memory.hpp
        vm/tr/TuringComplete.hpp
)

add_executable(converge math/converge.cpp)

# vm
add_executable(vm
        vm/main.cpp
        vm/kernel/Memory.hpp
        vm/kernel/Memory.cpp
        vm/kernel/Register.cpp
        vm/kernel/Register.hpp
        vm/kernel/Virtual.hpp
        vm/kernel/Virtual.hpp
        vm/kernel/Word.cpp
        vm/kernel/Word.hpp
        vm/kernel/RegisterFile.cpp
        vm/kernel/RegisterFile.hpp
        vm/kernel/MicroInstruction.hpp
        vm/kernel/Cpu.cpp
        vm/kernel/Cpu.hpp
        vm/kernel/MacroInstruction.hpp
        vm/kernel/Instruction.hpp
)

# copy
add_executable(copy-problem copy/copy_problem.cpp)