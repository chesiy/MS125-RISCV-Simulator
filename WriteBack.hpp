//
// Created by admin on 2019/7/4.
//

#ifndef RISCV5_WRITEBACK_HPP
#define RISCV5_WRITEBACK_HPP

//#include "register.hpp"
#include "instruction.hpp"
#include "utility.hpp"
#include <iostream>

class WB{
private:
    regist *reg;
public:
    inst instruction;
    WB(regist*r):reg(r){}

    void perform(){
        switch (instruction.type){
            case LUI:
                reg->changereg(instruction.rd,instruction.imm);
                break;
            case AUIPC:
                reg->changereg(instruction.rd,instruction.res);
                break;
            case JAL:
                reg->changereg(instruction.rd,instruction.src1+4);//把下一条指令的地址设为pc+4
                reg->changepc(instruction.res);
                break;
            case JALR:
                reg->changereg(instruction.rd,instruction.src2);
                reg->changepc(instruction.res);
                break;
            case BEQ:case BNE:case BLT:
            case BGE:case BLTU:case BGEU:
                if(instruction.res)reg->changepc(instruction.rd-4+instruction.imm);
                break;
            case LB:case LH:case LW:
            case LBU:case LHU:
                reg->changereg(instruction.rd,instruction.res);
                break;
                //Stype无writeback操作
            case ADDI:
                reg->changereg(instruction.rd,instruction.res);
                break;
            case SLTI:case SLTIU:
                reg->changereg(instruction.rd,instruction.res);
                break;
            case XORI:
            case ORI:case ANDI:
                reg->changereg(instruction.rd,instruction.res);
                break;
            case SLLI:case SRLI:case SRAI:
                reg->changereg(instruction.rd,instruction.res);
                break;
            case ADD:case SUB:case SLL:case SLT:case SLTU:
            case XOR:case SRL:case SRA:case OR:case AND:
                reg->changereg(instruction.rd,instruction.res);
                break;
        }
    }
};

#endif //RISCV5_WRITEBACK_HPP
