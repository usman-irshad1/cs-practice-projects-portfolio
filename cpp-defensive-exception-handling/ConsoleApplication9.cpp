// ConsoleApplication9.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include<unordered_map>

using namespace std;

struct TrieNode {

    bool isEnd;
    unordered_map<char, TrieNode*> next;

    TrieNode() {
        isEnd = false;
    }

};


class Trie {

    TrieNode* root;

public:

    Trie() {
        root = new TrieNode();
    
    }
    void insert(string word) {

        TrieNode* temp=root;

        for (int i = 0; i < word.size(); i++) {
            if (temp->next.find(word[i]) == temp->next.end())
            {

                temp->next[word[i]] = new TrieNode();
            }
            temp = temp->next[word[i]];
        
        }
        temp->isEnd = true;
    }

    void search(string word) {
        TrieNode* temp = root;

        for (int i = 0; i < word.size(); i++) {
            if (temp->next.find(word[i]) != temp->next.end()) {
                temp = temp->next.at(word[i]);
            }
            else {
                cout << "broken";
                return;
            }
        }
        if (temp->isEnd) {
            cout << "is found";
        }
        else {
            cout << "Not found";
        }
    }


    void display(string word, TrieNode* temp) {

        if (temp->isEnd) {
            cout << word<<endl;
        }

        for (unordered_map<char, TrieNode*> ::iterator it = temp->next.begin(); it != temp->next.end(); ++it) {
            display(word + it->first, it->second);
            cout << endl;
        }


    }

        TrieNode* searchPrefix(string word) {
            TrieNode* temp = root;

            for (int i = 0; i < word.size(); i++) {
                if (temp->next.find(word[i]) != temp->next.end()) {
                    temp = temp->next.at(word[i]);
                    cout<< word[i];
                }
                else {
                 
                      cout << "broken";
                      return nullptr; 
        }
                    
                

                

            }
            display(word, temp);
            return temp;
            
}


        void count(int &no,TrieNode* node) {
            
            if (node->isEnd) {
                no++;
            }

            for (unordered_map<char, TrieNode* >::iterator it = node->next.begin(); it != node->next.end(); it++) {
                count(no, it->second);
            }
        }
        

        TrieNode* CountPrefix(string word) {
            TrieNode* temp = root;

            for (int i = 0; i < word.size(); i++) {
                if (temp->next.find(word[i]) != temp->next.end()) {
                    temp = temp->next.at(word[i]);
                    cout << word[i];
                }
                else {

                    cout << "broken";
                    return nullptr;
                }





            }
            int no=0;
            count(no, temp);
            cout << no;
            return temp;

        }

};
int main() {
    Trie myTrie;

    // Test Insertions
    myTrie.insert("apple");
    myTrie.insert("app");

    // Test Searches
    myTrie.search("apple");   // Found
    cout << endl;
    myTrie.search("app");     // Found
    cout << endl;
    myTrie.search("appl");    // Not found (prefix only)
    cout << endl;
    myTrie.search("banana");  // Broken
    cout << endl;
    // Test Prefix
    myTrie.searchPrefix("a"); // Will show apple then break
    myTrie.CountPrefix("a");
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
