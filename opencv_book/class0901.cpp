#include<opencv2/opencv.hpp>
#include<iostream>
#include<vector>

#define WINDOW_NAME1 "原图1"
#define WINDOW_NAME2 "效果"

cv::Mat g_srcImage;
cv::Mat g_srcImage1;
cv::Mat g_grayImage;
int thresh=30;
int max_thresh = 175;
void on_CornerHarris(int, void*);
int main()
{
	g_srcImage = cv::imread("Resources/robot.png");
	if (!g_srcImage.data)
	{
		printf("err");
		return 0;
	}
	cv::imshow("原图", g_srcImage);
	g_srcImage1 = g_srcImage.clone();

	cv::cvtColor(g_srcImage1, g_grayImage, cv::COLOR_BGR2GRAY);

	cv::namedWindow(WINDOW_NAME1, cv::WINDOW_AUTOSIZE);
	cv::createTrackbar("阈值", WINDOW_NAME1, &thresh, max_thresh, on_CornerHarris);

	on_CornerHarris(0, 0);

	cv::waitKey(0);
	return 0;
}

void on_CornerHarris(int, void*)
{
	cv::Mat dstImage;
	cv::Mat normImage;
	cv::Mat scaledImage;

	dstImage = cv::Mat::zeros(g_srcImage.size(), CV_32FC1);
	g_srcImage1 = g_srcImage.clone();

	cv::cornerHarris(g_grayImage, dstImage, 2, 3, 0.04, cv::BORDER_DEFAULT);
	//cv::imshow("灰度图", g_grayImage);
	//cv::imshow("corner", dstImage);

	cv::normalize(dstImage, normImage, 0, 255, cv::NORM_MINMAX, CV_32FC1, cv::Mat());
	//cv::imshow("归一图", normImage);

	cv::convertScaleAbs(normImage, scaledImage);
	//cv::imshow("数据处理", scaledImage);

	for (int j = 0; j < normImage.rows; j++)
	{
		for (int i = 0; i < normImage.cols; i++)
		{
			if ((int)normImage.at<float>(j, i) > thresh + 100)
			{
				cv::circle(g_srcImage1, cv::Point(i, j), 3, cv::Scalar(100, 10, 255), 2, 8, 0);
				cv::circle(scaledImage, cv::Point(i, j), 3, cv::Scalar(0, 10, 255), 2, 8, 0);
			}
		}
	}

	cv::imshow(WINDOW_NAME1, g_srcImage1);
	cv::imshow(WINDOW_NAME2, scaledImage);
}
