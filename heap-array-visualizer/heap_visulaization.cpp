#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

class MaxHeap {
private:
    vector<int> heap;

    int parent(int i) { return (i - 1) / 2; }
    int left(int i) { return (2 * i + 1); }
    int right(int i) { return (2 * i + 2); }

    void heapifyUp(int i) {
        while (i != 0 && heap[parent(i)] < heap[i]) {
            swap(heap[i], heap[parent(i)]);
            i = parent(i);
        }
    }

    void heapifyDown(int i) {
        int l = left(i);
        int r = right(i);
        int largest = i;

        if (l < heap.size() && heap[l] > heap[largest])
            largest = l;
        if (r < heap.size() && heap[r] > heap[largest])
            largest = r;

        if (largest != i) {
            swap(heap[i], heap[largest]);
            heapifyDown(largest);
        }
    }

public:
    // ADDED: Helper to check if heap has nodes
    bool isEmpty() {
        return heap.empty();
    }

    void insert(int key) {
        heap.push_back(key);
        heapifyUp(heap.size() - 1);
    }

    void extractMax() {
        if (heap.empty()) return;

        cout << "Deleting root (" << heap[0] << ")..." << endl;

        if (heap.size() == 1) {
            heap.pop_back();
            return;
        }

        heap[0] = heap.back();
        heap.pop_back();
        heapifyDown(0);
    }

    void displayTree() {
        if (heap.empty()) {
            cout << "Heap is Empty" << endl;
            return;
        }

        int n = heap.size();
        int h = ceil(log2(n + 1));

        int index = 0;
        for (int i = 0; i < h; i++) {
            int nodesAtLevel = pow(2, i);
            int firstSpace = pow(2, h - i) - 1;
            int midSpace = pow(2, h - i + 1) - 1;

            for (int k = 0; k < firstSpace; k++) cout << "  ";

            for (int j = 0; j < nodesAtLevel && index < n; j++) {
                printf("%02d", heap[index++]);
                for (int k = 0; k < midSpace; k++) cout << "  ";
            }
            cout << endl << endl;
        }
    }
};

int main() {
    MaxHeap mh;
    vector<int> values = { 12, 132, 14, 76, 44, 88 };

    cout << "--- MAX-HEAP INSERTION ---" << endl;
    for (int x : values) {
        mh.insert(x);
    }
    mh.displayTree();
    cout << "--------------------------" << endl;

    cout << "\n--- MAX-HEAP DELETION PHASE ---" << endl;
    // Now this loop works because of the isEmpty() method
    while (!mh.isEmpty()) {
        mh.extractMax();
        mh.displayTree();
        cout << "--------------------------------" << endl;
    }

    return 0;
}