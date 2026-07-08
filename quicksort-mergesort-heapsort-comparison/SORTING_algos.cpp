// SORTING_algos.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include<string>

using namespace std;

void selectionSort(int  array[], int size) {
    
    for (int i = 0; i < size; i++) {
        int index = i;
        int min = array[i];
       for(int j=i+1; j<size; j++) {
            if (array[j] < min) {
                min = array[j];
                index = j;
            }
        }
        array[index] = array[i];
        array[i] = min;
    }
}

void BubbleSort(int  array[], int size) {
  
    for (int i = 0; i < size; i++) {
        for (int j = i; j < size - 1; j++) {
            if (array[j] > array[j + 1]) {
                int temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
}

void InsertionSort(int  array[], int size) {

    for (int i = 0; i < size; i++) {
        int temp = array[i];
        int choose = i - 1;
        while (choose >= 0 && array[temp] > array[i]) {
            array[temp - 1] = array[temp];
            temp--;
        }
        array[i + 1] = temp;
    }
}


void merge(int left[], int right[], int merged[], int rightsize, int leftsize) {
    int i = 0;
    int right_index = 0; int left_index = 0;
    while (right_index < rightsize && left_index < leftsize) {
        if (left[left_index] < right[right_index]) {
            merged[i] = left[left_index];
            i++;
            left_index++;
        }
        else {
            merged[i] = right[right_index];
            i++;
            right_index++;
        }
    }
        while (left_index < leftsize) {
            merged[i] = left[left_index];
            i++;
            left_index++;
        }
        while (right_index < rightsize) {
            merged[i] = right[right_index];
            i++; right_index++;
        }

    }

    void MergeSort(int array[], int size) {
        if (size <= 1) { return; }
        
            int middle = size / 2;
            int* left_array=new int [middle];
			int *right_array=new int [size - middle];
            int j = 0;
            
            for (int i = 0; i < size; i++) {

                if (i < middle) {
                    left_array[i] = array[i];
                }
                else {
                    right_array[j] = array[i];
                    j++;
                }
            }
            MergeSort(left_array, middle);
            MergeSort(right_array, size - middle);
            merge(left_array, right_array, array, middle, size-middle);
            delete[] left_array;
            delete[] right_array;
        
    }



int main()
{
    int array[8] = {1,2,3,5,7,9,4,6};
	MergeSort(array, 8);
    
    for (int i=0; i<8; i++) {
        std::cout << array[i] << " ";
    }
    return 0;
}
