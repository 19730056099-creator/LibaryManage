---
artifact_id: milestone-06
language: zh-CN
---

# 里程碑

milestone_id: milestone-06

## 目标

全面加固：垃圾输入、损坏/缺失文件、容量上限、以及借出压力下的更新语义。

## 可观察结果

- 数量输入非数字时不会悄悄变成 0 本。
- `books.txt` 中一行被截断或字段损坏时，跳过（或报告）该行，而不是让后面所有记录解析错位。
- 删除有未还记录的书时，要么拒绝要么级联清理记录——由你决定并写明。

## 设计压力

真实用户乱输；磁盘丢文件。静默的数据损坏比崩溃更糟，因为它会扩散。

## 范围

- 数字输入的校验辅助函数。
- `loadData` 的防御性解析（token 计数检查）。
- "有未还记录时删除"的策略决策与实现。
- 可选：忽略大小写的搜索；重复借阅防护。

## 约束

- 文本格式保持与 milestone-05 写出的文件向后兼容。
- 不用外部库。

## 前置知识

- competency_id: project.array-crud（前序里程碑已就绪）
- competency_id: language.c.file-io（已就绪）

## 任务

1. 把数量输入的裸 `atoi` 换成带校验的解析（拒绝非数字）。
2. 在 `loadData` 中统计每行 token 数；不足 5 个字段的行跳过。
3. 决定并实现删除策略；在你的 README/帮助中写明。
4. 至少选做一项可选加固并实现。

## 验收

- m06-a01：数量输入 "abc" 报错且不添加任何书。
- m06-a02：手工破坏 `books.txt` 的一行后，加载后其余图书完好。
- m06-a03：删除有未还记录的书按你声明的策略执行，且 available 永远不出现不一致。
- m06-a04：帮助文本描述了你选择的各项策略。

## 提示 1

严格数字解析：先拒绝空串和任何非数字字符，再调 atoi。

## 提示 2

strtok 统计 token：连续调用五次；中途任何一次返回 NULL 即该行畸形。

## 提示 3

删除策略上，"有未还记录就拒绝"比级联清理更简单安全——但要给出理由。

## 提示 4

忽略大小写匹配：把两个字符串先用 tolower 复制到缓冲区再做 strstr。

## 提示 5

成熟项目并没有完全解决本里程碑——把你的方案与 `main.c::case 1`、`data_mgr.c::loadData` 对比，指出你超越它的地方。这个差距分析才是重点。

## 下一项压力

课程完成：在最终评审中把你的重构历程连回成熟仓库。

## 源码桥接

`main.c::case 1/case 6`, `business.c::updateBook/deleteBook/borrowBook`, `data_mgr.c::loadData`

## 证据台账

```text
evidence: teaching_inference
confidence: high
rationale: 成熟代码做了部分输入清洗（strcspn）但信任 atoi 和文件结构；本里程碑刻意超越它。
source: main.c::case 1, data_mgr.c::loadData
```

## 完成结论

（待最终评审填写）
