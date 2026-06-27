// doublylinkedlisst.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
using namespace std;
class Station {
    string name;
    int pos;
public:
    Station(string n = "Empty") {
        name = n;
        
    }

    Station(int n) {

        name = to_string(n);
    }

    void setName(string n) { name = n; }
    string getName() { return name; }

    bool operator==(Station q) {
        if (name == q.name) {
            return true;
        }
        else {
            return false;
        }
    }

    void operator=(Station data) {
        name = data.name;
    }

    friend ostream& operator<<(ostream& os, const Station& h) {
        os << h.name;
        return os;
    }
};


template <class t >
class node {
    t data;
    node<t>* next;
    node<t>* prev;

public:
    node() :data(t()), next(nullptr), prev(nullptr) {}


    void setData(t x) {
        data = x;
    }
    void setNext(node<t>* c) {
        next = c;
    }
    void setPrev(node<t>* c) {
        prev = c;
    }
    t getData() {
        return data;
    }
    node<t>* getNext() {
        return next;
    }
    node<t>* getPrev() {
        return prev;
    }

};
template <class t>
class DoublyLinkedList {

    node<t>* head, * tail;
    int size;

public:
    DoublyLinkedList() {
        head = tail = nullptr;
        size = 0;
    }


    DoublyLinkedList(const DoublyLinkedList& l) {
        size = 0;
        head = tail = nullptr;
        node<t>* current = l.head;
        if (l.head == nullptr) {
            return;
        }

        node<t>* n = new node<t>();
        n->setData(current->getData());
        head = tail = n;
        current = current->getNext();
        size++;
        while (current != nullptr) {
            node<t>* n = new node<t>();
            tail->setNext(n);
            n->setPrev(tail);
            n->setData(current->getData());
            tail = n;
            size++;
            current = current->getNext();
        }
    }



    void insertAtEnd(t d) {
        size++;
        node<t>* n = new node<t>();
        n->setData(d);
        if (head == nullptr) {
            head = tail = n;
            return;
        }
        else {
            tail->setNext(n);
            n->setPrev(tail);
            tail = n;

        }

    }


    void insertAtStart(t x) {
        size++;
        node <t>* n = new node<t>();
        n->setData(x);
        if (head == nullptr) {
            head = tail = n;
            return;

        }
        else {
            n->setNext(head);
            head->setPrev(n);

            head = n;
        }
    }



    void displayForward() {
        if (head == nullptr) {
            cout << "The list is empty\n";
            return;
        }
        else {
            node<t>* temp = head;
            while (temp != nullptr) {
                cout << "Data = " << temp->getData() << endl;
                temp = temp->getNext();
            }
        }
    }

    void displayBackward() {
        if (head == nullptr) {
            cout << "The list is empty\n";
            return;
        }
        else {
            node<t>* temp = tail;
            while (temp != nullptr) {
                cout << "Data = " << temp->getData() << endl;
                temp = temp->getPrev();

            }

        }

    }

    int search(t data) {
        int count = 0;
        node <t>* temp = head;
        while (temp != nullptr) {
            if (data == temp->getData())
            {
                cout << "Data " << data << " is present in the list." << endl;
                cout << "This is present in the list";
                return count;
            }
            temp = temp->getNext();
            count++;
        }
        cout << "The data is not present" << endl;
        return -1;
    }



    ~DoublyLinkedList() {
        node<t>* temp = tail;
        while (temp != nullptr) {
            node<t>* prev = temp->getPrev();
            delete temp;
            temp = prev;
        }
        tail = head = nullptr;

    }




    void deleteAtPosition(int pos) {
        int count = 0;
        node<t>* temp = head;
        if (pos < 0 || pos >= size) {
            cout << "Invalid position." << endl;
            return;
        }
        if (head == nullptr) {
            cout << "The list is empty " << endl;
        }

        if (pos < 0) {
            cout << "Invalid position." << endl;
            return;
        }

        if (pos == 0) {
            head = head->getNext();
            if (head != nullptr) {
                head->setPrev(nullptr);
            }
            else {
                tail = nullptr; // list became empty
            }
            delete temp;
            size--;
            return;
        }
        while (temp != nullptr && count < pos) {
            temp = temp->getNext();
            count++;

        }
        node<t>* prevNode = temp->getPrev();
        node<t>* nextNode = temp->getNext();

        if (prevNode != nullptr) {
            prevNode->setNext(nextNode);
        }

        if (nextNode != nullptr) {
            nextNode->setPrev(prevNode);
        }
        else {
            tail = prevNode; // deleted last node
        }
        size--;
        delete temp;
    }


    void deleteAtStart() {
        if (head == nullptr) {
            cout << "The List is empty";
            return;
        }
        node<t>* temp = head;
        head = head->getNext();
        delete temp;
        size--;

        if (head != nullptr) {
            head->setPrev(nullptr);
        }
        else {

            tail = nullptr;
            head = nullptr;
        }


    }


    void deleteAtEnd() {
        node<t>* n = tail;
        if (head == nullptr) {
            cout << "The list is empty";
            return;
        }
        tail = tail->getPrev();
        delete n;
        if (tail != nullptr) {
            tail->setNext(nullptr);
        }
        else {
            head = tail = nullptr;
        }
        size--;

    }


    void insertAtAnyPosition(int pos, t a ){
        node <t>* n=new node<t>();
        n->setData(a);
        node<t>* temp = head;
        int count = 0;
        size++;
        if (head == nullptr) {
            head = tail = n;
            return;
        }

        if (pos == 0 && head != nullptr)
        {

            n->setNext(head);
            head->setPrev(n);
            n->setPrev(nullptr);
            head = n;
            return;
        }

        while (count < pos - 1 && temp != nullptr) {
            count++;
            temp = temp->getNext();
        }
        node<t>* x = temp->getNext();
        n->setPrev(temp);
        n->setNext(temp->getNext());
        temp->setNext(n);
        if (x != nullptr) {
            x->setPrev(n);
        }
        else {
            tail = n;
        }


    }
    bool isEmpty() {
        return head == nullptr;
    }
    node<t>* getTail() {
        return tail;
    }
    node<t>* gethead() {
        return head;
    }
};

class MetroRoute {
    DoublyLinkedList<Station>d;
    node<Station>* station;

public:
    MetroRoute() {
        station = nullptr;
    }

    MetroRoute(const MetroRoute& list) : d(list.d) {
        this->station = d.gethead();
    }

    void AddStation(string name, int pos) {
        d.insertAtAnyPosition(pos, name);
        this->station = d.gethead();
    }

    void remove(string name) {
        int x = d.search(name);
        if (x >= 0){
            d.deleteAtPosition(x);
            cout << "Congrats deleted\n";
        }
        this->station = d.gethead();
    }

    void forward() {
        if (station == nullptr || station->getNext() == nullptr) {
            cout << "No more stations\n";
            return;
        }
        else {
            station = station->getNext();
            cout << station->getData();
           
        }
    }
    void back() {
        if (station == nullptr || station->getPrev() == nullptr) {
            cout << "No more stations\n";
            return;
        }
        else {
            station = station->getPrev();
            cout<<station->getData();
        }

        
    }
    void display() {
        d.displayForward();
    }


};
int main() {
    MetroRoute d;
    d.AddStation("Station_1",0);
    d.AddStation("Station_2", 1);
    d.AddStation("Station_3", 2);
    d.AddStation("Station_4", 3);
    d.AddStation("Station_5", 4);

    d.forward();
    d.remove("Station_2");
    d.back();
    d.display();
}