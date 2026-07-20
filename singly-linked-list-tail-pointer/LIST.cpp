// LIST.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include<list>
#include <algorithm>
#include<vector>
using namespace std;

template <class t>
void mul(t data)  
{
	cout << data << '\t';
}
template <class t>
t mutpliply(t data)
{
	return data /4;
}
int main()
{
	list<int> array;
	array.push_front(1);
	array.push_back(5);
	array.push_back(6);
	array.push_back(9);
	array.push_back(2);

	typename list<int>::iterator temp = array.begin();
	while (temp != array.end()) {

		cout << *temp<<"\t";
		temp++;
	}
	cout << endl;
	typename list<int>::reverse_iterator rtemp = array.rbegin();
	while (array.rend() != rtemp) {
		cout << *rtemp << "\t";
		rtemp++;
	}
	cout << endl;


	typename list<int>::iterator btemp = array.begin();
	while (btemp != array.end()) {
		cout << *btemp << "\t";
		btemp++;
		
	}
	cout << endl;
	while (btemp != array.begin()) {
		btemp--;
		cout << *btemp << "\t";
		
	}
	cout << "\n";
	cout << "Vectors\n";
	vector <int> vector_array;
	vector_array.push_back(5);
	vector_array.push_back(6);
	vector_array.push_back(2);
	vector_array.push_back(2);
	vector_array.push_back(2);
	vector_array.push_back(1);
	vector <int> vector_array1;

	vector_array1.push_back(23);
	vector_array1.push_back(45);
	vector_array1.push_back(24);
	vector_array1.push_back(223);
	vector_array1.push_back(21);
	vector_array1.push_back(135);

	typename vector<int>::iterator vtemp = vector_array.begin();
	
	for (int i = 0; i < vector_array.size(); i++) {
		cout << *vtemp << "\t";
		vtemp++;
	}
	cout << endl;
	sort(vector_array.begin(), vector_array.end());
	vtemp = vector_array.begin();
	for (int i=0 ; i<vector_array.size();i++){
		cout << *vtemp << "\t";
		vtemp++;
	}
	cout << endl;
	int x = 5;
	vtemp=find(vector_array.begin(), vector_array.end(), x);
	if (vtemp != vector_array.end()) {
		cout << *vtemp;
	}
	cout << "\n";
	int c=count(vector_array.begin(), vector_array.end(), 2);
	cout << c << endl;
	vector<int> dest;

	sort(vector_array1.begin(), vector_array1.end());
	sort(vector_array.begin(), vector_array.end());

	merge(vector_array.begin(), vector_array.end(), vector_array1.begin(), vector_array1.end(),back_inserter(dest));
	auto dest_iter = dest.begin();


	
	
	for (int i = 0; i < dest.size(); i++) {
		cout << *dest_iter<<"\t";
		dest_iter++;
	}
	cout << endl;
	for_each(dest.begin(), dest.end(), mul<int>);
	cout << endl;
	vector <float > transform_dest;

	//transform(dest.begin(), dest.end(), back_inserter(transform_dest), mutpliply<float>);
	//for_each(transform_dest.begin(), transform_dest.end(), mul<float>);
	vector <int> vector_array2;
	vector_array2.push_back(2);
	vector_array2.push_back(2);
	vector_array2.push_back(2);

	auto answer=search(dest.begin(), dest.end(), vector_array2.begin(),vector_array2.end());

	if (answer == dest.end()) {
		cout << "Not found";
	}

	else {
		cout << "Found\t";
		for_each(vector_array2.begin(), vector_array2.end(), mul<int>);
	}
}

