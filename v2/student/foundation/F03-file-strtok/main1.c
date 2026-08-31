#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    FILE *f = fopen("input.txt", "w");
    fprintf(f,"alice|30\nbob|25\n");
    fclose(f);

    f = fopen("input.txt","r");
    char line[256];
    while (fgets(line,sizeof(line),f)){
        line[strcspn(line,"\n")] = '\0';
        char *name = strtok(line,"|");
        char *age = strtok(NULL,"|");
        if (name && age) printf("%s will be %d\n", name, atoi(age)+1);
    }
    fclose(f);

    return 0;
}

//代码错误修正后，一定要重新编译，因为最终运行的是编译后的执行文件，所以的话必须使用编译器例如gcc重新编译代码文件
//生成新的执行文件