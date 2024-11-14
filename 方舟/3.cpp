#include <opencv2/opencv.hpp>
#include <iostream>
#include <opencv2/core/utils/logger.hpp>
#include <Windows.h>

//#pragma execution_character_set("utf-8")

using namespace cv;
using namespace std;

Mat imgHSV, mask, imgResize, imgCrop, imgGray, imgBlur, imgCanny, imgDil;

int main() {
    // 读取图像
    SetConsoleOutputCP(CP_UTF8);
    cv::utils::logging::setLogLevel(cv::utils::logging::LOG_LEVEL_SILENT);//不再输出日志

    Mat image = imread("方舟/3.jpg");
    imshow("3", image);

    cvtColor(image, imgGray, COLOR_BGR2GRAY);
    QRCodeDetector qrcodedetector;
    vector<Point> points;
    string information;

    information = qrcodedetector.detectAndDecode(imgGray, points);

    cout << information << endl;
    //cout << "好" << endl;

    waitKey(0);
    return 0;
}