---
artifact_id: foundation-02
language: zh-CN
---

# 前置补给单元

foundation_id: foundation-02
competency_id: language.c.arrays-pointers
required_by: milestone-01
required_by: milestone-02
acceptance_id: f02-a01
practice_id: f02-p01
manual_action_id: f02-manual-01
ai_boundary_id: f02-ai-01
transfer_check_id: f02-transfer-01
reappears_in: milestone-01, milestone-02, milestone-04
command: gcc -std=c11 -Wall -Wextra -pedantic main.c -o foundation02

## 为什么现在需要

M01 需要保存不止一本书，M02 还要删除中间元素。固定容量结构体数组、有效数量和前移是达到这两个阶段的最小能力。

## 依赖

依赖 `foundation-01` 的结构体和字符串基础，以及能用 gcc 编译运行一个小程序。

## 最小概念

- 数组元素连续存放，`count` 表示有效前缀 `[0, count)`；容量不是有效数量。
- 删除下标 `index` 后，把 `index + 1` 到末尾的每个元素赋值到前一格，然后 `count--`。
- 循环边界要避免读 `items[count]`；删除最后一个元素时不需要移动。

## 小例子

```c
Item items[3] = {{"A", 1}, {"B", 2}, {"C", 3}};
int count = 3;
int index = 1;
for (int i = index; i < count - 1; i++) items[i] = items[i + 1];
count--; /* items[0], items[1] 现在是 A、C */
```

## 首次触摸

先在纸上或终端打印 `A B C`，删除下标 1，再打印有效前缀。故意忘记 `count--`，观察为什么旧的 `C` 会被重复看见；然后只修复计数，不增加新抽象。

## 动手练习

在 `student/foundation/F02-array-delete/main.c` 定义一个小结构体数组，放入三个元素，实现按下标删除并打印删除后的有效元素。再分别测试删除第一个、最后一个和中间元素。不要复制 `business.c::deleteBook`。

## AI 使用边界

AI 可以画数组移动示意图、解释下标边界或帮助设计三个删除场景。你必须亲自写移动循环、修改 `count`、编译并用三种位置测试；要能指出每次赋值的左右两端。

## 理解与迁移检查

把练习改成删除第 0 个元素，并解释循环为什么仍从 `index` 开始；再把数组容量改成 5，说明为什么有效数量仍由 `count` 决定。

## 通过标准

```text
acceptance_id: f02-a01
```

- 无警告编译并运行。
- 删除头部、中部、尾部时，输出只包含剩余有效元素且顺序正确。
- 能解释 `[0, count)`、前移和 `count--`，并提交一次迁移结果。

## 项目桥接

回看 `data_mgr.c::books`、`bookCount` 和 `business.c::deleteBook`。M01 会先用数组承载添加/列表，M02 再把本练习的前移逻辑变成项目删除。

## 暂不学习

暂不学习 malloc、链表、排序、哈希表、指针算术优化或并发；本项目的固定容量和线性扫描暂时足够。

## 完成结论

提交手写移动循环、三种位置的运行记录和迁移解释后，才能将 `foundation-02` 标记为 `passed`，并解锁 milestone-01 的数组前置条件。

```text
evidence: code_evidence
source: data_mgr.c::books, bookCount
rationale: 参考项目用固定容量 Book 数组和 bookCount 表示有效前缀，直接对应本单元的数组模型。
```

```text
evidence: code_evidence
source: business.c::deleteBook
rationale: deleteBook 从目标索引向左移动后续结构体并减少 bookCount，提供了前移删除的代码证据。
```
