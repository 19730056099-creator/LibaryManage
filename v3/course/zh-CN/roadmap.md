---
artifact_id: roadmap
language: zh-CN
---

# 重构路线

## 路线原则

- 按“上一版本可观察价值 → 新压力 → 最小变化”排序，不按目录或提交顺序排序。
- 每个阶段先让学习者得到可运行结果，再用成熟源码做桥接。
- 参考实现是证据和对照，不是唯一答案；它本身也保留了输入与文件校验缺口。
- 后续前置知识在首次使用前即时补给，不把 `strtok`、借阅和健壮性一次塞入第一阶段。
- 所有运行数据使用学习 workspace 的副本，避免污染 `/home/mengzhouyi/LibaryManageSrc`。

## 里程碑总览

| ID | 文件 | 可观察目标 | 新压力 | 主要源码桥接 |
|---|---|---|---|---|
| `milestone-01` | `01-minimal-value.md` | 菜单中添加并列出内存图书 | 写死演示不能管理 | `main.c::main`, `data_mgr.c::Book`, `business.c::addBook` |
| `milestone-02` | `02-crud.md` | 内存增列改删和唯一 ID | 错误条目不能维护 | `business.c::updateBook`, `deleteBook` |
| `milestone-03` | `03-durability.md` | `books.txt` 保存并启动加载 | 退出会丢失状态 | `data_mgr.c::loadData`, `saveData` |
| `milestone-04` | `04-search.md` | 按 ID/书名/作者子串搜索 | 肉眼扫描太慢 | `business.c::searchBook`, `main.c::case 3` |
| `milestone-05` | `05-borrow-return.md` | 借还、库存、日期和记录 | 总量不等于可借量 | `business.c::borrowBook`, `returnBook`, `data_mgr.c::BorrowRecord` |
| `milestone-06` | `06-robustness.md` | 加固输入、坏行和删除策略 | 静默坏数据污染状态 | `main.c::atoi`, `data_mgr.c::loadData`, `business.c::deleteBook` |

## 覆盖范围

路线覆盖三个源文件的主行为：菜单输入（`main.c`）、图书/借还业务（`business.c`）和结构体/查找/日期/持久化（`data_mgr.c`），并使用 `books.txt`、`borrows.txt` 作为格式证据。学习者代码始终放在 `student/` 下。

有意不覆盖网络、数据库、并发、账号权限、图形界面和外部库。直接 include `.c` 的构建方式在 M01 解释，头文件化只作为末尾的可选讨论。

## 教学性推断

```text
evidence: teaching_inference
confidence: high
source: main.c, business.c, data_mgr.c
rationale: M01→M02→M03→M04→M05→M06 的顺序是教学重建：每阶段等上一阶段的限制变得可见后再引入主要机制，不是作者真实开发顺序。
```

```text
evidence: teaching_inference
confidence: medium
source: data_mgr.c::saveData, data_mgr.c::loadData, books.txt::lines 4-7, borrows.txt::lines 3-4
rationale: 把样例短行作为 M06 触发材料有代码和数据支持，但仓库没有说明这些行是否是故意的测试夹具。
```
