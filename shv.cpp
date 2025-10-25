#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

// 全局变量
Mat hsv, current_frame;
bool paused = false;

// 鼠标回调函数
void onMouse(int event, int x, int y, int flags, void* userdata) {
    if (event == EVENT_LBUTTONDOWN && paused) {
        // 检查坐标是否在图像范围内
        if (x >= 0 && x < hsv.cols && y >= 0 && y < hsv.rows) {
            Vec3b pixel = hsv.at<Vec3b>(y, x);
            
            cout << "点击位置(" << x << "," << y << ") HSV值: " 
                 << "H=" << (int)pixel[0] 
                 << " S=" << (int)pixel[1] 
                 << " V=" << (int)pixel[2] << endl;
                 
            // 在图像上标记点击位置
            circle(current_frame, Point(x, y), 8, Scalar(0, 0, 255), -1);  // 红色圆圈
            circle(current_frame, Point(x, y), 4, Scalar(255, 255, 255), -1);  // 白色内圈
            
            // 显示HSV值
            putText(current_frame, 
                    "H:" + to_string((int)pixel[0]) + 
                    " S:" + to_string((int)pixel[1]) + 
                    " V:" + to_string((int)pixel[2]), 
                    Point(x + 15, y), FONT_HERSHEY_SIMPLEX, 0.6, Scalar(255, 255, 255), 2);
            
            imshow("绿色HSV检测工具", current_frame);
        }
    }
}

int main() {
    VideoCapture cap;
    cap.open("TrafficLight.mp4");
    
    if (!cap.isOpened()) {
        cout << "错误：无法打开视频文件！" << endl;
        cout << "请检查文件是否存在" << endl;
        return -1;
    }
    
    // 获取视频信息
    double fps = cap.get(CAP_PROP_FPS);
    int total_frames = cap.get(CAP_PROP_FRAME_COUNT);
    
    cout << "视频信息：" << endl;
    cout << "帧率: " << fps << " FPS" << endl;
    cout << "总帧数: " << total_frames << " 帧" << endl;
    cout << endl;
    
    namedWindow("绿色HSV检测工具", WINDOW_NORMAL);
    resizeWindow("绿色HSV检测工具", 800, 600);
    setMouseCallback("绿色HSV检测工具", onMouse, NULL);
    
    cout << "=== 操作说明 ===" << endl;
    cout << "空格键: 暂停/继续视频" << endl;
    cout << "q 键: 退出程序" << endl;
    cout << "暂停时点击绿色区域查看HSV值" << endl;
    cout << "=================" << endl;
    
    while (true) {
        if (!paused) {
            cap >> current_frame;
            if (current_frame.empty()) {
                cout << "视频播放结束" << endl;
                break;
            }
            
            // 转换到HSV颜色空间
            cvtColor(current_frame, hsv, COLOR_BGR2HSV);
        }
        
        // 创建显示图像（添加状态信息）
        Mat display_frame = current_frame.clone();
        
        // 显示当前帧信息和状态
        int current_frame_pos = cap.get(CAP_PROP_POS_FRAMES);
        
        string status = paused ? "状态: [暂停] - 点击绿色区域获取HSV值" : "状态: [播放中]";
        putText(display_frame, status, Point(10, 30), 
                FONT_HERSHEY_SIMPLEX, 0.7, Scalar(255, 255, 255), 2);
        
        putText(display_frame, 
                "帧: " + to_string(current_frame_pos) + "/" + to_string(total_frames), 
                Point(10, 60), FONT_HERSHEY_SIMPLEX, 0.6, Scalar(255, 255, 255), 2);
        
        putText(display_frame, "操作: 空格=暂停/继续, Q=退出", 
                Point(10, display_frame.rows - 10), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255, 255, 255), 1);
        
        imshow("绿色HSV检测工具", display_frame);
        
        int key = waitKey(paused ? 0 : 30); // 暂停时无限等待，播放时30ms一帧
        
        if (key == ' ') { // 空格键暂停/继续
            paused = !paused;
            cout << (paused ? "=== 视频已暂停 ===" : "=== 继续播放 ===") << endl;
            if (paused) {
                cout << "现在可以点击绿色区域获取HSV值" << endl;
            }
        }
        else if (key == 'q' || key == 'Q') { // q键退出
            cout << "程序退出" << endl;
            break;
        }
    }
    
    cap.release();
    destroyAllWindows();
    return 0;
}