---
artifact_id: milestone-02
language: zh-CN
---

# 里程碑

milestone_id: milestone-02
competency_id: language.c.arrays-pointers
competency_id: language.c.structs-strings
competency_id: project.array-crud
foundation_id: foundation-02
acceptance_id: m02-a01
acceptance_id: m02-a02
acceptance_id: m02-a03
acceptance_id: m02-a04
practice_id: m02-p01
manual_action_id: m02-manual-01
ai_boundary_id: m02-ai-01
transfer_check_id: m02-transfer-01
reappears_in: milestone-04, milestone-05, milestone-06
command: gcc -std=c11 -Wall -Wextra -pedantic main.c -o library_m02

## 当前版本

在 M01 的内存添加/列表上增加唯一 ID 查找、部分更新和按下标删除，删除中间元素后数组仍保持连续。

## 上一版本解决了什么

M01 已经能把用户输入变成目录记录，但错误记录只能重启程序后消失，不能主动维护。

## 用户遇到的新问题

重复 ID 会使“按 ID 找书”含糊；书名、作者或数量变化后旧记录过期；删除中间元素若不前移会让列表遍历出现洞。

## 本阶段引入什么

引入 `findBookIndex`、唯一 ID 检查、空字符串表示“不修改”、结构体赋值前移和 `bookCount--`。数量修改的 `available` 关系只做最小解释，完整库存到 M05。

## 目标

让用户在一次运行内维护可信的内存目录：添加失败、修改、删除均有可观察结果。

## 可观察结果

添加重复 ID 会失败；修改一本书后列表反映新字段；删除中间书后剩余书籍顺序连续且没有重复尾项。

## 本阶段解决什么

解决内存目录的基本生命周期和数组紧凑性，而不是解决重启持久化。

## 范围

- 按 ID 线性查找和拒绝重复 ID。
- 更新非空字段；删除后移动后继元素。
- 为不存在的 ID 返回失败，不让 `count` 越界。

## 暂时不解决什么

不做文件读写、搜索、借还、复杂错误类型、动态内存或完整数量输入验证。

## 前置知识

需具备 F01 的结构体/字符串和 F02 的数组前移能力；`project.array-crud` 在本阶段首次通过代码行为形成。

## 首次触摸

用三个短标签 `A B C` 做一次删除中间元素实验，先观察输出应为 `A C`，再把同样的移动放进书目删除。先让数组压力可见，再谈函数抽象。

## 任务

1. 在上一阶段代码上加入 `findBookIndex`，用 `strcmp` 比较 ID。
2. 添加时拒绝已存在 ID；更新时允许空标题/作者表示保留原值。
3. 实现按下标左移删除，分别测试头、中、尾。
4. 记录一个不存在 ID 的失败场景，解释为何 `count` 不变。

## AI 使用边界

AI 可以帮助画删除前后数组、解释 `strcmp` 或指出边界条件。你必须亲自写查找循环、左移循环和计数更新，运行四个场景；不得让 AI 替你决定重复 ID 和不存在 ID 的返回语义。

## 理解与迁移检查

把删除目标改成最后一个元素，说明为何移动循环零次；再把 `Book` 增加一个整数 `year`，说明结构体整体赋值前移为何仍可复制它。

## 验收

```text
acceptance_id: m02-a01
```
不同 ID 可新增，重复 ID 被拒绝且原记录不变。

```text
acceptance_id: m02-a02
```
已存在 ID 的书名、作者或数量可按规则修改；不存在 ID 有明确失败结果。

```text
acceptance_id: m02-a03
```
删除头部、中部、尾部都保持有效元素连续、顺序正确，`count` 正确。

```text
acceptance_id: m02-a04
```
提交四个场景的输出、核心循环解释和一次迁移修改；核心代码由学习者亲自完成。

## 提示 1

先写出 `A B C` 删除 `B` 后哪些槽位是有效的，不要先写业务菜单。

## 提示 2

`findBookIndex` 找到就返回下标，扫完返回 `-1`；调用者必须处理 `-1`。

## 提示 3

删除时从 `index` 开始，把 `items[i + 1]` 赋给 `items[i]`，循环到 `count - 2`，最后减少 `count`。

## 提示 4

更新可以先复制旧记录，再只覆盖非空参数；删除和更新都应先检查查找结果。

## 提示 5

完整参考只能作为解阻：保留 `findBookIndex`、左移和 `count--` 的最小实现；你仍需改变删除位置并解释边界。

## 下一阶段为什么会出现

M02 的目录在一次运行内可靠，但一旦退出所有修改消失。这个具体压力会在 M03 触发文件持久化。

## 源码桥接

对照 `data_mgr.c::findBookIndex`、`business.c::updateBook` 和 `business.c::deleteBook`，特别看 `-1`、结构体赋值和 `bookCount` 的关系。

## 证据台账

```text
evidence: code_evidence
source: data_mgr.c::findBookIndex
rationale: 参考实现用线性 strcmp 查找 ID，并用 -1 表示不存在。
```

```text
evidence: code_evidence
source: business.c::updateBook
rationale: updateBook 展示了按 ID 修改非空字段和数量的路径。
```

```text
evidence: code_evidence
source: business.c::deleteBook
rationale: deleteBook 展示了中间删除时整体前移并减少 bookCount 的机制。
```

## 完成结论

通过四项验收并提交直接数组练习证据后，评审可标记 M02 为 `passed`。不要求此阶段具备后续文件和借阅机制。
