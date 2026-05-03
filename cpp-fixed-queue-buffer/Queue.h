
#pragma once
#include <iostream>
using namespace std;

template <class t>
class node {
    node<t>* next;
    t data;
public:
    node() : data(t()), next(nullptr) {}
    void setData(t d) { data = d; }
    t getData() { return data; }
    void setNext(node<t>* n) { next = n; }
    node<t>* getNext() { return next; }
};

template <class t>
class Queue {
    node<t>* start, * end;
public:
    Queue() : start(nullptr), end(nullptr) {}

    void Insert(t data) {
        node<t>* n = new node<t>();
        n->setData(data);
        if (start == nullptr) {
            end = start = n;
        }
        else {
            end->setNext(n);
            end = n;
        }
    }

    Queue(const  Queue& other) {
        start = end = nullptr;
        if (other.isEmpty()) { return; }
        else {
            node<t>* temp = other.start;
             node<t>* n = new node<t>();
            n->setData(temp->getData());
            
            start = end = n;
            temp = temp->getNext();
            while (temp != nullptr) {
                node<t>* n = new node<t>();
                n->setData(temp->getData());
                end->setNext(n);
                end = n;
                temp = temp->getNext();
            }
        
        }
    }

    void Delete() {
        if (start == nullptr) {
            cout << "The queue is empty\n";
            return;
        }
        node<t>* temp = start;
        start = start->getNext();
        delete temp;


        if (start == nullptr) {
            end = nullptr;
        }
    }

    t getFront() {
        if (isEmpty()) { return t(); }
        else {
            return start->getData();
        }
    }

    node<t>* getFrontNode() {
        return start;
    }

    bool isEmpty() {
        return start == nullptr;
    }

    ~Queue() {
        if (this->isEmpty()) { return; }
        else {
            while (start != nullptr) {
                this->Delete();
            }    
        }
    }

    void display() {
        if (this->isEmpty()) { return; }
        node<t>* temp = start->getNext();
        while (temp != nullptr) {
            cout << temp->getData();
            temp = temp->getNext();

    }

    }
    
};


