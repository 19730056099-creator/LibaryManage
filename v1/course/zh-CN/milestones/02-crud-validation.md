---
artifact_id: milestone-02
language: zh-CN
---

# 里程碑

milestone_id: milestone-02

## 目标

在 milestone-01 基础上补齐修改、删除、以及更严格的 ID 校验，形成完整的内存 CRUD。

## 可观察结果

- 菜单新增：3 搜索（可留到 milestone-04，本阶段可先按 ID 精确查）、4 修改、5 删除。
- 删除中间一本书后，剩余图书顺序保持、计数正确。
- 修改时"留空保留原值"，数量改为 -1 表示不变。

## 设计压力

重复 ID 和无法移除的过期条目会让列表失去可信度；数据结构必须支持任意位置的删除而不破坏遍历。

## 范围

- `updateBook(id, title, author, quantity)`：部分更新语义。
- `deleteBook(id)`：前移覆盖删除。
- 数量调整时同步 `available`（差额搬运，钳制 ≥ 0）。

## 约束

- 不引入新数据结构。
- 删除不做墓碑标记，直接左移。

## 前置知识

- competency_id: project.array-crud（blocking）
- competency_id: language.c.arrays-pointers（blocking）

## 任务

1. 实现 `updateBook`：找到下标后仅更新非空字符串字段；quantity ≥ 0 时计算差额同步 available。
2. 实现 `deleteBook`：左移 + 计数减一。
3. 在菜单中接入两个功能并打印成败。

## 验收

- m02-a01：添加 3 本，删除第 2 本后再列出，剩下的是原第 1、3 本且顺序正确。
- m02-a02：修改时书名留空 → 原书名保留；数量输入 -1 → 原数量保留。
- m02-a03：把数量从 5 改为 2，available 同步减少 3 且不为负。
- m02-a04：修改/删除不存在的 ID 得到失败提示。

## 提示 1

部分更新就是一连串 `if (strlen(new) > 0) strcpy(old, new);`。

## 提示 2

available 的同步：`int diff = newQty - oldQty; available += diff; if (available < 0) available = 0;`。

## 提示 3

删除的循环边界是 `for (i = idx; i < count - 1; i++) books[i] = books[i+1];`——注意是 `count - 1`。

## 提示 4

考虑一个坑：如果有人借走了书（available < quantity），直接改小 quantity 应该怎么处理？成熟实现选择了钳制到 0 并允许 available 与 quantity 的关系暂时失衡——想想这有什么隐患。

## 提示 5

参考：`business.c::updateBook/deleteBook`。先自己写再对照。

## 下一项压力

数据仍然一退出就没。下一步必须让状态在重启之间存活。

## 源码桥接

`business.c::updateBook`, `business.c::deleteBook`, `data_mgr.c::findBookIndex`

## 证据台账

```text
evidence: code_evidence
source: business.c::updateBook
rationale: "空串/-1 表示保留原值"的部分更新契约来自成熟代码。
```

## 完成结论

（待评审填写）
