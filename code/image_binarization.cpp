#include <opencv2/core/utils/logger.hpp>
#include<opencv2/core.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include<iostream>
#include<string>
const std::string image_path = "resource/coreball00.jpg";
int binarization = 253;
void Binarization()
{
	cv::namedWindow("Trackbars");
	cv::createTrackbar("Binarization", "Trackbars", &binarization, 255);

}
cv::Mat ImageBgrToGray(cv::Mat& image_src)
{
	cv::Mat image_gray;
	cv::cvtColor(image_src, image_gray, cv::COLOR_BGR2GRAY);
	return image_gray;
}
cv::Mat ImageBinaryzation(cv::Mat& image_gray)
{
	cv::Mat image_binaryzation;
	cv::threshold(image_gray, image_binaryzation, binarization, 255, cv::THRESH_BINARY);
	return image_binaryzation;
}
cv::Mat ImageDilate(cv::Mat image_binaryzation)
{
	cv::Mat image_dilate;
	cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));
	cv::dilate(image_binaryzation, image_dilate, kernel);
	//cv::imshow("ImageDilate", image_dilate);
	return image_dilate;
}
cv::Mat ImageErode(cv::Mat image_binaryzation)
{
	cv::Mat image_erode;
	cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(7, 7));
	cv::erode(image_binaryzation, image_erode, kernel);
	//cv::imshow("ImageDilate", image_dilate);
	return image_erode;
}
void ImageGetContours(cv::Mat image_binaryzation, cv::Mat image_src)
{
	std::vector<std::vector<cv::Point>> contours;
	std::vector<cv::Vec4i> hierarchy;
	cv::findContours(image_binaryzation, contours, hierarchy,
		cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);
	//cv::drawContours(image_src, contours, -1, cv::Scalar(255, 0, 255), 2);
	std::vector<std::vector<cv::Point>> conPoly(contours.size());
	std::vector<cv::Rect> boundRect(contours.size());
	//std::cout << contours.size() << std::endl;
	for (int i = 0; i < contours.size(); i++)
	{
		int area = cv::contourArea(contours[i]);
		//std::cout << area << std::endl;
		if (area < 1000||area>10000)continue;
		//cv::drawContours(image_src, contours, i, cv::Scalar(255, 0, 255), 5); 
		float peri = cv::arcLength(contours[i], true);
		cv::approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);
		cv::drawContours(image_src, conPoly, i, cv::Scalar(255, 0, 255), 5);
		//std::cout << conPoly[i].size() << std::endl;
		//cv::drawContours(img, contours, i, cv::Scalar(255, 0, 255), 5);
		boundRect[i] = cv::boundingRect(conPoly[i]);
		double ratio = boundRect[i].height * 1.0 / boundRect[i].width;
		std::cout << ratio << std::endl;
		if (ratio > 1.5)continue;
		cv::rectangle(image_src, boundRect[i].tl(), boundRect[i].br(), cv::Scalar(0, 255, 0), 5);
		int object = (int)conPoly[i].size();
		//cv::putText(img, objectType, { boundRect[i].x,boundRect[i].y - 5 }, cv::FONT_HERSHEY_PLAIN, 1, cv::Scalar(0, 69, 255), 1.5);
	}
}
void Image_Binarization()
{
	cv::Mat image_src = cv::imread(image_path);
	cv::Mat image_hsv = ImageBgrToGray(image_src);
	Binarization();
	while (true)
	{
		if (image_src.empty())
		{
			std::cout << "image no found" << std::endl;
			break;
		}
		cv::Mat image_binaryzation = ImageBinaryzation(image_hsv);
		//image_binaryzation = ImageDilate(image_binaryzation);
		//image_binaryzation = ImageErode(image_binaryzation);
		ImageGetContours(image_binaryzation, image_src);
		cv::imshow("ImageBinaryzation", image_binaryzation);
		cv::imshow("ImageSrc", image_src);
		cv::waitKey(1);
		cv::waitKey(0);
	}
}
int main()
{
	cv::utils::logging::setLogLevel(cv::utils::logging::LOG_LEVEL_SILENT);//不再输出日志
	Image_Binarization();
	return 0;
}
