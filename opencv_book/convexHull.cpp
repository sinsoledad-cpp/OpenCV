#include<opencv2/opencv.hpp>
#include<iostream>
#include<vector>


int main()
{
	cv::Mat image(600, 600, CV_8UC3);
	cv::RNG& rng = cv::theRNG();

	while (1)
	{
		char key;
		int count = (unsigned)rng % 100 + 3;
		std::vector<cv::Point> points;
		for (int i = 0; i < count; i++)
		{
			cv::Point point;
			point.x = rng.uniform(image.cols / 4, image.cols * 3 / 4);
			point.y = rng.uniform(image.rows / 4, image.rows * 3 / 4);

			points.push_back(point);
		}

		std::vector<int> hull;
		cv::convexHull(cv::Mat(points), hull, false, true);

		image = cv::Scalar::all(0);
		for (int i = 0; i < count; i++)
		{
			cv::circle(image, points[i], 3,
				cv::Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255)),
				cv::FILLED);
		}

		int hullcount = (int)hull.size();
		cv::Point point0 = points[hull[hullcount - 1]];
		for (int i = 0; i < hullcount; i++)
		{
			cv::Point point = points[hull[i]];
			cv::line(image, point0, point, cv::Scalar(255, 255, 255), 2);
			point0 = point;
		}
		cv::imshow("Ð§¹û", image);
		key = (char)cv::waitKey();
		if (key == 27)
		{
			break;
		}
	}

	cv::waitKey(0);
	return 0;
}

