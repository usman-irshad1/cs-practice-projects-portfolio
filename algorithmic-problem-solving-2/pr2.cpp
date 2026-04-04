#include <iostream>
using namespace std;


class Shape {
protected:
    string name;
public:
    Shape(string n = "xxx") :name(n) {}
    float virtual area() const = 0;
    void virtual display() const = 0;
    void virtual in() = 0;
    friend void printDetails(const Shape& t1);
};


class Triangle : public Shape {
    int  base, height;
public:
    Triangle(int b = 0, int h = 0) :base(b), height(h) {};

    float  area() const override {
        return 0.5 * base * height;
    }
    void in() {
        cin >> base;
        cin >> height;
    }

    void display() const {
        cout << name;
        cout << base;
        cout << height;
    }
    friend void printDetails(const Shape& t1);
};

class Square : public Shape {
    int  base;
public:
    Square(int b = 0) :base(b) {};

    float  area() const override {
        return base * base;
    }
    void in() {
        cin >> base;
    }

    void  display() const {
        cout << name;
        cout << base;
  
    }
    friend void printDetails(const Shape& t1);
};

 void printDetails(const Shape&  t1) {
     cout << "name = ";
     cout << t1.name;
     cout << "\nArea = ";
     cout << t1.area();
 }


int main()
{
    Shape* s1[2];
    int x = 0;
    cout << "1 for square and 2 for trinagle";
    cin >> x;
    for (int i = 0; i < 2; i++) {
        if (x == 1) {
            s1[i] = new Square;
            s1[i]->in();
            s1[i]->display();
            s1[i]->area();
            printDetails(*s1[i]);
        }
        if (x == 2) {
            s1[i] = new Triangle;
            s1[i]->in();
            s1[i]->display();
            s1[i]->area();
            printDetails(*s1[i]);
        }
        cin >> x;
    }
    for (int i = 0; i < 2; i++) {
        delete s1[i];
    }
}

