#include<opencv2/opencv.hpp>
#include<iostream>
#include<vector>
#define WINDOW_NAME "程序窗口"
cv::Mat g_srcImage, g_dstImage;
cv::Mat g_map_x, g_map_y;

int update_map(int key);
static void ShowHelpText();


int main()
{

	g_srcImage = cv::imread("Resources/lambo.png");
	cv::imshow("原图", g_srcImage);

	g_dstImage.create(g_srcImage.size(), g_srcImage.type());
	g_map_x.create(g_srcImage.size(), CV_32FC1);
	g_map_y.create(g_srcImage.size(), CV_32FC1);
	cv::namedWindow(WINDOW_NAME, cv::WINDOW_AUTOSIZE);
	cv::imshow(WINDOW_NAME, g_srcImage);

	while (true)
	{
		int key = cv::waitKey(0);
		if ((key & 255) == 27)
		{
			std::cout << "退出" ;
			break;
		}

		update_map(key);
		cv::remap(g_srcImage, g_dstImage, g_map_x, g_map_y, cv::INTER_LINEAR, cv::BORDER_CONSTANT, cv::Scalar(0, 0, 0));
		cv::imshow(WINDOW_NAME, g_dstImage);
	}

	cv::waitKey(0);
	return 0;
}

int update_map(int key)
{
	for (int j = 0; j < g_srcImage.rows; j++)
	{
		for (int i = 0; i < g_srcImage.cols; i++)
		{
			switch (key)
			{
			case '1':
				if (i > g_srcImage.cols * 0.25 && i<g_srcImage.cols * 0.75
					&& j>g_srcImage.rows * 0.25 && j < g_srcImage.rows * 0.75)
				{
					g_map_x.at<float>(j, i) = static_cast<float>(2 * (i - g_srcImage.cols * 0.25) + 0.5);
					g_map_y.at<float>(j, i) = static_cast<float>(2 * (j - g_srcImage.rows * 0.25) + 0.5);
				}
				else
				{
					g_map_x.at<float>(j, i) = 0;
					g_map_y.at<float>(j, i) = 0;
				}
				break;
			case '2':
				g_map_x.at<float>(j, i) = static_cast<float>(i);
				g_map_y.at<float>(j, i) = static_cast<float>(g_srcImage.rows - j);
				break;
			case '3':
				g_map_x.at<float>(j, i) = static_cast<float>(g_srcImage.cols - i);
				g_map_y.at<float>(j, i) = static_cast<float>(j);
				break;
			case '4':
				g_map_x.at<float>(j, i) = static_cast<float>(g_srcImage.cols - i);
				g_map_y.at<float>(j, i) = static_cast<float>(g_srcImage.rows - j);
				break;
			default:
				break;
			}
		}
	}
	return 0;
}

void ShowHelpText()
{
}
