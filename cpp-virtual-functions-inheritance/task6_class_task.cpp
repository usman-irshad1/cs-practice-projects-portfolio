
// task6_class_task.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include<C:\Users\usman\source\repos\HashTable.h>


class System {
    HashTable<Data, 101> map;
public:
    System() {}
    void SignUp(string user, string pass) {
        Data d;
        d.username = user;
        d.password = pass;
        map.insert(d);
        cout << "User " << user << " registered successfully.\n";
    }
    void login(string name, string pass) {
        Data temp;
        temp.username = name;
        temp.password = pass;
        bool result= map.search(temp);
        if (result) {
            cout << "Authentication successful\n";
        }
        else {
            cout << "Authentication failure\n";
        }
    
    }

};


int main() {
    System mySystem;
    int choice;
    string user, pass;

    cout << "\t\t\t\tWelcome to the Secure Login System " << endl;

    while (true) {
        cout << "\n1. Sign Up\n2. Login\n3. Exit\nEnter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter username\t";
            cin >> user;
            cout << "Enter password\t";
            cin >> pass;
            mySystem.SignUp(user, pass);
            break;

        case 2:
            cout << "Login\t" << endl;
            cout << "Username\t";
            cin >> user;
            cout << "Password\t";
            cin >> pass;
            mySystem.login(user, pass);
            break;

        case 3:
            cout << "Exiting system" << endl;
            return 0;

        default:
            cout << "Invalid choice. Try again." << endl;
        }
    }

    return 0;
}