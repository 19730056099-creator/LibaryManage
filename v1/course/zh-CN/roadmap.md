---
artifact_id: roadmap
language: zh-CN
---

# 重构路线

## 路线原则

- 按工程压力排序，而非文件顺序或提交历史（本项目无历史可考）。
- 每个阶段都必须可运行，并能用上一阶段的局限来解释。
- 成熟实现是参考桥接，不是唯一正确解法。

## 里程碑总览

| ID | 文件 | 目标（可观察结果） | 引入的新压力 |
|---|---|---|---|
| milestone-01 | `01-minimal-value.md` | 菜单驱动程序：能添加一本书并列出静态数组中的图书 | 写死的演示数据没用；用户输入必须变成数据 |
| milestone-02 | `02-crud-validation.md` | 完整 CRUD：ID 唯一性校验、删除即前移 | 重复 ID 和过期条目会摧毁列表的可信度 |
| milestone-03 | `03-durability.md` | 数据重启不丢：保存到/加载自管道符分隔文本文件 | 内存状态退出即消失 |
| milestone-04 | `04-search.md` | 按 id/title/author 子串搜索 | 图书变多后靠肉眼翻列表不可行 |
| milestone-05 | `05-borrow-return.md` | 借还流程：quantity 与 available 的不变量 + 带日期记录 | "拥有"和"在架"是两回事 |
| milestone-06 | `06-robustness.md` | 加固输入、缺文件、容量上限与更新语义 | 真实用户会乱输；磁盘会丢文件 |

## 覆盖范围

覆盖三个源文件的全部行为：菜单/界面（`main.c`）、业务规则（`business.c`）、持久化与工具（`data_mgr.c`）。仓库自身范围内无未覆盖部分。

## 教学性推断

```text
evidence: teaching_inference
confidence: high
rationale: 阶段顺序（CRUD → 持久化 → 搜索 → 借还 → 健壮性）是为教学压力而设计，并非声称这是作者的真实开发时间线。
source: main.c, business.c, data_mgr.c
```

```text
evidence: teaching_inference
confidence: medium
rationale: 设置 milestone-06 是因为成熟代码已有部分加固（strcspn 去换行、留空保留原值更新、MAX 上限），但仍留有缺口（atoi 把乱输入当 0、无重复借阅防护）。
source: main.c::case 1, business.c::updateBook, data_mgr.c::loadData
```
