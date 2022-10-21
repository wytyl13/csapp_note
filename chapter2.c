/**********************************************************************
 * Copyright (C) 2022. IEucd Inc. All rights reserved.
 * @Author: weiyutao
 * @Date: 2022-10-18 16:30:57
 * @Last Modified by: weiyutao
 * @Last Modified time: 2022-10-18 16:30:57
 * @Description: this file involved the integer calculate using bit operation, 
 * the integer multiplication, add, minimum, divide, and so on.
***********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>

/**
 * @Author: weiyutao
 * @Date: 2022-10-13 20:16:41
 * @Parameters: int1, int2
 * @Return: int value
 * @Description: use the bit operation to define the add minimum. ^ & will be used.
 * 1^1=0 0^0=0 1^0=1 1&1=1 1&0=0 0&0=0
 * add(1001, 1001)
 * 1 1001 ^ 1001 = 0000
 * 2 1001 & 1001 = 1001
 * 3 2.value<<1 = 10010
 * 4 1.value ^ 3.value = 0000 ^ 10010 = 10010
 * 5 (1.value & 3.value)<<1 = (0000 & 10010)<<1 = 000000
 * 6 5.value == 0;return 10010;
 * 7 so the result is 10010 = 16+2 = 18,
 * notice, the concept of above is ^ will sum, just like 1^0=1 1^1=0 0^0=0, and the
 * & will upper, just like 1&0=0, 1&1=1.0&0=0, if 1&1, then you should <<1 can only be
 * efficiently.
 * add(1001, 1001)
 * 1001 ^ 1001 = 0000, this will show summarize, but less step shift, just like we should
 * do the shift operation after add the zero index bit and three index bit. then you should
 * do the (1001 & 1001)<<1 = 10010, util here we have not finished, we should do the second
 * operation, 0000 ^ 10010 = 10010, if(!(0000 & 10010)<<1), return 10010, else recycle.
 */
int add(int a, int b) 
{
    if (b == 0)
        return a;
    int c = a ^ b;
    int d = (a & b) << 1;
    return add(c, d);
}

/**
 * @Author: weiyutao
 * @Date: 2022-10-13 21:26:49
 * @Parameters: 
 * @Return: 
 * @Description: the reduction method is simple, you should get the not of x, and do the add second.
 * just like a - b, you can do a + (-b), the main problem is defined the method of not function
 * you have two method to define the not int. the first is -x = 2^32-x, the second is -x = add(~x, 1);not bit and add 1.
 */
int negative1(int x) 
{
    return (int)(long)pow(2, 32) - x;
}

int negative2(int x) 
{
    return add(~x, 1);
}

int reduction(int a, int b) 
{
    return add(a, negative2(b));
}

//get sign from a int number, notice, if you want use the >>, you should notice the difference between
//int and unsigned, the default >> is arithmetic for negative int, logical for opposite int, the default >> is 
//logical for unsigned. so we cant use >> to get sign, because the default is arithmetic for negative int.
//we can use & operation, because the pass data type is int, it is fixed. we can use x & 0x80000000.
//it is x & 1000 0000 0000 0000 0000 0000 0000 0000, we want to get the highest bit value is itself, and the other bit
//is zero. the binary show is very complex, we can use hex to instead. the hex is given by each 4 bit. so we can get the hex
//is 0x80000000. when we get the result, we can conclude if base on whether it is equal to zero, if it is, it is opposite, else it is negative.
//notice:the highest bit is signed bit for int.

//you could also use >>, even if it is arithmetic for negative int, because you can make a judge, if it is a negative int, 
//you can get the 0xffffffff = -1, else you can get 0x00000000 = 0 
int getSign1(int x) 
{
    int y = x & 0x80000000;
    if (y == 0)
        return 1;
    return -1;
}

//return value: negative int return -1, opposite int return 0
int getSign2(int x) 
{
    return x >> 31;
}

//get the opposite of a int number
int beOpposite(int x) 
{
    if (getSign1(x) == -1)
        return negative2(x);
    return x;
}

