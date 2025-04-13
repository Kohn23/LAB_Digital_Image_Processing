#include "Distribution.hpp"

Histogram::Histogram(const std::vector<unsigned char>& imageData, int size) : Distribution(size) {
    // 清空数据
    std::fill(data.begin(), data.end(), 0);
    totalCount = 0;
    // 计算直方图，假设为灰度图像(不分通道)
    for (size_t i = 0; i < imageData.size(); ++i) {
        data[imageData[i]]++;
        totalCount++;
    }
}

// void Histogram::generateFrom(const std::vector<unsigned char>& imageData) {
//     // 清空数据
//     std::fill(data.begin(), data.end(), 0);
//     totalCount = 0;
//     // 计算直方图，假设为灰度图像
//     for (int i = 0; i < imageData.size(); ++i) {
//         data[imageData[i]]++;
//         totalCount++;
//     }
// }
