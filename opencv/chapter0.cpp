#include <opencv2/core/utils/logger.hpp>
#include<opencv2/core.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include<iostream>

void main()
{
	cv::utils::logging::setLogLevel(cv::utils::logging::LOG_LEVEL_SILENT);//不再输出日志
	cv::Mat img(512, 512, CV_8UC3, cv::Scalar(255, 255, 255));//bgr
	cv::circle(img, cv::Point(256, 256), 150, cv::Scalar(0, 0, 255), cv::FILLED);
	cv::rectangle(img, cv::Point(156, 206), cv::Point(356, 266), cv::Scalar(255, 255, 255), cv::FILLED);
	cv::line(img, cv::Point(156, 296), cv::Point(356, 296), cv::Scalar(255, 0, 0), 10);
	cv::putText(img, "hello world", cv::Point(160, 246), cv::FONT_HERSHEY_COMPLEX, 1, cv::Scalar(0, 0, 0), 2);
	cv::imshow("Image", img);
	cv::waitKey(0);
}

