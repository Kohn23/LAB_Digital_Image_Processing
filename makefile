# 编译器及编译选项
CXX := g++
CXXFLAGS := -g -I./include -Wall

# 目标可执行文件名及路径
TARGET := bin/demo.exe

# 源文件目录和目标文件目录
SRC_DIR := src
BIN_DIR := bin

# 获取所有源文件（包含子目录）
SRCS := $(wildcard $(SRC_DIR)/*/*.cpp) demo.cpp

# 生成扁平化目标文件名（去除子目录路径）
OBJS := $(addprefix $(BIN_DIR)/, $(notdir $(SRCS:.cpp=.o)))

# 获取头文件
HEADERS := $(wildcard include/*.hpp)

# 默认目标
all: $(BIN_DIR) $(TARGET)

# 创建bin目录
$(BIN_DIR):
	@mkdir -p $@

# 链接可执行文件
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

# 编译规则（处理子目录源文件）
$(BIN_DIR)/%.o: $(SRC_DIR)/*/%.cpp $(HEADERS) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# 特殊处理demo.cpp
$(BIN_DIR)/demo.o: demo.cpp $(HEADERS) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# 清理
clean:
	rm -rf $(BIN_DIR)/*.o $(TARGET)

.PHONY: all clean