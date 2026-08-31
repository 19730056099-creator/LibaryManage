---
artifact_id: architecture
language: zh-CN
---

# 架构

## 系统上下文

这是一个单进程、单用户的 C 命令行程序：stdin → 菜单 → 业务函数 → 全局内存数组 → 两个文本文件。没有网络、数据库或并发线程。`books.txt` 和 `borrows.txt` 相对于当前工作目录解析，而不是相对于源码目录。

仓库没有头文件。`main.c` 直接 include 两个实现文件，所以概念上可以分为 UI、业务、数据三个边界，但编译时它们会组成同一个翻译单元。

## 组件

- **UI：** `main.c::displayMenu`、`displayHelp`、`main`。它读取文本、用 `strcspn` 去换行、用 `atoi` 解析，并根据返回值打印消息。
- **业务：** `business.c::addBook`、`listAllBooks`、`searchBook`、`updateBook`、`deleteBook`、`borrowBook`、`returnBook`、`listAllBorrows`。它直接改变全局数组，并在成功变更后保存。
- **数据与工具：** `data_mgr.c::Book`、`BorrowRecord`、`loadData`、`saveData`、`getCurrentDate`、`findBookIndex`、`findBorrowIndex`。它定义数据模型、文件格式、线性查找和日期字符串。

## 数据流

```text
books.txt ──loadData──▶ books[MAX_BOOKS]
                           │
                           ├── business.c 读/改 ──saveData──▶ books.txt
                           │
borrows.txt ─loadData──▶ borrows[MAX_BORROWS]
                           │
                           └── business.c 借还 ──saveData──▶ borrows.txt
```

图书行格式是 `id|title|author|quantity|available`；借阅行格式是 `bookId|borrower|borrowDate|returnDate|returned`。`strtok` 会直接改写读入缓冲区。

## 控制流

`main()` 先调用 `initSystem()`，然后执行 `do { displayMenu(); fgets(...); atoi(...); switch (...) } while (choice != 0)`。每个 case 收集参数并调用业务函数。添加、修改、删除、借书、还书会在业务函数内调用 `saveData()`；退出分支再次调用 `saveAllData()`。

## 关键决策

| 决策 | 代码机制 | 应对的压力 | 教学处理 |
|---|---|---|---|
| 固定容量数组 | `Book books[MAX_BOOKS]`、`BorrowRecord borrows[MAX_BORROWS]` 与计数器 | 不引入 malloc/链表即可工作 | 先用数组，容量压力留到末阶段 |
| 双库存字段 | 借书减少 `available`，还书增加它；`quantity` 表示总量 | 区分总馆藏和在架副本 | 先观察不变量，再学习保护 |
| 删除时前移 | `deleteBook` 将后续结构体左移，再减少 `bookCount` | 保持有效元素连续 | 对比链表但不提前引入 |
| 全量覆写 | `saveData()` 以 `w` 模式写出全部记录 | 简单实现跨重启保存 | 原子替换留到未覆盖的扩展 |
| 管道符文本 | `fprintf` 写行，`strtok` 分字段 | 无第三方依赖且可查看 | 先接受格式限制，后处理坏行 |
| 直接包含 `.c` | `main.c` 包含实现文件 | 快速组合小项目 | 末尾讨论头文件化，不提前重构 |
| 线性查找 | `findBookIndex`、`findBorrowIndex` 顺序扫描 | 小容量下最短 | 不为未出现的规模建立索引 |

## 证据台账

```text
evidence: code_evidence
source: main.c::main
rationale: do-while/switch 菜单和退出保存完整展示了控制流。
```

```text
evidence: code_evidence
source: main.c::data_mgr.c::business.c includes
rationale: main.c 的两个源文件 include 证明了概念分层存在，但当前不是头文件接口分层。
```

```text
evidence: code_evidence
source: data_mgr.c::saveData
rationale: saveData 以 w 模式完整写出两组数组，证明了每次变更全量保存的机制。
```

```text
evidence: teaching_inference
confidence: medium
source: main.c, business.c, data_mgr.c
rationale: 把三个源文件讲成 UI/业务/数据三层有助于追踪责任，但仓库没有正式架构文档或头文件来声明这些层。
```
