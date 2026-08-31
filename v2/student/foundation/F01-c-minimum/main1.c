// struct Book{
//     char id[20];
//     char title[100];
//     int quantity;
// };//注意这边结构体的结尾一定要写;如果没有这个;编译器会认为前面的声明还没有正常结束，于是把后面的系统头文件也解析乱了

// #include <stdio.h>
// #include <string.h>
// int main() {
//     struct Book b;
//     strcpy(b.id, "B001");
//     strcpy(b.title, "C Programming");
//     b.quantity = 3;

//     if (strcmp(b.id,"B001") == 0)
//         printf("书号: %s,数量: %d\n", b.id, b.quantity);
//     printf("id length = %zu\n",strlen(b.id)); //输出 4,缓冲区至少要5
//     //printf("%d\n", strlen("hello"));不严谨，而且属于类型不匹配。因为 %d 要求后面的参数是 int，而 strlen() 返回 size_t

//     //而且表示的长度也不同,int → 通常32 位 size_t    → 通常 64 位
//     //strlen() 和 sizeof() 得到的结果，要用 %zu 打印。
//     return 0;
// }
//  //
//  //关于编译
//  //-o 里的 o 就是 output（输出） 的意思

//  //编译后可执行的文件
//  // ./main
//  //为什么不能是 main直接运行呢,这涉及到linux中寻找并执行程序的
//  //而 ./指明了是在当前根目录下寻找 执行程序


//  //window和linux默认的系统终端编码是不一样的是吧，windows中如果不使用gbk编码，
//  // 编译后的c程序就会输出乱码，而在linux中，使用gbk编码反而出现了报错，反而是默认的utf-8可以正常输出
//  // 乱码通常不是“中文有问题”，而是“产生这些字节的人”和“解释这些字节的人”使用了不同的编码规则。