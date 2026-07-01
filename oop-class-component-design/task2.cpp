#include <iostream>
using namespace std;

class Out_of_range: public exception{
public:
	const char* what() {
		return "OUT OF RANGE\n";
	}
};
class ID_error : public exception {
public:
	const char* what() {
		return "ID invalid \n";
	}
};
class high : public exception {
public:
	const char* what() {
		return "Temp is higher than the range \n Error 010";
	}
};
class low: public exception {
public:
	const char* what() {
		return "Temp is lower than the range \n Error 010";
	}
};

class Range {
protected:
	int high;
	int low;
public:
	Range(int i = 0, int j = 0) :high(i), low(j) {}

	int get_high() {
		return high;
	}
	int get_low() {
		return low;
	}

};

class Device {
	int device_id;
	int day_temp;
	Range r;
public:
	Device(int i = 0, int t = 0, int h = 50, int l = 10) : device_id(i), day_temp(t), r(h, l) {}

	void input()
	{
		int x, y, j;
		cout << "Input id";
		cin >> x;
		cout << "Temp\n";
		cin >> y;
		if (y < -50 || y>100) {
			throw Out_of_range();
		}
		if (x <= 0) {
			throw ID_error();
		}

		device_id = x;
		day_temp = y;
	}
	void Analyze() {
		if (day_temp > r.get_high()) {
			throw high();
		}
		else if (day_temp < r.get_low()) {
			throw low();
		}
		
	}
	void display(){
		cout << device_id;
		cout << endl;
		cout << day_temp;
		if (day_temp > 12) {
			cout << "low\n";

		}
		else if (day_temp > 30) {
			cout << "medium\n";

		}
		else if (day_temp > 40) {
			cout << "high\n";

		}
	}

};
int main()
{
	Device d1;
	try {
		d1.input();
		d1.Analyze();
		d1.display();
	}
	catch (Out_of_range& o) {
		cout<<o.what();
	}
	catch (high& o) {
		cout << o.what();
	}
	catch (low& o) {
		cout << o.what();
	}
	catch (ID_error& o) {
		cout << o.what();
	}
}