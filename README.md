# 数据结构课程设计（6 个项目）

本仓库包含《数据结构课程设计题目》中的 6 个项目实现（控制台程序，C++）。

## 目录结构

- `要求.txt`：课程设计题目与考核要求
- `p1/`：题目一「考试报名系统」
- `p3/`：题目三「勇闯迷宫游戏」
- `p5/`：题目五「银行业务」
- `p7/`：题目七「修理牧场（最小花费）」
- `p8/`：题目八「电网建设造价模拟系统（Prim 最小生成树）」
- `p10/`：题目十「8 种排序算法的比较案例」
- `output/`：本地编译生成的可执行文件（默认不纳入版本管理）

## 编译与运行（WSL2/Linux）

建议使用 `g++`（C++17）：

```bash
mkdir -p output

g++ -std=c++17 -O2 -Wall -Wextra -pedantic p1/p1.cpp -o output/p1
g++ -std=c++17 -O2 -Wall -Wextra -pedantic p3/maze_game.cpp -o output/p3
g++ -std=c++17 -O2 -Wall -Wextra -pedantic p5/bank_service.cpp -o output/p5
g++ -std=c++17 -O2 -Wall -Wextra -pedantic p7/p7.cpp -o output/p7
g++ -std=c++17 -O2 -Wall -Wextra -pedantic p8/p8.cpp -o output/p8
g++ -std=c++17 -O2 -Wall -Wextra -pedantic p10/10_sorting_comparison.cpp -o output/p10
```

运行示例：

```bash
./output/p1
./output/p3
./output/p5
./output/p7
./output/p8
./output/p10
```

## 各项目输入/输出说明（简要）

- `p1`：按提示输入考生人数与每位考生信息；菜单支持插入/删除/查找/修改/统计。
- `p3`：输入迷宫行列、迷宫矩阵（0 通路/1 墙）、起点与终点坐标；输出迷宫地图与路径。
- `p5`：输入一行：`N id1 id2 ... idN`；按完成顺序输出编号（A 窗口处理速度为 B 的 2 倍）。
- `p7`：输入 `N` 及 `N` 段木头长度；输出最小总花费。
- `p8`：菜单驱动：创建顶点、添加边、构造 Prim 最小生成树、显示生成树与总造价。
- `p10`：菜单选择排序算法与数据规模；可选择对所有算法做性能对比（100/1000/10000/100000 及自定义规模）。
  - 说明：按约束仅使用 `iostream/cmath/cstring` 三个头文件实现。

## 提交仓库

GitHub 仓库：`https://github.com/lilong555/DataStruct`

