#include "Distribution.hpp"

CDF::CDF(const Distribution& other, int size) : Distribution(size) {
    // 清空数据
    std::fill(data.begin(), data.end(), 0);
    totalCount = 0;
    // 计算积累数据
    auto otherData = other.getData();
    data[0] = otherData[0];
    totalCount = data[0];
    for (int i = 1; i < data.size(); ++i) {
        data[i] = data[i-1] + otherData[i];
    }
    totalCount = data[255];
}

// void CDF::generateFrom(const Distribution& other) {
//     // 清空数据
//     std::fill(data.begin(), data.end(), 0);
//     totalCount = 0;
//     // 计算积累数据
//     auto otherData = other.getData();
//     data[0] = otherData[0];
//     totalCount = data[0];
//     for (int i = 1; i < data.size(); ++i) {
//         data[i] = data[i-1] + otherData[i];
//     }
//     totalCount = data[255];
// }
