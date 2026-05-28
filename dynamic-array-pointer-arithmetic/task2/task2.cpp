#include <iostream>
using namespace std;

template <class data>
class holder {
    data* p1;
    int size;

public:

    holder(int n = 1) {
        size = n;
        p1 = new data[size]; 
    }

    holder(data x1 = 0, int n = 1) {
        size = n;
        p1 = new data[size];
        for (int i = 0; i < size; i++) {
            p1[i] = x1;
        }
    }

    ~holder() {  
        delete[] p1;
    }
    
    data max() {
        data y;
        if (size > 0) {
            y = p1[0];
                for (int i = 0; i < size; i++) {
                    if (y < p1[i]) {
                        y = p1[i];
                    }
                }
        }
        return y;
    }

    data min() {
        data y;
        if (size > 0) {
            y = p1[0];
            for (int i = 0; i < size; i++) {
                if (y > p1[i]) {
                    y = p1[i];
                }
            }
        }
        return y;
    }

    void search(data in) {
        int z = 0;
        int p=0;
        if (size > 0) {
            for (int i = 0; i < size; i++) {
                if (in == p1[i]) {
                    z = 1 ;
                    p = i; 
                    break;
                }
                
            }
        }
        if (z ==1) {
            cout << "The value exists in the loaction " << p << endl;
        }
        else {
            cout << "The value is not found ";
        }

    }



    friend ostream& operator<<(ostream& a, const holder <data>& x) {
        a << "The values of p1:\n";
        for (int i = 0; i < x.size; i++) {
            a << x.p1[i] << endl;
        }
        return a;
    }

    friend istream& operator>>(istream& i, holder <data>& x) {
        cout << "Input the values of p1:\n";
        for (int j = 0; j < x.size; j++) {  
            i >> x.p1[j];                   
        }
        return i;  
    }

};

int main() {
    holder<string> h1(5);
    cin >> h1;
    cout << h1;
    h1.search("hello");
    cout<<h1.max();
    cout << endl;
    cout<<h1.min();
}
