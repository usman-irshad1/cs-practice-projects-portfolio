#include<iostream>
using namespace std;


class incorrect_pass :public exception {
public:
	const char* what() {
		return"\nIncorrect Password\n";
	}
};



template <class t>
class storage {
protected:
	t* array;
	int size = 0;
public:
	storage(int s = 5) :size(s) {
		t data = t(0);
		if (size > 0) {
			array = new t[size];
			for (int i = 0; i < s; i++) {
				array[i] = data;
			}
		}
	}

	storage(const storage<t>& c) {
		array = new t[c.size];
		for (int i = 0; i < c.size; i++) {
			array[i] = c.array[i];
		}
		size = c.size;
	}

	friend ostream& operator<< (ostream& o, const storage<t>& s) {
		for (int i = 0; i < s.size; i++) {
			o << s.array[i] << endl;
		}
		return o;
	}

	virtual void display() {
		cout << *this;
	}
	~storage() {
		delete[] array;
	}


};
template <class t>
class secure_storage :public storage <t> {
	string pass;
public:
	secure_storage(int i = 0, string s = "1") :storage<t>(i), pass(s) {}
	void display() {
		string password;
		cout << "\ninput password\n";
		cin >> password;
		if (pass == password) {
			storage<t>::display();
		}
		else {
			throw incorrect_pass();
		}
	}
};

int main() {
	try {
		secure_storage <int> s1(3);
		s1.display();
	}
	catch (incorrect_pass& o) {
		cout << o.what();
	}
}