#include <opencv2/core/utils/logger.hpp>
#include<opencv2/core.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include<iostream>
//---image---
cv::Mat imgOriginal, imgGray, imgGanny, imgThre, imgBlur, imgCanny, imgDil, imgErode, imgWarp, imgCrop;
std::vector<cv::Point> initialPoints, docPoints;
float w = 420, h = 596;

cv::Mat preProcessing(cv::Mat img)
{
	cv::cvtColor(img, imgGray, cv::COLOR_BGR2GRAY);
	cv::GaussianBlur(img, imgBlur, cv::Size(3, 3), 3, 0);
	cv::Canny(imgBlur, imgCanny, 25, 75);

	cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));
	cv::dilate(imgCanny, imgDil, kernel);

	//cv::erode(imgDil, imgErode, kernel);

	return imgDil;
}

std::vector<cv::Point> getContours(cv::Mat image)
{
	std::vector<std::vector<cv::Point>> contours;
	std::vector<cv::Vec4i> hierarchy;

	cv::findContours(imgDil, contours, hierarchy,
		cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
	//cv::drawContours(img, contours, -1, cv::Scalar(255, 0, 255), 2);
	std::vector<std::vector<cv::Point>> conPoly(contours.size());
	std::vector<cv::Rect> boundRect(contours.size());

	std::vector<cv::Point> biggest;

	for (int i = 0; i < contours.size(); i++)
	{
		int area = cv::contourArea(contours[i]);
		std::cout << area << std::endl;

		std::string objectType;
		int maxArea = 0;
		if (area > 1000)
		{
			float peri = cv::arcLength(contours[i], true);
			cv::approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);
		
			if (area > maxArea && conPoly[i].size() == 4)
			{
				//cv::drawContours(imgOriginal, conPoly, i, cv::Scalar(255, 0, 255), 5);

				biggest = { conPoly[i][0],conPoly[i][1] ,conPoly[i][2] ,conPoly[i][3] };
				maxArea = area;
			}

			//cv::drawContours(imgOriginal, contours, i, cv::Scalar(255, 0, 255), 5);

		//cv::drawContours(imgOriginal, conPoly, i, cv::Scalar(255, 0, 255), 5);
		//cv::rectangle(img, boundRect[i].tl(), boundRect[i].br(), cv::Scalar(0, 255, 0), 5);
		}
	}
	return biggest;
}
void drawPoints(std::vector<cv::Point> points, cv::Scalar color)
{
	for (int i = 0; i < points.size(); i++)
	{
		cv::circle(imgOriginal, points[i], 8, color, cv::FILLED);
		cv::putText(imgOriginal, std::to_string(i), points[i],cv::FONT_HERSHEY_PLAIN, 4, color, 4);
	}
} 
std::vector<cv::Point> reorder(std::vector<cv::Point> points)
{
	std::vector<cv::Point> newPoints;
	std::vector<int> sumPoints, subPoints;
	for (int i = 0; i < 4; i++)
	{
		sumPoints.push_back(points[i].x + points[i].y);
		subPoints.push_back(points[i].x - points[i].y);
	}
	newPoints.push_back(points[std::min_element(sumPoints.begin(), sumPoints.end()) - sumPoints.begin()]);
	newPoints.push_back(points[std::max_element(subPoints.begin(), subPoints.end()) - subPoints.begin()]);
	newPoints.push_back(points[std::min_element(subPoints.begin(), subPoints.end()) - subPoints.begin()]);
	newPoints.push_back(points[std::max_element(sumPoints.begin(), sumPoints.end()) - sumPoints.begin()]);
	
	return newPoints;
}
cv::Mat getWarp(cv::Mat img, std::vector<cv::Point> points, float w, float h)
{
	cv::Point2f src[4] = { points[0],points[1],points[2],points[3] };
	cv::Point2f dst[4] = { {0.0f,0.0f},{w,0.0f},{0.0f,h},{w-20,h} };
	cv::Mat matrix = cv::getPerspectiveTransform(src, dst);
	cv::warpPerspective(img, imgWarp, matrix, cv::Size(w, h));
	return imgWarp;
}
void main()
{
	cv::utils::logging::setLogLevel(cv::utils::logging::LOG_LEVEL_SILENT);//不再输出日志
	std::string path = "Resources/paper.jpg";
	imgOriginal = cv::imread(path);
	cv::resize(imgOriginal, imgOriginal, cv::Size(), 0.5, 0.5);

	imgThre = preProcessing(imgOriginal);
	initialPoints = getContours(imgThre);
	drawPoints(initialPoints, cv::Scalar(0, 0, 255));
	docPoints = reorder(initialPoints);
	drawPoints(docPoints, cv::Scalar(0, 255, 0));

	imgWarp = getWarp(imgOriginal, docPoints, w, h);

	//int cropVal = 10;
	//cv::Rect roi(cropVal, cropVal, w - (2 * cropVal), h - (2 * cropVal));
	//imgCrop = imgWarp(roi);

	cv::imshow("Image", imgOriginal);
	cv::imshow("Image Dilation", imgThre);
	cv::imshow("Image imgWarp", imgWarp);
	//cv::imshow("Image imgCrop", imgCrop);
	cv::waitKey(0);
}