/**
 * @Author: weiyutao
 * @Date: 2022-10-13 19:02:22
 * @Parameters: integer1, integer2
 * @Return: the integer result
 * @Description: define the function to get the result for two integer multiplication
 * notice:this function can not handle the overflow
 * if multiplication x and y, x is negative and opposite all can be, but consider the y is negative.
 * 10 * -10
 * 10110 the 1, 2, 4 index bit value is 1
 * 10<<1 + 10 <<2 + 10<<4 = 10100 + 101000 + 10100000 = 10100000 + 111100 = 11011100
 * =-2^7+2^6+2^4+2^3+2^2 = -128+64+16+8+4=-36
 * the error above we can consider, because if the opposite integer result is correct, the
 * negative integer result must be error. because the highest signed bit is 1, but the opposite
 * integer is 0. but why the result of the function is correct? this concept we do not consider,
 * the rigorous logic structure is what we need to do. so we need to do judge first. judge whether the
 * integer is negative.
 * notice : this function can calculate two any number multiplication, it can be an odd, even, negative, 
 * opposite etc.. so the multication function is generally and we can use the << to handle all multiplication
 * problem. so you can use it to calculate 10 * 2, 10 * -2, -10 * 2, -10 * -2, 10 * 3, 10 * -3, -10 * 3, -10 * -3.
 * it means, you can calculate any multiplication used this function.
 */
int get_multiplication(int x, int y) 
{
    //1101 13 = 2^3+2^1+2^0
    //10000 16 = 2^4
    //know a number, we can get the power of 2 for it.
    //10 * 10 = 10 * (2^3+2^1) = 10<<3 + 10<<1;
    //1010 << 1 = 10100 = 20
    //1010 << 3 = 1010000 = 64+16=80
    //20+80=100

    //this code can cancle, but logical need it.
    int x_opposite = beOpposite(x);
    int y_opposite = beOpposite(y);
    //----------------this code can cancle above-------------------------------------

    int i, z = 0;
    for (i = 0; i < (sizeof(int) * 8); i++)
    {
        if ((y_opposite >> i) & 0x01)
        {
            x_opposite <<= i;
        }
        else
        {
            continue;
        }
        z = add(z, x_opposite);
        x_opposite >>= i;
    }
    if (((getSign2(x) == 0) && (getSign2(y) == 0)) || ((getSign2(x) == -1) && (getSign2(y) == -1)))
        return z;
    return negative1(z);
}

//you can also this fucntion that get multiplication
//we have show the why it can do, the code above can be cancled is because the 2^w-x and displacement operation worked.
int get_multiplication_simple(int x, int y) 
{
    int i, z = 0;
    for (i = 0; i < (sizeof(int) * 8); i++)
    {
        if ((y >> i) & 0x01)
        {
            x <<= i;
        }
        else
        {
            continue;
        }
        z = add(z, x);
        x >>= i;
    }
    return z;
}

/**
 * @Author: weiyutao
 * @Date: 2022-10-18 15:46:37
 * @Parameters: the first param is an any number, it can be opposite, negative, odd, even. the
 * second number can just be an even number, and it can not be negative. if it is negative, you only need to
 * add the negative symbol after calculate. so our function can be this, the first param can be any number, 
 * and the opposite of the second param must be an even. so you can calculate 10 / 2, 10 / -2, -10 / 2, -10 / -2; 
 * @Return: 
 * @Description: this function can calculate an any number divide an even number. do not calculate the divide
 * is an odd number. this is different from multiplication. this is different from multiplication, we should
 * consider the condition that the the divide is negative. but the multiplication need not to consider, so 
 * we should define our logical, not only multiplication but also the divide, we should consider condition that 
 * the second number is negative. so we should do a judge whether the second number is a negative at the start.
 */
