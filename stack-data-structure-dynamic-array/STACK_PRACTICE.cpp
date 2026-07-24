// STACK_PRACTICE.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std;
template <class t>
class node {

public:
    t data;
    node<t>* next;

    node() {
        data = t();
        next = nullptr;
    }
    node(t d) {
        data = d;
        next = nullptr;
    
    }


    
};
template<class t>
class Stack {
    node<t>* head;

public:

    node<t>* getHead() {
        return head;
    }
    Stack() {
        head = nullptr;
    }


    void pop() {
        if (head == nullptr) {
            cout << "You cant pop from an empty stack";
            return;
        }
        else {
            node<t>*n = head->next;
            delete head;
            head = n;
        }
    
    }

   void  push(t d){
        node<t>* n = new node<t>(d);
        if (head == nullptr) {
            head = n;
        }
        else {
           
            n->next = head;
            head = n;
        }

    
    }

   ~Stack(){
       while (head != nullptr) {
      this->pop();
    }
   }

   void deleteStack() {
       while (head != nullptr) {
           this->pop();
       }
   }

   t peek() {
       if (head) {
           return head->data;
       }
       else {
           cout << "EMPTY STACK\n";
               return t();
       }
   }

   void undo() {
       if (head == nullptr) {
           cout << "Nothing to undo!" << endl;
           return;
       }

       cout << "Undoing action: " << head->data << endl;
       pop();
   }


   void display() {
       node<t>* temp = head;
       while (temp != nullptr) {
           cout << temp->data << " -> ";
           temp = temp->next;
       }
       cout << "NULL" << endl;
   }

   bool isEmpty() {
       return head == nullptr;
   }

   Stack(const Stack& p) {
       if (p.isEmpty()) { head = nullptr; return; }
       else {
           node<t>* head_original= p.getHead();
           node<t>* n = new node<t>(head_original->data);
           head = n;
           node<t>* end_of_new_stack = head;

           head_original= head_original->next;

           while (head_original != nullptr) {
               node<t>* newNode = new node<t>(head_original->data);
               end_of_new_stack->next = newNode;
               end_of_new_stack = newNode;
               head_original = head_original->next;
           }

       }
   }

   void operator=(const Stack& s) {
       if (s.getHead() == this->getHead()) { return; }
       if (s.getHead() == nullptr) { return; }
       while (head != nullptr) {
           this->pop();
       }
       node<t>*n=s.getHead();
       node<t>* newNODE=new node<t>(n->data);
       head = newNODE;

       node<t>* end = head;
       n = n->next;
       while (n != nullptr) {
           node<t>* temp = new node<t>(n->data);
           end->next= temp;
           end= temp;
           n=n->next;
       }

       
   }

};
#include <string>
using namespace std;

class Doc {
    string name;
    int time;

public:
    Doc() {
        name = "empty";
        time = 0;
    }

    Doc(string n, int t):name(n), time(t) {}

    void setName(string n) {
        name = n;
    }

    void setTime(int t) {
        time = t;
    }
    string getName() {
        return name;
    }

    int getTime() {
        return time;
    }
};

template <class t>
class History {
    Stack<Doc> forward;
    Stack<Doc> backward;
    Doc current;

public:
    History() {}


    void goForward() {
        if (forward.isEmpty()) {
            cout << "Cant undo if just started";
        }
        else {
            backward.push(current);
            current = forward.peek();
            forward.pop();

        }
    }
    void goBack() {
        if (backward.isEmpty()) {
            cout << "Cant undo if just started";
        }
        else {
           
            forward.push(current);
            current = backward.peek();
            backward.pop();

        }
    }

    void visit(Doc t) {
        backward.push(current);
        current = t;
        forward.deleteStack();
    }

    void clearHistory() {

        backward.deleteStack();
    }



};
int main() {
    History<Doc> browser;

    cout << "Visiting Google, then YouTube..." << endl;
    browser.visit(Doc("google.com", 10));
    browser.visit(Doc("youtube.com", 12));

    cout << "Going Back..." << endl;
    browser.goBack(); // Should take you to google.com

    cout << "Visiting GitHub..." << endl;
    browser.visit(Doc("github.com", 15));
    // Now you can't go 'Forward' to YouTube anymore!

    return 0;
}