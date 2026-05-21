#include <iostream>
#include <C:\oops_folder\stack\stack\Stack.h>

using namespace std;

struct shape {
	int id;
	string name;
	shape(int i = int(), string s = string()) {
		id = i;
		name = s;
	}
};
template <class T>
class Editor {
private:
	Stack<shape> s;
	Stack<shape> q;
public:
	Editor() {
		s = Stack<shape>();
		q = Stack<shape>();
	}
	void push_stack(shape obj) {
		s.push(obj);
	}
	string undo() {
		shape e = s.get_top();
		q.push(e);
		s.pop();
		return e.name;
	}
	string redo() {
		shape e = q.get_top();

		s.push(e);
		q.pop();
		return e.name;
	}
	void display() {
		node<T>* temp = s.getStartpointer();
		shape s;
		while (temp != NULL) {
			s = temp->data;
			cout << s.name << "===";
			temp = temp->next;
		}
		cout << "NULL" << endl;

	}

};
void main() {
	Editor<shape> e;
	shape s1(1, "circle");
	shape s2(2, "triangle");
	shape s3(3, "rectangle");
	shape s4(4, "sqaure");
	e.push_stack(s1);
	e.push_stack(s2);
	e.push_stack(s3);
	e.push_stack(s4);
	e.display();
	e.undo();
	e.undo();
	e.display();
	e.redo();
	e.display();


}
