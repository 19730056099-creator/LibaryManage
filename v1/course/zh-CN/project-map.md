---
artifact_id: project-map
language: zh-CN
---

# 项目地图

## 项目目的

LibaryManage 是一个命令行图书管理系统（`code_evidence`：`main.c::main`）。它面向单机使用者，提供图书入库、查询、修改、删除、借阅、归还和借阅记录查看功能，并把数据持久化到 `books.txt` 与 `borrows.txt` 两个管道符分隔的文本文件中（`code_evidence`：`data_mgr.c::loadData/saveData`）。

## 核心用户路径

1. 启动程序，系统从 `books.txt` / `borrows.txt` 加载数据（`data_mgr.c::initSystem → loadData`）。
2. 用户在菜单中选择操作（`main.c::displayMenu`）。
3. 典型旅程：添加图书 → 查看列表 → 借书（库存 `available` 减一，生成借阅记录）→ 还书（`available` 加一，记录标记已还）→ 退出时保存（`business.c::borrowBook/returnBook`、`main.c::case 0`）。

## 子系统

| 子系统 ID | 职责 | 输入 | 输出 | 依赖 | 源码位置 |
|---|---|---|---|---|---|
| ui-menu | 菜单展示与输入收集 | stdin | 函数调用 | business | `main.c` |
| domain-business | 图书 CRUD 与借还规则 | 函数参数 | 内存数组变更 + 保存 | data-mgr | `business.c` |
| data-store | 结构体定义、数组存储、文件加载/保存、日期与查找工具 | 文本文件 / 内存数组 | 内存状态 / 文本文件 | 无 | `data_mgr.c` |

## 数据流

- 文件 → `strtok` 按 `|` 解析 → `Book books[]` / `BorrowRecord borrows[]` 全局数组。
- 业务函数修改数组 → 每次成功操作后立即 `saveData()` 全量覆写两个文件。

## 证据台账

```text
evidence: code_evidence
source: main.c::main
rationale: do-while 菜单循环 + switch 分发到业务函数，fgets 读入并 strcspn 去换行。
```

```text
evidence: code_evidence
source: data_mgr.c::Book,BorrowRecord
rationale: 固定上限 MAX_BOOKS/MAX_BORROWS=1000 的静态数组存储；Book 含 quantity/available 双计数。
```

```text
evidence: code_evidence
source: data_mgr.c::saveData
rationale: 管道符分隔的全量覆写式持久化，无事务保护。
```

```text
evidence: teaching_inference
confidence: high
rationale: 每次写操作后立即 saveData，说明作者关注崩溃/强退时的数据丢失，但选择的是最简单的全量重写方案。
source: business.c::addBook,updateBook,deleteBook,borrowBook,returnBook
```

## 未覆盖范围

- 未运行/编译验证（静态分析结论）；验证命令：`gcc main.c -o library && ./library`。
- 无 README、无测试、无构建脚本、无版本历史可考。
- `books.txt`/`borrows.txt` 为示例数据文件，不作为代码证据。
