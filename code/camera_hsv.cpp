#include <opencv2/core/utils/logger.hpp>
#include<opencv2/core.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include<iostream>
#include<string>
const std::string image_path = "resource/test.png";
int hmin = 0, smin = 40, vmin = 243;
int hmax = 71, smax = 255, vmax = 255;
void Hsv()
{
	cv::namedWindow("Trackbars");
	cv::createTrackbar("HueMin", "Trackbars", &hmin, 179);
	cv::createTrackbar("HueMax", "Trackbars", &hmax, 179);
	cv::createTrackbar("SatMin", "Trackbars", &smin, 255);
	cv::createTrackbar("SatMax", "Trackbars", &smax, 255);
	cv::createTrackbar("VakMin", "Trackbars", &vmin, 255);
	cv::createTrackbar("VakMax", "Trackbars", &vmax, 255);
}
cv::Mat ImageBgrToHsv(cv::Mat& image)
{
	cv::Mat image_hsv;
	cv::cvtColor(image, image_hsv, cv::COLOR_BGR2HSV);
	return image_hsv;
}
cv::Mat ImageBinaryzation(cv::Mat& image_hsv)
{
	cv::Mat image_binaryzation;
	cv::Scalar lower(hmin, smin, vmin);
	cv::Scalar upper(hmax, smax, vmax);
	cv::inRange(image_hsv, lower, upper, image_binaryzation);
	return image_binaryzation;
}
void camera_hsv()
{
	cv::VideoCapture cap(0);
	cv::Mat image;
	Hsv();
	while (true)
	{
		cap.read(image);
		if (image.empty())
		{
			std::cout << "image no found" << std::endl;
			continue;
		}
		cv::imshow("Image", image);
		cv::Mat image_hsv = ImageBgrToHsv(image);
		cv::Mat image_binaryzation = ImageBinaryzation(image_hsv);
		cv::imshow("ImageBinaryzation", image_binaryzation);
		cv::waitKey(1);
	}
}
int main()
{
	cv::utils::logging::setLogLevel(cv::utils::logging::LOG_LEVEL_SILENT);//不再输出日志
	camera_hsv();
	return 0;
}
