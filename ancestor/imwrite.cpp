#include<opencv2/opencv.hpp>
#include<iostream>
void main()
{
	cv::Mat src = cv::imread("Resources/shapes.png");
	cv::namedWindow("ÏÔÊ¾Í¼Ïñsrc", cv::WINDOW_FREERATIO);
	cv::imshow("ÏÔÊ¾Í¼Ïñsrc", src);
	cv::imwrite("shapes.jpg", src);
	cv::waitKey(0);
}
