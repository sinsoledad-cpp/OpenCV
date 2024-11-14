#include<opencv2/opencv.hpp>
#include<iostream>
#include<vector>

cv::Mat srcImage, dstImage;
int kernel_Size = 3;
int trackType;
void solve(int, void*)
{
	cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, 
		cv::Size(2*kernel_Size+1, 2 * kernel_Size + 1));
	if (trackType == 0)
	{
		cv::dilate(srcImage, dstImage, kernel);
	}
	else
	{
		cv::erode(srcImage, dstImage, kernel);
	}
	cv::imshow("效果图", dstImage);

}
int main()
{
	srcImage = cv::imread("Resources/lambo.png");
	cv::namedWindow("原图");
	cv::namedWindow("效果图");
	cv::imshow("原图", srcImage);
	cv::createTrackbar("膨胀/腐蚀", "效果图", &trackType, 1, solve);
	cv::createTrackbar("内盒尺寸", "效果图", &kernel_Size, 15, solve);
	solve(0, 0);
	cv::waitKey(0);
	return 0;
}