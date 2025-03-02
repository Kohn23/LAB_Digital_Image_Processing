#pragma once
#include "image_process.hpp"

// BMP 头部结构体
#pragma pack(push, 1)          // 以 1 字节对齐
struct BMPHeader {
    char signature[2];         // BMP 签名 ("BM")
    int fileSize;              // 文件大小
    int reserved;              // 保留字
    int dataOffset;            // 数据偏移量
};

struct BMPInfoHeader {
    int size;                  // 信息头大小
    int width;                 // 图像宽度
    int height;                // 图像高度
    short planes;              // 平面数
    short bitCount;            // 每像素位数
    int compression;           // 压缩方法
    int imageSize;             // 图像大小
    int xPelsPerMeter;         // 水平分辨率
    int yPelsPerMeter;         // 垂直分辨率
    int colorsUsed;            // 使用的颜色数
    int colorsImportant;       // 重要的颜色数
};
#pragma pack(pop)              // 恢复默认对齐方式



// BMP 图像处理器
class BMPProcessor : public ImageProcessor {
public:
    BMPProcessor() = default;
    ~BMPProcessor() override = default;

    virtual void readImage(const std::string& filePath) override;
    virtual void processImage(Algorithm* algorithm) override;
    virtual void saveImage(const std::string& filePath) override;

private:
    BMPHeader header;
    BMPInfoHeader infoHeader;
    std::vector<unsigned char> imageData;
};
