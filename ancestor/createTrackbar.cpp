#include<opencv2/opencv.hpp>
#include<iostream>
#define WINDOW_NAME "[���򴰿�]"
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
	cv::namedWindow("ԭͼ", cv::WINDOW_FREERATIO);
	cv::imshow("ԭͼ", src); 
	cv::cvtColor(src, src, cv::COLOR_RGB2GRAY);
	cv::namedWindow(WINDOW_NAME, cv::WINDOW_FREERATIO);
	cv::createTrackbar("ģʽ", WINDOW_NAME, &type, 4, onTreshold);
	cv::createTrackbar("����ֵ", WINDOW_NAME, &value, 255, onTreshold);
	onTreshold(0, 0);

	//cv::imshow(WINDOW_NAME, src);
	cv::waitKey(0);
}