#include <iostream>
#include <fstream>
using namespace std;

class Service {
    int Vehicle_Registration_no;
    string Owner_Name;
    string Service_Type;
    float Service_Cost;
    string Date_of_Service;
public:
    Service(int i = 0, string n = "", string s = "", float c = 0, string d = "")
        :Vehicle_Registration_no(i), Owner_Name(n), Service_Type(s), Service_Cost(c), Date_of_Service(d) {
    }

    void set_number(int n) {
        Vehicle_Registration_no = n;
    }
    void set_name(string n) {
        Owner_Name = n;
    }
    void service_type(string n) {
        Service_Type = n;
    }
    void service_cost(float c) {
        Service_Cost = c;
    }
    void date(string d) {
        Date_of_Service = d;
    }

    int get_number() {
        return Vehicle_Registration_no;
    }
    string get_name() {
        return Owner_Name;
    }
    string get_service_type() {
        return Service_Type;
    }
    float get_service_cost() {
        return Service_Cost;
    }
    string get_date() {
        return Date_of_Service;
    }
};

class Record {
    Service r[5];
    int count;
public:
    Record() {
        count = 0;
    }

    void add_record() {
        if (count >= 5) {
            cout << "Record limit reached.\n";
            return;
        }

        int reg;
        string name, type, date;
        float cost;

        cout << "Enter Vehicle Registration Number: ";
        cin >> reg;

        ifstream fin("Record.txt");
        Service temp;
        int treg;
        string tname, ttype, tdate;
        float tcost;
        bool exists = false;

        while (fin >> treg >> tname >> ttype >> tcost >> tdate) {
            if (treg == reg) {
                cout << "Record with same registration number already exists.\n";
                exists = true;
                break;
            }
        }
        fin.close();

        if (exists) return;

        cout << "Enter Owner Name: ";
        cin >> name;
        cout << "Enter Service Type: ";
        cin >> type;
        cout << "Enter Service Cost: ";
        cin >> cost;
        cout << "Enter Date of Service: ";
        cin >> date;

        r[count].set_number(reg);
        r[count].set_name(name);
        r[count].service_type(type);
        r[count].service_cost(cost);
        r[count].date(date);
        count++;

        ofstream fout("Record.txt", ios::app);
        fout << reg << " " << name << " " << type << " " << cost << " " << date << endl;
        fout.close();

        cout << "Record added successfully.\n";
    }

    void view_records() {
        ifstream fin("Record.txt");
        if (!fin) {
            cout << "No record file found.\n";
            return;
        }
        int reg;
        string name, type, date;
        float cost;
        while (fin >> reg >> name >> type >> cost >> date) {
            cout << "\nRegistration No: " << reg;
            cout << "\nOwner Name: " << name;
            cout << "\nService Type: " << type;
            cout << "\nService Cost: " << cost;
            cout << "\nDate of Service: " << date << "\n";
        }
        fin.close();
    }

    void search_record() {
        int reg;
        cout << "Enter Registration Number to Search: ";
        cin >> reg;

        ifstream fin("Record.txt");
        if (!fin) {
            cout << "No record file found.\n";
            return;
        }

        int treg;
        string name, type, date;
        float cost;
        bool found = false;

        while (fin >> treg >> name >> type >> cost >> date) {
            if (treg == reg) {
                cout << "\nRecord Found:\n";
                cout << "Registration No: " << treg << endl;
                cout << "Owner Name: " << name << endl;
                cout << "Service Type: " << type << endl;
                cout << "Service Cost: " << cost << endl;
                cout << "Date of Service: " << date << endl;
                found = true;
                break;
            }
        }
        if (!found)
            cout << "Record not found.\n";

        fin.close();
    }

    void update_record() {
        int reg;
        cout << "Enter Registration Number to Update: ";
        cin >> reg;

        ifstream fin("Record.txt");
        ofstream fout("Temp.txt");

        int treg;
        string name, type, date;
        float cost;
        bool found = false;

        while (fin >> treg >> name >> type >> cost >> date) {
            if (treg == reg) {
                found = true;
                cout << "Enter new Service Type: ";
                cin >> type;
                cout << "Enter new Service Cost: ";
                cin >> cost;
            }
            fout << treg << " " << name << " " << type << " " << cost << " " << date << endl;
        }

        fin.close();
        fout.close();

        remove("Record.txt");
        rename("Temp.txt", "Record.txt");

        if (found)
            cout << "Record updated successfully.\n";
        else
            cout << "Record not found.\n";
    }

    void delete_record() {
        int reg;
        cout << "Enter Registration Number to Delete: ";
        cin >> reg;

        ifstream fin("Record.txt");
        ofstream fout("Temp.txt");

        int treg;
        string name, type, date;
        float cost;
        bool found = false;

        while (fin >> treg >> name >> type >> cost >> date) {
            if (treg == reg) {
                found = true;
                continue;
            }
            fout << treg << " " << name << " " << type << " " << cost << " " << date << endl;
        }

        fin.close();
        fout.close();

        remove("Record.txt");
        rename("Temp.txt", "Record.txt");

        if (found)
            cout << "Record deleted successfully.\n";
        else
            cout << "Record not found.\n";
    }
};

int main() {
    Record rec;
    int ch;

    while (true) {
        cout << "\n1. Add New Maintenance Record\n";
        cout << "2. View All Maintenance Records\n";
        cout << "3. Search Maintenance Record\n";
        cout << "4. Update Record\n";
        cout << "5. Delete Record\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> ch;

        if (ch == 1)
            rec.add_record();
        else if (ch == 2)
            rec.view_records();
        else if (ch == 3)
            rec.search_record();
        else if (ch == 4)
            rec.update_record();
        else if (ch == 5)
            rec.delete_record();
        else if (ch == 6)
            break;
        else
            cout << "Invalid choice.\n";
    }
}
