#include<opencv2/opencv.hpp>
#include<iostream>
#include<vector>
cv::Mat src = cv::imread("Resources/lambo.png");
cv::Rect ccomp;
int arrpoint[2] = { 275,175 };
int arrchange[3] = { 255,0,0 };
//int arrinrange1[3] = { 20,20,20 };
//int arrinrange2[3] = { 20,20,20 };
int arrinrange1[3] = { 10,10,10 };
int arrinrange2[3] = { 10,10,10 };
static void on_callback(int, void*)
{
	std::cout << "arrinrange1" << "\t\t" << arrinrange1[0] << "\t" << arrinrange1[1] << "\t" << arrinrange1[2] << "\t" << std::endl;
	std::cout << "arrinrange2" << "\t\t" << arrinrange2[0] << "\t" << arrinrange2[1] << "\t" << arrinrange2[2] << "\t" << std::endl;
	cv::floodFill(src, cv::Point(arrpoint[0], arrpoint[1]), 
		cv::Scalar(arrchange[0], arrchange[1], arrchange[2]),
		&ccomp, 
		cv::Scalar(arrinrange1[0], arrinrange1[1], arrinrange1[2]), 
		cv::Scalar(arrinrange2[0], arrinrange2[1], arrinrange2[2]), 4);
	cv::imshow("效果图", src);
}
int main()
{
	cv::imshow("原图", src);

	cv::namedWindow("track",cv::WINDOW_FREERATIO);
	cv::createTrackbar("pointx", "track", &arrpoint[0], 620, on_callback);
	cv::createTrackbar("pointy", "track", &arrpoint[1], 460, on_callback);

	cv::createTrackbar("B", "track", &arrchange[0], 255, on_callback);
	cv::createTrackbar("G", "track", &arrchange[1], 255, on_callback);
	cv::createTrackbar("R", "track", &arrchange[2], 255, on_callback);

	cv::createTrackbar("B_1", "track", &arrinrange1[0], 255, on_callback);
	cv::createTrackbar("G_1", "track", &arrinrange1[1], 255, on_callback);
	cv::createTrackbar("R_1", "track", &arrinrange1[2], 255, on_callback);

	cv::createTrackbar("B_2", "track", &arrinrange2[0], 255, on_callback);
	cv::createTrackbar("G_2", "track", &arrinrange2[1], 255, on_callback);
	cv::createTrackbar("R_2", "track", &arrinrange2[2], 255, on_callback);

	on_callback(0, 0);

	cv::waitKey(0);

	return 0;
}
//static void on_callback(int, void*)
//{
//	cv::Scalar scalar1(arrinrange1[0], arrinrange1[1], arrinrange1[2]);
//	cv::Scalar scalar2(arrinrange2[0], arrinrange2[1], arrinrange2[2]);
//	cv::floodFill(src, cv::Point(arrpoint[0], arrpoint[1]),
//		cv::Scalar(arrchange[0], arrchange[1], arrchange[2]),
//		&ccomp,
//		scalar1,
//		scalar2, 8);
//	std::cout << "arrinrange1" << "\t\t" << arrinrange1[0] << "\t" << arrinrange1[1] << "\t" << arrinrange1[2] << "\t" << std::endl;
//	std::cout << "arrinrange2" << "\t\t" << arrinrange2[0] << "\t" << arrinrange2[1] << "\t" << arrinrange2[2] << "\t" << std::endl;
//	cv::imshow("效果图", src);
//}