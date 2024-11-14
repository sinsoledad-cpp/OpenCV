#include<opencv2/opencv.hpp>
#include<iostream>
#include<vector>


int main()
{
	cv::Mat image(600, 600, CV_8UC3);
	cv::RNG& rng = cv::theRNG();
	while (1)
	{
		int count = rng.uniform(3, 103);
		std::vector<cv::Point> points;
		for (int i = 0; i < count; i++)
		{
			cv::Point point;
			point.x = rng.uniform(image.cols / 4, image.cols * 3/4);
			point.y = rng.uniform(image.rows / 4, image.rows * 3/4);
			points.push_back(point);

		}

		cv::RotatedRect box = cv::minAreaRect(cv::Mat(points));
		cv::Point2f vertex[4];
		box.points(vertex);

		image = cv::Scalar::all(0);
		for (int i = 0; i < count; i++)
		{
			cv::circle(image, points[i], 3,
				cv::Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255),
					cv::FILLED));
		}

		for (int i = 0; i < 4; i++)
		{
			cv::line(image, vertex[i], vertex[(i + 1) % 4], cv::Scalar(100, 200, 211), 2);
		}
		cv::imshow("Ð§¹ûÍ¼", image);
		char key = (char)cv::waitKey();
		if (key == 27 || key == 'q' || key == 'Q')
		{
			break;
		}
	}

	cv::waitKey(0);
	return 0;
}

