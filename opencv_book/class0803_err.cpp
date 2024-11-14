#include<opencv2/opencv.hpp>
#include<iostream>
#include<vector>


int main()
{
	cv::Mat srcImage = cv::imread("Resources/lambo.png", 0);
	if (!srcImage.data)
	{
		std::cout << "fail to load image" << std::endl;
		return 0;
	}
	cv::imshow("ԭͼ", srcImage);

	int bins = 256;
	int hist_size[] = { bins };
	float range[] = { 0,256 };
	const float* ranges[] = { range };
	cv::MatND redHist, grayHist, blueHist;

	std::vector<cv::Mat>srcImages;
	cv::split(srcImage, srcImages);

	int channels_r[] = { 0 };
	cv::calcHist(&srcImages[0], 1, channels_r, cv::Mat(), redHist, 1, hist_size, ranges, true, false);
	int channels_g[] = { 0 };
	cv::calcHist(&srcImages[1], 1, channels_g, cv::Mat(), grayHist, 1, hist_size, ranges, true, false);
	int channels_b[] = { 0 };
	cv::calcHist(&srcImages[2], 1, channels_b, cv::Mat(), blueHist, 1, hist_size, ranges, true, false);

	double maxValue_red, maxValue_green, maxValue_blue;
	cv::minMaxLoc(redHist, 0, &maxValue_red, 0, 0);
	cv::minMaxLoc(grayHist, 0, &maxValue_green, 0, 0);
	cv::minMaxLoc(blueHist, 0, &maxValue_blue, 0, 0);

	int scale = 1;
	int histHeight = 256;
	cv::Mat hstImage(histHeight, bins*3, CV_8UC3);

	for (int i = 0; i < bins; i++)
	{
		float binValue_red = redHist.at<float>(i);
		float binValue_green = grayHist.at<float>(i);
		float binValue_blue = blueHist.at<float>(i);
		int intensity_red = cvRound(binValue_red * histHeight / maxValue_red);
		int intensity_green = cvRound(binValue_green * histHeight / maxValue_green);
		int intensity_blue = cvRound(binValue_blue * histHeight / maxValue_blue);
		cv::rectangle(hstImage, cv::Point(i * scale, histHeight - 1),
			cv::Point((i + 1) * scale - 1, histHeight - intensity_red), cv::Scalar(0, 0, 255));
		cv::rectangle(hstImage, cv::Point(i * scale, histHeight - 1),
			cv::Point((i + 1) * scale - 1, histHeight - intensity_green), cv::Scalar(255, 0, 0));
		cv::rectangle(hstImage, cv::Point(i * scale, histHeight - 1),
			cv::Point((i + 1) * scale - 1, histHeight - intensity_blue), cv::Scalar(255, 0, 0));
	}
	cv::imshow("һά", hstImage);
	cv::waitKey(0);
	return 0;
}

