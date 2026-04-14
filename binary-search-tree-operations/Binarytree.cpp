#define _HAS_STD_BYTE 0 // Disables std::byte to prevent conflicts with Windows headers
#include <string>       // Standard string handling
#include <filesystem>  // File system library for directory traversal
#include "list_1.h"     // Custom header (likely linked list implementation)
#include <windows.h>    // Windows API for directory watching (ReadDirectoryChangesW)
#include <thread>       // Support for running the watcher in the background
#include <iostream>     // Console input and output
#include <C:\oops_folder\Hash_Map\Hash_Map\tree.h>   // Custom BST/Tree implementation
#include <C:\oops_folder\Hash_Map\Hash_Map\Header1.h> // Additional custom logic/templates

namespace fs = std::filesystem; // Alias for the filesystem namespace
using namespace fs;             // Use filesystem members without prefix
using namespace std;            // Use standard library members without prefix

// --- Helper Functions ---
string getStandard(string x) {  // Normalizes strings (uppercase, removes extensions)
    string result = "";
    for (int i = 0; i < x.size(); i++) {
        if (x[i] == '.') { return result; } // Stop at the first dot (removes extension)
        result += toupper(x[i]);            // Convert character to uppercase
    }
    return result; // Return the standardized key
}

int hashkey(string x, int size) { // Generates a hash index for the Map
    long long sum = 0;            // Use long long to prevent overflow during math
    int array[] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71 }; // Prime multipliers
    int arrayLen = sizeof(array) / sizeof(array[0]); // Get count of primes
    int a = 0; // Index for the prime array
    for (int i = 0; i < x.length(); i++) {
        if (a < arrayLen) {
            sum += (long long)x[i] * array[a]; // Multiply char by prime for distribution
            a++;
        }
        else {
            sum += (x[i] * i / 11); // Fallback math for long strings
        }
    }
    return (int)(sum % size); // Return index within the bounds of the hash table
}

// --- Data Structure for Memory Efficiency ---
struct DirectoryEntry { // Stores directory info to avoid repeating long path strings
    string folderName;  // The name of this specific folder
    DirectoryEntry* parent; // Pointer to the parent folder (recursive structure)

    DirectoryEntry(string name, DirectoryEntry* p) : folderName(name), parent(p) {} // Constructor

    string getFullPath() const { // Reconstructs the full path string by climbing the tree
        if (parent == nullptr) return folderName; // Top-level folder found

        string pPath = parent->getFullPath(); // Get parent's path recursively

        if (pPath.empty()) return folderName; // Edge case safety check

        char last = pPath.back(); // Check last character for separators
        string sep;
        if (last == '\\' || last == '/') sep = ""; // No separator needed
        else sep = "\\"; // Add Windows backslash

        return pPath + sep + folderName; // Combine and return
    }

    // Overload for printing the path to the console
    friend ostream& operator<<(ostream& os, const DirectoryEntry* de) {
        if (de) os << de->getFullPath(); // Print reconstructed path
        else os << "ROOT"; // Print ROOT if null
        return os;
    }

    // Operators required for storing DirectoryEntry in the BST (registry)
    bool operator<(const DirectoryEntry& other) const { return getFullPath() < other.getFullPath(); }
    bool operator>(const DirectoryEntry& other) const { return getFullPath() > other.getFullPath(); }
    bool operator==(const DirectoryEntry& other) const { return getFullPath() == other.getFullPath(); }
};

struct Hnode { // Node for the Hash Map (Chaining for collisions)
public:
    string key;               // The standardized filename
    AVLTree<DirectoryEntry*> paths; // Tree of paths where this file exists
    Hnode* next;              // Pointer to next node in case of hash collision
    Hnode() : next(nullptr) {} // Initialize next as null
    friend ostream& operator<<(ostream& os, const Hnode& x) { // Overload for easy display
        os << "\tKey = " << x.key << endl << "\tPaths = " << x.paths << endl;
        return os;
    }
};

template <int size>
class HashMap {
    Hnode* Map[size];        // Array of Hnode pointers (the hash table)
    int used;                // Counter for unique keys
    tree<DirectoryEntry*> registry; // BST to store and reuse unique DirectoryEntry objects

public:
    HashMap() { // Constructor
        used = 0; // Initialize count
        for (int i = 0; i < size; i++) Map[i] = nullptr; // Clear pointers
    }

    DirectoryEntry* getOrInsert(fs::path p) { // Ensures each folder is only created in memory once
        if (p.empty()) return nullptr;

        DirectoryEntry searchKey(p.string(), nullptr); // Create temporary object to search
        Bnode<DirectoryEntry*>* foundNode = registry.search(&searchKey); // Check if folder exists

        if (foundNode != nullptr) {
            return foundNode->getData(); // Return existing pointer
        }

        DirectoryEntry* parentNode = nullptr; // Recursive logic to create parent tree
        if (p.has_parent_path() && p.parent_path() != p) {
            parentNode = getOrInsert(p.parent_path()); // Traverse up to root
        }

        DirectoryEntry* newNode = new DirectoryEntry(p.filename().string(), parentNode); // Create new folder node
        registry.insert(newNode); // Add to BST for future lookups
        return newNode;
    }

