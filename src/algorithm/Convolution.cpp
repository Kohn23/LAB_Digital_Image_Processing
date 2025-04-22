#include "Algorithm.hpp"

void Conv2d::operator()(
    const std::vector<unsigned char>& inputPlane,
    std::vector<unsigned char>& outputPlane, // 输出通过引用传递
    size_t inputWidth,
    size_t inputHeight,
    Filter& filter
) {
    int kernelWidth = filter.getWidth();
    int cutWidth = kernelWidth / 2;
    int cutHeight = filter.getHeight() / 2;

    outputPlane.assign(inputWidth * inputHeight, 0); // 复用输出缓冲区

    for(size_t y = cutHeight; y < inputHeight - cutHeight; ++y) {
        for(size_t x = cutWidth; x < inputWidth - cutWidth; ++x) {
            float sum = 0.0f;
            for(int ky = -cutHeight; ky <= cutHeight; ++ky) {
                for(int kx = -cutWidth; kx <= cutWidth; ++kx) {
                    sum += inputPlane[(y - ky) * inputWidth + (x - kx)] * filter.getKernel()[(ky + cutHeight) * kernelWidth + (kx + cutWidth)];
                }
            }
            // 限制输出范围在0-255之间
            outputPlane[y * inputWidth + x] = std::min(255, std::max(0, static_cast<int>(sum)));
        }
    }
}


void ConvolChannels::operator()(
    std::vector<unsigned char>& imageData,
    size_t width,
    size_t height,
    int channels,
    Filter& filter
) {
    Conv2d conv2d;

    // 共享的中间缓冲区（填充和卷积复用）
    // 注意多线程环境下可能需要线程安全的实现
    static std::vector<unsigned char> convolvedBuffer;

    // 处理每个通道
    for (int channel = 0; channel < channels; ++channel) {
        // 提取单个通道数据
        std::vector<unsigned char> channelData;
        channelData.reserve(width * height);
        for (size_t i = channel; i < imageData.size(); i += channels) {
            channelData.push_back(imageData[i]);
        }

        // 卷积操作
        conv2d(channelData, convolvedBuffer, width, height, filter);

        // 将结果写回原图像数据
        for (size_t i = 0, idx = channel; i < convolvedBuffer.size(); ++i, idx += channels) {
            imageData[idx] = convolvedBuffer[i];
        }
    }
}