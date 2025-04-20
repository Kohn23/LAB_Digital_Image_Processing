#include "Image.hpp"

int main() {
    try
    {
        Image* bmp = new BMP();
        bmp->readImage("img/exp1_colored.bmp");
        bmp->processImage(new GrayScale());
        bmp->saveImage("img/new_read_test.bmp");
    }
    catch(const std::exception& e)
    {
        // 输出异常信息
        std::cerr << e.what() << '\n';
    }
    return 0;
}
