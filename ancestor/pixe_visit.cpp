#include<opencv2/opencv.hpp>
#include<iostream>
void pixel_visit(cv::Mat& src)
{
	int dims = src.channels();
	int h = src.rows;
	int w = src.cols;
	for (int row = 0; row < h; row++)
	{
		for (int col = 0; col < w; col++)
		{
			if (dims == 1)
			{
				int pv = src.at<uchar>(row, col);
				src.at<uchar>(row, col) = 255 - pv;
			}
			if (dims == 3)
			{
				cv::Vec3b bgr=src.at<cv::Vec3b>(row, col);
				src.at<cv::Vec3b>(row, col)[0] = 255 - bgr[0];
				src.at<cv::Vec3b>(row, col)[1] = 255 - bgr[1];
				src.at<cv::Vec3b>(row, col)[2] = 255 - bgr[2];
			}
		}
	}
}
void main()
{
	cv::Mat src = cv::imread("Resources/shapes.png");
	cv::namedWindow("Ô­Í¼", cv::WINDOW_FREERATIO);
	cv::imshow("Ô­Í¼", src);
	pixel_visit(src);
	cv::namedWindow("¶ÁÈ¡ÏñËØ", cv::WINDOW_FREERATIO);
	cv::imshow("¶ÁÈ¡ÏñËØ", src);
	cv::waitKey(0);
}