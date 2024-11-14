#include <opencv2/core/utils/logger.hpp>
#include<opencv2/core.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include<iostream>
std::vector<cv::Mat> Channels;
cv::Mat imageThre, imageGau, blueImage, imagedilate;
cv::Mat image1;
cv::Mat image;
cv::Mat drawimage;
int thresh =  226, maxval = 255;
void findcontours(cv::Mat imageThre);
static void on_split(int, void*)
{
	cv::threshold(blueImage, imageThre, thresh, maxval, 0);
	cv::imshow("imageThre", imageThre);
	//cv::threshold(blueImage, imageThre, thresh, maxval, 0);
	cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));
	cv::dilate(imageThre, imagedilate, kernel);
	cv::imshow("imagedilate", imagedilate);
	//cv::imshow("imagedilate", imagedilate);
	findcontours(imagedilate);
}
void findcontours(cv::Mat imageThre)
{
	std::vector<std::vector<cv::Point>> contours;
	std::vector<cv::Vec4i> hierarchy;
	cv::findContours(imageThre, contours, hierarchy,
		cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);
	cv::drawContours(image, contours, -1, cv::Scalar(255, 0, 0), 1);
	std::vector<std::vector<cv::Point>> conPoly(contours.size());
	std::vector<cv::Rect> boundRect(contours.size());

	for (int i = 0; i < contours.size(); i++)
	{
		double area = cv::contourArea(contours[i]);
		cv::Point2f center;
		float radius = 0;
		cv::minEnclosingCircle(cv::Mat(contours[i]), center, radius);
		double circlearea = 3.1415926 * std::pow(radius, 2);
		std::cout << area<<"---"<<circlearea<<"---"<<area/circlearea << std::endl;
		if (area / circlearea < 0.5)//外接圆面积比轮廓面积
		{
			continue;
		}
		cv::circle(image, center, 3,cv::Scalar(255,0,0),cv::FILLED);
	}
	//for (int i = 0; i < contours.size(); i++)
	//{
	//	double area = cv::contourArea(contours[i]);
	//	if (area <= 100||area>=1000)
	//	{
	//		continue;
	//	}
	//	if (hierarchy[i][3] == -1&&hierarchy[i][2]==-1)
	//	{
	//		boundRect[i] = cv::boundingRect(contours[i]);
	//		cv::rectangle(image, boundRect[i].tl(), boundRect[i].br(), cv::Scalar(0, 255, 0), 5);
	//		if (static_cast<double>(boundRect[i].height) / boundRect[i].width > 1.1
	//			|| static_cast<double>(boundRect[i].width) / boundRect[i].height > 1.1)
	//		{
	//			cv::rectangle(image, boundRect[i].tl(), boundRect[i].br(), cv::Scalar(0, 0, 255), 5);
	//			//continue;
	//		}
	//		//std::cout << "---" << i << "---" << std::endl;
	//		//std::cout << area << std::endl;
	//		//std::cout << boundRect[i].area() << std::endl;
	//		if (area / boundRect[i].area() < 0.5)
	//		{
	//			std::cout << "---" << area / boundRect[i].area() << "---" << std::endl;
	//			continue;
	//		}
	//		std::cout << contours[i].size() << std::endl;
	//		cv::drawContours(image, contours, i, cv::Scalar(255, 0, 0), -1);
	//	}
	//}
	//cv::imshow("image", image);
}
int main()
{
	cv::utils::logging::setLogLevel(cv::utils::logging::LOG_LEVEL_SILENT);//不再输出日志
	cv::VideoCapture cap(1);
	cap.set(cv::CAP_PROP_AUTO_EXPOSURE, 0.25);           // 设置自动曝光的属性标识符，值为0.25表示将自动曝光设置为手动模式，并且将曝光值设置为0.25
	cap.set(cv::CAP_PROP_EXPOSURE, -1);                  // 设置曝光值的属性标识符，值为-1表示该参数的值将由摄像头驱动程序自动确定。这意味着曝光值将由摄像头自动调整，而不是手动设置。
	// 负数表示由摄像头驱动程序自动确定曝光值。非负数表示手动设置的曝光值。
	cap.set(cv::CAP_PROP_BRIGHTNESS, 170);              // 亮度 0-255
	cap.set(cv::CAP_PROP_HUE, 0);                       // 色调 0-360 0r 120g 240b
	cap.set(cv::CAP_PROP_SATURATION, 64);               // 饱和度 0-255
	cv::namedWindow("Trackbars");
	cv::createTrackbar("HueMin", "Trackbars", &thresh, 255);

	while (true)
	{
		cap.read(image);
	
		if (image.empty())
		{
			std::cout << "err" << std::endl;
			break;
		}
		
		cv::split(image, Channels);
		//blueImage =Channels.at(2);//245
		blueImage = Channels.at(2);
		on_split(0, 0);
		cv::imshow("image", image);
		cv::waitKey(1);
	}
	return 0;
}
