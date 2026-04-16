#include <iostream>
using namespace std;

class Order_id_error : public exception {
public:
	const char* what() {
		return "Your inputted ID does not exist\n Error 000";
	}
};
class Quantity_error : public exception {
public:
	const char* what() {
		return "Your inputted quantity cant be handled \n Error 001";
	}
};
class Quantity_error_2 : public exception {
public:
	const char* what() {
		return "0 cant be entered \n Error 002";
	}
};
class Quantity_error_cancel : public exception {
public:
	const char* what() {
		return "Your inputted quantity cant be handled as you did not order this much \n Error 010";
	}
};


class List {
protected:
	int productID[3];
	string productName[3];
	float price[3];
	int availableQuantity[3];
public:
	List() {
		for (int i = 0; i < 3; i++)
		{
			productID[i] = i;
			cout << "Name = ";
			cin >> productName[i];
			cout << "Price = ";
			cin >> price[i];
			cout << "Quantity = ";
			cin >> availableQuantity[i];
		}
	}
	friend class Shopping;

};
class Shopping {
	int userid_selected;
	int quantity;
public:
	Shopping(int i = 0, int j = 0) : userid_selected(i), quantity(j) {}

	void Order(List& l1) {
		cout << "Input product ID = ";
		cin >> userid_selected;
		cout << "Input the quantity = ";
		cin >> quantity;
		for (int i = 0; i < 3; i++) {
			if (userid_selected == l1.productID[i]) {
				if (quantity > l1.availableQuantity[i]) {
					throw Quantity_error();
				}
				else if (quantity == 0) {
					throw Quantity_error_2()
				}
				else {
					l1.availableQuantity[i] = l1.availableQuantity[i] - quantity;
				}

			}
			else {
				throw Order_id_error();
			}

		}
	}
	void Cancel_Order(List& l1) {
		int x, y;
		cout << endl;
		cout << "Input product ID = ";
		cin >> x;
		cout << "Input the quantity = ";
		cin >> y;
		for (int i = 0; i < 3; i++) {
			if (userid_selected == x) {
				if (quantity < y) {
					throw Quantity_error_cancel();
				}

				else {
					for (int i = 0; i < 3; i++) {
						if (x == l1.productID[i]) {
							l1.availableQuantity[i] = l1.availableQuantity[i] + y;
						}
					}
				}
			}
			else {
				throw Order_id_error();
			}


		}

	}
	void display(List& l1) {
		for (int i = 0; i < 3; i++) {
			cout << l1.productID[i] << endl;
			cout << l1.productName[i] << endl;
			cout << l1.availableQuantity[i] << endl;
			cout << l1.price[i] << endl;
		}

	}
}
;

int main() {
	List l1;
	Shopping s;
	try {
		s.Order(l1);
	}
	catch (Order_id_error& e) {
		cout << e.what();
	}
	catch (Quantity_error_2& e) {
		cout << e.what();
	}
	catch (Quantity_error& e) {
		cout << e.what();
	}
	catch (Quantity_error_cancel& e) {
		cout << e.what();
	}
	try {
		s.Cancel_Order(l1);
	}
	catch (Order_id_error& e) {
		cout << e.what();
	}
	catch (Quantity_error& e) {
		cout << e.what();
	}
	catch (Quantity_error_cancel& e) {
		cout << e.what();
	}
	try {
		s.display(l1);
	}
	catch (Order_id_error& e) {
		cout << e.what();
	}
	catch (Quantity_error& e) {
		cout << e.what();
	}
	catch (Quantity_error_cancel& e) {
		cout << e.what();
	}

}