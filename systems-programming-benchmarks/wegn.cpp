#include <iostream>
using namespace std;

class angle {
	int degree;
	float min;
	char direction;

public:
	angle(int d = 0, float m = 0, char di = 'a') :degree(d), min(m), direction(d) {}

	void set_value(int d , float m , char di) {
		degree = d;
		min = m;
		direction = di;
	}

	void display() {
		char x = '\xF8';
		cout << degree << x << min << "'" << direction;
	}
};

class ship {
	angle longitude;
	angle latitude;
	static int id;
	int ship_id;
public:
	ship(int d = 0, float m = 0, char di = 'a') :ship_id(id++), latitude(d, m, di) , longitude(d,m,di){}

	void set_val() {
		int de;
		float m;
		char di;
		cout << "Input degree = ";
		cin >> de;
		cout << "Input minutes = ";
		cin >> m;
		cout << "Input direction = ";
		cin >> di;
		longitude.set_value(de, m, di);
		cout << endl;
		latitude.set_value(de, m, di);
		cout << endl;

	}

	void display() {
		longitude.display();
		latitude.display();

		cout << "SHIP ID\n";
		cout << ship_id;
		cout << endl;
	}
};

int ship::id = 0;

int main() {
	ship s1,s2,s3;
	s1.set_val();
	s2.set_val();
	s3.set_val();

	cout << endl;
	s1.display();
	s2.display();
	s3.display();
	


}