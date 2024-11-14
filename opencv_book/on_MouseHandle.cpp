#include<opencv2/opencv.hpp>
#include<iostream>
#include<vector>

#define WINDOW_NAME "³ÌÐò´°¿Ú"

void on_MouseHandle(int event, int x, int y, int flags, void* param);
void DrawRectangle(cv::Mat& img, cv::Rect box);
void ShowHelpText();

cv::Rect g_rectangle;
bool g_bDrawingBox = false;
cv::RNG g_rng(12345);

int main()
{
	g_rectangle = cv::Rect(-1, -1, 0, 0);
	cv::Mat srcImage(600, 800, CV_8UC3), tempImage;
	srcImage.copyTo(tempImage);

	g_rectangle = cv::Rect(-1, -1, 0, 0);
	srcImage = cv::Scalar::all(0);
		
	cv::namedWindow(WINDOW_NAME);
	cv::setMouseCallback(WINDOW_NAME, on_MouseHandle, (void*)&srcImage);
	while (1)
	{
		srcImage.copyTo(tempImage);
		if (g_bDrawingBox)
		{
			DrawRectangle(tempImage, g_rectangle);
		}
		cv::imshow(WINDOW_NAME, tempImage);
		if (cv::waitKey(10) == 27)
		{
			break;
		}
	}

	cv::waitKey(0);
	return 0;
}

void on_MouseHandle(int event, int x, int y, int flags, void* param)
{
	cv::Mat& image = *(cv::Mat*)param;
	switch (event)
	{
	case cv::EVENT_MOUSEMOVE:
	{
		if (g_bDrawingBox)
		{
			g_rectangle.width = x - g_rectangle.x;
			g_rectangle.height = y - g_rectangle.y;
		}
	}
		break;
	case cv::EVENT_LBUTTONDOWN:
	{
		g_bDrawingBox = true;
		g_rectangle = cv::Rect(x, y, 0, 0);
	}
		break;
	case cv::EVENT_LBUTTONUP:
	{
		g_bDrawingBox = false;
		if (g_rectangle.width < 0)
		{
			g_rectangle.x += g_rectangle.width;
			g_rectangle.width *= -1;
		}
		if (g_rectangle.height < 0)
		{
			g_rectangle.y += g_rectangle.height;
			g_rectangle.height *= -1;
		}
		DrawRectangle(image, g_rectangle);
	}
		break;
	default:
		break;
	}
}

void DrawRectangle(cv::Mat& img, cv::Rect box)
{
	cv::rectangle(img, box.tl(), box.br(),
		cv::Scalar(g_rng.uniform(0, 255), g_rng.uniform(0, 255), g_rng.uniform(0, 255)));
}

void ShowHelpText()
{
}
