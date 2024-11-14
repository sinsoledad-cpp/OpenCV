#include "opencv2/video/tracking.hpp"
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <stdio.h>
#include <iostream>

using namespace cv;

using namespace std;


int main()

{

	float A[10][3] =

	{

	10, 50, 15.6,

	12, 49, 16,

	11, 52, 15.8,

	13, 52.2, 15.8,

	12.9, 50, 17,

	14, 48, 16.6,

	13.7, 49, 16.5,

	13.6, 47.8, 16.4,

	12.3, 46, 15.9,

	13.1, 45, 16.2

	};


	const int stateNum = 3;

	const int measureNum = 3;

	KalmanFilter KF(stateNum, measureNum, 0);

	KF.transitionMatrix = (Mat_<float>(3, 3) << 1, 0, 0, 0, 1, 0, 0, 0, 1); //ת�ƾ���A

	setIdentity(KF.measurementMatrix); //��������H

	setIdentity(KF.processNoiseCov, Scalar::all(1e-5)); //ϵͳ�����������Q

	setIdentity(KF.measurementNoiseCov, Scalar::all(1e-1)); //���������������R

	setIdentity(KF.errorCovPost, Scalar::all(1));

	Mat measurement = Mat::zeros(measureNum, 1, CV_32F);


	//��ʼ״ֵ̬

	KF.statePost = (Mat_<float>(3, 1) << A[0][0], A[0][1], A[0][2]);

	cout << "state0=" << KF.statePost << endl;


	for (int i = 1; i <= 9; i++)

	{

		//Ԥ��

		Mat prediction = KF.predict();

		//�������ֵ

		measurement.at<float>(0) = (float)A[i][0];

		measurement.at<float>(1) = (float)A[i][1];

		measurement.at<float>(2) = (float)A[i][2];

		//����

		KF.correct(measurement);

		//������

		cout << "predict =" << "\t" << prediction.at<float>(0) << "\t" << prediction.at<float>(1) << "\t" << prediction.at<float>(2) << endl;

		cout << "measurement=" << "\t" << measurement.at<float>(0) << "\t" << measurement.at<float>(1) << "\t" << measurement.at<float>(2) << endl;

		cout << "correct =" << "\t" << KF.statePost.at<float>(0) << "\t" << KF.statePost.at<float>(1) << "\t" << KF.statePost.at<float>(2) << endl;

	}

	system("pause");

}