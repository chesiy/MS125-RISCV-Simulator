//
// Created by admin on 2019/7/4.
//

#ifndef RISCV5_MEMORY_HPP
#define RISCV5_MEMORY_HPP

#include "utility.hpp"
#include <cstring>

class memory {
#define MAXN 0x3fffff
private:
    unsigned char mem[MAXN];//别忘了改
public:
    bool is_end=false;
    memory(){
        memset(mem,0,sizeof(mem));
    }
    void fullmem(){//把数据读入内存
        char tmp[20];
        memset(tmp,0,sizeof(tmp));
        int cursor=0;
        while(true) {
            cin>>tmp;
            if(tmp[0]=='#')break;
            if (tmp[0] == '@')cursor = string_to_int(tmp + 1);
            else {
                mem[cursor] = static_cast<unsigned char>(string_to_int(tmp));
                cursor++;
            }
            memset(tmp, 0, sizeof(tmp));
        }
    }

    inline unsigned char getmem(unsigned int p)const{
        return mem[p];
    }
    void changemem(int p,unsigned char ch){
        mem[p]=ch;
        if(p==0x30004)is_end=true;//当最后访问到0x30004的时候程序结束，并且最后写了0x30004
    }
};

class regist{
private:
    unsigned int pc;
    unsigned int regi[32];
    memory *m;
public:
    int unpc;//whether pc is available
    int unreg[32];//whether available

    regist(unsigned int p,memory *memo){
        for(int i=0;i<32;i++){
            regi[i]=0;unreg[i]=0;
        }
        unpc=0;
        pc=p;
        m=memo;
    }
    inline unsigned int getpc(){return pc;}

    inline void changepc(unsigned int x){pc=x;}

    void changereg(int pos,unsigned int x){
        if(pos==0)return;//0号寄存器永远是0
        regi[pos]=x;
    }
    unsigned int getreg(int pos){
        if(pos==0)return 0u;
        return regi[pos];
    }
    unsigned int load(unsigned int pos,int n){//把内存里位置是pos之后的n位读入寄存器(n小于4）
        unsigned int res=0,tmp[4];
        for(int i=0;i<n;i++){
            tmp[i]= static_cast<unsigned int>(m->getmem(pos+i));
        }
        for(int i=n-1;i>=0;i--)res=(res<<8)+tmp[i];
        return res;
    }
    void store(unsigned int pos,unsigned int x,int n){//把寄存器里的x存入内存中位置pos之后的n位
        unsigned int tmp[4];
        for(int i=0;i<4;i++){
            tmp[i]=(x & 255);
            x>>=8;
        }
        for(int i=0;i<n;i++){
            m->changemem(pos, static_cast<unsigned char>(tmp[i]));
            pos++;
        }
    }
    unsigned int getinst(){
        unsigned int res=load(pc,4);
        pc+=4;
        return res;
    }
    void printreg() {
        cout << "pc=";
        printf("%X", pc);
        cout << '\n';
        for (int i = 0; i < 32; i++) {
            printf("%X",regi[i]);
            cout<< ' ';
        }
        cout << '\n';
    }

};
#endif //RISCV5_MEMORY_HPP
