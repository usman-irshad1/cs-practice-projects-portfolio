
// QUEUE_PRACTICE.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std;

template <class t>
class node {
public:
    node<t>* next;
    t data;
    node() {

        next = nullptr;
        data = t();
    }
    node(t d) {

        next = nullptr;
        data = d;
    }
};




template <class t>
class QUEUE { 
    node<t>* head;
    node<t>* tail;
public:
    QUEUE() { head = tail = nullptr; }


    QUEUE(const QUEUE& x) {
        if (x.head == nullptr) { head = tail = nullptr; return; }
        node<t>* original_head = x.head;
       
        node<t>* ne = new node<t>(x.head->data);
        head = ne;
        node<t>* h = head;
        original_head = original_head->next;
        while (original_head != nullptr) {
           node<t>* n= new node<t>(original_head->data);
           h->next = n;
           h = n;
           original_head = original_head->next;
        }
        tail = h;
    }

    void enqueue(t data) {
        node<t>*n= new node<t>(data);
        if (head == nullptr) {
            head = tail = n;
            return;
        }
        tail->next = n;
        tail = n;
    }

    void dequeue() {
        if (head == nullptr) {
            
            return;
        }
        node<t>* n = head->next;
        delete head;
        head = n;

        if (head == nullptr) {
            tail = nullptr;
        }
    }

    void display() {
        node<t>* temp = head;
        while (temp != nullptr) {
            cout << "\tData = " << temp->data << endl;
            temp = temp->next;
        }
    }

    ~QUEUE() {
        while (head != nullptr) {
            this->dequeue();
        }
    }

    bool search(t data) {
        node<t>* temp = head;
        while (temp != nullptr) {
            if (temp->data == data) { return true; }
            temp = temp->next;
        }
    return false; 
    }
    t front() {
        if (head != nullptr) {
            return head->data;
        }
        return t();
      
    }

    QUEUE& operator=(const QUEUE& x) {
        if (this == &x) return *this; 

       
        while (head != nullptr) {
            dequeue();
        }

        
        node<t>* temp = x.head;
        while (temp != nullptr) {
            enqueue(temp->data);
            temp = temp->next;
        }
        return *this;
    }

    bool isEmpty() {
        return head == nullptr;
    }

    t back() {
        if (tail != nullptr) {
            return tail->data;
        }
        return t();
    }


};
int main()
{
    std::cout << "Hello World!\n";
}
