#include<opencv2/opencv.hpp>
#include<iostream>
#include<vector>

cv::Mat srcImage, dstImage, inrangeImage;
int hsv_min[3] = { 0 }, hsv_max[3] = {0};
void solve(int, void*)
{
	cv::inRange(inrangeImage, cv::Scalar(hsv_min[0], hsv_min[1], hsv_min[2]),
		cv::Scalar(hsv_max[0], hsv_max[1], hsv_max[2]), dstImage);
	cv::namedWindow("效果图");
	cv::imshow("效果图", dstImage);
}
int main()
{
	srcImage = cv::imread("Resources/lambo.png");
	cv::namedWindow("原图");
	cv::imshow("原图", srcImage);
	cv::cvtColor(srcImage, inrangeImage, cv::COLOR_BGR2HSV);
	cv::namedWindow("Trackbars", (640, 200));
	cv::createTrackbar("HueMin", "Trackbars", &hsv_min[0], 179,solve);
	cv::createTrackbar("HueMax", "Trackbars", &hsv_max[0], 179, solve);
	cv::createTrackbar("SatMin", "Trackbars", &hsv_min[1], 255, solve);
	cv::createTrackbar("SatMax", "Trackbars", &hsv_max[1], 255, solve);
	cv::createTrackbar("VakMin", "Trackbars", &hsv_min[2], 255, solve);
	cv::createTrackbar("VakMax", "Trackbars", &hsv_max[2], 255, solve);
	cv::waitKey(0);
	return 0;
}