#pragma once
#include <vector>
#include <stdexcept>
#include "Distribution.hpp"

// 算法接口
class Algorithm {
public:
    virtual ~Algorithm() = default;
    
    virtual void operator()(std::vector<unsigned char>& imageData) = 0; // 纯虚函数
    
    // 获取算法名称
    virtual const char* getName() const = 0;
};

// RGB转灰度算法
class GrayScale : public Algorithm {
public:
    void operator()(std::vector<unsigned char>& imageData) override; 

    const char* getName() const override {
        return "GrayScale";
    }
};

// 直方图均衡化算法
class HistogramEqual : public Algorithm {
public:
    HistogramEqual(bool isGray = false) : isGray(isGray) {}
    void operator()(std::vector<unsigned char>& imageData) override; 

    const char* getName() const override {
        return "HistogramEqual";
    }

private:
    bool isGray = false;
};