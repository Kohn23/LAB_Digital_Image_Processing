#include "Algorithm.hpp"

void Convol2d::operator()(
    const std::vector<unsigned char>& inputPlane,
    std::vector<unsigned char>& outputPlane, // 输出通过引用传递
    size_t inputWidth,
    size_t inputHeight,
    Filter& filter
) {
    int kernelWidth = filter.getWidth();
    int cutWidth = kernelWidth / 2;
    int cutHeight = filter.getHeight() / 2;
    size_t outputWidth = inputWidth - 2 * cutWidth;
    size_t outputHeight = inputHeight - 2 * cutHeight;

    outputPlane.assign(outputWidth * outputHeight, 0); // 复用输出缓冲区

    for (size_t y = cutHeight; y < inputHeight - cutHeight; ++y) {
        for (size_t x = cutWidth; x < inputWidth - cutWidth; ++x) {
            float sum = 0.0f;
            for (int ky = -cutHeight; ky <= cutHeight; ++ky) {
                for (int kx = -cutWidth; kx <= cutWidth; ++kx) {
                    sum += inputPlane[(y + ky) * inputWidth + (x + kx)] * filter.getKernel()[(ky + cutHeight) * kernelWidth + (kx + cutWidth)];
                }
            }
            outputPlane[(y - cutHeight) * outputWidth + (x - cutWidth)] = static_cast<unsigned char>(sum);
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
    int kernelWidth = filter.getWidth();
    int kernelHeight = filter.getHeight();
    Padding padding;
    Convol2d convol2d;

    // 共享的中间缓冲区（填充和卷积复用）
    // 注意多线程环境下可能需要线程安全的实现
    static std::vector<unsigned char> paddedBuffer;
    static std::vector<unsigned char> convolvedBuffer;

    // 处理每个通道
    for (int channel = 0; channel < channels; ++channel) {
        // 提取单个通道数据
        std::vector<unsigned char> channelData;
        channelData.reserve(width * height);
        for (size_t i = channel; i < imageData.size(); i += channels) {
            channelData.push_back(imageData[i]);
        }

        // 填充操作
        padding(channelData, paddedBuffer, width, height, kernelWidth/2, kernelHeight/2);

        // 卷积操作
        convol2d(paddedBuffer, convolvedBuffer, width + 2*(kernelWidth/2), height + 2*(kernelHeight/2), filter);

        // 将结果写回原图像数据
        for (size_t i = 0, idx = channel; i < convolvedBuffer.size(); ++i, idx += channels) {
            imageData[idx] = convolvedBuffer[i];
        }
    }
}