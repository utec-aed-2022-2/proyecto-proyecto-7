#ifndef V1_TRIE_H
#define V1_TRIE_H

#include <iostream>
#include <stdexcept>
#include <vector>
#include "Record.h"

const unsigned ALPHA_SIZE = 26;

template<typename TV>
class Trie {
private:
    struct TrieNode {
        TrieNode** children;

        bool is_end;

        std::vector<TV> end_values;

        TrieNode() {
            children = new TrieNode* [ALPHA_SIZE];

            for (int i = 0; i < ALPHA_SIZE; i++) {
                children[i] = nullptr;
            }

            is_end = false;
        }

        ~TrieNode() {
            for (int i = 0; i < ALPHA_SIZE; ++i) {
                delete children[i];
            }

            delete[] children;
        }
    };

    TrieNode* root;

public:
    Trie() : root(nullptr) {}

    std::vector<std::string> get_all_substring(std::string key) {
        std::vector<std::string> result;

        for (int len = 1; len <= key.size(); len++) {
            for (int i = 0; i <= key.size() - len; i++) {
                int j = i + len - 1;
                std::string sub;

                for (int k = i; k <= j; k++) {
                    sub += key[k];
                }

                result.push_back(sub);
            }
        }

        return result;
    }

    void insert(std::string key, TV value) {
        for (auto i = key.begin(); i < key.end(); ++i) {
            *i = std::tolower(*i);
        }

        if (root == nullptr) {
            root = new TrieNode();
        }

        for (auto substring: get_all_substring(key)) {
            TrieNode* node = root;
            int index;

            for (char i: substring) {
                index = i - 'a';

                if (node->children[index] == nullptr) {
                    node->children[index] = new TrieNode();
                }

                node = node->children[index];
            }

            node->is_end = true;
            node->end_values.push_back(value);
        }
    }

    std::vector<TV> search(std::string key) {
        for (auto i = key.begin(); i < key.end(); ++i) {
            *i = std::tolower(*i);
        }

        std::vector<TV> empty;

        if (root == nullptr) {
            return empty;
        }

        TrieNode* node = root;
        int index;

        for (char i: key) {
            index = i - 'a';

            if (node->children[index] == nullptr) {
                return empty;
            }

            node = node->children[index];
        }

        return node->end_values;
    }

    bool has_kids(TrieNode* node) {
        for (int i = 0; i < ALPHA_SIZE; ++i) {
            if (node->children[i] != nullptr) {
                return true;
            }
        }
        return false;
    }

    void remove(std::string key) {
        remove(root, key);
    }

    std::string toString(std::string sep) {
        return toString(root, sep, "");
    }

    void remove(TrieNode* node, std::string key) {
        if (node == nullptr) {
            throw std::invalid_argument("Given key is not in Trie structure.");
        }

        if (key.empty()) {
            node->is_end = false;

            if (!has_kids(node)) {
                delete node;
            }
            return;
        }

        int index = key[0] - 'a';
        remove(node->children[index], key.erase(0, 1));

        if (!has_kids(node) and !node->is_end) {
            delete node;
        }
    }

    std::string toString(TrieNode* node, const std::string& sep, const std::string& prefix) {
        if (node == nullptr) {
            return "";
        }
        std::string result;

        if (node->is_end) {
            result += prefix + sep;
        }

        for (int i = 0; i < ALPHA_SIZE; ++i) {
            if (node->children[i] != nullptr) {
                result += toString(node->children[i], sep, prefix + char('a' + i));
            }
        }

        return result;
    }
};

#endif