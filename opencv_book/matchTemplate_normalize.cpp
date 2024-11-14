#include<opencv2/opencv.hpp>
#include<iostream>
#include<vector>

#define WINDOW_NAME1 "原图"
#define WINDOW_NAME2 "效果"

cv::Mat g_srcImage;
cv::Mat g_templateImage;
cv::Mat g_resultImage;
int g_nMatchMethod;
int g_nMaxTrackbarNum = 5;
void on_Matching(int, void*);

int main()
{
	g_srcImage = cv::imread("Resources/test.png");
	g_templateImage = cv::imread("Resources/test_s.png");

	cv::namedWindow(WINDOW_NAME1, cv::WINDOW_AUTOSIZE);
	cv::namedWindow(WINDOW_NAME2, 1);

	cv::createTrackbar("方法", WINDOW_NAME1, &g_nMatchMethod, g_nMaxTrackbarNum, on_Matching);
	on_Matching(0, 0);

	cv::waitKey(0);
	return 0;
}

void on_Matching(int, void*)
{
	cv::Mat srcImage;
	g_srcImage.copyTo(srcImage);

	int resultImage_cols = g_srcImage.cols - g_templateImage.cols + 1;
	int resultImage_rows = g_srcImage.rows - g_templateImage.rows + 1;
	g_resultImage.create(resultImage_cols, resultImage_rows, CV_32FC1);

	cv::matchTemplate(g_srcImage, g_templateImage, g_resultImage, g_nMatchMethod);
	cv::normalize(g_resultImage, g_resultImage, 0, 1, cv::NORM_MINMAX, -1);

	double minValue;
	double maxValue;
	cv::Point minLocation;
	cv::Point maxLocation;
	cv::Point matchLocation;
	cv::minMaxLoc(g_resultImage, &minValue, &maxValue, &minLocation, &maxLocation, cv::Mat());

	if (g_nMatchMethod == cv::TM_SQDIFF || g_nMatchMethod == cv::TM_SQDIFF_NORMED)
	{
		matchLocation = minLocation;
	}
	else
	{
		matchLocation = maxLocation;
	}
	cv::rectangle(srcImage, matchLocation,
		cv::Point(matchLocation.x + g_templateImage.cols, matchLocation.y + g_templateImage.rows),
		cv::Scalar(0, 0, 255), 2, 8, 0);
	cv::rectangle(g_resultImage, matchLocation,
		cv::Point(matchLocation.x + g_templateImage.cols, matchLocation.y + g_templateImage.rows),
		cv::Scalar(0, 0, 255), 2, 8, 0);
	cv::imshow(WINDOW_NAME1, srcImage);
	cv::imshow(WINDOW_NAME2, g_resultImage);
}
