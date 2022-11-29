#ifndef V1_BTREENODE_H
#define V1_BTREENODE_H

#include <iostream>

template<typename TK, typename TV>
struct BTreeNode {
    TK* keys;

    TV* values;

    BTreeNode** children;

    int count;

    bool leaf;

    BTreeNode() : keys(nullptr), children(nullptr), count(0), leaf(true) {}

    BTreeNode(int M, bool _leaf = true) {
        count = 0;
        leaf = _leaf;
        keys = new TK[M - 1];
        values = new TV[M - 1];
        children = new BTreeNode<TK, TV>* [M];
        for (int i = 0; i < M; i++) children[i] = nullptr;
    }

    void display() {
        std::cout << "Keys: ";
        for (int i = 0; i < count; ++i) {
            std::cout << keys[i] << ", ";
        }

        std::cout << "Values: ";
        for (int i = 0; i < count; ++i) {
            std::cout << values[i] << ", ";
        }

        std::cout << std::endl;
    }

    ~BTreeNode() {
        delete[] keys;
        delete[] values;
        delete[] children;
    }
};

#endif
