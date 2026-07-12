// recursion_practice.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std;
//
//int static factorial(int n) {
//    if (n <= 1) {
//        return 1;
//    }
//    else {
//    return n* factorial(n - 1);
//    
//    }
//}
//
//int static fibanouchi(int x) {
//    if (x == 0) { return 0; }
//    if (x == 1) {
//        return 1;
//    }
//    return fibanouchi(x - 1)+fibanouchi(x-2);
//
//}
int main()
{
    std::cout << "Hello World!\n";
    cout <<  fibanouchi(10);
}

