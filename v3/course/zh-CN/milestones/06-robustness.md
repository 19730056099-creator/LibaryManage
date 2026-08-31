---
artifact_id: milestone-06
language: zh-CN
---

# 里程碑

milestone_id: milestone-06
competency_id: language.c.c-control-input
competency_id: language.c.file-io
competency_id: language.c.structs-strings
competency_id: project.input-validation
competency_id: project.defensive-parsing
competency_id: project.borrow-delete-policy
acceptance_id: m06-a01
acceptance_id: m06-a02
acceptance_id: m06-a03
acceptance_id: m06-a04
practice_id: m06-p01
manual_action_id: m06-manual-01
ai_boundary_id: m06-ai-01
transfer_check_id: m06-transfer-01
reappears_in: milestone-06
command: gcc -std=c11 -Wall -Wextra -pedantic main.c -o library_m06

## 当前版本

M05 的正常借还系统增加显式输入校验、文件坏行处理、容量错误和删除策略，形成面对已知边界的加固版本。

## 上一版本解决了什么

M05 已能在正常输入和格式正确的文件上管理借阅；但它把失败当成了成功路径中的隐含副作用。

## 用户遇到的新问题

用户可能输入 `12x`、负数或过大数量；文件可能有字段不足的行；删除一本仍被借出的书会让记录引用消失。程序应拒绝或报告，而不是静默制造状态。

## 本阶段引入什么

用 `strtol` 或等价的完整解析检查代替裸 `atoi`；加载时检查字段数、长度和数值；容量已满返回失败；选择并实现“有未归还记录时拒绝删除”的策略，并在关键操作后检查库存不变量。

## 目标

让可预见的坏输入和坏数据成为可定位、可测试的结果，同时不破坏 M05 的正常行为。

## 可观察结果

非法数量被拒绝且原状态不变；短行被跳过并报告；容量满时添加失败；有未归还记录的图书不能删除；正常借还仍通过。

## 本阶段解决什么

解决失败的可见性和跨记录一致性，使文件和用户输入不会无声污染数组。

## 范围

- 菜单/数量的完整数字解析和范围检查。
- 文件行字段数量、字符串长度和整数范围检查。
- 明确容量错误、坏行报告和借出书删除策略。
- 验证 `0 <= available <= quantity`。

## 暂时不解决什么

不做数据库事务、并发锁、原子文件替换、国际化、复杂转义格式或彻底重构成头文件/多翻译单元；这些不是参考项目当前压力。

## 前置知识

需要 M05 的借还状态、M03/F03 的文件模型和 F01 的输入控制流。所有新增概念在本阶段即时引入。

## 首次触摸

用 `12x`、`-1`、`5` 三个字符串观察裸 `atoi` 的结果，再定义本阶段应接受/拒绝的结果表。接着拿 `books.txt` 的短行做一次字段计数，先让失败可见再改代码。

## 任务

1. 写一个完整检查数字尾部的解析函数，拒绝空字符串、非数字和越界值。
2. 加载每行时验证字段数、字段长度和数值；坏行跳过并给出行号。
3. 设定容量满和写文件失败的可观察结果。
4. 检查未归还记录后拒绝删除图书，执行正常借还回归测试。

## AI 使用边界

AI 可以解释 `strtol` 的 end pointer、帮你列边界测试或审阅错误消息。你必须亲自写至少一个校验函数、决定坏行处理和删除策略、运行坏输入/坏文件/回归场景，并解释“拒绝后状态为何不变”。

## 理解与迁移检查

把“坏行跳过”改成“加载失败并停止”，比较两种策略对用户和数据一致性的影响；再增加数量上限，列出输入校验和文件校验必须共享的规则。

## 验收

```text
acceptance_id: m06-a01
```
非数字、尾随字符、负数和越界数量被拒绝，已有状态不变化。

```text
acceptance_id: m06-a02
```
含字段不足/过长/非法数值的文件行不会产生半初始化记录，并能报告或统计坏行。

```text
acceptance_id: m06-a03
```
容量满、文件打开/写入失败和删除未归还图书都有明确结果；删除策略在文档和代码中一致。

```text
acceptance_id: m06-a04
```
正常增删改查、借还、重启回归通过；提交边界测试、解释、AI 使用记录和迁移决策。

## 提示 1

先列出输入字符串的分类：完整数字、空串、前缀数字、尾随字符、负数、溢出。

## 提示 2

`strtol` 之后检查 `endptr` 是否停在字符串末尾，再检查 `errno` 和上下界；不要只检查返回值。

## 提示 3

文件行应先确认每个 token 存在且长度可放入目标数组，再复制和转换；失败时不要递增计数。

## 提示 4

删除前扫描 borrows，若存在同 bookId 且 `returned == 0` 就拒绝；这是本路线选择的最小一致性策略。

## 提示 5

完整参考可提供解析函数和删除策略样例；你仍须改变坏行策略、运行回归，并解释为什么拒绝比静默修复安全。

## 下一阶段为什么会出现

本路线已覆盖参考项目的主要边界。若继续，应由新的规模或可靠性压力驱动，例如测试、模块接口或原子持久化，而不是自动增加抽象。

## 源码桥接

对照 `main.c::atoi`、`data_mgr.c::loadData` 的无条件字段复制、`business.c::deleteBook` 未检查借阅关联，以及 `data_mgr.c` 的容量常量。

## 证据台账

```text
evidence: code_evidence
source: main.c::main
rationale: main.c 使用 atoi 解析菜单和数量，非数字输入没有完整错误分类。
```

```text
evidence: code_evidence
source: data_mgr.c::loadData
rationale: loadData 在字段存在性、长度和数值范围未验证时就复制并递增记录，短行会污染状态。
```

```text
evidence: code_evidence
source: business.c::deleteBook
rationale: deleteBook 只按图书 ID 删除，没有检查 borrows 中是否存在未归还记录，留下明确的业务策略压力。
```

## 完成结论

通过四项验收、坏输入/坏文件和正常回归证据，并完成策略迁移解释后，评审可标记 M06 `passed`。这会结束本路线；课程只有在所有里程碑通过并完成最终桥接评审后才算 `complete`。
