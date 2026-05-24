// doublylinkedlisst.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std;
template <class t >
class node {
    t data;
    node<t>* next;
    node<t>* prev;

public:
    node() :data(t()), next(nullptr),prev(nullptr) {}


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
            cout << "The list is empty";
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
            cout << "The list is empty";
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

    bool search(t data) {
        node <t>* temp = head;
        while (temp != nullptr) {
            if (data == temp->getData())
            {
                cout << "Data " << data << " is present in the list." << endl;
                cout << "This is present in the list";
                return true;
            }
            temp = temp->getNext();
        }
        cout << "The data is not present" << endl;
        return false;
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


    //~DoublyLinkedList(){
    //    node<t>* temp = head;
    //    while (temp != nullptr) {
    //        node<t>* node = temp->getNext();
    //        delete temp;
    //        temp = node;
    //    }
    //    head = tail = nullptr;
    //}



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
        while (temp != nullptr && count<pos){
            temp=temp->getNext();
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
        tail=tail->getPrev();
        delete n;
        if (tail != nullptr) {
            tail->setNext(nullptr);
        }
        else {
            head = tail = nullptr;
        }
        size--;

    }


    void insertAtAnyPosition(int pos,node <t>*n) {
        node<t> *temp = head;
        int count = 0;
        size++;
        if (head == nullptr) {
            head = tail = n;
            return;
        }

        if (pos==0 && head!=nullptr)
        {
            
            n->setNext(head);
            head->setPrev(n);
            n->setPrev(nullptr);
            head = n;
            return;
        }

        while (count<pos-1 && temp!=nullptr) {
            count++;
            temp = temp->getNext();
        }
        node<t>* x = temp->getNext();
        n->setPrev(temp);
        n->setNext(temp->getNext());
        temp->setNext(n);
        if(x != nullptr) {
            x->setPrev(n);
        }
        else {
            tail = n; 
        }
        
        
    }
    bool isEmpty() {
        return head == nullptr;
    }

    DoublyLinkedList Intersection(const  DoublyLinkedList& d1) {
        DoublyLinkedList <t>Intersect;
        node<t>* temp = d1.head;
        node<t> *temp1 = head;
        if (temp1 == nullptr || temp == nullptr) {
            cout << "No insteresction";
            return Intersect;
        }

        while (temp != nullptr) {
            while (temp1 != nullptr) {
                if (temp1->getData() == temp->getData()) {
                    Intersect.insertAtStart(temp1->getData());
                    break;
                }
                temp1 = temp1->getNext();
                
            }
            temp1 = head;
            temp = temp->getNext();
        }

        return Intersect;
    }
};
int main() {
   
    DoublyLinkedList<int> myList;

   
    DoublyLinkedList<int> copyList = myList;


    cout << "Is list empty? " << (myList.isEmpty() ? "Yes" : "No") << endl;

    for (int i = 1; i <= 5; i++) {
        myList.insertAtEnd(i);
    }

   
    cout << "Is list empty now? " << (myList.isEmpty() ? "Yes" : "No") << endl;

    
    cout << "Current List: " << endl;
    myList.displayForward();

 
    myList.deleteAtStart();

 
    cout << "After deleting from start: " << endl;
    myList.displayForward();

   
    myList.insertAtStart(6);

  
    cout << "After inserting 6 at start: " << endl;
    myList.displayForward();

   
    myList.insertAtEnd(9);

   
    cout << "After inserting 9 at end: " << endl;
    myList.displayForward();

   
    myList.deleteAtEnd();


    cout << "After deleting from end: " << endl;
    myList.displayForward();

   
    myList.deleteAtPosition(3);

  
    cout << "After deleting position 3: " << endl;
    myList.displayForward();

 
    node<int>* newNode = new node<int>();
    newNode->setData(7);
    myList.insertAtAnyPosition(4, newNode);


    cout << "After inserting 7 at position 4: " << endl;
    myList.displayForward();

  
    myList.deleteAtStart();

  
    cout << "After deleting from start: " << endl;
    myList.displayForward();

  
    myList.deleteAtPosition(2);

    cout << "After deleting position 2: " << endl;
    myList.displayForward();

    myList.deleteAtStart();
    myList.deleteAtStart();
    myList.deleteAtStart();

    cout << "Final traversal: " << endl;
    myList.displayForward();

    return 0;
}