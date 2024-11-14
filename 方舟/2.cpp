#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

Mat imgHSV, mask, imgResize, imgCrop, imgGray, imgBlur, imgCanny, imgDil;

int main() {
    // ∂¡»°ÕºœÒ
    Mat image = imread("∑Ω÷€/2.jpg");
    imshow("2", image);
    medianBlur(image, imgBlur, 3);

    imshow("imgblur", imgBlur);
    waitKey(0);
    return 0;
}