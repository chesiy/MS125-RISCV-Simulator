//
// Created by admin on 2019/7/4.
//

#ifndef RISCV5_INSTRUCTIONDECODE_HPP
#define RISCV5_INSTRUCTIONDECODE_HPP

#include <iostream>
#include "instruction.hpp"
#include "prediction.hpp"

///根据IF里读到的指令类型，从作为右值的寄存器里读值（rs），
/// 解析立即数的值，然后赋给（src）；
class ID{
private:
    regist *reg;
    predict *pre;
public:
    inst instruction;
    bool cantdo;

    ID(regist *r,predict *p):reg(r),cantdo(0),pre(p){}
    bool setsrc(){
        switch (instruction.type){
            case AUIPC:
                if(reg->unpc)return false;
                instruction.src1=reg->getpc()-4;
                break;
            case JAL:
                if(reg->unpc)return false;
                instruction.src1=reg->getpc()-4;
                break;
            case JALR:
                if(reg->unpc)return false;
                instruction.src1=reg->getreg(instruction.rs1);
                instruction.src2=reg->getpc();
                break;
            case BEQ:case BNE:case BLT:
            case BGE:case BLTU:case BGEU:
                if(reg->unpc)return false;
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
        return true;
    }

    void lockit(){//保护pc,现在只有JAL和JALR需要保护了
        switch (instruction.type) {
            case JAL:
            case JALR:
                reg->unpc++;
                break;
            default:
                break;
        }
    }

    void prediction(){
        if(instruction.type==BEQ||instruction.type==BGE||instruction.type==BGEU||instruction.type==BLT||
        instruction.type==BLTU||instruction.type==BNE){
            instruction.preresult=pre->predictit(instruction.type);
            if(instruction.preresult){//预测出来需要跳
                reg->changepc(instruction.rd-4+instruction.imm);
            }
        }
    }

    void reget(){
        instruction.initial();
        instruction.instr=reg->getinst();
    }

    void perform(){
        cantdo=false;
        if(instruction.type==LOCK)return;
        instruction.chooseType();
        instruction.setarg();
        if(!setsrc()){
            cantdo=true;
        }//需要等待了
        else {
            prediction();
            lockit();
        }
    }
    void go_on(EX &next){
        next.instruction=instruction;
        if(cantdo)next.instruction.type=LOCK;
    }
};

#endif //RISCV5_INSTRUCTIONDECODE_HPP
