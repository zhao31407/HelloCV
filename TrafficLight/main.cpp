#include <opencv2/opencv.hpp>
#include <iostream>
#include "video_process.h"

using namespace cv;
using namespace std;

int main() {
    VideoCapture cap;
    // 修改为当前目录的视频文件
    cap.open("TrafficLight.mp4");
    
    if (!cap.isOpened()) {
        cout << "Error: Cannot open video file TrafficLight.mp4" << endl;
        cout << "Please make sure TrafficLight.mp4 is in the current directory." << endl;
        return -1;
    }
    
    // 获取原视频的帧率和尺寸
    double fps = cap.get(CAP_PROP_FPS);
    int width = cap.get(CAP_PROP_FRAME_WIDTH);
    int height = cap.get(CAP_PROP_FRAME_HEIGHT);
    
    cout << "Video opened successfully: " << width << "x" << height << " FPS: " << fps << endl;
    
    // 创建 VideoWriter 来保存结果视频
    VideoWriter writer;
    writer.open("result.avi", 
                VideoWriter::fourcc('M','J','P','G'), 
                fps, 
                Size(width, height));
    
    if (!writer.isOpened()) {
        cout << "Error: Cannot create result.avi" << endl;
        return -1;
    }
    
    while(true) {
        Mat frame, smallframe;
        cap >> frame;
        
        if (frame.empty()) {
            cout << "Video ended" << endl;
            break;
        }
        
        // 处理视频帧
        processVideoFrame(frame);
        
        // 保存处理后的帧到输出视频
        writer.write(frame);
        
        // 显示缩小后的帧
        resize(frame, smallframe, Size(), 0.5, 0.5);
        imshow("红绿灯灯灯", smallframe);
        
        if(waitKey(30) == 'q') {
            break;
        }
    }
    
    // 释放资源
    writer.release();
    cap.release();
    destroyAllWindows();
    
    cout << "视频已保存为 result.avi" << endl;
    
    return 0; 
}