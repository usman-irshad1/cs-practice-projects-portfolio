#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

class Service {
    int id;
    string Name;
    string Dep;
    int rating;
    string remarks;
public:
    Service(int i = 0, string n = "", string s = "", int c = 0, string d = "") {
        id = i;
        Name = n;
        Dep = s;
        rating = c;
        remarks = d;
    }

    void set_number(int n) { id = n; }
    void set_name(string n) { Name = n; }
    void service_type(string n) { Dep = n; }
    void service_cost(int c) { rating = c; }
    void date(string d) { remarks = d; }

    int get_number() { return id; }
    string get_name() { return Name; }
    string get_service_type() { return Dep; }
    int get_service_cost() { return rating; }
    string get_date() { return remarks; }
};

class Record {
    Service r[5];
    int count;
public:
    Record() {
        count = 0;
        load_data();
    }

    void load_data() {
        ifstream fin("employees.csv");
        if (!fin) return;

        string line;
        while (getline(fin, line) && count < 5) {
            stringstream ss(line);
            string id, name, dep, rating, rem;
            getline(ss, id, ',');
            getline(ss, name, ',');
            getline(ss, dep, ',');
            getline(ss, rating, ',');
            getline(ss, rem, ',');
            r[count].set_number(stoi(id));
            r[count].set_name(name);
            r[count].service_type(dep);
            r[count].service_cost(stoi(rating));
            r[count].date(rem);
            count++;
        }
        fin.close();
    }

    void save_data() {
        ofstream fout("employees.csv", ios::trunc);
        for (int i = 0; i < count; i++) {
            fout << r[i].get_number() << "," << r[i].get_name() << "," << r[i].get_service_type() << "," << r[i].get_service_cost() << "," << r[i].get_date() << endl;
        }
        fout.close();
    }

    void add_record() {
        if (count >= 5) {
            cout << "Record limit reached.\n";
            return;
        }

        int id;
        string name, dep, rem;
        int rating;

        cout << "Enter Employee ID: ";
        cin >> id;

        for (int i = 0; i < count; i++) {
            if (r[i].get_number() == id) {
                cout << "Employee ID already exists.\n";
                return;
            }
        }

        cout << "Enter Name: ";
        cin >> name;
        cout << "Enter Department: ";
        cin >> dep;
        cout << "Enter Monthly Rating (1-10): ";
        cin >> rating;
        cout << "Enter Remarks: ";
        cin >> rem;

        r[count].set_number(id);
        r[count].set_name(name);
        r[count].service_type(dep);
        r[count].service_cost(rating);
        r[count].date(rem);
        count++;

        save_data();
        cout << "Employee added successfully.\n";
    }

    void view_records() {
        if (count == 0) {
            cout << "No employee records found.\n";
            return;
        }
        for (int i = 0; i < count; i++) {
            cout << "\nEmployee ID: " << r[i].get_number();
            cout << "\nName: " << r[i].get_name();
            cout << "\nDepartment: " << r[i].get_service_type();
            cout << "\nMonthly Rating: " << r[i].get_service_cost();
            cout << "\nRemarks: " << r[i].get_date() << endl;
        }
    }

    void search_record() {
        int id;
        cout << "Enter Employee ID to search: ";
        cin >> id;

        int found = 0;
        for (int i = 0; i < count; i++) {
            if (r[i].get_number() == id) {
                cout << "\nEmployee Found:\n";
                cout << "Employee ID: " << r[i].get_number() << endl;
                cout << "Name: " << r[i].get_name() << endl;
                cout << "Department: " << r[i].get_service_type() << endl;
                cout << "Rating: " << r[i].get_service_cost() << endl;
                cout << "Remarks: " << r[i].get_date() << endl;
                found = 1;
                break;
            }
        }
        if (found == 0)
            cout << "Employee not found.\n";
    }

    void update_record() {
        int id;
        cout << "Enter Employee ID to update: ";
        cin >> id;

        int found = 0;
        for (int i = 0; i < count; i++) {
            if (r[i].get_number() == id) {
                int newRating;
                string newRemarks;
                cout << "Enter new Monthly Rating (1-10): ";
                cin >> newRating;
                cout << "Enter new Remarks: ";
                cin >> newRemarks;
                r[i].service_cost(newRating);
                r[i].date(newRemarks);
                found = 1;
                break;
            }
        }

        if (found == 1) {
            save_data();
            cout << "Record updated successfully.\n";
        }
        else {
            cout << "Employee not found.\n";
        }
    }

    void delete_record() {
        int id;
        cout << "Enter Employee ID to delete: ";
        cin >> id;

        int found = 0;
        for (int i = 0; i < count; i++) {
            if (r[i].get_number() == id) {
                for (int j = i; j < count - 1; j++) {
                    r[j] = r[j + 1];
                }
                count--;
                found = 1;
                break;
            }
        }

        if (found == 1) {
            save_data();
            cout << "Record deleted successfully.\n";
        }
        else {
            cout << "Employee not found.\n";
        }
    }

    void performance_report() {
        if (count == 0) {
            cout << "No data available.\n";
            return;
        }

        int total = 0;
        int best = r[0].get_service_cost();
        string bestName = r[0].get_name();

        for (int i = 0; i < count; i++) {
            total += r[i].get_service_cost();
            if (r[i].get_service_cost() > best) {
                best = r[i].get_service_cost();
                bestName = r[i].get_name();
            }
        }

        float avg = (float)total / count;
        cout << "\nAverage Rating: " << avg << endl;
        cout << "Best Performing Employee: " << bestName << " (Rating: " << best << ")\n";
    }
};

int main() {
    Record rec;
    int ch;

    while (1) {
        cout << "\n1. Add New Employee Record\n";
        cout << "2. View All Employees\n";
        cout << "3. Search Employee\n";
        cout << "4. Update Employee\n";
        cout << "5. Delete Employee\n";
        cout << "6. Performance Report\n";
        cout << "7. Exit\n";
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
            rec.performance_report();
        else if (ch == 7)
            break;
        else
            cout << "Invalid choice.\n";
    }
}
