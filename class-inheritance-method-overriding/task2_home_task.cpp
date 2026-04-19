// task2_home_task.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <stack>
using namespace std;



template <class t>
class s :public stack<t> {
public:
    int checking(string f) {
        while (!this->empty()) {
            this->pop();
        }
        for (int i = 0; i < f.size(); i++) {
            if (f[i] == '(') {
                this->push(f[i]);
            }
            else if (f[i] == ')') {
                if (!this->empty() && this->top() == '(') {
                    this->pop();
                }
                else {
                    
                    cout << "Not equal at " << i <<  endl;
                    return i;
                }
            }

        }
        if (this->empty()) {
            cout << "Equal";
            return -1;
        }
        else {
            cout << "Not equal "<< endl;
            return f.size();
        }
    }
};

int main()
{
    s<char> checker;
    
    string test1 = "(()uytr45((()*)";
    cout << "Checking: " << test1 << endl;
    checker.checking(test1);

    cout << "\n----------------------------\n" << endl;

    string test2 = "(((rgh)h))))";
    cout << "Checking: " << test2 << endl;
    checker.checking(test2);
    cout << "\n----------------------------\n" << endl;

    string test3 = "(((rghh)))";
    cout << "Checking: " << test3 << endl;
    checker.checking(test3);
    return 0;
}

