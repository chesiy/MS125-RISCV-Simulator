//
// Created by admin on 2019/7/4.
//

#ifndef RISCV5_WRITEBACK_HPP
#define RISCV5_WRITEBACK_HPP

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
        if(instruction.type==LOCK)return;
        switch (instruction.type){
            case LUI:
                reg->changereg(instruction.rd,instruction.res);
                break;
            case AUIPC:
                reg->changereg(instruction.rd,instruction.res);
                break;
            case JAL: {
                unsigned int resultpc = instruction.src1 + instruction.imm;
                reg->changereg(instruction.rd, instruction.src1 + 4);//把下一条指令的地址设为pc+4
                reg->changepc(resultpc);
                break;
            }
            case JALR: {
                reg->changereg(instruction.rd, instruction.src2);
                unsigned int resultpc = instruction.src1 + instruction.imm;
                resultpc = setzero(resultpc);//最低位置零
                reg->changepc(resultpc);
                break;
            }
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
            default:break;
        }
        removelock();
    }
    void removelock(){
        switch (instruction.type){
            case JAL:
            case JALR:
            case BEQ:
            case BNE:
            case BLT:
            case BGE:
            case BLTU:
            case BGEU:
                reg->unpc--;
                break;
            default:
                break;
        }
    }
};

#endif //RISCV5_WRITEBACK_HPP
