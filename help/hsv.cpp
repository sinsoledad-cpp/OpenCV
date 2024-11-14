#include <opencv2/core/utils/logger.hpp>
#include<opencv2/core.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include<iostream>

void getContours(cv::Mat imgDil);
int hmin = 0, smin = 40, vmin = 243;
int hmax = 71, smax = 255, vmax = 255;
//int hmin = 0, smin = 54, vmin = 59;
//int hmax = 19, smax = 255, vmax = 255;
//int hmin = 1, smin = 40, vmin = 83;
//int hmax = 13, smax = 255, vmax = 236;
//int hmin = 0, smin = 68, vmin = 118;
//int hmax = 11, smax = 234, vmax = 250;
cv::Mat image, imageGray, imageBlur, imageCanny, imageDil, imagemor, imageHSV, imageIn;
void HSV()
{
	cv::namedWindow("Trackbars");
	cv::createTrackbar("HueMin", "Trackbars", &hmin, 179);
	cv::createTrackbar("HueMax", "Trackbars", &hmax, 179);
	cv::createTrackbar("SatMin", "Trackbars", &smin, 255);
	cv::createTrackbar("SatMax", "Trackbars", &smax, 255);
	cv::createTrackbar("VakMin", "Trackbars", &vmin, 255);
	cv::createTrackbar("VakMax", "Trackbars", &vmax, 255);
}
static void image_process(cv::Mat& image)
{
	

	cv::Scalar lower(hmin, smin, vmin);
	cv::Scalar upper(hmax, smax, vmax);
	cv::inRange(imageHSV, lower, upper, imageIn);
	cv::imshow("ImageMask", imageIn);

	//break;
	cv::imshow("Image", image);
	cv::imshow("ImageHSV", imageHSV);

	//getContours(imageIn);
}

void getContours(cv::Mat imgDil)
{
	std::vector<std::vector<cv::Point>> contours;
	std::vector<cv::Vec4i> hierarchy;

	cv::findContours(imgDil, contours, hierarchy,
		cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);
	cv::drawContours(image, contours, -1, cv::Scalar(255, 0, 255), 2);
	cv::imshow("Image", image);return;
	for (int i = 0; i < contours.size(); i++)
	{
		int area = cv::contourArea(contours[i]);
		//std::cout << area << std::endl;

		std::vector<std::vector<cv::Point>> conPoly(contours.size());
		std::vector<cv::Rect> boundRect(contours.size());

		std::string objectType;

		if (area > 3000)
		{
			//cv::drawContours(image, contours, i, cv::Scalar(255, 0, 255), 2);

			float peri = cv::arcLength(contours[i], true);
			cv::approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);
			cv::drawContours(image, conPoly, i, cv::Scalar(255, 0, 255), 2);
			//std::cout << conPoly[i].size() << std::endl;

			//cv::drawContours(img, contours, i, cv::Scalar(255, 0, 255), 5);

			boundRect[i] = cv::boundingRect(conPoly[i]);
			cv::rectangle(image, boundRect[i].tl(), boundRect[i].br(), cv::Scalar(0, 255, 0), 5);

			//int object = (int)conPoly[i].size();
			//if (object == 3)
			//{
			//	objectType = "Tri";
			//}
			//else if (object == 4)
			//{
			//	float aspRatio = (float)boundRect[i].width / (float)boundRect[i].height;
			//	std::cout << aspRatio << std::endl;
			//	if (aspRatio > 0.95 && aspRatio < 1.05)
			//	{
			//		objectType = "Square";
			//	}
			//	else
			//	{
			//		objectType = "Rect";
			//	}
			//}
			//else if (object > 4)
			//{
			//	objectType = "Circle";
			//}
			cv::putText(image, std::to_string(area), { boundRect[i].x,boundRect[i].y - 5 }, cv::FONT_HERSHEY_PLAIN, 2, cv::Scalar(0, 69, 255), 3);
		}
	}
	cv::imshow("iamge", image);

}

int main()
{
	//cv::utils::logging::setLogLevel(cv::utils::logging::LOG_LEVEL_SILENT);//不再输出日志
	//cv::VideoCapture cap(1);
	//cap.set(cv::CAP_PROP_AUTO_EXPOSURE, 0.25);           // 设置自动曝光的属性标识符，值为0.25表示将自动曝光设置为手动模式，并且将曝光值设置为0.25
	//cap.set(cv::CAP_PROP_EXPOSURE, -1);                  // 设置曝光值的属性标识符，值为-1表示该参数的值将由摄像头驱动程序自动确定。这意味着曝光值将由摄像头自动调整，而不是手动设置。
	//// 负数表示由摄像头驱动程序自动确定曝光值。非负数表示手动设置的曝光值。
	//cap.set(cv::CAP_PROP_BRIGHTNESS, 170);              // 亮度 0-255
	//cap.set(cv::CAP_PROP_HUE, 0);                       // 色调 0-360 0r 120g 240b
	//cap.set(cv::CAP_PROP_SATURATION, 64);               // 饱和度 0-255
	//HSV();
	image = cv::imread("方舟/4.jpg");
	HSV();
	while (true)
	{
		//cap.read(image);
		if (image.empty())
		{
			std::cout << "err" << std::endl;
			break;
		}
		cv::cvtColor(image, imageHSV, cv::COLOR_BGR2HSV);
		image_process(imageHSV);
		cv::waitKey(1);
	}
	return 0;
}
