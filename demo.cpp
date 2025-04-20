#include "Image.hpp"

int main() {
    try
    {
        Image* bmp = new BMP();
        bmp->readImage("img/exp3_smoothing.bmp");       // 读取图像
        bmp->processImage(new BoxSmoothing()); // 处理图像
        bmp->saveImage("img/exp3_box_smoothing.bmp");  // 保存图像
    }
    catch(const std::exception& e)
    {
        // 输出异常信息
        std::cerr << e.what() << '\n';
    }
    return 0;
}