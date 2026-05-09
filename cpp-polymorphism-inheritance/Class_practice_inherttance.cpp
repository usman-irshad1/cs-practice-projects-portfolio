
#include <iostream>
using namespace std;

class Shape {
protected:
    float dimension;
public:
    Shape(float d = 0) :dimension(d) {}
    void setter(float d) {
        dimension = d;
    }
    float getter() {
        return dimension;
    }

};
class Circle : public Shape {
    float area;
    float circumference;

public:

    Circle(float d = 10, float a = 314, float p = 61.8) :Shape(d), area(a), circumference(p){}
    void ar() {
        area = dimension * dimension*3.14;
    }
    void per() {
        circumference = dimension * 2 *3.14;
    }
    float get_area() {
        return area;
    }
};

class Square : public Shape {
    float area;
    float perimeter;
public:
    void ar() {
        area = dimension * dimension;
    }
    void per() {
        perimeter= dimension *4;
    }
    float get_area() {
        return area;
    }
    float get_per() {
        return perimeter;
    }

};

int main()
{
    Circle c1;
    c1.setter(25);
    cout<<c1.getter();

}

