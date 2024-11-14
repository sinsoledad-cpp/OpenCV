#include <opencv2/core/utils/logger.hpp>
#include<opencv2/opencv.hpp>
#include<iostream>
#include<vector>

#define WINDOW_NAME1 "原图"
#define WINDOW_NAME2 "效果"

cv::Mat g_srcImage;
cv::Mat g_grayImage;
int g_nThresh = 100;
int g_maxThresh = 255;
cv::RNG g_rng(12345);
cv::Mat g_cannyMat_output;
std::vector<std::vector<cv::Point>> g_vContours;
std::vector<cv::Vec4i> g_vHierarchy;
static void ShowHeloText();
void on_ThreshChange(int, void*);


int main()
{
	cv::utils::logging::setLogLevel(cv::utils::logging::LOG_LEVEL_SILENT);//不再输出日志

	g_srcImage = cv::imread("Resources/lambo.png", 1);
	cv::cvtColor(g_srcImage, g_grayImage, cv::COLOR_BGR2GRAY);
	cv::blur(g_grayImage, g_grayImage, cv::Size(3, 3));

	cv::namedWindow(WINDOW_NAME1, cv::WINDOW_AUTOSIZE);
	cv::imshow(WINDOW_NAME1, g_srcImage);

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
	cv::Canny(g_grayImage, g_cannyMat_output, g_nThresh, g_nThresh*2, 3);

	cv::findContours(g_cannyMat_output, g_vContours, g_vHierarchy,
		cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE, cv::Point(0, 0));

	std::vector<cv::Moments> mu(g_vContours.size());

	for (unsigned int i = 0; i < g_vContours.size(); i++)
	{
		mu[i] = cv::moments(g_vContours[i], false);
		
	}
	std::vector<cv::Point2f> mc(g_vContours.size());
	for (unsigned int i = 0; i < g_vContours.size(); i++)
	{
		mc[i] = cv::Point2f(static_cast<float>(mu[i].m10 / mu[i].m00), static_cast<float>(mu[i].m01 / mu[i].m00));
	}
	cv::Mat drawing = cv::Mat::zeros(g_cannyMat_output.size(), CV_8UC3);
	for (unsigned int i = 0; i < g_vContours.size(); i++)
	{
		cv::Scalar color = cv::Scalar(g_rng.uniform(0, 255), g_rng.uniform(0, 255), g_rng.uniform(0, 255));
		cv::drawContours(drawing, g_vContours, i, 
			color, 2, 8, g_vHierarchy, 0, cv::Point());
		cv::circle(drawing, mc[i], 4, color);
	}
	//for (unsigned int i = 0; i < g_vContours.size(); i++)
	//{
	//	printf("轮廓%d\t面积1%.2f\t面积2%.2f\t和长度%.2f\n",
	//		i, mu[i].m00, cv::contourArea(g_vContours[i]), cv::arcLength(g_vContours, true));
	//	cv::Scalar color = cv::Scalar(g_rng.uniform(0, 255), g_rng.uniform(0, 255), g_rng.uniform(0, 255));
	//	cv::drawContours(drawing, g_vContours, i, color, 2, 8, g_vHierarchy, 0, cv::Point());
	//	cv::circle(drawing, mc[i], 4, color, -1, 8, 0);
	//}
	cv::namedWindow(WINDOW_NAME2, cv::WINDOW_AUTOSIZE);
	cv::imshow(WINDOW_NAME2, drawing);
}
