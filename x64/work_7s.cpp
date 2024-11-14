#include <opencv2/core/utils/logger.hpp>
#include<opencv2/core.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include<iostream>

cv::Mat image, imageResize, imageHSV, imageInRange;
int hmin = 0, smin = 87, vmin = 106;
int hmax = 7, smax = 203, vmax = 238;

static void on_HSV(int, void*)
{
	//筛选颜色
	cv::Scalar lower(hmin, smin, vmin);
	cv::Scalar upper(hmax, smax, vmax);
	cv::inRange(imageHSV, lower, upper, imageInRange);
	cv::imshow("Image", imageInRange);
}

int main()
{
	cv::utils::logging::setLogLevel(cv::utils::logging::LOG_LEVEL_SILENT);
	//插入图片
	std::string path = "P&V/7.jpg";
	imageResize = cv::imread(path);

	cv::imshow("srcaaa",imageResize);
	//转化图片颜色空间
	cv::cvtColor(imageResize, imageHSV, cv::COLOR_BGR2HSV);
	//创建动态窗口
	cv::namedWindow("HSV");
	cv::createTrackbar("HueMin", "HSV", &hmin, 179, on_HSV);
	cv::createTrackbar("HueMax", "HSV", &hmax, 179, on_HSV);
	cv::createTrackbar("SatMin", "HSV", &smin, 255, on_HSV);
	cv::createTrackbar("SatMax", "HSV", &smax, 255, on_HSV);
	cv::createTrackbar("ValMin", "HSV", &vmin, 255, on_HSV);
	cv::createTrackbar("ValMax", "HSV", &vmax, 255, on_HSV);
	on_HSV(0, 0);

	//进行膨胀处理
	//int kernel_Size = 3;
	//cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT,
	//	cv::Size(2 * kernel_Size + 1, 2 * kernel_Size + 1));
	//cv::dilate(imageInRange, imageInRange, kernel);

	////查找轮廓
	//std::vector<std::vector<cv::Point>> contours;
	//std::vector<cv::Vec4i> hierarchy;
	//cv::findContours(imageInRange, contours, hierarchy,
	//	cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

	//std::vector<std::vector<cv::Point>> conPoly(contours.size());
	//std::vector<cv::Rect> boundRect(contours.size());

	//for (int i = 0; i < contours.size(); i++)
	//{
	//	int area = cv::contourArea(contours[i]);
	//	if (area > 1000)
	//	{

	//		cv::drawContours(imageResize, contours, i, cv::Scalar(255, 0, 0), -1);

	//		float peri = cv::arcLength(contours[i], true);
	//		cv::approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);

	//		boundRect[i] = cv::boundingRect(conPoly[i]);
	//		cv::rectangle(imageResize, boundRect[i].tl(), boundRect[i].br(), cv::Scalar(0, 0, 255), 2);
	//	}
	//}
	//cv::imshow("Image", imageResize);
	cv::waitKey(0);
	return 0;
}