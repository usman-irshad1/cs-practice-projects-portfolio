#include <iostream>

using namespace std;

int main() {
    int x;
    int y;
    char c;
    while (true) {
        cout << "\nInput 1st number = ";
        cin >> x;
        cout << "Input 2nd number = ";
        cin >> y;
        cout << "Enter symbol = ";
        cin >> c;

        if (c == '*') {

            cout << x * y;
        }

        if (c == '+') {

            cout << x + y;
        }

        if (c == '-') {

            cout << x - y;
        }
        if (c == '/') {
            if (y != 0) {
                cout << x / y;
            }
        }
    }
}
