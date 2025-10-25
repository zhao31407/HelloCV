#include <opencv2/opencv.hpp>
#include <iostream>

int main() {
    std::cout << "测试 GUI 功能..." << std::endl;
    
    // 创建一张纯色图像（不依赖外部文件）
    cv::Mat test_image(300, 400, CV_8UC3, cv::Scalar(0, 100, 200)); // 蓝绿色
    
    // 添加文字
    cv::putText(test_image, "OpenCV GUI Test", cv::Point(50, 150), 
                cv::FONT_HERSHEY_SIMPLEX, 0.8, cv::Scalar(255, 255, 255), 2);
    
    std::cout << "创建图像成功，尝试显示窗口..." << std::endl;
    cv::imshow("测试窗口", test_image);
    std::cout << "窗口已显示，等待按键..." << std::endl;
    
    cv::waitKey(0); // 等待按键
    std::cout << "程序结束" << std::endl;
    
    return 0;
}