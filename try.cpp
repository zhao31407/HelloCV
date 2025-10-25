#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(){
    VideoCapture cap;
    cap.open("TrafficLight.mp4");
    
    if(cap.isOpened()){
        Mat frame, grayFrame;  // 在这里声明grayFrame
        
        cap >> frame;           
        
        // 先进行灰度化处理
        cvtColor(frame, grayFrame, COLOR_BGR2GRAY);
        
        // 然后显示结果
        imshow("原始视频", frame); 
        imshow("灰度视频", grayFrame);
        
        waitKey(0);  
    }
    
    return 0; 
}