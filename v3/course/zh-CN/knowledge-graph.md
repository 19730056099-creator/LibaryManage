---
artifact_id: knowledge-graph
language: zh-CN
---

# 知识图谱

## 概念依赖

```text
tooling.c.gcc-build ───────────────────────────────┐
language.c.c-control-input ────────────────────────┤
language.c.structs-strings ──▶ language.c.arrays-pointers ──▶ project.array-crud
          │                    │                         │
          └──▶ language.c.file-io ──▶ project.delimited-persistence ──┘
                                                              │
                                      project.array-crud ──────┴──▶ domain.borrow-inventory
language.c.time-format ───────────────────────────────────────▶ domain.borrow-inventory
language.c.c-control-input ──▶ project.input-validation
language.c.file-io + project.delimited-persistence ──▶ project.defensive-parsing
 domain.borrow-inventory ──▶ project.borrow-delete-policy
```

这是项目需要的能力图，不是学习者水平评价。基础知识只在首次产生压力前补给；业务概念在里程碑中通过行为引入。

## 学习优先级

| competency_id | 类别 | 最小可观察能力 | 首次需要 | 阻塞情况 |
|---|---|---|---|---|
| `tooling.c.gcc-build` | tooling | 用 gcc 编译 `main.c` 并在正确工作目录运行 | milestone-01 | 阻塞 |
| `language.c.c-control-input` | language | 用 `fgets`、`atoi`、`do-while`、`switch` 完成菜单输入 | milestone-01 | 阻塞 |
| `language.c.structs-strings` | language | 操作含定长 char 数组的结构体 | milestone-01 | 阻塞 |
| `language.c.arrays-pointers` | language | 遍历结构体数组并按下标前移删除 | milestone-01 | 阻塞 |
| `language.c.file-io` | language | 用 `fopen/fgets/fprintf/fclose` 读写文本 | milestone-03 | 阻塞 |
| `language.c.time-format` | language | 用 `time/localtime` 生成 `YYYY-MM-DD` | milestone-05 | 非阻塞，即时补给 |
| `project.array-crud` | project_concept | 在固定容量数组上实现唯一 ID 的增列改删 | milestone-02 | 里程碑引入 |
| `project.delimited-persistence` | project_concept | 写出 `|` 分隔行并用 `strtok` 恢复字段 | milestone-03 | F03/里程碑引入 |
| `domain.borrow-inventory` | domain | 保持 `0 <= available <= quantity` 并追踪借阅人 | milestone-05 | 里程碑引入 |
| `project.input-validation` | project_concept | 拒绝非数字和越界数量，而非静默接受 `atoi` | milestone-06 | 里程碑引入 |
| `project.defensive-parsing` | project_concept | 校验字段数、长度和数值后再接受文件行 | milestone-06 | 里程碑引入 |
| `project.borrow-delete-policy` | project_concept | 对有未归还记录的删除定义明确策略 | milestone-06 | 里程碑引入 |

## 源码位置

- `tooling.c.gcc-build`, `language.c.c-control-input`：`main.c::main`。
- `language.c.structs-strings`：`data_mgr.c::Book`, `data_mgr.c::BorrowRecord`, `business.c::addBook`。
- `language.c.arrays-pointers`：`data_mgr.c::books`, `data_mgr.c::findBookIndex`, `business.c::deleteBook`。
- `language.c.file-io`：`data_mgr.c::loadData`, `data_mgr.c::saveData`。
- `language.c.time-format`：`data_mgr.c::getCurrentDate`。
- `project.array-crud`：`business.c::addBook`, `updateBook`, `deleteBook`, `listAllBooks`。
- `project.delimited-persistence`：`data_mgr.c::loadData`, `saveData` 中的 `strtok` 与 `fprintf`。
- `domain.borrow-inventory`：`business.c::borrowBook`, `returnBook`, `data_mgr.c::findBorrowIndex`。
- 健壮性概念的压力来自 `main.c::atoi`、`data_mgr.c::loadData` 和 `business.c::deleteBook` 的现有行为。

## 最小练习

1. 写一个读取一行 ID、复制到 `Item.code` 再打印的程序。
2. 创建三个结构体，删除下标 1，证明剩余元素顺序不变。
3. 将 `B001|Title|2` 写入临时文件，再用 `fgets` + `strtok` 读出字段。
4. 画出 quantity=3、借出两次、归还一次后的库存和记录状态。

## 螺旋复现与理解深度

下列是课程对能力的计划性复现，不是学习者已经掌握的证据。`practice_depth` 表示本路线希望达到的阶段深度，`reappears_in` 表示再次使用位置。

competency_id: tooling.c.gcc-build
practice_depth: touched
reappears_in: milestone-01
competency_id: language.c.c-control-input
practice_depth: explained
reappears_in: milestone-01, milestone-06
competency_id: language.c.structs-strings
practice_depth: explained
reappears_in: milestone-01, milestone-02, milestone-03, milestone-05, milestone-06
competency_id: language.c.arrays-pointers
practice_depth: explained
reappears_in: milestone-01, milestone-02, milestone-04, milestone-05
competency_id: language.c.file-io
practice_depth: debugged
reappears_in: milestone-03, milestone-06
competency_id: language.c.time-format
practice_depth: touched
reappears_in: milestone-05
competency_id: project.array-crud
practice_depth: debugged
reappears_in: milestone-02, milestone-04, milestone-06
competency_id: project.delimited-persistence
practice_depth: debugged
reappears_in: milestone-03, milestone-05, milestone-06
competency_id: domain.borrow-inventory
practice_depth: transferred
reappears_in: milestone-05, milestone-06
competency_id: project.input-validation
practice_depth: transferred
reappears_in: milestone-06
competency_id: project.defensive-parsing
practice_depth: transferred
reappears_in: milestone-06
competency_id: project.borrow-delete-policy
practice_depth: explained
reappears_in: milestone-06

```text
evidence: code_evidence
source: data_mgr.c::Book, data_mgr.c::BorrowRecord
rationale: 两个结构体定义了图书字段、库存字段和借阅记录字段，形成项目概念的核心数据模型。
```

```text
evidence: code_evidence
source: main.c::main, data_mgr.c::loadData, business.c::borrowBook
rationale: 输入、解析、业务状态变化分别在这些路径中出现，支持按依赖顺序安排能力。
```
