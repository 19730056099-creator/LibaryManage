---
artifact_id: foundation-03
language: zh-CN
---
# 前置补给单元

foundation_id: foundation-03
competency_id: language.c.file-io
competency_id: project.delimited-persistence

## 为什么现在需要

milestone-03 要让数据在重启之间存活：把管道符分隔的行写入 `books.txt`，再解析回来。开始该里程碑前，你需要 fopen/fgets/fprintf 和 strtok 解析模式。

## 依赖

foundation-01（字符串）、foundation-02（数组）。

## 最小概念

- **写模式**：`fopen(path, "w")` 打开**已存在**的文件会先把它清空。`"r"` 是读；返回 NULL 表示文件不存在。
- **写一行**：`fprintf(f, "%s|%d\n", name, age);` 然后 `fclose(f)`。
- **读回来**：
  ```c
  char line[256];
  while (fgets(line, sizeof(line), f)) {   // 每次一行，保留 '\n'
      char *tok = strtok(line, "|");       // 第一次调用：传整行
      while (tok) {
          printf("[%s]\n", tok);           // 依次得到每个 | 分隔的字段
          tok = strtok(NULL, "|");         // 之后传 NULL
      }
  }
  ```
- `strtok` 会原地修改缓冲区（把 `|` 替换成 `\0`）——需要保留原文就先复制一份。
- 数字回来时是字符串：用 `atoi` 转换。

## 小例子

```c
#include <stdio.h>
#include <string.h>
#include <stdlib.h> #atoi是stdlib.h中的函数

int main() {
    FILE *f = fopen("demo.txt", "w");
    fprintf(f, "alice|30\nbob|25\n");
    fclose(f);

    f = fopen("demo.txt", "r");
    char line[256];
    while (fgets(line, sizeof(line), f)) {
        line[strcspn(line, "\n")] = '\0';
        char *name = strtok(line, "|");
        char *age = strtok(NULL, "|");
        if (name && age) printf("%s will be %d\n", name, atoi(age) + 1);
    }
    fclose(f);
    return 0;
}
```

## 动手练习

f03-a01：写一个程序：把两条 `name|age` 记录存入文件，再读回两个结构体实例并打印。然后删掉文件再运行一次——程序在 fopen 返回 NULL 时不能崩溃。

## 通过标准

- 存取往返后打印的数据一致；
- 能解释 strtok 的 NULL 参数是什么含义、为什么必须避免 atoi(NULL)；
- 文件缺失时不崩溃。

## 项目桥接

这正是 `data_mgr.c::loadData/saveData` 的机制，milestone-03 使用它并在 milestone-05 扩展到借阅记录。required_by: milestone-03。

## 暂不学习

二进制文件、fseek/ftell、CSV 转义规则、NULL 检查之外的错误码处理。

```
evidence: code_evidence
source: data_mgr.c::saveData
rationale: The unit's mechanism mirrors this mature-code location.
```

## 完成结论

（未开始）
