
#include <iostream>
using namespace std;
class hello {
protected:
    string name;
public:
    hello(string n="hello") {
        name = n;
    }
    void display() {
        cout << name;
        cout << endl;
    }

};
class bye:public hello {
public:
    void display() {
        hello::display();
        cout << "bye";

    }
};
int main()
{
    bye b1;
    b1.display();
}

