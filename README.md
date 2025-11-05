<!-- # 数字图像处理实验项目说明

## 实验内容

1. **灰度图像转换**  
   将彩色图像转换为灰度图像

2. **直方图均衡**  
   通过调整像素分布增强图像对比度

3. **滤波器处理**  
   - 平滑滤波（如均值滤波、高斯滤波）  
   - 锐化滤波（如拉普拉斯算子、Sobel算子）

---

## 如何运行本项目

0. **环境配置**  
   实验在VSCode下完成，需安装：  
   - 编译器：`g++`（mingw-w64 v8.10）  
   - 构建工具：`make`

1. **修改配置**
    在demo.cpp中，根据需要修改内容：
    - 图片路径
    - 算法

2. **编译与运行**
    在vscode内打开终端：
    - 输入 make 命令，编译链接项目到bin文件夹下
    - 输入 bin\demo ，运行可执行文件

## 注意事项

1. 本实验所有图片都是24位BMP图片，请首先使用画图工具转换图片格式 -->

# Digital Image Processing Lab Project – README

## Content

1. **Grayscale Conversion**  
   Convert a color image to grayscale.

2. **Histogram Equalization**  
   Enhance image contrast by redistributing pixel intensities.

3. **Filtering**
   - Smoothing: mean filter, Gaussian filter  
   - Sharpening: Laplacian kernel, Sobel operators


## How to Run

0. **Environment**  
   Developed and tested in VSCode. Install:
   - Compiler: `g++` (mingw-w64 v8.10)  
   - Build tool: `make`

1. **Edit Configuration**  
   Open `demo.cpp` and adjust:
   - Input image path  
   - Algorithm parameters / switches

2. **Build & Execute**  
   Inside VSCode terminal:
   ```bash
   make              # builds the project; output goes to ./bin
   bin\demo          # run the executable
   ```

## Notes

- All images must be 24-bit BMP format. Convert any other format with Paint (or equivalent) before use.