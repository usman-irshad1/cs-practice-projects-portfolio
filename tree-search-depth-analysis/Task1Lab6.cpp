// Task1Lab6.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std;
#include <iostream>
using namespace std;
template <class t>
class node {
public:
    t data;
    node<t>* left;
    node<t>* right;


    node() {
        left = right = nullptr;
    }
    node(t f) {
        left = right = nullptr;
        data = f;
    }
    void setLeft(node<t>* t) { left = t; }
    void setRight(node<t>* t) { right = t; }
    node<t>*  getLeft() { return left; }
    node<t>*  getRight() { return right; }
    void setData(t d) { data = d; }
    t getData() { return data; }
};


template <class t>
class BinaryTree {
    node<t>*  root;

    int height(node<t>* temp) {
        if (temp == nullptr) { return 0; }

        int left = height(temp->left);
        int right = height(temp->right);
        return 1 + max(left, right);
    }

    int count(node<t>* temp) {
        if (temp == nullptr) { return 0; }
        int left = count(temp->left);
        int right = count(temp->right);
        return left + right + 1;
    }


    void insert(t data, node<t>*& temp) {
        if (temp == nullptr) {
            temp = new node(data);
            return;
        }
        else if (data < temp->data) { insert(data, temp->left); }
        else if (data > temp->data) { insert(data, temp->right); }
        else  { return; }
    }

    bool search(t data, node<t>* temp) {
        if (temp == nullptr) { return false; }
        if (temp->data < data) { return search(data, temp->getRight()); }
        if (temp->data > data) { return  search(data, temp->getLeft()); }
        else { return true; }
    }

    t min(node<t>* temp) {
        if (temp->left == nullptr) { return temp->data; }
        return min(temp->left);
    }

    t maax(node<t>* temp) {
        if (temp->right == nullptr) { return temp->data; }
        return maax(temp->right);
    }
public:
    BinaryTree() {
        root = nullptr;
    }

    BinaryTree(const BinaryTree<t>& c) {
        root = copyTree(c.root);
    }



    void insertNode(t data) {
        this->insert(data, root);
    }

    t getMin() { return min(root); }
    t getMax() { return maax(root); }
    bool searchNode(t data) {
       return search(data, root);
    }
   
    int getHeight() {
       return height(root);
    }

   
    int countNodes() {
       return count(root);
    }
};


int main() {
    BinaryTree<int> tree;

  

    // 1. Using Insert
    tree.insertNode(50);
    tree.insertNode(30);
    tree.insertNode(70);
    tree.insertNode(20);
    tree.insertNode(40);
    tree.insertNode(60);
    tree.insertNode(80);


  

    cout << "Tree Height: " << tree.getHeight() << endl;

    cout << "Maximum Value: " << tree.getMax() << endl;

    cout << "Search = " << tree.searchNode(20)<<endl;
    cout << "Minimum Value: " << tree.getMin() << endl;

    return 0;
}