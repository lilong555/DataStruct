# 快速开始

本文档说明如何在 WSL2/Linux 环境下编译与运行本仓库的 6 个课程设计项目。

## 环境要求

- 操作系统：WSL2 或 Linux
- 编译器：`g++`（支持 C++17）
- 目录：建议在仓库根目录下编译，产物输出到 `output/`

## 统一编译参数

各项目采用相同的编译参数，便于对比与复现：

- `-std=c++17`：使用 C++17 标准
- `-O2`：二级优化
- `-Wall -Wextra -pedantic`：输出更全面的告警信息

## 编译全部项目

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

## 运行方式

编译完成后可直接运行（部分程序为交互式菜单）：

```bash
./output/p1
./output/p3
./output/p5
./output/p7
./output/p8
./output/p10
```

## 常见问题

### 1）找不到 `g++`

请先安装编译器（示例）：

```bash
sudo apt update
sudo apt install -y g++
```

### 2）为什么 `output/` 里生成的文件没有提交到 Git

`output/` 为本地编译产物目录，默认不纳入版本管理，避免污染仓库历史与不同平台的二进制差异。

