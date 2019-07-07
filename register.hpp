//
// Created by admin on 2019/7/4.
//

#ifndef RISCV5_REGISTER_HPP
#define RISCV5_REGISTER_HPP

using namespace std;

/*class memory;

class regist{
private:
    int pc;
    int regi[32];
    memory *m;
public:
    regist(int p,memory *memo){
        for(int i=0;i<32;i++)regi[i]=0;
        pc=p;
        m=memo;
    }
    int getpc(){return pc;}

    void changepc(int x){pc=x;}

    void changereg(int pos,int x){
        regi[pos]=x;
    }
    int getreg(int pos){
        return regi[pos];
    }
    int load(int pos,int n){//把内存里位置是pos之后的n位读入寄存器(n小于4）
        int res,tmp[4];
        for(int i=0;i<n;i++){
            char t=m->getmem(pos+i);
            tmp[i]= static_cast<int>(t);
        }
        for(int i=n-1;i>=0;i--)res=(res<<8)+tmp[i];
        return res;
    }
    void store(int pos,int x,int n){//把寄存器里的x存入内存中位置pos之后的n位
        int tmp[4];
        for(int i=0;i<4;i++){
            tmp[i]=(x&0xff);
            x>>=8;
        }
        for(int i=0;i<n;i++){
            m->setmem(pos, static_cast<char>(tmp[i]));
            pos++;
        }
    }
};*/
#endif //RISCV5_REGISTER_HPP
