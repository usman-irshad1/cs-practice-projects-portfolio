#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cmath>

using namespace std;

// --- AVL NODE ---
class AVLNode {
public:
    int data;
    AVLNode* left;
    AVLNode* right;
    int height;

    AVLNode(int val) : data(val), left(nullptr), right(nullptr), height(1) {}
};

// --- AVL TREE CLASS ---
class AVLTree {
private:
    // Helper to get height of a node
    int height(AVLNode* n) { return n ? n->height : 0; }                  

    // Helper to get Balance Factor (Left Height - Right Height)
    int getBalance(AVLNode* n) { return n ? height(n->left) - height(n->right) : 0; }

    // Right Rotation (LL Case)
    AVLNode* rightRotate(AVLNode* y) {
        AVLNode* x = y->left;
        AVLNode* T2 = x->right;
        x->right = y;
        y->left = T2;
        y->height = max(height(y->left), height(y->right)) + 1;
        x->height = max(height(x->left), height(x->right)) + 1;
        return x;
    }

    // Left Rotation (RR Case)
    AVLNode* leftRotate(AVLNode* x) {
        AVLNode* y = x->right;
        AVLNode* T2 = y->left;
        y->left = x;
        x->right = T2;
        x->height = max(height(x->left), height(x->right)) + 1;
        y->height = max(height(y->left), height(y->right)) + 1;
        return y;
    }

    // Helper to find the In-order Predecessor (Largest in Left Subtree)
    AVLNode* maxValueNode(AVLNode* node) {
        AVLNode* current = node;
        while (current->right != nullptr) current = current->right;
        return current;
    }

public:
    AVLNode* root;
    AVLTree() : root(nullptr) {}

    // --- INSERTION ---
    AVLNode* insert(AVLNode* node, int data) {
        if (!node) return new AVLNode(data);
        if (data < node->data) node->left = insert(node->left, data);
        else if (data > node->data) node->right = insert(node->right, data);
        else return node; // No duplicates allowed

        node->height = 1 + max(height(node->left), height(node->right));
        int balance = getBalance(node);

        // LL Case
        if (balance > 1 && data < node->left->data) return rightRotate(node);
        // RR Case
        if (balance < -1 && data > node->right->data) return leftRotate(node);
        // LR Case
        if (balance > 1 && data > node->left->data) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        // RL Case
        if (balance < -1 && data < node->right->data) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
        return node;
    }

    // --- DELETION (Using Largest of Left Subtree) ---
    AVLNode* deleteNode(AVLNode* root, int key) {
        if (!root) return root;

        if (key < root->data)
            root->left = deleteNode(root->left, key);
        else if (key > root->data)
            root->right = deleteNode(root->right, key);
        else {
            // Node with only one child or no child
            if (!root->left || !root->right) {
                AVLNode* temp = root->left ? root->left : root->right;
                if (!temp) {
                    temp = root;
                    root = nullptr;
                }
                else {
                    *root = *temp; // Copy child to current node
                }
                delete temp;
            }
            else {
                // Node with two children: Get In-order Predecessor
                AVLNode* temp = maxValueNode(root->left);
                root->data = temp->data; // Swap data
                root->left = deleteNode(root->left, temp->data); // Delete predecessor
            }
        }

        if (!root) return root;

        // Update height of current node
        root->height = 1 + max(height(root->left), height(root->right));
        int balance = getBalance(root);

        // Rebalancing after deletion
        // Left Heavy
        if (balance > 1 && getBalance(root->left) >= 0) return rightRotate(root);
        if (balance > 1 && getBalance(root->left) < 0) {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }
        // Right Heavy
        if (balance < -1 && getBalance(root->right) <= 0) return leftRotate(root);
        if (balance < -1 && getBalance(root->right) > 0) {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }

        return root;
    }

    // --- VISUAL PRINTER ---
    void printLevelOrder() {
        if (!root) { cout << "Tree is Empty" << endl; return; }
        int h = root->height;
        queue<AVLNode*> q;
        q.push(root);

        for (int i = 0; i < h; i++) {
            int nodesAtLevel = q.size();
            int firstSpace = pow(2, h - i) - 1;
            int midSpace = pow(2, h - i + 1) - 1;

            for (int k = 0; k < firstSpace; k++) cout << "  ";
            while (nodesAtLevel > 0) {
                AVLNode* curr = q.front(); q.pop();
                if (curr) {
                    printf("%02d", curr->data);
                    q.push(curr->left); q.push(curr->right);
                }
                else {
                    cout << "  ";
                    q.push(nullptr); q.push(nullptr);
                }
                for (int k = 0; k < midSpace; k++) cout << "  ";
                nodesAtLevel--;
            }
            cout << endl << endl;
        }
    }
};

int main() {
    AVLTree tree;
    vector<int> inserts = { 50, 25, 75, 15, 35, 60, 120, 10, 68, 90, 150, 125, 170 };

    cout << "--- STEP 1: INSERTING OMEGA PROTOCOL VALUES ---" << endl;
    for (int val : inserts) {
        cout << "Inserting " << val << "..." << endl;
        tree.root = tree.insert(tree.root, val);
    }
    tree.printLevelOrder();

    vector<int> deletes = {10 ,75,150,68,15,60,170,50,90};
    cout << "--- STEP 2: STARTING ENTROPY DELETIONS (Predecessor Method) ---" << endl;
    for (int val : deletes) {
        cout << "Deleting " << val << "..." << endl;
        tree.root = tree.deleteNode(tree.root, val);
        tree.printLevelOrder();
        cout << "----------------------------------------------------" << endl;
    }

    return 0;
}