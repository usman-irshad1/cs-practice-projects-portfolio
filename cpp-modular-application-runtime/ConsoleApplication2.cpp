// ConsoleApplication2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
using namespace std;

class Asset {
protected:
	string name;
public:

	Asset(string n):name(n) {}
	virtual double get_value() const = 0;
	virtual  void display() const = 0;


};
class Stock : public Asset {
protected:
	double shares, price_per_share;
public:
	Stock(string n = "", int s = 0, int p = 0) :Asset(n), shares(s), price_per_share(p) {}
	friend ostream& operator<<(ostream& o, const Stock& s1) {
		o << "\nName = ";
		o<<s1.name;
		o << "\nShares = ";
		o << s1.shares;
		o << "\nPrice per share = ";
		o << s1.price_per_share;
		return o;
	}
	friend istream& operator>>(istream& o, Stock& s1) {
		cout << "\nName = ";
		o>>s1.name;
		cout << "\nShares = ";
		o>> s1.shares;
		cout<< "\nPrice per share = ";
		o >> s1.price_per_share;
		return o;
	}
	double get_value() const override {
		return  this->price_per_share * this->shares;
		
	}
	void display() const override {
		cout << *this;
	}
};

class Real_Estate :public Asset{
protected:
	double property_value;
	double mortgage_debt;
public:
	Real_Estate(string n = "", int s = 0, int p = 0) :Asset(n), property_value(s), mortgage_debt(p) {}

	friend ostream& operator<<(ostream& o, const Real_Estate& s1) {
		o << "\nName = ";
		o << s1.name;
		o << "\nProperty value = " << s1.property_value;
		o << "\nMortgage debt = " << s1.mortgage_debt;

		return o;
	}
	void display() const override {
		cout << *this;
	}

	double get_value() const override {
		return (this->property_value - this->mortgage_debt);
	}
	friend istream& operator>>(istream& o, Real_Estate& s1) {
		cout << "\nName = ";
		o >> s1.name;
		cout << "\nProperty_value = ";
		o >> s1.property_value;
		cout << "\nMortgage debt = ";
		o >> s1.mortgage_debt;
		return o;
	}
};

class Portfolio  {
	vector <Asset*> assets;
public:
	Portfolio() {
		int i, n;
		cout << "How many assets you want to add ata the start";
		cin >> n;
		for (int x = 0; x < n; x++) {
			cout << "If you want to add stock press 0 for real estate press 1";
			cin >> i;
				if (i == 0) {
					Stock * a = new Stock;
					cin >> *a;
					assets.push_back(a);
				}

				else if (i == 1) {
					Real_Estate *a= new Real_Estate;
					cin>>*a;
					assets.push_back(a);
				}
		}
	}

	void add() {
		int i;
		cout << "If you want to add stock press 0 for real estate press 1";
		cin >> i;
		if (i == 0) {
			Stock* a = new Stock;
			cin >> *a;
			assets.push_back(a);
		}

		else if (i == 1) {
			Real_Estate* a = new Real_Estate;
			cin >> *a;
			assets.push_back(a);
		}
	}
	double get_value() const  {
		double sum = 0;
		for (int i = 0; i < assets.size(); i++) {
			sum = sum + assets[i]->get_value();
		}
		return sum;
	}
	 void display() const {
		double sum = 0;
		for (int i = 0; i < assets.size(); i++) {
			assets[i]->display();
			cout<<endl;
		}
	}

	~Portfolio() {
		for (int i = 0; i < assets.size(); i++) {
			delete assets[i];
		}
	}
};