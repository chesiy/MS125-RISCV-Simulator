//
// Created by admin on 2019/7/9.
//

#ifndef RISCV5_FORWARDING_HPP
#define RISCV5_FORWARDING_HPP

#include "InstructionDecode.hpp"
#include "excution.hpp"
#include "MemoryAccess.hpp"

class Forwarding{//除了要改pc的六个（JAL~BGEU）其他都需要forwarding
public:
    void MA_forward_EX(MA &ma,EX &ex){
        switch (ma.instruction.type){
            case LUI:
            case AUIPC:
            case LB:case LH:case LW:
            case LBU:case LHU:
            case SB:
            case SH:
            case SW:
            case ADDI:case SLTI:
            case SLTIU:case XORI:
            case ORI:case ANDI:
            case SLLI:
            case SRLI:
            case SRAI:
            case ADD:case SUB:case SLL:case SLT:case SLTU:
            case XOR:case SRL:case SRA:case OR:case AND:
                if(ma.instruction.rd==ex.instruction.rs1&&ma.instruction.rd!=0){
                    //后面指令的execution阶段要用寄存器里还没被写入的数据
                    ex.instruction.src1=ma.instruction.res;
                }
                if(ma.instruction.rd==ex.instruction.rs2&&ma.instruction.rd!=0){
                    ex.instruction.src2=ma.instruction.res;
                }
                break;
            default:break;
        }
    }
    void MA_forward_ID(MA &ma,ID &id){
        switch (ma.instruction.type){
            case LUI:
            case AUIPC:
            case LB:case LH:case LW:
            case LBU:case LHU:
            case SB:
            case SH:
            case SW:
            case ADDI:case SLTI:
            case SLTIU:case XORI:
            case ORI:case ANDI:
            case SLLI:
            case SRLI:
            case SRAI:
            case ADD:case SUB:case SLL:case SLT:case SLTU:
            case XOR:case SRL:case SRA:case OR:case AND:
                if(ma.instruction.rd==id.instruction.rs1&&ma.instruction.rd!=0){
                    //后面指令的decode阶段要读寄存器里还没被写入的数据
                    id.instruction.src1=ma.instruction.res;
                }
                if(ma.instruction.rd==id.instruction.rs2&&ma.instruction.rd!=0){
                    id.instruction.src2=ma.instruction.res;
                }
                break;
            default:break;
        }
    }
    void EX_forward_ID(EX &ex,ID &id){
        switch (ex.instruction.type){
            case LUI:
            case AUIPC:
            case LB:case LH:case LW:
            case LBU:case LHU:
            case SB:
            case SH:
            case SW:
            case ADDI:case SLTI:
            case SLTIU:case XORI:
            case ORI:case ANDI:
            case SLLI:
            case SRLI:
            case SRAI:
            case ADD:case SUB:case SLL:case SLT:case SLTU:
            case XOR:case SRL:case SRA:case OR:case AND:
                if(id.instruction.rs1==ex.instruction.rd&&ex.instruction.rd!=0){
                    //后面指令的execution阶段要用寄存器里还没被写入的数据（是个二传）
                    id.instruction.src1=ex.instruction.res;
                }
                if(id.instruction.rs2==ex.instruction.rd&&ex.instruction.rd!=0){
                    id.instruction.src2=ex.instruction.res;
                }
                break;
            default:break;
        }
    }

};
#endif //RISCV5_FORWARDING_HPP
