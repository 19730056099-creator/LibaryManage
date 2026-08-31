---
artifact_id: architecture
language: zh-CN
---

# 架构

## 系统上下文

单进程 C 程序：stdin ↔ 菜单界面 ↔ 全局内存数组 ↔ 两个文本文件。无网络、无数据库、无并发。

## 组件

- `main.c::displayMenu/displayHelp/main` — 表现层：菜单渲染、`fgets` 收集输入、`atoi`/`strcspn` 清洗。
- `business.c::addBook/listAllBooks/searchBook/updateBook/deleteBook/borrowBook/returnBook/listAllBorrows/initSystem/saveAllData` — 业务层。
- `data_mgr.c::Book/BorrowRecord/loadData/saveData/getCurrentDate/findBookIndex/findBorrowIndex` — 数据层与工具函数。

## 数据流

```text
books.txt ──loadData──▶ Book books[1000] ◀──read/write── business.c ◀──calls── main.c
borrows.txt ─loadData─▶ BorrowRecord borrows[1000]
        ▲                                        │
        └────────saveData()（每次写操作后）◀─────┘
```

## 控制流

在 `main()` 中：`do { displayMenu(); fgets; atoi; switch } while (choice != 0)`。每个 case 收集参数、调用业务函数，并根据 0/1 返回值打印成败。

## 关键决策

| 决策 | 机制 | 应对的压力 | 证据中可见的替代方案 |
|---|---|---|---|
| 静态数组 | `Book books[MAX_BOOKS]` + 计数器 `bookCount` | 回避 malloc/链表复杂度 | 链表或动态数组（代码中未出现；teaching_inference: medium） |
| 双计数 quantity/available | 借书减 `available`，还书加回 | 区分总馆藏与在架数量 | 单一计数字段 |
| 删除即前移覆盖 | `deleteBook` 左移元素并 `bookCount--` | 保持数组紧凑 | 软删除（未采用） |
| 每次写操作后全量保存 | 每个变更末尾调用 `saveData()` | 崩溃导致数据丢失 | 仅退出时保存 / 追加日志 |
| 管道符分隔文本 | `fprintf("%s|%s|...")` + `strtok(line,"|")` | 无依赖、人类可读 | CSV/JSON/二进制 |

## 证据台账

```text
evidence: code_evidence
source: data_mgr.c::deleteBook
rationale: 删除采用左移元素而非打墓碑标记，保持遍历顺序稳定。
```

```text
evidence: code_evidence
source: business.c::updateBook
rationale: 更新支持"留空保留原值"；quantity 差额同步到 available 并钳制不小于 0。
```

```text
evidence: teaching_inference
confidence: medium
rationale: 全局数组 + 在 main.c 中直接 #include .c 文件（无头文件）是典型的单二进制教学项目布局。
source: main.c::#include "data_mgr.c"
```

## 未检查项

- 未验证编译警告与运行时行为；`localtime` 的非线程安全在此单线程场景可接受。
- 未测试对损坏文件或缺失字段的容错。