int get_divide(int x, int y) 
{
    if (y == 0)
    {
        perror("the logical error\n");
        exit(1);
    }
    // when we started, we should be opposite all number right now.
    int x_opposite = beOpposite(x);
    int y_opposite = beOpposite(y);

    int i;
    // 1 = 0001 = 2^0, 2 = 0010 = 2^1; so we can get the power is the bit index of the bit value is 1.
    // 1010 / 1 = 1010 / 2^0 = 1010 >> 0 = 1010 = 10
    // and because the second param must be an even, so we can break the loop for bits once we found
    // one bit value is one. so it means we should return once the if condition is true.
    for (i = 0; i < (sizeof(int) * 8); i++)
    {
        if ((y_opposite >> i) & 0x01)
        {
            x_opposite >>= i;
            break;
        }
    }

    // then we should consider the signed before we return the result.
    // if have two negative or zero negative among the two number, we should return x_opposite, 
    // else return -x_opposite.
    if (((getSign2(x) == 0) && (getSign2(y) == 0)) || ((getSign2(x) == -1) && (getSign2(y) == -1)))
        return x_opposite;
    return negative1(x_opposite);
}



int main(int argc, char const *argv[])
{
    //integer multiplication need to more than ten clock cycle, but add, sub, bit operation need only one
    //clock cycle, so we use the add and displacement operation to instead the integer multiplication. 
    //1 consider the multiplication a power of 2 first.
        //the unsigned integer x * 2^k (0 <= k < w, w=32), x << k === x * 2^k
        //10 * 2 = 1010 << 1 = 10100 = 16+4=20, the premise condition is not the overflow after the replacement operation.
        //the signed integer x * 2^k
        //-10 * 2 = 10110 << 1 = 101100 = -32+8+4=-20;

    //2 we have learned how to use bit displacement operation to calculate the multiplication about a integer and a power of 2.
    //then if you have a number that is not a power of 2. just like 11, 11 = 2^3 + 2^1 + 2^0.
    //then you can calculate the integer x<<3 + x<<1 + x<<0; it is used the add and replacement operation to
    //instead of the multiplication.
        //10 * 11 = 10 * (2^3 + 2^1 + 2^0) = 10<<3 + 10<<1 + 10<<0 = 1010000 + 10100 + 1010 = 
        //1010000 + 
        //  11110 = 
        //110 1110 =  64+32+8+4+2=110
        //the similar, you can use 11 = 2^4-2^2-2^0, then use the minus.
        //notice, the above operation are made of a comiler in the background.
    //until here, we can make a conclusion.
    //x truncate from w bit to k bit. the corresponding dec number is the number of w bit minus 2^k
    //x multiplication 2^k, the result is equal to x<<k. or x<<k1 + x<<k2 + ... + x<<kn.
    //the expand or truncate bit. signed use 1 to fill the expand highest bit. unsigned use 0.
    //expand will not change a number, but truncate can change a number.
    //unsigned 15 : 1111, 4 bit expand to 5 bit, 01111 is equal to 1111
    //signed -15 : 10001= -16+1=-15, 4 bit expand to 5 bit, 110001 = -32+16+1=-15 is equal to 10001.
    //the reduce is similar to expand.
    //if the operation result overfolw, the result = real result - 2^w, just like you use a int to store the result,
    //if overflow, the result of 2147483647+1 = 2147483648-2^32
    //11111111111111111111111111111111 + 1 = 1 00000000000000000000000000000000 = 0, because you use the int to store the number,
    //so the highest bit 1 is overflow.

    //the not of unsigned x. if x=0, int -x = x, else int -x = 2^w-x;
    //x : 1111 15, int -x = 2^32-15=4294967281 = 11111111111111111111111111110001 = 
    //int 10000000000000000000000000000000 + int 0111 1111 1111 1111 1111 1111 1111 0001 = 
    //-2647483648+2147483633=-15;
    //notice, you should cast the type to int first, just like you want to get the negative int from opposite int,
    //you should calculate the 2^32 first, and the result is unsigned long, you should cast it to long first, and then
    //cast it from long to int, then you can calculate the int 2^32 - int x. the result is the negative int.
    //if you want get negative int from unsigned, you should cast the unsigned x to int x, then you can calculate the int 2^32 - int x;


    //unsigned range is from 0 to 4294967295, 2^w-1;
    //int range is from -2147483648 to 2147483647, -2^(w-1) to 2^(w-1)-1;
    //if overflow happend for two unsigned added.
        //it must the opposite overflow. the result = the real result - 2^w, w = 32 if the type is int.
    //if overflow happend for two int added.
        //the opposite overflow : the result = the real result - 2^w
        //the negative overflow : the result = the real result + 2^w

    //the bit numbers, you should use w+1 bits to store two w bit data type added, and used
    //the 2w bits to store two w bit data type multiplication.
    //two integer multiplication, the unsigned or signed, the bit show of real result is different, 
    //but the result after truncate is similar.
    //unsigned 111 * unsigned 101 = 7 * 5 = 35 : 10 0011, the truncate is 011;
    //int 111 * unsigned 101 = -1 * 5 = -5 : 1011, the truncate is 011;
    //so the 3 bit show of result is 3, because the truncate happend.

    //the replacement operation of arithmetic right move, used one to fill the expand in c. if expand for int. the java is >>, is default in c for expand for signed.
    //the replacement operation of logical right move, used zero to fill the expand for unsigned in c. the java is >>>
    //notice, the left move use zero fill for all condition.

    //the multiplication for two integer we used left move, the left move will fill the expand
    //bit used zero. the right move for signed can only use the one to fill expand bit.

    //we can choose the minimum amount of calculation, just like x * 31
    //you can use 31 = 2^4+2^3+2^2+2^1+2^0 = x<<4 + x<<3 + x<<2 + x<<1 + x<<0, you will use 4 times replacement operation and 4 times add.
    //you can alse use 31 = 2^5-2^0 = x<<5 - x<<0, you just only need to use one times replacement operaytion and one minimum
    //so we should choose the second method base on the efficiency of calculating.

    //if you want to swap x and y, you should do this as follow, because x ^ x ^ y = y.
    //y = x ^ y;
    //x = x ^ y; means x=y
    //y = x ^ y; means y=x


    //the integer division, it is more slowly than the multiplication.
    //you will use the right move for a integer division a power of 2. just like x / 2^k
    // printf("%d\n", get_multiplication(10, 10));
    // printf("%d\n", add(10, 10));
    // printf("%d\n", negative1(10));
    // printf("%d\n", negative2(10));
    // printf("%d\n", reduction(10, -10));
    // printf("%s\n", getSign1(10) == 1 ? "opposite" : "negative");
    // printf("%s\n", getSign2(-10) == 0 ? "opposite" : "negative");
    // printf("%d\n", beOpposite(-10));
    // printf("%d\n", get_multiplication_simple(10, -10));


    //then we can think about the divide. just like the multiplication, the divide is >>
    // just like you want to calculate unsigned or int 10 / 2;
    // 10 / 2^1 = 10 >> 1 = 1010 >> 1 = 0101 = 5;
    // int -10 / 2 = 1111 1111 1111 1111 1111 1111 1111 0110 >> 1 = 1111 1111 1111 1111 1111 1111 1111 1011 = -1-4=-5;
    // but if you want to calculate an odd number, you can give an another method, you can not use this method directly. 
    // what method we should give? wait a moment, we should consider if this method we have defined can 
    // handle an odd divide a power of 2. so it mean the result for dividing have remainder
    // just like 9 / 2 = 4.5;
    // 1001 >> 1 = 0100 = 4;
    // so this method we have define is take down the whole.
    // printf("%d\n", get_divide(10, -2));// goto the row number 187.


    // but the difference between divide and multiplication is the former need different method to handle
    // divede the power of 2 and divide the not power of 2. and the last only need one method to handle this.
    // so it means, we need a extra metho to calculate the problem, a number divide an odd number.
    // so we have handle a number divide an even number, now we can consider divide an odd number.
    // notice, the method we defined above are all rounding,即计算结果都是向下取整
    // until here, we have learned all calculate about integer, so the next we will learn the calculate about float.

    // we should define it in another file.


    return 0;
}
