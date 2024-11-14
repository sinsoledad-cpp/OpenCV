#include<opencv2/opencv.hpp>
#include<opencv2/core/core.hpp>
#include<opencv2/features2d/features2d.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/nonfree/nonfree.hpp>
#include"opencv2/nonfree/nonfree.hpp"
#include<iostream>
#include<vector>


int main()
{
	cv::Mat srcImage1 = cv::imread("Resources/girl1.1.png");
	cv::Mat srcImage2 = cv::imread("Resources/girl1.2.png");
	cv::imshow("ԭͼ1", srcImage1);
	cv::imshow("ԭͼ2", srcImage2);

	int minHessian = 400;

	cv::SurfFeatureDetector detector(minHessian);
	std::SurfFeatureDetector detector(minHessian);
	SurfFeatureDetector



	cv::waitKey(0);
	return 0;
}

