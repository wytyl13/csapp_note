/**********************************************************************
 * Copyright (C) 2022. IEucd Inc. All rights reserved.
 * @Author: weiyutao
 * @Date: 2022-11-28 14:12:51
 * @Last Modified by: weiyutao
 * @Last Modified time: 2022-11-28 14:12:51
 * @Description: page376.we will learn how to optimize the performance of process
 * you can choose three main method to optimize your peocess.
 * 1 choose the appropriate datastructure and agrithmetic.
 * 2 the source code should appropriate the compiler. it means you should know the feature for compiler, or you will not code the appropriate source code.
 * 3 you should synchronous your code with system concept, just like you shoud know some knowledge about multithreading and parallel.
 * the last method suitable for large amount of calculation.
 * 
 * then we will learn how to realize the process optimize.
 * 1 first step is, dropped some unnecessary work. this is unrelated with compiler.
 * 2 second step, use the instruction-level parralelism abiliy that cpu provided.
 * it means, you can execute multiple instructions in the same time. it will be the most complex,
 * because you will try to reduce the correlation among the data in a process. this should show in your c language code.
 * 
 * then, we can get the meaning that we learned compiler and c language.
 * why we have learned compiler instruction, but we have not used it to optimize the process?
 * because we can get more portability used c language to optimize the process than using compiler.
 * just like the param that when you used gcc, -Og means the basic optimize.
 * -Ol, -O2, -O3 means the more and amount optimization. this can control gcc to
 * use the better method to optimize the process, the process will get different performance.
 * 
 * compiler must consider the most safety for you process, so it means
 * you should spend more effort on the more efficient machine code. just like the code as follow.
 * test1 and test2 function
 * 
***********************************************************************/
#include <stdio.h>
#include <stdlib.h>



// you can consider these two function.
// test1 will execute 6 times memery access. and test2 will execute 3 times memory access.
// just like test1, first line code, you should access memory xp twice, yp one time.
// read xp, read yp, and sub xp, yp, and mov %rax to xp. three times access memory.
// the step is read, sub and write.
// but for test2 function. read xp, read yp and write xp. three times memory access.
// obviously, test2 is more efficient. but consider the special condition, when xp address 
// is equal to yp, the test1 funciton result will be four time of xp, and the test2 function
// will be three times of xp. so the result will be different if the compiler used the more efficient 
// optimize, the compiler will consider the special condition, and choose the test1 function ranther than 
// the more efficient function test2. because it is not safety.
void test1(long *xp, long *yp) 
{
    *xp += *yp;
    *xp += *yp;
}

void test2(long *xp, long *yp) 
{
    *xp += 2* *yp;
}

// two pointer pointing to the same address,  we named this condition memory aliasing.
// compiler must ammusing that the different pointer can point to the same address.
// util here, the underlying code optimization ablity is beyond the code designed ability.
// so we will learn the ability about the code design and application first.
// then, we will return here and go on this part learning. 

int main(int argc, const char *argv[]) 
{

    printf("i am here\n");
    return 0;
}