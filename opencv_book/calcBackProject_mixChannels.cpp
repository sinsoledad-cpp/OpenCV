#include<opencv2/opencv.hpp>
#include<iostream>
#include<vector>

#define WINDOW_NAME1 "原图"	

cv::Mat g_srcImage;
cv::Mat g_hsvImage;
cv::Mat g_hueImage;
int g_bins = 30;

void on_BinChange(int, void*);
int main()
{
	g_srcImage = cv::imread("Resources/lambo.png", 1);
	cv::cvtColor(g_srcImage, g_hsvImage, cv::COLOR_BGR2HSV);

	g_hueImage.create(g_hsvImage.size(), g_hsvImage.depth());
	int ch[] = { 0,0 };
	cv::mixChannels(&g_hsvImage, 1, &g_hueImage, 1, ch, 1);

	cv::namedWindow(WINDOW_NAME1, cv::WINDOW_AUTOSIZE);
	cv::createTrackbar("色调组距", WINDOW_NAME1, &g_bins, 180, on_BinChange);
	on_BinChange(0, 0);
	cv::imshow(WINDOW_NAME1, g_srcImage);

	cv::waitKey(0);
	return 0;
}

void on_BinChange(int, void*)
{
	cv::MatND hist;
	int histSize = MAX(g_bins, 2);
	float hue_range[] = { 0,180 };
	const float* ranges = { hue_range };

	cv::calcHist(&g_hueImage, 1, 0, cv::Mat(), hist, 1, &histSize, &ranges, true, false);
	cv::normalize(hist, hist, 0, 255, cv::NORM_MINMAX, -1, cv::Mat());

	cv::MatND backproj;
	cv::calcBackProject(&g_hueImage, 1, 0, hist, backproj, &ranges, 1, true);

	cv::imshow("反向投影", backproj);

	int w = 400;
	int h = 400;
	int bin_w = cvRound((double)w / histSize);
	cv::Mat histImg = cv::Mat::zeros(w, h, CV_8UC3);

	for (int i = 0; i < g_bins; i++)
	{
		cv::rectangle(histImg, cv::Point(i * bin_w, h),
			cv::Point((i+1)*bin_w,h-cvRound(hist.at<float>(i)*h/255.0)),
			cv::Scalar(100, 123, 255), -1);
	}

	cv::imshow("直方图", histImg);
}
