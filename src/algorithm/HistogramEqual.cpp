#include "Algorithm.hpp"

void HistogramEqual::operator()(std::vector<unsigned char>& imageData) {
    // 计算直方图
    Histogram histogram(imageData);
    // 计算累积直方图
    CDF cdf(histogram);
    // 归一化
    cdf.normalize();
    // 直方图均衡化
    auto cdfData = cdf.getData();
    // 计算查找表
    std::vector<int> lut(256);
    for (int i = 0; i < 256; ++i) {
        lut[i] = static_cast<int>(cdfData[i] * 255 + 0.5);
    }
    // 应用查找表
    for (auto& pixel : imageData) {
        pixel = static_cast<unsigned char>(lut[pixel]);
    }
}