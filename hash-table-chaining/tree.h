#pragma once
#include <iostream>
using namespace std;

template <class t>
class Bnode {
    Bnode<t>* left, * right;
    t data;
public:
    Bnode() {
        left = right = nullptr;
        data = t();
    }
    void setData(t d) { data = d; }
    t getData() { return data; }
    void setLeft(Bnode<t>* r) { left = r; }
    void setRight(Bnode<t>* r) { right = r; }
    Bnode<t>* getRight() { return right; }
    Bnode<t>* getLeft() { return left; }
};

template <class t>
class tree {
    Bnode <t>* root;

    void inOrder(Bnode<t>* curr) {
        if (curr == nullptr) return;
        inOrder(curr->getLeft());
        cout << curr->getData() << " ";
        inOrder(curr->getRight());
    }

    void PreOrder(Bnode<t>* curr) {
        if (curr == nullptr) return;
        cout << curr->getData() << " ";
        PreOrder(curr->getLeft());
        PreOrder(curr->getRight());
    }

    void PostOrder(Bnode<t>* curr) {
        if (curr == nullptr) return;
        PreOrder(curr->getLeft());
        PreOrder(curr->getRight());
        cout << curr->getData() << " ";
    }

public:
    tree() {
        root = nullptr;
    }

    void insert(t data) {
        if (root == nullptr) {
            Bnode<t>* n = new Bnode<t>();
            n->setData(data);
            root = n;
            return;
        }

        Bnode<t>* temp = root;
        Bnode<t>* parent = nullptr;
        while (temp != nullptr) {
            parent = temp;
            if (data < temp->getData()) {
                temp = temp->getLeft();
            }
            else {
                temp = temp->getRight();
            }
        }
        Bnode<t>* n = new Bnode<t>();
        n->setData(data);
        if (data < parent->getData()) {
            parent->setLeft(n);
        }
        else {
            parent->setRight(n);
        }
    }

    void insert_1() {}

    Bnode<t>* search(t data) {
        Bnode<t>* temp = root;
        if (root == nullptr) {
            
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

    Bnode<t>* searchParent(t data) {
        Bnode<t>* temp = root;
        Bnode<t>* parent = nullptr;
        if (root == nullptr) {
            
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
        Bnode<t>* temp = search(data);

        if (temp->getLeft() == nullptr && temp->getRight() == nullptr) {
            if (temp == root) {
                delete root;
                root = nullptr;
            }
            else {
                Bnode<t>* parent = searchParent(data);
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
                Bnode<t>* parent = searchParent(data);
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
            t data;
            Bnode<t>* link_of_single_leaf_node = temp;
            link_of_single_leaf_node = link_of_single_leaf_node->getLeft();
            while (link_of_single_leaf_node->getRight() != nullptr) {
                link_of_single_leaf_node = link_of_single_leaf_node->getRight();
            }

            data = link_of_single_leaf_node->getData();
            delete_node(data);
            temp->setData(data);
        }
    }
};