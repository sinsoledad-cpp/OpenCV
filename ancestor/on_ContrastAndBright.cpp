#include<opencv2/opencv.hpp>
#include<iostream>
#include<vector>
static void on_ContrastAndBright(int, void*);
static void ShowHelpText();
int g_nContrastValue;
int g_nBrightValue;
cv::Mat g_srcImage, g_dstImage;
int main()
{
	g_srcImage = cv::imread("猫.png");
	g_dstImage = cv::Mat::zeros(g_srcImage.size(), g_srcImage.type());
	g_nBrightValue = 80;
	g_nContrastValue = 80;
	cv::namedWindow("效果窗口",1);
	cv::createTrackbar("对比度", "效果窗口", &g_nContrastValue, 300, on_ContrastAndBright);
	cv::createTrackbar("亮度", "效果窗口", &g_nBrightValue, 200, on_ContrastAndBright);
	on_ContrastAndBright(g_nBrightValue, 0);
	on_ContrastAndBright(g_nContrastValue, 0);

	cv::waitKey(0);
	return 0;
}
void on_ContrastAndBright(int, void*)
{
	cv::namedWindow("src", 1);
	for (int y = 0; y < g_dstImage.rows; y++)
	{
		for (int x = 0; x < g_dstImage.cols; x++)
		{
			for (int c = 0; c < 3; c++)
			{
				g_dstImage.at<cv::Vec3b>(y, x)[c] =
					cv::saturate_cast<uchar>((g_nContrastValue * 0.01) * (g_srcImage.at<cv::Vec3b>(y, x)[c]) 
						+ g_nBrightValue);
			}
		}
	}
	cv::imshow("src", g_srcImage);
	cv::imshow("效果窗口", g_dstImage);
}

void ShowHelpText()
{
}
