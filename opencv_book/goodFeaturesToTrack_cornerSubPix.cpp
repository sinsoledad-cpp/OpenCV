#include<opencv2/opencv.hpp>
#include<iostream>
#include<vector>

#define WINDOW_NAME "角点检测"

cv::Mat g_srcImage, g_grayImage;;
int g_maxCornerNumber = 33;
int g_maxTrackbarNumber = 500;
cv::RNG g_rng(12345);

void on_GoodFeaturesToTrack(int, void*)
{
	if (g_maxCornerNumber <= 1)
	{
		g_maxCornerNumber = 1;
	}
	std::vector<cv::Point2f> corners;
	double qualityLevel = 0.01;
	double minDistance = 10;
	int blockSize = 3;
	double k = 0.04;
	cv::Mat copy = g_srcImage.clone();

	cv::goodFeaturesToTrack(g_grayImage,corners,g_maxCornerNumber,
		qualityLevel, minDistance, cv::Mat(), blockSize, false, k);

	std::cout << "本次角点数: " << corners.size() << std::endl;

	int r = 4;
	for (unsigned int i = 0; i < corners.size(); i++)
	{
		cv::circle(copy, corners[i], r, 
			cv::Scalar(g_rng.uniform(0, 255), g_rng.uniform(0, 255), g_rng.uniform(0, 255)),
			-1, 8, 0);
	}

	cv::imshow(WINDOW_NAME, copy);


	cv::Size winSize = cv::Size(5, 5);
	cv::Size zeroZone = cv::Size(-1, -1);
	cv::TermCriteria criteria = cv::TermCriteria(cv::TermCriteria::EPS + cv::TermCriteria::MAX_ITER, 40, 0.001);
	cv::cornerSubPix(g_grayImage, corners, winSize, zeroZone, criteria);
	for (int i = 0; i < corners.size(); i++)
	{
		std::cout << "\t>>精确角点坐[" << i << "](" << corners[i].x << "," << corners[i].y << ")" << std::endl;
	}
	
}

int main()
{
	g_srcImage = cv::imread("Resources/robot.png");
	cv::cvtColor(g_srcImage, g_grayImage, cv::COLOR_BGR2GRAY);

	cv::namedWindow(WINDOW_NAME, cv::WINDOW_AUTOSIZE);
	cv::createTrackbar("最大角点数", WINDOW_NAME, &g_maxCornerNumber, g_maxTrackbarNumber, on_GoodFeaturesToTrack);
	cv::imshow(WINDOW_NAME, g_srcImage);
	on_GoodFeaturesToTrack(0, 0);
	
	cv::waitKey(0);
	return 0;
}

