// Lab_11_practice.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include<list>
#include<stack>
using namespace std;

struct ticket {

    int ticketID; string customerName; int issueType; int priorityLevel;

    friend ostream&  operator<<(ostream& o, const ticket& t) {
        o <<"displaying\n"<< t.ticketID << "\n" << t.customerName << "\n" << t.issueType << "\n" << t.priorityLevel << "\n";
        return o;
    }

};


class Manager {
    list<ticket> database;

public:
    void insert() {
        ticket temp;
        cout << "Input id = ";
        cin >> temp.ticketID;
        cout << "Input name = ";
        cin >> temp.customerName;
        cout << "Input type = ";
        cin >> temp.issueType;
        cout << "Input priotity = ";
        cin >> temp.priorityLevel;

        if (temp.priorityLevel == 2) {
            database.push_front(temp);
        }
        else {
            database.push_back(temp);
        }
        cout << "Ticket has been pushed\n";
        //cout << temp;
    }

    void display(){
        for (typename list<ticket>::iterator it = database.begin(); it != database.end(); it++) {
            cout << *it;
        }
    }

    void searchbypriority(int p) {
        int c=0;
        for (typename list<ticket>::iterator it = database.begin(); it != database.end(); it++) {
            if (it->priorityLevel == p) {
                c++;
            }
        }
        cout << "for prioirity " << p << " the count is " << c << endl;
    }


    void treatment() {
        cout << database.front();
        database.pop_front();

    }

};

void balancing(string expression) {
    stack<char> holder;

    for (int i = 0; i < expression.size(); i++) {
        if (expression[i] == '(' || expression[i] == '{' || expression[i] == '[') {
            holder.push(expression[i]);
        }
        else {
            if (holder.empty()) {
                cout << "Not balanced \n";
                return;
            }
            if (expression[i] == ')') {
                if (holder.top() == '(') {
                    holder.pop();
                }
                else {
                    cout << "Not balanced";
                    return;
                }
            }
            else if (expression[i] == '}') {
                if (holder.top() == '{') {
                    holder.pop();
                }
                else {
                    cout << "Not balanced";
                    return;
                }
            }
            else if (expression[i] == ']') {
                if (holder.top() == '[') {
                    holder.pop();
                }
                else {
                    cout << "Not balanced";
                    return;
                }
            }
        }
    }
    if (holder.size() == 0) {
        cout << "balanced";
    }
}

int main()
{
    Manager oracle;
    oracle.insert();
    oracle.insert();
    oracle.display();
    oracle.searchbypriority(1);
    oracle.treatment();
    balancing("()");
}

