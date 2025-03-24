#include "Distribution.hpp"

void Histogram::generateFrom(const std::vector<unsigned char>& imageData) {
    // 清空数据
    std::fill(data.begin(), data.end(), 0);
    totalCount = 0;
    // 计算直方图，假设为灰度图像
    for (int i = 0; i < imageData.size(); ++i) {
        data[imageData[i]]++;
        totalCount++;
    }
}
