// Task1_home_task.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <list>
#include <algorithm>
using namespace std;

struct Ticket{
    int ticketID; string customerName; string issueType; double  priority;
    static int id;
    Ticket() {
        ticketID = id++;
        customerName = "Hello";
        issueType = "Hi";
        priority = 2;

    }


    bool operator==(const string & s) {
        return issueType == s;
    }
   


    bool operator==(const int& s) {
        return ticketID == s;
    }

    friend ostream& operator<<(ostream& os, const Ticket & s) {
        os <<"\nTicket Details\n"<< s.ticketID << "\n" << s.customerName << "\n" << s.issueType << "\n" << s.priority << "\n---------------\n";
        return os;
    }
};


template <class t>
void display(t data) {
    cout << data << "\n";
}
template <class t>
class l : public list<t> {
public:  

    void Display_for_each() {
        for_each(this->begin(), this->end(), display<t>);
    }

    void currentTicket() {
        typename list<t>::iterator i;
        i=this->begin();
        display(*i);
    }

    int counting(string f) {
      int i=  count(this->begin(), this->end(), f);
      cout << "\nNumber of Tickets with issue type " << f << " is/are " << i;
      return i;
    }

    void searching(int id) {
        typename list<t> ::iterator i = find(this->begin(), this->end(), id);
        if (i != this->end()) {
            display(*i);
        }
        else {
            cout << "Not Found\n";
        }
    }
    void insert(Ticket data) {
        if (data.priority == 1) {
            this->push_back(data);
        }
        else if (data.priority == 2) {
            this->push_front(data);
        }
        else {
            cout << "not catered";
        }
    
    }

    void working() {
        if (!this->empty()) {
            this->pop_front();
            cout << "Ticket processed\n";
        }
        else {
            cout << "No tickets to work on\n";
        }
    }
};

int Ticket::id = 0;

int main() {
    l<Ticket> mySystem;

    Ticket t1;
    t1.customerName = "Alice";
    t1.issueType = "Network";
    t1.priority = 1;

    Ticket t2;
    t2.customerName = "Bob";
    t2.issueType = "Hardware";
    t2.priority = 2;

    Ticket t3;
    t3.customerName = "Charlie";
    t3.issueType = "Network";
    t3.priority = 1;

    mySystem.insert(t1);
    mySystem.insert(t2);
    mySystem.insert(t3);

    cout << " All Pending Tickets ";
    mySystem.Display_for_each();

    cout << "\nCurrent Ticket";
    mySystem.currentTicket();

    mySystem.counting("Network");

    cout << "\nSearching for ID 1";
    mySystem.searching(1);

    mySystem.working();

    return 0;
}