#include <opencv2/core/utils/logger.hpp>
#include<opencv2/core.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include<iostream>
float w = 250, h = 300;
cv::Mat matrix1, imgWarp1;
cv::Mat matrix2, imgWarp2;
void main()
{
	cv::utils::logging::setLogLevel(cv::utils::logging::LOG_LEVEL_SILENT);//不再输出日志

	std::string path = "Resources/cards.jpg";

	cv::Mat img = cv::imread(path);
	cv::Point2f src1[4] = { {529,142},{771,190},{405,395},{674,457} };
	cv::Point2f dst1[4] = { {0.0f,0.0f},{w,0.0f},{0.0f,h},{w,h} };

	matrix1 = cv::getPerspectiveTransform(src1, dst1);
	cv::warpPerspective(img, imgWarp1, matrix1, cv::Size(w, h));
	for (int i = 0; i < 4; i++)
	{
		cv::circle(img, src1[i], 5, cv::Scalar(255, 0, 0), cv::FILLED);
	}

	cv::imshow("Image", img);
	cv::imshow("ImageWarp1", imgWarp1);

	cv::Point2f src2[4] = { {776,107},{1018,84},{844,357},{1115,330} };
	cv::Point2f dst2[4] = { {0.0f,0.0f},{w,0.0f},{0.0f,h},{w,h} };
	matrix2 = cv::getPerspectiveTransform(src2, dst2);
	cv::warpPerspective(img, imgWarp2, matrix2, cv::Size(w, h));
	cv::imshow("ImageWarp2", imgWarp2);

	cv::waitKey(0);
}

