---
artifact_id: milestone-03
language: zh-CN
---

# 里程碑

milestone_id: milestone-03

## 目标

让数据在重启之间存活：每次成功写操作后把所有图书保存到 `books.txt`（管道符分隔）；启动时加载回来。

## 可观察结果

- 添加/修改/删除后，`books.txt` 与内存一致。
- 重启程序后列表完整恢复。
- 缺少 `books.txt` 时以空库干净启动。

## 设计压力

内存状态退出即消失。最简单可靠的答案：一个人类可读的文本文件，整体重写。

## 范围

- `saveData()`：`fprintf(file, "%s|%s|%s|%d|%d\n", ...)`。
- `loadData()`：`fgets` 读行 + 逐字段 `strtok(line, "|")`。
- 每条写路径末尾调用保存；启动时加载。

## 约束

- 只做图书；借阅记录的持久化并入 milestone-05。
- 不处理字段中嵌入的 `|` 或换行的转义。
- 容量上限不变（读到 MAX 即停）。

## 前置知识

- competency_id: language.c.file-io（blocking）
- competency_id: project.delimited-persistence（blocking）

## 任务

1. 写 `saveData` 并在 `addBook` 成功路径调用；用文本编辑器检查格式。
2. 写 `loadData`：第一次 `strtok` 传行，之后传 NULL；数字用 `atoi`。
3. 处理文件缺失（fopen 返回 NULL 表示空库）。
4. 给 update/delete 路径补上保存调用。

## 验收

- m03-a01：添加两本书后，`cat books.txt` 显示两行、每行五个管道符分隔字段。
- m03-a02：重启后列出的内容与退出前一致。
- m03-a03：删除一本书并重启，该书消失。
- m03-a04：把 `books.txt` 改名移走不会崩溃；列表为空。

## 提示 1

解析模式固定：`char *tok = strtok(line, "|"); ... tok = strtok(NULL, "|");`——字段数固定就按位置取五个 token。

## 提示 2

`atoi(NULL)` 是未定义行为——每个 token 用前先判空。

## 提示 3

保存用 `"w"` 模式整文件重写；不要追加，否则重启会重复行。

## 提示 4

给行缓冲留足空间（如 512），避免长书名被截断导致下一条记录解析错位。

## 提示 5

参考：`data_mgr.c::loadData/saveData`。成熟实现在读循环前先把计数器清零，避免重复加载时叠加。

## 下一项压力

书目变多后肉眼浏览失效；而且"拥有量"和"在架量"需要分开管理了。

## 源码桥接

`data_mgr.c::loadData`, `data_mgr.c::saveData`

## 证据台账

```text
evidence: code_evidence
source: data_mgr.c::saveData
rationale: 管道符分隔的全量覆写持久化格式来自成熟代码。
```

```text
evidence: teaching_inference
confidence: medium
rationale: 字段值里含 '|' 会破坏数据；成熟代码未处理——留给 milestone-06 讨论。
source: data_mgr.c::loadData
```

## 完成结论

（待评审填写）
