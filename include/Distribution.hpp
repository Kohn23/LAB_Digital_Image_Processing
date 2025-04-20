#pragma once
#include <vector>
#include <memory>

// 数据接口
class Distribution {
public:
    Distribution(int size = 256) : data(size, 0), totalCount(0) {} // 默认8位图像
    virtual ~Distribution() = default;

    // 处理数据
    virtual void normalize() {for (size_t i = 0; i < data.size(); ++i) {data[i] = data[i] / totalCount;}};

    // 获取数据
    virtual const std::vector<float>& getData() const { return data; }
    virtual int getCount() const { return totalCount; }

protected:
    std::vector<float> data;
    int totalCount;
};

// 直方图类
class Histogram : public Distribution {
public:
    Histogram(const std::vector<unsigned char>& imageData, int size = 256) ;
};

// 累积直方图类
class CDF : public Distribution {
public:
    CDF(const Distribution& other, int size = 256) ;
};