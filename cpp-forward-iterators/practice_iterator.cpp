// practice_iterator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <algorithm>
#include <iostream>
#include <list>
using namespace std;

template <class t>
void printing(t data) { cout << data << "\t"; }
template <class t>
int doubling(t data) {
    return data * 2;
}
template <class t>
class l : public list<t> {
public:
    void Display() {

        typename list<t> ::iterator temp = this->begin();
        while (temp !=this->end()) {
            cout << *temp << "\t";
            temp++;
        }
        cout << endl;
    }



    bool operator<(l<t> & ar) {
        typename list<t> ::iterator temp1 = this->begin();
        typename list<t> ::iterator temp2 = ar.begin();
        

        
        while (temp1 != this->end() && temp2 != ar.end()) {
            if (*temp1 > *temp2) {
                return false;
            }
            temp1++;
            temp2++;
        }
        return true;
    }

    typename list<t>:: iterator finding(t data) {
      typename list<t>:: iterator h= find(this->begin(), this->end() , data);
      if (h == this->end()) {
          cout << "Not present\n";
          return h;
      }
      cout << "Present\n";
      return h;
    }
    int counting(t data) {
        return count(this->begin(), this->end(), data);
    
    }

    list<t> sorting() {
        this -> sort();
        return *this;

    }

    typename list<t> :: iterator pattern(t data, t data2) {
        t search_pattern[] = { data, data2 };
        typename list<t>::iterator h =  search(this->begin(), this->end(), search_pattern, search_pattern+2);

       if (h == this->end()) {
           cout << "Not present\n";
           return h;
       }
       cout << "Present\n";
       return h;
    }

  
    void Display_using_foreach() {
        for_each(this->begin(), this->end(), printing<t>);
    }
    


    void change(list<t>& temp) {
        
        transform(this->begin(), this->end(), back_inserter(temp), doubling<t>);


    }



};

int main()
{
    l<int > ar,ar1,f ;
    ar.push_back(2);
    ar.push_back(32);
    ar.push_back(43);
    ar.push_back(15);
    ar.push_back(26);
    ar.push_back(27);
    ar.push_back(38);
    ar.push_back(81);
    ar1.push_back(1);
    ar1.push_back(2);
    ar1.push_back(3);
    ar1.push_back(4);
    ar1.push_back(5);
    ar1.push_back(6);
    ar1.push_back(7);
    ar1.push_back(8);
    ar1.Display();
    ar.Display();
    ar.finding(6);
    cout<<ar.counting(4) << endl;
    //ar.sorting();
    ar.Display();
    ar1.pattern(2, 3);
    ar1.Display();
     ar.change(f);
     f.Display_using_foreach();
 bool x=  ar1 < ar;
 cout << x;
}

