// doublylinkedlisst.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
using namespace std;
class History {
    string name;
public :
    History(string n="Empty") {
        name = n;
    }

    History(int n) {

        name = to_string(n);
    }

    void setName(string n) { name = n; }
    string getName() { return name; }

    bool operator==(History q) {
        if (name == q.name) {
            return true;
        }
        else {
            return false;
        }
    }

    friend ostream& operator<<(ostream& os, const History& h) {
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

    DoublyLinkedList<t> Union(const DoublyLinkedList<t>& other) {
        DoublyLinkedList<t> result;
        node<t>* temp = head;

      
        while (temp != nullptr) {
            result.insertAtEnd(temp->getData());
            temp = temp->getNext();
        }

        
        node<t>* tempOther = other.head;
        while (tempOther != nullptr) {
            bool exists = false;
            node<t>* check = result.head;

            while (check != nullptr) {
                if (check->getData() == tempOther->getData()) {
                    exists = true;
                    break;
                }
                check = check->getNext();
            }

            if (!exists) {
                result.insertAtEnd(tempOther->getData());
            }
            tempOther = tempOther->getNext();
        }
        return result;
    }

    DoublyLinkedList<t> Intersection(const DoublyLinkedList<t>& other) {
       node<t>* temp= other.head;
       
       DoublyLinkedList<t> list;

       if (temp == nullptr || head == nullptr) {

           cout << "there is no intersection";
       }
       else {
           while (temp != nullptr) {
               node<t>* temp1 = head;
               while (temp1 != nullptr) {
                   if (temp1->getData() == temp->getData()) {
                       if (!list.search(temp1->getData())) {
                           list.insertAtEnd(temp1->getData());
                       }

                       break;
               }
                   temp1=temp1->getNext();
               }
               temp = temp->getNext();
           }
           
       }
       return list;
    
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


    void insertAtAnyPosition(int pos, node <t>* n) {
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
};

    class BrowserHistory{
    DoublyLinkedList<History>d;
    node<History>* page;

    public:
        BrowserHistory() {
            page = nullptr;
        }

        BrowserHistory(const BrowserHistory& list) : d(list.d) {
            this->page = d.getTail();
        }

        void visitPage(string name) {
            d.insertAtEnd(name);
            page = d.getTail();

        }

        void back() {
            if (page == nullptr || d.getTail() == nullptr|| page->getPrev()==nullptr) {
                cout << "The list is empty\n";
            }
            else { page = page->getPrev();
            cout << page->getData() << endl;
            }
        
        }

        void forward() {
            if (page == nullptr || d.getTail() == nullptr || page->getNext() == nullptr) {
                cout << "No more pages .\n";
            }
            else {
                page = page->getNext();
                cout << page->getData()<<endl;
            }
        }

        void display() {
            d.displayBackward();
        }
     
    };
int main() {
    BrowserHistory b;
    b.display();
    b.visitPage("google.com");
    b.visitPage("bing.com");
    b.visitPage("yahoo.com");
    b.visitPage("netflix.com");
    b.display();
    b.back();
    b.display();
    b.display();
}