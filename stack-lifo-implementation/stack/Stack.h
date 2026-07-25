// stack.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
/////////////////////////////////////////////////////////////////////////the dynamic stack/////////////////////////////////////
#include <iostream>
using namespace std;
template <class t>
class node {
    node<t>* next;
    t data;
public:

    node() {
        next = nullptr;
        data = t();
    }

    void setNext(node<t>* n) { next = n; }
    node<t>* getNext() { return next; }
    void setData(t d) { data = d; }
    t getData() { return data; }

};
template <class t>
class Stack {
    node<t>* head;
public:
    Stack() {
        head = nullptr;
    }
    void push(t d) {
        node<t>* n = new node<t>();
        n->setData(d);
        n->setNext(head);
        head = n;
    }
    t pop() {
        if (head == nullptr) {
            
            return t();
        }
        node<t>* n = head;
        head = head->getNext();
        t data = n->getData();
        delete n;
        return data;
    }
    t peek() {
        if (head != nullptr) {
            return head->getData();
        }
        return t();
    }

    bool isEmpty() {
        return head == nullptr;
    }

    Stack(const Stack& p) {

        if (p.isEmpty()) { 
            head = nullptr;
            return; }
        else {
            node<t>* temp = p.head;
            node<t>* n = new node<t>();
            n->setData(temp->getData());
            head = n;
            node<t>* temp2 = head;
            temp = temp->getNext();
            while (temp != nullptr) {
                node<t>* n = new node<t>();
                n->setData(temp->getData());
                temp2->setNext(n);
                temp2 = temp2->getNext();
                temp = temp->getNext();
            }
        }
    }

    ~Stack() {
        while (head != nullptr) {
            pop();
        }
    }

    node<t>* getStartpointer() {

        return head;
    }
    void printStack() {
        node<t>* current = head;
        while (current != nullptr) {
            cout << current->getData() << " ";
            current = current->getNext();
        }
        cout << endl;
    }
};


  
