#pragma once 
#include <vector>
// 滤波核
class Filter {
public:
    // 构造函数
    Filter(int width, int height): width(width), height(height) {kernel.resize(width * height);};

    // 获取滤波核的宽度
    int getWidth() const { return width; }

    // 获取滤波核的高度
    int getHeight() const { return height; }

    // 获取滤波核的值
    const std::vector<float>& getKernel() const { return kernel; }

protected:
    int width;                      // 滤波核的宽度
    int height;                     // 滤波核的高度
    std::vector<float> kernel;      // 滤波核的值
};

// 平滑滤波器
class BoxFilter : public Filter {
public:
    BoxFilter(int width, int height): Filter(width, height) {
        // 初始化滤波核
        for (int i = 0; i < width * height; ++i) {
            kernel[i] = 1.0f / (width * height);
        }
    }
};
