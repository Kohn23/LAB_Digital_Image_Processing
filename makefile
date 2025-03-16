# Makefile
# 编译器及编译选项
CXX := g++
CXXFLAGS := -g

# 目标可执行文件名及路径
TARGET := bin/demo.exe

# 源文件列表
SRCS := bmp_process.cpp demo.cpp GrayScale.cpp

# 生成对应的.o文件列表（路径在bin目录下）
OBJS := $(addprefix bin/,$(SRCS:.cpp=.o))

# 头文件列表（用于依赖跟踪）
HEADERS := Algorithm.hpp bmp_process.hpp image_process.hpp

# 默认目标：编译整个项目
all: bin $(TARGET)

# 链接
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

# 编译
bin/%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# 清理生成的文件
clean:
	rm -f bin/*.o $(TARGET)

.PHONY: all clean