// static_que.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std;
template <class t, int cap>
class PlaceHolder{
    t d;
    int priority;
public:
    PlaceHolder():d(t()) , priority(int()){}
    void operator= (const t &data) {
        d = data;
    }
    bool operator<(const PlaceHolder& c) {
        if (this->priority < c.priority) { return true; }
        else { return false; }
    }
    void setData(const t& data) { d = data; }
    void setPriority(int p) { priority = p; }
};
template <class t, int cap>
class static_queue{
    t data[cap];
    int head, tail, count;


public:
    static_queue() {
        head = count = 0;
        tail = -1;
    }

    bool isFull() {
        return count == cap;
    }

    bool isEmpty() {
        if (count == 0) {
            return true;
        }
        else {
            return false;
        }
    }

    void Enqueue(t d) {
        if (isFull()) {   
            return;
        }
        else {
            count++;
            tail = (tail + 1) % cap;
            data[tail] = d;
          
    
        }
    }

    void insertAtPriority(t d) {
        if (isFull()) { return; }
        else {
            for (int i = 0; i < count; i++) {
                if (data[i] < d) {
                    count++;
                    tail = (tail + 1) % cap; break;
                }
            }
        }
    }

    t dequeue() {
        if (isEmpty()) { return t(); }
        t item = data[head];
        head=(head+1)%cap;
        count--;
        return item;
    }

    t getTop() {
        return data[head];
    }
   
};


int main() {
    static_queue<int, 5> q;

    q.Enqueue(10);
    q.Enqueue(20);
    q.Enqueue(30);
    q.Enqueue(40);
    q.Enqueue(50);

    if (q.isFull()) {
        cout << "Queue is full cannot add more." << endl;
    }

    cout << "Delete= " << q.dequeue() << endl;
    cout << "Delete= " << q.dequeue() << endl;
    cout << "Top " <<q.getTop()<<endl;
    q.Enqueue(60);

    while (!q.isEmpty()) {
        cout << "Deleting " << q.dequeue() << endl;
    }
    
    return 0;
}
// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
