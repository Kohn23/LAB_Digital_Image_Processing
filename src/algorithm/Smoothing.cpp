#include "Algorithm.hpp"

void BoxSmoothing::operator()(
    std::vector<unsigned char>& imageData,
    size_t width,
    size_t height
) {
    BoxFilter filter(3, 3);                                 // 创建卷积核
    ConvolChannels convolChannels;                          // 创建卷积对象
    convolChannels(imageData, width, height, 3, filter);    // 卷积操作
}
