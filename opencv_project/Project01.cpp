#include <opencv2/core/utils/logger.hpp>
#include<opencv2/core.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include<iostream>

//int hmin = 0, smin = 64, vmin = 156;
//int hmax = 46, smax = 252, vmax = 255;
cv::Mat img;
std::vector<std::vector<int>> newPoints;

int hmin = 0, smin = 0, vmin = 0;
int hmax = 179, smax = 255, vmax = 255;
std::vector<std::vector<int>> mycolor{ {68,12,147,122,50,243} };
std::vector<cv::Scalar> mycolorvalue{ {255,0,0 } };

cv::Point getContours(cv::Mat imgDil)
{
	std::vector<std::vector<cv::Point>> contours;
	std::vector<cv::Vec4i> hierarchy;

	cv::findContours(imgDil, contours, hierarchy,
		cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
	//cv::drawContours(img, contours, -1, cv::Scalar(255, 0, 255), 2);
	std::vector<std::vector<cv::Point>> conPoly(contours.size());
	std::vector<cv::Rect> boundRect(contours.size());
	cv::Point myPoint(0, 0);
	for (int i = 0; i < contours.size(); i++)
	{
		int area = cv::contourArea(contours[i]);
		std::cout << area << std::endl;

		std::string objectType;

		if (area > 1000)
		{
			float peri = cv::arcLength(contours[i], true);
			cv::approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);
			std::cout << conPoly[i].size() << std::endl;

			//cv::drawContours(img, contours, i, cv::Scalar(255, 0, 255), 5);

			boundRect[i] = cv::boundingRect(conPoly[i]);
			myPoint.x = boundRect[i].x + boundRect[i].width / 2;
			myPoint.y = boundRect[i].y;
				//+ boundRect[i].height / 2;
			
			
			//cv::drawContours(img, conPoly, i, cv::Scalar(255, 0, 255), 5);
			//cv::rectangle(img, boundRect[i].tl(), boundRect[i].br(), cv::Scalar(0, 255, 0), 5);
		}
	}
	return myPoint;
}

std::vector<std::vector<int>> foundcolor(cv::Mat img)
{
	cv::Mat imgHSV;
	cv::cvtColor(img, imgHSV, cv::COLOR_BGR2HSV);
	for(int i=0;i<mycolor.size();i++)
	{
		cv::Scalar lower(mycolor[i][0], mycolor[i][1], mycolor[i][2]);
		cv::Scalar upper(mycolor[i][3], mycolor[i][4], mycolor[i][5]);
		cv::Mat  mask;

		cv::inRange(imgHSV, lower, upper, mask);
		//cv::imshow(std::to_string(i), mask);
		cv::Point myPoint = getContours(mask);
		if (myPoint.x != 0 && myPoint.y != 0)
		{
			newPoints.push_back({ myPoint.x,myPoint.y,i });
		}
	}
	return newPoints;
}

void drawOnCanvas(std::vector<std::vector<int>> newPoints, std::vector<cv::Scalar> myColorValues)
{
	for (int i = 0; i < newPoints.size(); i++)
	{
		cv::circle(img, cv::Point(newPoints[i][0],newPoints[i][1]), 10, myColorValues[newPoints[i][2]], cv::FILLED);
	}
}
void main()
{
	cv::utils::logging::setLogLevel(cv::utils::logging::LOG_LEVEL_SILENT);//不再输出日志


	cv::VideoCapture cap(0);
	while (true)
	{
		cap.read(img);
		newPoints = foundcolor(img);
		drawOnCanvas(newPoints, mycolorvalue);
		cv::imshow("Image", img);
		cv::waitKey(20);
	}
}

