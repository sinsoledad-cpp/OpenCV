#include <opencv2/core/utils/logger.hpp>
#include<opencv2/core.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include<opencv2/objdetect.hpp>
#include<iostream>


void main()
{
	cv::utils::logging::setLogLevel(cv::utils::logging::LOG_LEVEL_SILENT);//不再输出日志
	cv::VideoCapture cap(0);
	cv::Mat img;

	cv::CascadeClassifier platesCascade;
	platesCascade.load("Resources/haarcascade_russian_plate_number.xml");

	if (platesCascade.empty())
	{
		std::cout << "XML file no find" << std::endl;
	}

	std::vector<cv::Rect> plate;

	while (true)
	{
		cap.read(img);

		platesCascade.detectMultiScale(img, plate, 1.1, 10);

		for (int i = 0; i < plate.size(); i++)
		{
			cv::Mat imgCrop = img(plate[i]);
			cv::imshow(std::to_string(i), imgCrop);
			cv::imwrite("Resources/Plates/" + std::to_string(i) + ".png", imgCrop);
			cv::rectangle(img, plate[i].tl(), plate[i].br(), cv::Scalar(255, 0, 255), 3);
		}
		cv::imshow("Image", img);
		cv::waitKey(1);
	}
}
