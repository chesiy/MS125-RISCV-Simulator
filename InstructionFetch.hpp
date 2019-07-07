//
// Created by admin on 2019/7/4.
//

#ifndef RISCV5_INSTRUCTIONFETCH_HPP
#define RISCV5_INSTRUCTIONFETCH_HPP

#include <iostream>
#include "register.hpp"
#include "instruction.hpp"
///根据pc寄存器指向的位置获取指令
using namespace std;

class IF{
private:
    regist *reg;//其实只用了pc寄存器
public:
    inst instruction;
    IF(regist *r):reg(r){}

    void perform(){
        instruction.initial();
        instruction.instr=reg->getinst();
    }
    void go_on(ID &next){
        next.instruction=instruction;
    }
};

#endif //RISCV5_INSTRUCTIONFETCH_HPP
