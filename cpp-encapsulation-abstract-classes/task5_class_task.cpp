// task5_class_task.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std;


int HashingFunction(string x, int size) {
    int s[] = { 3,5,7,11,13,17,19,23,47,3,7,11,13,17,97 };
    long long res = 0;
    for (int i = 0; i < x.size(); i++) {
        if (i < 15) {
            res += int(x[i]) * s[i];
        }
        else {
            res += int(x[i]) * s[6];
        }
    }
    res = res % size;
    return res;
}


template <class t>
class Hnode {
public:
    t data;
    Hnode<t>* next;

    Hnode() {
        data = t();
        next = nullptr;
    }
};


template <class t, int size>
class HashTable {
    Hnode<t>* array[size];

public:
    HashTable() {
        for (int i = 0; i < size; i++) {
            array[i] = nullptr;
        }
    }
    void insert(t x) {
        int index = HashingFunction(x, size);
        Hnode<t>* NewNode = new Hnode<t>();
        NewNode->data = x;
        NewNode->next = array[index];
        array[index] = NewNode;
    
    }

    void search(t d) {
        int index = HashingFunction(d, size);

        if (array[index]==nullptr) {
            cout << "Does not exist\n";
            return;
        }
        else {
            Hnode<t>* temp = array[index];
            while (temp != nullptr) {
                if (temp->data == d) {
                    cout << "Found \n";
                    return;
                }
                temp=temp->next;
            }
            cout << "Does not exist\n";
        }
    }


    void deleteFuntion(t d) {
        int index = HashingFunction(d, size);
        if (array[index] == nullptr) {
            cout << "Does not exist\n";
            return;
        }
        else {
            Hnode<t>* temp = array[index];
            Hnode<t>* parent = nullptr;
            while (temp != nullptr) {
                if (temp->data == d) {
                    if (parent == nullptr) {
                        array[index] = temp->next;
                    }
                    else {
                        Hnode<t>* abc = temp->next;
                        parent->next = abc;
                    }
                    cout << "Deleted\n";
                    delete temp;
                    return;
                }
                parent = temp;
                temp = temp->next;
            }
            cout << "Does not exist\n";
        }
    
    }

    void display() {
        cout << "\nHash Table Contents" << endl;
        for (int i = 0; i < size; i++) {
            cout << "Index " << i << ": ";
            Hnode<t>* temp = array[i];
            if (temp == nullptr) {
                cout << "EMPTY";
            }
            else {
                while (temp != nullptr) {
                    cout <<temp->data << " \n\t ";
                    temp = temp->next;
                }
            }
            cout << endl;
        }
    }
   
};




int main() {
    HashTable<string, 7> myTable;
    myTable.insert("Here");
    myTable.insert("i");
    myTable.insert("am");
    myTable.insert("this");
    myTable.insert("is");
    myTable.insert("me");
    myTable.display();
    myTable.search("Here");       
    myTable.search("h"); 
    myTable.deleteFuntion("i");
    myTable.deleteFuntion("me");
    myTable.display();
    return 0;
}