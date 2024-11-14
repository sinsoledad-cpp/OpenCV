#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

Mat imgHSV, mask, imgResize, imgCrop, imgGray, imgBlur, imgCanny, imgDil;

int main() {
    // 读取图像
    Mat image = imread("方舟/4.jpg");
    imshow("4", image);
    
	for (int i = 0; i < image.rows; i++) {
		for (int j = 0; j < image.cols; j++) {
			if (image.at<cv::Vec3b>(i, j)[2] <= 255 && image.at<cv::Vec3b>(i, j)[2] >= 100 && image.at<cv::Vec3b>(i, j)[1] <= 105)
			{
				image.at<cv::Vec3b>(i, j)[0] = 0;
				image.at<cv::Vec3b>(i, j)[1] = 0;
				image.at<cv::Vec3b>(i, j)[2] = 0;
			}
		}
	}

	cv::cvtColor(image, imgHSV, cv::COLOR_BGR2HSV);

	Scalar lower(0, 29, 147);
	Scalar upper(179, 255, 255);
	inRange(imgHSV, lower, upper, imgCanny);

	cv::imshow("cann", imgCanny);


	std::vector<std::vector<cv::Point>> contours;
	std::vector<cv::Vec4i> hierarchy;

	cv::findContours(imgCanny, contours, hierarchy,
		cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);
	//cv::drawContours(image, contours, -1, cv::Scalar(0, 255, 255), 3);


	std::vector<std::vector<cv::Point>> conPoly(contours.size());


	for (size_t i = 0; i < contours.size(); i++)
	{
		//多边形拟合
		double length = cv::arcLength(contours[i], true);
		cv::approxPolyDP(contours[i], conPoly[i], 0.03 * length, true);
		if (conPoly[i].size() != 8)continue;
		cout << "good" << endl;
		cv::drawContours(image, conPoly, i, cv::Scalar(0, 255, 255), 3);

	}
    imshow("4_", image);
    waitKey(0);
    return 0;
}