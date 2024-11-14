#include<opencv2/opencv.hpp>
#include<opencv2/core/core.hpp>
#include<opencv2/features2d/features2d.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/calib3d/calib3d.hpp>
//#include<opencv2/nonfree/nonfree.hpp>
#include<iostream>
#include<vector>


int main()
{
	cv::Mat srcImage = cv::imread("Resources/lambo.png");



	cv::waitKey(0);
	return 0;
}

