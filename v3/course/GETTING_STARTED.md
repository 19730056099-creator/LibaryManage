---
artifact_id: getting-started
language: bilingual
---

# 学习指南 / Learning Guide

## 课程是什么 / What This Course Is

这是一条用 `LibaryManageSrc` 重建 C 图书管理系统的双语课程。它把成熟仓库拆成“可观察价值 → 新压力 → 最小变化”的学习路线；路线是教学重建，不是作者真实提交历史。参考仓库只读，练习和数据放在本 workspace 的 `student/` 下。

This is a bilingual reconstruction course for the C library manager in `LibaryManageSrc`. It orders work as “observable value → new pressure → smallest change”; it is a teaching reconstruction, not the author's verified commit history. The reference is read-only; exercises and data live under `student/` in this workspace.

## 文件总览与阅读顺序 / File Overview and Reading Order

按下面顺序阅读；不要一次把所有后期知识前置：

1. 阅读 `course/zh-CN/project-map.md` 与 `course/en/project-map.md` 的项目目的、核心用户路径、**技术层级地图 / Technology Layer Map** 和 **故障定位地图 / Troubleshooting Map**。
2. 阅读 `course/<lang>/readiness.md`，确认项目能力、学习者基线、`learning_mode` 和进入条件。
3. 阅读 `course/<lang>/knowledge-graph.md`，只关注当前阶段及其依赖。
4. 阅读当前前置单元；现在的 `current_unit` 是 `foundation-01`，所以先读 `course/zh-CN/foundations/F01-c-build-and-structs.md` 和 `course/en/foundations/F01-c-build-and-structs.md`。
5. 完成并评审当前基础单元后，再按拓扑顺序进入后续基础单元或里程碑。
6. 阅读 `course/<lang>/project-evolution.md`，理解每一阶段为什么在上一阶段之后出现；它回答“为什么”。
7. 阅读 `course/<lang>/roadmap.md`，确认要构建什么以及顺序；它回答“做什么”。
8. 每次只阅读当前 `course/<lang>/milestones/NN-*.md`，完成验收后再继续。
9. 里程碑完成后回看 `course/<lang>/architecture.md`，把实践中的调用和数据流映射回成熟结构。
10. 用 `progress.json` 查看状态；评审记录放在 `reviews/zh-CN/` 和 `reviews/en/`。

Read in this order; do not front-load every later concept:

1. Read the purpose, journey, **Technology Layer Map**, and **Troubleshooting Map** in both `project-map.md` files.
2. Read both `readiness.md` files and confirm competencies, baseline, `learning_mode`, and entry conditions.
3. Read `knowledge-graph.md` and focus only on the current unit's dependencies.
4. Read the current foundation pair. The current unit is `foundation-01`, so start with `course/zh-CN/foundations/F01-c-build-and-structs.md` and its English pair.
5. Complete and review the current foundation before moving to the next available foundation or milestone.
6. Read `project-evolution.md` to understand why each stage appears after the previous one.
7. Read `roadmap.md` to see what to build and in what order.
8. Read only the current milestone pair and advance after acceptance.
9. Revisit `architecture.md` after milestones to map your calls and data flow to the mature structure.
10. Check `progress.json` for state; reviews live in `reviews/zh-CN/` and `reviews/en/`.

## 各文件的用途速查 / Quick File Reference

| 文件 / File | 用途 / Purpose | 什么时候读 / When |
|---|---|---|
| `project-map.md` | 项目目的、用户路径、技术层和故障第一检查点 / purpose, journey, technology layers, first failure checks | 第一次进入项目 / first entry |
| `architecture.md` | 组件、数据流、控制流和设计取舍 / components, data/control flow, trade-offs | 完成阶段后回看 / revisit after practice |
| `knowledge-graph.md` | 项目能力依赖和复现深度 / competency dependencies and recurrence | 进入新单元前 / before a new unit |
| `readiness.md` | 学习者证据、差距、学习模式、门控 / learner evidence, gaps, mode, gates | 评估或路线变化时 / assessment or route change |
| `project-evolution.md` | 每阶段的上一价值、新压力、引入变化和延后限制；解释“为什么” / why stages appear | 开始里程碑路线前 / before milestones |
| `roadmap.md` | 里程碑目标和构建顺序；说明“做什么” / what to build and order | 规划当前任务 / plan current work |
| `foundations/FNN-*.md` | 只补项目当前需要的语言/工具能力 / just-in-time prerequisite bridge | 当前 foundation 时 / when current |
| `milestones/NN-*.md` | 可观察价值、任务、提示、验收和源码桥接 / value, tasks, hints, acceptance, source bridge | 当前 milestone 时 / when current |
| `progress.json` | 唯一共享状态，包括 learner evidence 和 practice evidence / shared state | 每次开始或提交 / start or submit |
| `reviews/<lang>/` | 成对阶段评审、结论和风险 / paired stage reviews | 提交 milestone 后 / after milestone submission |
| `student/` | 学习者手写代码、输出和测试数据 / learner code, output, test data | 所有动手操作 / all hands-on work |

