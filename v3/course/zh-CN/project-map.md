---
artifact_id: project-map
language: zh-CN
---

# 项目地图

## 项目目的

`LibaryManageSrc` 是一个单进程、单用户的 C 命令行图书管理系统。用户可以添加、查看、搜索、修改、删除图书，借阅和归还图书，并查看借阅记录；运行状态保存在相对路径的 `books.txt` 与 `borrows.txt` 中。

仓库没有 README、Makefile 或自动化测试。`main.c` 直接包含 `data_mgr.c` 和 `business.c`，因此当前仓库的最小构建入口是只把 `main.c` 传给 gcc。运行时必须在数据文件所在的工作目录启动。

## 核心用户路径

1. `main()` 调用 `initSystem()`，从两个文本文件加载全局数组。
2. `displayMenu()` 展示菜单；`fgets` 读取选择，`atoi` 转成整数，再由 `switch` 分派。
3. 添加、列表、搜索、修改和删除操作读写 `Book` 数组。
4. 借阅检查 `available`，减少库存并创建 `BorrowRecord`；归还增加库存并标记记录。
5. 变更操作调用 `saveData()`；选择 0 时调用 `saveAllData()` 后退出。

## 子系统

| 子系统 ID | 责任 | 输入 | 输出 | 依赖 | 源码位置 |
|---|---|---|---|---|---|
| `ui-menu` | 菜单、提示、stdin 输入和结果消息 | 用户文本 | 对业务函数的调用 | `domain-business` | `main.c::displayMenu`, `main.c::displayHelp`, `main.c::main` |
| `domain-business` | 图书 CRUD、搜索、借还规则 | 字符串与数量 | 数组变更、0/1 结果、保存调用 | `data-store` | `business.c::addBook`, `searchBook`, `updateBook`, `deleteBook`, `borrowBook`, `returnBook` |
| `data-store` | 结构体、固定容量数组、查找、文件读写、日期 | 两个文本文件 | 内存状态与文件状态 | C 标准库 | `data_mgr.c::Book`, `BorrowRecord`, `loadData`, `saveData` |

## 技术层级地图

从一次用户动作向下定位：

- `layer-01`：shell 与当前工作目录；决定 gcc 是否找到源文件，以及程序是否找到 `books.txt`。
- `layer-02`：C11 编译器；`main.c` 是当前翻译单元入口，编译命令是 `gcc -std=c11 -Wall -Wextra -pedantic main.c -o library`。
- `layer-03`：单进程 stdin/stdout 运行时；菜单输入经过 `fgets`、`atoi` 和 `switch`。
- `layer-04`：应用组件；`main.c` 的 UI 调用 `business.c`，业务函数读写 `data_mgr.c` 的全局数组。
- `layer-05`：文本存储；`books.txt` 使用 `id|title|author|quantity|available`，`borrows.txt` 使用 `bookId|borrower|borrowDate|returnDate|returned`。

## 故障定位地图

| `failure_id` | 可观察现象 | 先检查 | 下一边界 |
|---|---|---|---|
| `failure-01` | 编译时重复定义或声明冲突 | 是否只编译 `main.c`；查看它的两个 `.c` include | `layer-02` → `main.c` 的构建边界 |
| `failure-02` | 启动后列表为空或保存到了意外位置 | `pwd`、`ls books.txt borrows.txt` | `layer-01` → `layer-05` |
| `failure-03` | 列表出现空记录或字段错位 | 用 `nl -ba books.txt` 查看每行字段数 | `layer-05` → `data_mgr.c::loadData` |
| `failure-04` | 非数字菜单/数量被当成 0 或其他数字 | 检查 `main.c::atoi` 的输入路径 | `layer-03` → 输入校验 |
| `failure-05` | 借书失败或库存异常 | 检查 `findBookIndex` 与 `available` | `layer-04` → `business.c::borrowBook` |

## 证据台账

```text
evidence: code_evidence
source: main.c::main
rationale: main.c::main 负责初始化、菜单循环、输入读取、switch 分派和退出保存，证明了端到端控制入口。
```

```text
evidence: code_evidence
source: business.c::borrowBook
rationale: borrowBook 查找图书、检查可用库存、写入借阅记录并保存，证明了借阅状态变化。
```

```text
evidence: code_evidence
source: data_mgr.c::loadData
rationale: loadData 从 books.txt 和 borrows.txt 读取管道符分隔行并填充固定容量数组。
```

```text
evidence: document_evidence
source: books.txt::lines 1-8
rationale: 样例文件展示了图书行格式，也包含字段不足的异常行，后续加固阶段可用来观察解析风险。
```

## 未覆盖范围

- 不把 `.git` 元数据、提交历史或远程平台操作当作学习主线；仓库的两次提交不足以证明开发顺序。
- 不加入网络、数据库、并发、账号权限、图形界面或第三方库，因为参考项目没有这些边界。
- 运行数据只复制到学习者自己的 `student/` 目录，绝不直接修改参考仓库。
- 仓库没有自动化测试；课程验收使用隔离运行、手工场景和文件内容检查。
