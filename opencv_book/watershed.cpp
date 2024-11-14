#include <opencv2/opencv.hpp>
#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;
#include <iostream>
#include <fstream>
using namespace cv; //����cv�����ռ�
#include <opencv2/core/core.hpp>
//-- -------------------------���궨�岿�֡�---------------------------
// ����������һЩ������
#define WINDOW_NAME "�����򴰿�1��" //Ϊ���ڱ��ⶨ��ĺ�
//-------------------------��ȫ�ֺ������������֡�---------------------
// ������ ȫ�ֱ���������
//- ------------------------ -------
Mat g_maskImage, g_srcImage;
Point prevPt(-1, -1);
//-----------------------------------------��ȫ�ֺ����������֡�------------
// ������ȫ�ֺ���������
// ----- ----
static void ShowHelpText();
static void on_Mouse(int event, int x, int y, int flags, void*);
//---------------------------��main()������-------------------------
// ������ ����̨Ӧ�ó������ں����� ���ǵĳ�������￪ʼִ��
int main(int argc, char** argv)
{
	//��1������ԭͼ����ʾ����ʼ����Ĥ�ͻҶ�ͼ
	g_srcImage = imread("Resources/lambo.png", 1);
	imshow(WINDOW_NAME, g_srcImage);
	Mat srcImage, grayImage;
	g_srcImage.copyTo(srcImage);
	cvtColor(g_srcImage, g_maskImage, COLOR_BGR2GRAY);
	cvtColor(g_maskImage, grayImage, COLOR_GRAY2BGR);
	g_maskImage = Scalar::all(0);
	//��2���������ص�����
	setMouseCallback(WINDOW_NAME, on_Mouse, 0);
	//��3����ѯ������ ���д���
	while (1)
	{
		//��ȡ��ֵ
		int c = waitKey(0);
		//��������ֵΪ ESCʱ�� �˳�
		if ((char)c == 27)
			break;
		//������ֵΪ2ʱ���ָ�Դͼ
		if ((char)c == '2')
		{
			g_maskImage = Scalar::all(0);
			srcImage.copyTo(g_srcImage);
			imshow("image", g_srcImage);
		}
		//����⵽����ֵΪ1���߿ո� ����д���
		if ((char)c == '1' || (char)c == ' ')
		{
			//����һЩ����
			int i, j, compCount = 0;
			vector<vector<Point> > contours;
			vector<Vec4i> hierarchy;
			//Ѱ������
			findContours(g_maskImage, contours, hierarchy, cv::RETR_CCOMP, cv::CHAIN_APPROX_SIMPLE);
			//����Ϊ��ʱ�Ĵ���
			if (contours.empty())
				continue;
			//������Ĥ
			Mat maskImage(g_maskImage.size(), CV_32S);
			maskImage = Scalar::all(0);
			//ѭ�����Ƴ�����
			for (int index = 0; index >= 0; index = hierarchy[index][0], compCount++)
				drawContours(maskImage, contours, index,
					Scalar::all(compCount + 1), -1, 8, hierarchy, INT_MAX);
			//compCountΪ��ʱ�Ĵ���
			if (compCount == 0)
				continue;
			//���������ɫ
			vector<Vec3b> colorTab;
			for (i = 0; i < compCount; i++)
			{
				int b = theRNG().uniform(0, 255);
				int g = theRNG().uniform(0, 255);
				int r = theRNG().uniform(0, 255);
				colorTab.push_back(Vec3b((uchar)b, (uchar)g, (uchar)r));
			}
			//���㴦��ʱ�䲢�����������
			double dTime = (double)getTickCount();
			watershed(srcImage, maskImage);
			dTime = (double)getTickCount() - dTime;
			printf("\t����ʱ�� = %gms\n",
				dTime * 1000. / getTickFrequency());
			//˫��ѭ��,����ˮ��ͼ���������watershedImage��
			Mat watershedImage(maskImage.size(), CV_8UC3);
			for (i = 0; i < maskImage.rows; i++)
				for (j = 0; j < maskImage.cols; j++)
				{
					int index = maskImage.at<int>(i, j);
					if (index == -1)
						watershedImage.at<Vec3b>(i, j) = Vec3b(255, 255, 255);
					else if (index <= 0 || index > compCount)
						watershedImage.at<Vec3b>(i, j) - Vec3b(0, 0, 0);
					else
						watershedImage.at<Vec3b>(i, j) = colorTab[index - 1];
				}
			//��ϻҶ�ͼ�ͷ�ˮ��Ч��ͼ����ʾ���յĴ���
			watershedImage = watershedImage * 0.5 + grayImage * 0.5;
			imshow("watershed transform", watershedImage);
		}
	}
	return 0;
}
void ShowHelpText()
{
}
//--��onMouse()������--
// ������ �����Ϣ�ص�����
static void on_Mouse(int event, int x, int y, int flags, void*)
{
	//������겻�ڴ����е����
	if (x < 0 || x >= g_srcImage.cols || y < 0 || y >= g_srcImage.rows)return;
	//���������������Ϣ
	if (event == EVENT_LBUTTONUP || !(flags & EVENT_FLAG_LBUTTON))
		prevPt = Point(-1, -1);
	else if (event == EVENT_LBUTTONDOWN)
		prevPt = Point(x, y);
	//���������²��ƶ������Ƴ���ɫ����
	else if (event == EVENT_MOUSEMOVE && (flags & EVENT_FLAG_LBUTTON))
	{
		Point pt(x, y);
		if (prevPt.x < 0)
			prevPt = pt;
		line(g_maskImage, prevPt, pt, Scalar::all(255), 5, 8, 0);
		line(g_srcImage, prevPt, pt, Scalar::all(255), 5, 8, 0);
		prevPt = pt;
		imshow(WINDOW_NAME, g_srcImage);
	}
}
