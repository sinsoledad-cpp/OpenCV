#include<opencv2/opencv.hpp>
#include<iostream>
#include<vector>

#define WINDOW_NAME1 "原图"
#define WINDOW_NAME2 "效果"

cv::Mat g_srcImage;
cv::Mat g_grayImage;
int g_nThresh = 50;
int g_maxThresh = 255;
cv::RNG g_rng(12345);
cv::Mat srcImage_copy = g_srcImage.clone();
cv::Mat g_thresholdImage_output;
std::vector<std::vector<cv::Point>> g_vContours;
std::vector<cv::Vec4i> g_vHierarchy;
static void ShowHeloText();
void on_ThreshChange(int, void*);


int main()
{
	g_srcImage = cv::imread("Resources/lambo.png", 1);
	cv::cvtColor(g_srcImage, g_grayImage, cv::COLOR_BGR2GRAY);
	cv::blur(g_grayImage, g_grayImage, cv::Size(3, 3));

	cv::namedWindow(WINDOW_NAME1, cv::WINDOW_AUTOSIZE);


	cv::createTrackbar("阈值", WINDOW_NAME1, &g_nThresh, g_maxThresh, on_ThreshChange);
	on_ThreshChange(0, 0);

	cv::waitKey(0);
	return 0;
}

void ShowHeloText()
{
}

void on_ThreshChange(int, void*)
{
	cv::threshold(g_grayImage, g_thresholdImage_output, g_nThresh, 255, cv::THRESH_BINARY);
	cv::imshow(WINDOW_NAME1, g_thresholdImage_output);
	cv::findContours(g_thresholdImage_output, g_vContours, g_vHierarchy,
		cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE, cv::Point(0, 0));
	std::vector<std::vector<cv::Point>> hull(g_vContours.size());
	for (unsigned int i = 0; i < g_vContours.size(); i++)
	{
		cv::convexHull(cv::Mat(g_vContours[i]), hull[i], false);
	}
	cv::Mat drawing = cv::Mat::zeros(g_thresholdImage_output.size(), CV_8UC3);
	for (unsigned int i = 0; i < g_vContours.size(); i++)
	{
		cv::Scalar color = cv::Scalar(g_rng.uniform(0, 255), g_rng.uniform(0, 255), g_rng.uniform(0, 255));
		cv::drawContours(drawing, g_vContours, i, color, 1, 8, std::vector<cv::Vec4i>(), 0, cv::Point());
		cv::drawContours(drawing, hull, i, color, 1, 8, std::vector<cv::Vec4i>(), 0, cv::Point());

	}
	cv::imshow(WINDOW_NAME2, drawing);
}
