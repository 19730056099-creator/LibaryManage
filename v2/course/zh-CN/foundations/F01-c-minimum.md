---
artifact_id: foundation-01
language: zh-CN
---

# 前置补给单元

foundation_id: foundation-01
competency_id: language.c.structs-strings

## 为什么现在需要

本项目里每本书都是一个带定长 char 数组字段的结构体（`data_mgr.c::Book`）。进入 milestone-01 前，你必须会定义这种结构体、复制和比较其中的字符串、并按下标传递它们。

## 依赖

无（第一个单元）。默认你有 C 语言基础印象——这是恢复性复习。

## 最小概念

- **带 char 数组的结构体**：
  ```c
  struct Book {
      char id[20];
      char title[100];
      int quantity;
  };
  struct Book b;            // 一个实例
  struct Book books[1000];  // 实例数组
  ```
- **字符串复制**：`strcpy(dst, src)`——连同结尾的 `'\0'` 一起复制。
- **字符串比较**：`strcmp(a, b)` 相等时返回 0。相等判断是 `== 0`，不是 `== 1`。
- **长度**：`"B001"` 占 6 个字节——4 个字符 + 隐藏的 `'\0'` 结尾符。每个字符串都要给它留位置。
- **fgets 后去换行**：`s[strcspn(s, "\n")] = '\0';`

## 小例子

```c
#include <stdio.h>
#include <string.h>

int main() {
    struct Book b;
    strcpy(b.id, "B001");
    strcpy(b.title, "C Programming");
    b.quantity = 3;

    if (strcmp(b.id, "B001") == 0)
        printf("match: %s, qty=%d\n", b.id, b.quantity);
    printf("id length = %zu\n", strlen(b.id));   // 输出 4，缓冲区至少要 5
    return 0;
}
```

## 动手练习

f01-a01：定义 `struct Point {char name[20]; int x;}`。创建两个名字不同的实例，用 `printf("%s %d\n", ...)` 打印各自内容，再用 `strcmp` 写一个 if/else 报告两个名字是否相同。

## 通过标准

- 练习编译通过、输出正确；
- 能说出为什么存 5 个字母的名字缓冲区至少要 6。

## 项目桥接

直接对应 `data_mgr.c::Book/BorrowRecord` 的字段处理和 `business.c::addBook` 里的 ID 匹配。required_by: milestone-01。

## 暂不学习

动态内存（malloc/free）、结构体指针（`->`）、strcpy/strcmp/strlen/strcspn/strstr 之外的字符串函数。

```
evidence: code_evidence
source: data_mgr.c::Book
rationale: The unit's mechanism mirrors this mature-code location.
```

## 完成结论

（未开始）
