
// DSA_lab_1_task1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std;

int main()
{
	float number1, number2;
	number1 = 5.6;

	float * fPtr = nullptr;
	//cout << *fPtr; will cause a crash as the null pointer does not point any where
	//fPtr = ( & number1); can not do this as the ptr is of double type and the variable is of type float so to complete the question I am changing the data type to be the same
	fPtr = &number1;

	cout << "Pointer 1 = " << *fPtr<<endl;
	number2 = *fPtr;
	cout << "Number 2 = " << number2<<endl;

	cout << "Number 1 address = " << &number1 << endl;
	cout << "Pointer 1 address = " << fPtr << endl;
}

