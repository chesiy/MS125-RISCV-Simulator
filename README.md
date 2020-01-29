# RISC-V Simulator
## Brief Introduction
  在过去的一周里，我完成了一个RISC-V模拟器，可以解析RISC-V32I指令集。我先后写了三个版本：
  1. 串行  
  2. 并行（使用等待闲置的方法处理Data Hazard和Control Hazard）    
  3. 并行（使用Forwarding处理Data Hazard，使用Branch Prediction处理Control Hazard） 
  
## Knowledge Points
**RISC-V32I指令集**：汇编语言的一种，每条指令语句都是简单的，仅涉及三个元素的操作。

**寄存器**：本次设计的模拟器采用32个*32位寄存器*和*PC寄存器*（用于记录当前程序运行到的位置）。

**指令**：长度为32位的01串，二进制表示，分为以下几类：  
  &emsp;1.寄存器间的简单运算（运算类指令）&emsp;  
  &emsp;2.内存操作，如读取和写入（内存操作）&emsp;  
  &emsp;3.流程控制操作，即跳转（分支）&emsp;  
  
**指令的执行**  
1.获取指令，从内存中PC寄存器指向的地址中读取指令内容  
2.分析指令，解析指令的类型、含义、操作  
3.获取指令右值，从寄存器或内存中读取  
4.按指令要求运算  
5.将结果写回左值  
6.移动PC寄存器向下一指令  

**基础结构**：需要一个模拟内存类，和一个模拟寄存器类。

**硬件分析**：硬件模块是一种由输入信号决定输出信号的设施，每一个硬件模块的任务是唯一确定的。对于RISC-V模拟器，我们可以将整体根据指令执行的流程来划分硬件块，使不同的块分别处理不同的任务。假设完成一条指令需要三个硬件块，那么最后一个模块完成后就会通知第一个模块——该指令完成，可以开始下一条指令。但是，三个模块同一时间只有一个在工作，另外两个被闲置，为了提高效率，采用**流水设计**，处理前一条指令的同时处理下几条指令。

 **五级流水结构**  
 **Instruction Fetch**：根据PC寄存器访问内存得到指令。（IF）  
 **Instruction Decode**：根据指令类型找到作为右值的寄存器，读值。解析立即数的值。（ID）  
 **Excution**：对解析好的值按指令要求进行计算。（EX）  
 **Memory Access**：根据计算出的地址从内存中读取数据值，或写入已准备好的数据值。（MA）  
 **Write Back**：完成对左值寄存器的赋值。（WB）  
 
 ### Hazard  
 **Data Hazard**：一个寄存器在一条赋值指令后紧接着又被调用（寄存器里的值就不是原来的那个了）
 
 **Control Hazard**：由跳转指令引起的提前读入错误指令（本来下一条指令应该是跳转后指令的后一条，但读入的却是跳转指令顺序的后一条）  
 最简单的处理方法是等待闲置，即给可能出现Hazard的指令上锁。也可以用Forwarding和Branch Prediction。
 
 **Forwarding**：在EX和MA过程中得到的应被赋给寄存器的值直接通知EX或ID（给下面几条指令用）。  
 【但Forwarding仍不能解决*内存load指令后紧随的依赖该寄存器的指令*这种情况，故只能等待闲置】  
 
 **Branch Prediction**：对跳转指令分类讨论：  
 &emsp;1.JAL直接跳至立即数位置，可直接被发现并做好处理。&emsp;   
 &emsp;2.JALR跳转位置依赖寄存器的值难以提前处理。&emsp;  
 &emsp;3.B类指令根据寄存器的比较情况确定是否跳转到立即数位置，这里就是需要预测的地方，即在比较结果算出之前(提前猜测下一条指令的位置。（注意：预测错误后仍要清除错误指令进度）&emsp;   
 
 ## Thoughts and Result
  在实现串行的过程中，我一开始采用的结构是一个command类完成IF和ID中解析指令的opcode确定大类的部分，然后按照R-type，I-type等类型分为六个类，再分别完成ID的剩余部分和EX、MA、WB。  
  然而一开始思路不太清楚，导致每个hpp文件的include关系非常混乱，写完之后发现出现了一大片类的前置声明而未定义导致的编译错误。于是我改变了自己的结构，采用了五级流水中的一个阶段作为一个类的结构，发现这样做不仅各个阶段之间的关系非常清晰，而且由串行到并行过渡时，并不需要进行大的重构。  
  从串行修改到并行，为了验证是否是真正的并行，将其中几个阶段调换了位置，发现答案依旧正确，但是发现IF和ID换了顺序之后，程序无法正常运行，应该是因为IF是否继续执行需要有从ID阶段传过来的是否需要停的信号。  
  
  加入forwarding处理data hazard的时候，MA给EX和ID分别传了数据。  
  分支预测采用的是根据最近5个的历史决定要不要跳，成功率如下：

Bulgarian  
Success num= 56853 total num= 71493  
 rate= 0.795225

magic  
success num= 35949 total num= 67869  
 rate= 0.529682

Hanoi  
Success num= 12840 total num= 17457  
 rate= 0.735522

Qsort  
Success num= 165302 total num= 200045  
 rate= 0.826324

queen  
success num= 51732 total num= 77116  
 rate= 0.670834

super loop  
success num= 371666 total num= 435027  
 rate= 0.854352

tak  
success num= 42479 total num= 60639  
 rate= 0.700523

Pi  
 Success num= 32350534 total num= 39956380  
 rate= 0.809646
