#include <opencv2/core/utils/logger.hpp>
#include<opencv2/core.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include<iostream>
//---basic function---
cv::Mat imgGray, imgBlur, imgCanny, imgDil, imgErode;
void getContours(cv::Mat imgDil, cv::Mat img)
{
	std::vector<std::vector<cv::Point>> contours;
	std::vector<cv::Vec4i> hierarchy;

	cv::findContours(imgDil, contours, hierarchy, 
		cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
	//cv::drawContours(img, contours, -1, cv::Scalar(255, 0, 255), 2);

	for (int i = 0; i < contours.size(); i++)
	{
		int area = cv::contourArea(contours[i]);
		std::cout << area << std::endl;

		std::vector<std::vector<cv::Point>> conPoly(contours.size());
		std::vector<cv::Rect> boundRect(contours.size());

		std::string objectType;

		if (area > 1000)
		{

			float peri = cv::arcLength(contours[i], true); 
			cv::approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);
			cv::drawContours(img, conPoly, i, cv::Scalar(255, 0, 255), 5);
			std::cout << conPoly[i].size() << std::endl;

			//cv::drawContours(img, contours, i, cv::Scalar(255, 0, 255), 5);

			boundRect[i] = cv::boundingRect(conPoly[i]);
			cv::rectangle(img, boundRect[i].tl(), boundRect[i].br(), cv::Scalar(0, 255, 0), 5);

			int object = (int)conPoly[i].size();
			if (object == 3)
			{
				objectType = "Tri";
			}
			else if (object == 4)
			{
				float aspRatio = (float)boundRect[i].width / (float)boundRect[i].height;
				std::cout << aspRatio << std::endl;
				if (aspRatio > 0.95 && aspRatio < 1.05)
				{
					objectType = "Square";
				}
				else
				{
					objectType = "Rect";
				}
			}
			else if (object > 4)
			{
				objectType = "Circle";
			}
			cv::putText(img, objectType, { boundRect[i].x,boundRect[i].y - 5 }, cv::FONT_HERSHEY_PLAIN, 1, cv::Scalar(0, 69, 255), 1.5);
		}
	}
}
void main()
{
	cv::utils::logging::setLogLevel(cv::utils::logging::LOG_LEVEL_SILENT);//不再输出日志

	std::string path = "Resources/shapes.png";
	cv::Mat img = cv::imread(path);
	cv::cvtColor(img, imgGray, cv::COLOR_BGR2GRAY);

	cv::GaussianBlur(imgGray, imgBlur, cv::Size(3, 3), 3, 0);

	cv::Canny(imgBlur, imgCanny, 25, 75);

	cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));
	cv::dilate(imgCanny, imgDil, kernel);

	getContours(imgDil, img);

	cv::imshow("Image", img);
	//cv::imshow("imgGray", imgGray);
	//cv::imshow("imgBlur", imgBlur);
	//cv::imshow("imgCanny", imgCanny);
	//cv::imshow("imgDil", imgDil);
	cv::waitKey(0);
}
