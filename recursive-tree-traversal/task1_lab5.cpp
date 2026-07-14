// task1_lab5.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std;

class book {
    string name;
    int ISBN;
    int price;
public:
    book(string n = "", int i = 0, int p = 0) :name(n),ISBN(i),price(p){}   

    void set_name() {
        cin >> name;
    }
    void set_ISBN(){
        cin >> ISBN;
    }

    void set_price(){
        cin >> price;
    }
    string get_name() {
        return name;
    }

    int get_ISBN() {
        return ISBN;
    }

    int get_price() {
        return price;
    }
};


class author {
    string name;
    string nationality;
    int year;
    public:
    author(string n = "", string i = "", int p = 0) :name(n), nationality(i), year(p) {}
    void set_name() {
        cin >> name;
    }
    void set_nation() {
        cin >> nationality;
    }

    void set_year() {
        cin >> year;
    }
    string get_name() {
        return name;
    }

    string get_nation() {
        return nationality;
    }

    int get_year() {
        return year;
    }

};
class Lib {
    book* b;
    author* a;
public:
    Lib(book * f , author* g) {
        b = f;
        a = g;
    }
    Lib() {
        b = new book;
        a = new author;
    }

    void input() {
        b->set_name();
        b->set_ISBN();
        b->set_price();
        a->set_name();
        a->set_nation();
        a->set_year();
    }

    void output() {
        cout << b->get_name();
        cout << endl;
        cout << b->get_ISBN();
        cout << endl;
        cout << b->get_price();
        cout << endl;
        cout << a->get_name();
        cout << endl;
        cout << a->get_nation();
        cout << endl;
        cout << a->get_year();
        cout << endl;
    }

    void output_book() {
        cout << b->get_name();
        cout << endl;
        cout << b->get_ISBN();
        cout << endl;
        cout << b->get_price();
        cout << endl;
    }
    void delete_book(){
        delete b;
}

    void delete_author() {
        delete a;
    }
    ~Lib() {
      
    }
};




int main()
{
    
    book* b1= new book;
    book *b2 =new book;
    author *a1= new author;
    cout << "Name = ";
    b1->set_name();
    cout << "ISBN = ";
    b1->set_ISBN();
    cout << "Price = ";
    b1->set_price();
    cout << "Name = ";
    b2->set_name();
    cout << "ISBN = ";
    b2->set_ISBN();
    cout << "Price = ";
    b2->set_price();
    cout << "Name of author = ";
    a1->set_name();
    cout << "Set nationality= ";
    a1->set_nation();
    cout << "Set year = ";
    a1->set_year();
    

    Lib l1(b1,a1);
    Lib l2(b2, a1);

    l1.output();
    l2.output();
    cout<< a1->get_name();
    cout << endl;
    cout<<a1->get_nation();
    cout << endl;
    cout<<a1->get_year();
    cout << endl;
    delete b1;
    delete b2;
    delete a1;   


}

