
    // list_swap.cpp : This file contains the 'main' function. Program execution begins and ends there.
    //

    #include <iostream>
    using namespace std;

template <class x, int size>
class Stack {
    x array[size];
    int count;

public:
    Stack() { count = 0; }

    void push(x s) {
        if (count >= size) { return; }
        array[count] = s;
        count++;
    }

    void pop() {
        if (count <= 0) { return; }
        count--;
    }

    x peek() {
        if (count <= 0) { return x(); }
       return array[count-1];
    }

};
int main() {
    // 1. Create a stack of 3 strings
    Stack<string, 3> nameStack;

    cout << "--- String Stack ---" << endl;
    nameStack.push("Gemini");
    nameStack.push("C++");
    nameStack.push("Data Structures");

    cout << "Top: " << nameStack.peek() << endl; // Data Structures

    nameStack.pop();
    cout << "After Pop, Top: " << nameStack.peek() << endl; // C++

    // 2. Create a stack of 5 integers
    Stack<int, 5> numStack;

    cout << "\n--- Integer Stack ---" << endl;
    numStack.push(100);
    numStack.push(200);

    cout << "Top: " << numStack.peek() << endl; // 200

    return 0;
}