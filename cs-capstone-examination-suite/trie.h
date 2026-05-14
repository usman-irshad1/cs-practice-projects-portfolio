#pragma once
#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

struct TRIENode {
    bool isEnd;
    unordered_map<char, TRIENode*> children;

    TRIENode() : isEnd(false) {}
};

class Trie {
private:
    TRIENode* root;

    void get_all_Words(TRIENode* node, string currentPrefix, vector<string>& allWords) {
        if (!node) return;

        if (node->isEnd) {
            allWords.push_back(currentPrefix);
        }

        for (auto const& [character, childNode] : node->children) {
            get_all_Words(childNode, currentPrefix + character, allWords);
        }
    }

    bool recursive_delete(TRIENode* node, const string& word, int index) {
        if (!node) return false;

        if (index == word.size()) {
            if (!node->isEnd) return false;

            node->isEnd = false;
            return node->children.empty();
        }

        char currentChar = word[index];
        if (node->children.find(currentChar) == node->children.end()) return false;

        bool canDeleteChild = recursive_delete(node->children[currentChar], word, index + 1);

        if (canDeleteChild) {
            delete node->children[currentChar];
            node->children.erase(currentChar);
            return !node->isEnd && node->children.empty();
        }

        return false;
    }

public:
    Trie() {
        root = new TRIENode();
    }

    void insert(string word) {
        TRIENode* crawler = root;
        for (char character : word) {
            if (crawler->children.find(character) == crawler->children.end()) {
                crawler->children[character] = new TRIENode();
            }
            crawler = crawler->children[character];
        }
        crawler->isEnd = true;
    }

    bool search(string word) {
        TRIENode* crawler = root;
        for (char character : word) {
            if (crawler->children.find(character) == crawler->children.end()) {
                return false;
            }
            crawler = crawler->children[character];
        }
        return crawler->isEnd;
    }

    bool searchPrefix(string prefix) {
        TRIENode* crawler = root;
        for (char character : prefix) {
            if (crawler->children.find(character) == crawler->children.end()) {
                return false;
            }
            crawler = crawler->children[character];
        }
        return true;
    }

    vector<string> getWordsWithPrefix(string prefix) {
        TRIENode* crawler = root;
        vector<string> results;

        for (char character : prefix) {
            if (crawler->children.find(character) == crawler->children.end()) {
                return results;
            }
            crawler = crawler->children[character];
        }

        get_all_Words(crawler, prefix, results);
        return results;
    }

    void deleteWord(string word) {
        recursive_delete(root, word, 0);
    }
};