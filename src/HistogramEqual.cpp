#include "Algorithm.hpp"

void HistogramEqual::operator()(std::vector<unsigned char>& imageData) {
    // 转换为灰度图像
    if (!isGray) {
        GrayScale grayScale;
        grayScale(imageData);
    }
    // 计算直方图
    Histogram histogram(imageData);
    // 计算累积直方图
    CDF cdf(histogram);
    // 归一化
    cdf.normalize();
    // 直方图均衡化
    auto cdfData = cdf.getData();
    for (int i = 0; i < imageData.size(); ++i) {
        imageData[i] = (cdfData[imageData[i]] + 0.5) * 255;
    }
}