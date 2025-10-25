#include "video_process.h"
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

bool processVideoFrame(Mat& frame) {
    Mat hsv, red_mask, green_mask;
    
    cvtColor(frame, hsv, COLOR_BGR2HSV);
    
    inRange(hsv, Scalar(170, 120, 100), Scalar(180, 255, 255), red_mask);
    inRange(hsv, Scalar(35, 190, 120), Scalar(90, 255, 255), green_mask);
    
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
    
    return true;
}