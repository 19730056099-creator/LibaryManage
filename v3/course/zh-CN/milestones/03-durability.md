---
artifact_id: milestone-03
language: zh-CN
---

# 里程碑

milestone_id: milestone-03
competency_id: language.c.file-io
competency_id: language.c.structs-strings
competency_id: project.delimited-persistence
foundation_id: foundation-03
acceptance_id: m03-a01
acceptance_id: m03-a02
acceptance_id: m03-a03
acceptance_id: m03-a04
practice_id: m03-p01
manual_action_id: m03-manual-01
ai_boundary_id: m03-ai-01
transfer_check_id: m03-transfer-01
reappears_in: milestone-05, milestone-06
command: gcc -std=c11 -Wall -Wextra -pedantic main.c -o library_m03

## 当前版本

M02 的内存 CRUD 加上 `books.txt`：成功变更后把图书数组写成管道符行，启动时再读回。

## 上一版本解决了什么

M02 让单次运行中的目录可维护，但进程结束后所有状态消失。

## 用户遇到的新问题

图书管理员第二天重新打开程序仍需要看到昨天的目录；仅靠内存不满足“管理”的实际价值。

## 本阶段引入什么

引入 `fopen`、`fgets`、`fprintf`、`fclose`，以及 `id|title|author|quantity|available` 的简单行格式。先只持久化图书，不把借阅记录一起塞入。

## 目标

让添加、修改、删除后的图书数据在重新启动后仍可恢复。

## 可观察结果

运行程序添加一本书并退出；重新启动后列表仍显示它。打开 `books.txt` 能看到一行与字段顺序一致的文本。

## 本阶段解决什么

解决图书目录的跨进程存活问题，建立“内存模型 ↔ 文本表示”的边界。

## 范围

- 启动时加载 `books.txt`，成功变更后全量覆写。
- 用 `strtok` 拆分五个字段，并把数值字段转成整数。
- 文件打不开时从空目录开始，错误信息可观察。

## 暂时不解决什么

不持久化 `borrows.txt`，不处理短行、超长字段、正文含 `|`、原子写入或恢复半写文件；这些放到 F03/M06 的压力中。

## 前置知识

先完成 `foundation-03` 的文件读写与 `strtok` 练习；需要 M02 的 `Book` 数组和 CRUD。

## 首次触摸

先把一条内存 `Book` 用 `fprintf` 写进临时文件，关闭后重新用 `fgets` 打印原文；再加上 `strtok` 恢复字段。最后才把读写接入菜单，观察重启前后列表的差异。

## 任务

1. 设计并实现图书行格式，明确五个字段的写入/读取顺序。
2. 启动时加载文件到数组；每次成功 add/update/delete 后保存全部图书。
3. 在隔离的 `student/milestone-03/` 目录测试“添加 → 退出 → 重启 → 列表”。
4. 故意删除数据文件，记录程序如何处理文件不存在。

## AI 使用边界

AI 可以解释文件模式、`strtok` 的状态或帮助画序列图。你必须亲自写 `load`/`save` 循环、选择字段顺序、检查 `fopen`、运行两次进程并查看文件；不能只提交 AI 生成的持久化代码。

## 理解与迁移检查

把保存格式中的 `available` 暂时改名为 `on_shelf`（只改自己的程序），列出需要同步修改的写入和读取位置；再加入一条少字段行，说明为什么不能把它当作合法 `Book`。

## 验收

```text
acceptance_id: m03-a01
```
无警告编译运行，程序在正确工作目录找到自己的 `books.txt`。

```text
acceptance_id: m03-a02
```
添加至少两本书、退出并重新启动，列表恢复相同的字段和数量。

```text
acceptance_id: m03-a03
```
直接查看 `books.txt`，每条合法记录的字段顺序和程序读取顺序一致；文件不存在时不会解引用空文件指针。

```text
acceptance_id: m03-a04
```
提交两次进程的运行记录、文件内容、读写循环解释和迁移回答。

## 提示 1

先回答：如果写入顺序是 ID、书名、作者、总量、可用量，读取必须按什么顺序调用 `strtok`？

## 提示 2

`fopen("books.txt", "r")` 失败可以表示首次运行；不要把 `FILE *` 继续传给 `fgets`。

## 提示 3

保存时遍历 `[0, bookCount)`；加载每一行时只在字段足够时填入一个数组槽位。

## 提示 4

把持久化分成两个边界：`saveBooks` 负责数组到文本，`loadBooks` 负责文本到数组；先在临时文件上验证。

## 提示 5

若明确请求完整参考，先实现五字段的 `fprintf`/`fgets`/`strtok` 循环；仍须修改一个字段名、重启验证并说明短行风险。

## 下一阶段为什么会出现

持久化目录可以变大，而用户还要逐行寻找目标。M04 将复用数组遍历，用 `strstr` 支持多字段搜索。

## 源码桥接

对照 `data_mgr.c::loadData` 的 `strtok` 链和 `saveData` 的 `fprintf` 格式。参考实现还同时读写借阅文件；本阶段先隔离图书文件压力。

## 证据台账

```text
evidence: code_evidence
source: data_mgr.c::loadData
rationale: loadData 打开 books.txt，逐行 strtok 五个字段并填充 books 数组。
```

```text
evidence: code_evidence
source: data_mgr.c::saveData
rationale: saveData 用 fprintf 将每本书写成 id|title|author|quantity|available 行，并以 w 模式全量覆写。
```

```text
evidence: document_evidence
source: books.txt::lines 1-3
rationale: 样例前三行展示了合法图书记录的五字段顺序，可用来核对序列化格式。
```

## 完成结论

通过重启验收、文件检查和直接文件 I/O 练习证据后，评审可标记 M03 `passed`；短行和坏字段不在此阶段强行解决。
