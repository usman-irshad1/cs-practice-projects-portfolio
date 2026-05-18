#include <iostream>
#include <algorithm>
#include <list>
#include <stack>
#include <utility>
#include <queue>
#include <map>
#include <string>
#include<unordered_map>

using namespace std;

struct Node {
    int data;
    Node* left, * right;
    Node() : data(0), left(nullptr), right(nullptr) {}
};

class BinaryTree {
    Node* root;
public:
    BinaryTree() : root(nullptr) {}
    void insert(int data) {
        if (root == nullptr) {
            root = new Node();
            root->data = data;
            return;
        }
        Node* temp = root;
        while (temp != nullptr) {
            if (temp->data < data) {
                if (temp->right == nullptr) {
                    temp->right = new Node();
                    temp->right->data = data;
                    return;
                }
                temp = temp->right;
            }
            else if (temp->data > data) {
                if (temp->left == nullptr) {
                    temp->left = new Node();
                    temp->left->data = data;
                    return;
                }
                temp = temp->left;
            }
            else { return; }
        }
    }

    Node* deleteNode(Node* temp, int data) {
        if (temp == nullptr) { return temp; }
        if (temp->data < data) {
            temp->right = deleteNode(temp->right, data);
        }
        else if (temp->data > data) {
            temp->left = deleteNode(temp->left, data);
        }
        else {
            if (temp->left == nullptr) {
                Node* t = temp->right;
                delete temp;
                return t;
            }
            else if (temp->right == nullptr) {
                Node* t = temp->left;
                delete temp;
                return t;
            }
            Node* t = temp->left;
            while (t->right != nullptr) {
                t = t->right;
            }
            temp->data = t->data;
            // Removed t->data = data; to follow recursive deletion logic
            temp->left = deleteNode(temp->left, t->data);
        }
        return temp;
    }

    void dNode(int data) {
        root = deleteNode(root, data);
    }

    void printInorder(Node* temp) {
        if (temp == nullptr) { return; }
        printInorder(temp->left);
        cout << temp->data << " ";
        printInorder(temp->right);
    }

    void printPreorder(Node* temp) {
        if (temp == nullptr) { return; }
        cout << temp->data << " ";
        printPreorder(temp->left);
        printPreorder(temp->right);
    }

    void printPostOrder(Node* temp) {
        if (temp == nullptr) { return; }
        printPostOrder(temp->left);
        printPostOrder(temp->right);
        cout << temp->data << " ";
    }
};

struct Pnode {
    int data;
    Pnode* next;
    Pnode() : data(0), next(nullptr) {}
};

class PriorityQueue {
    Pnode* head;
public:
    PriorityQueue() : head(nullptr) {}

    void insert(int data) {
        if (head == nullptr) {
            Pnode* temp = new Pnode();
            head = temp;
            head->data = data;
            return;
        }
        else {
            Pnode* temp = head;
            while (temp->next != nullptr) {
                if (temp->data > data) {
                    break;
                }
                else { temp = temp->next; }
            }
            if (head->data > data) {
                Pnode* newNode = new Pnode();
                newNode->data = data;
                newNode->next = head;
                head = newNode;
                return;
            }
            Pnode* newNode = new Pnode();
            newNode->data = data;
            newNode->next = temp->next;
            temp->next = newNode;
        }
    }

    void deleteNode(int data) {
        if (head == nullptr) { return; }
        if (head->data == data) {
            Pnode* toDelete = head;
            head = head->next;
            delete toDelete;
            return;
        }
        Pnode* temp = head;
        while (temp->next != nullptr) {
            if (temp->next->data == data) {
                Pnode* n = temp->next;
                temp->next = temp->next->next;
                delete n;
                return;
            }
            temp = temp->next;
        }
    }

    void getFront() {
        if (head == nullptr) {
            cout << "Queue is empty\n";
            return;
        }
        cout << head->data << endl;
    }
};

template <class t>
void print(t data) {
    cout << data << "\t";
}

template <class t>
t divideBy16(t data) { // Renamed from div to avoid std::div conflict
    return data / 16;
}

