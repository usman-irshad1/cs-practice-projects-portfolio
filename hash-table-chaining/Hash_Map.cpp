#define _HAS_STD_BYTE 0
#include <string>
#include <filesystem>
#include "list_1.h"
#include <windows.h>
#include <thread>
#include <iostream>
#include "tree.h"
#include "Header1.h"

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
            sum += (long long)x[i] * array[a];
            a++;
        }
        else {
            sum += (x[i] * i / 11);
        }
    }
    return (int)(sum % size);
}


struct DirectoryEntry {
    string folderName;
    DirectoryEntry* parent;

    DirectoryEntry(string name, DirectoryEntry* p) : folderName(name), parent(p) {}

    string getFullPath() const {
        
        if (parent == nullptr) return folderName;

        string pPath = parent->getFullPath();

      
        if (pPath.empty()) return folderName;

        char last = pPath.back();
        string sep;
        if (last == '\\' || last == '/') sep = "";
        else sep = "\\";

        return pPath + sep + folderName;
    }

    
    friend ostream& operator<<(ostream& os, const DirectoryEntry* de) {
        if (de) os << de->getFullPath();
        else os << "ROOT";
        return os;
    }

    bool operator<(const DirectoryEntry& other) const {
        if (this->parent == other.parent) {
            return this->folderName < other.folderName;
        }
        return getFullPath() < other.getFullPath();
    }
    bool operator>(const DirectoryEntry& other) const {
        if (this->parent == other.parent) {
            return this->folderName > other.folderName;
        }
        return getFullPath() > other.getFullPath();
    }
    bool operator==(const DirectoryEntry& other) const {

        if (this->parent != other.parent) return false;

        return this->folderName == other.folderName;
    }
};

struct Hnode {
public:
    string key;
    AVLTree<DirectoryEntry*> paths;
    Hnode* next;
    Hnode() : next(nullptr) {}
    friend ostream& operator<<(ostream& os, const Hnode& x) {
        os << "\tKey = " << x.key << endl << "\tPaths = " << x.paths << endl;
        return os;
    }
};

template <int size>
class HashMap {
    Hnode* Map[size];
    int used;
    tree<DirectoryEntry*> registry;

public:
    HashMap() {
        used = 0;
        for (int i = 0; i < size; i++) Map[i] = nullptr;
    }

    DirectoryEntry* getOrInsert(fs::path p) {
        if (p.empty()) return nullptr;

        
        DirectoryEntry searchKey(p.string(), nullptr);
        Bnode<DirectoryEntry*>* foundNode = registry.search(&searchKey);

        if (foundNode != nullptr) {
            return foundNode->getData();
        }

        DirectoryEntry* parentNode = nullptr;
        if (p.has_parent_path() && p.parent_path() != p) {
            parentNode = getOrInsert(p.parent_path());
        }

        DirectoryEntry* newNode = new DirectoryEntry(p.filename().string(), parentNode);
        registry.insert(newNode);
        return newNode;
    }

    void insert(string name, DirectoryEntry* pathPtr) {
        string n = getStandard(name);
        int x = hashkey(n, size);
        if (Map[x] == nullptr) {
            Map[x] = new Hnode();
            Map[x]->key = n;
            Map[x]->paths.insert(pathPtr);
            used++;
        }
        else {
            Hnode* temp = Map[x];
            while (temp != nullptr) {
                if (temp->key == n) {
                    temp->paths.insert(pathPtr);
                    return;
                }
                if (temp->next == nullptr) break;
                temp = temp->next;
            }
            Hnode* newNode = new Hnode();
            newNode->key = n;
            newNode->paths.insert(pathPtr);
            temp->next = newNode;
        }
    }

    void loadDirectory(const path& directoryPath) {
        int totalFiles = 0;
        if (!fs::is_directory(directoryPath)) return;

        for (const auto& entry : fs::recursive_directory_iterator(directoryPath)) {
            if (fs::is_regular_file(entry.path())) {
                string fileName = entry.path().filename().string();
                DirectoryEntry* sharedFolder = getOrInsert(entry.path().parent_path());
                insert(fileName, sharedFolder);
                totalFiles++;
            }
        }
        cout << "Total files scanned: " << totalFiles << endl;
    }

    void search(string name) {
        string x = getStandard(name);
        int i = hashkey(x, size);
        Hnode* temp = Map[i];
        while (temp != nullptr) {
            if (temp->key == x) {
                cout << *temp;
                return;
            }
            temp = temp->next;
        }
        cout << "File not found." << endl;
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

    ~HashMap() { clear(); }
};

bool needsUpdate = false;
void watchForChanges(string path) {
    HANDLE hDir = CreateFileA(path.c_str(), FILE_LIST_DIRECTORY,FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,  NULL, OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS, NULL);
    char buffer[1024];
    DWORD bytes;
    while (true) {
        if (ReadDirectoryChangesW(hDir, buffer, sizeof(buffer), TRUE,FILE_NOTIFY_CHANGE_FILE_NAME, &bytes, NULL, NULL))
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
        if (n == "EXIT") break;
        else if (n == "DISPLAY") myVault.display();
        else if (n == "REFRESH") {
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