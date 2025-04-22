#include "Algorithm.hpp"

void LaplacianSharpening::operator()(
    std::vector<unsigned char>& imageData,
    size_t width,
    size_t height
) {
    LaplacianFilter laplacianFilter;
    ConvolChannels convolChannels;
    std::vector<unsigned char> mask(width * height, 0);
    mask = imageData;
    // 卷积操作得到mask
    convolChannels(mask, width, height, 3, laplacianFilter);
    // 处理每个通道
    for (size_t i = 0; i < imageData.size(); i += 3) {
        // 提取单个通道数据（示例：假设 RGB 交错存储）
        unsigned char b = imageData[i];
        unsigned char g = imageData[i + 1];
        unsigned char r = imageData[i + 2];
        // 提取mask通道数据
        unsigned char maskB = mask[i];
        unsigned char maskG = mask[i + 1];
        unsigned char maskR = mask[i + 2];
        // 相加（注意不能超出灰度范围）
        imageData[i]     = std::min(255, std::max(0, static_cast<int>(b + maskB)));
        imageData[i + 1] = std::min(255, std::max(0, static_cast<int>(g + maskG)));
        imageData[i + 2] = std::min(255, std::max(0, static_cast<int>(r + maskR)));
    }
}

void SobelSharpening::operator()(
    std::vector<unsigned char>& imageData,
    size_t width,
    size_t height
) {
    SobelFilterH sobelFilterH;
    SobelFilterV sobelFilterV;
    ConvolChannels convolChannels;
    std::vector<unsigned char> maskH(width * height, 0);
    std::vector<unsigned char> maskV(width * height, 0);
    maskH = imageData;
    maskV = imageData;
    // 卷积操作得到maskH和maskV
    convolChannels(maskH, width, height, 3, sobelFilterH);
    convolChannels(maskV, width, height, 3, sobelFilterV);
    // 处理每个通道
    for (size_t i = 0; i < imageData.size(); i += 3) {
        unsigned char b = imageData[i];
        unsigned char g = imageData[i + 1];
        unsigned char r = imageData[i + 2];
        // 提取mask通道数据
        unsigned char maskHB = maskH[i];
        unsigned char maskHG = maskH[i + 1];
        unsigned char maskHR = maskH[i + 2];
        unsigned char maskVB = maskV[i];
        unsigned char maskVG = maskV[i + 1];
        unsigned char maskVR = maskV[i + 2];
        // 相加（注意不能超出灰度范围）
        imageData[i]     = std::min(255, std::max(0, static_cast<int>(b + 0.25*maskHB + 0.25*maskVB)));
        imageData[i + 1] = std::min(255, std::max(0, static_cast<int>(g + 0.25*maskHG + 0.25*maskVG)));
        imageData[i + 2] = std::min(255, std::max(0, static_cast<int>(r + 0.25*maskHR + 0.25*maskVR)));
    }
}