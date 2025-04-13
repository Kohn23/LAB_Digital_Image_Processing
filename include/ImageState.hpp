#pragma once
#include <iostream>
/*为了防止Image和Algorithm相互引用，单独列出ImageState*/
/*这里也可以反映目前项目所支持的色彩模式*/

// 图像状态枚举
enum class ImageState {
    UNKNOWN,    // 未知状态
    RGB,        // RGB彩色图像
    GRAY,       // 灰度图像
};

// 头文件中使用内联函数
inline std::string ImageStateToString(ImageState state) {
    switch (state) {
        case ImageState::UNKNOWN: return "UNKNOWN";
        case ImageState::RGB: return "RGB";
        case ImageState::GRAY: return "GRAY";
        default: return "INVALID STATE";
    }
}