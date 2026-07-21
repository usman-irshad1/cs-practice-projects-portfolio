#include <opencv2/opencv.hpp>
#include <iostream>
#include "Header.h"

using namespace cv;
using namespace std;


//have to use \\ instead of \ in the data 
Album::Album(string Path) {
    imagePath = Path;
    image = imread(imagePath);
}


void Album::display() {
    if (image.empty()) {
        cout << "Image not loaded." << endl;
        return;
    }
    // i have done this as if not implemented the pixls blur and are zoomed in so we can obly view a single part of the pic usually the top roght corner
    Mat resizedImage;
    int maxWidth = 800;
    int maxHeight = 600;
    double scaleX = (double)maxWidth / image.cols;
    double scaleY = (double)maxHeight / image.rows;
    double scale = min(scaleX, scaleY);

    if (scale < 1.0) {
        resize(image, resizedImage, Size(), scale, scale);
    }
    else {
        resizedImage = image;
    }

    namedWindow("My Image", WINDOW_NORMAL);
    imshow("My Image", resizedImage);//this will print the image

    cout << " Image loaded successfully. Press any key to close.\n";
    waitKey(100);
}
void Album::setter(string path) {
    imagePath = path;
    image = imread(imagePath);
}
string Album::getter() {
    return imagePath;
}



void Album::input() {
    cout << "Input your path";
    string p;
    getline(cin, p);
    imagePath = p;
    image = imread(imagePath);
    
}



int main()
{
    Album a1("C:\\Users\\usman\\OneDrive\\Pictures\\Screenshots\\Screenshot 2025-11-27 215212.png");
    //a1.input();
    
    a1.display();

    a1.input();
    a1.display();
    waitKey(0);
    destroyAllWindows();
    return 0;
}
