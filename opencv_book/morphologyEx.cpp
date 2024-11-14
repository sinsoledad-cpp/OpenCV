#include <opencv2/core/utils/logger.hpp>
#include<opencv2/opencv.hpp>
#include<iostream>
#include<vector>

/*
MORPH_OPEN	������(open) ,�ȸ�ʴ�����͵Ĺ��̡������������������С�ڵ㣬����ϸ�㴦�������塢ƽ���ϴ�����ı߽�� ͬʱ�������Ըı��������
MORPH_CLOSE	������(close)�������ͺ�ʴ�Ĺ��̡���������������ų�С�ڶ���
MORPH_GRADIENT	��̬ѧ�ݶ�(morph-grad)������ͻ���ſ�(blob)�ı�Ե����������ı�Ե������
MORPH_TOPHAT	��ñ(top-hat)����ͻ����ԭ�������Ĳ��֡�
MORPH_BLACKHAT	��ñ(black-hat)����ͻ����ԭ�������Ĳ��֡�
*/
int main()
{
	cv::Mat image = cv::imread("Resources/robot.png");
	cv::resize(image, image, cv::Size(), 0.5, 0.5);

	cv::namedWindow("ԭʼͼ");
	cv::namedWindow("Ч��ͼ");
	cv::imshow("ԭʼͼ", image);

	cv::Mat element = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));
	cv::morphologyEx(image, image, cv::MORPH_GRADIENT, element);

	cv::imshow("Ч��ͼ", image);


	cv::waitKey(0);
	return 0;
}
