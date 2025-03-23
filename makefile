# 编译器及编译选项
CXX := g++
CXXFLAGS := -g -I./include

# 目标可执行文件名及路径
TARGET := bin/demo.exe

# 源文件列表（src目录下的源文件和根目录下的demo.cpp）
SRCS := $(wildcard src/*.cpp) demo.cpp

# 生成对应的.o文件列表（路径在bin目录下）
OBJS := $(addprefix bin/,$(notdir $(SRCS:.cpp=.o)))

# 头文件列表（include目录下的头文件）
HEADERS := $(wildcard include/*.hpp)

# 默认目标：编译整个项目
all: bin $(TARGET)

# 创建bin目录
bin:
	mkdir -p bin

# 链接
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

# 编译src目录下的源文件
bin/%.o: src/%.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# 编译根目录下的demo.cpp
bin/demo.o: demo.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# 清理生成的文件
clean:
	rm -rf bin/*.o $(TARGET)

.PHONY: all clean