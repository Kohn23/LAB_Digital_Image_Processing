#include "Image.hpp"

// 读取图像
void BMP::readImage(const std::string& filePath) {
    try {
        // 清理已分配的资源
        imageData.clear();
        header = BMPHeader();
        infoHeader = BMPInfoHeader();
        this->filePath.clear();

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

        // 记录处理文件路径
        this->filePath = filePath;
        // 设置图像状态为 RGB
        imageState = ImageState::RGB;
    }
    // 捕获并立即处理异常
    catch (const std::exception& e) {
        // 清理已分配的资源
        imageData.clear();
        header = BMPHeader();
        infoHeader = BMPInfoHeader();
        this->filePath.clear();
        // 抛出异常
        throw;
    }
}

// 处理图像
void BMP::processImage(Algorithm* algorithm) {
    try {
        // 检查算法的输入状态要求
        if (algorithm->getInputState() != imageState) {
            throw std::runtime_error(
                std::string("算法 ") + 
                std::string(algorithm->getName()) +
                std::string(" 需要的状态为 ") +
                ImageStateToString(algorithm->getInputState()) +
                std::string("，但当前图片状态为 ") + 
                ImageStateToString(imageState)
            );
        }

        // 调用算法处理图像
        (*algorithm)(imageData);
        
        // 更新图像状态
        setState(algorithm->getOutputState());
        
        std::cout << "图像已处理：" << algorithm->getName() << std::endl;
    }
    catch (const std::exception& e) {
        throw;
    }
}

// 保存图像
void BMP::saveImage(const std::string& filePath) {
    // 打开输出文件
    std::ofstream outputFile(filePath, std::ios::binary);
    if (!outputFile) {
        throw std::runtime_error("无法打开输出文件：" + filePath);
    }

    // 写入文件头和信息头
    outputFile.write(reinterpret_cast<const char*>(&header), sizeof(BMPHeader));
    outputFile.write(reinterpret_cast<const char*>(&infoHeader), sizeof(BMPInfoHeader));

    // 写入图像数据
    if (imageData.empty()) {
        throw std::runtime_error("图像数据为空，无法保存！");
    }
    outputFile.write(reinterpret_cast<const char*>(imageData.data()), imageData.size());
    std::cout << "图像已保存：" << filePath << std::endl;
}
