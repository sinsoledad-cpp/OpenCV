#include<opencv2/opencv.hpp>
#include<iostream>
#include<vector>
void MultiChannelBlending()
{
	cv::Mat srcImage;
	cv::Mat logoImage;
	std::vector<cv::Mat>channels;
	cv::Mat imageBlueChannel;
	srcImage = cv::imread("√®1.png");
	logoImage = cv::imread("¿÷.png", 0);
	//cv::imshow("srcImage", srcImage);
	cv::imshow("logoImage", logoImage);
	cv::split(srcImage, channels);
	imageBlueChannel = channels.at(0);
	//cv::imshow("imageBlueChannel", imageBlueChannel);
	cv::addWeighted(imageBlueChannel(cv::Rect(500, 250, logoImage.cols, logoImage.rows)), 0.5,
		logoImage, 0.5, 0.0, imageBlueChannel(cv::Rect(500, 250, logoImage.cols, logoImage.rows)));
	//cv::imshow("imageBlueChannels", imageBlueChannel);
	cv::merge(channels, srcImage);

	cv::imshow("imageBlueChannel", srcImage);

}
int main()
{
	MultiChannelBlending();
	cv::waitKey(0);
}