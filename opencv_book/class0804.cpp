#include<opencv2/opencv.hpp>
#include<iostream>
#include<vector>


int main()
{
	cv::Mat srcImage_base, hsvImage_base;
	cv::Mat srcImage_test1, hsvImage_test1;
	cv::Mat srcImage_test2, hsvImage_test2;
	cv::Mat hsvImage_halfDown;





	cv::Mat srcImage = cv::imread("Resources/lambo.png");




	cv::waitKey(0);
	return 0;
}

