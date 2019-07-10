//
// Created by admin on 2019/7/4.
//

#ifndef RISCV5_EXCUTION_HPP
#define RISCV5_EXCUTION_HPP

#include "memory.hpp"
#include "utility.hpp"
#include <iostream>
#include "instruction.hpp"
#include "MemoryAccess.hpp"

using namespace std;

class EX{
private:
    regist *r;
public:
    inst instruction;

    EX(regist *reg):r(reg){}
    void perform(){
        if(instruction.type==EMPTY|instruction.type==LOCK)return;
        switch (instruction.type){
            case LUI:
                instruction.res=instruction.imm;
                break;
            case AUIPC:
                instruction.res=instruction.src1+instruction.imm;
                break;
                //JAL~BGEU的pc是要变的，这里的res并不完全是要写入寄存器的值
                //所以在forwarding的时候，应该要特殊处理
            case JAL://此result是个pc
         //       instruction.res=instruction.src1+instruction.imm;
         //       break;
            case JALR://此result是个pc
         //       instruction.res=instruction.src1+instruction.imm;
         //       instruction.res=setzero(instruction.res);//最低位置零
                break;
                //B-type的result pc并没有在execution阶段被算出来，
                // 这里的result甚至并不用被写入寄存器
            case BEQ:
                instruction.res= static_cast<unsigned int>(instruction.src1==instruction.src2);
                break;
            case BNE:
                instruction.res= static_cast<unsigned int>(instruction.src1!=instruction.src2);
                break;
            case BLT:
                instruction.res= static_cast<unsigned int>((int)instruction.src1<(int)instruction.src2);
                break;
            case BGE:
                instruction.res= static_cast<unsigned int>((int)instruction.src1>=(int)instruction.src2);
                break;
            case BLTU:
                instruction.res= static_cast<unsigned int>(instruction.src1<instruction.src2);
                break;
            case BGEU:
                instruction.res= static_cast<unsigned int>(instruction.src1>=instruction.src2);
                break;
            case LB:case LH:case LW:
            case LBU:case LHU:
                instruction.src1=instruction.src1+signedExtend(instruction.imm,11);
                break;
            case SB:case SH:case SW:
                instruction.src1=instruction.src1+signedExtend(instruction.imm,11);
                break;
            case ADDI:
                instruction.res=instruction.src1+instruction.imm;
                break;
            case SLTI:
                instruction.res= static_cast<unsigned int>((int)instruction.src1<(int)instruction.imm);
                break;
            case SLTIU:
                instruction.res= static_cast<unsigned int>(instruction.src1<instruction.imm);
                break;
            case XORI:
                instruction.res=(instruction.src1^instruction.imm);
                break;
            case ORI:
                instruction.res=(instruction.src1|instruction.imm);
                break;
            case ANDI:
                instruction.res=(instruction.src1&instruction.imm);
                break;
            case SLLI:
                instruction.res=(instruction.src1<<instruction.imm);
                break;
            case SRLI:
                instruction.res=(instruction.src1>>instruction.imm);
                break;
            case SRAI:
                instruction.res=(instruction.src1>>instruction.imm)|(instruction.src1>>31<<31);
                break;
            case ADD:
                instruction.res=instruction.src1+instruction.src2;
                break;
            case SUB:
                instruction.res=instruction.src1-instruction.src2;
                break;
            case SLL:
                instruction.res=(instruction.src1<<instruction.src2);
                break;
            case SLT:
                instruction.res= static_cast<unsigned int>((int)instruction.src1<(int)instruction.src2);
                break;
            case SLTU:
                instruction.res= static_cast<unsigned int>(instruction.src1<instruction.src2);
                break;
            case XOR:
                instruction.res=(instruction.src1^instruction.src2);
                break;
            case SRL:
                instruction.res=(instruction.src1>>instruction.src2);
                break;
            case SRA:
                instruction.res=((instruction.src1>>instruction.src2)|(instruction.src1>>31<<31));
                break;
            case OR:
                instruction.res=(instruction.src1|instruction.src2);
                break;
            case AND:
                instruction.res=(instruction.src1&instruction.src2);
                break;
            default:break;
        }
    }
    void go_on(MA &next){
        next.instruction=instruction;
    }
};
#endif //RISCV5_EXCUTION_HPP
