#include <iostream>
#include "utility.hpp"
#include "excution.hpp"
#include "instruction.hpp"
#include "InstructionDecode.hpp"
#include "InstructionFetch.hpp"
#include "memory.hpp"
#include "MemoryAccess.hpp"
#include "WriteBack.hpp"
#include "forwarding.hpp"
#include <stdio.h>
#include <string.h>

memory mem;
predict pred;
regist reg(0,&mem);
IF fet(&reg);
ID deco(&reg,&pred);
EX exe(&reg,&pred);
MA meac(&reg);
WB wbck(&reg);
Forwarding forw;

int main() {
    mem.fullmem();
    while(true){
        wbck.perform();
        meac.perform();
        forw.MA_forward_EX(meac,exe);
        exe.perform();
        if(exe.confirm()==false){//跳错了
            deco.reget();
        }
        deco.perform();
        forw.MA_forward_ID(meac,deco);
        fet.perform();

        if(mem.is_end)break;
        //cantdo的情况主要是ID的时候pc正在被用
        meac.go_on(wbck);
        exe.go_on(meac);
        deco.go_on(exe);
        fet.go_on(deco);
    }

    pred.printpre();
    cout<<(unsigned int)((reg.getreg(10)) & 255u)<<endl;//只取最低八位

    return 0;
}