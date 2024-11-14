#include <opencv2/core/utils/logger.hpp>
#include<opencv2/core.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include<iostream>


cv::Mat channels[3], imageThre, imageGau;
cv::Mat image, imageGray, imageBlur, imageCanny, imageDil, imagemor;
int thresh = 243, maxval = 255;
void on_thres(int, void*)
{
	cv::threshold(channels[2], imageThre, thresh, maxval, 0);
	cv::GaussianBlur(imageThre, imageGau, cv::Size(5, 5), 0, 0);

	cv::imshow("imageThre", imageThre);
	//cv::imshow("imageGau", imageGau);
}
static void image_process(cv::Mat image)
{
	cv::split(image, channels);

	cv::imshow("channels[0]", channels[0]);
	cv::namedWindow("thres");
	cv::createTrackbar("thresh", "thres", &thresh, 255, on_thres);
	cv::createTrackbar("maxval", "thres", &maxval, 255, on_thres);
	on_thres(0, 0);

}


int main()
{
	cv::utils::logging::setLogLevel(cv::utils::logging::LOG_LEVEL_SILENT);//不再输出日志

	image = cv::imread("P&V/5.jpg");

	while (true)
	{

		if (image.empty())
		{
			std::cout << "err" << std::endl;
			break;
		}
		image_process(image);
		cv::waitKey(0);
	}
	return 0;
}
