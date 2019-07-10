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
regist reg(0,&mem);
IF fet(&reg);
ID deco(&reg);
EX exe(&reg);
MA meac(&reg);
WB wbck(&reg);
Forwarding forw;

int main() {
    mem.fullmem();
//    int i=1;
    while(true){
 //       cout<<i<<' ';
        wbck.perform();
        meac.perform();
        forw.MA_forward_EX(meac,exe);
        exe.perform();
        deco.perform();
        if(!deco.cantdo)forw.MA_forward_ID(meac,deco);
        if(!deco.cantdo)forw.EX_forward_ID(exe,deco);
        if(!deco.cantdo)fet.perform();
        if(mem.is_end)break;
        //cantdo的情况主要是ID的时候pc正在被用
        meac.go_on(wbck);
        exe.go_on(meac);
        deco.go_on(exe);
        if(!deco.cantdo)fet.go_on(deco);
  //      i++;
 //       reg.printreg();
//        fet.instruction.printinst();
    }
    cout<<(unsigned int)((reg.getreg(10)) & 255u)<<endl;

    return 0;
}