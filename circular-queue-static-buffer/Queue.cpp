// Queue.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std;
template<class t >
struct node {
    t data;
    node<t>* left;
    node<t>* right;
    node():data(t()), left(nullptr) , right(nullptr) {}
    node(t d):data(d), left(nullptr), right(nullptr) {}
};

template<class t >
class Tree{
    node<t>* root;
    node<t>* insert(node<t>* n, t data) {
        if (n == nullptr) { return n = new node<t>(data); }
        else if (n->data < data) { n->right=insert(n->right, data); }
        else if (n->data > data) {n->left= insert(n->left, data); }
         return n; 
    }


 


public:
    Tree() { root = nullptr; }
    void insertNode( t data) {
        root=insert(root, data);
    }

private:
    // Sorted Order (Left, Root, Right)
    void inOrder(node<t>* n) {
        if (n == nullptr) return;
        inOrder(n->left);
        cout << n->data << " ";
        inOrder(n->right);
    }

public:
    void displaySorted() {
        cout << "In-Order (Sorted): ";
        inOrder(root);
        cout << endl;
    }

    // Layer by Layer (Level-Order)
    void displayLayers() {
        if (root == nullptr) return;

        cout << "\n--- Tree Layers (Top to Bottom) ---" << endl;
        node<t>* queue[100];
        int head = 0, tail = 0;

        queue[tail++] = root;

        int level = 1;
        while (head < tail) {
            int nodesInLevel = tail - head; // Count how many nodes are on this specific layer
            cout << "Layer " << level++ << ": ";

            while (nodesInLevel > 0) {
                node<t>* current = queue[head++];
                cout << current->data << " ";

                if (current->left != nullptr) queue[tail++] = current->left;
                if (current->right != nullptr) queue[tail++] = current->right;
                nodesInLevel--;
            }
            cout << endl; // Move to the next line for the next layer
        }
        cout << "-----------------------------------" << endl;
    }
    node<t>* parent(t d) {
        if (root == nullptr) { return nullptr; }
        node<t>* temp = root;
        while (temp != nullptr) {
            if (temp->left != nullptr && temp->left->data == d) return temp;
            if (temp->right != nullptr && temp->right->data == d) return temp;
            if (d < temp->data) { temp = temp->left; }
            else if (d > temp->data) { temp = temp->right; }
            else { return nullptr; }
        }
        return nullptr;
    }

    void deleteNode(t d) {

        if (root == nullptr) { return; }
        node<t>* n = root;
        while (n != nullptr) {
            if (n->data < d) { n = n->right; }
            else if (n->data > d) { n = n->left; }
            else if (n->data == d && n->left == nullptr && n->right == nullptr) {
                node<t>* temp = parent(d);
                if (temp == nullptr) { delete n; root = nullptr; return; }
                else if (temp->left->data == d) {
                    temp->left = nullptr;
                    delete n;
                    return;
                }
                else  if (temp->right->data == d) {
                    temp->right = nullptr;
                    delete n; return;
                }

            }
            else if (n->data == d && n->left != nullptr && n->right == nullptr) {
                node<t>* par = parent(d);
                if (par == nullptr) { root = n->left; return; }
                else if (par->right == n) {
                    par->right = n->left;
                }
                else if (par->left == n) {
                    par->left = n->left;
                }
                delete n;
                return;
            }

            else if (n->data == d && n->right != nullptr && n->left == nullptr) {
                node<t>* par = parent(d);
                if (par == nullptr) { root = n->right; return; }
                else if (par->right == n) {
                    par->right = n->right;
                }
                else if (par->left == n) {
                    par->left = n->right;
                }
                delete n;
                return;
            }

            else if (n->data == d && n->left != nullptr && n->right != nullptr) {
                node<t>* mov = n;
                mov = mov->left;
                while (mov->right != nullptr) {
                    mov = mov->right;
                }
                t result = mov->data;
                deleteNode(mov->data);
                n->data = result;
            }




        }

    }
    private:
        int height(node<t>* n) {
            if (n == nullptr) return 0;
            int l = height(n->left);
            int r = height(n->right);
            return (l > r ? l : r) + 1;
        }

        void printLevel(node<t>* n, int level, int indent) {
            if (n == nullptr) {
                // Optional: Print spaces for empty children to keep shape
                return;
            }
            if (level == 1) {
                // Add some spacing between nodes on the same level
                cout << n->data << "   ";
            }
            else if (level > 1) {
                printLevel(n->left, level - 1, indent);
                printLevel(n->right, level - 1, indent);
            }
        }

public:
    void displayTreeStructure() {
        int h = height(root);
        cout << "\n--- Visual Tree Structure ---" << endl;
        for (int i = 1; i <= h; i++) {
            // Add leading spaces to center the top of the tree (simple version)
            for (int s = 0; s < (h - i) * 2; s++) cout << " ";

            cout << "Layer " << i << ": ";
            printLevel(root, i, h);
            cout << endl;
        }
        cout << "-----------------------------" << endl;
    }



};
int main() {
    Tree<int> bst;

    // 1. Initial Insertions
    // Expected Shape:
    //        50
    //      /    \
    //    30      70
    //   /  \    /  \
    // 20   40  60   80
    int vals[] = { 50, 30, 70, 20, 40, 60, 80 };
    cout << "--- Building Tree ---" << endl;
    for (int v : vals) {
        bst.insertNode(v);
    }

    bst.displaySorted();
    bst.displayLayers(); // Should show 50 at the top

    // 2. Case 1: Delete a Leaf (Node 20)
    cout << "\n[TEST] Deleting Leaf node: 20" << endl;
    bst.deleteNode(20);
    bst.displaySorted();
    bst.displayLayers();

    // 3. Case 2: Delete Node with One Child (Node 30)
    // Since 20 is gone, 30 only has child 40. 
    // 50 should "adopt" 40.
    cout << "\n[TEST] Deleting Node with One Child: 30" << endl;
    bst.deleteNode(30);
    bst.displaySorted();
    bst.displayLayers();

    // 4. Case 3: Delete the Root with Two Children (Node 50)
    // Your logic will find the Predecessor (the largest value in left subtree).
    // In this case, 40 will become the new Root.
    cout << "\n[TEST] Deleting the Root (Two Children): 50" << endl;
    bst.deleteNode(50);
    bst.displaySorted();
    bst.displayLayers();

    cout << "\n--- Testing Complete! ---" << endl;
    return 0;

}