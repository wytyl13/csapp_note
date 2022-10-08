#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

typedef unsigned char *byte_pointer;

//define the buf
#define KSIZE 1024
char kbuf[KSIZE];
char dbuf[KSIZE];


void show_bytes(byte_pointer start, size_t len) 
{
    size_t i;
    for (i = 0; i < len; i++)
        //use at least two hexadecimal character to show each bit for one pointer of byter_pointer type
        //the start mean a pointer of byte_pointer type
        //if you pass a int type, the sizeof int is 32, so the i will be 0 to 31, loop for all start by bit.
        printf("%.2x", start[i]);
    printf("\n");
}

void show_int(int x) 
{
    show_bytes((byte_pointer)&x, sizeof(int));
}

void show_float(float x) 
{
    show_bytes((byte_pointer)&x, sizeof(x));
}

//the void * can represent all pointer type, for example, pointer of any type(int *), pointer of pointer of
//any type(int **)
void show_pointer(void *x) 
{
    //the param pass a pointer pointing to a pointer.
    //casting does not change the real pointer, just tell the compiler to view  the data that pointing to
    //as a new data type.
    show_bytes((byte_pointer)x, sizeof(x));
}

void test_show_bytes(int val) 
{
    int ival = val;
    float fval = (float)val;
    int *pval = &val;
    show_int(ival);
    show_float(fval);
    show_pointer(pval);
}

/**
 * @Author: weiyutao
 * @Date: 2022-10-05 19:30:17
 * @Parameters: 
 * @Return: 
 * @Description: this function show a swap between two int, the special in it is 
 * it need not use a temp variable to store. we used bit operation in it. 
 * use the theory x ^ y ^ x = y;
 */
void inplace_swap(int *x, int *y) 
{
    *y = *x ^ *y;
    *x = *x ^ *y;//x = x ^ x ^ y = y -> x = y
    *y = *x ^ *y;//y = y ^ x ^ y = x -> y = x

}

void reverse_array(int a[], int cnt) 
{
    int first, last;
    for (first = 0, last = cnt - 1; first < (cnt / 2); first++, last--)
        inplace_swap(&a[first], &a[last]);
}

//the logical
int logical(int x, int y) 
{
    return x && y;
}

//the second param pass the length for your array.
float sum_array(float a[], unsigned length) 
{
    int i;
    float result = 0;
    for (i = 0; i < length; i++)
        result += a[i];
    return result;
}


//if you want to return int, you should cast from unsigned to int first.
int str_longer(char *s, char *t) 
{
    return (int)strlen(s) - (int)strlen(t) > 0;
}

//copy conten from kbuf to dbuf
//notice, you should use the size_t type define the len, because the memcpy used it.
size_t copy_from_kbuf(void *dbuf, size_t maxlen) 
{
    //define the len is less than maxlen
    size_t len = KSIZE < maxlen ? KSIZE : maxlen;
    memcpy(dbuf, kbuf, len);
    return len;
}



