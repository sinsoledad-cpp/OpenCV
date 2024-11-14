#include <opencv2/core/utils/logger.hpp>
#include<opencv2/core.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include<iostream>
std::vector<cv::Mat> Channels;
cv::Mat imageThre, imageGau, blueImage, imagedilate;
cv::Mat image1;
cv::Mat image;
std::vector<cv::Point2f> fan_blades_corners;
int thresh = 14, maxval = 255;
static double Distance(cv::Point2f p1, cv::Point2f p2)
{
	double result = std::sqrt(std::pow(p1.x - p2.x, 2) + std::pow(p1.y - p2.y, 2));
	return result;
}
static void on_split(int, void*)
{
	cv::threshold(blueImage, imageThre, thresh, maxval, 0);
	//cv::threshold(blueImage, imageThre, thresh, maxval, 0);
	cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));
	cv::dilate(imageThre, imagedilate, kernel, cv::Point(-1, -1), 3);
	cv::erode(imagedilate, imagedilate, kernel);
	cv::imshow("imageThre", imageThre);
	cv::imshow("imagedilate", imagedilate);
}
static void findcontours()
{
	std::vector<std::vector<cv::Point>> contours;
	std::vector<cv::Vec4i> hierarchy;
	cv::findContours(imagedilate, contours, hierarchy,
		cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);
	//cv::drawContours(image, contours, -1, cv::Scalar(255, 0, 0), 1);
	//cv::drawContours(imageThre, contours, -1, cv::Scalar(255, 0, 0), 2);
	//cv::drawContours(image, contours, -1, cv::Scalar(255, 0, 0), 2);
	std::vector<std::vector<cv::Point>> conPoly(contours.size());
	std::vector<cv::Rect> boundRect(contours.size());
	for (int i = 0; i < contours.size(); i++)
	{
		double area = cv::contourArea(contours[i]);
		if (area <= 800 || area >= 10000)
		{
			continue;
		}
		cv::RotatedRect box = cv::minAreaRect(cv::Mat(contours[i]));
		cv::Point2f vertex[4];
		box.points(vertex);
		std::vector<cv::Point2f> vertexs;

		for (int i = 0; i < 4; i++)
		{
			vertexs.push_back(vertex[i]);
			//cv::circle(image, vertex[i], 10, cv::Scalar(255,255,0), cv::FILLED);
			//cv::putText(image, std::to_string(i), vertex[i], cv::FONT_HERSHEY_PLAIN, 4, cv::Scalar(0,0,0), 4);

		}
		double boundRectarea = cv::contourArea(vertexs);
		if (hierarchy[i][2] != -1)
		{
			continue;
		}
		if (area / boundRectarea > 0.6 || area/boundRectarea < 0.4)
		{
			continue;
		}
		for (int i = 0; i < 4; i++)
		{
			cv::line(image, vertex[i], vertex[(i + 1) % 4], cv::Scalar(0, 2, 211), 2);
		}
		std::cout << area << std::endl;
		//cv::drawContours(image, contours, i, cv::Scalar(255, 0, 0), 2);		
		fan_blades_corners.clear();
		for (int i = 0; i < 4; i++)
		{
			fan_blades_corners.push_back(vertex[i]);
			//cv::circle(image, vertex[i], 2, cv::Scalar(0, 255, 0), cv::FILLED);
			//cv::putText(image, std::to_string(i), vertex[i], cv::FONT_HERSHEY_PLAIN, 2, cv::Scalar(255, 255, 255), 2);

		}




	}

}
static void DeterminePoints()
{
	std::cout << fan_blades_corners.size() << std::endl;
	for (int i = 0; i < 4; i++)
	{
		//cv::circle(image, fan_blades_corners[i], 2, cv::Scalar(0, 255, 0), cv::FILLED);
		//cv::putText(image, std::to_string(i), fan_blades_corners[i], 
			//cv::FONT_HERSHEY_PLAIN, 2, cv::Scalar(255, 255, 255), 2);
	}
	cv::Point2f r_center_(458, 254);
	cv::circle(image, r_center_, 2, cv::Scalar(0, 255, 0), cv::FILLED);

	cv::Point2f diskcenter;
	diskcenter.x = (fan_blades_corners[0].x + fan_blades_corners[1].x + fan_blades_corners[2].x + fan_blades_corners[3].x) / 4;
	diskcenter.y = (fan_blades_corners[0].y + fan_blades_corners[1].y + fan_blades_corners[2].y + fan_blades_corners[3].y) / 4;
	cv::circle(image, diskcenter, 2, cv::Scalar(0, 255, 0), cv::FILLED);

	std::vector<cv::Point> upperline;
	std::vector<cv::Point> lowerline;
	std::vector<cv::Point> middleline;
	double middlelength = Distance(diskcenter, r_center_);
	for (int i = 0; i < 4; i++)
	{
		double templength = Distance(fan_blades_corners[i], r_center_);
		if (templength > middlelength)
		{
			upperline.push_back(fan_blades_corners[i]);
			//cv::circle(image, fan_blades_corners[i], 2, cv::Scalar(0, 255, 0), cv::FILLED);

		}
		else
		{
			lowerline.push_back(fan_blades_corners[i]);
			//cv::circle(image, fan_blades_corners[i], 2, cv::Scalar(0, 255, 0), cv::FILLED);
		}
	}
	cv::Point2f uppercenter((upperline[0].x + upperline[1].x) / 2, (upperline[0].y + upperline[1].y) / 2);
	cv::circle(image, uppercenter, 2, cv::Scalar(0, 255, 0), cv::FILLED);

	cv::Point2f lowercenter((lowerline[0].x + lowerline[1].x) / 2, (lowerline[0].y + lowerline[1].y) / 2);
	cv::circle(image, lowercenter, 2, cv::Scalar(0, 255, 0), cv::FILLED);

	double height = Distance(lowercenter, uppercenter);
	double width = Distance(upperline[0], upperline[1]);
	double slope = ((uppercenter.y - lowercenter.y) / (uppercenter.x - lowercenter.x));
	double verticalslope = -1.0 / slope;
	cv::Point2f point; 
	point.x = uppercenter.x - width * verticalslope / 2 + 9;
	point.y = uppercenter.y - width * verticalslope / 2 + 9;
	cv::circle(image, point, 2, cv::Scalar(0, 255, 0), cv::FILLED);

}
int main()
{
	cv::utils::logging::setLogLevel(cv::utils::logging::LOG_LEVEL_SILENT);//不再输出日志

	image = cv::imread("assess/02.jpg");
	if (image.empty())
	{
		std::cout << "empty" << std::endl;
	}
	cv::resize(image, image, cv::Size(), 0.5, 0.5);

	cv::split(image, Channels);
	//blueImage =Channels.at(2);//245
	blueImage = Channels.at(1) - Channels.at(0);//38
	//blueImage = Channels.at(2) - 0.2 * Channels.at(1) - 0.8 * Channels.at(0);//38
	//blueImage = Channels.at(0) - 0.2 * Channels.at(1) - 0.8 * Channels.at(2);//38

	cv::namedWindow("split");
	cv::createTrackbar("thresh", "split", &thresh, 255, on_split);
	on_split(0, 0);
	findcontours();
	DeterminePoints();



	cv::imshow("image", image);

	cv::waitKey(0);
	return 0;
}