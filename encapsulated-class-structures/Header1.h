#pragma once
#include <iostream>
#include<list>
#include<stack>
#include<queue>


using namespace std;
struct weighted {
    int index;
    int weight;
    bool operator==(const weighted& other) const {
        return index == other.index;
    }
};
template <class t>
struct Gnode {
    t vertex;
    list<weighted> Neighbors;
    bool operator==(t v) {
        return vertex == v;
    }
};

template <class t, int size>
class Graph {
    int Vcount;
    Gnode<t> array[size];
    bool directed;
public:
    Graph() {
        Vcount = 0;
        directed = false;
    }
    Graph(bool x) {
        Vcount = 0;
        directed = x;
    }

    void bfs() {
        if (Vcount <= 0) { return; }
        int visited[size] = { 0 };
        queue<int> adjacent;
        int starting = getIndex(array[0].vertex);
        adjacent.push(starting);
        visited[starting] = 1;

        while (!adjacent.empty()) {
            int top = adjacent.front();
            cout << array[top].vertex << "\t";
            adjacent.pop();

            typename list<weighted>::iterator temp = array[top].Neighbors.begin();
            while (temp != array[top].Neighbors.end()) {
                int neighborIndex = temp->index;
                if (visited[neighborIndex] != 1) {
                    visited[neighborIndex] = 1;
                    adjacent.push(neighborIndex);
                }
                temp++;
            }
        }
        cout << endl;
    }
    void insertVertex(t vertex) {
        if (Vcount < size) {
            array[Vcount].vertex = vertex;
            Vcount++;
        }
        else { return; }
    }


    void makeEdge(int a, int b, int w = 1) {
        if (!directed) {
            if (a < size && b < size && a >= 0 && b >= 0) {
                weighted tempA = { b, w };
                weighted tempB = { a, w };
                array[a].Neighbors.push_back(tempA);
                array[b].Neighbors.push_back(tempB);
            }
        }
        else {
            if (a < size && b < size && a >= 0 && b >= 0) {
                weighted tempA = { b, w };
                array[a].Neighbors.push_back(tempA);
            }
        }
    }
    int getIndex(t label) {
        for (int i = 0; i < Vcount; i++) {
            if (array[i].vertex == label) return i;
        }
        return -1; // Not found
    }

    int getVertex() {
        return Vcount;
    }



    bool isEmpty() {
        return Vcount <= 0;
    }



    int No_of_indexes_btw_2_vertices(t data, t data2) {
        int a = getIndex(data);
        int b = getIndex(data2);
        int links = 0;
        if (a == -1 || b == -1) { return 0; }

        typename list<weighted>::iterator temp = array[a].Neighbors.begin();
        typename list<weighted>::iterator temp1 = array[b].Neighbors.begin();
        while (temp != array[a].Neighbors.end()) {
            if (temp->index == b) {
                links++;
            }
            temp++;
        }
        while (temp1 != array[b].Neighbors.end()) {
            if (temp1->index == a) {
                links++;
            }
            temp1++;
        }if (!directed) {
            return links / 2;
        }
        else {
            return links;
        }
    }
    void DeleteEdge(t data1, t data2) {
        int a = getIndex(data1);
        int b = getIndex(data2);
        if (a == -1 || b == -1) return;


        weighted B = { b, 0 };
        weighted A = { a, 0 };

        if (!directed) {
            array[a].Neighbors.remove(B);
            array[b].Neighbors.remove(A);
        }
        else {
            array[a].Neighbors.remove(B);
        }

        cout << "\t\t\t\t\t\tDeleted\n";
    }
    void DeleteVertex(t data) {
        int index = getIndex(data);
        if (index == -1) return;
        weighted d = { index, 0 };

        for (int i = 0; i < Vcount; i++) {
            array[i].Neighbors.remove(d);
        }

        for (int i = index; i < Vcount - 1; i++) {
            array[i] = array[i + 1];
        }

        Vcount--;

        for (int i = 0; i < Vcount; i++) {
            typename list<weighted>::iterator it = array[i].Neighbors.begin();
            while (it != array[i].Neighbors.end()) {
                if (it->index > index) {
                    it->index = it->index - 1;
                }
                it++;
            }
        }
    }

    void dfs() {
        stack<int> holder;
        bool visited[size] = { false };
        t data = array[0].vertex;
        int start = getIndex(data);
        holder.push(start);
        visited[start] = true;

        while (!holder.empty()) {
            int index = holder.top();
            cout << array[index].vertex << "\t";
            holder.pop();
            typename list<weighted>::iterator temp = array[index].Neighbors.begin();
            while (temp != array[index].Neighbors.end()) {
                if (visited[temp->index] == false) {
                    holder.push(temp->index);
                    visited[temp->index] = true;
                }
                temp++;
            }

        }
    }



    bool edgeExist(t data1, t data2) {
        int a = getIndex(data1);
        int b = getIndex(data2);
        if (a == -1 || b == -1) { return false; }

        typename list<weighted>::iterator temp = array[a].Neighbors.begin();
        while (temp != array[a].Neighbors.end()) {
            if (b == temp->index) {
                return true;
            }
            temp++;
        }
        return false;
    }

