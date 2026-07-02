

#include <iostream>
using namespace std;
# include <string>
//template <class data, class data2>
//class Container {
//    data* a;
//    data2 b1;
//public:
//
//    Container(const Container& b) {
//        a = new data;
//        *a = *b.a;
//        b1 = b.b1;
//
//    }
//    Container(data b, data2 c) {
//        a = new data;
//        *a = b;
//        this->b1 = c;
//    }
//
//    data compare(Container <data,data2>& b) {
//        if (*a > *(b.a)) {
//            return *(this->a);
//        }
//        else return *(b.a);
//    }
//    ~Container() {
//        delete a;
//    }
//    void get() const {
//        cout << *a;
//        cout << b1;
//
//    }
//};

//int main() {
//    Container <int, char>c1(5, 'a');
//    c1.get();
//    cout << endl;
//    Container <char, int>c2('6', 3);
//    c2.get();
//    Container <int, char>c3 = c1;
//    c3.get();
//    cout<<c3.compare(c1);
//}



//operating overload
//a+b
// first funtion 
//
//

class Circle {
	float r;
public:

	void get(float b) {
		r = b;
	}
	Circle operator+(Circle & b) {
		Circle c;
		c.r = r + b.r;
		return c;
	}
	void print() const{
		cout << r;
	}
	Circle& operator++() {
		r++;
		return *this;
	}
	Circle  operator++(int) {
		Circle c3=*this;
		r++;
		return c3;
	}

	
	friend ostream& operator<<(ostream& o, Circle& c3);
	friend istream& operator>>(istream& o, Circle& c3);
};
ostream& operator<<(ostream & o, Circle& c3) {
	o << c3.r;
	return o;
}

istream& operator>>(istream& i, Circle& c3) {
	i >> c3.r;
	return i;
}
int main() {
	Circle c1; 
	c1.get(5);
	Circle c2;
	c2.get(6);
	Circle c3 = c1 + c2;
	c3.print();	
	cout << c2++<<++c3;
}