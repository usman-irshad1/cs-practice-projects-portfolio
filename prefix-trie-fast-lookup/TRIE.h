#pragma once
#include<iostream>
using namespace std;
#include<unordered_map>
#include <vector>

struct TRIENode
{
    bool isEnd;
    unordered_map<char, TRIENode*> children;
    TRIENode() {

        isEnd = false;
    }
};

class Trie {
    TRIENode* root;

public:
    Trie() {

        root = new TRIENode();
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
            cout << prefix<<endl;
        }
        for (typename unordered_map<char, TRIENode*>::iterator i=n->children.begin(); i!=n->children.end(); i++) {
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
