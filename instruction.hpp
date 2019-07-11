//
// Created by admin on 2019/7/4.
//

#ifndef RISCV5_INSTRUCTION_HPP
#define RISCV5_INSTRUCTION_HPP

#include "memory.hpp"
#include "utility.hpp"
#include <stdio.h>
///选好这条指令的type，然后把该赋的值给rs，rd，imm
enum InsType{
    EMPTY,//用于第一轮空跑                            //0
    LUI, AUIPC, JAL, JALR,                          //1-4
    BEQ, BNE, BLT, BGE, BLTU,BGEU,                   //5-10
    LB, LH, LW, LBU, LHU,                           //11-15
    SB, SH, SW,                                      //16-18
    ADDI, SLTI, SLTIU, XORI, ORI, ANDI, SLLI, SRLI, SRAI,     //19-27
    ADD, SUB, SLL, SLT, SLTU, XOR, SRL, SRA, OR, AND,          //28-37
    LOCK//如果decode之后发现寄存器或者pc没法用，就把类型设为lock。
    // 然后进行下去的时候，碰到lock就返回。
};

class inst{
    friend class IF;
    friend class ID;
    friend class EX;
    friend class MA;
    friend class WB;
    friend class Forwarding;
private:
    InsType type;
    unsigned int instr;//指令
    unsigned int imm,rd,rs1,rs2;
    unsigned int src1,src2,res;

public:
    inst(){
        instr=imm=rd=rs1=rs2=0;
        src1=src2=res=0;
    }
    void initial(){
        instr=imm=rd=rs1=rs2=0;
        src1=src2=res=0;
    }
    void chooseType(){
        unsigned int opcode;
        unsigned int func3,func7;
        opcode=(instr& 127);
        func3=((instr>>12)&0b111);
        func7=((instr>>25)&127);
        switch (opcode){
            case 0b0110111:{type=LUI;break;}
            case 0b0010111:{type=AUIPC;break;}
            case 0b1101111:{type=JAL;break;}
            case 0b1100111:{type=JALR;break;}
            case 0b1100011:{
                switch (func3){
                    case 0b000:{type=BEQ;break;}
                    case 0b001:{type=BNE;break;}
                    case 0b100:{type=BLT;break;}
                    case 0b101:{type=BGE;break;}
                    case 0b110:{type=BLTU;break;}
                    case 0b111:{type=BGEU;break;}
                }
                break;
            }
            case 0b0000011:{
                switch (func3){
                    case 0b000:type=LB;break;
                    case 0b001:type=LH;break;
                    case 0b010:type=LW;break;
                    case 0b100:type=LBU;break;
                    case 0b101:type=LHU;break;
                }
                break;
            }
            case 0b0100011:{
                switch (func3){
                    case 0b000:type=SB;break;
                    case 0b001:type=SH;break;
                    case 0b010:type=SW;break;
                }
                break;
            }
            case 0b0010011:{
                switch(func3) {
                    case 0: type = ADDI; break;
                    case 1:	type = SLLI; break;
                    case 2: type = SLTI; break;
                    case 3: type = SLTIU; break;
                    case 4: type = XORI; break;
                    case 5:
                        if(func7 == 0) type = SRLI;
                        else type = SRAI;
                        break;
                    case 6: type = ORI; break;
                    case 7: type = ANDI; break;
                }
                break;
            }
            case 0b0110011:{
                switch(func3) {
                    case 0: {
                        if (func7 == 0) type = ADD;
                        else type = SUB;
                        break;
                    }
                    case 1: {type = SLL; break;}
                    case 2: {type = SLT; break;}
                    case 3: {type = SLTU; break;}
                    case 4: {type = XOR; break;}
                    case 5: {
                        if (func7 == 0) type = SRL;
                        else type = SRA;
                        break;
                    }
                    case 6: {type = OR; break;}
                    case 7: {type = AND; break;}
                }
                break;
            }
            default: {type=LOCK;break;}
        }
    }
    void setarg(){
        switch (type){
            case LUI:
            case AUIPC:
                rd = ((instr >> 7) & 0b11111);
                imm = (instr >> 12 << 12);
                break;
            case JAL: {
                rd = ((instr >> 7) & 0b11111);
                unsigned int tmp1, tmp2, tmp3, tmp4;
                tmp1 = instr >> 31;//第20位
                tmp2 = instr >> 20 & 1;//第11位
                tmp3 = instr >> 21 & 1023;//第1到10位
                tmp4 = instr >> 12 & 0b11111111;//第12到19位
                imm = (tmp1 << 20) + (tmp4 << 12) + (tmp2 << 11) + (tmp3<<1);
                imm = signedExtend(imm, 20);//一共21位
                break;
            }
            case JALR: {
                rs1 = (instr >> 15) & 0b11111;
                rd = ((instr >> 7) & 0b11111);
                imm = (instr >> 20) & 4095;
                imm = signedExtend(imm, 11);
                break;
            }
            case BEQ:case BNE:case BLT:
            case BGE:case BLTU:case BGEU: {
                rs1 = instr >> 15 & 0b11111;
                rs2 = instr >> 20 & 0b11111;
                unsigned int tmp1, tmp2, tmp3, tmp4;
                tmp1 = (instr >> 31) & 1;//第12位
                tmp2 = (instr >> 7) & 1;//第11位
                tmp3 = (instr >> 8) & 0b1111;//第1到4位
                tmp4 = (instr >> 25) & 0b111111;//第5到10位
                imm = (tmp1 << 12) + (tmp2 << 11) +(tmp4 << 5) + (tmp3<<1);//按顺序连起来
                imm = signedExtend(imm, 12);//一共13位
                break;
            }
            case LB:case LH:case LW:
            case LBU:case LHU: {
                rs1 = (instr >> 15) & 0b11111;
                rd = (instr >> 7) & 0b11111;
                imm = (instr >> 20)& 4095;
                imm = signedExtend(imm, 11);
                break;
            }
            case SB:
            case SH:
            case SW: {
                rs1 = (instr >> 15) & 0b11111;
                rs2 = (instr >> 20) & 0b11111;
                unsigned int tmp1, tmp2;
                tmp1 = (instr >> 7) & 31;
                tmp2 = (instr >> 25) & 127;
                imm = tmp1+(tmp2<<5);//把tmp1和tmp2连起来
                imm = signedExtend(imm, 11);
                break;
            }
            case ADDI:case SLTI:
            case SLTIU:case XORI:
            case ORI:case ANDI: {
                rs1 = (instr >> 15) & 0b11111;
                rd = (instr >> 7) & 0b11111;
                imm = (instr >> 20) &4095;
                imm = signedExtend(imm, 11);
                break;
            }
            case SLLI:
            case SRLI:
            case SRAI: {
                rs1 = (instr >> 15) & 0b11111;
                rd = (instr >> 7) & 0b11111;
                imm = (instr >> 20) & 0b11111;
                imm = signedExtend(imm, 4);
                break;
            }
            case ADD:case SUB:case SLL:case SLT:case SLTU:
            case XOR:case SRL:case SRA:case OR:case AND: {
                rs1 = (instr >> 15) & 0b11111;
                rs2 = (instr >> 20) & 0b11111;
                rd = (instr >> 7) & 0b11111;
                break;
            }
            default:break;
        }
    }
    void printinst(){
        cout<<"inst=";printf("%X",instr);
        cout<<'\t';
    }
};


#endif //RISCV5_INSTRUCTION_HPP
