#include <opencv2/core/utils/logger.hpp>
#include<opencv2/core.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include<iostream>
#include <map>
//---basic function---
cv::Mat image, imageresize, imageGray, imageBlur, imagethresh, imageDil, imageErode;
int thresh = 80;
std::vector<cv::Point> points;
std::vector<cv::Point> shortpoints;
std::vector<cv::Point> longpoints;

cv::Point2f center;
float radius = 0;
std::map<double, cv::Point> mappoint;
/*
查找五角星轮廓
通过层次关系排除
*/
static void getContours(cv::Mat imagethresh)
{
	std::vector<std::vector<cv::Point>> contours;
	std::vector<cv::Vec4i> hierarchy;

	cv::findContours(imagethresh, contours, hierarchy,
		cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);

	std::vector<std::vector<cv::Point>> conPoly(contours.size());
	std::vector<cv::Rect> boundRect(contours.size());

	for (int i = 0; i < contours.size(); i++)
	{
		if (hierarchy[i][3] == -1)continue;
		if (hierarchy[i][2] == -1)continue;
		//cv::drawContours(imageresize, contours, i, cv::Scalar(255, 0, 255), 2);
		//std::cout << contours[i].size() << std::endl;

		cv::minEnclosingCircle(cv::Mat(contours[i]), center, radius);

		double length = cv::arcLength(contours[i], true);
		//cv::approxPolyDP(contours[i], conPoly[i], 0.03 * length, true);
		cv::approxPolyDP(contours[i], conPoly[i], 0.03 * length, true);
		//cv::approxPolyDP(contours[i], conPoly[i], 0.017 * length, true);
		cv::drawContours(imageresize, conPoly, i, cv::Scalar(25, 0, 255), 5);
		//std::cout << conPoly[i].size() << std::endl;
		points.clear();
		for (int j = 0; j < conPoly[i].size(); j++)
		{
			points.push_back(conPoly[i][j]);
		}
	}

	//std::cout << contours.size() << std::endl;
}

static void Point()
{
	mappoint.clear();
	cv::circle(imageresize, center, cvRound(radius), cv::Scalar(250, 25, 0), 2);
	cv::circle(imageresize, center, 5, cv::Scalar(250, 25, 0), -1);
	for (int i = 0; i < points.size(); i++)
	{
		cv::circle(imageresize,points[i], 5, cv::Scalar(0, 255, 0), cv::FILLED);

		double dy = points[i].y - center.y;
		double dx = points[i].x - center.x;

		double angle = atan2(dy, dx);

		//std::cout << angle << std::endl;
		//cv::putText(imageresize, std::to_string(angle)+"--" + std::to_string(i), points[i], cv::FONT_HERSHEY_PLAIN, 1, cv::Scalar(200, 69, 0), 1.5);
		mappoint.insert(std::make_pair(angle, points[i]));

	}

	for (std::map<double, cv::Point>::iterator it = mappoint.begin(); it != mappoint.end(); it++)
	{
		std::cout << " key " << (*it).first << std::endl;
	}

}

static void ClassifyPoint()
{
	shortpoints.clear();
	longpoints.clear();
	cv::Point2f firstpoint, secondpoint;
	bool oneflag = true, flag = true;
	do
	{
		firstpoint = (*mappoint.begin()).second;
		mappoint.erase(mappoint.begin());
		secondpoint = (*mappoint.begin()).second;
		mappoint.erase(mappoint.begin());
		if (oneflag)
		{
			oneflag = false;
			double firstlength = cv::norm(firstpoint - center);
			double secondlength = cv::norm(secondpoint - center);
			flag = firstlength > secondlength ? true : false;
		}
		if (flag)
		{
			longpoints.push_back(firstpoint);
			shortpoints.push_back(secondpoint);
		}
		else
		{
			longpoints.push_back(secondpoint);
			shortpoints.push_back(firstpoint);
		}
	} while (!mappoint.empty());
}

