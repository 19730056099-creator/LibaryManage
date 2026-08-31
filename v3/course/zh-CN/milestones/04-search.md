---
artifact_id: milestone-04
language: zh-CN
---

# 里程碑

milestone_id: milestone-04
competency_id: language.c.arrays-pointers
competency_id: language.c.structs-strings
competency_id: project.array-crud
acceptance_id: m04-a01
acceptance_id: m04-a02
acceptance_id: m04-a03
practice_id: m04-p01
manual_action_id: m04-manual-01
ai_boundary_id: m04-ai-01
transfer_check_id: m04-transfer-01
reappears_in: milestone-05, milestone-06
command: gcc -std=c11 -Wall -Wextra -pedantic main.c -o library_m04

## 当前版本

在 M03 的可持久化目录上，用户可以输入一个关键字，按 ID、书名或作者做子串搜索。

## 上一版本解决了什么

M03 保证目录能跨重启保存，但列表只提供完整扫描。

## 用户遇到的新问题

图书变多后，用户通常只记得标题片段、作者片段或 ID 片段，不应逐行阅读整个列表。

## 本阶段引入什么

引入 `strstr`、found 标志和一次线性扫描；每条记录匹配任一字段就输出。暂不建立索引，因为固定容量和当前规模没有提出这种压力。

## 目标

提供可预测的多字段包含搜索，并保留“不匹配时明确提示”的行为。

## 可观察结果

搜索 `C语言`、某个作者片段和某个 ID 片段分别能命中；搜索不存在的关键字显示没有结果。

## 本阶段解决什么

降低查找目录条目的操作成本，同时让学习者看到复用已有数组遍历的价值。

## 范围

- 对 `id`、`title`、`author` 调用 `strstr`。
- 输出每条记录一次；用 `found` 判断空结果。
- 保持大小写和排序规则简单，不引入索引。

## 暂时不解决什么

不做大小写不敏感、相关性排序、正则表达式、模糊匹配或数据库全文搜索。

## 前置知识

需要 M02 的数组遍历/字符串和 M03 的图书加载；没有新的基础补给单元。

## 首次触摸

先在三个普通字符串上测试 `strstr("C language", "lang")` 和不存在片段的返回值，再把同一判断放入图书循环。先观察 `NULL`/非 `NULL`，再接菜单。

## 任务

1. 添加搜索菜单入口和关键字读取。
2. 遍历有效图书，对三个字段做包含判断。
3. 设计命中计数或 `found` 标志，保证一条书只打印一次。
4. 用 ID、标题、作者、无结果四组输入验证。

## AI 使用边界

AI 可以解释 `strstr` 返回指针的含义或帮你生成四组测试数据。你必须亲自写匹配条件、避免重复输出、运行测试并解释为什么空结果不等于程序崩溃。

## 理解与迁移检查

把搜索范围改成只匹配作者，再恢复三字段；说明条件如何变化。然后增加一个字段 `publisher`，列出要修改的匹配和输出位置。

## 验收

```text
acceptance_id: m04-a01
```
ID、标题、作者片段都能命中正确记录。

```text
acceptance_id: m04-a02
```
不存在关键字有明确空结果；同一记录同时命中多个字段时只输出一次。

```text
acceptance_id: m04-a03
```
提交四组运行记录、核心判断解释和一次迁移修改；搜索不破坏原列表或持久化数据。

## 提示 1

先单独打印 `strstr` 的返回是否为 `NULL`，不要一开始调试菜单。

## 提示 2

一条记录的条件是 `id 命中 || title 命中 || author 命中`；命中后只打印一次。

## 提示 3

初始化 `found = 0`，每次输出后置 1，循环结束仍为 0 才打印无结果。

## 提示 4

搜索函数只负责遍历和输出，菜单只负责读关键字和调用它；不要复制一份数组。

## 提示 5

完整参考可只给出 `strstr` 条件和 found 模式；你仍须改变字段范围、运行空结果并解释线性成本。

## 下一阶段为什么会出现

“找到书”仍不知道是否有可借副本，也不知道谁借走了它。M05 在现有书目旁引入库存和借阅记录。

## 源码桥接

对照 `business.c::searchBook` 的三个 `strstr` 条件和 `main.c::case 3` 的输入路径；注意它复用内存数组而没有索引。

## 证据台账

```text
evidence: code_evidence
source: business.c::searchBook
rationale: searchBook 对 id、title、author 使用 strstr，并用 found 处理空结果。
```

```text
evidence: code_evidence
source: main.c::case 3
rationale: 菜单 case 3 读取关键字并调用 searchBook，证明搜索从用户输入进入业务层。
```

## 完成结论

通过三项验收和直接搜索练习后，评审可标记 M04 `passed`；索引等规模机制继续延后。
