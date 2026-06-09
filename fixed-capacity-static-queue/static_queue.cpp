#include <iostream>
using namespace std;

template <class t, int size>
class stack {
    t array[size];
    int head;

public:
    stack() {
        head = -1;
    }

    bool isFull() {
        return (size == head + 1);
    }

    bool isEmpty() {
        return (head == -1);
    }

    void push(t data) {
        if (isFull()) {
            cout << "Stack is full" << endl;
            return;
        }
        head++;
        array[head] = data;
    }

    t pop() {
        if (isEmpty()) {
            return t();
        }
        return array[head--];
    }

    t peek() {
        if (!isEmpty()) {
            return array[head];
        }
        return t();
    }


};

int main() {
    stack<int, 4> s;

    s.push(10);
    s.push(20);
    s.push(30);

    cout << "Top element: " << s.peek() << endl;

    cout << "Popped: " << s.pop() << endl;
    cout << "Popped: " << s.pop() << endl;


    s.push(40);
    s.push(50);
    s.push(60);
    s.push(70);
    s.push(80); 

    while (!s.isEmpty()) {
        cout << "Popping: " << s.pop() << endl;
    }

    return 0;
}