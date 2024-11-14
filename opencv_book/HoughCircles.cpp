#include<opencv2/opencv.hpp>
#include<iostream>
#include<vector>


int main()
{
	cv::Mat srcImage = cv::imread("Resources/shapes.png");
	cv::imshow("ԭͼ", srcImage);

	cv::Mat midImage, dstImage;
	cv::cvtColor(srcImage, midImage, cv::COLOR_BGR2GRAY);

	cv::GaussianBlur(midImage, midImage, cv::Size(9, 9), 2, 2);

	std::vector<cv::Vec3f> circles;
	cv::HoughCircles(midImage, circles, cv::HOUGH_GRADIENT, 1.5, 10, 200, 100);

	for (size_t i = 0; i <circles.size(); i++)
	{
		cv::Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
		int radius = cvRound(circles[i][2]);
		cv::circle(srcImage, center, 3, cv::Scalar(0, 255, 0), -1, 8, 0);
		cv::circle(srcImage, center, radius, cv::Scalar(155, 250, 255), 3, 8, 0);
	}

	cv::imshow("xiaoguo", srcImage);


	cv::waitKey(0);
	return 0;
}

