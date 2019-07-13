  在过去的两个星期里，我用C++实现了一个RISC-V模拟器（支持RV32Ⅰ指令集），先后实现了串行、并行（用lock处理hazard）、并行（用forwarding处理data hazard）和并行（用branch prediction处理control hazard）。
  在实现串行的过程中，我一开始采用的结构是一个command类完成instruction fetch，和instruction decode中解析指令的opcode确定大类的部分，然后按照R-type，I-type等类型分为六个类，再分别完成ID的剩余部分和EX、MA、WB。然而一开始思路不太清楚，导致每个hpp文件的include关系非常混乱，写完之后发现出现了一大片类的前置声明而未定义导致的编译错误。于是我改变了自己的结构，采用了五级流水中的一个阶段作为一个类的结构，发现这样做不仅各个阶段之间的关系非常清晰，而且由串行到并行过渡时，并不需要进行大的重构。
  从串行修改到并行，之后为了验证是否是真正的并行，将其中几个阶段调换了位置，发现答案依旧正确，但是发现IF和ID换了顺序之后，程序无法正常运行，应该是因为IF是否继续执行需要有从ID阶段传过来的是否需要停的信号。
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
