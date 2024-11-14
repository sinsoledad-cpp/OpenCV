#include <opencv2/core/utils/logger.hpp>
#include<opencv2/core.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include<iostream>
//---resize and crop---
void main()
{
	cv::utils::logging::setLogLevel(cv::utils::logging::LOG_LEVEL_SILENT);//不再输出日志
	std::string path = "Resources/test.png";
	cv::Mat img = cv::imread(path);
	std::cout << img.size() << std::endl;

	cv::Mat imgSize1, imgSize2, imgCrop;
	cv::resize(img, imgSize1, cv::Size(300, 200));
	cv::resize(img, imgSize2, cv::Size(), 0.5, 0.5);

	cv::Rect roi(200, 100, 300, 300);
	imgCrop = img(roi);

	cv::imshow("Image", img);
	cv::imshow("ImageSize1", imgSize1);
	cv::imshow("ImageSize2", imgSize2);
	cv::imshow("ImageCrop", imgCrop);
	cv::waitKey(0);
}
