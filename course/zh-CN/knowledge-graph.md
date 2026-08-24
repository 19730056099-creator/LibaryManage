---
artifact_id: knowledge-graph
language: zh-CN
---

# 知识图谱

## 概念依赖

```text
tooling.c.gcc-build
language.c.structs-strings ──▶ language.c.arrays-pointers
language.c.arrays-pointers ──▶ project.array-crud
language.c.arrays-pointers ──▶ language.c.file-io
language.c.file-io + language.c.structs-strings ──▶ project.delimited-persistence
project.array-crud ──▶ domain.borrow-inventory
```

## 学习优先级

| competency_id | 类别 | 最小能力 | 影响里程碑（候选） | 是否阻塞 |
|---|---|---|---|---|
| tooling.c.gcc-build | tooling | 用 gcc 编译多文件 C 程序并在工作目录运行二进制，使相对路径的文件读写生效 | milestone-01 | 是 |
| language.c.structs-strings | language | 定义含 char 数组字段的结构体；使用 strcpy/strcmp/strlen/strstr；按下标访问结构体 | milestone-01 | 是 |
| language.c.arrays-pointers | language | 维护"结构体数组 + 计数器"；删除时前移元素；通过全局数组共享数据 | milestone-01, milestone-02 | 是 |
| language.c.file-io | language | 用 fopen/fgets/fprintf/fclose 打开、读、写文本文件 | milestone-03 | 是 |
| project.array-crud | project_concept | 在定容数组上实现带唯一 ID 查找的增列改删 | milestone-02 | 是 |
| project.delimited-persistence | project_concept | 把记录序列化为管道符分隔行，并用 strtok 解析回来 | milestone-03 | 是 |
| domain.borrow-inventory | domain | 维护总量 quantity 与在架 available 的不变量，借还生成带日期记录 | milestone-05 | 是 |

## 源码位置

- gcc-build：整个仓库；入口 `main.c::main`。
- structs-strings：`data_mgr.c::Book/BorrowRecord`、`business.c::addBook`。
- arrays-pointers：`data_mgr.c::findBookIndex`、`business.c::deleteBook`。
- file-io：`data_mgr.c::loadData/saveData`。
- array-crud：`business.c::addBook/updateBook/deleteBook/listAllBooks/searchBook`。
- delimited-persistence：`data_mgr.c::loadData/saveData`（`strtok`、`fprintf`）。
- borrow-inventory：`business.c::borrowBook/returnBook`、`findBorrowIndex`。

## 最小练习

- gcc-build：编译并运行一个"主文件 + 辅助文件"的双文件程序。
- structs-strings：定义 `Point {char name[20]; int x;}` 并打印。
- arrays-pointers：给定 int 数组，用前移方式删除一个元素并更新计数。
- file-io：向文件写三行再读回来。
- array-crud：内存联系人列表的增查删。
- delimited-persistence：用 strtok 保存/加载 `name|age` 行。
- borrow-inventory：一个不能减到负数的库存计数器。

每个练习都必须比成熟实现更小，且不得照抄它。
