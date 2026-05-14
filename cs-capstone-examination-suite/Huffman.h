#pragma once

#include <iostream>
#include <list>
#include <string>
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

struct HuffmanNode {
    int frequency;
    char data;
    HuffmanNode* left, * right;

    HuffmanNode() : left(nullptr), right(nullptr), frequency(1), data('\0') {}
    HuffmanNode(char s, int freq = 1) : left(nullptr), right(nullptr), frequency(freq), data(s) {}
};

inline bool compareNodes(HuffmanNode* a, HuffmanNode* b) {
    return a->frequency < b->frequency;
}

class HuffmanEncoder : public list<HuffmanNode*> {
private:
    void deleteTree(HuffmanNode* node) {
        if (!node) return;
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }

    string getCharCode(HuffmanNode* node, string currentPath, char target) {
        if (!node) return "";
        if (!node->left && !node->right) {
            return (node->data == target) ? currentPath : "";
        }
        string leftPath = getCharCode(node->left, currentPath + '0', target);
        if (!leftPath.empty()) return leftPath;
        return getCharCode(node->right, currentPath + '1', target);
    }

    void writeKeyRecursive(HuffmanNode* node, string code, ofstream& outfile) {
        if (!node) return;
        if (!node->left && !node->right) {
            // Save as ASCII integer to prevent issues with whitespace/newlines
            outfile << (int)((unsigned char)node->data) << " " << code << endl;
        }
        writeKeyRecursive(node->left, code + '0', outfile);
        writeKeyRecursive(node->right, code + '1', outfile);
    }

public:
    HuffmanEncoder() {}
    ~HuffmanEncoder() { clearAndFree(); }

    void clearAndFree() {
        if (!this->empty()) {
            deleteTree(this->front());
            this->clear();
        }
    }

    void buildTreeFromText(string text) {
        clearAndFree();
        // Frequency counting
        for (char c : text) {
            bool found = false;
            for (auto node : *this) {
                if (node->data == c) {
                    node->frequency++;
                    found = true;
                    break;
                }
            }
            if (!found) this->push_back(new HuffmanNode(c));
        }
        this->sort(compareNodes);

        // Tree construction
        while (this->size() > 1) {
            HuffmanNode* x = this->front(); this->pop_front();
            HuffmanNode* y = this->front(); this->pop_front();
            HuffmanNode* parent = new HuffmanNode('*', x->frequency + y->frequency);
            parent->left = x;
            parent->right = y;
            this->push_front(parent);
            this->sort(compareNodes);
        }
    }

    void saveKey(string filename = "Key_for_encryption.txt") {
        if (this->empty()) return;
        ofstream outfile(filename);
        if (outfile.is_open()) {
            writeKeyRecursive(this->front(), "", outfile);
            outfile.close();
        }
    }

    void rebuildFromKey(string filename = "Key_for_encryption.txt") {
        clearAndFree();
        ifstream infile(filename);
        if (!infile.is_open()) return;

        this->push_back(new HuffmanNode('*'));
        int asciiVal;
        string code;
        while (infile >> asciiVal >> code) {
            HuffmanNode* temp = this->front();
            for (char bit : code) {
                if (bit == '0') {
                    if (!temp->left) temp->left = new HuffmanNode('*');
                    temp = temp->left;
                }
                else {
                    if (!temp->right) temp->right = new HuffmanNode('*');
                    temp = temp->right;
                }
            }
            temp->data = (char)asciiVal;
        }
        infile.close();
    }

    // Encrypts OriginalFile and saves to Encrypted_file.txt
    void encryptAndSave(string inputSource = "OriginalFile.txt") {
        ifstream infile(inputSource, ios::binary);
        if (!infile.is_open()) return;

        string content((istreambuf_iterator<char>(infile)), istreambuf_iterator<char>());
        infile.close();

        buildTreeFromText(content);
        saveKey();

        ofstream outfile("Encrypted_file.txt");
        for (char c : content) {
            outfile << getCharCode(this->front(), "", c);
        }
        outfile.close();
        cout << "File encrypted and saved to Encrypted_file.txt" << endl;
    }

    // Decrypts Encrypted_file.txt and saves to Decrypted_file.txt
    void decryptAndSave() {
        ifstream infile("Encrypted_file.txt");
        if (!infile.is_open()) {
            cout << "Error: Could not find Encrypted_file.txt" << endl;
            return;
        }
        string encodedData;
        infile >> encodedData;
        infile.close();

        // Ensure we have a tree loaded (either from encryption or key file)
        if (this->empty()) rebuildFromKey();

        string decodedResult = "";
        HuffmanNode* current = this->front();
        for (char bit : encodedData) {
            if (bit == '0') current = current->left;
            else current = current->right;

            if (current && !current->left && !current->right) {
                decodedResult += current->data;
                current = this->front();
            }
        }

        ofstream outfile("Decrypted_file.txt", ios::binary);
        outfile << decodedResult;
        outfile.close();
        cout << "File decrypted and saved to Decrypted_file.txt" << endl;
    }
};