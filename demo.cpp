#include"bmp_process.cpp"
#include"GrayScale.cpp"

int main() {
    std::string inputFilePath = "image/image1.bmp";         // 输入文件路径
    std::string outputFilePath = "image/grayscale_result.bmp";  // 输出文件路径

    ImageProcessor* processor = new BMPProcessor();
    processor->readImage(inputFilePath);                    // 读取图像
    processor->processImage(new GrayScale());               // 处理图像
    processor->saveImage(outputFilePath);                   // 保存图像

    return 0;
}