template <class t>
class LIST : public list<t> {
public:
    void display() {
        for_each(this->begin(), this->end(), print<t>);
    }
    void add(t data) { this->push_front(data); }
    void remove(t data) {
        for (auto it = this->begin(); it != this->end(); it++) {
            if (*it == data) {
                this->erase(it);
                break;
            }
        }
    }
    typename LIST<t>::iterator search(t data) {
        for (auto it = this->begin(); it != this->end(); it++) {
            if (*it == data) { return it; }
        }
        return this->end();
    }
};

template <class t>
struct Hnode {
    t data;
    friend ostream& operator<<(ostream& os, const Hnode& node) {
        os << node.data;
        return os;
    }
};

template <class t>
void printer(Hnode<t> d) {
    cout << d.data << "\t";
}

template <class t, int s>
class DhashTable {
    int size;
    list<Hnode<t>>* table;
    int elements;
public:
    DhashTable() : size(s), elements(0) {
        table = new list<Hnode<t>>[size];
    }

    int hashFunction(t key, int tableSize) {
        return (int)key % tableSize;
    }

    void insert(t data) {
        rehash();
        int index = hashFunction(data, size);
        Hnode<t> temp;
        temp.data = data;
        elements++;
        table[index].push_front(temp);
    }

    void snap(t data) {
        int index = hashFunction(data, size);
        for (auto it = table[index].begin(); it != table[index].end(); it++) {
            if (it->data == data) {
                table[index].erase(it);
                elements--;
                cout << "Deleted\n";
                return;
            }
        }
    }

    void rehash() {
        if ((float)elements / size < 0.6) { return; }
        cout << "Rehashing\n";
        int nsize = size * 7;
        list<Hnode<t>>* newTable = new list<Hnode<t>>[nsize];
        for (int i = 0; i < size; i++) {
            for (auto it = table[i].begin(); it != table[i].end(); it++) {
                int newIndex = hashFunction(it->data, nsize);
                newTable[newIndex].push_front(*it);
            }
        }
        delete[] table;
        table = newTable;
        size = nsize;
    }

    ~DhashTable() { delete[] table; }

    void display() {
        for (int i = 0; i < size; i++) {
            cout << "Index = " << i << ": ";
            for_each(table[i].begin(), table[i].end(), printer<t>);
            cout << endl;
        }
    }
};

template <class t>
struct Neighbor {
    t name;
    int weight;
    Neighbor(t n, int w) : name(n), weight(w) {}
    bool operator==(const t& otherData) const { return name == otherData; }
};

template <class t>
struct GraphNode {
    t data;
    list<Neighbor<t>> neighbors;
    GraphNode() : data(t()) {}
    bool operator==(const t& otherData) const { return data == otherData; }
};

template <class t, int size>
class Graph {
    int count;
    GraphNode<t> Vertex[size];
    bool directed;

public:
    Graph(bool f) : count(0), directed(f) {
        for (int i = 0; i < size; i++) {
            Vertex[i] = GraphNode<t>();
        }
    }

    int getVertex(t data) {
        for (int i = 0; i < count; i++) {
            if (Vertex[i].data == data) return i;
        }
        return -1;
    }

    void addVertex(t data) {
        for (int i = 0; i < count; i++) {
            if (Vertex[i].data == data) { cout << "The vertex already exists"; return; }
        }
        Vertex[count].data = data;
        count++;
    }

    void add_edge(t data, t data2, int distance = 0) {
        int i1 = getVertex(data);
        int i2 = getVertex(data2);
        if (i1 == -1 || i2 == -1) return;

        Vertex[i1].neighbors.push_back(Neighbor<t>(data2, distance));
        if (!directed) {
            Vertex[i2].neighbors.push_back(Neighbor<t>(data, distance));
        }
    }

    void deleteEdge(t data, t data2) {
        int i1 = getVertex(data);
        int i2 = getVertex(data2);
        if (i1 == -1 || i2 == -1) return;

        Vertex[i1].neighbors.remove(data2);
        if (!directed) {
            Vertex[i2].neighbors.remove(data);
        }
        cout << "The edge has been deleted\n";
    }

