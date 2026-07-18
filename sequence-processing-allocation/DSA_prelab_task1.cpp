#include <iostream>
using namespace std;

class node {
    int data;
    node* next;

public:
    node() : data(0), next(nullptr) {}

    void setData(int x) {
        data = x;
    }
    void setNext(node* c) {
        next = c;
    }
    int getData() {
        return data;
    }
    node* getNext() {
        return next;
    }
};

class linkedList {
    node* head;
    int size;

public:
    linkedList() {
        head = nullptr;
        size = 0;
    }

    void insertAtEnd(int data) {
        size++;
        node* temp = new node();
        temp->setData(data);
        if (head == nullptr) {
            head = temp;
        }
        else {
            node* t = head;
            while (t->getNext() != nullptr) {
                t = t->getNext();
            }
            t->setNext(temp);
        }
    }

    void insertAtStart(int data) {
        size++;
        node* temp = new node();
        temp->setData(data);
        temp->setNext(head);
        head = temp;
    }

    void display() {
        node* temp = head;
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
        node* temp = head;
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
        node* temp = head;
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

    void search(int d) {
        bool found = false;
        if (head == nullptr) {
            cout << "The list is empty";
        }
        else {
            node* temp = head;
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
        node* temp = head;
        while (temp != nullptr) {
            node* nextNode = temp->getNext();
            delete temp;
            temp = nextNode;
        }
        head = nullptr;
    }

    int sizeOfList() {
        return size;
    }
};

int main()
{
    linkedList l; 
    l.deleteFromEnd();
    l.deleteFromStart();
    l.insertAtEnd(10);

    l.deleteFromEnd();
    l.insertAtEnd(20);

    l.deleteFromStart();
    l.insertAtEnd(30);
    l.insertAtEnd(40);
    l.insertAtStart(12);

    l.display();
}