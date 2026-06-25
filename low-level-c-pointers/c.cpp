#include "album.h" 
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;


int main() {
	image_manip i("C:\\Users\\usman\\OneDrive\\Pictures\\Screenshots\\Screenshot 2025-10-25 161759.png", 1, 1);
	cout << i;
	i++;
	cout << i;
	i--;
	cout << i;
	cin >> i;
	cout << i;

}
