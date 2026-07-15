// Prcatice_algos.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <algorithm>
#include <iostream>
using namespace std;


void print(int s) { cout << s << " "; }


void selectionSort(int array[], int size) {
    for (int i = 0; i < size; i++) {
        int index = i;

        for (int j = i+1; j < size; j++) {
            if (array[j] < array[index]) {
                index = j;
            }
        }
        int temp = array[i];
        array[i] = array[index];
        array[index] = temp;
        for_each(array, array + 10, print);
        cout << endl;
    }
}


void Bubblesort(int array[], int size) {

    for (int i = 0; i < size; i++) {
        for (int j = 0 ; j < size-1; j++) {
            if (array[j] > array[j+1]) {
                swap(array[j], array[j+1]);
            }  
        }
        for_each(array, array + 10, print);
        cout << endl;
    }


}

void insertionSort(int array[], int size) {
    for (int i = 0; i < size; i++) {
        int smallest = array[i];
        int j = i - 1;
        while (j >= 0 && array[j] > smallest) {
            array[j + 1] = array[j];
            j--;
        }
        array[j + 1] = smallest;
        for_each(array, array + 10, print);
        cout << endl;
    }
    
}

void mergesort(int array[], int size) {

    if (size <= 1) { return; }
    int middle = size / 2;
    int leftSize = size / 2;
    int rightSize = size - leftSize;
    int* left_array = new int[leftSize];
    int* right_array = new int[rightSize];

    for (int i = 0; i < size; i++) {
        if (i < middle) {
            left_array[i] = array[i];
        }
        else {
            right_array[i - middle] = array[i];
        }
    }

    mergesort(left_array, middle);
    mergesort(right_array, size - middle);

    int left = 0; int right = 0; int index = 0;

    while (left < middle && right < size - middle) {
        if (left_array[left] <= right_array[right]) {
            array[index] = left_array[left];
            left++;
            index++;
        }
        else  {
            array[index] = right_array[right];
            right++;
            index++;
        }
    }

        while (left < middle) {
            array[index] = left_array[left];
            left++;
            index++;
        }

        while (right < size - middle) {
            array[index] = right_array[right];
            right++;
            index++;
        }
        delete[]left_array;
        delete[]right_array;
        for_each(array, array + 10, print);
        cout << endl;
    
}

int quicksort(int array[], int start, int high) {
	int pivot = array[high];
    int i = start - 1;
    for (int j = start;j<high; j++) {
        if (array[j] <= pivot) {
            i++;
            swap(array[i], array[j]);
        }
    }
    swap(array[i+1], array[high]);
    for_each(array, array + 10, print);
    cout << endl;
    return (i+1);
}
void quickSort(int array[], int low, int high) {
    if (low < high) {
        int pi = quicksort(array, low, high);
        quickSort(array, low, pi - 1);
        quickSort(array, pi + 1, high);
    }
}

int main()
{
	cout << "Selection Sort: " << endl;
    int array[10] = {64, 34, 25, 12, 22, 11, 90, 88, 76, 50};
    int array2[10] = { 64, 34, 25, 12, 22, 11, 90, 88, 76, 50 };
    selectionSort(array, 10);
    cout << "Bubble Sort: " << endl;
    Bubblesort(array2, 10);
	cout << "Insertion Sort: " << endl;
	int array3[10] = { 64, 34, 25, 12, 22, 11, 90, 88, 76, 50 };
	insertionSort(array3, 10);
    int array4[10] = { 64, 34, 25, 12, 22, 11, 90, 88, 76, 50 };
	cout << "Merge Sort: " << endl;
    mergesort(array4, 10);  

    int array5[10] = { 64, 34, 25, 12, 22, 11, 90, 88, 76, 50 };
    cout << "Quick Sort: " << endl;
    quickSort(array5, 0, 9);
    std::cout << "Hello World!\n";
}
