#include <opencv2/opencv.hpp>
#include<iostream>
using namespace cv;
using namespace std;

int main(){
    VideoCapture builtinCamera;
    builtinCamera.open(0);
    if(builtinCamera.isOpened()){
        cout<<"open";
        
        Mat frame;
        builtinCamera >> frame; 
        
        if(!frame.empty()) {     // 这个if应该在第一个if的大括号内
            imshow("Camera Test", frame);
            waitKey(0);
        }
        
        builtinCamera.release(); 
    }
    return 0;
}