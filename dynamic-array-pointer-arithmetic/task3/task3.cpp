


#include <iostream>
using namespace std;


class Cart {
	int* i;
	string* s;
	int size;
	public:
	Cart( int l = 0, string in = "",int number = 0){
		size = l;
		i = new int[size];
		s = new string[size];
		for (int z = 0; z < size; z++) {
			s[z] = in;
			i[z] = number;
		}
	}
	//copy 
	Cart(const Cart& b) {
		s = new string[b.size];
		i = new int[b.size];
		size = b.size;
		for (int z = 0; z < b.size; z++) {
			s[z] = b.s[z];
			i[z] = b.i[z];
		}
	}

	~Cart(){
		delete [] s;
		delete [] i;

	}


	friend ostream& operator<<(ostream& out, Cart & a) {
		if (a.size > 0) {
			for (int z = 0;z < a.size; z++) {
			
				out <<"Item = " << a.s[z] << " \tPrice =" << a.i[z]<<endl;
				}
		}
		return out;
	}
	friend istream& operator>>(istream& in, Cart& a) {
		
		if (a.size > 0) {
			for (int z = 0; z < a.size; z++) {
				cout << "Input the name of the item and the price ";
				in>> a.s[z] >>a.i[z];
			}
			
		}
		return in;
	}
	void modify() {
		int oldSize = size;
		size = size + 1;

		int* newPrices = new int[size];
		string* newItems = new string[size];

		for (int z = 0; z < oldSize; z++) {
			newItems[z] = s[z];
			newPrices[z] = i[z];
		}

		cout << "The name of the new item = ";
		cin >> newItems[size - 1];
		cout << "The value of the new item = ";
		cin >> newPrices[size - 1];

		delete[] s;
		delete[] i;

		s = newItems;
		i = newPrices;
	}


	
};
void size(int& s) {
	cout << "Input the size of the cart of want to use = ";
	cin >> s;
}
int main()
{
	int s;
	size(s);
	Cart c1(s);
	cin >> c1;
	cout << c1;
	Cart c2 = c1;
	cout << c2;
	c2.modify();

}
