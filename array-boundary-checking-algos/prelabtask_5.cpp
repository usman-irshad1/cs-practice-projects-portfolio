
#include <iostream>
#include <vector>
using namespace std;


class room {
    string room_Name;
    int area;
    bool window;

    public:
    room(string n ="room", int i = 101, bool w = true ) :room_Name(n),area(i),window(w){}


    void set_name() {
        cin >> room_Name;
    }

    void set_area() {
        cin >> area;
    }

    void set_window() {
        cin >> window;
    }

    string get_name() {
        return room_Name;
    }

    int get_area() {
        return area;
    }

    bool get_window() {
        return window;
    }
};

class House {
    int house_id;
    string name;
    int room_number;
    ;
    vector <room*> r1;
public:
    House() {
        cout << "House id = ";
        cin >> house_id;
        cout << "Name = ";
        cin >> name;
        cout << "Room in the house = ";
        cin >> room_number;
        for (int i = 0; i < room_number ; i++) {
            room* r2 = new room;
            cout << "Input the name of the room = ";
            r2->set_name();
            cout << "Input the area of the room = ";
            r2->set_area();
            cout << "Input if it has a window or not either 1 or 0 = ";
            r2->set_window();
            r1.push_back(r2);
    }
    }

    void add_room() {
        room* r2=new room;
        cout << "Input the name of the room = ";
        r2->set_name();
        cout << "Input the area of the room = ";
        r2->set_area();
        cout << "Input if it has a window or not either 1 or 0 = ";
        r2->set_window();
        r1.push_back(r2);
        room_number++;
    }

    void display() {
        cout << "House ID = ";
        cout << house_id;
        cout << endl;
        cout << "Name = ";
        cout << name;
        cout << endl;
        cout << "Rooms = ";
        cout << room_number;
        cout << endl;
        for (int i = 0; i < room_number; i++) {
            cout << "Name of room = ";
            cout<<r1[i]->get_name();
            cout << endl;
            cout << "Area of room = ";
            cout<<r1[i]->get_area();
            cout << endl;
            cout << "Window = ";
            cout<<r1[i]->get_window();
            cout << endl;
        }
    }

    void delete_House() {
        for (int i = 0; i < room_number; i++) {
            delete r1[i];
        }
    }
};

int main() {
    House h1;
    House h2;
    h1.add_room();
    h2.add_room();
    h1.display();
    h2.display();
    h1.delete_House();
}







