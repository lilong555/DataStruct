# 编译与测试

本文档给出 6 个项目的统一编译方法，以及每个项目可用于自检的最小测试方式。

## 编译

在仓库根目录执行：

```bash
mkdir -p output
g++ -std=c++17 -O2 -Wall -Wextra -pedantic p1/p1.cpp -o output/p1
g++ -std=c++17 -O2 -Wall -Wextra -pedantic p3/maze_game.cpp -o output/p3
g++ -std=c++17 -O2 -Wall -Wextra -pedantic p5/bank_service.cpp -o output/p5
g++ -std=c++17 -O2 -Wall -Wextra -pedantic p7/p7.cpp -o output/p7
g++ -std=c++17 -O2 -Wall -Wextra -pedantic p8/p8.cpp -o output/p8
g++ -std=c++17 -O2 -Wall -Wextra -pedantic p10/10_sorting_comparison.cpp -o output/p10
```

## 运行与最小自检

说明：本仓库以控制台交互为主，没有统一的自动化测试框架，建议按以下方式做最小自检。

### P1：考试报名系统（交互式）

```bash
./output/p1
```

建议自检点：

- 初始化录入 N 个考生后，能正确显示列表
- 插入/删除/查找/修改后，统计与显示正确
- 对非法输入（非数字年龄/考号等）有提示并能继续

### P3：勇闯迷宫（交互式/可重定向）

```bash
./output/p3 < p3/test_input.txt
```

建议自检点：

- 能输出迷宫地图与路径
- 无路可走时给出“无路径”提示

### P5：银行业务（批处理输入）

示例输入（来自题目样例）：

```bash
printf '8 2 1 3 9 4 11 13 15\n' | ./output/p5
```

期望输出：

```
1 3 2 9 11 4 13 15
```

### P7：修理牧场（批处理输入）

示例输入（题目样例）：

```bash
printf '8\n4 5 1 2 1 3 1 1\n' | ./output/p7
```

期望输出：

```
49
```

### P8：电网建设造价模拟（菜单交互）

```bash
./output/p8
```

建议自检点：

- A：创建顶点（名称不重复）
- B：输入边，使用 `? ? 0` 结束输入
- C：生成最小生成树（图不连通时给出提示）
- D：显示最小生成树边及总造价

### P10：排序算法比较（菜单交互）

```bash
./output/p10
```

建议自检点：

- 单个算法：选择算法编号与数据规模后，输出时间/比较/交换统计
- 全量对比：输出 100、1000、10000、100000 以及自定义规模的对比结果

