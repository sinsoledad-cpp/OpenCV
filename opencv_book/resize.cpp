#include<opencv2/opencv.hpp>
#include<iostream>
#include<vector>

int main()
{
	cv::Mat srcImage = cv::imread("Resources/lambo.png");
	cv::Mat tmpImage, dstImage1, dstImage2;
	tmpImage = srcImage;
	cv::imshow("ԭͼ", srcImage);
	cv::resize(tmpImage, dstImage1, cv::Size(tmpImage.cols / 2, tmpImage.rows / 2), 0.0, 0.0, 3);
	cv::resize(tmpImage, dstImage2, cv::Size(tmpImage.cols * 2, tmpImage.rows * 2), 0.0, 0.0, 3);
	cv::imshow("Ч��1", dstImage1);
	cv::imshow("Ч��2", dstImage2);
	cv::waitKey(0);
	return 0;
}