#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class wrong_input :public exception {
public:
    const char* what()  const {
        return "Your input is incorrect = ";
    }
};

class Course {
protected:
    static int id;
    int course_id;
    string name;
public:
    Course(string n = " ") :name(n), course_id(id++) {}
    friend istream& operator>>(istream& i, Course& c) {
        cout << "Enter the name of the course = ";
        i >> c.name;
        return i;
    }
    friend ostream& operator<< (ostream& o, const Course& c) {
        o << "\nCourse Id = " << c.course_id << "\nName = " << c.name;
        return o;
    }
    virtual void input() {
        cin >> *this;
    }
    virtual void display()const {
        cout << *this;
    }

    virtual float calc_grade() = 0;

    virtual void store(ofstream&) = 0;
    virtual void load(ifstream&) = 0;
};




class Theory : public Course {
    float quiz, mid, final;

public:
    Theory(float a = 0, float b = 0, float c = 0) :quiz(a), mid(b), final(c) {}
    void input() {
        Course::input();
        float a, b, c;
        cout << "Enter the values of quiz , mid and final = ";
        cin >> a >> b >> c;
        if (a > 0 && b > 0 && c > 0) {
            quiz = a;
            mid = b;
            final = c;
        }
        else {
            throw wrong_input();
        }
    }

    friend ostream& operator<<(ostream& o, const Theory& t) {
        o << "\nThe Mark in quizzes, midterms and finals = " << t.quiz << endl << t.mid << endl << t.final << endl;
        return o;
    }
    void display() const {
        Course::display();
        cout << *this;
    }

    float calc_grade()override {
        return (0.2 * quiz + 0.3 * mid + 0.5 * final);
    }
    void store(ofstream& f_out) {

        if (!f_out) {
            cout << "The file has not been opened";
        }
        else {
            size_t  name_len = name.length();
            f_out.write(reinterpret_cast<const char*>(&name_len), sizeof(name_len));
            f_out.write(name.c_str(), name_len);

            f_out.write(reinterpret_cast<const char*> (&course_id), sizeof(course_id));
            f_out.write(reinterpret_cast<const char*>(&quiz), (sizeof(quiz)));
            f_out.write(reinterpret_cast<const char*>(&mid), (sizeof(mid)));
            f_out.write(reinterpret_cast<const char*>(&final), (sizeof(final)));
        }
    }

    void load(ifstream& f_in) {
        if (!f_in) {
            cout << "The file has not been opened ";
        }
        else {
            size_t name_len;
            f_in.read(reinterpret_cast<char*> (&name_len), (sizeof(name_len)));
            name.resize(name_len);
            f_in.read(&name[0], name_len);


            f_in.read(reinterpret_cast<char*>(&course_id), sizeof(course_id));
            f_in.read(reinterpret_cast<char*>(&quiz), sizeof(quiz));
            f_in.read(reinterpret_cast<char*>(&mid), sizeof(mid));
            f_in.read(reinterpret_cast<char*>(&final), sizeof(final));
        }
    }
};








class Lab : public Course {
    float final, viva;

public:
    Lab(float a = 0, float b = 0) :final(a), viva(b) {}
    void input() {
        Course::input();
        float a, b;
        cout << "Enter the values of final and viva = ";
        cin >> a >> b;
        if (a > 0 && b > 0) {
            final = a;
            viva = b;
        }
        else {
            throw wrong_input();
        }
    }

    friend ostream& operator<<(ostream& o, const Lab& t) {
        o << "\nThe Mark finals and viva are = " << t.final << "\t" << t.viva << endl;
        return o;
    }
    void display() const {
        Course::display();
        cout << *this;
    }

    float calc_grade()override {
        return (0.3 * viva + 0.7 * final);
    }

    void store(ofstream& f_out) {

        if (!f_out) {
            cout << "The file has not been opened";
        }
        else {
            size_t name_len = name.length();
            f_out.write(reinterpret_cast<const char*>(&name_len), sizeof(name_len));
            f_out.write(name.c_str(), name_len);
            f_out.write(reinterpret_cast<const char*>(&course_id), (sizeof(course_id)));
            f_out.write(reinterpret_cast<const char*>(&final), (sizeof(final)));
            f_out.write(reinterpret_cast<const char*>(&viva), (sizeof(viva)));
        }
    }

    void load(ifstream& f_in) {

        if (!f_in) {
            cout << "The file has not been opened ";
        }
        else {
            size_t name_len;
            f_in.read(reinterpret_cast<char*>(&name_len), sizeof(name_len));
            f_in.read((&name[0]), name_len);
            f_in.read(reinterpret_cast<char*>(&course_id), sizeof(course_id));
           f_in.read(reinterpret_cast<char*>(&final), sizeof(final));
           f_in.read(reinterpret_cast<char*>(&viva), sizeof(viva));
            
        }
    }
};

int Course::id = 100;


int main() {
    const int l = 3;
    Course* c1[l];
    int choice, c2;
    try {
        cout << "to load from mem press 1 ";
        cin >> c2;
        if (c2 == 0) {
            ofstream f_out("THEORY_Courses.dat", ios::trunc | ios::binary);
            ofstream f2_out("LAB_Courses.dat", ios::trunc | ios::binary);
            for (int i = 0; i < l; i++) {
                cout << "To register lab course press 1 and for theory press 2 = ";
                cin >> choice;
                if (choice == 1) {
                    c1[i] = new Lab;
                    c1[i]->input();
                    c1[i]->store(f2_out);
                }
                else if (choice == 2) {
                    c1[i] = new Theory;
                    c1[i]->input();
                    c1[i]->store(f_out);
                }
                else {
                    throw wrong_input();
                }
            }
            f_out.close();
            f2_out.close();

            for (int i = 0; i < l; i++) {
                c1[i]->display();
                cout << endl;
                cout << c1[i]->calc_grade();
                cout << endl;
            }


        }
        else if (c2 == 1) {
            ifstream f_in("LAB_Courses.dat",ios::binary);
            ifstream f2_in("THEORY_Courses.dat",ios::binary);
            for (int i = 0; i < l; i++) {
                cout << "To read lab course press 1 and for theory press 2 = ";
                cin >> choice;
                if (choice == 1) {
                    c1[i] = new Lab;
                    c1[i]->load(f_in);

                }
                else if (choice == 2) {
                    c1[i] = new Theory;
                    c1[i]->load(f2_in);
                }
                else {
                    throw wrong_input();
                }
            }
            for (int i = 0; i < l; i++) {
                c1[i]->display();
                cout << endl;
                cout << c1[i]->calc_grade();
                cout << endl;
            }

        }

        else {
            throw wrong_input();
        }

    }
    catch (wrong_input& o) {
        cout << o.what();
    }



    for (int i = 0; i < l; i++) {
        delete c1[i];
    }
}