    void shortestPath(t d, t target) {
        int index = getVertex(d);
        if (index == -1) return;

        int distances[size];
        for (int i = 0; i < size; i++) distances[i] = 1000000;
        distances[index] = 0;

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.push({ 0, index });

        while (!pq.empty()) {
            int dist = pq.top().first;
            int u = pq.top().second;
            pq.pop();

            if (dist > distances[u]) continue;

            for (auto& neighbor : Vertex[u].neighbors) {
                int v = getVertex(neighbor.name);
                if (distances[u] + neighbor.weight < distances[v]) {
                    distances[v] = distances[u] + neighbor.weight;
                    pq.push({ distances[v], v });
                }
            }
        }
        cout << "Shortest Path to " << target << ": " << distances[getVertex(target)] << endl;
    }

    void BFS(t start) {
        int index = getVertex(start);
        if (index == -1) return;
        queue<int> q;
        bool visited[size] = { false };
        q.push(index);
        visited[index] = true;

        while (!q.empty()) {
            int curr = q.front();
            q.pop();
            cout << Vertex[curr].data << " ";
            for (auto& n : Vertex[curr].neighbors) {
                int next = getVertex(n.name);
                if (!visited[next]) {
                    visited[next] = true;
                    q.push(next);
                }
            }
        }
        cout << endl;
    }

    void DFS(t start) {
        int index = getVertex(start);
        if (index == -1) return;
        stack<int> s;
        bool visited[size] = { false };
        s.push(index);
        visited[index] = true;

        while (!s.empty()) {
            int curr = s.top();
            s.pop();
            cout << Vertex[curr].data << " ";
            for (auto& n : Vertex[curr].neighbors) {
                int next = getVertex(n.name);
                if (!visited[next]) {
                    visited[next] = true;
                    s.push(next);
                }
            }
        }
        cout << endl;
    }

    void printVertex() {
        for (int i = 0; i < count; i++) cout << Vertex[i].data << endl;
    }


    bool checkCycle() {
		bool visited[size] = { false };
        if (count == 0) return false;
		visited[0] = true;
        for (int i = 0; i < count; i++) {
            for (auto it = Vertex[i].neighbors.begin(); it != Vertex[i].neighbors.end(); ++it) {
                int neighborIndex = getVertex(it->name);
                if (visited[neighborIndex]) {
                    cout << "Cycle detected!" << endl;
                    return true;
                }
            }
        }
        retur false;
    }


    void KruskalAlgo_sppaning_gargh() {
        int distance = 10000000000;
		int index1 = -1, index2 = -1;x  
		Graph <int, 5> mst(false);
        for (int i = 0; i < count; i++) {
            mst.addVertex(Vertex[i].data);
        }
        while (mst.checkCycle() == false) {
            for (int i = 0; i < count; i++) {
                for (auto it = Vertex[i].neighbors.begin(); it != Vertex[i].neighbors.end(); ++it) {
                    if (it->weight < distance) {
                        index1 = i;
                        index2 = getVertex(it->name);
                        distance = it->weight;
                    }
                }
                mst.add_edge(Vertex[index1].data, Vertex[index2].data, distance);
                mst.checkCycle();

            }
        }
};

struct Enode {
    char x;
    int f;
    Enode* left, * right;
    Enode(char t = '*') : x(t), f(0), left(nullptr), right(nullptr) {}
};

struct compare {
    bool operator()(Enode* a, Enode* b) { return a->f > b->f; }
};

class Huffman {
    priority_queue<Enode*, vector<Enode*>, compare> array;
    Enode* root;

public:
    Huffman() : root(nullptr) {}
    void frequency_list(string s) {
        map<char, int> freq;
        for (char c : s) freq[c]++;
        for (auto const& [ch, f] : freq) {
            Enode* temp = new Enode(ch);
            temp->f = f;
            array.push(temp);
        }
    }

    void buildtree(string tree) {
        frequency_list(tree);
        if (array.empty()) return;
        while (array.size() > 1) {
            Enode* left = array.top(); array.pop();
            Enode* right = array.top(); array.pop();
            Enode* parent = new Enode('*');
            parent->left = left;
            parent->right = right;
            parent->f = left->f + right->f;
            array.push(parent);
        }
        root = array.top();
    }

