// TRIE_task.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "TASK.h"
#include"TRIE.h"
#include<fstream>
#include<iostream>
using namespace std;


class Dictionary {
	Trie trie;

public:
	Dictionary() {};
	void load_from_file(const string name) {
		ifstream file(name);

		if (file.is_open()) {
			string word;
			while (file >> word) {
				cout << "Insering " << word << endl;
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
			
		}
	}
};




int main()
{
	Dictionary OXFORD;
	OXFORD.load_from_file("Text.txt");
	OXFORD.search();
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
