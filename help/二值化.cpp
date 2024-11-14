#include <opencv2/core/utils/logger.hpp>
#include<opencv2/core.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include<iostream>
//---basic function---
cv::Mat image, imageResize, imageGray, imageBlur, imagethresh, imageDil, imageErode;
int thresh = 80;

void solve(int, void*)
{
	cv::threshold(imageGray, imagethresh, thresh, 255, cv::THRESH_BINARY); 
	cv::imshow("Thresh", imagethresh);
}

int main()
{
	cv::utils::logging::setLogLevel(cv::utils::logging::LOG_LEVEL_SILENT);//不再输出日志

	std::string path = "D:/NHJ/Documents/Visual Studio 2022/VS 2022/Projects/opencv_help/项目/五角星.png"; 
	image = cv::imread(path);
	cv::resize(image, imageResize, cv::Size(), 0.3, 0.3);
	cv::cvtColor(imageResize, imageGray, cv::COLOR_BGR2GRAY);

	cv::imshow("imageresize", imageResize);
	cv::namedWindow("Trackbars", (640, 200));

	cv::createTrackbar("thresh", "Trackbars", &thresh, 255, solve);
	solve(0,0);
	cv::waitKey(0);
	return 0;
}