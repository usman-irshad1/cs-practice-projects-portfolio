// practice9679.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include<list>
#include<algorithm>
#include<stack>
#include<queue>
#include<utility>
#include<map>
#include<unordered_map>
using namespace std;

template <class t>
void view(t data) {
    cout << data << "\t";
}
template <class t>
t add(t data) {
    return data * 52;
}


template <class t>
class List :public list<t> {
public:

    void insert_data(t data) {
        this->push_back(data);
    }
    void display() {
        for (typename List<t>::iterator it = this->begin(); it != this->end(); it++) {
            cout << *it << "\t";
        }
        cout << endl;
    }
    void see() {
        for_each(this->begin(), this->end(), view<t>);
    }


    List<t> magic() {
        List<t> f;
        transform(this->begin(), this->end(), back_inserter(f), add<t>);
        f.display();
        return f;
    }

    void order() {
        this->sort();
    }


    List<t> merging(List<t> x){
        List<t> y;
        merge(this->begin(), this->end(), x.begin(), x.end(), back_inserter(y));
        y.display();
        return y;
    }

    void hide_and_seek(auto begin , auto end ,t data){
        typename List<t> ::iterator it =find(begin, end, data);
        if (it == this->end()) {
            cout << "Not found";
            return;
        }
        else {
            cout << "Found\n";
            it++;
            hide_and_seek(it, end, data);
        }
    }

    int counting_heads(t data) {
       return count(this->begin(), this->end(), data);
    
    }

    void pattren_matching(List<t> spare) {
       auto temp= search(this->begin(), this->end(), spare.begin(), spare.end());
       if (temp != this->end()) {
           cout << endl;
           spare.display();
               cout<< "exsists in the list" << endl;
          
       }
       else {
           cout << "false";
       
       }
    }

    ~List() {
        if (this->size() > 10) { return; }
        while (this->size() != 0) {

            this->pop_back();
        }
    
    }
};


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


struct Hnode {
    string key;
    string data;
    Hnode(string x, string y){
        key = x;
        data = y;
    }

};

template <int size>
class HashMap {
    list<Hnode> map[size];
public:
    void insert(string key, string data) {
        int index = HashKey(key, size);
        for (typename list<Hnode>::iterator it = map[index].begin(); it != map[index].end(); it++) {
            if (key == it->key) {
                it->data = data;
                return;
            }
        }
        map[index].push_back(Hnode(key, data));
        }
        

    void search(string key) {
        int index = HashKey(key, size);
        bool found = false;
        for (typename list<Hnode> ::iterator it = map[index].begin(); it != map[index].end(); it++) {
            if (it->key == key) {
                cout << it->data;
                found = true;

            }
        
        }
    
        if (!found) { cout << "Not in Hash Table"; }
    }
    };



struct Weighted {

    int weight;
    int index;
    Weighted() {}
    Weighted(int a, int b) {
        index = a;
        weight = b;

    }
};


template <class t>
struct Gnode {
    t vertex;
    list<Weighted> neighbours;
    Gnode(){    }
    Gnode(t v) {
        vertex = v;
    }
};

template<class t , int size>
class Graph {
    Gnode<t> array[size];
    int count;
public:
    Graph() {
        count = 0;
    }


    int get_index(t vertex) {

        for (int i = 0; i < count; i++) {
            if (array[i].vertex == vertex) {
                return i;
            }
        }
        return -1;
    }

    void insertVertex(t vertex) {

        if (get_index(vertex) == -1) {
            array[count] = Gnode<t>(vertex);
            count++;
            cout << "Successfull insertion";
        }
        else {
            cout << "Already inserted";
        }

    }

    void insertEdge(t vertex, t vertex2, int distance) {

        int a = get_index(vertex);
        int b = get_index(vertex2);
        array[a].neighbours.push_back(Weighted(b, distance));
        array[b].neighbours.push_back(Weighted(a, distance));

    }


    void dfs()
    {
        if (count <= 0) { return; }
        stack<int> holder;
        bool visited[size] = { false };
        int start = get_index(array[0].vertex);
        visited[0] = true;
        holder.push(start);
        while (holder.size() != 0) {
            int index = holder.top();
            cout << array[index].vertex << "t";
            holder.pop();
            for (typename list<Weighted>::iterator temp = array[index].neighbours.begin(); temp != array[index].neighbours.end(); temp++) {
                if (visited[temp->index] != true) {
                    holder.push(temp->index);
                    visited[temp->index] = true;
                }

            }
        
        }
    }

    void bfs() {
        queue<int> holder;
        bool visited[size] = { false };
        int start = get_index(array[0].vertex);
        visited[start] = true;
        holder.push(start);
        while (!holder.empty()) {
            int index = holder.front();
            cout << array[index].vertex<<"t";
            holder.pop();
            for (typename list<Weighted>::iterator it = array[index].neighbours.begin(); it != array[index].neighbours.end(); it++) {
                if (!visited[it->index]) {
                    holder.push(it->index);
                    visited[it->index] = true;

                }
                
            }
        }
    
    }
};

int main()
{
//    list<pair<int, string>> holder;
//
//
//    holder.push_back({ 1,"apple" });
//    holder.push_back({ 2 ,"orange" });
//    holder.push_back({ 3,"pineapple" });
//    holder.push_back({ 4,"banana" });
//
//
//    for (list<pair<int, string>>::iterator it = holder.begin(); it != holder.end(); it++) {
//        cout << it->first << "\t" << it->second << endl;
//
//    }


    map<int, int> mapper;
    mapper[5] = 23;
    mapper[6] = 223;
    mapper[10] = 223;
    mapper[8] = 25;
    mapper[9] = 21;
    map<int, int, greater<int>> mapper2;
    mapper2[5] = 23;
    mapper2[6] = 223;
    mapper2[10] = 223;
    mapper2[8] = 25;
    mapper[9] = 21;

   map<int, int>::iterator temp= mapper.find(5);
   //if (temp != mapper.end()) {
   //    cout << temp->first << "\t" << temp->second;
   //}
   //else { cout << "Not found"; }


   temp = mapper.begin();
   while (temp != mapper.end()) {
       cout << temp->first << "\t" << temp->second << endl;
       temp++;
   }
   cout << endl;
   temp = mapper2.begin();
   while (temp != mapper2.end()) {
       cout << temp->first << "\t" << temp->second << endl;
       temp++;
   }
   
   cout << endl;
   unordered_map<int, int> mapper3;

   mapper3.insert({ 4,23456 });
   mapper3[5] = 23;
   mapper3[6] = 223;
   mapper3[10] = 223;
   mapper3[8] = 25;
   mapper3[9] = 21;

  auto temp1 = mapper3.begin();
   while (temp1 != mapper3.end()) {
       cout << temp1->first << "\t" << temp1->second << endl;
       temp1++;
   }
   // List<int> row;

   // row.insert_data(5);
   // row.insert_data(6);
   // row.insert_data(7);
   // row.insert_data(3);
   // row.insert_data(2);
   // row.insert_data(1);
   // row.display();
   // row.see();
   // cout << endl;
   // List<int> column=row.magic();
   // row.order();
   // column.order();
   // column.see();
   // cout << endl;
   // row.see();
   // cout << endl;
   // List<int> matrix=row.merging(column);
   // matrix.hide_and_seek(matrix.begin(), matrix.end(), 5);
   //cout<< endl<<matrix.counting_heads(5);

   //matrix.pattren_matching(row);
    //std::cout << "Hello World!\n";
}

