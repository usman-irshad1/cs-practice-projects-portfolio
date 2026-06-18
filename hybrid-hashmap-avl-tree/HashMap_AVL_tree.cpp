// Hash_Map.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <string>
#include <filesystem>
#include<C:\oops_folder\HashMap_AVL_tree\AVL_tree.h>
using namespace std;
namespace fs = std::filesystem;

string getStandard(string x) {
    string result = "";
    int lastDot = x.find_last_of('.');
    for (int i = 0; i < x.size(); i++) {
        if (i==lastDot) { return result; }
        result += toupper(x[i]);
    }
    return result;
}
int hashkey(string x, int size) {
    long long sum = 0;
    int array[] = { 2, 3, 5, 7, 11,13, 17, 19, 23, 29,31, 37, 41, 43, 47,53, 59, 61, 67, 71 };
    int arrayLen = sizeof(array) / sizeof(array[0]);
    int a = 0;
    for (int i = 0; i < x.length(); i++) {
        if (a < arrayLen) {
            sum += x[i] * array[a];
            a++;
        }
        else {
            sum += (x[i] * i / 11);
        }
    }
    return sum % size;
}

struct Hnode {
public:
    string key;             
    AVLTree<string> paths;  
    Hnode* next;
    Hnode() { next = nullptr; }
    friend ostream& operator<<(ostream& os, const Hnode& x) {
        os << "\tKey = " << x.key << endl << "\n\tPaths = " << x.paths << endl;
        return os;
    }


};

template <int size>
class HashMap {
    Hnode* Map[size];
    int used;

public:
    HashMap() {
        used = 0;
        for (int i = 0; i < size; i++) {
            Map[i] = nullptr;

        }
    }
    HashMap(const HashMap& original) {
        for (int i = 0; i < size; i++) {
            if (original.Map[i] == nullptr) {
                Map[i] = nullptr;
            }
            else {
                Map[i] = new Hnode();
                Map[i]->key = original.Map[i]->key;
                Map[i]->paths = original.Map[i]->paths;
                Hnode* temp = original.Map[i]->next;
                Hnode* current = Map[i];
                while (temp != nullptr) {
                    Hnode* n = new Hnode();
                    n->key = temp->key;
                    n->paths = temp->paths;
                    current->next = n;
                    current = n;
                    temp = temp->next;
                }
                current->next = nullptr;
            }
        }
    }


    void insert(string name, string path) {
        string n = getStandard(name);
        int x = hashkey(n, size);
        if (Map[x] == nullptr) {
            Map[x] = new Hnode();
            Map[x]->key = n;
            Map[x]->paths.insert(path);
            used++;
        }
        else if (Map[x]->key == n) {
            Map[x]->paths.insert(path);
        }
        else {
            Hnode* temp = Map[x];
            while (temp != nullptr && temp->next != nullptr) {
                if (temp->key == n) {
                    temp->paths.insert(path);
                    return;
                }
                temp = temp->next;
            }

            if (temp != nullptr && temp->key == n) {
                temp->paths.insert(path);
                return;
            }
            Hnode* newNode = new Hnode();
            newNode->key = n;
            newNode->paths.insert(path);
            temp->next = newNode;
        }
    }

    void display() {
        for (int i = 0; i < size; i++) {
            Hnode* n = Map[i];
            while (n != nullptr) {
                cout << "\n\t\t\t\tHash Value = " << i << endl;
                cout << *n;
                n = n->next;
            }


        }
        cout << "\t\t\t\t\t\t\USED = " << used << endl;
    }


    AVLTree<string> search(string name) {
        string x = getStandard(name);
        int i = hashkey(x, size);
        Hnode* temp = Map[i];
        while (temp != nullptr) {
            if (temp->key == x) {
                cout << temp->paths;
                return temp->paths;
            }
            temp = temp->next;
        }
        return AVLTree<string>();
    }

    ~HashMap() {
        for (int i = 0; i < size; i++) {
            Hnode* current = Map[i];
            while (current != nullptr) {
                Hnode* nextNode = current->next;
                delete current;
                current = nextNode;
            }
        }
    }

    void loadDirectory(const fs::path& directoryPath) {
        int totalFiles = 0;
        if (!fs::is_directory(directoryPath)) {
            cout << "Error: Not a valid directory path." << endl;
            return;
        }


        for (const auto& entry : fs::recursive_directory_iterator(directoryPath)) {
            fs::path entryPath = entry.path();

            if (fs::is_regular_file(entryPath)) {

                string fileName = entryPath.filename().string();
                string filePath = entryPath.string();

                // INSERT INTO hashmapp
                insert(fileName, filePath);
                totalFiles++;
                cout << "Indexed: " << fileName << endl;
            }
        }
        cout << "----------------------------------------" << endl;
        cout << "Total files scanned: " << totalFiles << endl;
        cout << "Unique keys stored: " << used << std::endl;
        cout << "----------------------------------------" << endl;
    }
};

int main() {
    HashMap<13001> myVault;
    string root;

    cout << "Enter the root directory to index: ";
    getline(cin, root);


    myVault.loadDirectory(root);

    string query;
    while (true) {

        cout << "\nEnter filename to search, 'DISPLAY' to see index, or 'EXIT': ";
        getline(cin, query);

        string standardQuery = getStandard(query);

        if (standardQuery == "EXIT") {
            break;
        }

        else if (standardQuery == "DISPLAY") {
            myVault.display();
        }
        else {
            cout << "\nResults for: " << query << endl;
            myVault.search(query);
        }
    }



    return 0;
}