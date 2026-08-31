---
artifact_id: review-f02
language: zh-CN
---

# 阶段评审

review_id: review-01-02
milestone_id: foundation-01
verdict: passed

## 优点

- f02-a01 完成：3+ 个 `struct Point` 的数组初始化、删除下标 2、打印剩余 name。编译零警告，输出正确（鸣人/佐助/大和/卡卡西）。
- 注释中的概念理解全部正确且深入：
  - 结构体数组 = 数组每个元素是一整组数据 ✅
  - 数组初始化需要 `= {...}`；`char name[20] = "鸣人"` 只能在定义时初始化，之后必须 strcpy——总结的"出生时可以整体初始化，出生后用 strcpy"非常准确 ✅
  - 对三处漏 `;` 的错误传播链分析（声明失败 → 后续 undeclared 连锁报错）完全正确 ✅
- 主动提出了关键问题："这种实现没有真正删除，只是覆盖 + 少访问最后一位，时间复杂度 O(n)，有没有更好的方法/第三方库？"

## 正确性

- 前移循环边界 `i < count - 1` 正确；`Points[i] = Points[i+1]` 结构体整体赋值正确。
- 删除最后一个元素时循环执行 0 次（只做 count--）——你代码里 idx=2 不是末尾，但机制上已隐含支持。

## 验收证据

- f02-a01：`student/foundation/F02-array-delete/main.c` — demonstrated（本机编译运行验证）。
- 命令：`gcc -Wall -Wextra main.c -o main && ./main`

## 当前阶段权衡

- 回答你的问题：**O(n) 就是这个数据结构的代价，没有免费的更好方案**。链表删除是 O(1) 但失去按下标随机访问；成熟项目选静态数组正是权衡了简单性与 1000 本的上限。"不访问最后一位"不是 hack，而是计数器语义的正确使用——这正是 milestone-02 `deleteBook` 的标准做法。

## 下一项规模压力

内存里的书一退出就没了。F03 将教你把结构体写进文件再解析回来（fopen/fgets/strtok），这是 milestone-03 持久化的全部基础。

## 参考项目对比

你的前移删除与 `business.c::deleteBook` 完全一致（同样的 for 边界和 count--）。区别仅在成熟代码把删除封装成按 ID 查找 + 删除的函数。

## 必须修改

无。（两处注释里写的"忘记加个:"是学习笔记，不影响代码本身。）

## 可选改进

- 练习要求删除的是**中间**元素并打印剩余——已达成；可再加一步：删除最后一个元素验证循环执行 0 次。
- 关于"第三方库"：C 标准库没有现成的动态集合；实际项目中会用 glib 的 GArray 或自己写动态数组，但本项目刻意保持零依赖。

## 结论

**passed** — foundation-02 通过。能力 `language.c.arrays-pointers` 升级为 `ready / demonstrated`。请进入 foundation-03（`course/zh-CN/foundations/F03-file-strtok.md`）。
