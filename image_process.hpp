#pragma once
#include "Algorithm.hpp"
#include <iostream>
#include <fstream>


// 图像处理器接口
class ImageProcessor {
public:
    virtual ~ImageProcessor() = default;
    virtual void readImage(const std::string& filePath) = 0;
    virtual void processImage(Algorithm* algorithm) = 0;
    virtual void saveImage(const std::string& filePath) = 0;
};
