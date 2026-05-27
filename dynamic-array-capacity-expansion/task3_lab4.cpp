
#include <iostream>
using namespace std;

class Course {
protected:
    string name;
    int code;
public:
    Course(string n="OOPS", int c=101) :code(c), name(n){}

    Course(const Course& c1) {
        name = c1.name;
        code = c1.code;
    }

    //friend istream& operator>>(istream& i, Course& c1) {
    //    cout << "Enter the name of the course\n";
    //   i >> c1.name;
    //    cout << "Enter the code of the course\n";
    //    i >> c1.code;
    //    return i;
    //}

    //friend ostream& operator <<(ostream& o, const Course& c1) {
    //    o << "\nName = " << c1.name << "\Code = " << c1.code<<endl;
    //    return o;
    //}

   virtual float grade()= 0;
   virtual void Input()=0;
   virtual void out()=0;
};

class Theory:public Course{
    float  quiz, midterm, final;
public:
    Theory(int q=0, int m=0, int f=0) {
        
        quiz = q;
        midterm = m;
        final = f;
    }
    float grade() override {
        return 0.3*quiz + 0.3*midterm + 0.4*final;
    }

    void Input() override {
        cout << "Enter the name of the course\n";
        cin >> name;
        cout << "Enter the code of the course\n";
        cin >> code;
        cout << "Enter the marks obtained in quiz= \n";
        cin >> quiz;
        cout << "Enter the marks obtained in midterms= \n";
        cin >> midterm;
        cout << "Enter the marks obtained in final = \n";
        cin >> final;
    }

    void out() override {
        cout << "The name of the course = ";
        cout<< name;
        cout << endl;
        cout << "The code of the course = ";
        cout<< code;
        cout << endl;
        cout << "Quizzes = " << quiz << "\nMidterms = " << midterm << "\n Final = " << final<<endl;
    }


    
};

class Lab :public Course {
    int viva;
    int tasks;
public:
    Lab(int v=10,  int t=0) :viva(v), tasks(t){}
    void Input() override {
        cout << "Enter the name of the course\n";
        cin >> name;
        cout << "Enter the code of the course\n";
        cin >> code;
        cout << "Enter the marks obtained in lab = \n";
        cin >> tasks;
        cout << "Enter the marks obtained in viva = \n";
        cin >> viva;
    }

    float grade() override {
        return 0.7*tasks + 0.3*viva;
    }
    void out() override {
        cout << "The name of the course = ";
        cout << name;
        cout << endl;
        cout << "The code of the course = ";
        cout << code;
        cout << endl;
        cout << "Lab tasks = " << tasks << "\nViva= " << viva <<endl;
    }



};

int main()
{
    const int x = 10;
    Course* c1[x];
    int in;
    for (int i = 0; i < x; i++) {
        cout << "If you want to register a theory course press 1 = \nFor lab press 2 =\n";
        cin >> in;
        if (in == 1) {
            c1[i] = new Theory;
            c1[i]->Input();
            c1[i]->out();
            cout << "Grade = " << c1[i]->grade();
        }
        else if (in == 2) {
            c1[i] = new Lab;
            c1[i]->Input();
            c1[i]->out();
            cout <<"Grade = " <<c1[i]->grade();
        }
        else {
            cout << "Your input is incorrect\n";

        }
    }
    
}

