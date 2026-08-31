---
artifact_id: readiness
language: zh-CN
---

# 学习准备

## 项目所需能力

以下是从主用户路径反向展开的能力 DAG。`state` 只表示课程当前如何安排前置补给，不是对学习者的笼统评级。

competency_id: tooling.c.gcc-build
state: learning
required_by: milestone-01

competency_id: language.c.c-control-input
state: learning
required_by: milestone-01, milestone-06

competency_id: language.c.structs-strings
state: learning
required_by: milestone-01, milestone-02, milestone-03, milestone-04, milestone-05, milestone-06

competency_id: language.c.arrays-pointers
state: needs_refresh
required_by: milestone-01, milestone-02, milestone-04, milestone-05, milestone-06

competency_id: language.c.file-io
state: needs_refresh
required_by: milestone-03, milestone-05, milestone-06

competency_id: language.c.time-format
state: unknown
required_by: milestone-05

competency_id: project.array-crud
state: unknown
required_by: milestone-02, milestone-04, milestone-06

competency_id: project.delimited-persistence
state: unknown
required_by: milestone-03, milestone-05, milestone-06

competency_id: domain.borrow-inventory
state: unknown
required_by: milestone-05, milestone-06

competency_id: project.input-validation
state: unknown
required_by: milestone-06

competency_id: project.defensive-parsing
state: unknown
required_by: milestone-06

competency_id: project.borrow-delete-policy
state: unknown
required_by: milestone-06

## 学习者基线

沿用本项目之前已经提供的学习者证据：学习者学过 C 语法，但没有实际项目构建经验，许多细节需要恢复；选择了 `assume_beginner`。目标是“从零理解并重建 LibaryManageSrc 的 C 图书管理路径”。

## 差距与决策

- `tooling.c.gcc-build`、`language.c.c-control-input`、`language.c.structs-strings`：安排到 F01，先恢复编译、输入循环和结构体/字符串。
- `language.c.arrays-pointers`：安排到 F02，完成 milestone-01 前必须通过数组与删除练习。
- `language.c.file-io` 与 `project.delimited-persistence`：安排到 F03，在 milestone-03 前即时补给，不提前学习。
- 其余能力在首次出现的里程碑中通过小实验引入。

本次生成把学习模式定为 `balanced`：目标同时强调完成产品和理解机制，因此 AI 可以减少机械脚手架，但学习者仍须亲自运行、修改、解释和诊断关键路径。

learner_choice: assume_beginner

## 学习模式与 AI 边界

learning_mode: balanced

AI 可以：解释编译器信息、帮助设计测试输入、指出可能的错误位置、在学习者先尝试后提供局部脚手架。AI 不可以替代关键操作：学习者必须亲自创建/修改核心 C 代码、执行命令、观察输出、检查文件，并能解释输入到状态变化的因果链。

## 前置补给路线

| 单元 | 覆盖能力 | 安排 | 解锁 |
|---|---|---|---|
| `foundation-01` / `F01-c-build-and-structs.md` | gcc、菜单控制流、结构体/字符串 | **当前待开始** | milestone-01 的前三项基础能力 |
| `foundation-02` / `F02-array-delete.md` | `language.c.arrays-pointers` | F01 通过后 | milestone-01、milestone-02 |
| `foundation-03` / `F03-file-strtok.md` | 文件 I/O、分隔格式解析 | milestone-03 前即时进行 | milestone-03、milestone-05、milestone-06 |

foundation_id: foundation-01
foundation_id: foundation-02
foundation_id: foundation-03

## 进入项目的条件

当前路线已经生成，但学习者尚未因生成课程而自动获得能力。完成 F01 和 F02 的可观察退出标准后，milestone-01 的阻塞能力才会变为 `ready`；F03 在 milestone-03 前再门控。每个通过单元都需要自己的手写动作、可观察结果、解释和 AI 使用记录。

```text
evidence: code_evidence
source: main.c::main
rationale: 入口实际使用 gcc 可编译的单翻译单元、菜单控制流和 fgets/atoi 输入路径。
```

```text
evidence: code_evidence
source: data_mgr.c::Book
rationale: Book 的定长 char 数组和数量字段决定了结构体、字符串与库存能力的项目需求。
```
