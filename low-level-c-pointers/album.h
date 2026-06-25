#pragma once
#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

class image_manip {
	Mat image;
	double alpha, beta;
public:
	image_manip(string s = "", double a = 1, double b = 1) :alpha(a), beta(b) {
		image = cv::imread(s);
	}
	friend ostream& operator<<(ostream& o, const image_manip& a) {
		o << "\nimage displayed\n";
		if (!a.image.empty()) {
			namedWindow("terminal", WINDOW_NORMAL);
			imshow("terminal", a.image);
			waitKey(1000);
		}
		else {
			o << "Wrong input";
		}
		return o;
	}
	void update() {
		this->image.convertTo(this->image, -1, alpha, beta);
	}

	image_manip operator++(int) {
		image_manip temp = *this;
		alpha = alpha +1;
		update();
		return temp;
	}

	image_manip operator++() {
		alpha = alpha + 1;
		update();
		return* this;
	}

	image_manip operator--(int) {
		image_manip temp = *this;
		alpha = alpha + 1;
		update();
		return temp;
	}

	image_manip operator--() {
		alpha = alpha  - 1;
		update();
		return  *this;
	}
	friend istream& operator>>(istream& i, image_manip& p) {
		string x;
		std::getline(i, x);
		p.image=imread(x);
		return i;
	}
};
