---
artifact_id: foundation-02
language: zh-CN
---

# 前置补给单元

foundation_id: foundation-02
competency_id: language.c.arrays-pointers

## 为什么现在需要

本项目把所有书放在一个全局数组里，用一个计数器记录"实际有几本"。删除一本书不是挖个洞，而是把后面的元素整体左移——这是 milestone-01/02 的核心动作。

## 依赖

foundation-01（结构体与字符串）。

## 最小概念

- **结构体数组 + 计数器**：
  ```c
  struct Item items[100];
  int count = 0;              // count 是"有效元素个数"，不是数组长度
  items[count++] = 新元素;     // 追加：先放下标再自增
  ```
- **按下标访问**：`items[i].quantity`，遍历用 `for (int i = 0; i < count; i++)`。
- **前移删除**：把被删元素之后的每个元素往左挪一位，再让计数减一：
  ```c
  for (int i = idx; i < count - 1; i++) {
      items[i] = items[i + 1];   // 结构体可以整体赋值
  }
  count--;
  ```

## 小例子

```c
#include <stdio.h>

int main() {
    int a[5] = {10, 20, 30, 40, 50};
    int count = 5;

    int idx = 1;                     // 删除 20
    for (int i = idx; i < count - 1; i++) {
        a[i] = a[i + 1];
    }
    count--;

    for (int i = 0; i < count; i++) printf("%d ", a[i]);  // 10 30 40 50
    return 0;
}
```

## 动手练习

f02-a01：把上面的例子改成结构体版本——3 个 `struct Point {char name[20]; int x;}`，删除中间一个，打印剩余的 name。再思考：如果删除的是最后一个元素，循环会执行几次？（答案：0 次，只做 count--）

## 通过标准

- 练习程序输出正确的剩余元素与顺序；
- 能解释循环上界为什么是 `count - 1` 而不是 `count`。

## 项目桥接

这就是 milestone-02 `deleteBook` 的全部机制（对应 `business.c::deleteBook`），也是 `findBookIndex` 线性扫描的基础。required_by: milestone-01, milestone-02。

## 暂不学习

指针算术、`items[i]` 与 `*(items+i)` 的等价性、链表——静态数组够用，指针细节遇到再说。

```
evidence: code_evidence
source: business.c::deleteBook
rationale: The unit's mechanism mirrors this mature-code location.
```

## 完成结论

（未开始）
