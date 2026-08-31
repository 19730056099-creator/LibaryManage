---
artifact_id: milestone-04
language: zh-CN
---

# 里程碑

milestone_id: milestone-04

## 目标

一次遍历完成对 id、title、author 的子串搜索。

## 可观察结果

菜单选项 3 接收关键字，打印 id 或 title 或 author 包含它的所有图书；无匹配时给出明确提示。

## 设计压力

书目增长后无法靠肉眼浏览。一个关键字要覆盖用户可能记得住的每个字段。

## 范围

- 用 `strstr` 对三个字段实现 `searchBook(keyword)`。
- 复用与列表视图相同的行打印格式。

## 约束

- 区分大小写可接受（记入 milestone-06 待办）。
- 不建索引/哈希表——线性扫描即可。

## 前置知识

- competency_id: project.array-crud（blocking）

## 任务

1. 带 found 标志实现 `searchBook`。
2. 把选项 3 接入菜单。

## 验收

- m04-a01：搜索书名片段只打印匹配的书。
- m04-a02：某 ID 是另一 ID 的前缀时两者都命中（记录该行为）。
- m04-a03：无匹配时提示"没有找到"，而不是只剩表头的歧义输出。

## 提示 1

`strstr(haystack, needle) != NULL` 就是"包含"。

## 提示 2

三个条件用 || 连接放进一个 if 即可覆盖三个字段。

## 提示 3

复用打印代码或抽一个 `printBookRow` 辅助函数——视图间复制粘贴走样是经典 bug 源。

## 提示 4

空关键字会匹配一切（`strstr(x, "") == x`）。决定是否提前拒绝。

## 提示 5

参考：`business.c::searchBook`。

## 下一项压力

系统能管"拥有"，但管不了"流通"：现在谁手里有书？

## 源码桥接

`business.c::searchBook`

## 证据台账

```text
evidence: code_evidence
source: business.c::searchBook
rationale: 成熟搜索用 strstr 扫描三字段并用 found 标志。
```

## 完成结论

（待评审填写）
