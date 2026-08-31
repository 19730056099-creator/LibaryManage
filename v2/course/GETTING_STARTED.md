---
artifact_id: getting-started
language: zh-CN
---

# 学习指南

（本文件为中英双语入口；英文版见 `en/` 目录下同名结构。）

## 课程是什么

通过从零重建 [LibaryManage](../../../LibaryManage)（一个 C 语言命令行图书管理系统，约 570 行、3 个源文件），掌握：C 结构体与字符串处理、数组 CRUD 与前移删除、管道符分隔文本持久化（strtok）、库存不变量（quantity/available）与借还流程。参考仓库只读，你的代码写在 `student/`。

## 文件总览与阅读顺序

1. `zh-CN/readiness.md` — 先做校准，决定是否需要补给单元。
2. （如创建）`zh-CN/foundations/FNN-*.md` — 补齐缺口。
3. `zh-CN/milestones/01-minimal-value.md` → `06-robustness.md` — 按序重建。
4. `zh-CN/project-map.md` / `architecture.md` / `knowledge-graph.md` / `roadmap.md` — 需要对照成熟设计时查阅。
5. `course/GETTING_STARTED.md` — 本文件。

## 各文件的用途速查

| 文件 | 用途 | 何时读 |
|---|---|---|
| readiness.md | 能力校准与差距决策 | 开始前必读 |
| roadmap.md | 6 个里程碑总览 | 开课时浏览一次 |
| milestones/NN-*.md | 每个里程碑的目标/任务/验收/5 级提示 | 做对应阶段时 |
| foundations/FNN-*.md | 个性化前置补给 | 校准显示有缺口时 |
| project-map.md | 子系统与证据台账 | 想知道"成熟代码里在哪"时 |
| architecture.md | 架构与关键决策 | 对照自己设计时 |
| knowledge-graph.md | 能力依赖图与最小练习 | 规划学习路径时 |

## 使用规则

- **回答校准问题**：直接在对话中回答 readiness.md 的 Q1–Q5，或说 "assume_beginner"，或说 "waive" 跳过。
- **开始单元**：说"开始 milestone-01"（或当前单元）。
- **请求提示**：卡住时说"提示"——默认给最低级别提示，可指定"提示 3"等更深级别。
- **提交评审**：完成验收项后说"请评审"，我会对照验收标准给出 verdict 并写入 `reviews/`。
- **查看进度**：随时问"我的进度"。
- 后续补给单元按需即时引入，不会提前堆给你。

## 现在就开始

当前状态：**等待能力校准**。你的第一个动作：

> 打开 `course/zh-CN/readiness.md`，回答 Q1–Q5（或直接回复 "assume_beginner"）。

完成后我会生成需要的补给单元（如有），并把 milestone-01 设为当前任务。
