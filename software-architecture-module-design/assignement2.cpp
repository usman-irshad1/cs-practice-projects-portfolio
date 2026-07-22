#include "Header12.h" 
#include <opencv2/opencv.hpp>
#include <iostream>


using namespace std;
using namespace cv;

class infinite_loop :public exception {
public:
    const char* what() {
        return ("Your input is invalid \n");
    }
};
int main(int argc, char** argv)
{
    int c;
    int f;
    float a, b;
    int i = 0;
    string x;
    cout << "Input the path\n";
    getline(cin, x);
    ImageManipulator pic(x);
    pic.display();
    waitKey(10000); //this makes it wait 10 seconds for the other input.
    cout << "\n1 for flipping it \n2 For rotating it \n3 For changing the contrast and brightness\n";
    cin >> i;

    while (i != 4) {
        try {
            if (i == 1) {


                cout << "ENTER either 1 , -1 or 0 for flipping = ";
                cin >> f;
                pic.flip_image(f);
                pic.display();

                waitKey(10000); //this makes it wait 10 seconds for the other input.
            }

            else if (i == 2) {
                cout << "Input 90 180 or 270 = ";
                cin >> c;
                pic.rotate_image(c);
                pic.display();
                waitKey(10000);
            }
            else if (i == 3) {
                cout << "Input the value of contrast = ";
                cin >> a;
                cout << "Enter the value of brightness = ";
                cin >> b;
                pic.contrast(a, b);
                pic.display();
                waitKey(1000);
            }
            else {
                throw infinite_loop();
            }
        }

        catch (infinite_loop& e) {
            cout << e.what();
        }

        cout << "\n1 for flipping it \n2 For rotating it \n3 For changing the contrast and brightness\n for exit press 4\n";
        cin >> i;
    }

    return 0;
}