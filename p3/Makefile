# Makefile for Maze Game
# 迷宫游戏编译文件

# 编译器
CXX = g++

# 编译选项
CXXFLAGS = -std=c++11 -Wall -Wextra -O2

# 目标文件
TARGET = maze_game

# 源文件
SOURCES = maze_game.cpp

# 对象文件
OBJECTS = $(SOURCES:.cpp=.o)

# 默认目标
all: $(TARGET)

# 链接目标文件
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)
	@echo "编译完成！运行程序: ./$(TARGET)"

# 编译源文件
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# 清理编译文件
clean:
	rm -f $(OBJECTS) $(TARGET)
	@echo "清理完成！"

# 运行程序（使用测试输入）
run: $(TARGET)
	./$(TARGET) < test_input.txt

# 调试编译
debug: CXXFLAGS += -g -DDEBUG
debug: clean $(TARGET)
	@echo "调试版本编译完成！"

# 帮助信息
help:
	@echo "可用的make目标："
	@echo "  make          - 编译程序"
	@echo "  make all      - 编译程序"
	@echo "  make clean    - 清理编译文件"
	@echo "  make run      - 编译并运行（使用test_input.txt）"
	@echo "  make debug    - 编译调试版本"
	@echo "  make help     - 显示此帮助信息"

.PHONY: all clean run debug help
