// binary_tree_practice_2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

using namespace std;

template <class t>
class node {
public:
    node<t>* left;
    node<t>* right;
    t data;
    node() {

        right = left =nullptr;
        data = t();
    }
    node(t d) {

        right = left = nullptr;
        data = d;
    }
};

template <class t>
class BinaryTree {
    node<t>* root;
public:

    BinaryTree() { root = nullptr; }


    //void insert(t data) {
    //    if (root == nullptr) { root = new node<t>(data); return; }

    //    node<t>* temp = root;
    //    node<t>*  parent;
    //    while (temp != nullptr) {
    //        if (data < temp->data) {
    //            parent = temp;
    //            temp = temp->left; 
    //            
    //    }
    //        else if (data > temp->data) {
    //            parent = temp;
    //            temp = temp->right;             
    //        } 
    //        else {
    //            return;
    //        }
    //        
    //    }


    //    node<t>* n=new node<t>(data);
    //    if (data < parent->data) {
    //        parent->left =n ;
    //    }
    //    else {

    //        parent -> right = n;
    //    }


    //}



    void insert(t data, node<t>*& temp) {
        if (temp == nullptr) {
            temp = new node(data);
            return;
        }
        else if (data < temp->data) { insert(data, temp->left); }
        else if (data > temp->data) { insert(data, temp->right); }
        else { return; }
    }

    bool search(node<t>* n, t data) {
        if (n == nullptr) { return false; }

        if (data < n->data) {
           return  search(n->left, data);
        }
        else if (data > n->data) {
           return  search(n->right, data);
        }
        else {
            return true;
        }
    }


    t findMax(node<t>* n) {
        if (n->right == nullptr) { return n->data; }
        return findMax(n->right);    
    }


    void inOrder(node<t>* n) {
        if (n == nullptr) {
            return;
        }
        if (n->left != nullptr) { inOrder(n->left); };
        cout << n->data;
        if (n->right != nullptr) {
            inOrder(n->right);
        }
    
        }

    void PreOrder(node<t>* n) {
        if (n == nullptr) {
            return;
        }
        cout << n->data;

        if (n->left != nullptr) { PreOrder(n->left); };
       
        if (n->right != nullptr) {
            PreOrder(n->right);
        }

    }

    void PostOrder(node<t>* n) {
        if (n == nullptr) {
            return;
        }
        if (n->left != nullptr) { PostOrder(n->left); };
       
        if (n->right != nullptr) {
            PostOrder(n->right);
        }
        cout << n->data;

    }

    void deleteTree(node<t>* n) {
        if (n == nullptr) {
            return;
        }

        deleteTree(n->left);
        deleteTree(n->right);
         delete n;
       

    }

    ~BinaryTree() {
        deleteTree(root);

    
    }


    void deleteNode(t data) {
        if (root == nullptr) { return; }
        
        node<t>* temp = root;
        while (temp != nullptr) {
            if (temp->data == data && temp->left == nullptr && temp->right == nullptr) { delete temp; return; }
            if (temp->data == data && temp->left == nullptr && temp->right == nullptr) { delete temp; return; }
            if (temp->data == data && temp->left != nullptr && temp->right != nullptr) {
                node<t>* n = temp;
                n = n->left;
                while (n->left != nullptr) {
                    n = n->left;
                }//how to put the put the praent pointer loft equal to nullptr
                temp->data = n->data;
                delete n;
                

            
            
            }
            if (data < temp->data) { temp = temp->left; }
            if (data > temp->data) { temp = temp->right; }

        }
    }
};



int main()
{
    std::cout << "Hello World!\n";
}
