#include <opencv2/core/utils/logger.hpp>
#include<opencv2/core.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include<iostream>

void getContours(cv::Mat imgDil);

cv::Mat image, imageGray, imageBlur, imageCanny, imageDil, imagemor;

static void image_process(cv::Mat& image)
{
	//转成灰度图
	cv::cvtColor(image, imageGray, cv::COLOR_BGR2GRAY);
	//高斯模糊
	cv::GaussianBlur(imageGray, imageBlur, cv::Size(3, 3), 3, 0);
	//Canny边缘检测
	cv::Canny(imageBlur, imageCanny, 25, 75);
	//cv::imshow("imageCanny", imageCanny);
	//getContours(imageCanny);

	//膨胀处理
	cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));
	cv::dilate(imageCanny, imageDil, kernel);
	cv::imshow("imageDil", imageDil);
	//getContours(imageDil);

	//cv::Mat element = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));
	//cv::morphologyEx(imageCanny, imagemor, cv::MORPH_GRADIENT, element);
	//cv::imshow("Image mor", imagemor);
	//getContours(imagemor);

}

void getContours(cv::Mat imgDil)
{
	std::vector<std::vector<cv::Point>> contours;
	std::vector<cv::Vec4i> hierarchy;

	cv::findContours(imgDil, contours, hierarchy,
		cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);
	//cv::drawContours(image, contours, -1, cv::Scalar(255, 0, 255), 2);
	for (int i = 0; i < contours.size(); i++)
	{
		int area = cv::contourArea(contours[i]);
		//std::cout << area << std::endl;

		std::vector<std::vector<cv::Point>> conPoly(contours.size());
		std::vector<cv::Rect> boundRect(contours.size());

		std::string objectType;

		if (area > 1000)
		{
			cv::drawContours(image, contours, i, cv::Scalar(255, 0, 255), 2);

			float peri = cv::arcLength(contours[i], true);
			cv::approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);
			//cv::drawContours(image, conPoly, i, cv::Scalar(255, 0, 255), 5);
			//std::cout << conPoly[i].size() << std::endl;

			//cv::drawContours(img, contours, i, cv::Scalar(255, 0, 255), 5);

			boundRect[i] = cv::boundingRect(conPoly[i]);
			//cv::rectangle(image, boundRect[i].tl(), boundRect[i].br(), cv::Scalar(0, 255, 0), 5);

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
			//cv::putText(image, objectType, { boundRect[i].x,boundRect[i].y - 5 }, cv::FONT_HERSHEY_PLAIN, 1, cv::Scalar(0, 69, 255), 1.5);
		}
	}
	cv::imshow("iamge", image);

}

int main()
{
	cv::utils::logging::setLogLevel(cv::utils::logging::LOG_LEVEL_SILENT);//不再输出日志

	image = cv::imread("P&V/5.jpg");
	
	while (true)
	{

		if (image.empty())
		{
			std::cout << "err" << std::endl;
			break;
		}
		image_process(image);
		cv::waitKey(0);
	}
	return 0;
}
