//这是对应的练习部分 错误:错把标签符号当成注释符号了

struct Point{
    char name[20];
    int age;
};

#include <stdio.h>
#include <string.h>

int main(){
    struct Point a;
    struct Point b;
    //strcpy方法之所以叫strcpy是因为其是针对于字符串的方法，所以仅限于对字符串进行操作
    //包括strcmp等方法
    //而对于整数类型直接赋值即可

    //Why 不使用字符串类型
    //ans c中没有真正意义上的字符串类型，只有字符数组,如果要对字符串进行操作就是
    // 用strcpy函数（不能叫方法，方法是java，python这类面向对象的语言所有的）
    strcpy(a.name,"鸣人");
    a.age = 18;
    strcpy(b.name,"佐助");
    b.age = 19;
    
    printf("名字: %s,年龄: %d\n",a.name,a.age);
    printf("名字: %s,年龄: %d\n",b.name,b.age);

    if (strcmp( a.name, b.name) == 0)
        printf("两个名字相同");
    else
        printf("两个名字不同\n");
    return 0;
}

// 如果你确实想写成“可以直接赋值”的效果，可以用指针：
//char *name = "Alice";
//name = "Bob";   

//注意
//编译时候 
//gcc -Wall -Wextra main.c -o main 和 gcc -Wall -Wextra main.c -o main.exe是不一样的命令
// 最后的参数其实就是指定输出文件名了，扩展名并不是默认 exe——Linux 下 -o main 生成的是无扩展名的可执行文件，exe 只是 Windows 的命名惯例
//所以说如果使用第一种情况去编译（-o main），你执行./main.exe是没有输出结果
//因为当前目录下并没有叫 main.exe 的文件
