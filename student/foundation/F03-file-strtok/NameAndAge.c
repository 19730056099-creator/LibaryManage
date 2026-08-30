#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    FILE *f = fopen("input.txt", "w");
    fprintf(f,"鸣人|30\n佐助|25\n");
    fclose(f);

    f = fopen("input.txt","r");
    char line[256];
    //char line[256]：保存一行文本，最多 255 个字符。
    while (fgets(line,sizeof(line),f)){
        line[strcspn(line,"\n")] = '\0';
        //strcspn：找到换行符并删除。
        char *name = strtok(line,"|");
        //strtok(line, "|")：按 | 分割，第一次取得姓名。
        char *age = strtok(NULL,"|");
        //strtok(NULL, "|")：继续分割同一行，取得年龄；NULL 表示沿用上次字符串。
        if (name && age) 
            printf("%s will be %d\n", name, atoi(age)+1);
        //atoi：把字符串形式的年龄，如 "18"，转换成整数 18。相当于是强转，将字符串类型转化为整型
    }
    fclose(f);

    return 0;
}

//代码错误修正后，一定要重新编译，因为最终运行的是编译后的执行文件，所以的话必须使用编译器例如gcc重新编译代码文件
//生成新的执行文件