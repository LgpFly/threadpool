# makefile book

1. include 可以包含例如common.mk,target.mk为后缀的文件。可以正常使用这里面定义的变量等
2. 找所有.c结尾的文件$(wildcard *.c)
3. 将所有.c结尾的文件进行字符替换，替换成所有.o结尾的文件 $\(patsubst %.c, %.o, $(wildcard *.c)\)
4. VPATH:所有前置条件都会去这设置的路径进行寻找 VPATH=src:../head
5. vpath:为各种类型的文件分别设置寻找路径 (vpath %.c src) (vpath %.so ../lib64)
6. $^:所有依赖 $<:第一个依赖 $@:目标
7. 虚假目标，比如clean操作，如果不设定为虚假目标，而该目录下又恰巧有该文件，那么永远得不到执行，所以设定为虚假目标
   1. >.PHONY:clean <br> clean: <br> rm -fr *
   2. 程序有多个目标的时候,如果不这样的话就只能有一个目标
        >all:pro1,pro2,pro3 <br> .PHONY:all 
8. 赋值的话  直接用=就行，可以在后面追加 += 
9. 判断相等
    ```shell
    #判断相等
    ifeq ($(var), a)
        xxx
    else
        xxx
    endif

    #判断是否定义
    ifdef foo
    xxx
    else
    xxx
    endif
    ```
10. 替换字符
    ```shell
    comma:= ,
    empty:=
    space:= $(empty) $(empty)
    foo:= a b c
    bar:= $(subst $(space),$(comma),$(foo))
    # bar is now ‘a,b,c’.
    ```
   