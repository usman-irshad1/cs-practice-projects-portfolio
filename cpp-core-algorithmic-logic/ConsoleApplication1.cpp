// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std;
class counter {
protected:
	int count;
public:
	counter() :count(0) {}
	counter(int c) : count(c) {}
	int get_count() const {
		return count;
	}
	counter operator++() {
		return counter(++count);
	}
 };

class countDn : public counter{
public:
	counter operator-() {
		return counter(--count);
	}

};
