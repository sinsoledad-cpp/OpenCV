#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

Mat imgHSV, mask, imgResize, imgCrop, imgGray, imgBlur, imgCanny, imgDil;

int main() {
    // ∂¡»°ÕºœÒ
    Mat image = imread("∑Ω÷€/1.jpg");
    imshow("1", image);

    for (int i = 0; i < image.rows; i++)
    {
        for (int j = 0; j < image.cols; j++)
        {
            uchar temp = image.at<Vec3b>(i, j)[1];
            image.at<Vec3b>(i, j)[1] = image.at<Vec3b>(i, j)[2];
            image.at<Vec3b>(i, j)[2] = temp;
        }
    }
    imshow("1_", image);
    waitKey(0);
    return 0;
}