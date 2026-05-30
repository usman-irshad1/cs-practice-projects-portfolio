// Task1_home_task.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <list>
#include <algorithm>
using namespace std;

struct Product {
    int ProductID; string customerName; string issueType; int  price;
    static int id;
    Product() {
        ProductID = id++;
        customerName = "Hello";
        issueType = "Hi";
        price = 2;

    }


    bool operator==(const string& s) {
        return issueType == s;
    }

    
    bool operator<(const Product& other) const {
        return this->price < other.price;
    }


    bool operator==(const int& s) {
        return ProductID == s;
    }

    friend ostream& operator<<(ostream& os, const Product& s) {
        os << "\Product Details\n" << s.ProductID << "\n" << s.customerName << "\n" << s.issueType << "\n" << s.price << "\n---------------\n";
        return os;
    }
};



template <class t>
void display(t data) {
    cout << data << "\n";
}

Product increase(Product data) {
    data.price = data.price*2 ;
    return data;
}
template <class t>
class l : public list<t> {
public:

    void Display_for_each() {
        for_each(this->begin(), this->end(), display<t>);
    }

    void currentTicket() {
        typename list<t>::iterator i;
        i = this->begin();
        display(*i);
    }

    int counting(string f) {
        int i = count(this->begin(), this->end(), f);
        cout << "\n\n\t\t\t\t\tNumber of Products with issue type " << f << " is/are " << i<<endl;
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
    void insert(Product data) {
        
            this->push_back(data);
   
    }

    void price_increase() {
        transform(this->begin(), this->end(), this->begin(), increase);
        Display_for_each();
    }


    void sorting() {
        this->sort();
    }

};

int Product::id = 0;

int main() {
    l<Product> mySystem;

    Product t1;
    t1.customerName = "Cheetos";
    t1.issueType = "Food";
    t1.price = 13;

    Product t2;
    t2.customerName = "Lays";
    t2.issueType = "Food";
    t2.price = 14;

    Product t3;
    t3.customerName = "Takis";
    t3.issueType = "Food";
    t3.price = 15;

    mySystem.insert(t1);
    mySystem.insert(t2);
    mySystem.insert(t3);

    cout << " All Products ";
    mySystem.Display_for_each();
    mySystem.sorting();
    mySystem.counting("Food");

    cout << "\nSearching for ID 1";
    mySystem.searching(1);
    mySystem.price_increase();

    return 0;
}