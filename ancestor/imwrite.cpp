#include<opencv2/opencv.hpp>
#include<iostream>
void main()
{
	cv::Mat src = cv::imread("Resources/shapes.png");
	cv::namedWindow("��ʾͼ��src", cv::WINDOW_FREERATIO);
	cv::imshow("��ʾͼ��src", src);
	cv::imwrite("shapes.jpg", src);
	cv::waitKey(0);
}
