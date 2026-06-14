#pragma once

#include <iostream>
using namespace std;
template <class t>
class node {
public:
    t data;
    node<t>* next;


    node() :data(t()), next(nullptr) {}


    void setData(t x) {
        data = x;
    }
    void setNext(node<t>* c) {
        next = c;
    }
    t getData() {
        return data;
    }
    node<t>* getNext() {
        return next;
    }



};
template <class t>
class linkedList {
    node<t>* head;
    int size;

    node<t>* reverseKGroupHelper(node<t>* currentHead, int k) {
        node<t>* temp = currentHead;
        int count = 0;


        while (count < k) {
            if (temp == nullptr) {
                return currentHead;
            }
            temp = temp->getNext();
            count++;
        }


        node<t>* previousnode = reverseKGroupHelper(temp, k);


        temp = currentHead;
        int count2 = 0;
        while (count2 < k) {
            node<t>* nextNode = temp->getNext();
            temp->setNext(previousnode);
            previousnode = temp;
            temp = nextNode;
            count2++;
        }

        return previousnode;
    }

public:
    linkedList() {
        head = nullptr;
        size = 0;
    }
    linkedList(const linkedList<t>& list) {
        node<t>* current = list.head;
        if (list.head == nullptr) {
            head = nullptr;
            size = list.size;
        }

        else {
            this->head = new node<t>();
            node<t>* temp = head;
            while (current != nullptr) {
                temp->setData(current->getData());
                if (current->getNext() != nullptr) {
                    node<t>* n = new node<t>();
                    temp->setNext(n);
                    temp = n;
                }
                else {
                    temp->setNext(nullptr);
                }
                current = current->getNext();
            }

            size = list.size;
        }
    }



    void insertAtEnd(t data) {
        size++;
        node<t>* temp = new node<t>();
        temp->setData(data);
        if (head == nullptr) {
            head = temp;
            return;
        }
        else {
            node<t>* t = head;
            while (t->getNext() != nullptr) {
                t = t->getNext();
            }
            t->setNext(temp);
        }
    }


    void insertAtStart(t data) {
        size++;
        node<t>* temp = new node<t>();
        temp->setData(data);
        temp->setNext(head);
        head = temp;
    }

    void display() {
        node<t>* temp = head;
        if (head == nullptr) {
            cout << "The linked list is empty\n";
        }
        else {
            while (temp != nullptr) {
                cout << "Data = " << temp->getData() << endl;
                temp = temp->getNext();
            }
        }
    }

    void deleteFromEnd() {

        node<t>* temp = head;
        if (temp == nullptr) {
            cout << "The linked list is empty\n";
        }
        else if (head->getNext() == nullptr) {
            delete head;
            size--;
            head = nullptr;
        }
        else {
            while (temp->getNext()->getNext() != nullptr) {
                temp = temp->getNext();
            }
            delete temp->getNext();
            temp->setNext(nullptr);
            size--;
        }
    }

    void deleteFromStart() {

        node<t>* temp = head;
        if (head == nullptr) {
            cout << "The linked list is empty\n";
        }
        else {
            temp = head->getNext();
            delete head;
            head = temp;
            size--;
        }
    }

    void search(t d) {
        bool found = false;
        if (head == nullptr) {
            cout << "The list is empty";
            return;
        }
        else {
            node <t>* temp = head;
            while (temp != nullptr) {
                if (temp->getData() == d) {
                    cout << "The data exists in the linked list\n";
                    found = true;
                    break;

                }
                temp = temp->getNext();
            }
        }
        if (found == false) {
            cout << "The data does not exist in the linked list\n";
        }
    }
    ~linkedList() {
        node<t>* temp = head;
        while (temp != nullptr) {
            node<t>* nextNode = temp->getNext();
            delete temp;
            temp = nextNode;
        }
        head = nullptr;
    }
    int sizeOfList() {
        return size;
    }

