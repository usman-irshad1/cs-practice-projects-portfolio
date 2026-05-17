#include<iostream>
using namespace std;

class wrong_size : public exception {
public:
	const char* what() {
		return "\nWrong size\n";
	}
};

template <class t>
class data_storage {
protected:
	t* array;
	int size;
public:
	data_storage(int i = 0) :size(i) {
		if (size > 0) {
			array = new t[size];
			for (int j = 0; j < size; j++) {
				array[j] = t(9);
			}
		}
		else {
			throw wrong_size();
		}
	}

	data_storage(const data_storage& old) {
		size = old.size;
		if (size > 0) {
			array = new t[size];
			for (int j = 0; j < size; j++) {
				array[j] = old.array[j]; 
			}
		}
		else {
			throw wrong_size();
		}
	}

	~data_storage() {
		delete[] array;
	}

	virtual void insert(int index=0,t value=t(6)) {
		array[index] = value;
	}
	virtual void display() {
		for (int i = 0; i < size; i++) {
			cout << array[i];
			cout << endl;
		}
	}
};

class loggerDetails {
	int id;
	string name;
public :
	loggerDetails(int i = 0, string n = ""): name(n), id(i) {};

	void set_data() {
		cin >> name;
		cin >> id;
	}
	int get_id() {
		return id;
	}
	string get_name() {
		return name;
	}
	friend void display_log(const loggerDetails&);
};

void display_log(const loggerDetails&x) {
	cout << "\nName = ";
	cout << x.name;
	cout << "\nID = ";
	cout << x.id;
	cout << endl;

}
template <class t>
class SensorLogger : public data_storage<t> {
	loggerDetails l;
public:
	SensorLogger(int i = 0, int j = 0, string n = "") :l(j, n), data_storage<t>(i) {}

	void display() override {
		display_log(l);
		data_storage<t>::display();
	}
};

int main() {
	try {
		SensorLogger<int> s1(5, 6, "usman");
		s1.display();
		s1.insert();
		s1.display();
	}
	catch (wrong_size& e) {
		cout<<e.what();
	}
}