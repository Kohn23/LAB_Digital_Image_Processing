#include "Image.hpp"

int main() {
    try
    {
        Image* bmp = new BMP();
        bmp->readImage("img/exp2_haze.bmp");       // 读取图像
        bmp->processImage(new GrayScale());        // 处理图像
        bmp->processImage(new HistogramEqual());      // 处理图像
        bmp->saveImage("img/exp2_haze_result.bmp");  // 保存图像
    }
    catch(const std::exception& e)
    {
        // 输出异常信息
        std::cerr << e.what() << '\n';
    }
    return 0;
}