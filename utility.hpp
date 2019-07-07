//
// Created by admin on 2019/7/4.
//

#ifndef RISCV5_UTILITY_HPP
#define RISCV5_UTILITY_HPP

#include <iostream>
using namespace std;

unsigned int signedExtend(unsigned int data,int bits){//bits是最高位
    if((data>>bits)&1){
        data|=(0xffffffff>>bits<<bits);//扩展成32位
    }
    return data;
}

unsigned int setzero(unsigned int x){
    if(x&1)return x^1;
    else return x;
}

unsigned int decodeit(char c){
    if(c>='0'&&c<='9')return c-'0';
    else return c-'A'+10;
}
unsigned int string_to_int(char* s){//把16进制的文本转化为int
    unsigned int res = 0;
    for (int i=0; s[i]!='\0'; ++i)
        res = (res << 4) + decodeit(s[i]);
    return res;
}


#endif //RISCV5_UTILITY_HPP
