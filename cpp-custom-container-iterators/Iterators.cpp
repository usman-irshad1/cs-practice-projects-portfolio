#include <iostream>

#include <list>

#include <string>



using namespace std;



template<class t>

class myList :public list<t>

{



public:

    void display()

    {

        

        typename list<t>::random_access_iterator temp;

        temp = (*this).begin();



        while (temp != (*this).end())

        {

            cout << (*temp) << endl;

            temp+5;

        }

    }



    bool operator==(myList<t>l)

    {
        typename list<t> ::iterator temp1 = this->begin();;
        typename list<t> ::iterator temp2 = l.begin();

        if (this->size() !=l.size()) { return false; }
        
        while (temp1!=this->end()) {
            if (*temp1 == *temp2) {
                temp1++;
                temp2++;
            }
            else { return false; }
        }
        return true;
   

    }

};



int main() {

    myList<int>l, l2;



    l.push_back(10);

    l.push_front(11);



    l.display();


    if (l == l2) {
        cout << "Equal" << endl;
    }
    else {
        cout << "Not Equal"<< endl;
    }



    return 0;

}

