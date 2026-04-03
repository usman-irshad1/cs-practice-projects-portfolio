#include <iostream>
#include <list>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

class Record {
public:
    int recordID;
    string name;
    double value;

    Record(int id, string n, double v) : recordID(id), name(n), value(v) {}

  
    bool operator<(const Record& other) const {
        return this->value < other.value;
        
    }

   
    friend ostream& operator<<(ostream& os, const Record& r) {
        os << "\nID: " << r.recordID << " | Name: " << r.name << " | Value: " << r.value << endl;
        return os;
    }
};

template <class t >
void display(t data) {
    cout << data<<"\t";
}

template <class t>
class l : public list<t> {
public:

    void Display_for_each() {
        for_each(this->begin(), this->end(), display<t>);
    }

    l<t> merging(l<t> d) {
        this->sort();
        d.sort();
        l<t> temp;
        merge(this->begin(), this->end(), d.begin(), d.end(), back_inserter(temp));
        return temp;
    }

    void duplicates_IDS() {
        bool found=false;
        vector<t> temp(this->begin(), this->end());    
        for (int i = 0; i < temp.size(); i++) {
            for (int j = i+1; j < temp.size() ; j++) {
                if (temp[j].recordID == temp[i].recordID) {
                    cout << temp[i];
                }
                found = true;
            }
        }
        if (found == false)
        {
            cout << "No Duplicates";
        }
    }

    void verify_sorting() {
        if (is_sorted(this->begin(), this->end())) {
            cout << "\n Data is correctly sorted by value.\n";
        }
        else {
            cout << "\Data is incorrect .\n";
        }
    }
   
};

int main() {
    l<Record> dept1;
    l<Record> dept2;

    dept1.push_back(Record(101, "Laptop", 1200.50));
    dept1.push_back(Record(103, "Mouse", 25.99));


    dept2.push_back(Record(102, "Keyboard", 45.00));
    dept2.push_back(Record(101, "Monitor", 300.00));

    cout << "Department 1 Contents" << endl;
    dept1.Display_for_each();

    cout << "Department 2 Contents " << endl;
    dept2.Display_for_each();

    cout << "\nMerging departments" << endl;
    l<Record> mergedData = dept1.merging(dept2);


    cout << "\nFinal Merged Collection " << endl;
    mergedData.Display_for_each();

    mergedData.verify_sorting();

    mergedData.duplicates_IDS();

    return 0;
}