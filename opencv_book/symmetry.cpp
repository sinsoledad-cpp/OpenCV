#include<opencv2/opencv.hpp>
#include<iostream>
#include<vector>


int main()
{

	cv::Mat srcImage, dstImage;
	cv::Mat map_x, map_y;
	srcImage = cv::imread("Resources/lambo.png", 0);
	
	dstImage.create(srcImage.size(), srcImage.type());
	map_x.create(srcImage.size(), CV_32FC1);
	map_y.create(srcImage.size(), CV_32FC1);

	for (int j = 0; j < srcImage.rows; j++)
	{
		for (int i = 0; i < srcImage.cols; i++)
		{
			map_x.at<float>(j, i) = static_cast<float>(i);
			map_y.at<float>(j, i) = static_cast<float>(srcImage.rows - j);
		}
	}
	cv::remap(srcImage, dstImage, map_x, map_y, cv::INTER_LINEAR, cv::BORDER_CONSTANT, cv::Scalar(0, 0, 0));
	cv::imshow("dst", dstImage);
	cv::waitKey(0);
	return 0;
}

