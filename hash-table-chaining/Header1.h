#pragma once
#include <algorithm>
#include <iostream>
using namespace std;
template<class t>
struct AVLNode {
    int h;
    t data;
    AVLNode<t>* left;
    AVLNode<t>* right;
    AVLNode(t d) { left = right = nullptr; data = d; h = 1; }
    AVLNode() { left = right = nullptr; data = t(); h = 1; }
};
template <class t>
class AVLTree {
    AVLNode<t>* root;

    void insertNode(t d, AVLNode<t>*& node) {
        if (node == nullptr) {
            node = new AVLNode<t>(d);

            return;
        }
        else if (d < node->data) { insertNode(d, node->left); }
        else if (d > node->data) { insertNode(d, node->right); }
        else { return; }

        node->h = 1 + max(height(node->left), height(node->right));
        int balance = balanceFactor(node);
        if (balance > 1) {
            if (d < node->left->data)
                rotateLeftLeft(node);
            else
                rotateLeftRight(node);
        }
        else if (balance < -1) {
            if (d > node->right->data)
                rotateRightRight(node);
            else
                rotateRightLeft(node);
        }
    }

    int balanceFactor(AVLNode<t>* n) {
        if (n == nullptr) return 0;
        return height(n->left) - height(n->right);
    }

    int height(AVLNode<t>* n) {
        if (n == nullptr) return 0; // important change
        return n->h;
    }

public:
    AVLTree() { root = nullptr; }


    void insert(t data) {
        insertNode(data, root);
    }
    void rotateLeftLeft(AVLNode<t>*& node) {
        AVLNode<t>* L = node->left;
        AVLNode<t>* T2 = L->right;

        L->right = node;
        node->left = T2;
        node->h = 1 + max(height(node->left), height(node->right));
        L->h = 1 + max(height(L->left), height(L->right));

        node = L;
    }
    void rotateRightRight(AVLNode<t>*& node) {
        AVLNode<t>* R = node->right;
        AVLNode<t>* T2 = R->left;

        R->left = node;
        node->right = T2;

        node->h = 1 + max(height(node->left), height(node->right));
        R->h = 1 + max(height(R->left), height(R->right));

        node = R;
    }
    void rotateLeftRight(AVLNode<t>*& node) {
        rotateRightRight(node->left);
        rotateLeftLeft(node);
    }
    void inorder(AVLNode<t>* node) {
        if (!node) return;
        inorder(node->left);
        cout << node->data << " ";
        inorder(node->right);
    }


    void display() {
        inorder(root);
        cout << endl;
    }

    void rotateRightLeft(AVLNode<t>*& node) {
        rotateLeftLeft(node->right);
        rotateRightRight(node);
    }

    friend ostream& operator<<(ostream& os, const AVLTree<t>& tree) {
        tree.printInorder(tree.root, os);
        return os;
    }
   
    void printInorder(AVLNode<t>* node, ostream& os) const { 
        if (!node) return;
        printInorder(node->left, os);
        os << node->data << " | ";
        printInorder(node->right, os);
    }
    void clear(AVLNode<t>* node) {
        if (node == nullptr) return;
        clear(node->left);
        clear(node->right);
        delete node;
    }
    ~AVLTree() {
        clear(root);
        root = nullptr;
    }
};