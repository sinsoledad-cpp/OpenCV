#include <opencv2/core/utils/logger.hpp>
#include<opencv2/core.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include<iostream>
//---image---
cv::Mat channels[3], imageThre, imageGau;
cv::Mat image;
int thresh = 229, maxval = 255;
void on_thres(int, void*)
{
	cv::threshold(channels[0], imageThre, thresh, maxval, 0);
	cv::GaussianBlur(imageThre, imageGau, cv::Size(5, 5), 0, 0);

	//cv::imshow("imageThre", imageThre);
	cv::imshow("imageGau", imageGau);

}
void main()
{
	cv::utils::logging::setLogLevel(cv::utils::logging::LOG_LEVEL_SILENT);//不再输出日志
	//或
	//utils::logging::setLogLevel(utils::logging::LOG_LEVEL_ERROR);//只输出错误日志
	std::string path = "P&V/7_1.jpg";
	image = cv::imread(path);
	cv::split(image, channels);
	//cv::imshow("channels[0]", channels[0]);
	cv::namedWindow("thres");
	cv::createTrackbar("thresh", "thres", &thresh, 255, on_thres);
	cv::createTrackbar("maxval", "thres", &maxval, 255, on_thres);
	on_thres(0, 0);

	//查找轮廓
	std::vector<std::vector<cv::Point>> contours;
	std::vector<cv::Vec4i> hierarchy;
	cv::findContours(imageGau, contours, hierarchy,
		cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
	//cv::drawContours(image, contours, -1, cv::Scalar(255, 0, 255), 2);

	std::vector<std::vector<cv::Point>> conPoly(contours.size());
	std::vector<cv::Rect> boundRect(contours.size());

	for (int i = 0; i < contours.size(); i++)
	{
		int area = cv::contourArea(contours[i]);
		if (area > 300 && area < 1800)
		{
			cv::drawContours(image, contours, i, cv::Scalar(255, 0, 0), -1);

			float peri = cv::arcLength(contours[i], true);
			cv::approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);
			//cv::drawContours(image, conPoly, i, cv::Scalar(255, 0, 255), 2);

			boundRect[i] = cv::boundingRect(contours[i]);
			if(boundRect[i].height>50&&boundRect[i].width<30)
			{

				cv::rectangle(image, boundRect[i].tl(), boundRect[i].br(), cv::Scalar(0, 0, 255), 2);
			}
		}
	}

	cv::imshow("Image", image);

	cv::waitKey(0);
}
