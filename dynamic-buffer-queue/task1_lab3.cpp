#include <iostream>
#include <C:\oops_folder\ConsoleApplication7\Queue.h>

using namespace std;

class work {
    int id;
    int workUnits;

public:
    work() {
        id = 0;
        workUnits = 0;
    }

    void setId(int i) {
        id = i;
    }

    void setWorkUnits(int w) {
        workUnits = w;
    }

    int getId() const {
        return id;
    }

    int getWorkUnits() const {
        return workUnits;
    }

    void operator=(work d) {
        id = d.id;
        workUnits = d.workUnits;
    }

    friend ostream& operator<<(ostream& os, const work& obj) {
        os << "ID = " << obj.id << "\t Work units = " << obj.workUnits;
        return os; 
    }
    
};
class  System_operator {
    Queue<work> list;
    Queue<work> list_done;

public:

    void add(work t) {
        cout << "Adding"<<endl;
        list.Insert(t);
    }
    void Delete() {
        cout << "" << endl;
        cout <<"The task completed is = " <<list.getFront();
        list_done.Insert(list.getFront());
        list.Delete();

    }
    void check() {
        cout<<"The task being processed is = "<<list.getFront()<<endl;
    }
    void showPendingTasks()
    {
        cout << "The task in line is/are = ";
        list.display();
    }
    
    void consume() {
        while (!list.isEmpty()) {
          int s = list.getFront().getWorkUnits();

          cout << "\t\t\t\t\t\tProcessing Task " << list.getFront()<<endl;

            while (s > 0) {
                s--; 
            }

            Delete();
        }
    }
    void showCompletedTasks() {
        cout << "Completed Tasks: 123 " << endl;
        list_done.display();
    }

};
int main() {
    System_operator sys;
    work w1, w2, w3;

    w1.setId(1); 
    w1.setWorkUnits(10);
    w2.setId(2); 
    w2.setWorkUnits(20);
    w3.setId(3);
    w3.setWorkUnits(30);
    sys.add(w1);
    sys.add(w2);
    sys.add(w3); 
    sys.check(); 
    
    sys.consume();
    sys.showPendingTasks();
    sys.showCompletedTasks();

    return 0;
}
