#include<opencv2/opencv.hpp>
#include<iostream>
#include<vector>


int main()
{
	cv::Mat srcImage = cv::imread("Resources/lambo.png", 0);
	cv::imshow("ԭͼ", srcImage);
	if (!srcImage.data)
	{
		std::cout << "fail to load image" << std::endl;
		return 0;
	}
	cv::MatND dstHist;
	int dims = 1;
	float hranges[] = { 0,255 };
	const float* ranges[] = { hranges };
	int size = 256;
	int channels = 0;
	cv::calcHist(&srcImage, 1, &channels, cv::Mat(), dstHist, dims, &size, ranges);
	
	int scale = 1;
	cv::Mat dstImage(size * scale, size, CV_8U, cv::Scalar(0));

	double minValue = 0;
	double maxValue = 0;
	cv::minMaxLoc(dstHist, &minValue, &maxValue, 0, 0);

	int hpt = cv::saturate_cast<int>(0.9 * size);
	for (int i = 0; i < 256; i++)
	{
		float binValue = dstHist.at<float>(i);
		int realValue = cv::saturate_cast<int>(binValue * hpt / maxValue);
		cv::rectangle(dstImage, cv::Point(i * scale, size - 1), 
			cv::Point((i + 1) * scale - 1, size - realValue), cv::Scalar(255));
	}
	cv::imshow("һά", dstImage);
	cv::waitKey(0);
	return 0;
}

