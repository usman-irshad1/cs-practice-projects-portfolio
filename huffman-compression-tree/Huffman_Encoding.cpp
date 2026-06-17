// Huffman_Encoding.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <queue>
using namespace std;
struct Hnode {

    char x;
    int freq;
    Hnode* left, * right;
    Hnode() { x = '$'; left = nullptr; right = nullptr;  freq = 0; }
    Hnode(char a, int b) { x = a; left = nullptr; right = nullptr; freq = b; }
    Hnode( int b) { x = '$'; left = nullptr; right = nullptr; freq = b; }
};

struct compare {
    bool operator()(Hnode* a, Hnode* b) {
        return a->freq > b->freq;
    }
};
class Huffnode {
    priority_queue<Hnode*, vector<Hnode*>, compare> array;

public:
    void Encoding(string x) {
        int freq[256] = { 0 };
        for (int i = 0; i < x.size(); i++) {
            freq[int(x[i])]++;
        }

        for (int i = 0; i < 256; i++) {

            if (freq[i] > 0) {
                array.push(new Hnode(char(i), freq[i]));
            }
        }

        while (array.size()>1) {
            Hnode *a = array.top();
            array.pop();
            Hnode* b = array.top();
            array.pop();
            int freq_sum = a->freq + b->freq;
            Hnode* temp = new Hnode(freq_sum);
            temp->left = a;
            temp->right = b;
            array.push(temp);
        }
    }

    void printing(Hnode* node, string code) {
        if (node == nullptr) { return; }
        if (node->x != '$') {
            cout << node->x << ": " << code << endl;
        }
        printing(node->left, code+'0');
        printing(node->right,code+'1');
    }
    void printer( string code) {
        printing(array.top(), code);
        
    }
};

int main()
{
    string c="";
    string code = "Hello";
    Huffnode encoder;
    encoder.Encoding(code);
    encoder.printer(c);
    cout << "\n"<<c;

    std::cout << "Hello World!\n";
}

