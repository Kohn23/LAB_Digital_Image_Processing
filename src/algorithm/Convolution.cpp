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