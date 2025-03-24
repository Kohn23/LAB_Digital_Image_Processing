#include "Image.hpp"

int main() {
    try
    {
        Image* bmp = new BMP();
        bmp->readImage("image/exp2_highlight.bmp");       // 读取图像
        bmp->processImage(new GrayScale());               // 处理图像
        bmp->processImage(new HistogramEqual());      // 处理图像
        bmp->saveImage("image/equal_highlight_result.bmp");     // 保存图像
    }
    catch(const std::exception& e)
    {
        // 输出异常信息
        std::cerr << e.what() << '\n';
    }
    return 0;
}