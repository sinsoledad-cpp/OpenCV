#include <opencv2/core/utils/logger.hpp>
#include<opencv2/opencv.hpp>
#include<iostream>
#include<vector>

/*
MORPH_OPEN	开运算(open) ,先腐蚀后膨胀的过程。开运算可以用来消除小黑点，在纤细点处分离物体、平滑较大物体的边界的 同时并不明显改变其面积。
MORPH_CLOSE	闭运算(close)，先膨胀后腐蚀的过程。闭运算可以用来排除小黑洞。
MORPH_GRADIENT	形态学梯度(morph-grad)，可以突出团块(blob)的边缘，保留物体的边缘轮廓。
MORPH_TOPHAT	顶帽(top-hat)，将突出比原轮廓亮的部分。
MORPH_BLACKHAT	黑帽(black-hat)，将突出比原轮廓暗的部分。
*/
int main()
{
	cv::Mat image = cv::imread("Resources/robot.png");
	cv::resize(image, image, cv::Size(), 0.5, 0.5);

	cv::namedWindow("原始图");
	cv::namedWindow("效果图");
	cv::imshow("原始图", image);

	cv::Mat element = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));
	cv::morphologyEx(image, image, cv::MORPH_GRADIENT, element);

	cv::imshow("效果图", image);


	cv::waitKey(0);
	return 0;
}
