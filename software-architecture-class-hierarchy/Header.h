#pragma once
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

class Album {
    string imagePath;
    Mat image;

public:
    Album(string Path);
    void display();
    void setter(string path);
    string getter();
    void input();
};

