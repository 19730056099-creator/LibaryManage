# LibaryManage 学习记录

这是一个通过分阶段重建 C 语言命令行图书管理系统来学习项目开发的仓库。课程覆盖：

- C 结构体、字符串、数组与指针
- 图书 CRUD 与数组前移删除
- `fopen` / `fgets` / `fprintf` / `strtok` 文本持久化
- 搜索、借还记录与库存约束
- 输入校验和错误数据处理

## 目录

| 目录 | 内容 |
|---|---|
| `v1/` | 第一版课程与 Foundation 01–02 学习记录 |
| `v2/` | 第二版课程，加入 Foundation 03 文件读写练习 |
| `v3/` | 重构后的双语课程，补充技术地图、故障定位、项目演变和更完整的能力进度模型 |

每个版本中的主要文件：

- `course/`：中英文课程、基础单元和六个里程碑
- `student/`：学习者手写 C 代码和测试数据（如果该版本已有）
- `reviews/`：阶段评审（如果该版本已有）
- `progress.json`：当前能力、单元和里程碑状态

## 当前版本

`v3/` 是最新课程版本。入口为：

```text
v3/course/GETTING_STARTED.md
```

当前学习状态记录在 `v3/progress.json`，下一步是完成 `foundation-01`。

## 编译练习

进入对应练习目录后，用 GCC 编译，例如：

```bash
gcc -std=c11 -Wall -Wextra -pedantic main.c -o main
./main
```

编译产物和 Windows 下载元数据不会提交到 Git。
