#include <opencv2/opencv.hpp>
#include <iostream> 

int main(){

cv::Mat image_color = cv::imread("1.jpg", cv::IMREAD_COLOR);
cv::imshow("1.jpg",image_color);
cv::waitKey(0); 
 cv::imwrite("2.jpg",image_color);
return 0
;}