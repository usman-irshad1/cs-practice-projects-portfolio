
#pragma once

#include <iostream>
#include <algorithm> // Added for std::max
using namespace std;

template <class t>
class node {
public:
    node<t>* left, * right;
    t data;

    node() {
        left = right = nullptr;
        data = t();
    }
    void setData(t d) { data = d; }
    t getData() { return data; }
    void setLeft(node<t>* r) { left = r; }
    void setRight(node<t>* r) { right = r; }
    node<t>* getRight() { return right; }
    node<t>* getLeft() { return left; }
};

template <class t>
class tree {
    node <t>* root;


    int height(node<t>* temp) {
        if (temp == nullptr) { return 0; }
        int left = height(temp->getLeft());
        int right = height(temp->getRight());
        return 1 + std::max(left, right);
    }

    int count(node<t>* temp) {
        if (temp == nullptr) { return 0; }
        int left = count(temp->getLeft());
        int right = count(temp->getRight());
        return left + right + 1;
    }

    t min(node<t>* temp) {
        if (temp == nullptr) { return t(); }
        if (temp->getLeft() == nullptr) { return temp->getData(); }
        return min(temp->getLeft());
    }

    t maax(node<t>* temp) {
        if (temp == nullptr) { return t(); }
        if (temp->getRight() == nullptr) { return temp->getData(); }
        return maax(temp->getRight());
    }


    void inOrder(node<t>* curr) {
        if (curr == nullptr) return;
        inOrder(curr->getLeft());
        cout << curr->getData() << " ";
        inOrder(curr->getRight());
    }

    void PreOrder(node<t>* curr) {
        if (curr == nullptr) return;
        cout << curr->getData() << " ";
        PreOrder(curr->getLeft());
        PreOrder(curr->getRight());
    }

    void PostOrder(node<t>* curr) {
        if (curr == nullptr) return;
        PostOrder(curr->getLeft());
        PostOrder(curr->getRight());
        cout << curr->getData() << " ";
    }

public:
    tree() {
        root = nullptr;
    }

   
    t getMin() { return min(root); }
    t getMax() { return maax(root); }
    int getHeight() { return height(root); }
    int countNodes() { return count(root); }
   

    void displayInOrder() { inOrder(root); cout << endl; }
    void displayPreOrder() { PreOrder(root); cout << endl; }
    void displayPostOrder() { PostOrder(root); cout << endl; }

    void insert(t data) {
        if (root == nullptr) {
            node<t>* n = new node<t>();
            n->setData(data);
            root = n;
            return;
        }

        node<t>* temp = root;
        node<t>* parent = nullptr;
        while (temp != nullptr) {
            parent = temp;
            if (data < temp->getData()) {
                temp = temp->getLeft();
            }
            else if (data > temp->getData()) {
                temp = temp->getRight();
            }
            else {
                cout << "Duplicate value";
                return;
            }
        }
        node<t>* n = new node<t>();
        n->setData(data);
        if (data < parent->getData()) {
            parent->setLeft(n);
        }
        else {
            parent->setRight(n);
        }
    }

    node<t>* search(t data) {
        node<t>* temp = root;
        if (root == nullptr) {
            cout << "It does not exist in an empty tree";
            return nullptr;
        }
        else {
            while (temp != nullptr) {
                if (temp->getData() < data) {
                    temp = temp->getRight();
                }
                else if (temp->getData() > data) {
                    temp = temp->getLeft();
                }
                else if (temp->getData() == data) {
                    return temp;
                }
            }
            return nullptr;
        }
    }

    node<t>* searchParent(t data) {
        node<t>* temp = root;
        node<t>* parent = nullptr;
        if (root == nullptr) {
            cout << "It does not exist in an empty tree";
            return nullptr;
        }
        else {
            while (temp != nullptr) {
                if (temp->getData() < data) {
                    parent = temp;
                    temp = temp->getRight();
                }
                else if (temp->getData() > data) {
                    parent = temp;
                    temp = temp->getLeft();
                }
                else if (temp->getData() == data) {
                    return parent;
                }
            }
            return nullptr;
        }
    }

    void delete_node(t data) {
        node<t>* temp = search(data);
        if (temp == nullptr) return;

        if (temp->getLeft() == nullptr && temp->getRight() == nullptr) {
            if (temp == root) {
                delete root;
                root = nullptr;
            }
            else {
                node<t>* parent = searchParent(data);
                if (parent->getRight() == temp) {
                    delete temp;
                    parent->setRight(nullptr);
                }
                else if (parent->getLeft() == temp) {
                    delete temp;
                    parent->setLeft(nullptr);
                }
            }
        }
        else if (temp->getLeft() == nullptr || temp->getRight() == nullptr) {
            if (temp == root) {
                if (root->getLeft() == nullptr) {
                    root = root->getRight();
                    delete temp;
                    return;
                }
                else if (root->getRight() == nullptr) {
                    root = root->getLeft();
                    delete temp;
                    return;
                }
            }
            else {
                node<t>* parent = searchParent(data);
                if (parent->getRight() == temp) {
                    if (temp->getRight() != nullptr) {
                        parent->setRight(temp->getRight());
                    }
                    else {
                        parent->setRight(temp->getLeft());
                    }
                    delete temp;
                }
                else if (parent->getLeft() == temp) {
                    if (temp->getRight() != nullptr) {
                        parent->setLeft(temp->getRight());
                    }
                    else {
                        parent->setLeft(temp->getLeft());
                    }
                    delete temp;
                }
            }
        }
        else {
            t data_val;
            node<t>* link_of_single_leaf_node = temp;
            link_of_single_leaf_node = link_of_single_leaf_node->getLeft();
            while (link_of_single_leaf_node->getRight() != nullptr) {
                link_of_single_leaf_node = link_of_single_leaf_node->getRight();
            }

            data_val = link_of_single_leaf_node->getData();
            delete_node(data_val);
            temp->setData(data_val);
        }
    }

    bool isEmpty() {
        return root == nullptr;
    }

    tree(const tree& Christmas) {
        root = copyTree(Christmas.root);
    }

    void destroyTree(node<t>* curr) {
        if (curr != nullptr) {
            destroyTree(curr->getLeft());
            destroyTree(curr->getRight());
            delete curr;
        }
    }

    ~tree() {
        destroyTree(root);
    }

    node<t>* copyTree(node<t>* otherNode) {
        if (otherNode == nullptr) {
            return nullptr;
        }
        node<t>* newNode = new node<t>();
        newNode->setData(otherNode->getData());
        newNode->setLeft(copyTree(otherNode->getLeft()));
        newNode->setRight(copyTree(otherNode->getRight()));
        return newNode;
    }
};

