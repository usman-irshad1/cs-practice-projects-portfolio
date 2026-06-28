// practice_lab_mid.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class p_error :public exception {
public:
    const char* what() {
       return "The input entered is invalid";
    }
};

///////////////////////////////////////////////////////////////////
class Person {
protected:
    static int people_counter;
    int CNIC;
    string name;

public:
    Person(string n = "John Doe") :name(n), CNIC(people_counter++) {}

    
};
///////////////////////////////////////////////////////////////////

class Customer:public Person {
    int card_number;
    float balance;
    static int no;
public:
    Customer(string n="John",float b=10):Person(n),card_number(no++){
        if (b  > 0 ) {
            balance = b;
    }
        else {
            throw p_error();
        }
    }

    void set_b() {
        float b;
        cin >> b;
        if (b > 0) {
            balance = b;
        }
        else {
            throw p_error();
        }
    }

    void subtract (float a) {
        balance = balance - a;
    }

    void set_n() {
        cin >> name;
    }
    string get_name() {
        return name;
    }
    float get_b() {
        return balance;
    }
    int get_id() {
        return CNIC;
    }
    int get_card() {
        return card_number;
    }


};
///////////////////////////////////////////////////////////////////
class item {
    static int count;
    int id;
    string name;
    float price;
public:
    item(float p, string n) :name(n),price(p),id(++count){}
    item() :name(""), price(0), id(0) {}
    static int get_count()  {
        return count;
    }
    float get_p() {
        return price;
    }
    void item_set(){
        string n = "";
        float p = 0;
        cout << "Enter the name of the item = ";
        cin >> n;
        cout << "Enter the price of the item = ";
        cin >> p;
        id = count++;

        if (p > 0) {
            name = n;
            price = p;
        }
        else {
            throw p_error();
        }
    }
    string loading() const {
        
        ofstream fout("items.txt",ios::app);
        if (!fout) {

            return  "Error 101";
        }
        else {
            fout << id << " " << name << " " << price << endl;
            fout.close();
            return "Saved";
        }
    }

    static void read(item items_array[]) {
        item temp;
        ifstream fin("items.txt");
        for (int i = 0; i < 2; i++) {
            if (!fin) {
                break;
            }
            if (!(fin >> items_array[i].id >> items_array[i].name >> items_array[i].price)) {
                break; // Stop if we can't read more items
            }
        }
        fin.close();
    
    }
    friend ostream& operator<< (ostream& o, const item& i) {
        o << "Name of item = " << i.name << endl << "Price of item = " << i.price << endl<<"Id of Item = "<<i.id<<endl;
        return o;
    }
    void display() {
        cout << *this;
    }
};

///////////////////////////////////////////////////////////////////

class Shopping {
   
    item* list;
    Customer c1;
public:
    Shopping(item l1[], Customer c) :c1(c) {
        list = new item[item::get_count()];
        for (int i = 0; i < item::get_count(); i++) {
            list[i] = l1[i];
        }
    }

    ~Shopping() {
        delete[] list;
    }

    void buy() {
        int i;
        for (int i = 0; i < 2; i++) {
            list[i].display();
        }
        cout << "Enter the id of the item ";
        cin >> i;
        i--;
        if (i > 2 || i < 0) {
            throw p_error();
        }
        else {
            if (c1.get_b() >= list[i].get_p()) {
                c1.subtract(list[i].get_p());
            }
            else {
                cout << "Your input is incorrect";
            }
        }
    }
    };

int item::count = 0;
int Person::people_counter = 0;
int Customer::no = 0;


int main()
{
    try {
        const int abc = 2;
        
        item loaded[abc];
        
        item::read(loaded);

        Customer c;
        c.set_n();
        c.set_b();

       Shopping s1 (loaded, c);
       s1.buy();


       for (int i = 0; i < abc; i++) {
           loaded[i].loading();
       }
    }
    catch (p_error& p) {
        cout<<p.what();
    }
    
}