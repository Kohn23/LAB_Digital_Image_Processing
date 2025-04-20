#include "Image.hpp"

// 读取图像
// 由于BMP图像的四位补全特性，读取时需要考虑行的填充字节
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
        inputFile.read(reinterpret_cast<char*>(&header), sizeof(BMPHeader));
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

        // 计算四位补全参数
        const size_t width = infoHeader.width;
        const size_t height = infoHeader.height;
        const size_t channels = 3; // 24位BMP为3通道
        const size_t bytes_per_row = width * channels; // 每行有效字节数
        const size_t padding = (4 - (bytes_per_row % 4)) % 4; // 每行填充字节数

        // 调整 imageData 大小以仅存储有效像素数据
        imageData.resize(width * height * channels);

        // 跳过可能的文件头后的保留区域
        inputFile.seekg(header.dataOffset, std::ios::beg);

        // 逐行读取像素数据，跳过填充字节
        for (size_t y = 0; y < height; ++y) {
            // 计算当前行的起始位置
            size_t row_start = y * width * channels;
            // 读取有效像素数据
            inputFile.read(reinterpret_cast<char*>(imageData.data() + row_start), bytes_per_row);
            if (!inputFile) {
                throw std::runtime_error("读取图像数据失败");
            }
            // 跳过填充字节
            inputFile.seekg(padding, std::ios::cur);
        }

        // 记录处理文件路径
        this->filePath = filePath;
        // 设置图像状态为 RGB
        imageState = ImageState::RGB;
    }
    catch (const std::exception& e) {
        // 清理已分配的资源
        imageData.clear();
        header = BMPHeader();
        infoHeader = BMPInfoHeader();
        this->filePath.clear();
        throw;
    }
}

// 处理图像
void BMP::processImage(Algorithm* algorithm) {
    try {
        // 检查算法的输入状态要求
        if (algorithm->getInputState() != imageState && algorithm->getInputState() != ImageState::ANY) {
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
        (*algorithm)(imageData, infoHeader.width, infoHeader.height);
        
        // 更新图像状态
        if (algorithm->getOutputState() != ImageState::ANY) {
            imageState = algorithm->getOutputState();
        }
        
        std::cout << "图像已处理：" << algorithm->getName() << std::endl;
    }
    catch (const std::exception& e) {
        throw;
    }
}

// // 保存图像
// void BMP::saveImage(const std::string& filePath) {
//     // 打开输出文件
//     std::ofstream outputFile(filePath, std::ios::binary);
//     if (!outputFile) {
//         throw std::runtime_error("无法打开输出文件：" + filePath);
//     }

//     // 写入文件头和信息头
//     outputFile.write(reinterpret_cast<const char*>(&header), sizeof(BMPHeader));
//     outputFile.write(reinterpret_cast<const char*>(&infoHeader), sizeof(BMPInfoHeader));

//     // 写入图像数据
//     if (imageData.empty()) {
//         throw std::runtime_error("图像数据为空，无法保存！");
//     }
//     outputFile.write(reinterpret_cast<const char*>(imageData.data()), imageData.size());
//     std::cout << "图像已保存：" << filePath << std::endl;
// }
    
// 保存图像
// 由于BMP图像的四位补全特性，保存时需要考虑行的填充字节
void BMP::saveImage(const std::string& filePath) {
    // 打开输出文件
    std::ofstream outputFile(filePath, std::ios::binary);
    if (!outputFile) {
        throw std::runtime_error("无法打开输出文件：" + filePath);
    }

    // 计算四位补全参数
    const size_t width = infoHeader.width;
    const size_t height = infoHeader.height;
    const size_t channels = 3; // 24位BMP为3通道
    const size_t bytes_per_row = width * channels; // 有效像素数据长度
    const size_t padding = (4 - (bytes_per_row % 4)) % 4; // 每行填充字节数
    const size_t stride = bytes_per_row + padding; // 每行实际存储长度（含填充）

    // 更新 BMP 信息头中的 imageSize（含填充）
    infoHeader.imageSize = stride * height;

    // 写入更新后的文件头和信息头
    outputFile.write(reinterpret_cast<const char*>(&header), sizeof(BMPHeader));
    outputFile.write(reinterpret_cast<const char*>(&infoHeader), sizeof(BMPInfoHeader));

    // 写入图像数据（逐行添加填充）
    if (imageData.empty()) {
        throw std::runtime_error("图像数据为空，无法保存！");
    }

    // 填充字节（全0）
    const std::vector<unsigned char> pad(padding, 0);

    // 逐行写入数据
    for (size_t y = 0; y < height; ++y) {
        // 写入有效像素数据
        size_t row_start = y * bytes_per_row;
        outputFile.write(
            reinterpret_cast<const char*>(imageData.data() + row_start),
            bytes_per_row
        );
        // 写入填充字节
        outputFile.write(reinterpret_cast<const char*>(pad.data()), padding);
    }

    std::cout << "图像已保存：" << filePath << std::endl;
}
