#pragma once 
#include <vector>
#include <cmath>
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

// 盒式平滑滤波器
class BoxFilter : public Filter {
public:
    BoxFilter(int width, int height): Filter(width, height) {
        // 初始化滤波核
        for (int i = 0; i < width * height; ++i) {
            kernel[i] = 1.0f / (width * height);
        }
    }
};

// 高斯滤波器
// 需要使用cmath库来计算指数函数和平方根
class GaussianFilter : public Filter {
public:
    GaussianFilter(int width, int height, float sigma);
};

// 拉普拉斯滤波器
class LaplacianFilter : public Filter {
public:
    LaplacianFilter(int width=3, int height=3) : Filter(width, height) {
        // 初始化滤波核
        kernel = {
            -1.0, -1.0, -1.0, 
            -1.0, 8.0, -1.0, 
            -1.0, -1.0, -1.0
        };
    }
};

// 垂直索伯滤波器
class SobelFilterV : public Filter {
public:
    SobelFilterV(int width=3, int height=3) : Filter(width, height) {
        // 初始化滤波核
        kernel = {
            -1.0, 0.0, 1.0,
            -2.0, 0.0, 2.0,
            -1.0, 0.0, 1.0
        };
    }
};

// 水平索伯滤波器
class SobelFilterH : public Filter {
public:
    SobelFilterH(int width=3, int height=3) : Filter(width, height) {
        // 初始化滤波核
        kernel = {
            -1.0, -2.0, -1.0,
            0.0, 0.0, 0.0,
            1.0, 2.0, 1.0
        };
    }
};