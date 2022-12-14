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
#include <inttypes.h>

char *getss(char *s) 
{
    int c;
    char *dest = s;
    while ((c = getchar()) != '\n' && c != EOF)
    {
        *dest++ = c;
    }
    if (c == EOF && dest == s)
    {
        return NULL;
    }
    *dest++ = '\0';

    return s;
}

void echo() 
{
    char buf[8]; // define the size of array
    getss(buf); 
    // get a line form standard input, and store it used buf
    // if you stored a big size content, you will generate a reference boundary error.
    puts(buf); // echo the content in buf.
}

// void echo_test() 
// {
//     char buf[8];
//     gets(buf);
//     puts(buf);
// }

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

    /**
    the intel assembly instruction.
    the assembly code suffix. based on the byters of the variable.
    b/1 bytes; w/2 bytes; l/4 bytes; q/8 bytes; s/float; l/double;
    the intel term is not the bytes, the unit is word for intel.
    datatype        intel term         assembly suffix      size(bytes)
    char            byte                b                       1 byte
    short           word                w                       2 bytes
    int             double words        l                       4 bytes
    long            four words          q                       8 bytes
    char *          four words          q                       8 bytes
    float           single precision    s                       4 bytes
    double          double precision    l                       8 bytes
    the special is float and double. you can just keep in mind that
    just like the mov instruction.
    movb    mov byte
    movw    mov word
    movl    mov double words
    movq    move four words
    32 bits can be names long word.
    movl can show four bytes integer and eight bytes double.
    movs can show float.

    a x86-64 cpu involved a group of 16 registers, what can store 64 bits. these registers
    can store integer and pointer. the name of these registers are start with %r, but the name
    rule is not so single, it is based on the history of register development.

    the original 8086 : the register numbers is 8, 16 bits. %rax~%rbp
        %rax %rbx %rcx %rdx %rsi %rdi %rbp
    IA32 version : the register numbers is 8, expand to 32 bits.
        %rax %rbx %rcx %rdx %rsi %rdi %rbp
    x86-64 version : the register numbers is 16, %rax~%rbp expand to 64 bits. the new registers
    %r8~%r15 is 64 bits. all registers are 64 bits in this version.

    what is the concept of the register? first, the register is 64 bits in x86-64 version.
    we should combine the assembly instruction to consider the register, just like the movb
    movw movl, the assembly instruction can do operation from the low bits of register. the
    16 bits operation can operate 2 bytes, 32 bits operation can operate 4 bytes, 64 bits operation
    can operate all register, beacause the register has 64 bits. then if we used assembly
    instruction to operate less than 64 bits, then what the rest bits state of the register will be?
    it also has a rule, if you operate less than 8 bytes, the rest bits will not be changed if you operated
    1 and 2 bytes, and the rest bits will be changed to 0 if you operated 4 bytes. the different register
    has the different function. the special is stack pointer %rsp what can point the end address for stack.
    the function of the register involved stack management, pass the function params, the return value of function,
    store the local or temp data. it has the special rule.


    the multiple oprands can be exists in assembly instruction, it was suppoeted in x86-64.
    the operands has three types, the three types are defined based on the original data what
    is the object that register will operate. the original data can be from const, register and
    memory. the const can be named immediate, just like $0x1f.  the reigister is register, can be
    used by R[r]. the memory can be named memory reference,  can be used by M[Addr].

    just like the follow
    operand type        format      operand value       name
    the immediate       $Imm        Imm                 immediate addressing
    register            r_a         R[r_a]              register addressing
    memory              Imm         M[Imm]              absolute addressing
    memory              (r_a)       M[R[r_a]]           indirect addressing
    memory              Imm(r_b)    M[Imm+R[r_b]]       basic address sub the offset addressing
    memory              (r_b, r_i)  M[R[r_b]+R[r_i]]    indexed adddressing
    memory              Imm(r_b, r_i)   M[Imm+R[r_b]+R[r_i]] indexed addressing
    memory              (, r_i, s)  M[R[r_i]*s]         proportion indexd addressing
    memory              Imm(, r_i, s)   M[Imm+R[r_i]*s] proportion indexd addressing
    memory              (r_b, r_i, s)   M[R[r_b]+R[r_i]*s]  proportion indexd addressing
    memory              Imm(r_b, r_i, s) M[Imm+R[r_b]+R[r_i]*s] proportion indexd addressing

    you can keep in mind it by three type operated by register.
    the first type, the data from immediate. $Imm, it is const number.
    the second type, the data from register. r_a, R[r_a], you should use R[] to index the register
    the third type, memory, it involved many types,
        r_b, the offset to immediate.
        r_i, the indexd addressing.
        s, the proportion to r_i, it is limited to 1, 2, 4, 8. the s is based on the r_i
        you should use the Imm if the format has the Imm(), just like Imm(r_b) = M[Imm+R[r_b]]
        (r_b) = M[R[r_b]]. it is indirect addressing. you should use M[] index the memeory operand.
        you should use (r_b) not the r_b to distinguish the memory relative addressing and register addressing.
        but you should notice, if you use the address directly, then you are addressing based on the address, it is named memory addressing.
        just like 0x104, this means you want to return the content of this memory, and you should notice, all
        the return values are address, it means the return values of assembly instructions are all the address.

    immediate : $Imm   Imm
    register  : r_a    R[r_a]         register addressing
    memory    : 0x104   M[0x104]      absolute addressing
    memory    : (r_a)  M[R[r_a]]      indirect memory addressing
    memory    : Imm(r_b) M[Imm+R[r_b]]      offset memory addressing
    memory    : Imm(r_b, r_i)  M[Imm+R[r_b]+R[r_i]]     indexd addressing
    memory    : Imm(r_b, r_i, s)    M[Imm+R[r_b]+R[r_i]*s]    proportion indexd addressing

    注意三种操作数类型的专业术语，分别为立即数、寄存器和内存引用，注意内存引用的专业术语
    r_b  : offset to the immediate      基址加偏移
    r_i  : indexd to the immediate      变址
    s    :  proportion to the r_i      比例变址
    只有r_b的情况我们称之为基址加便宜，有了r_i就称为变址，有了s就称为比例变址，注意没有r_i只有s是没有意义的

    the above knowledge, you should know a few important points.
    1 you should understand the calculate of binary, dec, and hex. just like,
        (bin : 10001) + (dec : 10) = 17 + 10 = 27 = bin : 0001 1011
        you should understand the hex calculate, because it is general for people.
            0x100 + 0x3 * 4 = 0x100 + 0xc = 0x10c. notice, each min unit in the hex calculate are 1, and
            the max unit is f. each unit in hex mean 4 bits. because the max number in hex is f, it mean 16 for dec.
            0x100 + 0xc = 0x10c. you can try to transform it from hex to binary.
            0001 0000 0000 + 0000 0000 1100 = bianry : 0001 0000 1100 = hex : 10c = dec : 256+12=268
        you should understant that, 8 bits are 1 byte, 4 bits can represent the max hex f. so 32 bits can present
        8 hex. and the same system can add directly, just like add(hex, hex). you can add directly as long as it has not
        greater than max hex f. you should use the binary idea to calculate it if it happend.
    2 the assembly oprands has three types, immediate, register, memory. the format $0x100 means immediate,
    it will return the value of this address 0x100, it is also an address. the format %rax means register, it will
    return the value of R[%rax], it is also an address. the format 0x100 means absolutely memory addressing,
    it will return the value of M[0x100], it is also an address. the format (%rax) means relative memory addressing,
    it will return the value of M[R[%rax]], it is also an address. so the different between %rax and (%rax) is register addressing
    and memeory addressing. the memory addressing format is Imm(%rax, %rbx, s), you should use the basic address Imm, if it is exist.
    the s is dedicated to %rbx, the %rax is the offset for Imm. the %rbx is indexd param. it means Imm+%rax+%rbx*s.
    $0x100 means immediate addressing. 0x100 means absolutely memory addressing.


    now, give you a table, you should give the return value of the assembly operands based on it.
    address     value                   register       value
    0x100       0xff                    %rax            0x100
    0x104       0xab                    %rcx            0x1
    0x108       0x13                    %rdx            0x3
    0x10c       0x11


    assemble oprand         addressing type        apression          return value
    %rax                    register               R[%rax]              0x100
    $0x108                  immediate              0x108                0x108
    0x104                   absolutely memory       M[0x104]            0xab
    (%rax)                  relative memory         M[R[%rax]]          0xff
    4(%rax)                 offset memory           M[0x4+R[%rax]]      0xab
    260(%rcx, %rdx)         indexd memory           M[0x104+R[%rcx]+R[%rdx]]    0x13   note:dec 260 = hex 0x104
    0xfc(, %rcx, 4)         proportion indexd memory M[0xfc+R[%rcx]*4]  0x11       note: hex 0xfc+ hex 0xc = 0x10c


    then, the commonly used instruction is mov. it means copy the data of one address to the other address.
    mov s, d        s->d
    movb. movw, movl, movq. these instruction will realise the same function, the difference is they will operate the different size data.
    movb, move byte data
    movw, move 1 word data
    movl, move double words data
    movq, move four words data
    movabsq, move absolutely four words data.

    the two operands for mov instruction, just like the source operads s and target operands d in mov s d.
    the s and d can not be both the memory addressing. it means s and d must have one is not the memory addressing.
    in other words, the two operands must have one is immediate or register addressing.

    the corresponding for the different sizes register.
    register        1 byte      2 bytes     4 bytes         the function
    %rax            %al         %ax         %eax            return value
    %rbx            %bl         %bx         %ebx            stored by the caller
    %rcx            %cl         %cx         %ecx            the fourth param
    %rdx            %dl         %dx         %edx            the third param
    %rsi            %sil         %si         %esi            the second param
    %rdi            %dil         %di         %edi            the first param
    %rbp            %bpl         %bp         %ebp            stored by the caller
    %rsp            %spl         %sp         %esp            the stack pointer
    ..........


    if you want to move from memeory addressing to memory addressing, you must use two instruction. you can do as follow.
    the register bit numbers are 32, 8 bytes
    movl $0x100, %eax   imeediate--register 4 bytes
    movw %rax, %rbx     register--register  2 bytes
    movb (%rax, %rbx), %rax memory--memory  1 bytes
    movb $-17, (%rax)   immediate--memory   1 bytes
    movq %rax, -12(%rax) register--memory   8 bytes

    b w l q. corresponding 1 2 4 8 bytes.

    there are one another clustering for mov instruction, movz and movs, the former is zero extension, the
    last is one extension, just like the arithmetic move to right and logical move to right. you will use it
    when you want to move the small source data size to big target data size. just like the follow
    movzbw s, r           move byte to word. and used zero extension.
    movzbl s, r           move byte to double words, and used zero extension.
    movzwl s, r           move word to double words, and used zero extension.
    movzbq s, r           movve byte to four words, and used zero extension.
    cltq   %eax, %rax     move four words %eax register to 8 words register %rax, and used the signed extension.
    and it is dedicated to the register %rax and %eax, it means it can just be used for them. expand four words to eight words.
    it will happend when you want mov the source data size is smaller than the target data size.
    you can use movz or movs, the last is one extension. it can also be named signed extension.
    the especial is, you should use cltq %eax %rax, it means you want to use signed extension from %eax to %rax,
    it is dedicated to the register.

    for example,
        1 instruction and operands : movabsq $0x0011223344556677, %rax
        2 description : movabsq means move 64 bits of $0x0011223344556677 to %rax
        3 result : %rax = 0011223344556677

        1 instruction and operands : movb $-1, %al
        2 description : movb means move 1 byte, 8 bits, or 2 hex of -1 to %al, the %al is the lowest 1 byte of %rax.
                        it means this instruction will change the lowest 8 bits of dec -1 to the lowest 8 bits of %rax
                        the hex show for -1 is ffffffff. so this instruction will change ff to the lowest 8 bits of %rax
                        , so the result of %rax after this instruction is 00112233445566ff, change 77 to ff.
        3 result : 00112233445566ff

        1 instruction and operands : movw $-1, %ax
        2 description : move the lowest 1 word of dec -1 to %ax, the %ax is the lowest 1 words of %rax.
                        so this instruction will change 1 word, can also be named 2 bytes or 16 bits or 4 hex to %ax.
                        so the result value of %rax after this instruction is 001122334455ffff
        3 result :  001122334455ffff

        1 instruction and operands : movl $-1, %eax
        2 description : move the lowest double words of dec -1 to the lowest double words %eax, the %eax is the lowest
                        double words of %rax. the 1 word is 2 bytes, double words are 4 bytes, 1 byte is 8 bits.
                        so the 1 word is 16 bits, double words are 32 bits, 8 hex numbers. so you will change ffffffff to
                        %eax, so the result of %rax after this instruction will be 00112233ffffffff
        3 result : 00112233ffffffff

        1 instruction and operands : movq $-1, %rax
        2 description : movq will move 64 bits, also can be named 8 bytes or four words. %rax is 64 bits
                        so the result of %rax after this instruction will be ffffffffffffffff
        3 result : ffffffffffffffff

    so you should understand the above, and you should notice the bit numbers or word number for register.
    the size of each register for x86-64 are both 64 bits, or four words, or 8 bytes.
    %rax, the register, 64 bits.  you should use movq instruction to oprate it
    %eax, the lowest double words, or 32 bits, or 4 bytes of register %rax. you should use movl instruction to oprate it.
    %ax, the lowest 1 word, or 16 bits, or 2 bytes of register %rax, you should use movw instruction to operate it.
    %al, the lowest 1 byte, or 8 bits, or 2 hex of register %rax, you should use movb instruction to operate it.

    binary, 32 bits are a unit in a 32 bits operate system. it is used in computer executive.
    dec, it is not commonly in computer.
    hex, it is commonly used in computer optput.
    1 hex number is equal to 4 bits.
    2 hex numbers is equal to 1 byte.

    32 bits can show 8 hex numbers.

    you should notice the point, movb, movw,movl, movq corresponding byte, word, double words and four words.
    it is corresponding the %al(byte), %ax(word), %eax(double words), %rax(four words) of this original register %rax.
    so if the assemble instructions is not cooresponding, just like movb $0xF, (%ebx), the immediate $0xF is four bits,
    and the %ebx is double words, so this size in it is not corresponding, so this assemble will be erro.

    then let's simulation a sample that the data transfer. we will code the data exchange function used c language and then
    code the assembly instruction for it.

    c language data transfer function as follow
    long exchange(long *xp, long y)
    {
        long x = *xp;
        *xp = y;
        return x;
    }
    then we will descripe the function used assembly

    1 long exchange(long *xp, long y) --> assembly : xp in %rdi, y in %rsi, they are all store by the function param register.

    2 long x = *xp --> assembly : movq (%rdi), %rax, you should understand that you are move long type variable from
    the variable xp to the new created variable x, the long x is stored in the register %rid, you should use the indirectly
    addressing to get the data about it, the new variable x is stored in the register %rax, so this instruction will be it.
    but you should notice that the %rdi and %rsi is dedicated to the function parmas.

    3 *xp = y --> assembly : movq %rsi, (%rdi), notice, the pointer param will be the memory addressing.
    and it will be the register addressing if the param is not the pointer param. but it is not absolutely correct.
    we can understand it used the comparison method. just like the local variable x, it is stored used register,
    and the param is also stored used register if the param is not the pointer, that means the param is not
    got from the memory, it is also mean this get meothod of this param is not the indirectly addressing, it is register addressing,
    why?because these local variable will be efficient if we stored it used register. but the reference data must used the
    indirectly addressing, beacause this data we can just get it from the memory used the indirectly addressing, just like M[R[%rdi]].
    this assembly (%rdi) is mean M[R[%rdi]], its efficient is lower than the register addressing just like %rdi.

    4 return --> assembly : ret.

    the pointer in c language is addressing in memeory in fact, it is defined during the process runing,
    and it is created in memory, the indirectly addressing means put this pointer into a register, the used it
    in memory addressing. the local variable is not created in memory, it is just define in register.

    then we will learn the for assembly casts.
    0 src_t *sp; assuming that the variable sp is stored in %rdi
    1 dest_t *dp; assuming that the variable dp is stored in %rsi
    2 *dp = (dest_t) *sp; --> assembly code, you should read the data from the memory, beacause the *sp
    is a pointer, so you should use M(R[%rsi]) to get the address of sp, and the * can get the data of this address.
    then, you should cast the data type from src_t to dest_t. and you should do a temp store used the register %rax or other.
    you can store the data after casts used %rax, you can just use the part type of the register %rax, just like %eax or %ax, %al.
    it means you should use the assembly code movq (%rdi), %rax if the data size is 64 bits or four words.
    3 then you should move %rax to (%rsi), (%rsi) means M[R[%rsi]], the indirectly memory addressing.
    just like the assembly code movq %rax, (%rsi)

    we can do some cases, the assembly code of casts from src_t to dest_t.
    just like the function
    src_t *x; the x is memory address, stored in >>>> %rd i>>>> when the process run.
    dest_t *y; the y is memory address, stored in >>>>> %rsi >>>> when the process run.
    *y = (dest_t)*x;

    the table for assembly code the c language casts code the above, the concept is you should use a temp varibale to store the data first,
    it means you should use a register to store the src_t data, and the selected about the move instruction must correct, beacuse the
    realise of casts based on it. because it can determined the move size of register. just like movb, movw, movl, movq.

    src_t               dest_t              instruction
    long                long                movq (%rdi), %rax; movq %rax, (%rsi); notice, the %rsi register is a local variable to as a temp data variable.
                                            why use a temp variable, beacuase the assembly code can not move data from memory to memory, it means you should
                                            move instruction must have a not memory addressing.
    char                int                 movl (%rdi), %eax; movl %eax, (%rsi); notice, the int is 4 bytes or 32 bits or double words, you should use the %eax
                                            to show the size of register, corresponding the instruction is movl.

    char                unsigned            just like casts from char to int, you should use the instruction that can corresponding the tranform data size. just like
                                            the dest_t data type.

    then give you the assmebly code, you give the c language code used it.
    void decodel(long *xp, ;long *yp, long *zp)

    decodel:
        movq    (%rdi), %r8
        movq    (%rsi), %rcx
        movq    (%rdx), %rax
        movq    %r8, (%rsi)
        movq    %rcx, (%rdx)
        movq    %rax, (%rdi)
        ret

    then, we will give the c language code based on it.
    the three param used the register, %rdi, %rsi, %rdx
    the param *xp is stored in %rdi, the param *yp is stored in %rsi, the param *zp is stored in %rdx.
    movq (%rdi), %r8; the (%rdi) means indirectly memory addressing, means the *xp, %r8 means the original register.
    this instruction mean move the data *xp to a local variable, and the register is 64 bits. so this register can
    also store a 64 bits data type, just like long, so this instruction has not involved the casts.

    the c language can show just like, long x = *xp;
    similarly, the second code can show used c language, long y = *yp
    the third code can show used c language, long z = *zp
    the fourth code can show used c language, *yp = x
    the fifth code can show used c language, *zp = y
    the sixth code can show used c language, *xp = z
    the seventh code can show used c language, return; because the function has no return value.
    and the special you should notice is that the move instruction is movq, the size about the movq is 64 bits, or four words.

    so the complete function can show used the c language as the follow.
    void decodel(long *xp, *yp, *zp)
    {
        long x = *xp;
        long y = *yp;
        long z = *zp;

        *yp = x;
        *zp = y;
        *xp = z;

        return;
    }

    then, we will learn the push and pop instruction. these two instructions is based on the stack dataStructure.
    the rule of stack is after the advanced. the process stack is stored into the area of memory in x86-64.
    the direction of increasing is down. so the address of the stack elements is the smallest. the register %rsp is
    dedicated to the stack, so we can name the %rsp as stack pointer. so the register %rsp is dedicated to the stack.

    notice, then we will learn the stack instruction push and pop. we can learn based on the four words, it can also be named
    as 8 bytes, or 64 bits. this is the one read size of 64 bit computers

    instruction              the efficient                              description
    pushq S                  R[%rsp] - 8 -> R[%rsp]; S -> M[R[%rsp]]     push four words to stack
    popq D                   M[R[%rsp]] -> D; R[%rsp] + 8 -> R[%rsp]     pop four words to stack

    you should understand that the address of stack top elemet is smallest.
    the push isntruction:
        you should change the address that stack pointer first, it can alse be named register %rsp,
        because the operands is pushq, it can operate four words, 64 bits. so the address can --8,
        because the unit is 1 byte. so you should code R[%rsp] --8; then the register %rsp address is
        the address of stack top elment. so you can move the data S to memory address that register %rsp stored
        , you should use the indirectly memory addressing, just like movq S, (%rsp). it is the stack top elemnt.

    the pop isntruction:
        you should store the data of stack register %rsp, it can show by assembly code, M[R[%rsp]] -> D; move the data
        of %rsp to a temp data just like D, then you should change the address about stack register %rsp. you should code
        usd R[%rsp] ++8; beacause the stack address will ++ if you used the pop. beacause the stack top elment is the smallest address.

    because the push and pop will use the move instruction, so the push and pop is equal to the code as follow.
    pushq %rbp   >>> it means push data %rbp into stack.
    it is equal to the code as follow.
    subq $8, %rsp   you should change the address about the %rsp, %rsp--8, the instruction sub means --.
    movq %rbp, (%rsp)  notice, the %rbp is register addressing, and the %rsp is dedicated to stack, and it is created on
    the memory, beacause it has the address, so you should use the indirectly memory addressing.

    you should understand the special for %rsp, it is dedicated to storing the stack element address. so it is
    the address for the stack top elemnt, and the other register stored the stack data, the stack stored the address.
    it means the process stack also stored the address. what we want to emphasis on here is the %rsp stored the stack top address,
    and the other register also stored the address, but it has nothing to do with stack. notice, the process stack stored the address also.

    and the popq %rax is equal to the follow code, move the data from stack pointer, you should use the indirectly
    memory addressing to get the data that %rsp corresponding, and you should move the data to the register. it means a
    temp varaible, because it is nothing do with the memory address.
    movq (%rsp), %rax
    addq $8, %rsp

    just like the pop and push instruction,
    the push instruction
        you should sub the %rsp first, and the to store the data to the register
    the pop instruction
        you should get the data used indirectly memory addressing, and then add the %rsp second.
    we can understand based on the follow

    original stack   >>>    pushq %rax    >>>   popq %rdx
    %rax 0x123              %rax 0x123          %rax 0x123
    %rdx 0                  %rdx 0              %rdx 0x123
    %rsp 0x108              %rsp 0x100          %rsp 0x108

    this register %rsp is stack pointer, it stored the stack top element address.
    notice, you can acess any position in stack used the standard memory addressing method, because the stack
    , process code and other process data are in the same memory. just like, you can use the instruction
    movq 8(%rsp), %rdx to copy the second fourwords from stack to register %rdx, so you need not to used the strict
    instruction push or pop to get the stack data. you can use the address to access any address for the stack.
    this 8 is immediate at here, it means the data size stored in stack.8 means 8 byte, the stack pointer unit is byte,
    %rsp+1 means this pointer add one byte, then +8 means the address add 64 bits, or 8 byte, or 4 words. because 1 word
    is equal to 2 bytes.

    we have learned the instruction about mov, push, pop, add, sub.
    the next we will learn the arithmetic and logical operator in assembly code.
    add, involved addb, addw, addl, addq, corresponding to add byte, add word, add double words, add four words.

    instruction             effect             description
    leapq S, D              &S -> D             load the effectively address, copy the address of S to D

    INC D                   D+1 -> D            D increase 1
    DEC D                   D-1 -> D            D decline 1
    NEG D                   -D -> D             take the negative
    NOT D                   ~D -> D             the not D
    ADD S, D                D+S -> D            it is equal to D = D + S in c language
    SUB S, D                D-S -> D            it is equal to D = D - S
    IMUL S, D               D*S -> D            it is equal to D = D*S
    XOR S, D                D^S -> D            exclusive or
    OR  S, D                D|S -> D            or
    AND S, D                D&S -> D            and
    SAL k, D                D<<k -> D           left move k bits
    SHL k, D                D<<k -> D           left move k bits, it is equal to the SAL instruction
    SAR k, D                D>>k_A -> D         arithmetic move to right, it means used 0 to fill.
    SHR k, D                D>>k_L -> D         logical move to right, it menas used 1 to fill.

    so, we have learned all the logical and arithmetic operator, just like, INC, DEC, NEG, NOT, ADD, SUB, IMUL
    XOR, OR, AND, SAL, SHL, SAR, SHR and so on.

    // ---------------------------test the signed ~---------------------------------------
    printf("%d\n", ~10); // echo -11
    10 :0000 0000 0000 0000  0000 0000 0000 1010
    ~10 : 1111 1111 1111 1111 1111 1111 1111 0101
    -1 : 1111 1111 1111 1111 1111 1111 1111 1111
    the binary show, binary(-1) = binary(~10) + index(3) + index(1)
    the dec show, -1 = dec(~10) + 8 + 2 ==> dec(~10) = -1 - 8 - 2 = -11
    so we can conclude that the signal ~ is get the not bit. not the completment
    the complement is equal to not first and add 1 bit second.
    // ------------------------------------------------------------------------------------

    1 the leaq instruction
    the leaq is another kind of form for movq, the difference between them is the dest must be a register.
    , another difference is the leaq instruction is dedicated to the read data from memory and load it to one register.
    just like, leaq 7(%rdx, %rdx, 4), %rax, this instruction means %rax = 7+x+4x = 5x+7 if the data of %rdx is x.

    then we can give the case about leaq instruction.
    long scale(long x, long y, long z)
    {
        long t = x + 4 * y + 12 * z;
        return t;
    }

    this c language code is a calculate for long data type, x, y, and z. it will return the value.
    then we can list the assembly code, just like x in %rdi, y in %rsi, z in %rdx
    scale:
        leaq (%rdi, %rsi, 4), %rax; //first, you should use the leaq to calculate the x+4y, and stored it in a local variable, just is a register.
        leaq (%rdx, %rdx, 2), %rdx; // it means %rdx = z + 2z = 3z;
        leaq (%rax, %rdx, 4), %rax; // it means %rax = x+4y+12z;
        ret; // return the %rax, it means return x+4y+12z;

    so the leaq can calculate the add and limited multiplication, the compiler used it to instead the add and multiplication.
    assume that %rax is equal to x, %rcx is equal to y. do some test as the follow.

    instruction             expression
    leaq 6(%rax), %rdx       %rdx = 6+x
    leaq (%rax, %rcx), %rdx  %rdx = x+y
    leaq (%rax, %rcx, 4), %rdx  %rdx = x+4y
    leaq 7(%rax, %rax, 8), %rdx  %rdx = 15x
    leaq 0xa(, %rcx, 4), %rdx  %rdx = 0xa+4x
    leaq 9(%rax, %rcx, 2), %rdx  %rdx = 9+x+2y


    then we will learn the operands about unary and bianry.
    the unary and binary is based on the assembly instructions. just like INC D, it is a unary operand.
    ADD S, D, it is a bianry operand.
    incq(%rsp)  this instruction will make the stack top 8 bytes element add 1.
    this is equal to the ++ -- operation in c language.

    the binary operand, the second operand is both the source and target, just like the assignment operation in c language.
    += -=; x -= y; the first operand can be immediate, register and memory addressing. the second operand can be register or memory addressing.
    it means the second operand in bianry operand must be an container, it must could store the data, and only the register
    and memory can store the data in assembly code. and the cpu must read from the memory and calculate it, and then 
    write the result value to the memory.
    then we can do a test.

    address    value                    register        value
    0x100      0xff                     %rax            0x100
    0x108      0xab                     %rcx            0x1
    0x110      0x13                     %rdx            0x3
    0x118      0x11

    the left table is the address in memory and the corresponding value.
    the right table is the regsiter and the value in it. the register is the special container, it also has the address.
    you will need to give the result based on the instruction as follow.
    instruction               the target operand                            result
    addq %rcx, (%rax)         the indirectly memory addressing (%rax)       movq (%rax), %rbx; leaq %rcx, %rbx; movq %rbx, (%rax) , you should read it and calculate, then write it in memory.
    subq %rdx, 8(%rax)        the indirectly memory addressing 8(%rax)      

    then you should understand the assembly code about the displacement operate. because the multiplication and
    division calculate will be converd to it used assembly code. just like you want to calculate the 10 / 2
    the assembly will be SAR 1, %rax, it means right move %rax 1 bit. this register %rax stored the data what you want to calculate 10.
    1010 >> 1 = 0101 = 5. this assembly code will be SAL 1, %rax if you want to calculate 10 * 2. it means left move
    %rax 1 bit. 1010 << 1 = 10100 = 20. you should notice, this right move will consider the 1 fill if you want to calculate
    negative number. the SAL or SAR is always more efficient than IMUL, notice, the assembly has not the divide operate.

    then we will learn the more details about each assembly instruction. just like the IMUL instruction involved 
    imulq and mulq. these instructions can calculate the eight words or 16 bytes, or 128 bits. we can also name it
    as the special arithmetic operate. it can store the 128 bits number in fact, and the concept about it is append.
    the original multiplication will be truncated if the overflow happend, notice, two unsigned int multiplication, and two int
    multiplication will be same structure bits if the overflow happend, because of the exists about truncate. the highest bit will
    be truncated if the overflow happend, so the int and unsigned wii be same.

    just like imul, imulq and mulq. mulq is unsigned multiplication, imulq is signed multiplication. these two instruction all can
    get the result about 128 bits numbers. what you should notice is these two instruction all required a number must strore in
    register %rax, the other number is source operand for instruction, the result stored in register %rdx(high 64 bits) and %rax(low 64 bits)

    imulq   S       S * R[%rax] --> R[%rdx]:R[%rax]    signed multiplication, one operand must be provided by %rax. and the S must be given.
    mulq    S       S * R[%rax] --> R[%rdx]:R[%rax]     unsigned multiplication, the low 64 bits of result stored in %rax, the high 64 bits of result stored in %rdx.
    it means, if you want to calculate two int, you just need to give one number, the other number is fixed stored in %rax. so the assembly can just give one
    operands, but the imulq instruction can also calculate two operands. only the assembly instruction imulq can also calculate used one operand, but the
    mulq can just calculate used one operand. this instruction imul must give two operands.
    imul S, D
    */

    /*
    // define the unsigned __int128 type used uint128_t, this data type size is 16 bytes, 128 bits, 8 words.
    typedef unsigned __int128 uint128_t;
    void store_uprod(uint128_t *dest, uint64_t x, uint64_t y)
    {
        *dest = x * (uint128_t)y;
    }

    then we can code the assembly instruction used the c language above.
    void store_uprod(uint128_t *dest, uint64_t x, uint64_t y)
    dest in %rdi, x in %rsi, y in %rdx, notice, these register are all dedicated to the param about function.
    store_uprod:
        movq %rsi %rax   you should move one number you want to calculate to %rax, what is the register dedicated to the mulq
        mulq %rdx       then you can code  the instruction mulq, notice, you can give one oprand because we have move one number to the register %rax
                        this result will save in %rdx(high 64 bits) : %rax(low 64 bits).
        movq %rax, (%rdi) then you can store these two register respectively. just like you can store the 
                            low 64 bits used (%rdi), it is indirectly memory addressing about dest variable.
                            this variable is 128 bits, and the %rax is 64 bits, so you can store from the lowest bit to 64th bit.
        movq %rdx, 8(%rdi)  then you can store the high 64 bits %tdx used the 8(%rdi), this is also indirectly memory addressing
                            it means the dest variable from 65th bit to 128th bit. this unit is byte at here. the immediate is 8.
        ret                 return the result
    then you have stored the result value used dest, the 128 bits variable. notice, the dest is 128 bits, but the %rdi is 64 bits.
    the memory is independent with variable or register, this dest variable means this 128 bits in memory represent it, and
    the register %rdi is fixed 64 bits, you can just move data used it.

    you should notice the dedicated register %rax for mulq and imulq or idivq and divq at here.
    */

    /*
    then, we will learn add control to assembly code, it means the instructions will not run sequential. just like
    if, continue, switch and so on. machine code provide two basic low-level machanisms to realize it. test the data, and
    then change the control flow and data flow according to the test result.

    you can use the instruction jump to change the order that instruction run.
    excepy integer register, the cpu is also own a group of condition code registers. these register show
    the recent arithmetic or logical operate attribute. you can use it to check the register in order to you
    can call the condition instruction. it means you can use these condition code registers to chech the condition
    , it will implementation the conditional branch function.

    CF carry flag, it means the highest bit produced carry. you can use it to check if the unsigned overflow happend.
    ZF zero flag, it can check if the recent result is zero.
    SF signed flag, it can check if the recent result is negative.
    OF overflow flag, the recent operate result to a signed overflow. it is difference from CF, the former can check
    signed overflow, the second can check unsigned overflow.
    notice, CF means carry flag, ZF means zero flag, SF means signed flag, OF means overflow flag.
    the first can chech if carry flag happend in unsigned.
    the second flag can check if the recent result is zero happend.
    the third flag can check if the recent result is negative.
    the fourth flag can check if the signed overflow happend, it involved opposite overflow and negative overflow.

    leaq instruction can not change any condition code, because it is used to calculate address.
    all the instruction above can set the condition code. just like XOR, it will set CF and OF to 0.
    for mov bit operate, CF will be set as the lastest bit. and the OF will be set to 0.
    INC and DEC instruction will set OF and ZF, but it will not change CF.
    CMP and TEST instruction can also set the condition code. it means they will only set condition code, will not
    modified any registers value. so the difference between these instruction and original instruction is
    the former can only set the condition code and can not change the value of registers. and the former can change the
    register value. just like the CMP and SUB.
    the method for using TEST is, you can use like the code above.
    testq %rax, %rax    %rax & %rax     you can test %rax is negative, opposite or zero.
    testq %rax, %rbx    %rax & %rbx     the second register rbx is a mask, you can filter some bit should be tested.


    then how to access condition code?
    usually, you can not read it directly. you can use three method to access the condition code.
    1 you can set one byte as 0, 1 or 2 based the combine of some condition code.
    2 jump to one position based on the condition.
    3 transmit data conditional.

    the first situation
        it is named set instruction.
            setl, set when less than
            setb, set when below than

        just like the case as follow

        int comp(data_t a, data_t b)
        a in %rdi, b in %rsi

        comp:
            cmpq %rsi, %rdi         compare a:b, notice the param order.
            setl %al                set the register %al as to 0 or 1. the size of %al is 1 byte, 8 bits.
            movzbl %al, %eax        the insturction movzbl means expand %al to double words used 0 and
                                    then move it to the double words register %eax.
            ret                     return.

        notice, movzbl will clear the highest 3 bytes of the register %eax. and will clear the highest 4
        bytes of the register %rax. it means you will get the register %rax, the lowest 1 byte is 1 or 0, and
        the other bits will all be 0. this is the function of movzbl instruction.

        you should notice, int is 4 bytes, 32 bits, double words, so you should store the compare result used int size.
        and setl %al instruction means you will store the compare result 0 or 1 used the 1 byte register %al.
        %al, %eax is all the different size type of register %rax.

        you should notice.
        setl is sigend less, signed <
        setle is signed less equal, signed <=
        setg is signed greater, signed >
        setge is signed greater and equal, signed >=

        seta is unsigned greater, unsigned >
        setae is unsigned greater equal, unsigned >=
        setb is unsigned below, unsigned <
        setbe is unsigned below euqal, unsigned <=

        sete is equal. equal or zero. =/0
        setne is not equal, or not zero. ~=/~0

        sets is negative
        setns is not negative.

        these instruction will set one byte to 0 or zero above. it usually used register to store it,
        1 byte register is %al. double words is %eax. four words is %rax.

        it will be very important that distinguished signed and unsigned in machine code. because it will not
        connect every process value with data type, and the machine code will usually use the same instruction
        to handle the signed and unsigned number, it is because of the same bits operate for all arithmetic calculate.

    then,we will learn the jump instruction.
    jump instruction will lead to the runing process switch to
    a new location. the jump destination that process will jump to
    is usually indicated a label. just like the follow.
    movq $0, %rax       set %rax to 0
    jmp .L1             Goto L1
    movq(%rax), %rdx
  .L1:
    popq %rdx           this code is the destination will jump to.
                        this code means the process will skip to movq(%rax), %rdx
                        it mean this code will not be performed.


    skip while, switch, and so on condition keywords,
    , stack and recursive to pointer arithmetic.
    177 page.
    we will learn some about pointer arithmetic. c language
    can do the pointer arithmetic. just like p+i.

    a[2] == *(a+3))
    the cast is better than operator.
    function pointer.
        int (*f)(int *);
        f is a function pointer, the param is int *.
        the return value is int type.

        int *f(int *); it will be a function, that param is int *
        and return value is int *.
    notice, c language will not check the legitimacy about the reference boundary for an array.
    if you do an array reference that cross the boundary, you will get an error number.
    more serious, you will destroy the stack data structure.
    because the variable will be created in stack when process running, and you do some array
    reference in stack during process running.

    buffer overflow. a common form about array reference boundary.
    you defined an address to store a string, but the size of address is
    less than the content you want to store. just like the function as follow.

    attack about buffer overflow.
    in order to attack, they usually insert attack code and 
    insert the pointer that pointing to the attack code. so this 
    pointer is also one part for the attack code. but if they want to
    define this pointer that pointing to the code, they should know the stack
    address that the code in stack. in past, the code in stack is fix, so they
    can get it easily. and the same process run in each computer, and the stack 
    address is fix for this process, just like a server process, it own a fix stack
    address in each computer, so attacker can design a process to attack each computer.
    this can be named security monoculture. the random stack thought can solve this problem
    , it makes the different stack address that same server process run in different computer.
    so it means, the same code run in different compueter, the stack address will be difference 
    for each computer. you can use a method to show the different address that 
    same code run in one computer. just like the code as follow.

    skip to chapter5.
    */
    // echo();
    // echo_test();

    // you can run this code as follow many times, you will
    // find that each run will be get the different stack address.
    long local;
    printf("%p\n", &local);
    return 0;
}
