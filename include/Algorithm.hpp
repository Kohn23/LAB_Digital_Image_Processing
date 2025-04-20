#pragma once
#include <vector>
#include <stdexcept>
#include "Distribution.hpp"
#include "ImageState.hpp"
#include "Filter.hpp"

// 算法接口
class Algorithm {
public:
    virtual ~Algorithm() = default;
    // 处理图像数据
    virtual void operator()(std::vector<unsigned char>& imageData, size_t width, size_t height) = 0;
    // 获取算法名称
    virtual const char* getName() const = 0;
    // 获取算法的输入状态要求
    virtual ImageState getInputState() const = 0;
    // 获取算法处理后的输出状态
    virtual ImageState getOutputState() const = 0;
};

// RGB转灰度算法
class GrayScale : public Algorithm {
public:
    void operator()(std::vector<unsigned char>& imageData, size_t width, size_t height) override;

    ImageState getInputState() const override { return ImageState::RGB; }
    ImageState getOutputState() const override { return ImageState::GRAY; }
    const char* getName() const override { return "GrayScale"; }
};

// 直方图均衡化算法
class HistogramEqual : public Algorithm {
public:
    void operator()(std::vector<unsigned char>& imageData, size_t width, size_t height) override; 

    const char* getName() const override { return "HistogramEqual";}
    ImageState getInputState() const override { return ImageState::GRAY; }
    ImageState getOutputState() const override { return ImageState::GRAY; }
};

// 填边
class Padding{
public:
    void operator()(const std::vector<unsigned char>& inputPlane, std::vector<unsigned char>& outputPlane, size_t inputWidth, size_t inputHeight, int padWidth, int padHeight);
};

// 卷积
class Convol2d{
public:
    void operator()(const std::vector<unsigned char>& inputPlane, std::vector<unsigned char>& outputPlane, size_t inputWidth, size_t inputHeight, Filter& filter);
};

// 平滑滤波
class SmoothingFilter : public Algorithm {
public:
    void operator()(std::vector<unsigned char>& imageData, size_t width, size_t height) override;

    const char* getName() const override { return "SmoothingFilter";}
    ImageState getInputState() const override { return ImageState::ANY; }
    ImageState getOutputState() const override { return ImageState::ANY; }
};
