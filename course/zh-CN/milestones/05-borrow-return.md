---
artifact_id: milestone-05
language: zh-CN
---

# 里程碑

milestone_id: milestone-05

## 目标

实现借还流程：引入第二个数据结构 `BorrowRecord`、quantity 与 available 的不变量、当前日期，以及两个文件的完整持久化。

## 可观察结果

- 选项 6 借书：`available` 减一，`borrows.txt` 追加一条带当天日期的记录。
- 选项 7 按（书 ID + 借阅人）还书：`available` 加一，记录标记已还并写入归还日期。
- 选项 8 列出记录，状态为 Borrowing/Returned。
- 两个文件重启后都能完整恢复。

## 设计压力

"拥有"不等于"在架"。系统必须回答"现在谁手里有什么"，且永远不能借到负数。

## 范围

- `BorrowRecord {bookId, borrower, borrowDate, returnDate, returned}` + 平行数组。
- `borrowBook`、`returnBook`、`listAllBorrows`、`findBorrowIndex`、`getCurrentDate`。
- 把 `borrows.txt` 纳入 load/save。

## 约束

- 允许同一人借同一种书多本（成熟行为；记录下来）。
- 还书只匹配未归还的记录。

## 前置知识

- competency_id: domain.borrow-inventory（blocking）
- competency_id: project.delimited-persistence（blocking）

## 任务

1. 添加结构体、计数器与 `getCurrentDate`（`localtime`、`%04d-%02d-%02d`）。
2. `borrowBook`：检查书存在 且 available > 0 且容量未满；减库存；追加记录；保存。
3. `returnBook`：找到未归还记录；加库存；写 returnDate 和 returned = 1；保存。
4. 在 load/save 中同时处理借阅记录。

## 验收

- m05-a01：数量为 2 → 连续借两次成功，第三次失败并提示缺书。
- m05-a02：还一本后 available 回到 1，记录显示 Returned 及日期。
- m05-a03：给没有未还记录的人还书会优雅失败。
- m05-a04：重启后两个文件的状态完全保留。

## 提示 1

双计数器一条规则：`quantity` 只被 add/update 改动；`available` 只被借还改动。除添加时外不要互相推算。

## 提示 2

`findBorrowIndex` 必须过滤 `returned == 0`，否则会把已还记录再"还"一次。

## 提示 3

`getCurrentDate`：`time(NULL)` → `localtime` → `sprintf(dateStr, "%04d-%02d-%02d", tm->tm_year+1900, tm->tm_mon+1, tm->tm_mday)`。

## 提示 4

未还记录的 returnDate 写空字段，显示时把空串当作"未归还"。

## 提示 5

参考：`business.c::borrowBook/returnBook/listAllBorrows`、`data_mgr.c::findBorrowIndex/getCurrentDate`。

## 下一项压力

真实用户会在每个提示符乱输、删文件、超上限——该加固了。

## 源码桥接

`business.c::borrowBook`, `business.c::returnBook`, `business.c::listAllBorrows`, `data_mgr.c::BorrowRecord`, `data_mgr.c::findBorrowIndex`, `data_mgr.c::getCurrentDate`

## 证据台账

```text
evidence: code_evidence
source: business.c::borrowBook
rationale: 存在性检查 + available > 0 + 容量检查先于任何变更。
```

```text
evidence: teaching_inference
confidence: medium
rationale: 成熟代码没有重复借阅防护——同一人可把所有副本借光；标记为 milestone-06 讨论素材。
source: business.c::borrowBook
```

## 完成结论

（待评审填写）
