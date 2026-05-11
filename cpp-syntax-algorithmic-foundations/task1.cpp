
// task1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>

using namespace std;

class Course {
	int  credit_hours;
	string course_name, grade_earned;
public:
	Course(int i = 0, string n = "void", string g = "P") :credit_hours(i), course_name(n), grade_earned(g) {}
	void set_name() {
		cout << "\nEnter the name of the course = ";
		cin >> course_name;
	}
	void set_hours() {
		cout << "\nEnter the number of the credit hours = ";
		cin >> credit_hours;
	}
	void set_grade() {
		cout << "\nEnter the grade in the course = ";
		cin >> grade_earned;
	}
	string get_grade() {
		return grade_earned;
	}
	string get_name() {
		return course_name;
	}
	int get_hours() {
		return credit_hours;
	}
	friend class Transcript;

};

class student {
	string name, department;
	int  roll_number;

public:
	student(string n = "John Doe", string d = "Computers", int r = 533076) : name(n), department(d), roll_number(r) {}
	void set_name() {
		cout << "\nEnter your name = ";
		cin >> name;
	}
	void set_dep() {
		cout << "\nEnter the name of the department = ";
		cin >> department;
	}
	void set_roll() {
		cout << "\nEnter the roll number = ";
		cin >> roll_number;
	}
	string get_department() {
		return department;
	}
	string get_name() {
		return name;
	}
	int get_roll() {
		return roll_number;
	}
	friend class Transcript;

};

class Postgraduate {
	student s;
	vector <Course*> course;
	int total_courses;
public:
	Postgraduate(int i = 0, string c_n = "void", string g = "P", string n = "John Doe", string d = "Computers", int r = 533076) : s(n, d, r) {
		cout << "\nInput the number of courses you are enrolled in = ";
		cin >> total_courses;
		Course* c;
		for (int a = 0; a < total_courses; a++) {
			c = new Course;
			c->set_name();
			c->set_hours();
			c->set_grade();
			course.push_back(c);
		}
		
	}
	~Postgraduate() {
		for (int i = 0; i < total_courses; i++) {
			delete course[i];
		}
	}
		
		void input() {
			s.set_name();
			s.set_dep();
			s.set_roll();
		}

		void output() {
			cout << s.get_name();
			cout << endl;
			cout << s.get_roll();
			cout << endl;
			cout << s.get_department();
			cout << endl;
			for (int a = 0; a < total_courses; a++) {

				cout << course[a]->get_name();
				cout << endl;
				cout << course[a]->get_hours();
				cout << endl;
				cout << course[a]->get_grade();
				cout << endl;
			}
		}

	friend class Transcript;
};

class Undergraduate {
	student s;
	vector <Course*> course;
	int total_courses;
public:
	Undergraduate(int i = 0, string c_n = "void", string g = "P", string n = "John Doe", string d = "Computers", int r = 533076) : s(n, d, r) {
		cout << "\nInput the number of courses you are enrolled in = ";
		cin >> total_courses;
		Course* c;
		for (int a = 0; a < total_courses; a++) {
			c = new Course;
			c->set_name();
			c->set_hours();
			c->set_grade();
			course.push_back(c);
		}
	}
	void input() {
		s.set_name();
		s.set_dep();
		s.set_roll();
	}

	void output() {
		cout << s.get_name();
		cout << endl;
		cout << s.get_roll();
		cout << endl;
		cout<<s.get_department();
		cout << endl;
		for (int a = 0; a < total_courses; a++) {
			
			cout<<course[a]->get_name();
			cout << endl;
			cout << course[a]->get_hours();
			cout << endl;
			cout << course[a]->get_grade();
			cout << endl;
		}
	}
	~Undergraduate() {
		for (int i = 0; i < total_courses; i++) {
			delete course[i];
		}
	}
	
	friend class Transcript;
};

class Transcript {
public:
	float gpa(Postgraduate& p1) {
		int total=0;
		int grade=0;
		float total_g = 0;
		float gpa=0;
		string g;
		for (int i = 0; i < p1.total_courses; i++) {
			if (p1.course[i]->get_hours() >= 3) {
				total += p1.course[i]->get_hours();
				g = p1.course[i]->get_grade();
				if (p1.course[i]->get_grade() == "A" ||p1. course[i]->get_grade() == "a") {
					grade = 4;
				}
				else if (p1.course[i]->get_grade() == "B" ||p1.course[i]->get_grade() == "b") {
					grade = 3;
				}
				else if (p1.course[i]->get_grade() == "C" || p1.course[i]->get_grade() == "c") {
					grade = 2;
				}
				else if (p1.course[i]->get_grade() == "D" || p1.course[i]->get_grade() == "d") {
					grade = 1;
				}
				else if (p1.course[i]->get_grade() == "F" || p1.course[i]->get_grade() == "f") {
					grade = 0;
				}
				else {
					cout << "The grade is invalid\n";
				}
				total_g += grade * p1.course[i]->get_hours();
			}
		}
		gpa = total_g / total;
		return gpa;
	}

	float gpa(const Undergraduate & u1) {
		int total = 0;
		int grade = 0;
		float total_g = 0;
		float gpa = 0;
		string g;
		for (int i = 0; i <u1. total_courses; i++) {
			total += u1.course[i]->get_hours();
			g = u1.course[i]->get_grade();
			if (u1.course[i]->get_grade() == "A" || u1.course[i]->get_grade() == "a") {
				grade = 4;
			}
			else if (u1.course[i]->get_grade() == "B" || u1.course[i]->get_grade() == "b") {
				grade = 3;
			}
			else if (u1.course[i]->get_grade() == "C" || u1.course[i]->get_grade() == "c") {
				grade = 2;
			}
			else if (u1.course[i]->get_grade() == "D" || u1.course[i]->get_grade() == "d") {
				grade = 1;
			}
			else if (u1.course[i]->get_grade() == "F" || u1.course[i]->get_grade() == "f") {
				grade = 0;
			}
			else {
				cout << "The grade is invalid\n";
			}
			total_g += grade * u1.course[i]->get_hours();
		}
		gpa = total_g / total;
		return gpa;
	}
};

int main() {
	Transcript t1;
	Undergraduate u1;
	Postgraduate p1;
	u1.input();
	u1.output();
	cout << "gpa = ";
	cout<<t1.gpa(u1);
	p1.input();
	p1.output();
	cout << endl;
	cout << t1.gpa(p1);
}