// double_linked_list.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std;
template<class t>
class node {
public:
    node* next;
    node* prev;
    t data;

    node(): next(nullptr), prev(nullptr), data(t()){}
};
template<class t>
class doubleLinkedList {
    int size;
    node<t>* head;
    node<t>* tail;
public:
    doubleLinkedList() {
        head = tail = nullptr;
        size = 0;
    }
    

    void insertAtStart(t d) {
        size++;
        node<t>* temp = new node<t>();
        temp->data = d;
        if (head == nullptr) {
            head = temp;
            tail = temp;
        }
        else {
            
            temp->next = head;
            head->prev = temp;
            temp->prev = nullptr;
            head=temp;
            
        }
    }


    void insertAtEnd(t value) {
       
        size++;
        node <t>* temp = new node<t>();
        temp->data = value;
        if (head == nullptr) {
            head = temp;
            tail = temp;
        }
        else {
            temp->prev = tail;
            tail->next = temp;
            temp->next = nullptr;
            tail = temp; 
        }
    }
    void displayFromStart() {
        if (head == nullptr) {
            cout << "The linked list is empty"<<endl;
            return;
        }
        else {
            node* <t>temp = head;
            while (temp != nullptr) {
                cout << "Data = " << temp->data << endl;
                temp = temp->next;
            }
        }

    }
};




int main()
{
    cout << "Hello World!\n";
}

