#include<opencv2/opencv.hpp>
#include<iostream>
#include<vector>
void ROI_AddImage();
//bool ROI_AddImage();
void LinearBlending();
//bool LinearBlending();
void ROI_LinearBlending();
//bool ROI_LinearBlending();
//void ShowHelpText();
int main()
{
	//system("color 6F");
	//if (ROI_AddImage() && LinearBlending() && ROI_LinearBlending())
	//{
	//	std::cout << std::endl << "\n运行成功,得出了需要的图像";
	//}
	ROI_AddImage();
	//LinearBlending();
	//ROI_LinearBlending();

	cv::waitKey(0);
	return 0;
}
void ROI_AddImage()
{
	cv::Mat srcImage = cv::imread("Resources/shapes.png");
	cv::Mat logoImage = cv::imread("Resources/1.png");
	cv::rectangle(logoImage, cv::Point(0.0), 
		cv::Point(logoImage.cols, logoImage.rows), cv::Scalar(0, 0, 0), 10);
	//cv::imshow("srcImage", srcImage);
	cv::imshow("logoImage", logoImage);
	cv::imwrite("2.png", logoImage);
	if (!srcImage.data)
	{
		std::cout << "err src" << std::endl;
		//return false;
		return ;
	}
	if (!logoImage.data)
	{
		std::cout << "err logo" << std::endl;
		//return false;
		return;
	}

	cv::Mat imageROI = srcImage(cv::Rect(100, 250, logoImage.cols, logoImage.rows));
	cv::Mat mask = cv::imread("2.png",0);
	cv::imshow("imageROI", imageROI);
	cv::imshow("mask", mask);
	logoImage.copyTo(imageROI,mask);
	//cv::imshow("logoImage", logoImage);
	cv::imshow("srcImage", srcImage);
	
}
void LinearBlending()
{
	double alphaValue = 0.5;
	double betaValue = 1.0 - alphaValue;
	cv::Mat srcImage2, srcImage3, dstImage;
	srcImage2 = cv::imread("猫1.png");
	srcImage3 = cv::imread("背景1.png");
	cv::addWeighted(srcImage2, alphaValue, srcImage3, betaValue, 0.0, dstImage);
	cv::imshow("dstImage", dstImage);
	cv::imwrite("dst1.png", dstImage);
}
void ROI_LinearBlending()
{
	cv::Mat srcImage4 = cv::imread("Resources/shapes.png");
	cv::Mat logoImage = cv::imread("2.png");
	cv::Mat imageROI = srcImage4(cv::Rect(200, 200, logoImage.cols, logoImage.rows));
	cv::addWeighted(imageROI, 0.8, logoImage, 0.2, 0, imageROI);
	cv::imshow("srcImage4", srcImage4);
}
