// DSA_lab1_task2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std;

class IntStaticPointer {

int* ptr;
public:
  
    IntStaticPointer() {
        ptr = nullptr;
    }

     void AllocMem(int a) {
         delete ptr;
         ptr = new int (a);
    }
     void setValue(int a) {
        * ptr = a;
     }
     int getValue() {
         if (ptr!=nullptr)
         return *ptr;
     }

     ~IntStaticPointer() {
         if (ptr != nullptr) {
             cout << "-------------------Deconstructor called--------------------"<<endl;
             cout << "Address of pointer " << ptr << endl;
             cout << "Value of pointer " << *ptr << endl;
         }
         delete ptr;
         ptr = nullptr;
     }

    

};
void mystery(IntStaticPointer& b)
{
    int a = 100;
    b.AllocMem(a);
    cout << b.getValue() << endl;
}
int main()
{
  
        IntStaticPointer b;
        int z = 8;
    
        b.AllocMem(z);
        cout << b.getValue()<<endl;
        mystery(b);
        
        cout << b.getValue() << endl;
    }

 



