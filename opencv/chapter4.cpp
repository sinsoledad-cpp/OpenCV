#include <opencv2/core/utils/logger.hpp>
#include<opencv2/core.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include<iostream>
//---resize and crop---
void main()
{
	cv::utils::logging::setLogLevel(cv::utils::logging::LOG_LEVEL_SILENT);//不再输出日志
	cv::Mat img1(512, 512, CV_8UC3, cv::Scalar(255, 255, 255));//bgr

	cv::circle(img1, cv::Point(256, 256), 155, cv::Scalar(0, 69, 255));
	cv::circle(img1, cv::Point(256, 256), 100, cv::Scalar(255, 225, 255), 6);
	cv::circle(img1, cv::Point(256, 256), 50, cv::Scalar(0, 255, 0), cv::FILLED);
	cv::imshow("Image1", img1);

	cv::Mat img2(512, 512, CV_8UC3, cv::Scalar(255, 255, 255));
	cv::rectangle(img2, cv::Point(128, 128), cv::Point(384, 384), cv::Scalar(0, 69, 255));
	cv::rectangle(img2, cv::Point(118, 118), cv::Point(394, 394), cv::Scalar(0, 255, 0), 5);
	cv::rectangle(img2, cv::Point(158, 158), cv::Point(354, 354), cv::Scalar(255, 0, 0), cv::FILLED);
	cv::imshow("Image2", img2);

	cv::Mat img3(512, 512, CV_8UC3, cv::Scalar(255, 255, 255));
	cv::line(img3, cv::Point(354, 128), cv::Point(125, 354), cv::Scalar(0, 0, 255));
	cv::line(img3, cv::Point(128, 128), cv::Point(384, 384), cv::Scalar(0, 0, 255), 10);
	cv::imshow("Image3", img3);

	cv::Mat img4(512, 512, CV_8UC3, cv::Scalar(255, 255, 255));
	cv::putText(img4, "Murtaza's Workshop", cv::Point(256, 256), cv::FONT_HERSHEY_DUPLEX, 0.5, cv::Scalar(255, 0, 0), 1);
	cv::imshow("Image4", img4);
	cv::waitKey(0);
}
