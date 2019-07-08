cmake_minimum_required(VERSION 3.5)
project(Riscv5)

set(CMAKE_CXX_STANDARD 14)

add_executable(code main.cpp utility.hpp register.hpp memory.hpp
        instruction.hpp InstructionFetch.hpp InstructionDecode.hpp
        excution.hpp MemoryAccess.hpp WriteBack.hpp)