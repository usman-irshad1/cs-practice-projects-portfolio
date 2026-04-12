#pragma once
#include <iostream>
using namespace std;

template <class t, int size>
class Heap {
    t array[size];
    int avail;
public:
    Heap() {
        avail = 0;
    }

    void insert(t n) {
        if (avail >= size) { cout << "return as the index is full\n"; return; }
        array[avail] = n;
        int temp = avail;

        avail++;
        while (temp > 0) {
            int parent = (temp - 1) / 2;
            if (array[parent] < array[temp]) {
                swap(array[parent], array[temp]);
                temp = parent;
            }
            else { break; }
        }
    }

    t* getMax() { return array[0]; }
    void deleteNode() {
        if (avail == 0) { cout << "Nothing to delete\n"; return; }
        array[0] = array[avail - 1];
        int temp = 0;
        avail--;
        int large;
        while (true) {
            int child1 = 2 * temp + 1;
            int child2 = 2 * temp + 2;
            if (child1 >= avail) break;

            if (child1 < avail) { large = child1; }

            if (child2 < avail) {
                if (array[child1] < array[child2]) { large = child2; }
                else { large = child1; }
            }
            else {
                large = child1;
            }
            if (array[temp] < array[large] && large <= avail) {
                swap(array[temp], array[large]);
                temp = large;
            }
            else { break; }
        }
    }

    void display(int count) const {
        if (count >= avail) { return; }
        cout << array[count] << "\t";
        display(count + 1);
    }

    void display_heap() const {
        display(0);
    }

    int max() const {
        return array[0];
    }

    int min(int x) const {
        if (x == avail - 1) { return array[x]; }
        int minOfRest = min(x + 1);
        if (array[x] < minOfRest) {
            return array[x];
        }
        else {
            return minOfRest;
        }
    }

    int minElement() const {
        if (avail == 0) return -1; // Added safety for empty heap
        return min(0);
    }

    void insertArray(t Array[], int current, int Size) {
        if (current >= Size || avail >= size) { return; }
        insert(Array[current]);
        insertArray(Array, current + 1, Size);
    }

    void copy(int count, t array[]) const {
        if (count >= avail) { return; }
        array[count] = this->array[count];
        copy(count + 1, array);
    }

    void sort(int count, t array[], Heap<t, size>& original, int total) {
        if (count >= total) { return; }
        array[count] = original.max();
        original.deleteNode();
        sort(count + 1, array, original, total);
    }

    bool isEmpty() const { return avail == 0; }

    void sortArray() {
        t temp[size];
        int total = avail;
        Heap<t, size> h = *this;

        sort(0, temp, h, total);

        for (int i = 0; i < total; i++) {
            array[i] = temp[i];
        }
    }

    // ==========================================
    // --- OPERATOR OVERLOADS ADDED BELOW ---
    // ==========================================

    // 1. Equality Operator (==)
    bool operator==(const Heap<t, size>& other) const {
        if (this->avail != other.avail) return false;
        for (int i = 0; i < this->avail; i++) {
            if (this->array[i] != other.array[i]) return false;
        }
        return true;
    }

    // 2. Less Than Operator (<)
    // Compares element-by-element. If identical up to a point, the smaller heap is "less".
    bool operator<(const Heap<t, size>& other) const {
        int limit = (this->avail < other.avail) ? this->avail : other.avail;
        for (int i = 0; i < limit; i++) {
            if (this->array[i] < other.array[i]) return true;
            if (this->array[i] > other.array[i]) return false;
        }
        return this->avail < other.avail;
    }

    // 3. Greater Than Operator (>)
    bool operator>(const Heap<t, size>& other) const {
        return other < *this; // Reuses the logic from the '<' operator!
    }

    // 4. Output Stream (<<)
    friend ostream& operator<<(ostream& os, const Heap<t, size>& h) {
        if (h.avail == 0) {
            os << "[Empty Heap]";
            return os;
        }
        for (int i = 0; i < h.avail; i++) {
            os << h.array[i] << " ";
        }
        return os;
    }

    // 5. Input Stream (>>)
    // Reads a single value from the user and inserts it directly into the heap.
    friend istream& operator>>(istream& is, Heap<t, size>& h) {
        t val;
        is >> val;
        h.insert(val);
        return is;
    }
};