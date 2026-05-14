#pragma once

#pragma once
#include <iostream>
#include <list>
#include <queue>
#include <stack>
#include <vector>
#include <string>
#include <functional>
#include <stdexcept>

using namespace std;

// --- Data Structures ---

template <class W>
struct Weighted {
    int index;
    W weight;
    bool operator==(const Weighted& other) const { return index == other.index; }
};

template <class T, class W>
struct Gnode {
    T vertex;
    list<Weighted<W>> Neighbors;
    bool operator==(T v) { return vertex == v; }
};

// --- Main Graph Class ---

template <class T, class W, int size>
class Graph {
    Gnode<T, W> array[size];
    bool directed;
    int Vcount;

public:
    Graph(bool isDirected = false) : directed(isDirected), Vcount(0) {}

    // --- Vertex and Edge Management ---

    void insertVertex(T vertex) {
        if (Vcount < size) {
            array[Vcount].vertex = vertex;
            array[Vcount].Neighbors.clear();
            Vcount++;
        }
    }

    void makeEdge(T startNode, T endNode, W weight) {
        int a = getIndex(startNode);
        int b = getIndex(endNode);

        if (a == -1 || b == -1) return;

        Weighted<W> edgeToB = { b, weight };
        array[a].Neighbors.push_back(edgeToB);

        if (!directed) {
            Weighted<W> edgeToA = { a, weight };
            array[b].Neighbors.push_back(edgeToA);
        }
    }

    void deleteEdge(T data1, T data2) {
        int a = getIndex(data1);
        int b = getIndex(data2);
        if (a == -1 || b == -1) return;

        // Using a dummy weight for the comparison (index-based removal)
        Weighted<W> targetB = { b, W() };
        array[a].Neighbors.remove(targetB);

        if (!directed) {
            Weighted<W> targetA = { a, W() };
            array[b].Neighbors.remove(targetA);
        }
    }

    // --- Search Functions ---

    int getIndex(T label) {
        for (int i = 0; i < Vcount; i++) {
            if (array[i].vertex == label) return i;
        }
        return -1;
    }

    bool searchVertex(T data) {
        return getIndex(data) != -1;
    }

    bool edgeExist(T data1, T data2) {
        int a = getIndex(data1);
        int b = getIndex(data2);
        if (a == -1 || b == -1) return false;

        for (auto const& neighbor : array[a].Neighbors) {
            if (neighbor.index == b) return true;
        }
        return false;
    }

    // --- Traversal Functions ---

    void bfs(T startNode) {
        int startIdx = getIndex(startNode);
        if (startIdx == -1) return;

        bool visited[size] = { false };
        queue<int> q;

        q.push(startIdx);
        visited[startIdx] = true;

        cout << "BFS: ";
        while (!q.empty()) {
            int current = q.front();
            q.pop();
            cout << array[current].vertex << " ";

            for (auto const& neighbor : array[current].Neighbors) {
                if (!visited[neighbor.index]) {
                    visited[neighbor.index] = true;
                    q.push(neighbor.index);
                }
            }
        }
        cout << endl;
    }

    void dfs(T startNode) {
        int startIdx = getIndex(startNode);
        if (startIdx == -1) return;

        bool visited[size] = { false };
        stack<int> s;
        s.push(startIdx);

        cout << "DFS: ";
        while (!s.empty()) {
            int current = s.top();
            s.pop();

            if (!visited[current]) {
                cout << array[current].vertex << " ";
                visited[current] = true;
            }

            for (auto it = array[current].Neighbors.rbegin(); it != array[current].Neighbors.rend(); ++it) {
                if (!visited[it->index]) s.push(it->index);
            }
        }
        cout << endl;
    }

    // --- Shortest Path (Dijkstra) ---

    void shortestPath(T start, T destination) {
        int a = getIndex(start);
        int b = getIndex(destination);
        if (a == -1 || b == -1) return;

        vector<W> dist(Vcount, 1e9);
        vector<int> parent(Vcount, -1);
        dist[a] = 0;

        priority_queue<pair<W, int>, vector<pair<W, int>>, greater<pair<W, int>>> pq;
        pq.push({ 0, a });

        while (!pq.empty()) {
            W d = pq.top().first;
            int u = pq.top().second;
            pq.pop();

            if (d > dist[u]) continue;

            for (auto& edge : array[u].Neighbors) {
                if (dist[u] + edge.weight < dist[edge.index]) {
                    dist[edge.index] = dist[u] + edge.weight;
                    parent[edge.index] = u;
                    pq.push({ dist[edge.index], edge.index });
                }
            }
        }

        if (dist[b] >= 1e9) {
            cout << "No path found." << endl;
        }
        else {
            cout << "Min Weight: " << dist[b] << " | Path: ";
            printPathRecursive(parent, b);
            cout << endl;
        }
    }

    // --- Utility Functions ---

    void printPathRecursive(const vector<int>& parent, int j) {
        if (parent[j] == -1) {
            cout << array[j].vertex;
            return;
        }
        printPathRecursive(parent, parent[j]);
        cout << " -> " << array[j].vertex;
    }

    void display() {
        for (int i = 0; i < Vcount; i++) {
            cout << "[" << array[i].vertex << "] -> ";
            for (auto& n : array[i].Neighbors) {
                cout << "(" << array[n.index].vertex << ", w:" << n.weight << ") ";
            }
            cout << endl;
        }
    }

    int getVertexCount() { return Vcount; }
    bool isEmpty() { return Vcount == 0; }
};

