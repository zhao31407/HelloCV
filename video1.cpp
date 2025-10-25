#include <opencv2/opencv.hpp>
#include<iostream>
using namespace cv;
using namespace std;

int main(){
    // 使用视频文件测试
    VideoCapture cap("Trafficlight.mp4");  // 放一个视频文件在程序同目录
    
    if(cap.isOpened()){
        cout << "视频文件打开成功！" << endl;
        
        Mat frame;
        while(true) {
            cap >> frame; 
            if(frame.empty()) break;
            
            imshow("视频测试", frame);
            if(waitKey(30) == 27) break;  // ESC退出
        }
        cap.release();
    } else {
        cout << "请放一个test_video.mp4文件在程序目录" << endl;
    }
    return 0;
}