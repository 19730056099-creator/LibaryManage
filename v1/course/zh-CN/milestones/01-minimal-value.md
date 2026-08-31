---
artifact_id: milestone-01
language: zh-CN
---
# 里程碑

milestone_id: milestone-01

## 目标

写出一个菜单驱动的 C 程序：用户选 1 添加一本书（ID、书名、作者、数量），选 2 列出所有书。数据放在静态结构体数组里，程序退出即消失。

## 可观察结果

- `gcc main.c -o library && ./library` 可运行（或你自己的文件名）。
- 添加 2 本书后选 2，能看到两行格式化输出；重启后数据消失（此时是预期行为）。
- 重复 ID 被拒绝（本阶段允许用最简单的线性查找）。

## 设计压力

写死几本书的演示程序没有价值——用户输入必须变成程序里的数据，且要有菜单循环让操作可以反复进行。

## 范围

- 一个 `Book` 结构体：`char id[20]; char title[100]; char author[100]; int quantity; int available;`
- 全局数组 + `bookCount` 计数器，容量 1000。
- `addBook` / `listAllBooks` / `findBookIndex` 三个函数。
- `do-while` 菜单循环 + `switch` 分发。

## 约束

- 本阶段不写文件读写、不写搜索、不写借还。
- 不使用 malloc/链表；只用静态数组。
- `available` 暂时等于 `quantity`。

## 前置知识

- competency_id: tooling.c.gcc-build（blocking）
- competency_id: language.c.structs-strings（blocking）
- competency_id: language.c.arrays-pointers（blocking）

## 任务

1. 定义结构体与全局数组。
2. 实现 `findBookIndex`（strcmp 逐个比较）。
3. 实现 `addBook`：容量满或 ID 重复返回 0，否则填入结构体、`available = quantity`、计数加一并返回 1。
4. 实现 `listAllBooks`：表头 + 循环 printf；空列表给提示。
5. 搭菜单循环，用 `fgets` 读选择，`atoi` 转整数，`strcspn` 去换行。

## 验收

- m01-a01：编译零错误，程序能连续响应多次菜单选择。
- m01-a02：添加两本书后列出，输出包含全部字段。
- m01-a03：重复添加同一 ID 得到失败提示，列表仍只有两本。
- m01-a04：空库时选 2 显示"No book data"类提示而不是崩溃。

## 提示 1

先不写菜单，写一个 `main` 直接调用 `addBook` 两次再 `listAllBooks`，确认数组逻辑正确后再套菜单循环。

## 提示 2

`fgets` 会把换行符留在字符串里，用 `s[strcspn(s, "\n")] = '\0'` 去掉；否则 ID 永远匹配不上。

## 提示 3

`addBook` 的返回值用 int 0/1，让菜单层决定打印什么——不要在业务函数里直接 printf 结果。

## 提示 4

删除元素时（为 milestone-02 预习）：把后面每个元素整体左移一位 `books[i] = books[i+1]`，再 `bookCount--`。

## 提示 5

参考实现桥接：`business.c::addBook/listAllBooks`、`data_mgr.c::findBookIndex`、`main.c::main` 的 case 1/case 2。先自己写完再对照。

## 下一项压力

程序一退出数据全没了。用户明天再打开，书都不在了——你需要持久化（milestone-03），但先要把改、删、查补齐（milestone-02）。

## 源码桥接

`business.c::addBook`, `business.c::listAllBooks`, `data_mgr.c::Book`, `data_mgr.c::findBookIndex`, `main.c::displayMenu`, `main.c::case 1/case 2`

## 证据台账

```text
evidence: code_evidence
source: business.c::addBook
rationale: 成熟实现同样采用 0/1 返回值 + 容量与重复检查。
```

```text
evidence: code_evidence
source: main.c::main
rationale: fgets + strcspn + atoi 的输入清洗模式是本里程碑的核心技能点。
```

## 完成结论

（待学习者提交后由评审填写）
