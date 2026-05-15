// practice.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std;

class Course {
protected:
	string name;
	int code;

public:
	Course(string n = "OOPS", int c = 1) : name(n), code(c) {}
	virtual void out() const = 0;
	virtual void in() = 0;
	virtual int grade() = 0;
	};

class Theory :public Course{
	int quiz, mid, final;
public:
	Theory(string n="OOPs", int a = 0, int i = 0, int j = 0, int k = 0) : Course(n,a), quiz(i),mid(j), final(k) {}

	void out() const override {
		cout << "Name: " << name << ", Code: " << code
			<< ", Quiz: " << quiz << ", Mid: " << mid
			<< ", Final: " << final << endl;

	}

	void in() override {
		int x, y, z;
		string n;
		cout << "Enter the name of the course \n";
		cin >> name;
		cout << "Enter the code of the course \n";
		cin >> code;
		cout << "Enter the marks in quizzes\n";
		cin >> quiz;
		cout << "Enter the marks in midterms \n";
		cin >> mid;
		cout << "Enter the marks in finals\n";
		cin >> final;
	}

	int grade() override {
		int grade;
		grade = final + mid + quiz;
		return grade;
	}

};

class Lab :public Course {
	int lab, viva;
public:
	Lab(int l = 0, int v = 0) :lab(l), viva(v) {}

	void out() const override {
		cout << "Name: " << name << ", Code: " << code
			<< ", Lab: " << lab << ", Viva: " << viva << endl;

	}

	void in() override {
		int x, y, z;
		string n;
		cout << "Enter the name of the course \n";
		cin >> name;
		cout << "Enter the code of the course \n";
		cin >> code;
		cout << "Enter the marks in lab\n";
		cin >> lab;
		cout << "Enter the marks in viva \n";
		cin >> viva;
	}
	 
	int grade() override {
		return(lab + viva);
	}

};


int main() {
	Course* c1[10];
	int x;
	cout << "1 for theory and 2 for lab";
	cin >> x;
	for (int i = 0; i < 10; i++) {
		if (x == 1) {
			c1[i] = new Theory;
			c1[i]->in();
			cout << c1[i]->grade();
			c1[i]->out();
		}
		else if (x == 2) {
			c1[i] = new Lab;
			c1[i]->in();
			cout << c1[i]->grade();
			c1[i]->out();
		}
		cin >> x;
	}

	for (int i = 0; i < 10; i++) {
		delete c1[i];
	}
}