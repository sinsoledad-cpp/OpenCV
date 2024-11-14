#include<opencv2/opencv.hpp>
#include<iostream>
#include<vector>


int main()
{
	cv::Mat srcImage, dstImage;
	srcImage = cv::imread("Resources/test.png");

	cv::cvtColor(srcImage, srcImage, cv::COLOR_BGR2GRAY);
	cv::imshow("ԭͼ", srcImage);
	
	cv::equalizeHist(srcImage, dstImage);
	cv::imshow("Ч��ͼ", dstImage);


	cv::waitKey(0);
	return 0;
}

