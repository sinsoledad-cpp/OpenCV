#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>

#include <iostream>
//#include "rclcpp/rclcpp.hpp"
#include <cmath>

using namespace std;
using namespace cv;

#define PI 3.1415926535

class detector
{
private:
    Mat img;
    vector<Point> turning_points_;
    vector<Point2f> polar_sorting_points_;

public:
    Mat PreProcess();
    void FindPoints(Mat binary_image);
    void CalculatePolarCoordinates();
    void DrawPoints();
    detector();
    ~detector();
};

detector::detector(/* args */)
{
    VideoCapture cap(0);
    Mat gray;
    while (true)
    {
        cap.read(img);
        Mat binary_image = PreProcess();
        FindPoints(binary_image);


        imshow("binary_image", binary_image);
        imshow("img", img);
        waitKey(1);
    }
}

detector::~detector()
{
}

Mat detector::PreProcess()
{
    Mat gray_img, binary_image;
    cvtColor(img, gray_img, COLOR_BGR2GRAY);
    threshold(gray_img, binary_image, 120, 255, THRESH_BINARY);
    // 开运算去除噪声
   // morphologyEx(binary_image, binary_image, MORPH_OPEN, element);
    return binary_image;
}

void detector::FindPoints(Mat binary_image)
{
    // 轮廓
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy; // 层次体系

    // 传入一个图像,两个容器
    findContours(binary_image, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);
    vector<vector<Point>> conPoly(contours.size());
    for (int i = 0; i < contours.size(); i++)
    {
        double area = contourArea(contours[i]);
        if (hierarchy[i][2] == -1 || hierarchy[i][3] == -1 || area < 800)
        {
            continue;
        }
        if (!turning_points_.empty() || !polar_sorting_points_.empty())
        {
            turning_points_.clear();
            polar_sorting_points_.clear();
        }
        float peri = arcLength(contours[i], true);
        // 多边形拟合曲线
        approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true); // 参数1:输入的轮廓点集,参数2:输出的点集,参数3:原始曲线与近似曲线的最大距离,参数4:是否闭合

        if (conPoly[i].size() != 10)
        {
            continue;
        }

        drawContours(img, conPoly, i, (255, 0, 255), 2);
        turning_points_ = conPoly[i];
        Point2f circle_center;
        float circle_r;
        minEnclosingCircle(contours[i], circle_center, circle_r);
        circle(img, circle_center, circle_r, Scalar(0, 69, 255), 4);
        CalculatePolarCoordinates();
        DrawPoints();
    }
}

void detector::CalculatePolarCoordinates()
{
    for (int i = 0; i < turning_points_.size(); i++)
    {
        double n1, n2;
        n1 = turning_points_[i].x;
        n2 = turning_points_[i].y;
        Point2f point;
        point.x = sqrt(n1 * n1 + n2 * n2);
        if (atan2f(n2, n1) < 0)
            point.y = atan2f(n2, n1) + 2 * PI;
        else
            point.y = atan2f(n2, n1);
        polar_sorting_points_.emplace_back(point);
    }
}

void detector::DrawPoints()
{

    double sum = 0;
    //for (int i = 0; i < turning_points_.size() - 1; ++i)
    //{
    //    for (int j = 0; j < turning_points_.size() - i - 1; ++j)
    //    {
    //        if (polar_sorting_points_[j].y < polar_sorting_points_[j + 1].y)
    //        {
    //            swap(polar_sorting_points_[j], polar_sorting_points_[j + 1]);
    //            swap(turning_points_[j], turning_points_[j + 1]);
    //        }
    //    }
    //}

    for (int i = 0; i < turning_points_.size(); i++)
    {
        sum += polar_sorting_points_[i].x;
    }

    if (polar_sorting_points_[0].x < sum / polar_sorting_points_.size())
    {
        Point temp_point = polar_sorting_points_[0];
        polar_sorting_points_.erase(polar_sorting_points_.begin());
        polar_sorting_points_.emplace_back(temp_point);
    }

    for (int i = 0; i < turning_points_.size(); i++)
    {
        putText(img, to_string(i), turning_points_[i], FONT_HERSHEY_COMPLEX, 1, Scalar(0, 0, 255), 2);
    }
}

int main()
{
    detector de;
    return 0;
}