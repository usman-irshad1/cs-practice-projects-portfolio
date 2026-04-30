// deep_copy.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std;

class Intarray {
    int* array;
    int size;
public:
    Intarray(int i = 5) {
        size = i;
        array = new int[i];
        for (int i = 0; i < size; i++) {
            array[i] = 7;
        }
    }
    Intarray(const Intarray& a) {
        size = a.size;
        array = new int[a.size];
        for (int i = 0; i < size; i++) {
            array[i] = a.array[i];
        }
    }
    void change() {
        for (int i = 0; i < size; i++) {
            array[i] =5;
        }
    }

    void display() {
        for (int i = 0; i < size; i++) {
            cout << array[i];
            cout << endl;
        }

    }
};
int main()
{
    Intarray a;
    Intarray b = a;
    a.display();
    b.display();
    b.change();
    a.display();
    b.display();

    
}

