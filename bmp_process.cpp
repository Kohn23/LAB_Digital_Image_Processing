#include "bmp_process.hpp"

// 读取图像
void BMPProcessor::readImage(const std::string& filePath) {
    try {
        // 打开输入文件
        std::ifstream inputFile(filePath, std::ios::binary);
        if (!inputFile) {
            throw std::runtime_error("无法打开输入文件：" + filePath);
        }

        // 读取 BMP 文件头
        inputFile.read(reinterpret_cast<char*>(&header), sizeof(BMPHeader)); // read成员函数需要传入char*类型的指针, 所以需要强制类型转换
        if (!inputFile) {
            throw std::runtime_error("读取 BMP 文件头失败");
        }

        // 读取 BMP 信息头
        inputFile.read(reinterpret_cast<char*>(&infoHeader), sizeof(BMPInfoHeader));
        if (!inputFile) {
            throw std::runtime_error("读取 BMP 信息头失败");
        }

        // 检查是否是 24 位 BMP 文件
        if (infoHeader.bitCount != 24) {
            throw std::runtime_error("仅支持 24 位 BMP 文件");
        }

        // 计算图像数据的大小
        size_t dataSize = infoHeader.imageSize;
        if (dataSize == 0) {
            dataSize = infoHeader.width * infoHeader.height * 3;
        }

        // 读取图像数据
        imageData.resize(dataSize);
        inputFile.read(reinterpret_cast<char*>(imageData.data()), dataSize);
        if (!inputFile) {
            throw std::runtime_error("读取图像数据失败");
        }
    }
    // 捕获异常
    catch (const std::exception& e) {
        std::cerr << "ERROR: " << e.what() << std::endl;
        // 清理已分配的资源
        imageData.clear();
        header = BMPHeader();
        infoHeader = BMPInfoHeader();
    }
}

// 处理图像
void BMPProcessor::processImage(Algorithm* algorithm) {
    // 调用算法处理图像
    (*algorithm)(imageData, infoHeader.width, infoHeader.height);
    std::cout << "图像已处理：" << algorithm->getName() << std::endl;
}

// 保存图像
void BMPProcessor::saveImage(const std::string& filePath) {
    // 打开输出文件
    std::ofstream outputFile(filePath, std::ios::binary);
    if (!outputFile) {
        std::cerr << "无法打开输出文件！" << std::endl;
        return;
    }

    // 写入文件头和信息头
    outputFile.write(reinterpret_cast<const char*>(&header), sizeof(BMPHeader));
    outputFile.write(reinterpret_cast<const char*>(&infoHeader), sizeof(BMPInfoHeader));

    // 写入灰度图像数据
    outputFile.write(reinterpret_cast<const char*>(imageData.data()), imageData.size());
    std::cout << "灰度图像已保存到 " << filePath << std::endl;
}