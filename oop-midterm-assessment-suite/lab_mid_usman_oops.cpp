// lab_mid_usman_oops.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std;
#include <string>
class wrong_input :public exception {
public:
    const char* what() {
        return ("Your input is incorrect");
    }
};

///////////////////////////////////////////////////////////////////////////////////////////
class Zone {
    float temp;
    float humidity;

public:

    Zone(float i = 10, float j=10):temp(i), humidity(j){}

    float get_temp() {
        return temp;
    }
    float get_humid() {
        return humidity;
    }
    void set_temp() {
        float i;
        cout << "Input the value real value of the temp in degree Celcius for this zone \n";
        cin >> i;
        if (i > -50 && i < 100) {
            temp = i;
        }
        else {
            throw wrong_input();
        }

    }
    void set_humid() {
        float i;
        cout << "Input the value of the humidity from 1 to 100 ";
        cin >> i;
        if (i >0 && i<101) {
            humidity = i;
        }
        else {
            throw wrong_input();
        }
    }
    void observe(int dev, int sen) {
        cout << "\nThe humidity is ";
        cout<<this->get_humid();
        cout << "\nThe temp is ";
        cout<<this->get_temp();
    }
    void adjust() {
    }
    void regulate() {
    }



};

///////////////////////////////////////////////////////////////////////////////////////////

 //it should be comptoitio  as evry obervir has a zone
class Environmental_Obs {
    Zone z;
    float dev, sens;
public:
    Environmental_Obs(float i = 10, float j = 10, float k = 10, float l=10) :z(i, j), dev(k), sens(l){}

    void set_info() {
        z.set_temp();
        z.set_humid();
        float i;
        cout << "Input the ideal value of the temp in degree Celcius for this zone \n";
        cin >> i;
        if (i > -50 && i < 100) {
            float temp;
            temp =((z.get_temp() - i)/z.get_temp());  //this will get the value of deviation btw 1 and 0
            if (temp < 1 && temp > 0) {
                dev = temp;
            }
            else {
                temp = ((z.get_temp() - i) / i);  //this will get the value of deviation btw 1 and 0
                dev = temp;
            }
        }
        else {
            throw wrong_input();
        }
        float j;
        cout << "Input the value of the sensitivity it should be between 0 and 1 = ";
        cin >> j;
        if (j > 0 && j < 1) {
            sens = j;
        }
        else {
            throw wrong_input();
        }

    }

    float stability(){
        float stable = 1 - (dev * sens);
        if (stable < 0.6) {
            return 0;
        }
        else {
            return stable;
        }
    }

    friend class Zone_regulators;
};
///////////////////////////////////////////////////////////////////////////////////////////

class Adaptive_measures {
    float R_time,eff;
    Zone z;

public:
    Adaptive_measures(float i = 10, float j = 10, float k = 10, float l = 0.5) :z(i, j), R_time(k), eff(l){}
    void set_info() {
        z.set_temp();
        z.set_humid();
        cout << "Enter the reaction time in seconds = ";
        float j;
        cin >> j;
        if (j >= 0) {
            R_time = j;
        }
        else {
            throw wrong_input();
        }
        cout << "Enter the efficiency between 0 and 1  = ";
        cin >> j;
        if (j > 0 && j<1) {
            R_time = j;
        }
        else {
            throw wrong_input();
        }
    }

    int get_stability() {
        double temp;
        temp = 1 + (R_time / 10);
        temp = eff / temp;
        if (temp < 0.5) {
            cout<<"Dormant";
            return 1; //1 for unstable;
        }
        else {
            cout << "Active";
            return 0;
        }

    }

   

};


class Zone_regulators {
 
    float control;
    Adaptive_measures *i[10];
    Environmental_Obs *j[10];
    

public:
    Zone_regulators(float i=0.7):control(i){}

    void set_mechanisims() {
        int d;
        cout << "How many adaptive measures do you want ";
        cin >> d;
        for (int k = 0; k < d; k++) {
            i[k] = new Adaptive_measures;
            i[k]->set_info();
        }
        cout << "How many zone reulators do you want ";
        cin >> d;
        for (int k = 0; k < d; k++) {
            j[k] = new Environmental_Obs;
            j[k] ->set_info();        
        }
   }

    float get_zone_stability() {
        int active = 0;
        float sum=0;
        float temp;
        for (int k = 0; k < 10; k++) {
            temp=  j[k]->stability();
            if (temp > 0.6) {
                sum = sum + temp;
                active++;
            }
        }

        float zone_stab = 0;
        zone_stab = (sum / active) * control;
        return zone_stab;
    }

    void check() {
        int temp;
        for (int k = 0; k < 10; k++) {
            temp = i[k]->get_stability();
            if (temp == 1) {
                cout << "The regulator is failed";
                break;
            }
        }
    }

    
};
class Habitat{
    Zone z2 [4];
    Zone_regulators reg;
   
};
int main()
{
    std::cout << "Hello World!\n";
}

