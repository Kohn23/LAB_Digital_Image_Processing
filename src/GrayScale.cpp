#include"Algorithm.hpp"

void GrayScale::operator()(std::vector<unsigned char>& imageData, int width, int height) {
    // 转换为灰度图像
    for (size_t i = 0; i < imageData.size(); i += 3) {
        unsigned char r = imageData[i];
        unsigned char g = imageData[i + 1];
        unsigned char b = imageData[i + 2];
        //unsigned char gray = 0.299 * r + 0.587 * g + 0.114 * b;
        unsigned char gray = 0.333 * r + 0.333 * g + 0.333 * b;
        imageData[i] = gray;    // R
        imageData[i + 1] = gray; // G
        imageData[i + 2] = gray; // B
    }
}