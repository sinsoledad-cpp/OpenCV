#include<opencv2/opencv.hpp>
#include<iostream>
#include<vector>


int main()
{
	cv::Mat srcImage = cv::imread("Resources/lambo.png");
	cv::Mat tmpImage, dstImage;
	tmpImage = srcImage;
	cv::imshow("ԭͼ", srcImage);
	cv::pyrUp(tmpImage, dstImage, cv::Size(tmpImage.cols * 2, tmpImage.rows * 2));

	cv::imshow("Ч��", dstImage);
	cv::waitKey(0);
	return 0;
}