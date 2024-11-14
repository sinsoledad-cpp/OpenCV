#include <opencv2/core/utils/logger.hpp>
#include<opencv2/core.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include<iostream>
#include <map>
//---basic function---
cv::Mat image, imageresize, imageGray, imagethresh;
int thresh = 80;						//二值化阈值
std::vector<cv::Point> points;			//五角星拐点
std::vector<cv::Point> shortpoints;		//离中心近的拐点
std::vector<cv::Point> longpoints;		//离中心远的拐点
std::vector<cv::Point> resultpoints;	//结果


cv::Point2f center;						//外接圆圆心(五角星中心)
float radius = 0;						//外接圆半径
std::map<double, cv::Point> mappoint;	//排序拐点的map
/*
查找五角星轮廓
通过层次关系排除
对五角星轮廓拟合一个最小外接圆(得到圆心和半径)
对五角星轮廓进行多边形拟合得到10个拐点
*/
static void getContours(cv::Mat imagethresh)
{
	std::vector<std::vector<cv::Point>> contours;
	std::vector<cv::Vec4i> hierarchy;

	cv::findContours(imagethresh, contours, hierarchy,
		cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);

	std::vector<std::vector<cv::Point>> conPoly(contours.size());
	std::vector<cv::Rect> boundRect(contours.size());

	for (int i = 0; i < contours.size(); i++)
	{
		if (hierarchy[i][3] == -1)continue;
		if (hierarchy[i][2] == -1)continue;

		//拟合外接圆
		cv::minEnclosingCircle(cv::Mat(contours[i]), center, radius);
		
		//多边形拟合
		double length = cv::arcLength(contours[i], true);

		cv::approxPolyDP(contours[i], conPoly[i], 0.03 * length, true);

		//储存拐点
		points.clear();
		for (int j = 0; j < conPoly[i].size(); j++)
		{
			points.push_back(conPoly[i][j]);
		}
	}
}
/*
依据拐点和外接圆圆心的相对关系
建立极坐标系,向右👉
注意,上方是负,下方是正
然后依据两个点在x和y上的偏量计算弧度角
放进map<弧度角,拐点>,map会自动排序
*/
static void Point()
{
	mappoint.clear();

	for (int i = 0; i < points.size(); i++)
	{
		//计算弧度角
		double dy = points[i].y - center.y;
		double dx = points[i].x - center.x;

		double angle = atan2(dy, dx);

		mappoint.insert(std::make_pair(angle, points[i]));
	}
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
	do
	{
		firstpoint = (*mappoint.begin()).second;	//取出前面两个点
		mappoint.erase(mappoint.begin());
		secondpoint = (*mappoint.begin()).second;
		mappoint.erase(mappoint.begin());
		if (oneflag)//因为下面代码只需要运行一次(为了确定flag),为了代码简洁,多定义了一个oneflag,
		{
			oneflag = false;
			double firstlength = cv::norm(firstpoint - center);
			double secondlength = cv::norm(secondpoint - center);
			flag = firstlength > secondlength ? true : false;
		}
		if (flag)//flag用于两种情况的开关,因为不清楚是第一个点离圆心远还第二个,对于后续,因为拟合多边形的点位是顺时针的所以一远一近交替排列
		{
			longpoints.push_back(firstpoint);
			shortpoints.push_back(secondpoint);
		}
		else
		{
			longpoints.push_back(secondpoint);
			shortpoints.push_back(firstpoint);
		}
	} while (!mappoint.empty());
	if (!flag)//将最前面一个点放到最后面
	{
		cv::Point temp = shortpoints.front();
		shortpoints.erase(shortpoints.begin());
		shortpoints.push_back(temp);
	}
}
/*
封装结果
*/
static void makeresultpoint()
{
	resultpoints.push_back(longpoints[0]);
	resultpoints.push_back(shortpoints[0]);
	resultpoints.push_back(shortpoints[1]);

	resultpoints.push_back(longpoints[2]);
	resultpoints.push_back(shortpoints[2]);
	resultpoints.push_back(shortpoints[3]);

	resultpoints.push_back(longpoints[4]);
	resultpoints.push_back(shortpoints[4]);
	resultpoints.push_back(shortpoints[0]);

	resultpoints.push_back(longpoints[1]);
	resultpoints.push_back(shortpoints[1]);
	resultpoints.push_back(shortpoints[2]);

	resultpoints.push_back(longpoints[3]);
	resultpoints.push_back(shortpoints[3]);
	resultpoints.push_back(shortpoints[4]);
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

	std::string path = "D:/NHJ/Documents/Visual Studio 2022/VS 2022/Projects/opencv_help/项目/现实.jpg";
	image = cv::imread(path);
	//改大小
	cv::resize(image, imageresize, cv::Size(), 0.3, 0.3);
	//转灰度图
	cv::cvtColor(imageresize, imageGray, cv::COLOR_BGR2GRAY);
	//二值化
	cv::threshold(imageGray, imagethresh, thresh, 255, cv::THRESH_BINARY);

	getContours(imagethresh);
	Point();
	ClassifyPoint();

	test();

	cv::imshow("Thresh", imagethresh);
	cv::imshow("imageresize", imageresize);
	cv::waitKey(0);
	return 0;
}