int main(int argc, char const *argv[])
{
    /*
    linux64：
    int 12345 hex show : 39300000      小端法    数值的十六进制表示在每台机器上的输出结果一样,64位机器int类型是4字节大小
    float 12345 hex show : 00e44046    小端法    数值的十六进制表示在每台机器上的输出结果一样，64位机器上float是4字节大小
    the address 12345 hex show  : 393000006cc17a9c    小端法：地址在每台机器上不一样，64位机器上指针是8字节
    每个字节是8位，也就是说int和float 12345需要使用32位的二进制数字表示，而每4位二进制字符可以组成一个十六进制字符
    所以8个16进制字符完全可以表示一个4字节的十进制数。当然8字节的比如指针是64位，就需要16个16进制字符来表示
    我们可以依据四位二进制可以表示一个16进制字符来换算。十进制没有规则，不需要记忆。任何和10进制数字的转换都需要经过16进制的转换
    int 12345   the hex show is 0x00003039
    float 12345 the hex show is 0x4640e400

    hex 0x00003039 -=-> binary 0000 0000 0000 0000 0011 0000 0011 1001
    每个十六进制字符可以由4个二进制表示。
    
    格式化输出
    %.2x输出标准化16进制，也即至少使用两个16进制字符表示一个字节，也就是使用4位二进制表示一个16进制字符
    %d输出一个十进制整数
    %f输出一个浮点数
    %c输出一个字符

    */
    test_show_bytes(12345);
    const char *s = "abcdef";
    show_bytes((byte_pointer)s, strlen(s));

    /*     
    the boolean algebra, similar to logical operation
    & : and
    | : or
    ^ : with or  1 ^ 1 = 0   0 ^ 0 = 0  1 ^ 0 = 1;
    ~ : not 
    a & (b | c) = (a & b) | (a & c)
    a ^ a = 0
    a ^ b = 1
    (a ^ b) ^ a = a ^ a ^ b = 0 ^ b = b
    确定一个位级表达式的结果的最好办法，就是将十六进制的参数扩展成二进制表示并执行二进制运算
    然后再转回16进制
    */

   int a = 10, b = 20;
   printf("before swap ---> a = %d, b = %d\n", a, b);
   inplace_swap(&a, &b);
   printf("after swap ---> a = %d, b = %d\n", a, b);

    int arr[] = {1, 2, 3, 4, 5};
    int i;
    //notice:the sizeof function is aim to get the byte number about one object
    int len = sizeof(arr) / sizeof(int);
    printf("--------------before reverse-----------");
    for (i = 0; i < len; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
    reverse_array(arr, len);
    printf("--------------after reverse-----------");
    for (i = 0; i < len; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");

    //the one commonly used method of the bit operation is the mask.
    //0xff : 0x1111 1111
    //0x89abcdef & 0x000000ff = 0x000000ef
    //~0 means a mask 0xffffffff
    //hex 0x89abcdef : bin 0000 1000 0000 1001 0000 1010 0000 1011 0000 1100 0000 1101 0000 1110 0000 1111
    //if you want get hex 0x00000021 : bin 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0010 0000 0001
    //you can use the 0x89abcdef & 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0010 0000 0001
    //you can get bin 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0010 0000 0001 : hex 0x00000021

    //the logical operation in c language : && || !   and or not
    //the logical is different with bit operation, logical think o is false, and not 0 is true.
    //for example : !0x0 = 0x01 !0x41 = 0x00      !!0x41 = 0x01      0x69 && 0x55 =  0x01
    //the result in logical is two, one is 1, one is 0, the hex is 0x01 and 0x00

    //the standard hex print, the head is 0x.
    printf("0x%.2x\n", logical(10, 20));

    //the shift operation
    //x<<k : move k bit to left, the right use zero filling. you can think it will drop the highest bit.
    //x>>k : move k bit to right. the special in it is involved logical and arithmetic. the logical move to
    //right will use zero filling. and the arithmetic will use the highest bit filling. it is friendly to a signed.
    //for example x :       01100011 10010101
    //x << 4 :              00110000 01010000
    //x >> 4 :logical       00000110 00001001
    //x >> 4 :arithmetic    00000110 11111001
    //the difference is the arithmetic move to right, it use the highest bit to fill the null bit.
    //note : almost all of the compiler use arithmetic move to right for a signed number. for a unsigned
    //number, you should use logical when you move to right. 
    //but for java, it has a clear definition, the >> mean arithmetic and the >>> means logical.
    //then if you move a number that greater than 32 or 64, you do not need to have scruples, it will move
    //the mod, n % 32, if you move 32 in a 32 bit machine, it will move 32 % 32 = 0 bit, if you move 34 in 
    //a 32 bit machine, it will move 34 % 32 = 2 bit. but the different linux version will be difference.
    //it mean you should ensure the bit number you will move is less than the bit number for your machine.
    printf("0x%.2x\n", 0x00abcdef << 8);//echo 0xabcdef00
    printf("%d\n", (1 << 2) + (3 << 4));//echo 52  : 
    // dec 1 : bin 0000 0001 << 2 = 0000 0100
    // dec 3 : bin 0000 0011 << 4 = 0011 0000
    //0000 0100 + 0011 0000 = 0011 0100 = 32 + 16 + 4 = 52
    //notice : the + is proor to << , so if you need to adjust it, you should use ()

    //the unsigned is unsigned int.
    //32bit machine  int : -2147483648-->2147483647
    //32bit machine unsigned : 0 --> 4294967295
    //char 128 --> 127
    //unsigned char 0 --> 255
    //you should notice that, the negative number is a more than a positive number.
    //c and c++ support the unsigned, and the java not support the unsigned.
    //the max dex of w bit binary is 2^w - 1; for example, the 4 bit can represent max dec number is 2^4-1=15
    //so the range for it is 0-15, it is the unsigned, for example, a int in 32 bit is 4 byte = 32 bit, so
    //the unsigned int range in 32bit is 0-2^32-1 = 4294967295
    //then you can get the different represent if consider the highest bit is signed bit.
    //我们一般使用补码来表示最高位为1代表有符号数。正数的源码和补码相等，负数的补码等于最高符号位不变其余位取反+1
    //bin 1110 unsigned : dec 1*2^3+1*2^2+1*2^1+0*2^0 = 8+4+2+0 = 14
    //bin 1110 signed   : dec 1*(-2)^3+1*2^2+1*2^1+0*2^0 = -8+4+2+0 = -2
    //so the range for 4 bit signed is 1000=-8-->0111=7 ---->the range is -8 to 7, means -2^highesbit=-8 to 2^(highes)-1=7
    //the range for 4 bit unsiged is 0000=0 ---> 1111=15, so the range is 0 to 2^4-1=15
    //notice the highest bit is 4-1=3, the bit number is 4, but the highest is 3, beacause it start with 0 bit.
    //so you should keep in mind that the range for signed is -2^(bitnumber-1) to 2^(bit number - 1)-1
    //the range for unsigned is 0-2^bitnumber -1
    //the bit number is binary number, the highest is equal to binary number minus one.
    //c 语言的标准并没有要求用补码形式来表示有符号整数，但是几乎所有的机器都是这样做的。如果希望自己的程序具有更大的
    //可移植性，那么就也需要这样做。即使用补码来表示有符号整数。
    //limits.h headfile define some const variable, you can use INT_MAX INT_MIN UINT_MAX to represent signed or unsigned range.
    //you should use %d to format signed int, and use %u to format unsigned int.
    printf("the signed int range is from %d to %d\n", INT_MIN, INT_MAX);
    printf("the unsined int range is from 0 to %u\n", UINT_MAX);

    //当C预处理器遇到仅用空格隔开的一个字符串常量序列时，就把他们串联起来。如下案例
    //you should use %lu to format uin64_t, and use %d to format uint32_t
    printf("x = %" "d\n", INT_MAX);//equal to printf("x = %d\n", INT_MAX);
    uint64_t u64 = 10;
    uint32_t u32 = 20;
    printf("u64 = %lu, u32 = %d\n", u64, u32);

    //下面我们来理解下补码，先给出结论，如果将一个有符号的数强制类型转换为无符号数，位表示不会改变，改变的是数值
    //也就是说位表示不会被更改，只是使用相同的位表示在无符号和有符号之间切换。
    //比如unsigned 1110 --> (int)1110;14 --> -2
    //即 unsigned ux = 14; int x = (int)ux; printf("%d\n", x);echo -2
    int x = -12345;
    unsigned ux = (unsigned)x;
    //%d dec, %x hex, %c one char, %s string, %p pointer
    //数值可能会改变但是位模式不会改变。
    printf("x = %d, ux = %u\n", x, ux);

    //of course, you can also use the implicit type conversion.
    int x1 = -1;
    unsigned ux1 = 2147483648;
    //notice: the bit not change, the dec number is changed.
    //unsigned dec 2147483648 : binary 10000000000000000000000000000000
    //signed dec = -2^(32-1) = -2147483648

    //int dec -1 : binary 11111111111111111111111111111111
    //unsigned dec = 2^32 = 4294967296 - 1;
    //the you should keep in mind that, the unsigned range is 0..--> 1... = 0 to (2^w - 1), the w is bit number
    //the int range is 10000.. --> 0111.. = -2^(w-1) to 2^(w-1)-1 
    //and the dec -1, binary is 11111111111111111111111111111111
    //the dec -2147483648 binary is 10000000000000000000000000000000, only the highest bit is -2^, the other bit is 2^
    printf("x1 = %u = %d\n", x1, x1);
    printf("ux1 = %u = %d\n", ux1, ux1);
    //两个数进行运算，当其中一个数是无符号的时候，另一个也会被强制转换为无符号的进行运算。
    //无符号数的零扩展：要将一个无符号数转换为一个更大的数据类型，我们只要简单地在表示的开头添加0.
    //signed 111 == 1111 == 11111 == 111111
    //short -12345 = cf c7; int -12345 = ff ff cf c7; int类型的大于short类型的大小，所以在表示有符号数的时候
    //在高位填充1即可，填充后的数值等于填充前的，1111 = f, 无符号的使用填充0，这个在强制类型转换的时候很有用，可以
    //对多余或者少的内存进行扩容和减容，从高位减容或者扩容，有符号的使用1，无符号的使用0
    //unsigned 111 == 0111 == 00111 == 000111
    short sx = -12345;
    unsigned short usx = sx;//位表示不变的情况下将其隐式转换为无符号十进制数值53191
    int x2 = sx;//会扩容，有符号的会使用1填充
    unsigned ux2 = usx;//会扩容，无符号的会使用0填充
    //以上定义的是十进制数值，包含有符号short int 和无符号short int, 下面我们使用十六机制输出这些十进制数值
    printf("sx = %d\t", sx);
    show_bytes((byte_pointer)&sx, sizeof(sx));
    printf("usx = %u\t", usx);
    show_bytes((byte_pointer)&usx, sizeof(unsigned short));
    printf("x2 = %d\t", x2);
    show_bytes((byte_pointer)&x2, sizeof(int));
    printf("ux2 = %u\t", ux2);
    show_bytes((byte_pointer)&ux2, sizeof(unsigned));
    //you can also use the format directly, but it will only show the useful information, you will not see
    //the zero filling or one filling. but the show_bytes loop for all the bits, so it can show all information.
    //this is why we use the show_bytes function.
    printf("%.2x\n", ux2);//echo cfc7
    /*  
    因为我们的是小端法机器，所以输出的结果和实际结果顺序刚好是相反的，从低位开始写,每个16进制字符占用4个位
    ，每两个16进制字符占用一个字节，以一个字节为单位从低位开始读取。
    sx = -12345     c7cf         0xcfc7
    usx = 53191     c7cf         0xcfc7
    x2 = -12345     c7cfffff     0xffffcfc7    有符号的使用1填充
    ux2 = 53191     c7cf0000     0x0000cfc7    无符号的使用0填充
    */
    // int a1 = -12345;


    //page 89
    //then if you cast from short to unsigned, it will be cast from short to int, then cast from int to unsigned.
    printf("%lu\n", sizeof(unsigned));
    
    //truncate : if you do not want to expand bit, but want to reduce the bit numbers for a number.
    //just like you want cast from int to short. the int is 32 bits, and  the short is 16 bits.
    /*
        int x = 53191       bin = 0000 0000 0000 0000 1100 1111 1100 0111
        short sx = (short)x;bin = 1100 1111 1100 0111 = -2^15+2^14+2^11+2^10+2^9+2^8+2^7+2^6+4+2+1=-12345
        because the short is signed, so the highest bit is 1, mean it will be a negative number.
        int y = (int)sx; y = 1111 1111 1111 1111 1100 1111 1100 0111  -12345
        so you can get a rule, the expand will not change the dec number, but the reduce bit will change the number.
        just like above cast from int to short, from 32 bits to 16 bits. the reduce of bits numbers we call it truncate.
        16位的位模式就是-12345的补码表示
        notice :  unsigned number, we can use 8 bit numbers to show a dec from 0 to 255(2^8-1), and we can use
        4 bit numbers to show all hex numbers(0-f); 
        notice : unsigned or signed just as the dec number. int short long etc...
        imagine a situation, you have a 4 bit numbers hex, you want to truncate it to 3 bit number hex.
        hex 0 : bin 0x0000 --> truncate bin 0x000 = hex 0
        hex 2 : bin 0x0010 --> truncate bin 0x010 = hex 2
        hex 9 : bin 0x1001 --> truncate bin 0x001 = hex 1
        hex b : bin 0x1011 --> truncate bin 0x011 = hex 3
        hex f : bin 0x1111 --> truncate bin 0x111 = hex 7

        image it is a unsigned int number
        unsigned 0 : bin 0000 --> truncate bin 000 = unsigned 0
        ...

        image it is a int number
        int 0 : bin 0000 --> truncate bin 000 = int 0
        int 2 : bin 0010 --> truncate bin 010 = int 2
        int -7: bin 1001 --> truncate bin 001 = int 1
        int -5: bin 1011 --> truncate bin 011 = int 3
        int -1: bin 1111 --> truncate bin 111 = int 7

        we can get the rule from the int truncate. but the rule do not useful for our study, so we can 
        handle it by truncate binary to get the number when we need it.

        just like above, cast from signed to unsigned often lead to some intuitive behavior.
        and this often lead to a error in your process. and it is not easy to be found.
    */

    float arr_float[] = {};
    unsigned arr_len = sizeof(arr_float) / sizeof(int);
    float result = sum_array(arr_float, arr_len);
    printf("result = %.2f\n", result);

    //notice:the size_t in stdio.h head file is unsigned int type.
    int result_longer = str_longer("woshishui, bu woshi shen", "woshishen");
    printf("it is %s\n", result_longer ? "true" : "false");

    //then the data type do not match is how important? we need give one example to emphasize it.
    //for example, you define a function and you should user pass a variable len as param.
    //if you define the len type is unsigned, but the user pass a negative number, just like -1.
    //the int -1 binary is 1111 1111 1111 1111 1111 1111 1111 1111, it will be treated as a unsigned int,
    //it will be obvious that the -1 passed will be the max unsigned int number. if your function is about
    //important data get function, then the security vulnerabilities will bring you great losses.just like the following case
    //the function copy_from_kernel, it used memcpy system call function. the memcpy used size_t(unsigned int)
    //to accept the len, if you define the int as the len in your function, it will be a problem like above.
    //so you should define the size_t len and other param you will use, or you will have trouble.
    //then we create a function to copy content from one file to anther file. but we must use buf.
    //we have a test_src.txt in current dir, we need to copy it to test_des.txt
    int fd_src = open("test_src.txt", O_RDONLY);
    ssize_t len_src = read(fd_src, kbuf, 10);
    size_t len_des = copy_from_kbuf(dbuf, (size_t)len_src);
    printf("%zu\n", len_des);
    printf("%zd\n", len_src);
    printf("content in kbuf is %s\n", kbuf);
    printf("content in dbuf is %s\n", dbuf);

    //above we have done the copy from src to dest, then we will write it to driverdisk
    //you should open a fd in your path, and write the dbuf to it.
    int fd_des = open("test_des.txt", O_RDWR|O_CREAT|O_TRUNC, 0644);
    write(fd_des, dbuf, len_des);
    //above, we have get some information that the different type is very important 
    //vulnerability in progress, so we need to attention it in the follow-up work.

    //94
    return 0;
}
