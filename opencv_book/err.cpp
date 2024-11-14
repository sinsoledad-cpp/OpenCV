#include<opencv2/opencv.hpp>
#include<iostream>
#include<vector>

#define WINDOW_NAME "³ÌÐò´°¿Ú1"

cv::Mat g_maskImage, g_srcImage;
cv::Point prevPt(-1, -1);

static void ShowHelpText();

static void on_Mouse(int event, int x, int y, int flags, void*);

int main()
{
	g_srcImage = cv::imread("Resources/lambo.png");
	cv::imshow(WINDOW_NAME, g_srcImage);

	cv::Mat srcImage, grayImage;
	g_srcImage.copyTo(srcImage);
	cv::cvtColor(g_srcImage, g_maskImage, cv::COLOR_BGR2GRAY);
	cv::cvtColor(g_maskImage, grayImage, cv::COLOR_BGR2GRAY);
	g_maskImage = cv::Scalar::all(0);

	cv::setMouseCallback(WINDOW_NAME, on_Mouse, 0);

	while (1)
	{
		int c = cv::waitKey(0);

		if ((char)c == 27)
		{
			break;
		}
		if ((char)c == '2')
		{
			g_maskImage = cv::Scalar::all(0);
			srcImage.copyTo(g_srcImage);
			cv::imshow("image", g_srcImage);
		}
		if ((char)c == '1' || (char)c == ' ')
		{
			int i, j, compCount = 0;
			std::vector<std::vector<cv::Point>> contours;
			std::vector<cv::Vec4i> hierarchy;

			cv::findContours(g_maskImage, contours, hierarchy,
				cv::RETR_CCOMP, cv::CHAIN_APPROX_NONE);

			if (contours.empty())
			{
				continue;
			}

			cv::Mat maskImage(g_maskImage.size(), CV_32S);
			maskImage = cv::Scalar::all(0);
			for (int index = 0; index >= 0; index = hierarchy[index][0], compCount++)
			{
				cv::drawContours(maskImage, contours, index,
					cv::Scalar::all(compCount + 1), -1, 8, hierarchy, INT_MAX);
			}
			if (compCount == 0)
			{
				continue;
			}
			std::vector<cv::Vec3b> colorTab;
			for (i = 0; i < compCount; i++)
			{
				int b = cv::theRNG().uniform(0, 255);
				int g = cv::theRNG().uniform(0, 255);
				int r = cv::theRNG().uniform(0, 255);
				colorTab.push_back(cv::Vec3b((uchar)b, (uchar)g, (uchar)r));
			}
			double dTime = (double)cv::getTickCount();
			cv::watershed(srcImage, maskImage);
			dTime = (double)cv::getTickCount() - dTime;
			std::cout << dTime * 1000. / cv::getTickCount() << std::endl;

			cv::Mat watershedImage(maskImage.size(), CV_8UC3);
			for (i = 0; i < maskImage.rows; i++)
			{
				for (j = 0; j < maskImage.cols; j++)
				{
					int index = maskImage.at<int>(i, j);
					if (index == -1)
					{
						watershedImage.at<cv::Vec3b>(i, j) = cv::Vec3b(255, 255, 255);
					}
					else if (index <= 0 || index > compCount)
					{
						watershedImage.at<cv::Vec3b>(i, j) = cv::Vec3b(0, 0, 0);
					}
					else
					{
						watershedImage.at<cv::Vec3b>(i, j) = colorTab[index - 1];
					}
				}
			}
			watershedImage = watershedImage * 0.5 + grayImage * 0.5;
			cv::imshow("watershed transform", watershedImage);
		}
	}
	cv::waitKey(0);
	return 0;
}
void ShowHelpText()
{
}
void on_Mouse(int event, int x, int y, int flags, void*)
{
	if (x < 0 || x >= g_maskImage.cols || y < 0 || y >= g_srcImage.rows)
	{
		return;
	}
	if (event == cv::EVENT_LBUTTONUP || !(flags & cv::EVENT_FLAG_LBUTTON))
	{
		prevPt = (cv::Point(-1, -1));
	}
	else if (event == cv::EVENT_LBUTTONDOWN)
	{
		prevPt = cv::Point(x, y);
	}
	else if (event == cv::EVENT_MOUSEMOVE && (flags & cv::EVENT_FLAG_LBUTTON))
	{
		cv::Point pt(x, y);
		if (prevPt.x < 0)
		{
			prevPt = pt;
		}
		cv::line(g_maskImage, prevPt, pt, cv::Scalar::all(255), 5, 8, 0);
		cv::line(g_srcImage, prevPt, pt, cv::Scalar::all(255), 5, 8, 0);
		prevPt = pt;
		cv::imshow(WINDOW_NAME, g_srcImage);
	}
}
