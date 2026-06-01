// linked_list.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std;


class Patient {

    string name;
    int id;
    int severity;
    static int i ;

public :
    Patient(string n,  int s) {
        name = n;
        id = i++;
        severity = s;
    }

    Patient() {
        name = "John Doe";
        id = i++;
        severity = 1;



    }

    bool compare(Patient x) {
        bool flag = false;
        if (x.name == name && x.id == id && severity == x.severity) {
            flag = true;
         }
        return flag;
    }


    void setName(string n) { name = n; };

    void setSeverity(int i) { severity = i; }

    int getSeverity() { return severity; }

    string getName() { return name; }

    int getid() { return id; }

    
};


int Patient::i = 101; 

class node {
    Patient data;
    node* next;

public:
    node() :data(Patient()), next(nullptr) {}


    void setData(Patient x) {
        data = x;
    }
    void setNext(node* c) {
        next = c;
    }
    Patient getData() {
        return data;
    }
    node* getNext() {
        return next;
    }

    void display() {
        cout << "Name = " << data.getName()<<endl;
        cout << "ID = " << data.getid() << endl;
        cout << "Severity = " << data.getSeverity()<<endl;
    }

    bool compare_data(Patient t) {
        data.compare(t);
    }
    int getDataSeverity() { return data.getSeverity(); }
};




class linkedList {
    node* head;
    int size;
public:
    linkedList() {
        head = nullptr;
        size = 0;
    }
    linkedList(const linkedList& list) {
        node* current = list.head;
        if (list.head == nullptr) {
            head = nullptr;
            size = list.size;
        }

        else {
            this->head = new node();
            node* temp = head;
            while (current != nullptr) {
                temp->setData(current->getData());
                if (current->getNext() != nullptr) {
                    node* n = new node();
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



    void insertAtEnd(Patient data) {
        size++;
        node* temp = new node();
        temp->setData(data);
        if (head == nullptr) {
            head = temp;
            return;
        }
        else {
            node* t = head;
            while (t->getNext() != nullptr) {
                t = t->getNext();
            }
            t->setNext(temp);
        }
    }
    
    void Union() {
    
    }

    void insertAtStart(Patient data) {
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
                cout << "Data = \n";
                temp->display() ;
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

    void search(Patient d) {
        bool found = false;
        if (head == nullptr) {
            cout << "The list is empty";
            return;
        }
        else {
            node * temp = head;
            while (temp != nullptr) {
                if (temp->compare_data(d)) {
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

    void insertAtAnyPosition(int x, Patient data) {
        int count = 0;
        if (x > size || x < 0) {
            return;
        }



        if (x == 0) {
            node* n = new node;
            n->setData(data);
            n->setNext(head);
            head = n;
            size++;
            return;
        }

        else if (x <= size) {
            node* n = new node;
            n->setData(data);
            node* temp = head;
            while (count < x - 1) {
                temp = temp->getNext();
                count++;
            }
            n->setNext(temp->getNext());
            temp->setNext(n);
            size++;

        }

    }

    void insertBasedOnSeverity( Patient data) {

     
        node* temp = head;
        bool check = true;

        if (head == nullptr) {
            insertAtStart(data);
        }
        while (temp != nullptr) {
            if (temp->getDataSeverity() < data.getSeverity()) {
                temp = temp->getNext();
            }
            else {
                node *n = new node();
                n->setNext(temp->getNext());
                temp->setNext(n);
                n->setData(data);
                check = false;
                return;
            }
        }
        if (check) {
            insertAtEnd(data);
        }
            
       }


    void deleteFromAnyPoint(int x) {
        int count = 0;
        if (head == nullptr || x >= size || x < 0) {
            cout << "The array is either out of range or is empty \n";
            return;
        }
        if (x == 0) {//for head
            node* temp = head->getNext();
            delete head;
            size--;
            head = temp;
        }

        else if (x <= size) {//can only delete a node if it exists
            node* temp = head;
            while (count < x - 1 && temp->getNext() != nullptr) {
                temp = temp->getNext();
                count++;
            }
            node* target = temp->getNext(); //has the one that needs to be deleted
            temp->setNext(target->getNext());
            delete target;
            target = nullptr;
            size--;
        }

    }

    void reverse() {
        node* temp = head;
        node* a, * b;
        a = b = nullptr;
        while (temp != nullptr) {

            b = temp->getNext();

            temp->setNext(a);

            a = temp;
            temp = b;
        }
        head = a;
    }

    

    void findMiddle() {
        node * temp = head;
        node* slow = head;

        if (head == nullptr) {
            cout << "The list is empty";
            return;
        }


        while (temp != nullptr && temp->getNext() != nullptr) {

            temp = temp->getNext()->getNext();
            slow = slow->getNext();

        }
        cout << "The value of the middle is = \n" ;
        temp->display();


    }


    void insertBasedOnSeverity(Patient t) {
        if (t.getSeverity() == 1) {
            insertAtStart(t);
        }
        else if (t.getSeverity()==3) {
            insertAtEnd(t);
        }
        else if (t.getSeverity() == 2) {
        
        }
    
    }



};

int main() {
    
}
