/**********************************************************************
 * Copyright (C) 2022. IEucd Inc. All rights reserved.
 * @Author: weiyutao
 * @Date: 2022-10-18 16:35:25
 * @Last Modified by: weiyutao
 * @Last Modified time: 2022-10-18 16:35:25
 * @Description: this file involved the float calculate. and the some knowledge about machine show 
 * of process.
***********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <stdint.h>
#include <unistd.h>
#include <limits.h>

int main(int argc, char const *argv[])
{
    // IEEE regulation.电气和电子工程师协会 the float show in this file is based on it.
    // we will learn how to show a float and explore the problme about rounding.
    // we can start with the binary float. beacuse it is our final goal. how to show a
    // float based on binary, we can handle the float show for computer.
    // 12.34 = 1*10^1+2*10^0+3*10^-1+4*10^-2; so it mean the index is 2 1 0 . -1 -2,
    // so it has a dividing line on point, the negative index will be dedicated to the float.
    // and left of the point of float is equal to the integer number. so based on it, if 
    // we can show a float in form of adding the point and the number after the decimal point number
    // to the integer? of course, this thought is right, but not so simple.
    // we can give the conclusion first.
    // conclusion 1, the decimal of float binary x << 1 is equal to x/2, and the decimal of float bianry x
    // >> 1 is eqaul to x*2. we can do a test.
    // bin x 101.11 = 4+1+2^-1+2^-2 = float 5+1/2+1/4 = 23/4; if the decimal in float x << 1,
    // bin x<<1 = 10.111 = 1*2^1+0*2^0+1*2^-1+1*2^-2+1*2^-3 = 2+0+1/2+1/4+1/8 = 2+7/8=23/8
    // 23/4 /2 = 23/8; so if the decimal of float x << 1 is equal to x/2;
    // in the same way, if the decimal >> 1, is equal to x*2.
    // you should notice the precision of float, beacause we usually calculate used it. if you use the different
    // precision, you will get the error result. just like the missile interceptor system, the predict of 
    // hitting target is based on time and speed, the precision of time will be very important. if you use the
    // different precision, you will get the error predict target, then you will have a strong loss. this error will
    // bigger when the speed is infinite.
    // so we can get a conclusion, we can get more precision if we use the more bits to show the float.
    // just like 1001.010101001010101010 // it is float 9.几, if you use more bits, 1001.01010100101010101000100101010
    // you will get more precision float.
    // 1001.1 = 9.5
    // 1001.11 = 9.75
    // 1001.111 = 9.75+1/8

    // the next, we will learn the difference between float and double, the former is single precision, the last
    // is double precision. 1 8 23, 1 11 52, the former is float, the highest is singned, the second is the 
    // exp, the third is frac. the float is 32 bits, double is 64 bits.
    // the float and double in c language.
    // when you include math.h, you can get INFINITY to show +∞, the max number double can show is 1.8*10^308
    // if you want to define the max infinity and minux infinity, you can use head file.
    // you can use INT_MAX and INT_MIN to show infinity for int and need to include limits.h head file.
    // you can use DBL_MAX and -DBL_MAX to show infinity for double and need to include float.h
    // this is the method to show infinity used head file, you can also define by yourself
    // used the infinity number you known.
    printf("%lf\n", DBL_MAX); // the max infinity for double.
    printf("%d\n", INT_MAX);  // the max infinity for int.

    // the transform among int, float and double.
    // transform from int to float, will not overflow, but can be rounded
    // transform from int or float to double, will not overflow and will get more precision.
    // transform from double to float, the overflow will be happend, if it happend, the number will be infinity.
    // of course, beacuse the precision to be smaller, the rounding will be happend.
    // transform float or double to int, the number will be rounded to zero, just like
    // -1.001 will be transformed to -1, 1.99 will be transformed to 1. because the precision will be zero.
    // we can think it will be overflow. so it will usually be a error from floatr or double to int, because
    // it will be overflow.


    // the next we will learn the machine show of process. it is the chapter3 in csapp
    // we should give three explain, code, assembly code, machine code. the code is the process we write
    // used c language or other program language. the assembly code is text show of machine code, involved the
    // instruction in the process, the machine code is the generated by the assembly code, compiledr and
    // the linker. the assembly is the output of gcc. the step is as follow.
    // code --gcc--> assembly code --gcc and complier and linker --> machine code. we can review the compiler
    // for on program what we have learned in chapter1, it involved pretreatment, compilation, 
    // assembly, link. 预处理 编译 汇编 链接。
    // you can split the process that gcc from code to machine code.
    // code --pretreatment --> gcc -E, you will arrive step 1 use this param. 
    // this step will integration all program the main function involved. so it will find the head file and realize c file of the head file.
    // compilition gcc -S, you will arrive step 2 use this param. return the .s file. this step involved the checking for program.
    // assembly gcc -c, you will arrive the step 3 use this param. return the obj file what is the text show of machine code.
    // link. gcc, you will finish from code to machine code not use any param.
    // so if you want to learn this chapter, you should use gcc -s to get the .s file.
    // your all study will based on it. beacase it is the text show of machine code, we can read it easily.

    // generally, it will be the same effect with assembly programer code if you use the 
    // modern optimizing compiler. and we can use the high-level language to simplify our
    // code, so it is the reason why c, c++, java, python can be so popular in modern program.
    // another advantage used high-level language is compatibility, you can use the code that high-level language
    // coded to run at different machine. then why we should learn the compiler code? beacause you can 
    // do the greater optimize for you program and you can see some thing that dedicated to the compiler code.
    // this chapter, the machine language of intel we used is x86-64. it is original from 1978.
    // 32 bits machine can use 2^32 bytes random access memory, it is about 4GB. but 64 bit machine
    // can use 2^48 bytes random access memory, it is about 256TB. intel processor commonly known as
    // x86, 
    // page 148

    // the program counter : named pc, its role is to give the address in memory of next instruction
    // gcc -Og -S chapter3_test.c
    /**
     * use the instruction above, you can get the assembly instruction just like the next.
    pushq	%rbx   // push the %rbx into stack. the %rbx is register
	movq	%rdx, %rbx  // 
	call	mult2
	movq	%rax, (%rbx)
	popq	%rbx

    it will be genereted the hex code in .o file if you used -c param for gcc just like the next row 
    after assembling. you can check this binary code in .o file, and you can also check it by using gdb.
    the method is, gdb can debug the bianary .exe file, it can also debug the .o file.
    gdb chapter3_test
    gdb chapter3_test.o
    you should use the former if you want to debug the process and check the variable, pointer, and logical rule.
    you should use the last if you want to debug the assembly instruction, just like the push pop mov and call etc.

    this .o file involved the bianary code of assembly instruction just like push, pop.  the .exe file involved
    the binary code of machine code. this code will be executive by machine directly.
    fileName.c --> code for people.
    fileName.c ++ include file ++ define --> pretreatment
    fileName.s --> assembly instruction(push pop mov call) used gcc -Og -S
    fileName.o --> hex code for assembly instruction used gcc -Og -c
    fileName.exe --> bianry code for assembly instruction used gcc -Og -o

    so the order is ,c file --(gcc -Og -S)--> assembly instruction(.s file) --(gcc -Og -c)--> hex code(.o file) -(gcc -Og -o)-> binary code(.exe file).
    hex code in .o file,just like 53 48 89 d3 e8 00 00 00 00 48 89 03 5b c3, you can use gdb fileName.s to get it
    x/14xb multstore, this code in gdb program means get the 14 byte hex code start from multstore function
    in .o file. you can also open this .o file used vim, and show it used xxd to show binary. you can use the command 
    %!xxd in vim process. 

    x/14xb main, this command can used in gdb, it mean show the debug file orginal code start from main
    function to step 14 byte. the x mean hex show, the b means byte.

    you can also use the objdum to disassembly the .o file. just like objdump -d fileName.o
    the next code show the assembly instruction for each hex code, it is disassembly.
    the left is hex code in .o file, the right code is the assembly instruction corresponding the left hex code.
    0000000000000000 <multstore>:
    0:   53                      push   %rbx
    1:   48 89 d3                mov    %rdx,%rbx
    4:   e8 00 00 00 00          callq  9 <multstore+0x9>
    9:   48 89 03                mov    %rax,(%rbx)
    c:   5b                      pop    %rbx
    d:   c3                      retq   



    of course, the machine can just known the hex code, and it will know nothing about the 
    assembly code transformed from .c file in .s file.

    commonly used and less operation instruction will have more byte numbers.
    the concept of disassembly is got the assembly code based on hex code in .o file. it mean need not
    read the assembly code from .s file. it is the truely disassembly.
    the assembly code that disassembly are different from the assembly code in .s file that gcc generated.
    you can disassembly based on the exe file, and you can also disassembly based on the .o file. you can 
    get assembly code based on these method above.
    you should know these above code. 

    // page 154
    */

    return 0;
}
