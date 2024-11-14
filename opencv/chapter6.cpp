#include <opencv2/core/utils/logger.hpp>
#include<opencv2/core.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include<iostream>

cv::Mat imgHSV, mask;
//int hmin = 0, smin = 64, vmin = 156;
//int hmax = 46, smax = 252, vmax = 255;

int hmin = 0, smin = 0, vmin = 0;
int hmax = 179, smax = 255, vmax = 255;



void main()
{

	cv::utils::logging::setLogLevel(cv::utils::logging::LOG_LEVEL_SILENT);//不再输出日志

	std::string path = "Resources/shapes.png";
	cv::Mat img = cv::imread(path);
	cv::cvtColor(img, imgHSV, cv::COLOR_BGR2HSV);

	cv::namedWindow("Trackbars", (640, 200));
	cv::createTrackbar("HueMin", "Trackbars", &hmin, 179);
	cv::createTrackbar("HueMax", "Trackbars", &hmax, 179);
	cv::createTrackbar("SatMin", "Trackbars", &smin, 255);
	cv::createTrackbar("SatMax", "Trackbars", &smax, 255);
	cv::createTrackbar("VakMin", "Trackbars", &vmin, 255);
	cv::createTrackbar("VakMax", "Trackbars", &vmax, 255);

	while (true)
	{
		cv::Scalar lower(hmin, smin, vmin);
		cv::Scalar upper(hmax, smax, vmax);
		cv::inRange(imgHSV, lower, upper, mask);

		cv::imshow("Image", img);
		cv::imshow("ImageHSV", imgHSV);
		cv::imshow("ImageMask", mask);
		cv::waitKey(1);

	}
}

