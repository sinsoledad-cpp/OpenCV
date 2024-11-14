#include <opencv2/core/utils/logger.hpp>
#include<opencv2/core.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include<iostream>
#include <map>
//---basic function---
cv::Mat image, imageresize, imageGray, imagethresh;
int thresh = 80;							//二值化阈值
std::vector<cv::Point2f> points;			//五角星拐点
std::vector<cv::Point2f> shortpoints;		//离中心近的拐点
std::vector<cv::Point2f> longpoints;		//离中心远的拐点
std::vector<cv::Point2f> resultpoints;	//结果
std::vector<cv::Point2f> inside_points_;        //五角星内部拐点


cv::Point2f center;						//外接圆圆心(五角星中心)
float radius = 0;						//外接圆半径

/*
查找五角星轮廓
通过层次关系排除
对五角星轮廓拟/合一个最小外接圆(得到圆心和半径)
对五角星轮廓进行多边形拟合得到10个拐点
极坐标排序
依据拐点和外接圆圆心的相对关系
建立极坐标系,向右👉
注意,上方是负,下方是正
然后依据两个点在x和y上的偏量计算弧度角
*/
static void getContours(cv::Mat imagethresh)
{
	std::vector<std::vector<cv::Point>> contours;
	std::vector<cv::Vec4i> hierarchy;

	cv::findContours(imagethresh, contours, hierarchy,
		cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);

	std::vector<std::vector<cv::Point>> conPoly(contours.size());
	//std::vector<cv::Rect> boundRect(contours.size());

	for (int i = 0; i < contours.size(); i++)
	{
		if (hierarchy[i][3] == -1)continue;
		if (hierarchy[i][2] == -1)continue;
		//判断子轮廓个数是否为6
		int cnt = 0;
		for (int j = hierarchy[i][2]; j + 1; j = hierarchy[j][0]) {
			cnt++;
			std::cout << "contours :  " << j << std::endl;
		}
		//std::cout << cnt << std::endl;
		if (cnt != 6)continue;
		for (int j = hierarchy[i][2]; j + 1; j = hierarchy[j][0])
		{
			double length = cv::arcLength(contours[j], true);
			cv::approxPolyDP(contours[j], conPoly[j], 0.03 * length, true);
			if (conPoly[j].size() != 5)continue;
			inside_points_.clear();
			//std::cout << "contours :  " << i << std::endl;
			for (int k = 0; k < conPoly[j].size(); k++)
			{
				std::cout << "good-----" << std::endl;

				inside_points_.emplace_back(conPoly[j][k]);
			}
			//std::cout << inside_points_.size() << std::endl;
			std::sort(inside_points_.begin(), inside_points_.end(), [&](const cv::Point2f& p1, const cv::Point2f& p2) {return atan2(p1.y - center.y, p1.x - center.x) < atan2(p2.y - center.y, p2.x - center.x); });

		}

		//多边形拟合
		double length = cv::arcLength(contours[i], true);

		cv::approxPolyDP(contours[i], conPoly[i], 0.03 * length, true);

		if (conPoly[i].size() != 10)continue;

		//拟合外接圆
		cv::minEnclosingCircle(cv::Mat(contours[i]), center, radius);

		//储存拐点
		points.clear();
		for (int j = 0; j < conPoly[i].size(); j++)
		{
			points.emplace_back(conPoly[i][j]);
		}

		//极坐标排序
		std::sort(points.begin(), points.end(), [&](const cv::Point2f& p1, const cv::Point2f& p2) {return atan2(p1.y - center.y, p1.x - center.x) < atan2(p2.y - center.y, p2.x - center.x); });
		//std::cout << points.size() << std::endl;
	}
	//conPoly.clear();
	//conPoly.resize(contours.size());
	//for (size_t i = 0; i < contours.size(); i++)
	//{
	//	if (hierarchy[i][3] == -1)continue;
	//	if (hierarchy[i][2] != -1)continue;

	//	//多边形拟合
	//	double length = cv::arcLength(contours[i], true);

	//	cv::approxPolyDP(contours[i], conPoly[i], 0.03 * length, true);
	//	if (conPoly[i].size() != 5)continue;

	//	//cv::drawContours(imageresize, contours, i, cv::Scalar(255, 0, 255), 5);
	//	//cv::drawContours(imageresize, conPoly, i, cv::Scalar(0, 0, 255), 5);

	//	inside_points_.clear();
	//	std::cout << "contours :  " << i << std::endl;
	//	for (int j = 0; j < conPoly[i].size(); j++)
	//	{
	//		//std::cout << "good-----" << std::endl;

	//		inside_points_.emplace_back(conPoly[i][j]);
	//	}
	//	//std::cout << inside_points_.size() << std::endl;
	//	std::sort(inside_points_.begin(), inside_points_.end(), [&](const cv::Point2f& p1, const cv::Point2f& p2) {return atan2(p1.y - center.y, p1.x - center.x) < atan2(p2.y - center.y, p2.x - center.x); });

		for (int i = 0; i < inside_points_.size(); i++)
		{
			//std::cout << "good" << std::endl;
			cv::circle(imageresize, inside_points_[i], 5, cv::Scalar(250, 25, 0), 5);
			cv::putText(imageresize, std::to_string(i), inside_points_[i], cv::FONT_HERSHEY_PLAIN, 5, cv::Scalar(0, 0, 200), 2);
		}
	//}



}

