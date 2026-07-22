#pragma once
#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;

class ImageManipulator {

	Mat image;

public:

	ImageManipulator(const string& path = "") {
		image = cv::imread(path);
		if (image.empty()) {
			cout << "The image has not loaded successfully\n";
		}
	}
	void contrast(float& alpha, float& beta) {
		int value;
		for (int i = 0; i < image.rows; i++) {
			for (int j = 0; j < image.cols; j++) {
				Vec3b& pixel = image.at<Vec3b>(i, j);
				for (int k = 0; k < 3; k++) {
					value = pixel[k] * alpha + beta;
					if (value > 255) value = 255;
					if (value < 0) value = 0;
					pixel[k] = value;

				}
			}
		}
	}

	void rotate_image(int r) {
		if (r == 90) {
			cv::rotate(image, image, ROTATE_90_CLOCKWISE);
		}
		else if (r == 180) {
			cv::rotate(image, image, ROTATE_180);
		}
		else if (r == 270) {
			cv::rotate(image, image, ROTATE_90_COUNTERCLOCKWISE);
		}
	}

	void flip_image(int f) {
		cv::flip(image, image, f);

	}
	void display() {
		if (!image.empty()) {
			namedWindow("0_Image", WINDOW_NORMAL);
			imshow("0_Image", image);

		}
		else {
			cout << "It is not valid";
		}
	}

};