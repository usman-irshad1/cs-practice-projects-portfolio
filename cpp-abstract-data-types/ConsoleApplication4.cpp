#include<iostream>
#include<string>
using namespace std;
class pet {
protected:
	string name;
public:
	pet(string n = "Puss") :name(n) {}


	virtual void display() {
		cout << "Name = " << name << endl;
	};
	virtual void input() = 0;//pure virtual funtion
	virtual double get_weight()const {
		cout << "get_weight";
		return 0;
	};

};

class Cat : public pet {
	string color;
public:
	Cat(string n = "Death", string c = "black") :pet(n), color(c) {}
	void display() override {
		pet::display();
		cout << "Color = " << color << endl;
	}
	void input() override {
		cout << "Enter name = " ;
		cin >> name;
		cout << "Enter color = ";
		cin >> color;
	}


};

class Dog : public pet {
	double weight;
public:
	Dog(string n = "Death", double c = 967) :pet(n), weight(c) {}
	void display() override {
		pet::display();
		cout << "Weight = " << weight << endl;
	}
	void input() override {
		cout << "Enter name = ";
		cin >> name;
		cout << "Enter weight= ";
		cin >> weight;
	}

	double get_weight() const {
		return weight;
	}
	

};
class wrong_input :public exception {
	public :
		const char* what() {
			return "\nError 1\nYour input is incorrect\n ";

	}
};

int main() {
	pet* array[100];
	string choice;
	int count=0;
	
	cout << y;
	for (int i = 0; i < 100; i++) {
		try {
			cout << "\nInput c for cat \nd for doge\n-1 for exiting";
			cin >> choice;
			if (choice == "c" || choice == "C") {
				array[i] = new Cat("hello", "Green");
				array[i]->input();
				array[i]->display();
				count++;
			}
			else if (choice == "d" || choice == "D") {
				array[i] = new Dog("Dog", 156);
				array[i]->input();
				array[i]->display();
				count++;
			}
			else if (choice == "-1") {
				cout << "You have exited the program \n";
				break;

			}
			else {
				i--;
				throw wrong_input();
			}
		}
			catch (wrong_input & c){
				cout << c.what();
		}
	}
	double w;

	double sum=0;
	int d=0;
	Dog* array_d[100];
	Dog* temp;
	for (int i = 0; i < count; i++) {
		
		temp = dynamic_cast<Dog*>(array[i]);
		if (temp != nullptr) {
			array_d[d]=temp;
			d =d+1;
		}
	}
	if (d > 0) {
		double max = array_d[0]->get_weight();
		double min = array_d[0]->get_weight();
		for (int i = 0; i < d; i++) {
			w = array_d[i]->get_weight();
			if (max < w) {
				max = w;
			}
			if (min> w) {
				min = w;
			}
			sum = sum + w;
		}
		cout << max;
		cout << min;
	}
	
	cout << sum / d;
	for (int i = 0; i < count; i++) {
		delete array[i];
	}
}