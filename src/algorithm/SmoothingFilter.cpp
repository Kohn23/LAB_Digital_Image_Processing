#include "Algorithm.hpp"

void SmoothingFilter::operator()(
    std::vector<unsigned char>& imageData,
    size_t width,
    size_t height
) {
    int kernelWidth = 3; // 卷积核宽度
    int kernelHeight = 3; // 卷积核高度
    BoxFilter filter(kernelWidth, kernelHeight); // 创建卷积核
    Padding padding;
    Convol2d convol2d;

    // 共享的中间缓冲区（填充和卷积复用）
    // 注意多线程环境下可能需要线程安全的实现
    static std::vector<unsigned char> paddedBuffer;
    static std::vector<unsigned char> convolvedBuffer;

    // 处理每个通道
    for (int channel = 0; channel < 3; ++channel) {
        // 提取单个通道数据（示例：假设 RGB 交错存储）
        std::vector<unsigned char> channelData;
        channelData.reserve(width * height);
        for (size_t i = channel; i < imageData.size(); i += 3) {
            channelData.push_back(imageData[i]);
        }

        // 填充操作
        padding(channelData, paddedBuffer, width, height, kernelWidth/2, kernelHeight/2);

        // 卷积操作
        convol2d(paddedBuffer, convolvedBuffer, width + 2*(kernelWidth/2), height + 2*(kernelHeight/2), filter);

        // 将结果写回原图像数据
        for (size_t i = 0, idx = channel; i < convolvedBuffer.size(); ++i, idx += 3) {
            imageData[idx] = convolvedBuffer[i];
        }
    }
}