    void insertAtAnyPosition(int x, t data) {
        int count = 0;
        if (x > size || x < 0) {
            return;
        }



        if (x == 0) {
            node<t>* n = new node<t>;
            n->setData(data);
            n->setNext(head);
            head = n;
            size++;
            return;
        }

        else if (x <= size) {
            node<t>* n = new node<t>;
            n->setData(data);
            node<t>* temp = head;
            while (count < x - 1) {
                temp = temp->getNext();
                count++;
            }
            n->setNext(temp->getNext());
            temp->setNext(n);
            size++;

        }

    }

    void reverseUsingK(node<t>* temp, int k) {
        node<t>* temp = head;
        int count = 0;
        while (count < k) {
            if (temp == nullptr) { return; }
            else {
                count++; temp = temp->getNext();
            }
        }
        node<t>* prev = reverseUsingK(temp, k);
        temp = head;

    }



    void deleteFromAnyPoint(int x) {
        int count = 0;
        if (head == nullptr || x >= size || x < 0) {
            cout << "The array is either out of range or is empty \n";
            return;
        }
        if (x == 0) {//for head
            node<t>* temp = head->getNext();
            delete head;
            size--;
            head = temp;
        }

        else if (x <= size) {//can only delete a node if it exists
            node<t>* temp = head;
            while (count < x - 1 && temp->getNext() != nullptr) {
                temp = temp->getNext();
                count++;
            }
            node<t>* target = temp->getNext(); //has the one that needs to be deleted
            temp->setNext(target->getNext());
            delete target;
            target = nullptr;
            size--;
        }

    }

    void reverse() {
        node<t>* temp = head;
        node<t>* a, * b;
        a = b = nullptr;
        while (temp != nullptr) {

            b = temp->getNext();

            temp->setNext(a);

            a = temp;
            temp = b;
        }
        head = a;
    }

    void merge(const linkedList <t>& l1, const linkedList <t>& l2) {
        head = nullptr;
        node<t>* n = nullptr;
        node<t>* temp1 = l1.head;
        node<t>* temp2 = l2.head;

        while (temp1 != nullptr && temp2 != nullptr) {
            node<t>* newnode = new node<t>();
            if (temp1->getData() < temp2->getData()) {

                newnode->setData(temp1->getData());
                temp1 = temp1->getNext();

            }
            else if (temp2->getData() < temp1->getData()) {
                newnode->setData(temp2->getData());
                temp2 = temp2->getNext();

            }
            else {
                newnode->setData(temp1->getData());
                temp1 = temp1->getNext();
                temp2 = temp2->getNext();
                size++;

            }
            if (head == nullptr) {
                head = newnode;
                n = newnode;
            }
            else {
                n->setNext(newnode);
                n = newnode;
            }
            size++;
        }
        if (temp1 == nullptr) {
            while (temp2 != nullptr) {
                node<t>* newnode = new node<t>();

                newnode->setData(temp2->getData());
                temp2 = (temp2->getNext());
                n->setNext(newnode);
                n = newnode;
                size++;
            }
        }
        else if (temp2 == nullptr) {
            while (temp1 != nullptr) {
                node<t>* newnode = new node<t>();

                newnode->setData(temp1->getData());
                n->setNext(newnode);
                temp1 = (temp1->getNext());
                n = newnode;
                size++;
            }

        }


    }

    void findMiddle() {
        node <t>* temp = head;
        node<t>* slow = head;

        if (head == nullptr) {
            cout << "The list is empty";
            return;
        }


        while (temp != nullptr && temp->getNext() != nullptr) {

            temp = temp->getNext()->getNext();
            slow = slow->getNext();

        }
        cout << "The value of the middle is " << slow->getData() << endl;

    }

    node<t>* getHead()
    {
        return head;
    }
    
    friend ostream& operator<<(ostream& os, const linkedList<string>& list) {
        node<t>* temp = list.head;
        if (temp == nullptr) {
            os << "[Empty List]";
        }
        else {
            while (temp != nullptr) {
                os <<"\t"<< temp->getData();
                if (temp->getNext() != nullptr) {
                    os << "\n ";
                }
                temp = temp->getNext();
            }
        }
        return os;
    }

};
