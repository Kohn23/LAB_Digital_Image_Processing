#include "Algorithm.hpp"

// void Test::operator()(
//     std::vector<unsigned char>& imageData,
//     size_t width,
//     size_t height
// ) {
//     LaplacianFilter laplacianFilter;
//     ConvolChannels convolChannels;
//     convolChannels(imageData, width, height, 3, laplacianFilter);
// }


void Test::operator()(
    std::vector<unsigned char>& imageData,
    size_t width,
    size_t height
) {
    // 定义拉普拉斯算子
    const float laplacianKernel[9] = {
        1.0f,  1.0f, 1.0f,
        1.0f, -8.0f, 1.0f,
        1.0f,  1.0f, 1.0f
    };

    // 创建输出缓冲区（这就是我们要的mask）
    std::vector<unsigned char> mask(imageData.size());

    // 处理除边界外的所有像素
    for (size_t y = 1; y < height - 1; ++y) {
        for (size_t x = 1; x < width - 1; ++x) {
            float sumR = 0.0f, sumG = 0.0f, sumB = 0.0f;
            
            // 应用拉普拉斯算子
            for (int ky = -1; ky <= 1; ++ky) {
                for (int kx = -1; kx <= 1; ++kx) {
                    size_t idx = ((y + ky) * width + (x + kx)) * 3;
                    float kernel_val = laplacianKernel[(ky + 1) * 3 + (kx + 1)];
                    
                    sumB += imageData[idx] * kernel_val;
                    sumG += imageData[idx + 1] * kernel_val;
                    sumR += imageData[idx + 2] * kernel_val;
                }
            }

            // 计算当前像素位置
            size_t currentIdx = (y * width + x) * 3;
            
            // 直接存储拉普拉斯算子的结果作为mask
            mask[currentIdx]     = std::min(255, std::max(0, static_cast<int>(std::abs(sumB))));
            mask[currentIdx + 1] = std::min(255, std::max(0, static_cast<int>(std::abs(sumG))));
            mask[currentIdx + 2] = std::min(255, std::max(0, static_cast<int>(std::abs(sumR))));
        }
    }

    // 复制边界像素
    for (size_t y = 0; y < height; ++y) {
        for (size_t x = 0; x < width; ++x) {
            if (y == 0 || y == height - 1 || x == 0 || x == width - 1) {
                size_t idx = (y * width + x) * 3;
                mask[idx] = mask[idx + 1] = mask[idx + 2] = 0;
            }
        }
    }

    // 将mask复制回原图像
    imageData = std::move(mask);
}