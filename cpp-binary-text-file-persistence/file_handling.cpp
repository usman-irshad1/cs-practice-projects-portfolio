// file_handling.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
using namespace std;

class LIST {
	int arr[5] = { 0 };
	int arr1[5] = { 0 };
public:
	LIST() {
		for (int i = 0; i < 5; i++){
			cout << "Enter the data = ";
			cin >> arr[i];
		}
	}
	void write(ofstream& a) {
		for (int i = 0; i < 5; i++) {
			a << arr[i]<<endl;
		}
		a.close();
	}
	void read(ifstream& i) {
		for (int i = 0; i < 5; i++) {
			i >> arr1[i];
		}
		i.close();
	}
	void display() {
		for (int i = 0; i < 5; i++) {
			cout << arr1[i];
		}
	}
};
int main()
{
	LIST a1;
	ofstream a("Hell.txt");
	a1.write(a);
	ifstream j("Hell.txt");
	a1.read(j);
	a1.display();
}


