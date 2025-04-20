#include "Filter.hpp"

GaussianFilter::GaussianFilter(int width, int height, float sigma) : Filter(width, height) {
    // 计算高斯滤波核
    float sum = 0.0f;
    int halfWidth = width / 2;
    int halfHeight = height / 2;
    for (int y = -halfHeight; y <= halfHeight; ++y) {
        for (int x = -halfWidth; x <= halfWidth; ++x) {
            kernel[(y + halfHeight) * width + (x + halfWidth)] = exp(-(x * x + y * y) / (2 * sigma * sigma));
            sum += kernel[(y + halfHeight) * width + (x + halfWidth)];
        }
    }
    // 归一化滤波核
    for (int i = 0; i < width * height; ++i) {
        kernel[i] /= sum;
    }
}