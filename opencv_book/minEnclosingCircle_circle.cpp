#include<opencv2/opencv.hpp>
#include<iostream>
#include<vector>

#define WINDOW_NAME1 "原图"
#define WINDOW_NAME2 "效果"

cv::Mat g_srcImage;
cv::Mat g_grayImage;
int g_nThresh = 50;
int g_nMaxThersh = 255;
cv::RNG g_rng(12345);

static void ShowHeloText();
void on_ContoursChange(int, void*);

int main()
{
	g_srcImage = cv::imread("Resources/test.png", 1);
	cv::cvtColor(g_srcImage, g_grayImage, cv::COLOR_BGR2GRAY);
	cv::blur(g_grayImage, g_grayImage, cv::Size(3, 3));
	
	cv::namedWindow(WINDOW_NAME1, cv::WINDOW_AUTOSIZE);
	cv::imshow(WINDOW_NAME1, g_srcImage);

	cv::createTrackbar("阈值: ", WINDOW_NAME1, &g_nThresh, g_nMaxThersh, on_ContoursChange);
	on_ContoursChange(0, 0);

	cv::waitKey(0);
	return 0;
}



void ShowHeloText()
{
}

void on_ContoursChange(int, void*)
{
	cv::Mat threshold_output;
	std::vector<std::vector<cv::Point>> contours;
	std::vector<cv::Vec4i> hierachy;

	cv::threshold(g_grayImage, threshold_output, g_nThresh, 255, 0);
	cv::findContours(threshold_output, contours, hierachy, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE, cv::Point(0, 0));

	std::vector<std::vector<cv::Point>> contours_poly(contours.size());
	std::vector<cv::Rect> boundRect(contours.size());
	std::vector<cv::Point2f> center(contours.size());
	std::vector<float> radius(contours.size());

	for (unsigned int i = 0; i < contours.size(); i++)
	{
		cv::approxPolyDP(cv::Mat(contours[i]), contours_poly[i], 3, true);
		boundRect[i] = cv::boundingRect(cv::Mat(contours_poly[i]));
		cv::minEnclosingCircle(contours_poly[i], center[i], radius[i]);
	}

	cv::Mat drawing = cv::Mat::zeros(threshold_output.size(), CV_8UC3);
	for (unsigned int i = 0; i < contours.size(); i++)
	{
		cv::Scalar color = cv::Scalar(g_rng.uniform(0, 255), g_rng.uniform(0, 255), g_rng.uniform(0, 255));
		cv::drawContours(drawing, contours_poly, i, color);
		cv::rectangle(drawing, boundRect[i].tl(), boundRect[i].br(), color);		
		cv::circle(drawing, center[i], (int)radius[i], color);

	}
	cv::namedWindow(WINDOW_NAME2, 1);
	cv::imshow(WINDOW_NAME2, drawing);

}


