#include<opencv2/opencv.hpp>
#include<iostream>
int WINDOW_WIDTH = 600;
//cv::circle(img, cv::Point(WINDOW_WIDTH / 2, WINDOW_WIDTH / 2), cv::Size()
void DrawEllipse(cv::Mat img, double angle)
{
	int thickness = 2;
	int linetype = 8;
	cv::ellipse(img, cv::Point(WINDOW_WIDTH / 2, WINDOW_WIDTH / 2), cv::Size(WINDOW_WIDTH / 3, WINDOW_WIDTH / 4), angle, 90, 270, cv::Scalar(0, 0, 255), thickness, linetype);
}
void DrawCircle(cv::Mat img, cv::Point center)
{
	int thickness = 1;
	int lineType = 8;
	cv::circle(img, center, WINDOW_WIDTH / 3, cv::Scalar(0, 0, 255), thickness, lineType);
}
void main()
{
	cv::Mat rookImage = cv::Mat::zeros(600, 600, CV_8UC3);
	//cv::namedWindow("»æÖÆÍ¼Ïñ", cv::WINDOW_FREERATIO);
	DrawEllipse(rookImage, 90);
	DrawCircle(rookImage, cv::Point(WINDOW_WIDTH / 2, WINDOW_WIDTH / 2));
	cv::imshow("»æÖÆÍ¼Ïñ", rookImage);
	cv::waitKey(0);
}