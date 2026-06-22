// task1_lab_4.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std;


class Employee {
protected:
    string name;
    static int id;
    int employee_id;
    float base_salary=0;
public:
    Employee(string n = "John Doe", float b_s = 1000) :name(n), employee_id(++id) {
        if (b_s >= 0) {
            base_salary = b_s;
    };

    void set(string n = "John Doe", float b_s = 1000) {
        name=(n);
        if (b_s >= 0) {
            base_salary = (b_s);
            }
        }
    }

    Employee(const Employee& e1) {
        name = e1.name;
        base_salary = e1.base_salary;
        employee_id = ++id;
    }

    static int id_getter() {
        cout << "The number of employees in the company are = ";
        return id;
    }

    friend ostream& operator<<(ostream& o, const Employee& e1) {
        o << "\n\nName = " << e1.name << "\nBase salary = " << e1.base_salary << "\nEmployee ID = " << e1.employee_id << endl;
        return o;
    }
    friend istream& operator>>(istream& i, Employee& e1) {
        float x;
        cout << "\n\nEnter your name = ";
        i >> e1.name;
        cout<< "Enter your Base salary = ";
        i >> x;
        if (x >= 0) {
            e1.base_salary = x;
        }
        return i;
    }
    virtual float Salary()  {
        return base_salary;
    }

};

class Regular : public Employee{
public:
    Regular(string n = "John Doe", float b_s = 1000) :Employee(n, b_s) {
        if (b_s < 0) {
            base_salary = 0;
        }
    }
    float Salary() override {
        return base_salary;
    }

};

class Manager : public Employee {
public:
    Manager(string n = "John Doe", float b_s = 1000) :Employee(n, b_s) {
        if (b_s < 0) {
            base_salary = 0;
        }
    }
    float Salary() override{
        base_salary = base_salary * 0.25 + base_salary;
        return base_salary;//this would increase the base salary with a bonus of 25 percent.
    }

};


int Employee::id=0;

int main()
{
    cout << Employee::id_getter();//acessing the static funtion
    Regular r1("Usman", 100);//this would first call the employee class constructor and then the regular constructor
    r1.set("Usman", 1000);//this will call the set function defined in employee function
    cout << r1;//this will call the operator overloaded function
    Manager m1;
    cin >> m1;
    cout << m1.Salary();
    cout << m1;
}