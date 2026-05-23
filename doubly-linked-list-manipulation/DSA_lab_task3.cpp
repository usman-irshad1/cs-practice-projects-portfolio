// DSA_lab_task3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std;

class task {
    int date;
    int id;

    public :
        task(int d=1, int i=61) :date(d),id(i){}
        int getid() {
            return id;
        }
        int getdate() {
            return date;
        }
};

class  ToDoList {
    int size;
    task* array;
public:


    ToDoList(int s) {
        size = s;
        array = new task[size];

    }
    ToDoList() {
        size = 1;
        array = new task[size];

    }
    ~ToDoList() {
        cout << "Deconstructor called";
        delete[] array;
        array = nullptr;
    }

    ToDoList(const ToDoList& copy) {
        size = copy.size;
        array = new task[size];
        for (int i = 0; i < size; i++) {
            array[i] = copy.array[i];
        }

    }

    void AddTask(task t1) {
        size++;
        task* temp = new task[size];
        temp;
        for (int i = 0; i < size - 1; i++) {
            temp[i] = array[i];
        }
        delete[] array;
        temp[size - 1] = t1;
        array = temp;

    }

    void AddTask_random(task t1 , int x) {
        x--;
        size++;
        task* temp = new task[size];
        int xtemp = 0;
        for (int i = 0; i < size ; i++) {
            if (i != x) {
                temp[xtemp] = array[i];
                xtemp++;
            }
            else {
                temp[xtemp] = t1;
                xtemp++;
            }
        }
        delete[] array;
        array = temp;

    }


    void RemoveTask_id(int id) {
        int temp = -1;
        for (int i = 0; i < size; i++) {
            if (array[i].getid() == id) {
                temp = i;
                break;
            }
        }
        if (temp == -1) {
            cout << "the task does not exist" << endl;
        }
        else {
            int idcount = 0;
            int s = size - 1;
            task* save = new task[s];
            for (int i = 0; i < size; i++) {
                if (i != temp) {
                    save[idcount] = array[i];
                    idcount++;
                }
            }
            delete[]array;
            array = save;
            save = nullptr;
            size = s;
        }
    }
    void RemoveTask_date(int id) {
        int temp = -1;
        for (int i = 0; i < size; i++) {
            if (array[i].getdate() == id) {
                temp = i;
                break;
            }
        }
        if (temp == -1) {
            cout << "the task does not exist" << endl;
        }
        else {
            int idcount = 0;
            int s = size - 1;
            task* save = new task[s];
            for (int i = 0; i < size; i++) {
                if (i != temp) {
                    save[idcount] = array[i];
                    idcount++;
                }
            }
            delete[]array;
            array = save;
            save = nullptr;
            size = s;
        }
    }

    void display() {
        for (int i = 0; i < size; i++) {
            cout << "Date = "<<array[i].getdate() << endl;
            cout << "ID = " << array[i].getid() << endl;
        }
    }
};
    
    
 int main() {

        ToDoList List;


        
        task t1(10, 101);
        task t2(15, 102);
        task t3(20, 103);
        task t4(25, 104);
        task t5(30, 105);

     
        List.AddTask(t1);
        List.AddTask(t2);
        List.AddTask(t3);
        List.AddTask(t4);


        List.display();



        List.RemoveTask_id(102);
        List.display();

        List.RemoveTask_date(25);
        List.display();




        List.AddTask(task(30, 105));
        List.display();


        return 0;
   }
