#include <opencv2/opencv.hpp>
#include <iostream>
#include <opencv2/core/utils/logger.hpp>
#include <Windows.h>

//#pragma execution_character_set("utf-8")

using namespace cv;
using namespace std;

Mat imgHSV, mask, imgResize, imgCrop, imgGray, imgBlur, imgCanny, imgDil;

int main() {
    // ��ȡͼ��
    SetConsoleOutputCP(CP_UTF8);
    cv::utils::logging::setLogLevel(cv::utils::logging::LOG_LEVEL_SILENT);//���������־

    Mat image = imread("����/3.jpg");
    imshow("3", image);

    cvtColor(image, imgGray, COLOR_BGR2GRAY);
    QRCodeDetector qrcodedetector;
    vector<Point> points;
    string information;

    information = qrcodedetector.detectAndDecode(imgGray, points);

    cout << information << endl;
    //cout << "��" << endl;

    waitKey(0);
    return 0;
}