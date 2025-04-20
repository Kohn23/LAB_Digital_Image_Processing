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

// #include "Algorithm.hpp"

// void LaplacianSharpening::operator()(
//     std::vector<unsigned char>& imageData,
//     size_t width,
//     size_t height
// ) {
//     // 定义拉普拉斯算子
//     const float laplacianKernel[9] = {
//         1.0f,  1.0f, 1.0f,
//         1.0f, -8.0f, 1.0f,
//         1.0f,  1.0f, 1.0f
//     };

//     // 创建输出缓冲区
//     std::vector<unsigned char> output(imageData.size());

//     // 处理除边界外的所有像素
//     for (size_t y = 1; y < height - 1; ++y) {
//         for (size_t x = 1; x < width - 1; ++x) {
//             float sumR = 0.0f, sumG = 0.0f, sumB = 0.0f;
            
//             // 应用拉普拉斯算子
//             for (int ky = -1; ky <= 1; ++ky) {
//                 for (int kx = -1; kx <= 1; ++kx) {
//                     size_t idx = ((y + ky) * width + (x + kx)) * 3;
//                     float kernel_val = laplacianKernel[(ky + 1) * 3 + (kx + 1)];
                    
//                     sumB += imageData[idx] * kernel_val;
//                     sumG += imageData[idx + 1] * kernel_val;
//                     sumR += imageData[idx + 2] * kernel_val;
//                 }
//             }

//             // 计算当前像素位置
//             size_t currentIdx = (y * width + x) * 3;
            
//             // 原图减去拉普拉斯算子的结果（锐化）
//             output[currentIdx]     = std::min(255, std::max(0, static_cast<int>(imageData[currentIdx]     - sumB)));
//             output[currentIdx + 1] = std::min(255, std::max(0, static_cast<int>(imageData[currentIdx + 1] - sumG)));
//             output[currentIdx + 2] = std::min(255, std::max(0, static_cast<int>(imageData[currentIdx + 2] - sumR)));
//         }
//     }

//     // 复制边界像素
//     for (size_t y = 0; y < height; ++y) {
//         for (size_t x = 0; x < width; ++x) {
//             if (y == 0 || y == height - 1 || x == 0 || x == width - 1) {
//                 size_t idx = (y * width + x) * 3;
//                 output[idx]     = imageData[idx];
//                 output[idx + 1] = imageData[idx + 1];
//                 output[idx + 2] = imageData[idx + 2];
//             }
//         }
//     }

//     // 将结果复制回原图
//     imageData = std::move(output);
// }