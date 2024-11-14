#include<opencv2/opencv.hpp>
#include<iostream>
#include<vector>


int main()
{
	cv::Mat src = cv::imread("Resources/lambo.png");
	cv::Mat src1 = src.clone();
	cv::imshow("ԭͼ", src1);

	cv::Mat dst, edge, gray;
	dst.create(src1.size(), src1.type());
	dst = cv::Scalar::all(0);

	cv::cvtColor(src1, gray, cv::COLOR_BGR2GRAY);
	cv::imshow("gray", gray);


	cv::blur(gray, edge, cv::Size(3, 3));
	cv::imshow("edge0", edge);

	cv::Canny(edge, edge, 5, 15, 3);
	cv::imshow("edge", edge);

	src1.copyTo(dst, edge);
	cv::imshow("dst", dst);

	cv::waitKey(0);
	return 0;
}