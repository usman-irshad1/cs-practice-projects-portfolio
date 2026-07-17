#pragma once

#include <iostream>
#include<list>
#include<stack>

using namespace std;

int HashKey(string key, int size) {
    int array[] = { 2, 3, 5, 7, 11,13, 17, 19, 23, 29,31, 37, 41, 43, 47,53, 59, 61, 67, 71 };
    unsigned long long value = 0;
    int temp = 0;
    for (int i = 0; i < key.size(); i++) {
        if (i < 12) {
            value += key[i] * array[i];
        }
        else {
            value += key[i] * 32313;
        }
    }

    return value % size;
}

struct HNode {
	string key;
	string data;

    HNode() {}
    HNode(int a, string d) {
        key = a;
        data = d;
    }
};
template <int size>
class hashmap
{
	list<HNode> array[size];

public :
	void insert(string a, string data) {
		int key = HashKey(a,size);

        for (auto it = array[key].begin(); it != array[key].end(); it++) {
            if (it->key == a) {
                it->data = data;
                return;
            }
        }

        array[key].push_front(HNode(a, data));
	}

};