    int No_Of_Edges() {
        int edges = 0;
        for (int i = 0; i < Vcount; i++) {
            typename list<weighted>::iterator temp = array[i].Neighbors.begin();
            while (temp != array[i].Neighbors.end()) {
                edges++;
                temp++;
            }
        }
        if (!directed) {
            return edges / 2;
        }
        else {
            return edges;
        }
    }



    Graph minimumSpanningtree() {
        Graph<t, size> result;
        for (int i = 0; i < Vcount; i++) {
            result.insertVertex(array[i].vertex);
        }
        bool visited[size] = { false };
        visited[0] = true;
        for (int edges = 0; edges < Vcount - 1; edges++) {
            int minimum = 100000;
            int start = -1;
            int end = -1;
            for (int i = 0; i < Vcount; i++) {// checking  every node for the least wighted link that does not make a cycle
                if (visited[i] == true) {
                    typename list<weighted>::iterator temp = array[i].Neighbors.begin();
                    while (temp != array[i].Neighbors.end()) {
                        if (temp->weight < minimum && visited[temp->index] == false) {
                            minimum = temp->weight;
                            start = i;
                            end = temp->index;
                        }
                        temp++;
                    }

                }

            }
            if (end != -1) {
                visited[end] = true;
                result.makeEdge(start, end, minimum);
                cout << "Inserting link btw " << start << "\t" << end << "\t" << "for a weight of " << minimum << endl;
            }
        }
        return result;

    }


    void Shortest_Link_btw_two_vertices(t data, t data1) {
        int a = getIndex(data);
        int b = getIndex(data1);
        bool direct = false;
        typename list<weighted>::iterator temp = array[a].Neighbors.begin();
        int min = 100000;
        int index = -1;
        while (temp != array[a].Neighbors.end()) {
            if (b == temp->index) {
                if (temp->weight < min) {
                    min = temp->weight;
                    index = temp->index;
                    direct = true;
                }

            }
            temp++;
        }
        if (direct) {
            cout << "The minimum distance between the vertes" << data << "\t" << data1 << "\t" << "is \t" << min;
        }
        else {
            cout << "No direct link";
        }
    }

    void shortest_Path_btw2_vericex(t data, t data2) {

        int a = getIndex(data);//starting index
        int b = getIndex(data2);//target
        int distance[size];
        bool visited[size];
        int indexes[size];
        for (int i = 0; i < size; i++) {

            distance[i] = 1000000000;
            visited[i] = false;
            indexes[i] = -1;
        }


        distance[a] = 0;
        for (int i = 0; i < size; i++) {
            int nextNode = -1;
            int min = 1000000000;
            for (int j = 0; j < size; j++) {
                if (distance[j] < min && visited[j] == false) {
                    min = distance[j];
                    nextNode = j;
                }
            }
            if (nextNode == -1) {
                cout << "Path does not exist"; break;
            }
            else if (nextNode == b) {
                cout << "Distance reached";
                break;
            }
            else {
                visited[nextNode] = true;
            }

            for (auto it = array[nextNode].Neighbors.begin(); it != array[nextNode].Neighbors.end(); ++it) {
                int v = it->index;
                int weight = it->weight;

                if (!visited[v] && distance[nextNode] + weight < distance[v]) {
                    distance[v] = distance[nextNode] + weight;
                    indexes[v] = nextNode;
                }
            }
           
        }

        int current = b;
        int path[size];
        int count = 0;
        while (current != -1) {
            path[count] = current;
            count++;
            current = indexes[current];
        }
        cout << "\n\nShortest path\n";
        for (int i = count - 1; i >= 0; i--) {
            int nodeIndex = path[i];
            cout << array[nodeIndex].vertex << "\t";
        }
        cout << "\nTotal Travel Cost: " << distance[b] << " units" << endl;
    }

    bool searchVertex(t data) {
        return getIndex(data) != -1;
    }

    int getDegree(t data) {
        int a = getIndex(data);
        int degree = 0;
        typename list<weighted> ::iterator temp = array[a].Neighbors.begin();
        if (a == -1) { cout << "\nVertex does not exist \n"; return -1; }
        degree = array[a].Neighbors.size();
        cout << "\nThe degree of the vertex " << data << " is " << degree << endl;
        return degree;
    }

    void Type() {
        if (directed) {
            cout << "\nThe graph is Directed\n";
        }
        else {
            cout << "\nThe graph is Undirected\n";
        }
    }

    void display_edge_of_index(string s) {
        int index = getIndex(s);
        if (index == -1) { cout << "\nAirport not found.\n"; return; } // Safety
        typename list<weighted>:: iterator temp= array[index].Neighbors.begin();
        cout << "\nThe vertex ";
        cout << array[index].vertex<< " has links to \n";
        while (temp != array[index].Neighbors.end()) {
            cout << array[temp->index].vertex<<"\t";
            temp++;
        }

    }
    void Incoming(t target) {
        if (!directed) { return; }
        int targetIdx = getIndex(target);
        if (targetIdx == -1) return;

        cout << "Incoming flights to " << target << ":" << endl;
        for (int i = 0; i < Vcount; i++) {
            typename list<weighted>::iterator temp = array[i].Neighbors.begin();
            while (temp != array[i].Neighbors.end()) {
                if (temp->index == targetIdx) {
                    cout << array[i].vertex << "\t";
                }
                temp++;
            }

        }
    }
};



