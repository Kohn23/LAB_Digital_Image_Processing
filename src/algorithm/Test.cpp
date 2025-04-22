#include "Algorithm.hpp"

// 查看mask
void Test::operator()(
    std::vector<unsigned char>& imageData,
    size_t width,
    size_t height
) {
    LaplacianFilter laplacianFilter;
    ConvolChannels convolChannels;
    convolChannels(imageData, width, height, 3, laplacianFilter);
}