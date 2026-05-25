// Practice_doubly_linked_list.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <string>
#include <iostream>
using namespace std;
template <class t>
class node {
    t data;
    node<t>* next, * prev;
public:
    node() :next(nullptr), prev(nullptr) {}
    void setData(t f) {
        data = f;
    }
    t getData() {
        return data;
    }

    node<t>* getNext() { return next; }
    node<t>* getPrev() { return prev; }
    void setNext(node<t>* n) { next = n; }
    void setPrev(node<t>* n) { prev = n; }
};
template <class t>
class DoubleLinkedList {
    node <t>* head;
    node <t> *tail;
    int size;

public:
    DoubleLinkedList() :head(nullptr), tail(nullptr){}



    void insertAtStart(t d) {
        node<t>* n = new node<t>();
        n->setData(d);
        node<t>* temp = head;
        size++;
        if (head == nullptr) {
            head=n;
            tail = n;
            return;
        }
        
            head->setPrev(n);
            n->setNext(head);
            head = n;
            head->setPrev(nullptr);
        

    }

    void insertAtEnd(t data) {
        node<t>* n = new node<t>();
        size++;
        n->setData(data);
        if (head ==  nullptr) {
            head = tail = n;
            return;
        }


        tail->setNext(n); n->setPrev(tail); n->setNext(nullptr); tail = n;
    }

    ~DoubleLinkedList() {
        node <t>* temp = tail;
        while (temp != nullptr) {
            node<t>* prev = temp->getPrev();
            delete temp;
            temp = prev;
        }
        head = tail = nullptr;
    }
    
    void insertAtAnyPost(int x, t data) {

        int pos = 0;
        
        node<t>* temp = head;
        if (x == 0) {
            insertAtStart(data);
            size++;
            return;

        }
        while (pos < x - 1 && temp!=nullptr) {
            temp = temp->getNext();
            pos++;
        }

        if (temp->getNext() == nullptr) {
            insertAtEnd(data);
            size++;
            return;
           
        }

        node<t>* n = new node<t>();
        n->setData(data);
        n->setNext(temp->getNext());
        n->setPrev(temp);
        temp->getNext()->setPrev(n);
        temp->setNext(n);
        
        size++;
               
    }


    void deleteAtStart() {}

};

int main()
{
    std::cout << "Hello World!\n";
}