void test()
{
	for (int i = 0; i < longpoints.size(); i++)
	{
		cv::circle(imageresize, longpoints[i], 5, cv::Scalar(250, 25, 0), 5);
		cv::putText(imageresize, std::to_string(i), longpoints[i], cv::FONT_HERSHEY_PLAIN, 5, cv::Scalar(0, 0, 200), 2);
	}
	for (int i = 0; i < shortpoints.size(); i++)
	{
		cv::circle(imageresize, shortpoints[i], 5, cv::Scalar(250, 25, 0), 5);
		cv::putText(imageresize, std::to_string(i), shortpoints[i], cv::FONT_HERSHEY_PLAIN, 5, cv::Scalar(200, 0, 0), 2);
	}
}

int main()
{
	cv::utils::logging::setLogLevel(cv::utils::logging::LOG_LEVEL_SILENT);//不再输出日志

	std::string path = "D:/NHJ/Documents/Visual Studio 2022/VS 2022/Projects/opencv_help/项目/现实.jpg";
	image = cv::imread(path);
	cv::resize(image, imageresize, cv::Size(), 0.3, 0.3);
	//cv::resize(image, imageresize, cv::Size(), 1, 1);
	cv::cvtColor(imageresize, imageGray, cv::COLOR_BGR2GRAY);
	//cv::GaussianBlur(imageGray, imageGray, cv::Size(3, 3), 0, 0);
	//cv::imshow("Gou", imageGray);

	cv::threshold(imageGray, imagethresh, thresh, 255, cv::THRESH_BINARY);
	getContours(imagethresh);
	Point();
	ClassifyPoint();
	test();
	cv::imshow("Thresh", imagethresh);
	cv::imshow("imageresize", imageresize);
	cv::waitKey(0);
	return 0;
}






//void Point()
//{
//	cv::circle(imageresize, center, cvRound(radius),
//		cv::Scalar(250, 25, 0),
//		2);
//	cv::circle(imageresize, center, 5,
//		cv::Scalar(250, 25, 0),
//		-1);
//	for (int i = 0; i < points.size(); i++)
//	{
//		cv::circle(imageresize, points[i], 5, cv::Scalar(0, 255, 0), cv::FILLED);
//
//	}
//}


//static void ClassifyPoint()
//{
//	shortpoints.clear();
//	longpoints.clear();
//	cv::Point2f firstpoint, secondpoint;
//	firstpoint = (*mappoint.begin()).second;
//	mappoint.erase(mappoint.begin());
//	secondpoint = (*mappoint.begin()).second;
//	mappoint.erase(mappoint.begin());
//	//cv::circle(imageresize, firstpoint, 5, cv::Scalar(250, 25, 0), -1);
//	//cv::circle(imageresize, secondepoint, 5, cv::Scalar(250, 25, 0), -1);
//	double firstlength = cv::norm(firstpoint - center);
//	double secondlength = cv::norm(secondpoint - center);
//	bool flag = firstlength > secondlength ? true : false;
//	if (flag)
//	{
//		longpoints.push_back(firstpoint);
//		shortpoints.push_back(secondpoint);
//	}
//	else
//	{
//		longpoints.push_back(secondpoint);
//		shortpoints.push_back(firstpoint);
//		cv::circle(imageresize, longpoints[0], 5, cv::Scalar(250, 25, 0), -1);
//		//cv::circle(imageresize, shortpoints[0], 5, cv::Scalar(250, 25, 0), -1);
//	}
//	do
//	{
//		firstpoint = (*mappoint.begin()).second;
//		mappoint.erase(mappoint.begin());
//		secondpoint = (*mappoint.begin()).second;
//		mappoint.erase(mappoint.begin());
//		if (flag)
//		{
//			longpoints.push_back(firstpoint);
//			shortpoints.push_back(secondpoint);
//		}
//		else
//		{
//			longpoints.push_back(secondpoint);
//			shortpoints.push_back(firstpoint);
//		}
//	} while (!mappoint.empty());
//}