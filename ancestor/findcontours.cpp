#include<opencv2/opencv.hpp>
#include<iostream>
#include<vector>

int main()
{
	cv::Mat srcImage = cv::imread("Resources/lambo.png");
	cv::imshow("ԭͼ", srcImage);
	cv::cvtColor(srcImage, srcImage, cv::COLOR_BGR2HSV);
	cv::Mat inrangeImage;
	cv::inRange(srcImage, cv::Scalar(2, 134, 160),
		cv::Scalar(17, 255, 255), inrangeImage);

	cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));
	cv::dilate(inrangeImage, inrangeImage, kernel);

	cv::imshow("inrange", inrangeImage);

	std::vector<std::vector<cv::Point>> contours;
	std::vector<cv::Vec4i> hierachy;
	cv::findContours(inrangeImage, contours, hierachy, cv::RETR_CCOMP, cv::CHAIN_APPROX_SIMPLE);


	cv::Mat dstImage = cv::Mat::zeros(srcImage.rows, srcImage.cols, CV_8UC3);
	for (int i = 0; i < contours.size(); i++)
	{
		cv::Scalar color = cv::Scalar(255, 255, 0);
		cv::drawContours(dstImage, contours, i, color);

	}
	cv::imshow("Ч��ͼ", dstImage);

	cv::waitKey(0);
	return 0;
}