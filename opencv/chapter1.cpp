#include <opencv2/core/utils/logger.hpp>
#include<opencv2/core.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include<iostream>
//---image---
void main()
{
	cv::utils::logging::setLogLevel(cv::utils::logging::LOG_LEVEL_SILENT);//不再输出日志

	//或
	//utils::logging::setLogLevel(utils::logging::LOG_LEVEL_ERROR);//只输出错误日志
	std::string path = "Resources/test.png";
	cv::Mat img = cv::imread(path);
	cv::imshow("Image", img);
	cv::waitKey(0);
}
//---video---
void main()
{
	cv::utils::logging::setLogLevel(cv::utils::logging::LOG_LEVEL_SILENT);//不再输出日志

	std::string path = "Resources/test_video.mp4";
	cv::VideoCapture cap(path);
	cv::Mat img;
	while (true)
	{
		cap.read(img);
		cv::imshow("Image", img);
		cv::waitKey(20);
	}
}
//---webcom---
void main()
{
	cv::utils::logging::setLogLevel(cv::utils::logging::LOG_LEVEL_SILENT);//不再输出日志


	cv::VideoCapture cap(0);
	cv::Mat img;
	while (true)
	{
		cap.read(img);
		cv::imshow("Image", img);
		cv::waitKey(20);
	}
}