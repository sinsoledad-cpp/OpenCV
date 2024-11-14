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
	cv::imshow("Ч��ͼ", dstImage);

}
int main()
{
	srcImage = cv::imread("Resources/lambo.png");
	cv::namedWindow("ԭͼ");
	cv::namedWindow("Ч��ͼ");
	cv::imshow("ԭͼ", srcImage);
	cv::createTrackbar("����/��ʴ", "Ч��ͼ", &trackType, 1, solve);
	cv::createTrackbar("�ںгߴ�", "Ч��ͼ", &kernel_Size, 15, solve);
	solve(0, 0);
	cv::waitKey(0);
	return 0;
}