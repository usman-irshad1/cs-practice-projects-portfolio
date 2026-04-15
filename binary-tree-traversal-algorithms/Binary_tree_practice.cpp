// Binary_tree_practice.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std;

class node {
public:
    int data;
    node* left;
    node* right;


    node() {
        left = right = nullptr;    
    }
    node(int f) {
        left = right = nullptr;
        data = f;
    }
    void setLeft(node* t) { left = t; }
    void setRight(node* t) { right = t; }
    node* getLeft() { return left; }
    node* getRight() { return right; }
    void setData(int d) { data = d; }
    int getData() { return data; }
};
class BinaryTree {
    node* root;
public:
    BinaryTree() {
        root = nullptr;
    }

    BinaryTree(const BinaryTree & c) {
       root= copyTree(c.root);
    }

    ~BinaryTree() {
        delete_tree(root);
    }

    node* copyTree(node* t) {
        if (t == nullptr) { return nullptr; }
        node* n = new node(t->getData());

        n->setLeft(copyTree(t->getLeft()));
        n->setRight(copyTree(t->getRight()));
        return n;
    
    }

    void delete_tree(node*t) {
        if (t == nullptr) { return; }
        delete_tree(t->getLeft());
        delete_tree(t->getRight());
        delete t;
    }

    void infix(node * t) {
        if (t == nullptr) { return; }
        infix(t->getLeft());
        cout << t->getData();
        infix(t->getRight());
    }
    void prefix(node* t) {
        if (t == nullptr) { return; }
        cout << t->getData();
        prefix(t->getLeft());
        prefix(t->getRight());
    }
    void postfix(node* t) {
        if (t == nullptr) { return; }
        postfix(t->getLeft());
        postfix(t->getRight());
        cout << t->getData();;
    }



    void insertData(int d) {
        insert(d, root);
    }


    void insert(int d, node* & t) {
        if (t == nullptr) {
            t = new node(d);
            return;
        }
        else if (t->getData() > d) {
            insert(d, t->left);
        }
        else if (t->getData() < d) {
            insert(d, t->right);
        }

    }

    bool searchNode(node* t, int data) {
        if (t == nullptr) { return false; }

        else if (data < t -> data) {
            return searchNode(t->getLeft(),data);
        }
        else if (data > t->data) {
             return searchNode(t->getRight(), data);
        }
        else if (data==t->data){
            return true;
        }

    
    }


    bool searchNodeByIteration(int d) {
        node* temp = root;
        while (temp != nullptr) {
            if (d == temp->data) {
                return true;
            }
            else if (d<temp->data ) {
                temp = temp->getLeft();
            
            }
            else{
                temp = temp->getRight();
            }
         
        }
        return false;
    
    }


    int max() {
        node* temp = root;
        if (temp == nullptr) {
            return -1;
        }
        while (temp->getRight() != nullptr) {
            temp = temp->right;
        }
        return temp->getData();
    
    }


    int min() {
        node* temp = root;
        if (temp == nullptr) {
            return -1;
        }
        while (temp->getLeft() != nullptr) {
            temp = temp->left;
        }
        return temp->getData();

    }

    int count(node * t) {
        if (t == nullptr) {
            return 0;
        }
        return  1+  count(t->left) + count(t->right);
    }

    int sum(node * t) {
        if (t == nullptr) { return 0; }
        return t->getData() + sum(t->left) + sum(t->right);
    }
    
    void deleteNode(int d, node* t) {
        
        if (t == nullptr) {
            cout << "You cant delete from an empty tree";
        }
        else if (d < t->getData()) {
            deleteNode(d, t->left);
        }
        else if (d > t->getData()) {
            deleteNode(d, t->right);
        }
        else if (t->left != nullptr && t->right != nullptr) {///this has 2 children
            node* n = t->getRight();
            while (n->getLeft() != nullptr) {
                n = n->getLeft();
            }

            t->data = n->data;
            deleteNode(d, t);

        }
        else {
            node* old = t;
            if ()
        }
    
    
    
    }


};



int main()
{
    std::cout << "Hello World!\n";
}
