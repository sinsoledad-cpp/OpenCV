#include <opencv2/core/utils/logger.hpp>
#include<opencv2/core.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include<iostream>
//---basic function---
void main()
{
	cv::utils::logging::setLogLevel(cv::utils::logging::LOG_LEVEL_SILENT);//不再输出日志

	std::string path = "Resources/test.png";
	cv::Mat img = cv::imread(path);
	cv::Mat imgGray, imgBlur, imgCanny, imgDil, imgErode;
	cv::cvtColor(img, imgGray, cv::COLOR_BGR2GRAY);	

	cv::GaussianBlur(img, imgBlur, cv::Size(3, 3), 3, 0);

	cv::Canny(imgBlur, imgCanny, 25, 75);

	cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));
	cv::dilate(imgCanny, imgDil, kernel);

	cv::erode(imgDil, imgErode, kernel);

	cv::imshow("Image", img);
	cv::imshow("ImageGray", imgGray);
	cv::imshow("ImageBlur", imgBlur);
	cv::imshow("ImageCanny", imgCanny);
	cv::imshow("ImageDil", imgDil);
	cv::imshow("ImageErode", imgErode);
	cv::waitKey(0);
}
