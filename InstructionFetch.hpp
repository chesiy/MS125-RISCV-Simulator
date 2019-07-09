//
// Created by admin on 2019/7/4.
//

#ifndef RISCV5_INSTRUCTIONFETCH_HPP
#define RISCV5_INSTRUCTIONFETCH_HPP

#include <iostream>
#include "instruction.hpp"
///根据pc寄存器指向的位置获取指令
using namespace std;

class IF{
private:
    regist *reg;//其实只用了pc寄存器
public:
    bool cantdo;

    inst instruction;
    IF(regist *r):reg(r),cantdo(0){}

    void perform(){
        if(reg->unpc)cantdo=true;
        else{
            cantdo=false;
            instruction.initial();
            instruction.instr=reg->getinst();
        }
    }
    void go_on(ID &next){
        next.instruction=instruction;
        if(cantdo){next.instruction.type=LOCK;}//这里要怎么办啊。。。。。。
    }
};

#endif //RISCV5_INSTRUCTIONFETCH_HPP
