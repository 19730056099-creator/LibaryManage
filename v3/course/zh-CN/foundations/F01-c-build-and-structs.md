---
artifact_id: foundation-01
language: zh-CN
---

# 前置补给单元

foundation_id: foundation-01
competency_id: tooling.c.gcc-build
competency_id: language.c.c-control-input
competency_id: language.c.structs-strings
required_by: milestone-01
acceptance_id: f01-a01
practice_id: f01-p01
manual_action_id: f01-manual-01
ai_boundary_id: f01-ai-01
transfer_check_id: f01-transfer-01
reappears_in: milestone-01
command: gcc -std=c11 -Wall -Wextra -pedantic main.c -o foundation01

## 为什么现在需要

milestone-01 的第一条链路是“编译 → 菜单输入 → 结构体状态 → 列表输出”。先掌握最小 gcc 构建、字符串和结构体，才能把注意力放在项目行为上。

## 依赖

无。假设你能创建目录和文件；本单元只恢复项目需要的 C 语法，不展开完整 C 课程。

## 最小概念

- 当前仓库编译时只传 `main.c`：它已经直接包含 `data_mgr.c` 和 `business.c`。
- `struct` 把多个字段放在一个值中；`char text[N]` 要为结尾 `\0` 留空间。
- `strcpy` 复制字符串，`strcmp(a, b) == 0` 表示相等；`fgets` 后可用 `strcspn` 去掉换行。
- `do-while` 至少执行一次，`switch` 根据整数分派；`atoi` 先作为最小解析方式，坏输入放到 milestone-06。

## 小例子

```c
#include <stdio.h>
#include <string.h>

typedef struct { char code[8]; int pages; } Item;

int main(void) {
    Item item;
    char line[32];
    if (!fgets(line, sizeof line, stdin)) return 1;
    line[strcspn(line, "\n")] = '\0';
    strcpy(item.code, line);
    item.pages = 10;
    printf("%s %d\n", item.code, item.pages);
    return 0;
}
```

## 首次触摸

先创建只有 `printf("hello\\n")` 的 `main.c`，运行上面的 gcc 命令并执行 `./foundation01`。看到输出后，再把程序改成使用 `Item`；先观察“源文件 → 可执行文件 → 终端输出”，不要先背概念名词。

## 动手练习

在 `student/foundation/F01-c-build-and-structs/main.c` 手写一个更小版本：定义 `Item`，读入不超过 7 个字符的 code，读入整数 pages，打印两者；用 `do-while` 包住菜单，只有输入 `0` 才退出。不要复制参考项目函数。

## AI 使用边界

AI 可以解释编译器消息、帮你设计测试输入、指出换行或类型的可能位置。你必须亲自创建 `main.c`，写出 `Item`、输入循环和退出条件，运行 gcc，并保存一次输出；提交时说明哪些内容使用了 AI。AI 生成的成功代码不能单独作为通过证据。

## 理解与迁移检查

- 把 `code[8]` 改成 `code[12]`，输入 11 个字符，解释为什么这会改变可接受长度。
- 口头解释 `strcmp(...) == 0`、`fgets` 后去换行，以及本仓库为何只编译 `main.c`。

## 通过标准

```text
acceptance_id: f01-a01
```

- gcc 命令无错误、无警告，`./foundation01` 能运行。
- 输入一次后能看到相同 code 和 pages；输入 `0` 能退出循环。
- 提交 `main.c`、构建输出、一次运行记录和理解/迁移回答。

## 项目桥接

完成后回看 `data_mgr.c::Book`、`main.c::main`、`main.c::displayMenu`，指出自己的 `Item`、输入循环和参考代码的对应关系。下一单元处理结构体数组与删除。

## 暂不学习

暂不学习指针算术、动态内存、文件持久化、`strtok`、借阅业务、完整输入校验或头文件重构；这些会在后续压力出现时再引入。

## 完成结论

本单元只有在学习者提交手写练习、构建/运行证据并通过解释迁移检查后，才能在 `progress.json` 中标记为 `passed`，并把三个能力标为 `ready`。

```text
evidence: code_evidence
source: data_mgr.c::Book
rationale: Book 使用固定大小的 id/title/author 字符数组和整数数量字段，直接支持本单元的结构体与字符串桥接。
```

```text
evidence: code_evidence
source: main.c::main
rationale: main.c::main 使用 fgets、strcspn、atoi、do-while 和 switch，提供本单元的控制流与输入证据。
```

```text
evidence: code_evidence
source: main.c::data_mgr.c::business.c includes
rationale: main.c 直接包含两个实现文件，决定了当前仓库的最小 gcc 构建入口。
```
