#include <iostream>
using namespace std;
 
class input_error : public exception {
public:
	const char* what() {
		return "Input error";
	}
};


class Course {
protected:
	int code;
	string name;
public:
	Course(string c = "", int i = 0) :code(i), name (c){}
	virtual void input() = 0;
	virtual void display() = 0;
	virtual double grade() = 0;

};

class Theory:public Course {
	float mid, quiz, final;

public:
	Theory(string c = "", int i = 0, float a = 0, float b=0, float d=0) :Course(c, i), mid(a), final(b), quiz(d) {}
	void input() {
		cout << "Theory\n";
		cout << "Name = ";
		cin >> name;
		cout << "Code= ";
		cin >> code;
		cout << "Quiz = ";
		cin >> quiz;
		cout << "Mid = ";
		cin >> mid;
		cout << "Final = ";
		cin >> final;
	}
	void display() {
		cout << "Theory\n";
		cout << name << endl << code << endl << quiz << endl << mid << endl << final << endl;
	}
	double grade() {
		cout << "Theory\n";
		return 0.3 * quiz + 0.5 * mid + 0.5 * final;
	}

};
class Lab :public Course {
	float viva, mid;

public:
	Lab(string c = "", int i = 0, float a = 0, float b = 0,) :Course(c, i), mid(a), viva(b) {}
	void input() {
		cout << "lab \n";
		cout << "Name = ";
		cin >> name;
		cout << "Code= ";
		cin >> code;
		cout << "Mid = ";
		cin >> mid;
		cout << "Viva = ";
		cin >> viva;
	}
	void display() {
		cout << "lab \n";
		cout << name << endl << code << endl << mid << endl << viva << endl ;
	}
	f grade() {
		cout << "lab \n";
		return 0.3 * viva + 0.5 * mid;
	}

};
int main() {
	Course* base[10];
	int choice;
	cout << "1 for theory and 2 for lab\n ";
	cin >> choice;
	for (int i = 0; i < 10; i++) {
		try {
			if (choice == 1) {
				base[i] = new Theory;
				base[i]->input();
				base[i]->display();
				base[i]->grade();
			}
			else if (choice == 1) {
				base[i] = new Lab;
				base[i]->input();
				base[i]->display();
				base[i]->grade();
			}
			else {
				throw input_error();
			}
		}
		catch(input_error & a){
			cout<<a.what();
		}
		cout << "1 for theory and 2 for lab\n ";
		cin >> choice;
	}
}