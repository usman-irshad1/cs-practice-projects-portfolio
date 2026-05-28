
#include <iostream>
#include<cmath>
using namespace std;



template <class data>
class Point {
    data p1, p2;
public:
    Point(data i1 = data(), data data() = 0) {
        p1 = i1;
        p2 = i2;
    }
    void input() {
        cout << "Input x coordinate = ";
        cin >> p1;
        cout << "Input y coordinate = ";
        cin >> p2;
    }
    void display() const {
        cout << "Your x cordinate is " << p1 << endl;
        cout << "Your x cordinate is " << p2 << endl;
    }

    Point operator+ (Point <data>& o1) {
        Point n1;
        n1.p1 = p1 + o1.p1;
        n1.p2 = p2 + o1.p2;
        return n1;
    }

    Point operator- (Point <data>& o1) {
        Point n1;
        n1.p1 = p1 - o1.p1;
        n1.p2 = p2 - o1.p2;
        return n1;
    }

    Point operator* (Point <data>& o1) {
        Point n1;
        n1.p1 = p1 * o1.p1;
        n1.p2 = p2 * o1.p2;
        return n1;
    }
    int operator== (Point <data>& o1) {
        int checker = 0;
        if (p1 == o1.p1 && p2 == o1.p2) {
            checker = 1;
        }
        else {
            checker = 0;
        }
        return checker;
    }

    bool operator<(Point <data>& o2) {
        data d = p1 * p1 + p2 * p2;
        d = pow(d, 0.5);
        data d1 = o2.p1 * o2.p1 + o2.p2 * o2.p2;
        d1 = pow(d1, 0.5);
        if (d > d1) {
            return false;
        }
        else {
            return true;
        }
    }
    Point& operator++() {
        p1++;
        p2++;
        return *this;
    }

    Point operator++(int) {
        Point temp = *this;
        p1++;
        p2++;
        return temp;
    }

    Point& operator--() {
        p1--;
        p2--;
        return *this;
    }

    Point operator--(int) {
        Point temp = *this;
        p1--;
        p2--;
        return temp;
    }
    friend ostream& operator<<(ostream& out, const Point <data>& p) {
        out << "Point x = " << p.p1 << "\tPoint y = " << p.p2 << endl;
        return out;
    }
    friend istream& operator>>(istream& in, Point <data>& p) {
        cout << "Input point x and y\n";
        in >> p.p1 >> p.p2;
        return in;
    }
    Point<int> sort() {
        Point<int> p[3] = { Point<int>(0,1), Point<int>(1,2), Point<int>(1,3) };
        Point<int> x = p[0];

        for (int i = 1; i < 3; i++) {
            if (x < p[i]) {
                x = p[i];  
            }
        }
        return x;  
    }


};



int main()
{
    Point<float> p1(3, 9);
    Point <float>p2;
    Point <float>p3;
    cin >> p2;
    cout<<p2 + p1;
    cout << endl;
    cout << p2++;
    cout << endl;
    cout << p2--;
    cout << endl;
    p3=(p1 < p2);
}