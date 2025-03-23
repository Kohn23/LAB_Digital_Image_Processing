#pragma once
#include <vector>
#include <stdexcept>

// 算法接口
class Algorithm {
public:
    virtual ~Algorithm() = default;
    
    // 运算符重载，对图像数据进行处理
    virtual void operator()(std::vector<unsigned char>& imageData, int width, int height) {
        throw std::runtime_error("Not implemented!");
    }; 
    
    // 获取算法名称
    virtual const char* getName() const = 0;
};

// RGB转灰度算法
class GrayScale : public Algorithm {
public:
    void operator()(std::vector<unsigned char>& imageData, int width, int height) override; 

    const char* getName() const override {
        return "GrayScale";
    }
};
