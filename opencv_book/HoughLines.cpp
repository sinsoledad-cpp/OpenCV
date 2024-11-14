#include<opencv2/opencv.hpp>
#include<iostream>
#include<vector>


int main()
{
	cv::Mat srcImage = cv::imread("Resources/math.png");

	cv::Mat midImage, dstImage;
	cv::Canny(srcImage, midImage, 50, 200, 3);

	cv::cvtColor(midImage, dstImage, cv::COLOR_GRAY2BGR);

	std::vector<cv::Vec2f > lines;

	cv::HoughLines(midImage, lines, 1, CV_PI / 180, 150, 0, 0);

	for (size_t i = 0; i < lines.size(); i++)
	{
		float rho = lines[i][0], theta = lines[i][1];
		cv::Point pt1, pt2;
		double a = cos(theta), b = sin(theta);
		double x0 = a * rho, y0 = b * rho;
		pt1.x = cvRound(x0 + 1000 * (-b));
		pt1.y = cvRound(y0 + 1000 * (a));
		pt2.x = cvRound(x0 - 1000 * (-b));
		pt2.y = cvRound(y0 - 1000 * (a));
		cv::line(dstImage, pt1, pt2, cv::Scalar(55, 255, 0), 1);

	}
	cv::imshow("Ô­Í¼", srcImage);
	cv::imshow("±ßÔµ", midImage);
	cv::imshow("Ð§¹û", dstImage);
	cv::waitKey(0);
	return 0;
}

