#include "Image.hpp"

int main() {
    try
    {
        Image* bmp = new BMP();
        bmp->readImage("img/exp3_sharpening.bmp");
        bmp->processImage(new GrayScale());
        bmp->processImage(new SobelSharpening());
        bmp->saveImage("img/exp3_mySobel3.bmp");
    }
    catch(const std::exception& e)
    {
        // 输出异常信息
        std::cerr << e.what() << '\n';
    }
    return 0;
}
