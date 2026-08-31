---
artifact_id: milestone-05
language: zh-CN
---

# 里程碑

milestone_id: milestone-05
competency_id: language.c.file-io
competency_id: language.c.structs-strings
competency_id: language.c.time-format
competency_id: project.delimited-persistence
competency_id: domain.borrow-inventory
foundation_id: foundation-03
acceptance_id: m05-a01
acceptance_id: m05-a02
acceptance_id: m05-a03
acceptance_id: m05-a04
practice_id: m05-p01
manual_action_id: m05-manual-01
ai_boundary_id: m05-ai-01
transfer_check_id: m05-transfer-01
reappears_in: milestone-06
command: gcc -std=c11 -Wall -Wextra -pedantic main.c -o library_m05

## 当前版本

M04 能找到图书；M05 维护总量 `quantity`、在架量 `available` 和 `BorrowRecord`，并把借阅记录保存到 `borrows.txt`。

## 上一版本解决了什么

M04 降低了找书成本，但“有这本书”不代表现在有副本，也没有借阅人的追踪信息。

## 用户遇到的新问题

借出后可用库存必须减少但不能为负；归还必须对应一个未归还记录；重启后系统仍需知道谁借了什么。

## 本阶段引入什么

引入 `BorrowRecord`、`findBorrowIndex`、`time/localtime` 生成日期，以及第二个分隔文件。核心不变量是 `0 <= available <= quantity`。

## 目标

完成正常借阅/归还闭环，并让书目库存与借阅记录保持可解释、可恢复。

## 可观察结果

借出一本可用书后 `available` 减 1 并出现未归还记录；归还后日期和状态更新、库存加 1；库存为 0 时借阅失败。

## 本阶段解决什么

把目录管理扩展为可追踪的库存和借阅关系，并跨重启保存两种状态。

## 范围

- 借阅前查找图书、检查 `available` 和记录容量。
- 创建带借阅日期的记录，归还时设置 return date 和 `returned`。
- 保存/加载 `books.txt` 与 `borrows.txt`，展示借阅状态。

## 暂时不解决什么

不处理坏数字、坏行、日期格式校验、并发借阅、逾期计算或删除仍在借图书；M06 再明确这些边界。

## 前置知识

完成 F03；复用 M02 的数组与 M03 的文本持久化。`language.c.time-format` 在本阶段即时讲解，不要求提前补给。

## 首次触摸

画出 quantity=2、available=2 的一行书；借一次后画出 available=1 和一条未归还记录，归还后再更新两处。随后才写函数，让不变量先成为可见状态。

## 任务

1. 增加 `BorrowRecord` 和借阅记录数组/计数器。
2. 实现借阅：验证图书和库存、减少 available、生成日期、添加记录。
3. 实现归还：定位未归还记录、增加 available、写回日期和状态。
4. 保存并重新加载两个文件，测试库存为 0、重复归还和重启。

## AI 使用边界

AI 可以帮你画状态表、解释 `time/localtime` 或设计借还测试。你必须亲自维护两个数组的关系、写至少一个库存检查、运行借/还/重启场景，并解释每个字段何时改变。AI 不能替你选择数据一致性策略。

## 理解与迁移检查

把一本书的总量从 2 改成 3，借还两次，写出每一步 `quantity`、`available`、记录状态；再讨论为什么 `returned` 已为 1 的记录不能再次归还。

## 验收

```text
acceptance_id: m05-a01
```
可用库存大于 0 时借阅成功，库存减 1，记录含有效日期且状态为未归还。

```text
acceptance_id: m05-a02
```
库存为 0 或图书不存在时借阅失败；不能产生半条记录。

```text
acceptance_id: m05-a03
```
匹配的未归还记录可归还一次，库存加 1、归还日期出现、状态变为已归还；重复归还失败。

```text
acceptance_id: m05-a04
```
退出重启后两类记录仍可列出，且至少验证 `0 <= available <= quantity`；提交状态表和 AI 使用记录。

## 提示 1

先只追踪一条书：借前、借后、还后分别写出两个库存数和记录状态。

## 提示 2

借阅需要同时找到 `Book` 和可用库存；归还需要找到 bookId、borrower 且 `returned == 0` 的记录。

## 提示 3

借阅顺序应是检查 → 减库存 → 填记录 → 增计数 → 保存；任何失败分支不要只改变一半状态。

## 提示 4

`getCurrentDate` 可以封装日期格式；先把日期当字符串保存，避免把时间库扩展成新的持久化模型。

## 提示 5

完整参考可展示 `BorrowRecord` 字段和借还状态转移；你仍须改数量场景、测试重复归还并证明不变量。

## 下一阶段为什么会出现

正常场景能工作，但 `atoi` 会吞掉非数字，样例文件有短行，删除借出书也会留下关联问题。M06 将失败变成显式策略。

## 源码桥接

对照 `data_mgr.c::BorrowRecord`、`data_mgr.c::findBorrowIndex`、`data_mgr.c::getCurrentDate` 和 `business.c::borrowBook`/`returnBook`。

## 证据台账

```text
evidence: code_evidence
source: data_mgr.c::BorrowRecord
rationale: BorrowRecord 定义了书号、借阅人、借阅/归还日期和 returned 状态。
```

```text
evidence: code_evidence
source: business.c::borrowBook, business.c::returnBook
rationale: 两个函数分别减少/增加 available，并创建或完成借阅记录。
```

```text
evidence: code_evidence
source: data_mgr.c::getCurrentDate
rationale: getCurrentDate 使用 time/localtime 和固定格式生成日期字符串。
```

## 完成结论

通过四项验收、直接状态练习和重启证据后，评审可标记 M05 `passed`。健壮性边界仍留给 M06。
