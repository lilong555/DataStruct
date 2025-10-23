#include <iostream>
#include <cmath>
#include <cstring>

// 常量定义
const int kMaxSize = 100;
const int kDirections = 4;

// 方向数组：下、右、上、左
const int kDx[kDirections] = {1, 0, -1, 0};
const int kDy[kDirections] = {0, 1, 0, -1};

/**
 * 迷宫类
 * 使用回溯法求解迷宫路径问题
 */
class Maze {
 public:
  // 构造函数和析构函数
  Maze();
  ~Maze();
  
  // 公共接口
  void InputMaze();
  bool SolveMaze();
  void PrintPath();
  void PrintMaze();
  
 private:
  // 位置结构体，保存坐标和前进方向
  struct Position {
    int x;
    int y;
    int direction;
  };
  
  // 成员变量
  int maze_[kMaxSize][kMaxSize];           // 迷宫地图
  bool visited_[kMaxSize][kMaxSize];       // 访问标记数组
  Position path_[kMaxSize * kMaxSize];     // 路径栈
  int rows_;                                // 行数
  int cols_;                                // 列数
  int start_x_;                             // 起点x坐标
  int start_y_;                             // 起点y坐标
  int end_x_;                               // 终点x坐标
  int end_y_;                               // 终点y坐标
  int path_length_;                         // 路径长度
  
  // 私有方法
  bool IsValid(int x, int y);
  bool DFS(int x, int y);
};

/**
 * 构造函数：初始化迷宫对象
 */
Maze::Maze() {
  std::memset(maze_, 0, sizeof(maze_));
  std::memset(visited_, false, sizeof(visited_));
  rows_ = 0;
  cols_ = 0;
  start_x_ = 0;
  start_y_ = 0;
  end_x_ = 0;
  end_y_ = 0;
  path_length_ = 0;
}

/**
 * 析构函数
 */
Maze::~Maze() {
}

/**
 * 输入迷宫数据
 */
void Maze::InputMaze() {
  std::cout << "请输入迷宫的行数和列数：";
  std::cin >> rows_ >> cols_;
  
  std::cout << "请输入迷宫地图 (0表示通路，1表示墙壁)：" << std::endl;
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      std::cin >> maze_[i][j];
    }
  }
  
  std::cout << "请输入起点坐标(行 列，从0开始)：";
  std::cin >> start_x_ >> start_y_;
  
  std::cout << "请输入终点坐标(行 列，从0开始)：";
  std::cin >> end_x_ >> end_y_;
}

/**
 * 检查位置是否有效
 * @param x 行坐标
 * @param y 列坐标
 * @return 如果位置有效返回true，否则返回false
 */
bool Maze::IsValid(int x, int y) {
  return x >= 0 && x < rows_ && y >= 0 && y < cols_ && 
         maze_[x][y] == 0 && !visited_[x][y];
}

/**
 * 深度优先搜索（回溯法）
 * @param x 当前行坐标
 * @param y 当前列坐标
 * @return 如果找到路径返回true，否则返回false
 */
bool Maze::DFS(int x, int y) {
  // 到达终点
  if (x == end_x_ && y == end_y_) {
    path_[path_length_].x = x;
    path_[path_length_].y = y;
    path_[path_length_].direction = -1;
    path_length_++;
    return true;
  }
  
  // 标记当前位置已访问
  visited_[x][y] = true;
  path_[path_length_].x = x;
  path_[path_length_].y = y;
  
  // 尝试四个方向（右、下、左、上）
  for (int dir = 0; dir < kDirections; ++dir) {
    int next_x = x + kDx[dir];
    int next_y = y + kDy[dir];
    
    if (IsValid(next_x, next_y)) {
      path_[path_length_].direction = dir;
      path_length_++;
      
      // 递归搜索
      if (DFS(next_x, next_y)) {
        return true;
      }
      
      // 回溯：撤销选择
      path_length_--;
    }
  }
  
  // 回溯：取消访问标记
  visited_[x][y] = false;
  return false;
}

/**
 * 求解迷宫
 * @return 如果找到路径返回true，否则返回false
 */
bool Maze::SolveMaze() {
  std::memset(visited_, false, sizeof(visited_));
  path_length_ = 0;
  return DFS(start_x_, start_y_);
}

/**
 * 打印路径
 */
void Maze::PrintPath() {
  if (path_length_ == 0) {
    std::cout << "没有找到路径！" << std::endl;
    return;
  }
  
  std::cout << "迷宫路径：" << std::endl;
  for (int i = 0; i < path_length_; ++i) {
    std::cout << "(" << path_[i].x + 1 << "," << path_[i].y + 1 << ")";
    if (i < path_length_ - 1) {
      std::cout << " ---> ";
    }
  }
  std::cout << std::endl;
}

/**
 * 打印迷宫地图（包含路径标记）
 */
void Maze::PrintMaze() {
  std::cout << "迷宫地图：" << std::endl;
  
  // 创建显示数组
  char display[kMaxSize][kMaxSize];
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      if (maze_[i][j] == 1) {
        display[i][j] = '#';  // 墙壁
      } else {
        display[i][j] = 'o';  // 空地，使用o代替特殊字符ø
      }
    }
  }
  
  // 标记路径
  for (int i = 0; i < path_length_; ++i) {
    display[path_[i].x][path_[i].y] = 'x';  // 路径，使用x代替特殊字符×
  }
  
  // 打印表头
  std::cout << "    ";
  for (int j = 0; j < cols_; ++j) {
    std::cout << j << "列  ";
  }
  std::cout << std::endl;
  
  // 打印地图
  for (int i = 0; i < rows_; ++i) {
    std::cout << i << "行  ";
    for (int j = 0; j < cols_; ++j) {
      std::cout << display[i][j] << "   ";
    }
    std::cout << std::endl;
  }
}

/**
 * 主函数
 */
int main() {
  Maze maze;
  
  std::cout << "====== 勇闯迷宫游戏 ======" << std::endl << std::endl;
  
  // 输入迷宫数据
  maze.InputMaze();
  
  std::cout << std::endl;
  
  // 求解迷宫
  if (maze.SolveMaze()) {
    std::cout << "成功找到路径！" << std::endl << std::endl;
    maze.PrintMaze();
    std::cout << std::endl;
    maze.PrintPath();
  } else {
    std::cout << "无法找到从起点到终点的路径！" << std::endl;
  }
  
  std::cout << std::endl << "Press any key to continue" << std::endl;
  std::cin.get();
  std::cin.get();
  
  return 0;
}
