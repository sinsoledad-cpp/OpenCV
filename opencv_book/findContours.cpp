#include<opencv2/opencv.hpp>
#include<iostream>
#include<vector>
#include <cstdlib>


int main()
{
	srand(time(NULL));
	cv::Mat srcImage = cv::imread("Resources/test.png", 0);
	cv::imshow("ԭͼ", srcImage);

	cv::Mat dstImage = cv::Mat::zeros(srcImage.rows, srcImage.cols, CV_8UC3);


	//srcImageȡ������ֵ119���ǲ��� srcImage = srcImage > 119;  //�Ҷ�ֵ����119�����ص���1��������0��
	srcImage = srcImage > 119;
	cv::imshow("��ͼ", srcImage);

	std::vector<std::vector<cv::Point>> contours;
	std::vector<cv::Vec4i> hierarchy;

	cv::findContours(srcImage, contours, hierarchy, cv::RETR_CCOMP, cv::CHAIN_APPROX_SIMPLE);

	
	for (int index = 0; index >= 0; index = hierarchy[index][0])
	{
		cv::Scalar color(rand() & 255, rand() & 255, rand() & 255);
		cv::drawContours(dstImage, contours, index, color, cv::FILLED, 8, hierarchy);
		
	}
	cv::imshow("����", dstImage);
	cv::waitKey(0);
	return 0;
}

