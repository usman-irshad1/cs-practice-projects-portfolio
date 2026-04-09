// file_handling.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>

int main()
{
    int a = 15;
    ofstream f("test.txt");
    f << a;
    f.close();
    return 0;
}

