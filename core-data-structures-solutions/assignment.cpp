#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
    // Create a simple black image (400x400)
    Mat image = Mat::zeros(400, 400, CV_8UC3);

    // Draw some text
    putText(image, "OpenCV Works!", Point(50, 200), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 255, 0), 2);

    // Show image in a window
    imshow("Test Window", image);

    cout << "Press any key in the window to exit..." << endl;

    waitKey(0);  // Wait for a key press
    destroyAllWindows();

    return 0;
}