    void decrypt(string x) {
        if (!root) return;
        Enode* temp = root;
        for (char c : x) {
            if (c == '0') temp = temp->left;
            else temp = temp->right;
            if (!temp->left && !temp->right) {
                cout << temp->x;
                temp = root;
            }
        }
        cout << endl;
    }
    void code(string current_path, Enode* temp) {
        if (temp == nullptr) { return; }
        if (temp->left == nullptr && temp->right == nullptr) {
            cout << temp->x << ": " << current_path << endl;
            return;
        }
        code(current_path + '0', temp->left);
        code(current_path + '1',  temp->right);
    }
    void key() {
		code("", root);
    }



};




struct TrieNode {

    bool is_word;
    unordered_map <char, TrieNode*> children;

    TrieNode() { is_word = false; }
};

class Trie {

    TrieNode* root;
public:
    Trie() { root = new TrieNode(); }

    void insert(string data) {
        TrieNode* temp = root;
        for (int i = 0; i < data.size(); i++) {
            if (temp->children.find(data[i]) == temp->children.end()) {
                temp->children[data[i]] = new TrieNode();
            }
            temp = temp->children.at(data[i]);
        }
        temp->is_word = true;
    }

    void Search(string data) {
        TrieNode* temp = root;

        for (int i = 0; i < data.size(); i++) {
            
                
           
            if (temp->children.find(data[i]) == temp->children.end()) {
				cout << "the word does not exist in the trie\n";
                return;
            }
            temp = temp->children.at(data[i]);
			
        }
        if (temp->is_word == false) {
            cout << "The word does not exist in the trie\n";
        }
    }


    void PrintWordsfromprefix(string data) {

        TrieNode* temp = root;
        string p = "";
        for (int i = 0; i < data.size(); i++) {
            if (temp->children.find(data[i]) != temp->children.end()) {
                temp = temp->children.at(data[i]);
                p += data[i];
            }
			else {
				cout << "No words with the given prefix\n";
				return;
			}
        }

        printAllPrefixes(temp, p);

    }

    void printAllPrefixes(TrieNode* temp, string x) {
        if (temp->is_word) {
            cout << x << " \n";
        }
        for (auto it = temp->children.begin(); it != temp->children.end(); ++it) {
        printAllPrefixes(it->second, x + it->first);
        }
    }

	void countWords() {
		int count = 0;
		countingwords(root, count);
		cout << "Total words in the trie: " << count << endl;
	}

    void countingwords(TrieNode* temp, int& count) {

        if (temp->is_word) {
            count++;
        }

        for (unordered_map<char, TrieNode*> ::iterator it = temp->children.begin(); it != temp->children.end(); it++) {
            countingwords(it->second, count);
        }

    }

    void clear(TrieNode* temp) {
    for (auto it = temp->children.begin(); it != temp->children.end(); ++it) {
        clear(it->second);
    }
    delete temp;
    }
    ~Trie() {
        clear(root);
    }


    void deleteWord(string word) {


    }

    bool deleting(TrieNode* temp, string word, int index) {
        if (temp == nullptr) return false;
        if (index == word.size()) {
            temp->is_word = false;

        
        return (temp->children.empty());
        }
        
        char x = word[index];

        if (temp->children.find(x) == temp->children.end()) {
            return false;
        }

       bool check= deleting(temp->children[x], word, index + 1);

       if (check) {
           delete temp->children.at(x);
           temp->children.erase(x);
           return (!temp->is_word && temp->children.empty());
       }
       return false;
    }


   
};


int main() {
    Huffman h;
    string original = "ayesha";
    h.buildtree(original);
    h.key();
    string encoded = "000101011010";
    cout << "Decoding " << encoded << ": ";
    
    h.decrypt(encoded);

    DhashTable<int, 2> myHash;
    myHash.insert(10);
    myHash.insert(20);
    myHash.insert(30);
    myHash.display();

    Graph<string, 5> g(false);
    g.addVertex("Lahore");
    g.addVertex("Karachi");
    g.addVertex("Islamabad");
    g.add_edge("Lahore", "Karachi", 1200);
    g.add_edge("Lahore", "Islamabad", 300);
    cout << "Graph Vertices:" << endl;
    g.printVertex();

    return 0;
}