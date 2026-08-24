---
artifact_id: review-f01
language: zh-CN
review_id: review-01-01
milestone_id: foundation-01
verdict: passed
---

# 阶段评审

```
evidence: code_evidence
source: student/foundation/F01-c-minimum/main.c
rationale: 学习者的 f01-a01 练习，本机编译运行且输出正确。
```

## 优点

- 练习 f01-a01 完整实现：定义了 `struct Point`、两个实例、printf 输出和 strcmp 比较，编译零警告（`gcc -Wall -Wextra`），运行输出正确。
- 注释里主动澄清了几个关键概念：C 没有真正的字符串类型只有字符数组；strcpy/strcmp 只针对字符串而整数直接赋值；结构体结尾必须有 `;`；`strlen` 返回 `size_t` 要用 `%zu`——这些理解全部正确。
- 主动实验了编译命令差异（`-o` 参数即输出文件名）、`./` 与 Linux 程序查找机制、以及 Windows/Linux 编码差异导致的乱码问题，超出了单元要求。

## 正确性

- `main.c` 编译运行通过：打印两条记录并正确报告"两个名字不同"。
- 对 `%zu` 与 `size_t` 的理解正确。

## 验收证据

- f01-a01：`student/foundation/F01-c-minimum/main.c` — demonstrated（本机编译 + 运行验证）。
- 命令：`gcc -Wall -Wextra main.c -o main && ./main`

## 当前阶段权衡

- 用中文字符串做 strcmp 比较没问题（按字节比较），但注意 UTF-8 下一个汉字占 3 字节，`name[20]` 实际只能放约 6 个汉字——这正好呼应"结尾符要占位置"的知识点。

## 下一项规模压力

一本书不够用，也不该一个个变量存——你需要"结构体数组 + 计数器"，以及删除元素时的前移操作。这正是 F02 的内容。

## 参考项目对比

你的 `struct Point` 与成熟项目 `data_mgr.c::Book` 结构一致（char 数组字段 + 基础类型字段）。成熟代码额外依赖 `findBookIndex` 中的 strcmp 循环——F02 会覆盖数组部分。

## 必须修改

无。

## 可选改进

- 小勘误：你注释里说"文件的扩展名默认是 exe 格式"不准确——Linux 下 `-o main` 生成的就是无扩展名的可执行文件，exe 只是 Windows 惯例。不影响通过。
- `printf("两个名字不同")` 后可以加 `\n`，让输出更整洁。

## 结论

**passed** — foundation-01 通过。语言能力 `language.c.structs-strings` 升级为 `ready / demonstrated`。请进入 foundation-02（`course/zh-CN/foundations/F02-array-delete.md`）。
