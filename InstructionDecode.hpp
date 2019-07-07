//
// Created by admin on 2019/7/4.
//

#ifndef RISCV5_INSTRUCTIONDECODE_HPP
#define RISCV5_INSTRUCTIONDECODE_HPP

#include <iostream>
#include "register.hpp"
#include "instruction.hpp"

///根据IF里读到的指令类型，从作为右值的寄存器里读值（rs），
/// 解析立即数的值，然后赋给（src）；
class ID{
private:
    regist *reg;
public:
    inst instruction;
    ID(regist *r):reg(r){}
    void setsrc(){
        switch (instruction.type){
            case AUIPC:
                instruction.src1=reg->getpc()-4;
                break;
            case JAL:
                instruction.src1=reg->getpc()-4;
                break;
            case JALR:
                instruction.src1=reg->getreg(instruction.rs1);
                instruction.src2=reg->getpc();
                break;
            case BEQ:case BNE:case BLT:
            case BGE:case BLTU:case BGEU:
                instruction.src1=reg->getreg(instruction.rs1);
                instruction.src2=reg->getreg(instruction.rs2);
                instruction.rd=reg->getpc();
                break;
            case LB:case LH:case LW:
            case LBU:case LHU:
                instruction.src1=reg->getreg(instruction.rs1);
                break;
            case SB:
            case SH:
            case SW:
                instruction.src1=reg->getreg(instruction.rs1);
                instruction.src2=reg->getreg(instruction.rs2);
                break;
            case ADDI:
                instruction.src1=reg->getreg(instruction.rs1);
                break;
            case SLTI:
            case SLTIU:
                instruction.src1=reg->getreg(instruction.rs1);
                break;
            case XORI:
            case ORI:case ANDI:
                instruction.src1=reg->getreg(instruction.rs1);
                break;
            case SLLI:case SRLI:case SRAI:
                instruction.src1=reg->getreg(instruction.rs1);
                break;
            case ADD:case SUB:case SLL:case SLT:case SLTU:
            case XOR:case SRL:case SRA:case OR:case AND:
                instruction.src1=reg->getreg(instruction.rs1);
                instruction.src2=reg->getreg(instruction.rs2);
                break;
            default:break;
        }
    }
    void perform(){
        instruction.chooseType();
        instruction.setarg();
        setsrc();
    }
    void go_on(EX &next){
        next.instruction=instruction;
    }
};

#endif //RISCV5_INSTRUCTIONDECODE_HPP
