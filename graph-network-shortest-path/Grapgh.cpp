#include <iostream>
#include <list>
#include <queue>
using namespace std;

struct NODE {
    int vertex;
    std::list<int> node;
};

template <int size>
class adjencyList {
    NODE LIST[size];
    int vcount;

public: // Added public access so main() can reach these
    adjencyList() {
        vcount = size;
        for (int i = 0; i < size; i++) {
            LIST[i].vertex = i;
        }
    }

    bool isEmpty() {
        return vcount == 0;
    }

    int getvCount() {
        return vcount;
    }

    int geteCount() {
        int count = 0;
        for (int i = 0; i < vcount; i++) {
            count += LIST[i].node.size();
        }
        return count / 2;
    }

    int search(int v) {
        for (int i = 0; i < vcount; i++) {
            if (LIST[i].vertex == v) 
                return i;
        }
        return -1;
    }

    bool edgeExist(int v1, int v2) {
        int loc = search(v1);
        if (loc != -1) {
            list<int>::iterator temp = LIST[loc].node.begin();
            while (temp != LIST[loc].node.end()) {
                if (*temp == v2)
                    return true;
                temp++;
            }
        }
        return false;
    }

    void addEdge(int u, int v) {
        if (edgeExist(u, v)) { return; }
        int a = search(u);
        int b = search(v);
        if (a == -1 || b == -1) {
            return;
        }
        if (a< size && b< size && !edgeExist(u, v)) {
            LIST[a].node.push_back(b);
            LIST[b].node.push_back(a);
        }
    }
    void deleteEdge(int u, int v) {
        if (!edgeExist(u, v)) { return; }
        int a = search(u);
        int b = search(v);
        if (a == -1 || b == -1) {
            return;
        }
            LIST[a].node.remove(b);
            LIST[b].node.remove(a);
    }

    void deleteVertx(int z) {
        int a = search(z);
        for (int i = 0; i < size; i++) {
            if (LIST[i].vertex != -1) {
                deleteEdge(z, LIST[i].vertex);
            }
        }
        LIST[a].vertex = -1;
        vcount--;
    }

    void bfs() {
        
        int startNode = search(0);
        if (startNode == -1) return;
        bool visited[size] = { false };
        queue<int> q;
        visited[startNode] = true;
        q.push(startNode);

        while (!q.empty()) {
            int current = q.front();
            cout << LIST[current].vertex << "\t";
            q.pop();
            typename list<int> ::iterator x = LIST[current].node.begin();
            while (x != LIST[current].node.end()) {
                int neighborIdx = search(*x);
                x++;
                if (neighborIdx != -1 && visited[neighborIdx]==false) {
                    visited[neighborIdx] = true;
                    q.push(neighborIdx);
                }
            }
        }
    }


};

int main() {
    adjencyList<5> myGraph;

    myGraph.addEdge(0, 1);
    myGraph.addEdge(1, 2);

   
    myGraph.bfs();

    return 0;
}