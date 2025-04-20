#include "Algorithm.hpp"

void Padding::operator()(
    const std::vector<unsigned char>& inputPlane,
    std::vector<unsigned char>& outputPlane, // 输出通过引用传递
    size_t inputWidth,
    size_t inputHeight,
    int padWidth,
    int padHeight
) {
    size_t paddedWidth = inputWidth + 2 * padWidth;
    size_t paddedHeight = inputHeight + 2 * padHeight;
    outputPlane.assign(paddedWidth * paddedHeight, 0);

    for (size_t y = 0; y < inputHeight; ++y) {
        for (size_t x = 0; x < inputWidth; ++x) {
            outputPlane[(y + padHeight) * paddedWidth + (x + padWidth)] = inputPlane[y * inputWidth + x];
        }
    }
}    
