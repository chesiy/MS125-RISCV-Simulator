//
// Created by admin on 2019/7/4.
//

#ifndef RISCV5_MEMORYACCESS_HPP
#define RISCV5_MEMORYACCESS_HPP

//#include "register.hpp"
//#include "instruction.hpp"
#include "utility.hpp"
#include "WriteBack.hpp"
#include <iostream>

class MA{
private:
    regist *reg;
public:
    inst instruction;
    MA(regist *r):reg(r){}

    void perform(){
        switch(instruction.type){
            case LB:
                instruction.res=signedExtend(reg->load(instruction.src1,1),7);
                break;
            case LH:
                instruction.res=signedExtend(reg->load(instruction.src1,2),15);
                break;
            case LW:
                instruction.res=reg->load(instruction.src1,4);
                break;
            case LBU:
                instruction.res=reg->load(instruction.src1,1);
                break;
            case LHU:
                instruction.res=reg->load(instruction.src1,2);
                break;
            case SB:
                reg->store(instruction.src1,instruction.src2,1);
                break;
            case SH:
                reg->store(instruction.src1,instruction.src2,2);
                break;
            case SW:
                reg->store(instruction.src1,instruction.src2,4);
                break;
            default:
                break;
        }
    }
    void go_on(WB &next){
        next.instruction=instruction;
    }
};

#endif //RISCV5_MEMORYACCESS_HPP
