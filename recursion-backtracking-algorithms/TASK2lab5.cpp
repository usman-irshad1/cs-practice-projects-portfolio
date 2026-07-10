
// TASK2lab5.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include<C:\Users\usman\source\repos\BinaryTree.h>
using namespace std;
class book {
        int  BookID;
        string Title;
        string Author;
        int Popularity_score;
        static int id;

public:
    book() {
        Author = "john doe";
        Title = "Unknown";
        Popularity_score = id++;
        BookID = id;
    }
    book(string a, string b) {
        Author = a;
        Title = b;
        Popularity_score = id++;
        BookID = id;
    }

    friend ostream& operator<<(ostream& os, const book& b) {
        os << "book id " << b.BookID << endl;
        os << "book name " <<b.Title << endl;
        os << "book author " << b.Author<< endl;
        os << "book populatiry "<< b.Popularity_score<< endl;
        return os;
    }

    bool operator<(const book& other)  const{
        return this->Popularity_score < other.Popularity_score;
    }
    bool operator>(const book& other) const 
    { return Popularity_score > other.Popularity_score; 
    }
    bool operator==(const book& other) const
    { return Popularity_score == other.Popularity_score; 
    }
    bool operator<=(const book& other) const
    {
        return Popularity_score <= other.Popularity_score;
    }
    bool operator>=(const book& other) const
    {
        return Popularity_score >= other.Popularity_score;
    }
    void setPop(int p) { this->Popularity_score = p; }

};

class Library {
    tree<book> lib;
public:
    Library() {}
    void display() {
        lib.displayInOrder();
    }
    void insertBook(book b) {
        lib.insert(b);
    }

    void search(int pop) {
        book b;
        b.setPop(pop);
        node<book >* result=lib.search(b);
        if (result != nullptr) {
            cout << "Book Found \n" << result->getData() << endl;
        }
        else {
            cout << "No book found with popularity score: " << pop << endl;
        }
    }


    void delete_book(int pop) {
        book b;
        b.setPop(pop);
         lib.delete_node(b);

    }
    void RangeQuery(int minScore, int maxScore) {
        book minB, maxB;
        minB.setPop(minScore);
        maxB.setPop(maxScore);
        cout << "Books between scores " << minScore << " and " << maxScore << ":\n";
        lib.rangeSearch(lib.getRoot(), minB, maxB);
    }

    void size() {
        cout << "SIZE = "<<lib.getSize()<<endl;
    }
    void TopKBooks(int k) {
        int count = 0;
        cout << "Top " << k << " most popular books:\n";
        lib.getTopK(lib.getRoot(), k, count);
    }
};


int book:: id = 0;
int main() {
    Library myLibrary;

    book b1("1", "b1");
    book b2("2", "b2");
    book b3("3", "b3");
    book b4("4", "b4");
    book b5("5", "b5");

    b1.setPop(85);
    b2.setPop(95);
    b3.setPop(70);
    b4.setPop(60);
    b5.setPop(99);

    myLibrary.insertBook(b1);
    myLibrary.insertBook(b2);
    myLibrary.insertBook(b3);
    myLibrary.insertBook(b4);
    myLibrary.insertBook(b5);

    cout << "Full Inventory" << endl;
    myLibrary.display();
    cout << "Total Count: ";
    myLibrary.size();

    myLibrary.TopKBooks(3);
    cout << endl;

    myLibrary.RangeQuery(70, 90);
    cout << endl;

    myLibrary.search(95);

    myLibrary.delete_book(70);
    cout << "\nAfter Deletion Count: ";
    myLibrary.size();

    return 0;
}