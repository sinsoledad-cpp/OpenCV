#include<opencv2/opencv.hpp>
#include<iostream>
#include<vector>


int main()
{
	cv::Mat src = cv::imread("Resources/test.png", 0);
	cv::imshow("s", src);

	cv::Mat grad_x, grad_y;
	cv::Mat abs_grad_x, abs_grad_y, dst;

	cv::Scharr(src, grad_x, CV_16S, 1, 0);
	cv::convertScaleAbs(grad_x, abs_grad_x);
	cv::imshow("X", abs_grad_x);

	cv::Scharr(src, grad_y, CV_16S, 0, 1);
	cv::convertScaleAbs(grad_y, abs_grad_y);
	cv::imshow("Y", abs_grad_y);

	cv::addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, dst);
	cv::imshow("dst", dst);


	cv::waitKey(0);
	return 0;
}