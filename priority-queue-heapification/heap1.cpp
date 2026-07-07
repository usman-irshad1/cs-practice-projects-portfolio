#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <string>

using namespace std;

template <class t, int size>
class Heap {
    t array[size];
    int avail;

public:
    Heap() {
        avail = 0;
        // We don't strictly need to zero the array because 'avail' 
        // tracks the valid range, but it's good practice.
    }

    // A robust printer that maintains tree structure even with missing nodes
    void printTree() {
        if (avail == 0) {
            cout << "[Empty Heap]" << endl;
            return;
        }

        int levels = log2(avail) + 1;
        // Calculate a base width so the tree doesn't look cramped
        int maxWidth = pow(2, levels) * 4;

        int currentIdx = 0;
        for (int l = 0; l < levels; l++) {
            int nodesInLevel = pow(2, l);
            int firstPadding = maxWidth / (nodesInLevel * 2);
            int betweenPadding = maxWidth / nodesInLevel;

            cout << setw(firstPadding) << "";

            for (int i = 0; i < nodesInLevel; i++) {
                if (currentIdx < avail) {
                    // This prints the actual value (including 0)
                    cout << array[currentIdx];
                    cout << setw(betweenPadding) << "";
                }
                else {
                    // This prints nothing for indexes >= avail
                    cout << " " << setw(betweenPadding) << "";
                }
                currentIdx++;
            }
            cout << "\n\n";
        }
        cout << string(maxWidth + 5, '-') << endl;
    }

    void insert(t n) {
        if (avail >= size) {
            cout << "Heap full!" << endl;
            return;
        }
        array[avail] = n;
        int temp = avail;
        avail++;

        // Bubble Up logic
        while (temp > 0) {
            int parent = (temp - 1) / 2;
            if (array[parent] < array[temp]) {
                swap(array[parent], array[temp]);
                temp = parent;
            }
            else break;
        }
        cout << "Inserted " << n << ":" << endl;
        printTree();
    }

    void deleteNode() {
        if (avail == 0) return;
        t deleted = array[0];

        // Root is replaced by the last element
        array[0] = array[avail - 1];
        avail--;

        // Bubble Down logic
        int temp = 0;
        while (true) {
            int left = 2 * temp + 1;
            int right = 2 * temp + 2;
            int largest = temp;

            if (left < avail && array[left] > array[largest]) largest = left;
            if (right < avail && array[right] > array[largest]) largest = right;

            if (largest != temp) {
                swap(array[temp], array[largest]);
                temp = largest;
            }
            else break;
        }
        cout << "Deleted " << deleted << ":" << endl;
        printTree();
    }

    bool isEmpty() const { return avail == 0; }
};

int main() {
    // Increased size to 11 to fit all 11 numbers including 0
    Heap<int, 11> myHeap;

    // The 11 numbers to insert
    int values[] = { 45, 12, 89, 34, 1, 99, 56, 23, 7, 6, 0 };

    cout << "--- BUILDING MAX-HEAP (Including 0) ---" << endl;
    for (int v : values) {
        myHeap.insert(v);
    }



    cout << "\n--- DELETING ALL NODES ---" << endl;
    while (!myHeap.isEmpty()) {
        myHeap.deleteNode();
    }

    return 0;
}