#include<opencv2/opencv.hpp>
#include<iostream>
#include<vector>


int main()
{
	cv::Mat srcImage, hsvImage;
	srcImage = cv::imread("Resources/lambo.png");
	cv::cvtColor(srcImage, hsvImage, cv::COLOR_BGR2HSV);

	int hueBinNum = 30;
	int saturationBinNum = 32;
	int histSize[] = { hueBinNum,saturationBinNum };
	float hueRanges[] = { 0,180 };
	float saturationRanges[] = { 0,256 };
	const float* ranges[] = { hueRanges,saturationRanges };
	cv::MatND dstHIst;
	int channels[] = { 0,1 };
	cv::calcHist(&hsvImage, 1, channels, cv::Mat(), dstHIst, 2, histSize, ranges, true, false);

	double maxValue = 0;
	cv::minMaxLoc(dstHIst, 0, &maxValue, 0, 0);
	int scale = 10;
	cv::Mat histImg = cv::Mat::zeros(saturationBinNum * scale, hueBinNum * 10, CV_8UC3);
	for (int hue = 0; hue < hueBinNum; hue++)
	{
		for (int saturation = 0; saturation < saturationBinNum; saturation++)
		{
			float binValue = dstHIst.at<float>(hue, saturation);
			int intensity = cvRound(binValue * 255 / maxValue);
			cv::rectangle(histImg, cv::Point(hue * scale, saturation * scale),
				cv::Point((hue + 1) * scale - 1, (saturation + 1) * scale - 1),
				cv::Scalar::all(intensity), cv::FILLED);
		}
	}
	cv::imshow("ËØ²ÄÍ¼", srcImage);
	cv::imshow("H-SÖ±·½Í¼", histImg);
	cv::waitKey(0);
	return 0;
}

