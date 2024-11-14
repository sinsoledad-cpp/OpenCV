#include<opencv2/opencv.hpp>
#include<iostream>
#include<vector>

#define WINDOW_NAME "程序窗口"

int g_nThresholdValue = 100;
int g_nThresholdType = 3;
cv::Mat g_srcImage, g_grayImage, g_dstImage;

static void ShowHelpText();
void on_Threshold(int, void*);

int main()
{
	g_srcImage = cv::imread("Resources/lambo.png");

	cv::cvtColor(g_srcImage, g_grayImage, cv::COLOR_RGB2GRAY);
	cv::namedWindow(WINDOW_NAME, cv::WINDOW_AUTOSIZE);

	cv::createTrackbar("模式", WINDOW_NAME, &g_nThresholdType, 4, on_Threshold);
	cv::createTrackbar("参数值", WINDOW_NAME, &g_nThresholdValue, 255, on_Threshold);

	on_Threshold(0, 0);

	while (1)
	{
		int key;
		key = cv::waitKey(20);
		if ((char)key == 27)
		{
			break;
		}
	}

	cv::waitKey(0);
	return 0;
}


void on_Threshold(int, void*)
{
	cv::threshold(g_grayImage, g_dstImage, g_nThresholdValue, 255, g_nThresholdType);
	cv::imshow(WINDOW_NAME, g_dstImage);
}