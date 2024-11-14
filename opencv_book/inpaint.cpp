#include<opencv2/opencv.hpp>
#include<iostream>
#include<vector>

#define WINDOW_NAME1 "Ô­Í¼"
#define WINDOW_NAME2 "Ð§¹û"

cv::Mat srcImage1, inpaintMask;
cv::Point previousPoint(-1, -1);

static void On_Mouse(int event, int x, int y, int flags, void*)
{
	if (event == cv::EVENT_LBUTTONUP || !(flags & cv::EVENT_FLAG_LBUTTON))
	{
		previousPoint = cv::Point(-1, -1);
	}
	else if (event == cv::EVENT_LBUTTONDOWN)
	{
		previousPoint = cv::Point(x, y);
	}
	else if (event == cv::EVENT_MOUSEMOVE && (flags & cv::EVENT_FLAG_LBUTTON))
	{
		cv::Point pt(x,y);
		if (previousPoint.x < 0)
		{
			previousPoint = pt;
		}
		cv::line(inpaintMask, previousPoint, pt, cv::Scalar::all(255), 5, 8, 0);
		cv::line(srcImage1, previousPoint, pt, cv::Scalar::all(255), 5, 8, 0);
		previousPoint = pt;
		cv::imshow(WINDOW_NAME1, srcImage1);
	}
}

int main()
{
	cv::Mat srcImage = cv::imread("Resources/lambo.png");
	if (!srcImage.data)
	{
		printf("err\n");
		return false;
	}
	srcImage1 = srcImage.clone();
	inpaintMask = cv::Mat::zeros(srcImage.size(), CV_8U);
	cv::imshow(WINDOW_NAME1, srcImage1);
	cv::setMouseCallback(WINDOW_NAME1, On_Mouse, 0);
	while (1)
	{
		char c = (char)cv::waitKey();
		if (c == 27)
		{
			break;
		}
		if (c == '2')
		{
			inpaintMask = cv::Scalar::all(0);
			srcImage.copyTo(srcImage1);
			cv::imshow(WINDOW_NAME1, srcImage1);
		}
		if (c == '1' || c == ' ')
		{
			cv::Mat inpaintedImage;
			cv::inpaint(srcImage1, inpaintMask, inpaintedImage, 3, cv::INPAINT_TELEA);
			cv::imshow(WINDOW_NAME2, inpaintedImage);
		}
	}
	cv::waitKey(0);
	return 0;
}