    void insert(string name, DirectoryEntry* pathPtr) { // Inserts filename and its path into hash map
        string n = getStandard(name); // Normalize filename
        int x = hashkey(n, size);     // Calculate hash index
        if (Map[x] == nullptr) {      // If index is empty
            Map[x] = new Hnode();
            Map[x]->key = n;
            Map[x]->paths.insert(pathPtr); // Add path to AVL tree
            used++;
        }
        else {
            Hnode* temp = Map[x];
            while (temp != nullptr) {
                if (temp->key == n) { // If filename already exists (duplicate file name in different path)
                    temp->paths.insert(pathPtr); // Just add the new path to existing node
                    return;
                }
                if (temp->next == nullptr) break;
                temp = temp->next; // Move through collision chain
            }
            Hnode* newNode = new Hnode(); // Key not found in chain, create new
            newNode->key = n;
            newNode->paths.insert(pathPtr);
            temp->next = newNode; // Link it
        }
    }

    void loadDirectory(const path& directoryPath) { // Scans the disk
        int totalFiles = 0;
        if (!fs::is_directory(directoryPath)) return; // Validation

        for (const auto& entry : fs::recursive_directory_iterator(directoryPath)) { // Walk through all subfolders
            if (fs::is_regular_file(entry.path())) { // Only process files, not folders
                string fileName = entry.path().filename().string(); // Get file name
                DirectoryEntry* sharedFolder = getOrInsert(entry.path().parent_path()); // Get/Create folder ptr
                insert(fileName, sharedFolder); // Add to hash map
                totalFiles++;
            }
        }
        cout << "Total files scanned: " << totalFiles << endl;
    }

    void search(string name) { // Search for a file by name
        string x = getStandard(name); // Normalize query
        int i = hashkey(x, size);     // Find index
        Hnode* temp = Map[i];         // Start at head of chain
        while (temp != nullptr) {
            if (temp->key == x) {     // Match found
                cout << *temp;        // Print all paths for this file
                return;
            }
            temp = temp->next;        // Keep looking in chain
        }
        cout << "File not found." << endl;
    }

    void clear() { // Cleans up dynamic memory
        for (int i = 0; i < size; i++) {
            Hnode* current = Map[i];
            while (current != nullptr) {
                Hnode* nextNode = current->next;
                delete current; // Delete Hnode (AVL trees inside delete themselves)
                current = nextNode;
            }
            Map[i] = nullptr;
        }
        used = 0;
    }

    void display() { // Prints the entire hash map
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

    ~HashMap() { clear(); } // Destructor
};

// --- Watcher and Main ---
bool needsUpdate = false; // Shared flag between threads

void watchForChanges(string path) { // Runs in background thread
    HANDLE hDir = CreateFileA(path.c_str(), FILE_LIST_DIRECTORY,
        FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
        NULL, OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS, NULL); // Open folder for monitoring
    char buffer[1024]; // Buffer for change events
    DWORD bytes;
    while (true) {
        // This function blocks until a file is added/deleted/renamed
        if (ReadDirectoryChangesW(hDir, buffer, sizeof(buffer), TRUE,
            FILE_NOTIFY_CHANGE_FILE_NAME, &bytes, NULL, NULL))
        {
            needsUpdate = true; // Signal the main thread to refresh
        }
    }
}

HashMap<100003> myVault; // Instantiate hash map with a prime size

int main() {
    string root;
    cout << "\t\t\t\t\tFILE MANAGEMENT SYSTEM\n" << endl;
    cout << "Enter the root directory to index: ";
    getline(cin, root); // Get user path

    myVault.loadDirectory(root); // Initial scan
    std::thread watcherThread(watchForChanges, root); // Start monitoring thread
    watcherThread.detach(); // Let it run independently

    string query;
    while (true) { // Main interaction loop
        if (needsUpdate) { // Check if the watcher thread signaled a change
            cout << "\nChange detected... REFRESHING" << endl;
            myVault.clear();
            myVault.loadDirectory(root);
            needsUpdate = false;
        }
        cout << "\nEnter filename, 'DISPLAY', 'REFRESH', or 'EXIT': ";
        getline(cin, query);

        string n = getStandard(query); // Check command
        if (n == "EXIT") break; // Exit loop
        else if (n == "DISPLAY") myVault.display(); // Show all
        else if (n == "REFRESH") { // Manual refresh
            myVault.clear();
            myVault.loadDirectory(root);
        }
        else {
            cout << "\nResults for: " << query << endl;
            myVault.search(query); // Perform search
        }
    }
    return 0; // Terminate program
}