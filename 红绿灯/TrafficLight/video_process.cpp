#include "video_process.h"
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

bool processVideoFrame(Mat& frame) {
    Mat hsv, red_mask, green_mask,yellow_mask;
    
    cvtColor(frame, hsv, COLOR_BGR2HSV);
    
    inRange(hsv, Scalar(170, 120, 100), Scalar(180, 255, 255), red_mask);
    inRange(hsv, Scalar(35, 190, 120), Scalar(90, 255, 255), green_mask);
    inRange(hsv, Scalar(10, 30, 100), Scalar(30, 150, 255), yellow_mask);
    vector<vector<Point>> red_contours;
    findContours(red_mask, red_contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
    
    for(auto redcontour : red_contours) {
        if(contourArea(redcontour) > 17000) {
            Rect redbox = boundingRect(redcontour);
            rectangle(frame, redbox, Scalar(0, 0, 225), 3);
            putText(frame, "RED", Point(100, 100), 
                    FONT_HERSHEY_SIMPLEX, 1.8, Scalar(0, 0, 225), 2);
        }
    }
    vector<vector<Point>> green_contours;
    findContours(green_mask, green_contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
    
    for(auto greencontour : green_contours) {
        if(contourArea(greencontour) > 17000) {
            Rect greenbox = boundingRect(greencontour);
            rectangle(frame, greenbox, Scalar(0, 225, 0), 3);
            putText(frame, "GREEN", Point(100, 100), 
                    FONT_HERSHEY_SIMPLEX, 1.8, Scalar(0, 225, 0), 2);
        }
    }
    // 增强的黄色区域连接处理 - 加大模糊
    Mat yellow_processed;
    
    // 1. 先强力高斯模糊消除不连续区域（加大模糊核）
    GaussianBlur(yellow_mask, yellow_processed, Size(51, 51), 8.0);  // 核大小15x15，sigma=3.0
    
    // 2. 重新阈值化（可以调整阈值来更好地连接区域）
    threshold(yellow_processed, yellow_processed, 50, 255, THRESH_BINARY);  // 降低阈值到50
    
    // 3. 再次高斯模糊进一步平滑
    GaussianBlur(yellow_processed, yellow_processed, Size(31, 31), 6.0);
    
    // 4. 再次阈值化
    threshold(yellow_processed, yellow_processed, 100, 255, THRESH_BINARY);
    
    
    // 4. 超强闭运算连接
    Mat kernel1 = getStructuringElement(MORPH_RECT, Size(61, 61));  // 巨大内核61x61
    morphologyEx(yellow_processed, yellow_processed, MORPH_CLOSE, kernel1, Point(-1,-1), 3);
    
    // 5. 第二次闭运算确保完全连接
    Mat kernel2 = getStructuringElement(MORPH_RECT, Size(41, 41));
    morphologyEx(yellow_processed, yellow_processed, MORPH_CLOSE, kernel2, Point(-1,-1), 2);
    // 6. 填充内部空洞
    Mat yellow_filled = yellow_processed.clone();
    vector<vector<Point>> contours_temp;
    findContours(yellow_filled, contours_temp, RETR_CCOMP, CHAIN_APPROX_SIMPLE);
    for (int i = 0; i < contours_temp.size(); i++) {
        drawContours(yellow_filled, contours_temp, i, Scalar(255), -1);  // 填充轮廓
    }
    
    
    for (int i = 0; i < contours_temp.size(); i++) {
        drawContours(yellow_filled, contours_temp, i, Scalar(255), -1);  // 填充轮廓
    }
    
    vector<vector<Point>> yellow_contours;
    findContours(yellow_filled, yellow_contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
    
    
    for(auto yellowcontour : yellow_contours) {
        if(contourArea(yellowcontour) > 3000) {
            Rect yellowbox = boundingRect(yellowcontour);
            rectangle(frame, yellowbox, Scalar(0, 225, 225), 3);
            putText(frame, "YELLOW", Point(100, 100), 
                    FONT_HERSHEY_SIMPLEX, 1.8, Scalar(0, 225, 225), 2);
        }
    }
    
    return true;
}