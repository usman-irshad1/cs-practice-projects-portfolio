#pragma once
#include<iostream>
using namespace std;

const int s = 100;

class Heap {

	int arr[s];
	int avail;

public:

	Heap() :avail(0) {}

	bool isEmpty() { return avail == 0; }

	void insert(int d) {

		if (isEmpty()) {
			arr[avail] = d;
			avail++;
		}

		else {
			arr[avail] = d;
			int temp = avail++;
			int par;

			while (true) {

				par = (temp - 1) / 2;

				if (temp > 0 && arr[temp] > arr[par]) {
					swap(arr[temp], arr[par]);
					temp = par;
				}

				else { break; }
			}
		}
	}

	int getTop() {

		if (isEmpty()) {
			cout << "Heap is empty!" << endl;
			return -1;
		}

		return arr[0];
	}

	void Delete() {

		if (isEmpty()) {
			cout << "Heap is empty!" << endl;
			return;
		}

		arr[0] = arr[avail--];
		int temp = 0;

		while (true) {
			int l = 2 * temp + 1;
			int r = 2 * temp + 2;
			int par = temp;

			if (l < avail && arr[l] > arr[par]) {
				par = l;
			}

			if (r < avail && arr[r] > arr[par]) {
				par = r;
			}

			if (par != temp) {
				swap(arr[temp], arr[par]);
				temp = par;
			}

			else { break; }
		}
	}
};