/*
拐点分类
依据拐点到圆心的距离分成长短点集
*/
static void ClassifyPoint()
{
	shortpoints.clear();
	longpoints.clear();
	cv::Point2f firstpoint, secondpoint;
	bool oneflag = true, flag = true;
	for (int i = 0; i < points.size(); i += 2)
	{
		firstpoint = points[i];	//取出前面两个点
		secondpoint = points[i+1];
		if (oneflag)//因为下面代码只需要运行一次(为了确定flag),为了代码简洁,多定义了一个oneflag,
		{
			oneflag = false;
			flag = cv::norm(firstpoint - center) > cv::norm(secondpoint - center) ? true : false;
		}
		if (flag)//flag用于两种情况的开关,因为不清楚是第一个点离圆心远还第二个,对于后续,因为拟合多边形的点位是顺时针的所以一远一近交替排列
		{
			longpoints.emplace_back(firstpoint);
			shortpoints.emplace_back(secondpoint);
		}
		else
		{
			longpoints.emplace_back(secondpoint);
			shortpoints.emplace_back(firstpoint);
		}
	} 
	if (!flag)//将最前面一个点放到最后面
	{
		cv::Point2f temp = shortpoints.front();
		shortpoints.erase(shortpoints.begin());
		shortpoints.emplace_back(temp);
		temp = inside_points_.front();
		inside_points_.erase(inside_points_.begin());
		inside_points_.emplace_back(temp);
	}
	for (size_t i = 0; i < inside_points_.size(); i++)
	{
		shortpoints[i] = (shortpoints[i] + inside_points_[i]) / 2;
	}
}
/*
封装结果
*/
static void makeresultpoint()
{
	resultpoints.emplace_back(longpoints[0]);
	resultpoints.emplace_back(shortpoints[0]);
	resultpoints.emplace_back(shortpoints[1]);

	resultpoints.emplace_back(longpoints[2]);
	resultpoints.emplace_back(shortpoints[2]);
	resultpoints.emplace_back(shortpoints[3]);

	resultpoints.emplace_back(longpoints[4]);
	resultpoints.emplace_back(shortpoints[4]);
	resultpoints.emplace_back(shortpoints[0]);

	resultpoints.emplace_back(longpoints[1]);
	resultpoints.emplace_back(shortpoints[1]);
	resultpoints.emplace_back(shortpoints[2]);

	resultpoints.emplace_back(longpoints[3]);
	resultpoints.emplace_back(shortpoints[3]);
	resultpoints.emplace_back(shortpoints[4]);
}

void test()
{
	for (int i = 0; i < longpoints.size(); i++)
	{
		cv::circle(imageresize, longpoints[i], 5, cv::Scalar(250, 25, 0), 5);
		cv::putText(imageresize, std::to_string(i), longpoints[i], cv::FONT_HERSHEY_PLAIN, 5, cv::Scalar(0, 0, 200), 2);
	}
	for (int i = 0; i < shortpoints.size(); i++)
	{
		cv::circle(imageresize, shortpoints[i], 5, cv::Scalar(250, 25, 0), 5);
		cv::putText(imageresize, std::to_string(i), shortpoints[i], cv::FONT_HERSHEY_PLAIN, 5, cv::Scalar(200, 0, 0), 2);
	}
}

int main()
{
	cv::utils::logging::setLogLevel(cv::utils::logging::LOG_LEVEL_SILENT);//不再输出日志

	std::string path = "D:/NHJ/Documents/Visual Studio 2022/VS 2022/Projects/opencv_help/项目/五角星.png";
	image = cv::imread(path);
	//改大小
	cv::resize(image, imageresize, cv::Size(), 0.3, 0.3);
	//转灰度图
	cv::cvtColor(imageresize, imageGray, cv::COLOR_BGR2GRAY);
	//二值化
	cv::threshold(imageGray, imagethresh, thresh, 255, cv::THRESH_BINARY);

	getContours(imagethresh);

	//ClassifyPoint();

	//test();

	//makeresultpoint();

	cv::imshow("Thresh", imagethresh);
	cv::imshow("imageresize", imageresize);
	cv::waitKey(0);
	return 0;
}

//int main()
//{
//	cv::VideoCapture cap(0);
//	cv::Mat image;
//	while (true)
//	{
//		cap.read(image);
//		cv::resize(image, imageresize, cv::Size(), 0.3, 0.3);
//		//转灰度图
//		cv::cvtColor(imageresize, imageGray, cv::COLOR_BGR2GRAY);
//		//二值化
//		cv::threshold(imageGray, imagethresh, thresh, 255, cv::THRESH_BINARY);
//		
//		getContours(imagethresh);
//		
//		ClassifyPoint();
//		
//		test();
//		
//		makeresultpoint();
//		
//		cv::imshow("Thresh", imagethresh);
//		cv::imshow("imageresize", imageresize);
//		cv::waitKey(1);
//	}
//
//
//
//	return 0;
//}


