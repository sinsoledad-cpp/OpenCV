#include<opencv2/opencv.hpp>
#include<iostream>
#define WINDOW_NAME "[程序窗口]"
cv::Mat src = cv::imread("Resources/shapes.png");
cv::Mat dst;
int value = 100;
int maxValue = 255;
int type = 1;
void onTreshold(int, void*)
{
	cv::threshold(src, dst, value, maxValue, type);
	cv::imshow(WINDOW_NAME, dst);
}
void main()
{
	cv::namedWindow("原图", cv::WINDOW_FREERATIO);
	cv::imshow("原图", src); 
	cv::cvtColor(src, src, cv::COLOR_RGB2GRAY);
	cv::namedWindow(WINDOW_NAME, cv::WINDOW_FREERATIO);
	cv::createTrackbar("模式", WINDOW_NAME, &type, 4, onTreshold);
	cv::createTrackbar("参数值", WINDOW_NAME, &value, 255, onTreshold);
	onTreshold(0, 0);

	//cv::imshow(WINDOW_NAME, src);
	cv::waitKey(0);
}