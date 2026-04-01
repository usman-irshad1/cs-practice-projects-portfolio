// circle_file.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std;
#include <fstream>
class Circle {
    int rad;
    string color;
public:
    Circle(int i = 1,string c = "Yellow") {
        rad = i;
        color = c;

    }

    friend ofstream& operator<<(ofstream& o,  const Circle & c1 ) {
        o << "Radius = " << c1.rad << "\nColor = " << c1.color << endl;
        return o;
    }

    friend ifstream& operator>>(ifstream& i, Circle& c1) {
        i>>c1.rad>>c1.color;

        return i;
    }
    void display() {
        cout << rad;
        cout << endl;
        cout << color;
        cout << endl;
    }

};
int main()
{
    Circle c1[10];
    Circle c2[10];
    ofstream g("Circle_file.txt");
    for (int i = 0; i < 10; i++) {
        g << c1[i];
    }
    g.close();

    ifstream f("Circle_file.txt");
    for (int i = 0; i < 10; i++) {
        f >> c2[i];
        cout << i;
        c2[i].display();
    }
    f.close();
    

}