特别注意：`project-evolution.md` 解释每个阶段为什么出现；`roadmap.md` 规定要做什么和顺序。它们互补，不是重复文件。

Note the distinction: `project-evolution.md` explains why stages appear; `roadmap.md` says what to build and in what order. They are complementary, not duplicates.

## 使用规则 / Usage Rules

- 准备方式可选：`assume_beginner`（不做测验、生成短补给路线）、`self_report`/`mixed`（回答少量项目相关问题）、或 `waived`（明确接受风险）。本次记录沿用 `assume_beginner`。
- 学习模式可选 `product_builder`、`cs_depth` 或 `balanced`。本次目标同时强调完成产品和理解机制，因此使用 `balanced`。
- 开始单元：阅读中英文成对文件，先做“首次触摸”，再完成手写任务；不要把阅读当作通过证据。
- 请求提示：先请求 Hint 1；需要时逐步到 Hint 5。每次提示记录 unit、级别、原因和时间；完整答案也不免除手写/解释/迁移检查。
- 提交评审：提交当前代码、命令输出、运行场景、解释、迁移结果和 AI 使用记录；不要只提交“AI 生成后能运行”的结果。
- 查看进度：读取 `progress.json`；只有出现可观察练习、评审结论、提示请求或明确选择时才更新它。
- 放弃/跳过：必须明确选择并记录风险；后续 milestone 仍需满足或显式豁免阻塞能力。
- 后续基础单元按需即时引入：F03 在 M03 前出现，不会因为选择初学者路线而把文件、借阅和健壮性全部塞到开头。

- Choose readiness as `assume_beginner` (no quiz, short foundations), `self_report`/`mixed` (a few project-specific questions), or `waived` (accept recorded risk). This run reuses `assume_beginner`.
- Choose `product_builder`, `cs_depth`, or `balanced`. This goal combines building with understanding, so the route uses `balanced`.
- Start a unit by reading its paired files and doing First Touch before the full task; reading is not exit evidence.
- Request Hint 1 first and escalate to Hint 5 only as needed. Record unit, level, reason, and time; a full answer never waives hands-on, explanation, or transfer checks.
- Submit code, command output, scenarios, explanation, transfer result, and AI-use record for review. A successful AI-generated run alone is not mastery evidence.
- Check `progress.json`; update it only after observable practice, a review verdict, a hint request, or an explicit choice.
- Skipping requires an explicit choice and recorded risk; later milestones still need ready or explicitly waived blockers.
- Later foundations are introduced just in time: F03 appears before M03 rather than putting files, borrowing, and hardening at the beginning.

## 现在就开始 / Start Now

当前状态 / Current state:

```text
course_status: ready
learning_phase: foundations
current_unit: foundation-01
current_milestone: 0
```

第一步（必须由学习者亲自完成）：

```bash
mkdir -p student/foundation/F01-c-build-and-structs
cd student/foundation/F01-c-build-and-structs
# 手写 main.c，然后执行：
gcc -std=c11 -Wall -Wextra -pedantic main.c -o foundation01
./foundation01
```

让程序读入一个不超过 7 个字符的 code 和一个 pages，打印两者；用 `do-while`，输入 `0` 退出。随后提交 `main.c`、编译/运行输出，并解释 `strcmp(...) == 0`、`fgets` 去换行、以及本仓库为什么只编译 `main.c`。

First learner-owned action:

```bash
mkdir -p student/foundation/F01-c-build-and-structs
cd student/foundation/F01-c-build-and-structs
# Hand-write main.c, then run:
gcc -std=c11 -Wall -Wextra -pedantic main.c -o foundation01
./foundation01
```

Read a code of at most 7 characters and a pages value, print both, use a `do-while`, and exit on `0`. Submit `main.c`, build/run output, and explanations of `strcmp(...) == 0`, newline removal after `fgets`, and why this repository compiles only `main.c`.

AI may explain errors and suggest tests, but the learner must write the concept-bearing code, run the commands, observe the result, and explain the flow. After review, `progress.json` will select the next available unit.
