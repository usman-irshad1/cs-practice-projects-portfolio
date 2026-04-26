
// clas_task.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
using namespace std;
class person {

    char name[100];
    int roll;
public:
    person(int i=0) {
        cin >> name;
        roll = i;
    }
    void display() {
        cout << name << endl << roll<<endl;
    }
    ~person() {

    }

};
int main()
{

    person people,p2;

    ofstream o("Data.dat", ios::binary);
    o.write((char*)&people, sizeof(people));
    o.close();

    ifstream i("Data.dat", ios::binary);
    i.read((char*)&p2, sizeof(p2));
    i.close();
    p2.display();


}