// task2_lab4.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
using namespace std;

class Vehicle {
protected:
    string brand;
    float rental_rate=0;
public:

    Vehicle (string b = "Aston Martin", float r = 7) :brand(b){
        if (r > 0) {
            rental_rate = (r);
        }
    }

    Vehicle(const Vehicle& v1) {
        brand = v1.brand;
        rental_rate = v1.rental_rate;
    }

    void Set(string b = "Aston Martin", float r = 7){
        brand = b;
        if (r > 0) {
            rental_rate = r;
        }
    }
    float Get_rate () const {
        return rental_rate;
    }

    string Get_brand() const{
        return brand;
    }
    friend ostream& operator<<(ostream& o, const Vehicle& v1) {
        o << "Brand = " << v1.brand << "\nRate = " << v1.rental_rate;
        return o;
    }
    friend istream& operator>>(istream& i, Vehicle& v1) {
        cout << "Brand = ";
        i >> v1.brand;
        cout << "\nRate = ";
        i>> v1.rental_rate;
        return i;
    }
    virtual float bill()=0;
};

class Car : public Vehicle {
public:
    Car(string b="aston", float i=0) {
        brand = b;
        if (i > 0) {
            rental_rate = i;
        }
    }
    float bill() override {
        float bill_info;
        int d;
        cout << "Enter the number of days you rented ";
        cin >> d;
        if (d > 0) {
            bill_info = (d * rental_rate);
        }
        return bill_info;
    }

 };

class Bike : public Vehicle {
public:
    Bike(string b="Aston", float i=25) :Vehicle(b, i) {}
    float bill() override {
        float bill_info;
        int d;
        cout << "Enter the number of hours you rented ";
        cin >> d;
        if (d > 0) {
            bill_info = (d * rental_rate);
        }
        return bill_info;
    }

};

class Truck : public Vehicle {
public:
    Truck(string b="", float i = 0) :Vehicle(b, i) {}

    float bill() override {
        float bill_info;
        int d;
        cout << "Enter the number of kilometers you used ";
        cin >> d;
        bill_info = (d * rental_rate - d * 10);
        return bill_info;
    }

};



int main()
{
    Vehicle* transporter[4];

    transporter[0] = new Car;
    cin >> *transporter[0];

    transporter[1] = new Bike;
    cin >> *transporter[1];

    transporter[2] = new Truck;
    cin >> *transporter[2];

    for (int i = 0; i < 3; i++) {
        cout << *transporter[i];
        cout << endl;
        cout<<transporter[i]->bill();
    }

    delete transporter[0];
    delete transporter[1];
    delete transporter[2];

    

    
      

}

