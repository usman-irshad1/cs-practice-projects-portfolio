#define _HAS_STD_BYTE 0
#include <string>
#include <filesystem>
#include "list_1.h"
#include <windows.h>
#include <thread>
#include <iostream>
#include <C:\oops_folder\Hash_Map\Hash_Map\Header1.h>

namespace fs = std::filesystem;
using namespace fs;
using namespace std;
string getStandard(string x) {
    string result = "";
    for (int i = 0; i < x.size(); i++) {
        if (x[i] == '.') { return result; }
        result += toupper(x[i]);
    }
    return result;
}

int hashkey(string x, int size) {
    long long sum = 0;
    int array[] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71 };
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

struct FileNode {
    string name;
    FileNode* parent;

    FileNode(string n, FileNode* p) : name(n), parent(p) {}


    string getFullPath() {
        if (parent == nullptr) return name;
        string parentPath = parent->getFullPath();
        char lastChar = parentPath.back();
        string separator = (lastChar == '\\' || lastChar == '/') ? "" : "\\";

        return parentPath + separator + name;
    }
};
struct Hnode {
public:
    string key;
    AVLTree<FileNode*> paths;
    Hnode* next;
    Hnode() { next = nullptr; }
    friend ostream& operator<<(ostream& os, const Hnode& x) {
        os << "\tKey = " << x.key << endl << "\tPaths = " << x.paths << endl;
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


    void clear() {
        for (int i = 0; i < size; i++) {
            Hnode* current = Map[i];
            while (current != nullptr) {
                Hnode* nextNode = current->next;
                delete current;
                current = nextNode;
            }
            Map[i] = nullptr;
        }
        used = 0;
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
        else {
            Hnode* temp = Map[x];
            while (temp != nullptr) {
                if (temp->key == n) {
                    temp->paths.insert(path);
                    return;
                }
                if (temp->next == nullptr) break;
                temp = temp->next;
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
                cout << "\n\tHash Value = " << i << endl;
                cout << *n;
                n = n->next;
            }
        }
        cout << "\tUnique keys stored: " << used << endl;
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
        cout << "File not found." << endl;
        return AVLTree<string>();
    }
    FileNode* findFolderNode(string folderPath) {
        string n = getStandard(folderPath);
        int x = hashkey(n, size);
        Hnode* temp = Map[x];
        while (temp != nullptr) {
            if (temp->key == n) {
                return temp->paths.getRootValue();
            }
            temp = temp->next;
        }
        return nullptr;
    }
    ~HashMap() {
        clear();
    }

    void loadDirectory(const path& directoryPath) {
        int totalFiles = 0;
        if (!fs::is_directory(directoryPath)) {
            cout << "Error: Not a valid directory path." << endl;
            return;
        }

        for (const auto& entry : fs::recursive_directory_iterator(directoryPath)) {
            if (fs::is_regular_file(entry.path())) {
                insert(entry.path().filename().string(), entry.path().string());
                totalFiles++;
            }
        }
        cout << "Total files scanned: " << totalFiles << endl;
    }
};



bool needsUpdate = false;

void watchForChanges(string path) {
    HANDLE hDir = CreateFileA(path.c_str(), FILE_LIST_DIRECTORY, FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, NULL, OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS, NULL);
    char buffer[1024];
    DWORD bytes;
    while (true) {

        if (ReadDirectoryChangesW(hDir, buffer, sizeof(buffer), TRUE, FILE_NOTIFY_CHANGE_FILE_NAME, &bytes, NULL, NULL))
        {
            needsUpdate = true;
        }
    }
}

HashMap<100003> myVault;

int main() {
    string root;
    cout << "\t\t\t\t\tFILE MANAGEMENT SYSTEM\n" << endl;
    cout << "Enter the root directory to index: ";
    getline(cin, root);

    myVault.loadDirectory(root);
    std::thread watcherThread(watchForChanges, root);
    watcherThread.detach();
    string query;
    while (true) {
        if (needsUpdate) {
            cout << "\nChange detected REFRESHING" << endl;
            myVault.clear();
            myVault.loadDirectory(root);
            needsUpdate = false;
        }
        cout << "\nEnter filename, 'DISPLAY', 'REFRESH', or 'EXIT': ";
        getline(cin, query);

        string n = getStandard(query);
        if (n == "EXIT") {
            break;
        }
        else if (n == "DISPLAY") {
            myVault.display();
        }
        else if (n == "REFRESH") {
            cout << "Re-indexing directory" << endl;
            myVault.clear();
            myVault.loadDirectory(root);
        }
        else {
            cout << "\nResults for: " << query << endl;
            myVault.search(query);
        }
    }
    return 0;
}