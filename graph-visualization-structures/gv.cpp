// linked_list.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std;


class Patient {

    string name;
    int id;
    int severity;
    static int i;

public:
    Patient(string n, int s) {
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

template <class t >
class node {
    t data;
    node<t>* next;

public:
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

    void display() {
        cout << "Name = " << data.getName() << endl;
        cout << "ID = " << data.getid() << endl;
        cout << "Severity = " << data.getSeverity() << endl;
    }

    bool compare_data(Patient t) {
        return data.compare(t);
    }
    int getDataSeverity() { return data.getSeverity(); }

};
template <class t>
class linkedList {
    node<t>* head;
    int size;
public:
    linkedList() {
        head = nullptr;
        size = 0;
    }
    //linkedList(const linkedList<t>& list) {
    //    node<t>* current = list.head;
    //    if (list.head == nullptr) {
    //        head = nullptr;
    //        size = list.size;
    //    }

    //    else {
    //        this->head = new node<t>();
    //        node<t>* temp = head;
    //        while (current != nullptr) {
    //            temp->setData(current->getData());
    //            if (current->getNext() != nullptr) {
    //                node<t>* n = new node<t>();
    //                temp->setNext(n);
    //                temp = n;
    //            }
    //            else {
    //                temp->setNext(nullptr);
    //            }
    //            current = current->getNext();
    //        }

    //        size = list.size;
    //    }
    //}


    linkedList(const linkedList<t>& l) {
        node <t>* current = l.head;
        if (current == nullptr) {
            head = nullptr;
            size = 0;
        }
        else {
            head = new node<t>();
            node<t>* temp = head;
            while (current != nullptr) {
                
                if (current->getNext()!=nullptr) {
                    temp->setData(current->getData());
                    node<t>* n = new node<t>();
                    temp->setNext(n);

                    temp = n;
                   
                }
                else 
                {
                    temp->setData(current->getData());
                    temp->setNext(nullptr);
                    
                
                }
                current = current->getNext();
            }
           
            
        
        }
    
    }


    //linkedList(const linkedList<t>& l) {
    //    head = nullptr;
    //    size = 0;

    // node<t>*current =l.head;

    // while (current!= nullptr) {
    //     insertAtEnd(current->getData());
    //     current = current->getNext();
    //}
    //}



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
            cout << "The hospital queue is empty.\n";
        }
        else {
            while (temp != nullptr) {
                temp->display();
                cout << "--------------------" << endl;
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

    void insertStable(Patient data) {


        node<t>* temp = head;


        if (head == nullptr) {
            insertAtStart(data);
            return;
        }
        while (temp->getNext() != nullptr && temp->getNext()->getData().getSeverity() <= data.getSeverity()) {
            temp = temp->getNext();
        }

        node<t>* n = new node<t>();
        n->setNext(temp->getNext());
        temp->setNext(n);
        n->setData(data);
        size++;
        return;

    }

       
       

    

    void insertBasedOnSeverity(Patient t) {
        if (t.getSeverity() == 1) {
            insertAtStart(t);
        }
        else if (t.getSeverity() == 3) {
            insertAtEnd(t);
        }
        else if (t.getSeverity() == 2) {
            insertStable(t);
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
        cout << "The value of the middle is ";
        slow->display();

    }




    void removal() {
        while (head != nullptr) {
            deleteFromStart();
        }
    }

    linkedList<t> backup() {
        return linkedList<t>(*this);

    }

    void search(int x) {
        node<t> *temp = head;
        if (head == nullptr) {
            cout << "Empty list";
            return;
        }
        while (temp!=nullptr){
            if (x== temp->getData().getid()) {
                temp->display();
                
            }
            temp = temp->getNext();
        }
    }
    

};

int main() {
    linkedList <Patient> hospital;
    hospital.display();


    cout << "Add critical patient:\n";
    Patient p2("Saba", 1); 
    hospital.insertBasedOnSeverity(p2);
    hospital.display();
    cout << endl;

  
    cout << "Add stable patient:\n";
    Patient p3("Ahmed", 3);
    hospital.insertBasedOnSeverity(p3);
    hospital.display();
    cout << endl;

    
    cout << "Add serious patient:\n";
    Patient p4("Ayesha", 2); 
    hospital.insertBasedOnSeverity(p4);
    hospital.display();
    cout << endl;

    
    cout << "Add another critical patient:\n";
    Patient p5("Hina", 1);
    hospital.insertBasedOnSeverity(p5);
    hospital.display();
    cout << endl;

    
    cout << "Add another stable patient:\n";
    Patient p6("Bilal", 3);
    hospital.insertBasedOnSeverity(p6);
    hospital.display();
    cout << endl;

    
    cout << "Treat next patient (remove from start):\n";
    hospital.deleteFromStart();
    hospital.display();
    cout << endl;

    cout << "Remove patient with ID = 104:\n";
    hospital.deleteFromAnyPoint(2); 
    hospital.display();
    cout << endl;

    cout << "Remove last patient:\n";
    hospital.deleteFromEnd();
    hospital.display();
    cout << endl;

    
    cout << "Attempt to remove non-existent patient (ID = 999):\n";
    hospital.search(999);
    cout << endl;

  
    cout << "Search existing patient (ID = 102):\n";
    hospital.search(102);
    cout << endl;


    

    cout << "Create backup copy at shift end:\n";
    linkedList<Patient> backupList = hospital.backup();
    cout << "Backup created.\n\n";

    cout << "Modify original (remove patient) and display both:\n";
    hospital.deleteFromStart();
    cout << "Original list:\n";
    hospital.display();
    cout << "Backup list:\n";
    backupList.display();
    cout << endl;

    
    cout << "Modify backup (add patient) and display both:\n";
    Patient p7("Zara", 2);
    backupList.insertBasedOnSeverity(p7);
    cout << "Original list:\n";
    hospital.display();
    cout << "Backup list:\n";
    backupList.display();
    cout << endl;

    cout << "Discharge all remaining patients:\n";
    hospital.removal();
    hospital.display();
    cout << endl;

    cout << "Display empty list:\n";
    hospital.display();
    cout << endl;

    
 
    return 0;
}
