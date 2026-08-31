---
artifact_id: foundation-03
language: zh-CN
---

# 前置补给单元

foundation_id: foundation-03
competency_id: language.c.file-io
competency_id: project.delimited-persistence
required_by: milestone-03
required_by: milestone-05
required_by: milestone-06
acceptance_id: f03-a01
practice_id: f03-p01
manual_action_id: f03-manual-01
ai_boundary_id: f03-ai-01
transfer_check_id: f03-transfer-01
reappears_in: milestone-03, milestone-05, milestone-06
command: gcc -std=c11 -Wall -Wextra -pedantic main.c -o foundation03

## 为什么现在需要

M03 的压力是“退出后数据消失”。在接入整个项目前，先用一个临时文件练习 `fopen`、逐行读取、`strtok`、`fprintf` 和关闭文件，避免把文件 API 与 CRUD 同时引入。

## 依赖

依赖结构体/字符串和数组基础；不需要数据库知识。所有实验都在自己的 student 目录进行，不修改参考仓库的 `books.txt`。

## 最小概念

- `fopen` 可能返回 `NULL`；读写后要 `fclose`。
- `fgets` 每次得到一行；`strtok(line, "|")` 会在分隔符处写入 `\0` 并返回字段指针。
- `fprintf` 可以把结构体字段写成一行；字段顺序必须与读取顺序一致。
- 本单元先接受简单格式；字段缺失、越界和分隔符出现在正文中的情况留到 M06。

## 小例子

```c
char line[64] = "B001|Title|2\n";
for (char *token = strtok(line, "|"); token; token = strtok(NULL, "|")) {
    printf("%s\n", token);
}
```

## 首次触摸

在练习目录写入一行 `B001|Title|2`，用 `fgets` 读回来并打印每个 token。打开生成的文件确认它是普通文本；再观察 `strtok` 调用后 `line` 已被切开。

## 动手练习

在 `student/foundation/F03-file-strtok/main.c`：创建 `probe.txt`，写入两行管道符记录；重新打开它，逐行读取、拆出三个字段并打印。处理文件打开失败，最后关闭文件。不要直接复制 `data_mgr.c::loadData`。

## AI 使用边界

AI 可以解释 `FILE *`、`NULL`、`strtok(NULL, ...)` 和文件模式，或帮你设计一条坏行。你必须亲自选择文件名、写读写循环、运行并检查文件内容；必须解释为什么第一次 `strtok` 传 `line`，后续传 `NULL`。

## 理解与迁移检查

把记录从三个字段改成四个字段，保持写入和读取顺序一致；再加入一行只有两个字段，说明当前练习会发生什么，以及为什么 M06 需要先验证字段数。

## 通过标准

```text
acceptance_id: f03-a01
```

- 无警告编译运行，`probe.txt` 被创建并包含两行预期文本。
- 重新读取后能打印每个字段，文件打开失败不会继续使用空指针。
- 能解释 `strtok` 的首次/后续调用和短行风险，并提交迁移结果。

## 项目桥接

回看 `data_mgr.c::loadData` 和 `saveData` 的图书行格式。M03 只先让 `books.txt` 跨重启，M05 再加入 `borrows.txt`，M06 最后把当前解析器的缺口显式化。

## 暂不学习

暂不学习数据库、二进制序列化、事务、原子替换、并发文件锁或复杂转义格式；参考项目没有这些边界。

## 完成结论

提交手写文件读写程序、文件内容、运行记录和迁移解释后，才能把 F03 标记为 `passed`。它不会提前解锁 milestone-01，只在相关阶段前生效。

```text
evidence: code_evidence
source: data_mgr.c::loadData
rationale: loadData 使用 fopen、fgets、strtok 和 atoi 从 books.txt/borrows.txt 恢复字段。
```

```text
evidence: code_evidence
source: data_mgr.c::saveData
rationale: saveData 使用 fopen 的 w 模式和 fprintf 将数组记录写回管道符文本文件。
```
