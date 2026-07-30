#pragma once
#include <iostream>
#include<fstream>
#include<iostream>

#include<unordered_map>
#include <vector>
using namespace std;




struct TRIENode
{
    bool isEnd;
    unordered_map<char, TRIENode*> children;
    TRIENode() {

        isEnd = false;
    }
};

class Trie {
   

public:
    TRIENode* root;
    Trie() {

        root = new TRIENode();
    }

    vector<string> getSuggestions(string prefix) {
        vector<string> results;
        TRIENode* temp = root;
        for (char c : prefix) {
            if (temp->children.find(c) == temp->children.end()) {
                return results; // Return empty vector if prefix not found
            }
            temp = temp->children.at(c);
        }
        // Now get all words starting from this node
        get_all_Words(temp, prefix, results);
        return results;
    }
    void insert(string x) {

        TRIENode* temp = root;
        for (int i = 0; i < x.size(); i++) {
            if (temp->children.find(x[i]) == temp->children.end()) {

                temp->children[x[i]] = new TRIENode();
            }
            temp = temp->children.at(x[i]);
        }
        temp->isEnd = true;
    }

    bool search(string x) {
        TRIENode* temp = root;
        for (int i = 0; i < x.size(); i++) {
            if (temp->children.find(x[i]) == temp->children.end()) {
                cout << "It does not exist";
                return false;
            }
            temp = temp->children.at(x[i]);
        }
        if (temp->isEnd) {
            cout << "The word exists in the map";
            return true;
        }
        else {
            cout << "It does not exist";
            return false;
        }
    }
    bool searchPrefix(string x) {
        TRIENode* temp = root;
        for (int i = 0; i < x.size(); i++) {
            if (temp->children.find(x[i]) == temp->children.end()) {
                cout << "It does not exist";
                return false;
            }
            temp = temp->children.at(x[i]);
        }
        display(temp, x);
    }


    void display(TRIENode* n, string prefix)
    {
        if (n == nullptr) {
            return;
        }
        if (n->isEnd) {
            cout << prefix << endl;
        }
        for (typename unordered_map<char, TRIENode*>::iterator i = n->children.begin(); i != n->children.end(); i++) {
            char c = i->first;
            if (i->second != nullptr) {
                display(i->second, prefix + c);
            }
        }
    }




    // void deleteWord(string x){

    //     TRIENode* temp=root;
    //     for (int i=0;i<x.size();i++){

    //         if (temp->children.find(x[i])==temp->children.end()){cout<<"The word does not exist";return;}
    //         TRIENode* parent=temp;   

    //     }
    //     temp->isEnd=false;
    // }

    bool resurive_delete(TRIENode* node, string& x, int index) {

        if (index == x.size()) {
            if (node->isEnd == false) {
                return false;
            }
            else {
                node->isEnd = false;
                return node->children.empty(); //it will return true for deletion if no children like in cat and call when we delete cat when it reached t it says true but when it reches a it says false as one child is also l
            }
        }


        char c = x[index];
        if (node->children.find(c) == node->children.end()) {
            return false;
        }
        bool canDeleteChild = resurive_delete(node->children[c], x, index + 1);
        if (canDeleteChild) {

            delete node->children[c];//deleeting node
            node->children.erase(c);//deletng node form the map

            return (node->isEnd == false && node->children.empty());

        }
        return false;
    }

    void deleteWord(string x) {
        resurive_delete(root, x, 0);
    }

    void get_all_Words(TRIENode* x, string y, vector<string>& allWords) {
        if (x == nullptr) { return; }
        if (x->isEnd) {
            allWords.push_back(y);
        }
        for (auto temp = x->children.begin(); temp != x->children.end(); temp++) {
            char local = (*temp).first;
            get_all_Words(temp->second, y + local, allWords);
        }
    }

    void retrieveAllWords(vector<string>& allWords) {
        get_all_Words(root, "", allWords);
    }
};

class Dictionary {
public:
    Trie trie;
    Dictionary() {};
    void load_from_file(const string name) {
        ifstream file(name);

        if (file.is_open()) {
            string word;
            while (file >> word) {
                cout << "Inserting " << word << endl;
                trie.insert(word);

            }
            file.close();
        }
        else {
            cout << "The file is not opened";
        }
    }
    void search() {
        char input = ' ';
        string result = "";
        cout << "Input the word you want to search for:  0 for exit\n";
        while (true) {

            cin >> input;

            if (input == '0') break;
            result += input;
            trie.searchPrefix(result);
            cout << "\n WORD entered = " << result << endl;

        }
    }

    // Add this to your Trie class

};




