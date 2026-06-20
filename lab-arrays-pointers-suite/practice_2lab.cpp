// LAB_MID_UsmanIrshad_533076.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <C:\oops_folder\lab_mid_usman_oops\.vs\lab_mid_usman_oops.slnx\Stack.h>
#include<C:\oops_folder\lab_mid_usman_oops\.vs\lab_mid_usman_oops.slnx\BST_mid.h>
#include<C:\oops_folder\lab_mid_usman_oops\.vs\lab_mid_usman_oops.slnx\Queue.h>
#include<C:\oops_folder\LAB_MID_UsmanIrshad_533076\heap_h.h>
using namespace std;
struct Medicine {
	string Medname;
	Medicine() {
		Medname = "Panadole";
	}

	friend istream& operator>>(istream& i, Medicine& g) {
		i >> g.Medname;
		return i;
	}

	friend ostream& operator<<(ostream& i, const Medicine& g) {
		i << g.Medname;
		return i;
	}

};
struct Patient {

	int id;
	string name;
	static int id_count;
	string status;  //P PROCCESED OR NOT
	Stack <Medicine> treatment;
	Patient() {
		id = id_count++;
		name = "John Doe";
		status = "Not treated";
	}
	bool operator<(const Patient& c) const {
		if (id < c.id) { return true; }
		else { return false; }
	}
	bool operator>(const Patient& c) const {
		if (id > c.id) { return true; }
		else { return false; }
	}
	bool operator==(const Patient& c) const {
		if (id == c.id) { return true; }
		else { return false; }
	}
	void setStatus(string d) { status = d; }
	void push(Medicine c) {
		treatment.push(c);
	}

	void pop() {
		treatment.pop();
	}
	friend ostream& operator<<(ostream& i, const Patient& g) {
		i << "Name = " << g.name << endl;
		i << "ID = " << g.id << endl;
		i << "Status= " << g.status << endl;
		g.treatment.display();
		return i;

	}

};


class Documentation {


};
