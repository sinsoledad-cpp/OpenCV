#include<opencv2/opencv.hpp>
#include<iostream>
#include<vector>


int main()
{
	cv::Mat srcImage = cv::imread("Resources/math.png");

	cv::Mat midImage, dstImage;
	cv::Canny(srcImage, midImage, 50, 200, 3);
	cv::cvtColor(midImage, dstImage, cv::COLOR_GRAY2BGR);

	std::vector<cv::Vec4i> lines;
	cv::HoughLinesP(midImage, lines, 1, CV_PI / 180, 80, 50, 10);

	for (size_t i = 0; i < lines.size(); i++)
	{
		cv::Vec4i l = lines[i];
		cv::line(dstImage, cv::Point(l[0], l[1]), cv::Point(l[2], l[3]), cv::Scalar(186, 88, 255));
	}

	cv::imshow("Ô­Í¼", srcImage);
	cv::imshow("±ßÔµ", midImage);
	cv::imshow("Ð§¹û", dstImage);

	cv::waitKey(0);
	return 0;
}

