#include<opencv2/opencv.hpp>
#include<iostream>
#include<vector>


int main()
{
	cv::Mat src_gray, dst, abs_dst;
	cv::Mat src = cv::imread("Resources/test.png");

	cv::imshow("ԭͼ", src);

	cv::GaussianBlur(src, src, cv::Size(3, 3), 0, 0, cv::BORDER_DEFAULT);

	cv::cvtColor(src, src_gray, cv::COLOR_RGB2GRAY);
	
	cv::Laplacian(src_gray, dst, -1, 5);


	cv::convertScaleAbs(dst, abs_dst);
	cv::imshow("dst", abs_dst);

	cv::waitKey(0);
	return 0;
}