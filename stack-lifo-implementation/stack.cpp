// stack.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
/////////////////////////////////////////////////////////////////////////the dynamic stack/////////////////////////////////////

#include <regex>
#include <iostream>
using namespace std;
template <class t>
class node {
    node<t>* next;
    t data;
public:

    node() {
        next = nullptr;
        data = t();
    }
    node(t data) {
        this->data = data;
        next = nullptr;
    }

    void setNext(node<t>* n) { next = n; }
    node<t>* getNext() { return next; }
    void setData(t d) { data = d; }
    t getData() { return data; }

};
template <class t>
class Stack {
    node<t>* head;
public:
    Stack() {
        head = nullptr;
    }
    void push(t d) {
        node<t>* n = new node<t>();
        n->setData(d);
        n->setNext(head);
        head = n;
    }
    t pop() {
        if (head == nullptr) {
            // You could throw an exception here or return a default value
            return t();
        }
        node<t>* n = head;
        head = head->getNext();
        t data = n->getData();
        delete n;
        return data;
    }
    t peek() {
        if (head != nullptr) {
            return head->getData();
        }
        return t();
    }

    bool isEmpty() {
        return head == nullptr;
    }

    Stack(const Stack& p) {
        if (p.isEmpty()) { head = nullptr; return; }
        else {
            node<t>* temp = p.head;
            node<t>* n = new node<t>(temp->getData());
            
            head = n;
            node<t>* temp2=head;
            temp = temp->getNext();
            while (temp != nullptr) {
                node<t>* n = new node<t>(temp->getData());
                temp2->setNext(n);
                temp2 = temp2->getNext();
                temp = temp->getNext();            
            }
        }
    }

    bool checkBrackets(string x) {
        Stack<char> store;

        for (int i = 0; i < x.length(); i++) {
            if (x[i] == '(' || x[i] == '[' || x[i] == '{') {
                store.push(x[i]);
            }
            else if (x[i] == ')' || x[i] == ']' || x[i] == '}') {


                if (store.isEmpty()) {
                  
                    return false;
                }


                if (x[i] == ']') {
                    char a = store.pop();
                    if ('[' != a) {  return false; }

                }
                if (x[i] == '}') {
                    char a = store.pop();
                    if ('{' != a) {  return false; }

                }
                if (x[i] == ')') {
                    char a = store.pop();
                    if ('(' != a) {  return false; }

                }


            }
        }
   
        if (store.isEmpty())
            return true;
        else {
            return false;
        }

        
    }

    ~Stack() {
        while (head != nullptr) {
            pop();
        }
    }

    string reverse(string x) {
        Stack<char> store;
        for (int i = 0; i < x.length(); i++) {

            store.push(x[i]);
        }
        for (int i = 0; i < x.length(); i++) {
            x[i] = store.pop();
        }
        return x;
    }
    int getP(char x) {
        if (x == '+') {
            return 1;
        }
        if (x == '-') {
            return 1;
        }
        if (x == '*') {
            return 2;
        }
        if (x == '/') {
            return 2;
        }
        if (x == '^') {
            return 3;
        }
        return 0;
    }

    bool isNotOperator(char a) {
        string s(1, a);
        std::regex x ( "[a-zA-Z0-9]");
        return regex_match(s, x);
        
    }

    string postfix(string x) {
        Stack<char> store;
        string end="";

        for (int i = 0; i < x.length(); i++) {
            bool b = isNotOperator(x[i]);
            if (b) {
                end += x[i];

            }
            else if (x[i] == '(') {
                store.push(x[i]);
            }
            else if (x[i] == ')') {
                while (!store.isEmpty() && store.peek() != '(') {
                    end += store.pop();
                }
                if (!store.isEmpty()) store.pop();

            }

            else {
                int check = getP(x[i]);
                while (!store.isEmpty() && getP(store.peek()) >= check && store.peek() != '(') {
                    if (x[i] == '^' && store.peek() == '^') {
                        break;
                    };
                    char peek = store.pop();
                    end += peek;
                }
                store.push(x[i]);
            }
        }
        while (!store.isEmpty()) {
            end += store.pop();
        }
        return end;
    }



    double calPostfix(string x) {
        Stack<double>store;
        for (int i = 0; i < x.length(); i++) {
            if (isNotOperator(x[i])) {
                store.push(x[i]-'0');
            }

            else {
                double val1 = store.pop();
                double val2 = store.pop();
                // we push the resut back ontot the stakc
                switch (x[i]) {
                case '+': store.push(val2 + val1); break;
                case '-': store.push(val2 - val1); break;
                case '*': store.push(val2 * val1); break;
                case '/': store.push(val2 / val1); break;
                case '^': store.push(pow(val2, val1)); break;
                }
            }
        }
        return store.pop();
    }
};
int main() {
    Stack<char> s;

    // --- 1. Bracket Tests ---
    string test1 = "{[()]}";
    cout << "--- Bracket Test ---" << endl;
    cout << "Balanced Test: " << (s.checkBrackets(test1) ? "Pass" : "Fail") << endl;

    // --- 2. Postfix Conversion Tests (Variables) ---
    cout << "\n--- Postfix Conversions ---" << endl;
    string infix1 = "A+B*C";
    string infix2 = "(A+B)*C";
    string infix3 = "A^B^C";
    string infix4 = "A+B*(C-D)";

    cout << infix1 << " -> " << s.postfix(infix1) << endl;
    cout << infix2 << " -> " << s.postfix(infix2) << endl;
    cout << infix3 << " -> " << s.postfix(infix3) << endl;
    cout << infix4 << " -> " << s.postfix(infix4) << endl;

    // --- 3. Calculation Tests (Numbers) ---
    cout << "\n--- Math Evaluation ---" << endl;
    // Let's test (5+3)*2^2 / 4 -> Postfix: 53+22^*4/
    string mathInfix = "(5+3)*2^2/4";
    string mathPostfix = s.postfix(mathInfix);

    // We use a Stack<double> or just call the method from our existing instance
    // since the method handles its own internal Stack<double>
    double result = s.calPostfix(mathPostfix);

    cout << "Infix:   " << mathInfix << endl;
    cout << "Postfix: " << mathPostfix << endl;
    cout << "Result:  " << result << " (Expected: 8)" << endl;

    // Testing division with doubles: 5/2
    cout << "5/2 Postfix: " << s.postfix("5/2") << " | Result: " << s.calPostfix(s.postfix("5/2")) << endl;

    return 0;
}