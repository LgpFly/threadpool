# gdb book

## breakpoint

1. $bpnum:上次设置的断点编号
2. $_hit_bpnum:上次命中的断点编号，程序运行之后上次命中的断点号
3. $_hit_locno:断点代码位置编号，程序运行之后上次命中的代码位置
4. disable bpnum.locno 将断点设置为无效，但是不删除
5. enable bpnum.locno 将断点设置为有效
6. 设置断点：b (函数名，代码行数) 
7. 条件断点 b func if cond(a == 5) 
8. 只触发一次的断点， 触发之后自动删除 tbreak args
9. 正则表达式设置断点：rbreak regex (rbreak foo*, 就给所有的foo开头的函数都打上断点) 
10. rbreak file.c:foo* 断点的查找限定在file.c文件中
11. info b 查看断点
12. 如果在共享库中设置断点，但是共享库还没有加载，那设置断点时能不能设置上通过下面的来控制
    1.  set breakpoint pending auto gdb的默认行为
    2.  set breakpoint pending on 可以预加载在动态库中设置断点
    3.  set breakpoint pending off 不可以
13. 给已经设定的断点添加和删除条件和忽略断点多少次
    1.  condition bnum expression 给第第bnum个断点添加expression这个条件
    2.  condition bnum 给第bnum个删除条件
    3.  ignore bnum count 忽略第bnum个断点 count次
14. 在断点处加命令
    > commands bnum(相当于给第几个断点加命令) <br> silent(不会打印在断点处停止的通常消息) <br> printf "a:%d",a <br> cont(continue) <br>end (必须时end结尾)
15. 动态打印（以后就不用重新在文件中添加打印，再重新编译输出了）<font color="#dd0000">（鸡肋 直接用command来进行往文件里面写）</font>
    1. set dprintf-style (gdb/call/agent(三选1))，但是只有gdb支持%V的格式
    2. set dprintf-function (fprintf/printf) 选择用哪个函数
    3. 如果选用fprintf的话需要设置往哪里写 set dprintf-channel mylog
    4. dprintf num(第几行加这个类似断点的东西), "数据格式", 数据 （后面这就是往里面写的或者打印的格式）
16. <font color="#dd0000">直接用command来进行往文件里面写</font>
    1.  设置断点
    2.  call (FILE*)fopen("log.txt", "w+")
    3.  set $log_fp = $1
    4.  commands 1.1
    5.  silent
    6.  call fprintf($log_fp, "i is :%llu", i)
    7.  call fflush($log_fp)
    8.  continue
    9.  end
17. 多线程调试
    1.  info thread
    2.  thread n 切换到第n号线程
    3.  b location thread n if condition
18. 附着到指定的进程：gdb attach pid
19. 进入某个函数之后 可以用finish跳出当前函数
20. 格式话打印 p/x a
    1.  x 16进制
    2.  o 8进制
    3.  d/u 十进制
    4.  s 字符串
    5.  t 二进制的形式进行打印
    6.  a 打印地址
21. x/nfu addr
    1.  n是想打印几个 默认一个
    2.  f是以什么格式打开 x/u/d/o/s等
    3.  u是每个单元几个字节 b h w g 还能用s这个地方 x/hs 打印16字节字符串 x/ws 打印32字节字符串 s是打印8字节字符串
22. 栈信息的调试
    1.  ctrl-c 可以停止程序 或者程序出现的段错误
    2.  bt 会显示所有的堆栈的信息
    3.  up n 会调整栈到相应的位置
    4.  down n 调整栈的位置
    5.  调整到相应的位置之后，info f 会打印栈的信息
    6.  info args 会显示函数的传入参数 可以打印当前函数的参数信息



