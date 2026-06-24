// HUFFMAN_Encoding_1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include<list>
#include <string>
#include<fstream>
using namespace std;

struct  encryption {
    int number;
    char x;
    encryption* left, * right;//this is for tree
    encryption() {
        left = right=nullptr;
        number = 1;
        x = char();
    }
    encryption(char s) {
        left = right = nullptr;
        number = 1;
        x = s;
    }
    void operator++(int ) {
        this->number++;
        
    }

};

bool compare(encryption* y, encryption* x) {
    return (y->number < x->number);

}
class priority_list : public list<encryption*> {
public:
    void encoding(string array) {


        for (int i = 0; i < array.size(); i++) {
            bool  found = false;
            auto temp = this->begin();
            while (temp != this->end()) {
                if (array[i] == (*temp)->x) {
                    (*temp)->number++;
                    found = true;
                    break;
                }
                temp++;
            }
            if (found != true) {
                encryption* x = new encryption();
                x->x = array[i];
                this->push_front(x);
            }
        }

        this->sort(compare);
    }

    void making_tree(string array) {
        this->encoding(array);
        while (this->size() > 1) {
            encryption* x = this->front();
            this->pop_front();
            encryption* y = this->front();
            this->pop_front();

            encryption* parent = new encryption();
            parent->x = '*';
            parent->left = x;
            parent->right = y;
            parent->number = x->number + y->number;
            this->push_front(parent);
            this->sort(compare);
        }

    }


    string printCODE(encryption* node, string x, char target) {
        if (node == nullptr) { return ""; }
        if (node->left == nullptr && node->right == nullptr) {
            if (node->x == target) return x;
            else return "";
        }
        string a= printCODE(node->left, x + '0', target);
        if(a!="") return a;
        string b= printCODE(node->right, x + '1', target);
        if(b!="") return b;
        return "";
    }

    void writing(encryption* node, string x,ofstream& outfile) {
        if (node == nullptr) { return; }
        if (node->x != '*') {
            outfile << node->x << ' ' << x << endl;

        }
        writing(node->left, x + '0', outfile);
        writing(node->right, x + '1', outfile);
    }




    string  decrypt(string x) {
         string result="";
        if (this->size() == 0) {
            cout << "the list is empty" << endl;
            return result;
        }
        else {
            encryption* temp = this->front();;
            for (int i = 0; i < x.size(); i++) {
                if (x[i] == '0') {
                    temp = temp->left;
                }
                else if (x[i] == '1' ){
                    temp = temp->right;
                }
                if (temp->left==nullptr && temp->right==nullptr) {
                    if (temp->x != '*') {
                        result += temp->x;
                       
                    }
                    temp = this->front();
                }
                
            }
        }
        return result;

    }



    void savekey() {
        ofstream outfile("Key_for_encryption.txt");
        if (outfile.is_open()) {
            writing(this->front(), "", outfile);
			cout << "the key is saved in the file Key_for_encryption.txt" << endl;
        }
		else { cout << "Failure"; }
    
    }

    void rebuilding() {
        this->clear();//so the prevoius tree is deleed
        ifstream infile("Key_for_encryption.txt");;
        if (infile.is_open()) {
            if (this->empty()) {
				this->push_back(new encryption('*'));
            }
            char x;
            string code;
            while (infile >> noskipws >> x) {
                infile >> code;
                infile.ignore();
				encryption* temp = this->front();
                for (int i = 0; i < code.size(); i++) {
                    if (code[i] == '0') {
                        if (temp->left==nullptr) {
                            temp->left = new encryption('*');
                        }
                        temp = temp->left;
                    }
                    if (code[i] == '1') {
                        if (temp->right == nullptr) {
                            temp->right = new encryption('*');
                        }
                        temp = temp->right;
                    }
                    
                }
                temp->x = x;
            }
            infile.close();
        }
        else { cout << "Failure"; }
    }




    string readingFile(string x) {
        ifstream infile(x);
        string temp;
        string result;
        if (infile.is_open()) {
            while (getline(infile,temp)) {
				result += temp+'\n';
            }
            infile.close();

        }
        else {
            cout << "Failure";
        }
        return result;
    }

    string encryptFile(string x) 
    { 
       string file= readingFile(x);
       making_tree(file);
       string result = "";
       for (int i = 0; i < file.size(); i++) {
            string c=printCODE(this->front(), "", file[i]);
            result += c;
       }
       return result;
    }


    void SAVEENCRYPTED(string x) {
        string result = encryptFile(x);
        ofstream outfile("Encrypted_file.txt");
        if (outfile.is_open()) {
            outfile << result;
            cout << "the encrypted file is saved in the file Encrypted_file.txt" << endl;
        }
        else {
            cout << "Failure";
        }
	}

    void decryptFile(string x) {
		string encryoted_text = readingFile(x);
        string result = decrypt(encryoted_text);
        ofstream outfile("Decrypted_file.txt");
        if (outfile.is_open()) {
            outfile << result;
            cout << "the decrypted file is saved in the file Decrypted_file.txt" << endl;
            outfile.close();
        }
        else {
            cout << "Failure";
        }
    }

    void deleteTree(encryption* node) {
        if (node == nullptr) { return;}
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    
    }


    ~priority_list() {
        if (this->empty()) { return; }
		deleteTree(this->front());
        this->clear();
    }
};
int main()
{
    


    priority_list map;
    map.encryptFile("OriginalFile.txt");
    map.savekey();
    map.rebuilding();
	map.SAVEENCRYPTED("OriginalFile.txt");
    map.decryptFile("Encrypted_file.txt");

}

