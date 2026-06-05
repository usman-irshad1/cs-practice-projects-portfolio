// classpractice1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std;
class TV {
    string company;
    int channels;
    int volume;
    string source;
    bool power;
public:
    TV(string c = "", int ch= 0, int vol= 0, string s = "", bool p =false) {
         company=c;
         channels=ch;
         volume=vol;
        source=s;
         power=p;
    }


    void chanel_jump() {
       
            cout << "Input the chanel you want to go to = ";
            cin >> channels;
        
     
    }

    void chanel_increase() {
       
            ++channels;
        
     
            
        
    }
    void chanel_decrease() {
       

            --channels;
      
   
    }
    void volume_decrease(a) {
       
        int x;
        cout << "enter how much the volume should be decreased by = ";
        cin >> x;
        volume = volume - x;
       
    }

    void volume_increase() {
        int x;
        cout << "enter how much the volume should be increased by = ";
        cin >> x;
        volume = volume + x;
      
    }
    void Power() {
        int i = 0;
        cout << "Enter 1 to swicth on and 0 for off";
        cin >> i;
       
            if (i == 1)
            {
                power = true;
            }
            else {
                power = false;
            }
       
        
    }

    void Source() {
        

            cout << "Enter the source you want to use ";
            cin >> source;
        
       
    }
    void display() const {
        cout << company;
        cout << endl;
        cout << channels;
        cout << endl;
        cout << source;
        cout << endl;
        cout << volume;
        cout << endl;
        cout << power;
        cout << endl;
    }

    friend class Remote;


};
class Remote {
    string Company;
public:
    Remote(string c = "") {
        Company = c;
 
    }

    void chanel_jump(TV& a) {
        if (Company == a.company) {
            cout << "Input the chanel you want to go to = ";
            cin >> a.channels;
        }
        else {
            cout << "Your remote is invalid";
        }
    }

    void chanel_increase(TV& a) {
        if (Company == a.company) {
           
           ++ a.channels;
        }
        else {
            cout << "Your remote is invalid";
        }
    }
    void chanel_decrease(TV& a) {
        if (Company == a.company) {

           --a.channels;
        }
        else {
            cout << "Your remote is invalid";
        }
    }
    void volume_decrease(TV& a) {
        if (Company == a.company) {
            int x;
            cout << "enter how much the volume should be decreased by = ";
            cin >> x;
                a.volume = a.volume - x;
        }
        else {
            cout << "Your remote is invalid";
        }
    }

    void volume_increase(TV& a) {
        if (Company == a.company) {
            int x;
            cout << "enter how much the volume should be increased by = ";
            cin >> x;
            a.volume = a.volume + x;
        }
        else {
            cout << "Your remote is invalid";
        }
    }
    void Power(TV& a) {
        int i=0;
        cout << "Enter 1 to swicth on and 0 for off";
        cin >> i;
        if (Company == a.company) {
            if (i == 1)
            {
                a.power = true;
            }
            else {
                a.power = false;
            }
        }
        else {
            cout << "Your remote is invalid";
        }
    }

    void Source(TV& a) {
        if (Company == a.company) {

            cout << "Enter the source you want to use ";
            cin >> a.source;
        }
        else {
            cout << "Your remote is invalid";
        }
    }
    void display(TV& a) const {
        cout << a.company;
        cout << endl;
        cout << a.channels;
        cout << endl;
        cout << a.source;
        cout << endl;
        cout << a.volume;
        cout << endl;
        cout << a.power;
        cout << endl;
    }




};


int main()
{
    TV t ("h", 10, 10, "cable", true);
    Remote r ("h");
    r.chanel_increase(t);
    r.chanel_decrease(t);
    r.chanel_jump(t);
    r.volume_decrease(t);
    r.volume_increase(t);
    r.Power(t);
    r.Source(t);
    r.display(t);
        

}

