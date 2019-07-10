cmake_minimum_required(VERSION 3.5)
project(Riscv5)

set(CMAKE_CXX_STANDARD 14)

add_executable(Riscv5 main.cpp utility.hpp memory.hpp
        instruction.hpp InstructionFetch.hpp InstructionDecode.hpp
        excution.hpp MemoryAccess.hpp WriteBack.hpp forwarding.hpp)