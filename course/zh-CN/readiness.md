---
artifact_id: readiness
language: zh-CN
---

# 学习准备

## 项目所需能力

完整依赖图见 `knowledge-graph.md`：7 项能力（tooling 1、language 3、project_concept 2、domain 1），对其首个里程碑均为阻塞项。

competency_id: tooling.c.gcc-build
state: needs_refresh
competency_id: language.c.structs-strings
state: ready
competency_id: language.c.arrays-pointers
state: ready
competency_id: language.c.file-io
state: needs_refresh
competency_id: project.array-crud
state: needs_refresh
competency_id: project.delimited-persistence
state: needs_refresh
competency_id: domain.borrow-inventory
state: needs_refresh

## 学习者基线

**尚未校准。** 目前没有任何学习者证据。课程结构已就绪，但个性化路线（需要创建哪些前置补给单元）取决于你的回答。

## 差距与决策

请选择一种校准方式：

1. **`assume_beginner`（零基础假设）**——我会在 milestone-01 之前创建补给单元 F01–F03（C 结构体与字符串、数组与前移删除、文件读写与 strtok）。最稳妥，多花约 2–4 小时。
2. **`self_report` / `mixed`（自报 / 混合）**——回答下面 5 个问题；只在你不确定的地方创建补给单元。
3. **`waived`（跳过校准）**——直接进入 milestone-01 并记录风险（中途可能撞上 C 语法或 strtok 的墙）。

校准问题（能力导向，约 5 分钟）：

- Q1（编译）：能否用 `gcc a.c b.c -o app` 编译拆成两个 .c 文件的程序，并解释这里直接 `#include "xxx.c"` 为什么也能工作？
- Q2（结构体与字符串）：`char id[20]; strcpy(id, "B001"); if (strcmp(id,"B001")==0) ...` 会发生什么？为什么数组长度必须 ≥ 6？
- Q3（数组与前移删除）：5 个元素、count=5 的结构体数组：写出用前移方式删除下标 2 的循环。能不看资料写出来吗？
- Q4（文件读写）：`fopen(path, "w")` 对已存在的文件做什么？第二次调用 `strtok(NULL, "|")` 在继续做什么？
- Q5（领域不变量）：quantity=3 且已借出 2 本时，`available` 应该是多少？哪个操作把它加回来？

## 前置补给路线

校准后按需即时创建：

| 候选单元 | 覆盖能力 | 解锁 |
|---|---|---|
| F01-c-minimum | language.c.structs-strings | milestone-01 |
| F02-array-delete | language.c.arrays-pointers | milestone-01/02 |
| F03-file-strtok | language.c.file-io, project.delimited-persistence | milestone-03 |


foundation_id: foundation-01
foundation_id: foundation-02
foundation_id: foundation-03

## 进入项目的条件

当 gcc-build、structs-strings、arrays-pointers 三项为 `ready`（自报或演示证实），或明确豁免并记录风险时，milestone-01 才能开始。
