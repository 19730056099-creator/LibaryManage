---
artifact_id: milestone-01
language: zh-CN
---

# 里程碑

milestone_id: milestone-01
competency_id: tooling.c.gcc-build
competency_id: language.c.c-control-input
competency_id: language.c.structs-strings
competency_id: language.c.arrays-pointers
foundation_id: foundation-01
foundation_id: foundation-02
acceptance_id: m01-a01
acceptance_id: m01-a02
acceptance_id: m01-a03
acceptance_id: m01-a04
practice_id: m01-p01
manual_action_id: m01-manual-01
ai_boundary_id: m01-ai-01
transfer_check_id: m01-transfer-01
reappears_in: milestone-02, milestone-04, milestone-05
command: gcc -std=c11 -Wall -Wextra -pedantic main.c -o library_m01

## 当前版本

一个可反复运行的菜单程序：用户输入图书 ID、书名、作者和数量，添加到固定容量内存数组，并列出当前图书。数据退出后消失。

## 上一版本解决了什么

V0 只需证明“一个值可以显示”；它不能接受用户输入，也没有重复操作的入口。本阶段把最小演示变成可操作的目录。

## 用户遇到的新问题

用户可以添加，但还不能修正或删除错误条目；重复 ID 也会让后续定位不可靠。这些压力留给 M02。

## 本阶段引入什么

引入 `Book` 结构体、有效数量计数器、菜单 `do-while`/`switch`、添加函数和列表输出。先用线性数组，不引入文件和复杂抽象。

## 目标

完成 V1：一次运行内能添加并查看多本图书。

## 可观察结果

输入两个不同 ID 后选择列表，能看到两条记录和对应数量；重新启动后记录不保证存在。

## 本阶段解决什么

建立完整的第一条用户链路：stdin → 结构体 → 数组状态 → stdout。

## 范围

- `Book { id, title, author, quantity }` 与固定容量数组。
- 添加、列表、退出；拒绝超过容量。
- 使用自己的学生目录和自己的 `main.c`。

## 暂时不解决什么

暂不实现更新、删除、搜索、文件持久化、借阅、严格数字校验或头文件重构。重复 ID 的明确策略在 M02 处理。

## 前置知识

需先通过 `foundation-01` 和 `foundation-02`：gcc 构建、输入/结构体/字符串、数组遍历和前移删除。对应能力已在 `progress.json` 中门控。

## 首次触摸

先硬编码一条 `Book` 并打印它，确认字段能组合成一个值；再删除硬编码，改为只读取一条用户输入。最后加入 `do-while` 菜单，让“用户输入导致列表变化”成为第一个可观察结果。

## 任务

1. 在 `student/milestone-01/` 创建自己的程序和一份空数据目录。
2. 写 `Book`、计数器、add/list 函数；输入字符串后去掉换行。
3. 加入菜单循环和退出分支，连续添加至少两本书。
4. 为容量已满写一个可观察的失败消息，但不提前实现所有输入校验。

## AI 使用边界

AI 可以解释编译错误、帮助设计测试输入或画调用链。你必须亲自写结构体、计数器、添加/列表核心逻辑，运行编译命令并手工执行场景；必须解释一次“选择 1 后数据如何到达列表”。不要让 AI 直接复制参考函数作为提交。

## 理解与迁移检查

把列表字段顺序改为“作者、书名、ID、数量”，不改变内部数据；再添加第三本书，解释 `count` 哪一刻增加、列表循环为何只到 `[0, count)`。

## 验收

```text
acceptance_id: m01-a01
```
编译命令无错误/警告，并在正确目录运行。

```text
acceptance_id: m01-a02
```
依次添加两本不同 ID 的书，列表能显示两条完整记录。

```text
acceptance_id: m01-a03
```
重复运行菜单不会丢失当前进程内的数据，输入 0 能退出；退出后数据是否持久化不属于本阶段。

```text
acceptance_id: m01-a04
```
提交一次手写核心代码、运行记录、AI 使用说明和迁移回答；能口头追踪输入到数组再到输出。

## 提示 1

先预测：如果 `count` 初始为 0，添加一条后列表循环应访问哪些下标？

## 提示 2

把用户输入拆成三步：读取一行、去掉换行、复制到 `Book` 的对应 char 数组。

## 提示 3

让 `addBook` 接收四个参数；成功时写入 `books[count]`，再递增 `count`，列表只遍历有效前缀。

## 提示 4

伪代码：`while menu != 0: if menu == 1 read fields; books[count] = new; count++; if menu == 2 for i in [0,count) print`。

## 提示 5

若你明确请求完整参考，可先实现 `Book`、`bookCount`、`addBook`、`listBooks` 和 `do-while` 的最小版本；仍须自己改一个字段顺序、运行并解释控制流。

## 下一阶段为什么会出现

M01 能录入但不能维护。重复 ID 和错误条目会迫使用户直接编辑代码，因此 M02 引入查找、更新和前移删除。

## 源码桥接

对照 `data_mgr.c::Book` 的字段、`main.c::main` 的菜单循环和 `business.c::addBook` 的写入顺序。这里只提取最小行为，不要求复制全项目。

## 证据台账

```text
evidence: code_evidence
source: main.c::main
rationale: main.c::main 展示菜单输入、do-while/switch 分派和用户可观察的结果路径。
```

```text
evidence: code_evidence
source: data_mgr.c::Book
rationale: Book 提供本阶段所需的 ID、书名、作者和数量字段。
```

```text
evidence: code_evidence
source: business.c::addBook
rationale: addBook 展示固定数组写入、容量判断、计数递增和保存调用的成熟路径；学习者本阶段只实现内存部分。
```

## 完成结论

通过四项验收且具备直接练习证据后，评审可将 M01 标记为 `passed`。运行成功但核心代码完全由 AI 生成、没有解释或迁移证据时，不能单独通过。
