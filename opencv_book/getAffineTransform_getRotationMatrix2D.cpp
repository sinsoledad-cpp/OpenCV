#include<opencv2/opencv.hpp>
#include<iostream>
#include<vector>

#define WINDOW_NAME1 "srcs"
#define WINDOW_NAME2 "warp"
#define WINDOW_NAME3 "warp and rotate"

static void showHelpText();


int main()
{
	showHelpText();
	cv::Point2f srcTriangle[3];
	cv::Point2f dstTriangle[3];

	cv::Mat rotMat(2, 3, CV_32FC1);
	cv::Mat warpMat(2, 3, CV_32FC1);
	cv::Mat srcImage, dstImage_warp, dstImage_warp_rotate;

	srcImage = cv::imread("Resources/test.png", 1);
	dstImage_warp = cv::Mat::zeros(srcImage.rows, srcImage.cols, srcImage.type());

	srcTriangle[0] = cv::Point2f(0, 0);
	srcTriangle[1] = cv::Point2f(static_cast<float>(srcImage.cols - 1), 0);
	srcTriangle[2] = cv::Point2f(0, static_cast<float>(srcImage.rows - 1));

	dstTriangle[0] = cv::Point2f(static_cast<float>(srcImage.cols * 0.0), static_cast<float>(srcImage.rows * 0.33));
	dstTriangle[1] = cv::Point2f(static_cast<float>(srcImage.cols * 0.65), static_cast<float>(srcImage.rows * 0.35));
	dstTriangle[2] = cv::Point2f(static_cast<float>(srcImage.cols * 0.15), static_cast<float>(srcImage.rows * 0.6));

	warpMat = cv::getAffineTransform(srcTriangle, dstTriangle);
	cv::warpAffine(srcImage, dstImage_warp, warpMat, dstImage_warp.size());

	cv::Point center = cv::Point(dstImage_warp.cols / 2, dstImage_warp.rows / 2);
	double angle = -30.0;
	double scale = 0.8;

	rotMat = cv::getRotationMatrix2D(center, angle, scale);
	cv::warpAffine(dstImage_warp, dstImage_warp_rotate, rotMat, dstImage_warp.size());


	cv::imshow(WINDOW_NAME1, srcImage);
	cv::imshow(WINDOW_NAME2, dstImage_warp);
	cv::imshow(WINDOW_NAME3, dstImage_warp_rotate);

	cv::waitKey(0);

	return 0;
}

void showHelpText()
{
}
