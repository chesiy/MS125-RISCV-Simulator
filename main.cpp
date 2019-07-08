#include <iostream>
#include "utility.hpp"
#include "excution.hpp"
#include "instruction.hpp"
#include "InstructionDecode.hpp"
#include "InstructionFetch.hpp"
#include "memory.hpp"
#include "MemoryAccess.hpp"
#include "WriteBack.hpp"
#include <stdio.h>
#include <string.h>

memory mem;
regist reg(0,&mem);
IF fet(&reg);
ID deco(&reg);
EX exe(&reg);
MA meac(&reg);
WB wbck(&reg);

int main() {

    mem.fullmem();
/*    for(int i=0;i<10000;i++){
        int tmp= static_cast<int>(mem.getmem(i));
        printf("%X",tmp);
        cout<<' ';
    }
    cout<<'\n';
*/
    while(!mem.is_end){
    //    cout<<i<<' ';
        fet.perform();
        fet.go_on(deco);

        deco.perform();
        deco.go_on(exe);

        exe.perform();
        exe.go_on(meac);

        meac.perform();
        meac.go_on(wbck);

        wbck.perform();
  //      reg.printreg();
  //      i++;
    }
    cout<<(unsigned int)((reg.getreg(10)) & 255u)<<endl;

    return 0;
}