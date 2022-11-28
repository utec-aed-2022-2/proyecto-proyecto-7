#ifndef V1_BTREE_H
#define V1_BTREE_H

#include "BTreeNode.h"

template<typename TK, typename TV>
class BTree {
private:
    BTreeNode<TK, TV>* root;

    int M;

    struct ExtractionResult {
        TK key;

        TV value;

        BTreeNode<TK, TV>* right_tree;

        BTreeNode<TK, TV>* left_tree;

        ExtractionResult() : left_tree(nullptr), right_tree(nullptr) {}

        ExtractionResult(TK _k, TV _v, BTreeNode<TK, TV>* _left_tree, BTreeNode<TK, TV>* _right_tree) : key(_k), value(_v),
                                                                                                        left_tree(_left_tree),
                                                                                                        right_tree(_right_tree) {}
    };

public:
    explicit BTree(int M = 5) : M(M), root(nullptr) {}

    std::vector<TV> search(TK key) {
        std::vector<TV> result;
        range_search(root, key, key, result);
        return result;
    }

    void remove(TK key) {
        if (root != nullptr) {
            remove(root, key);

            if (root->count == 0) {
                BTreeNode<TK, TV>* temp = root;
                root = root->children[0];
                delete temp;
            }
        }
    }

    void remove(BTreeNode<TK, TV>*& node, TK key) {
        int i = 0;

        while (i < node->count && key > node->keys[i]) {
            i++;
        }

        if (node->leaf) {
            if (i < node->count && node->keys[i] == key) {
                popElement(node, i);
            }
        }
        else {
            if (i < node->count && node->keys[i] == key) {
                key = minKey(node->children[i + 1]);
                node->keys[i] = key;
                i = i + 1;
            }

            remove(node->children[i], key);

            if (node->children[i]->count < (M - 1) / 2) {
                ExtractionResult extract_result;
                if (i > 0 && node->children[i - 1]->count > (M - 1) / 2) {
                    extract_result = extractLast(node->children[i - 1]);
                    relocate_left(node->children[i], node->keys[i - 1], node->values[i - 1], extract_result.right_tree);
                    node->keys[i - 1] = extract_result.key;
                    node->values[i - 1] = extract_result.value;
                }
                else if (i < node->count && node->children[i + 1]->count > (M - 1) / 2) {
                    extract_result = extractFirst(node->children[i + 1]);
                    relocate_right(node->children[i], node->keys[i], node->values[i], extract_result.left_tree);
                    node->keys[i] = extract_result.key;
                    node->values[i] = extract_result.value;
                }
                else if (i > 0) {
                    join(node->children[i - 1], node->keys[i - 1], node->values[i - 1], node->children[i]);
                    delete node->children[i];
                    popElement(node, i - 1);
                }
                else {
                    join(node->children[i], node->keys[i], node->values[i], node->children[i + 1]);
                    delete node->children[i + 1];
                    popElement(node, i);
                }
            }
        }
    }

    TK minKey(BTreeNode<TK, TV>* node) {
        while (!node->leaf)
            node = node->children[0];
        return node->keys[0];
    }

    ExtractionResult extractLast(BTreeNode<TK, TV>*& node) {
        ExtractionResult result;
        result.key = node->keys[node->count - 1];
        result.value = node->values[node->count - 1];
        result.right_tree = node->children[node->count];
        node->count--;
        return result;
    }

    ExtractionResult extractFirst(BTreeNode<TK, TV>*& node) {
        ExtractionResult result;
        result.key = node->keys[0];
        result.value = node->values[0];
        result.left_tree = node->children[0];
        int i = 0;
        for (; i < node->count - 1; i++) {
            node->keys[i] = node->keys[i + 1];
            node->values[i] = node->values[i + 1];
            node->children[i] = node->children[i + 1];
        }
        node->children[i] = node->children[i + 1];
        node->count--;
        return result;
    }

    void popElement(BTreeNode<TK, TV>*& node, int pos) {
        int i = pos;
        for (; i < node->count - 1; i++) {
            node->keys[i] = node->keys[i + 1];
            node->values[i] = node->values[i + 1];
            node->children[i + 1] = node->children[i + 2];
        }
        node->count--;
    }

    void join(BTreeNode<TK, TV>*& left_nodo, TK middle, TV mid_val, BTreeNode<TK, TV>*& right_node) {
        relocate_right(left_nodo, middle, mid_val, right_node->children[0]);
        for (int i = 0; i < right_node->count; ++i)
            relocate_right(left_nodo, right_node->keys[i], right_node->values[i], right_node->children[i + 1]);
    }

    std::vector<TV> range_search(TK begin, TK end) {
        std::vector<TV> result;
        range_search(root, begin, end, result);
        return result;
    }

    void range_search(BTreeNode<TK, TV>* node, TK begin, TK end, std::vector<TV>& result) {
        if (node == nullptr) {
            return;
        }

        int i;
        for (i = 0; i < node->count; ++i) {
            if (begin <= node->keys[i]) {
                range_search(node->children[i], begin, end, result);
            }
            if (begin <= node->keys[i] && node->keys[i] <= end) {
                result.push_back(node->values[i]);
            }
        }
        if (node->keys[i] < end) {
            range_search(node->children[i], begin, end, result);
        }
    }

    std::vector<TV> get_sorted_elements() {
        std::vector<TV> result;
        get_sorted_elements(root, result);
        return result;
    }

    void get_sorted_elements(BTreeNode<TK, TV>* node, std::vector<TV>& result) {
        if (root == nullptr) {
            return;
        }

        int i;
        for (i = 0; i < node->count; i++) {
            if (node->children[i] != nullptr) {
                get_sorted_elements(node->children[i], result);
            }
            result.push_back(node->values[i]);
        }
        if (node->children[i] != nullptr) {
            get_sorted_elements(node->children[i], result);
        }
    }

    void insert(TK key, TV value) {
        if (root == nullptr) {
            root = new BTreeNode<TK, TV>(M, true);
            root->keys[0] = key;
            root->values[0] = value;
            root->count = 1;
        }
        else {
            ExtractionResult* split_result = insert(root, key, value);
            if (split_result != nullptr) {
                auto* parent = new BTreeNode<TK, TV>(M, false);
                parent->keys[0] = split_result->key;
                parent->values[0] = split_result->value;
                parent->children[0] = root;
                parent->children[1] = split_result->right_tree;
                parent->count = 1;
                root = parent;
            }
        }
    }

    ExtractionResult* insert(BTreeNode<TK, TV>*& node, TK key, TV value) {
        int i;

        // verificar si es llave repetida
        i = 0;
        while (i < node->count && key > node->keys[i])
            i++;

        // es nodo hoja
        if (node->leaf) {
            // si la hoja tiene espacio, insertar
            if (node->count < M - 1)
                relocate(node, key, value);
                // dividir y retornar el resultado al antecesor
            else if (M % 2 == 0)
                return split_par(node, key, value);
            else
                return split_impar(node, key, value);
        }
            // es nodo interno
        else {
            // insertar en el hijo respectivo
            ExtractionResult* split_result = insert(node->children[i], key, value);
            // si split_result != null es porque se produjo un split en el children[i]
            if (split_result != nullptr) {
                // si hay espacio, reubicar el split_result
                if (node->count < M - 1)
                    relocate_right(node, split_result->key, split_result->value, split_result->right_tree);
                    // caso, dividir y retornar el nuevo nodo al antecesor
                else if (M % 2 == 0)
                    return split_par(node, split_result->key, split_result->value, split_result->right_tree);
                else
                    return split_impar(node, split_result->key, split_result->value, split_result->right_tree);
            }
        }
        return nullptr;
    }

    void relocate(BTreeNode<TK, TV>*& node, TK key, TV value) {
        int i = node->count - 1;
        // se  mueve las keys para dejar espacio para la nueva key
        while (i >= 0 && key < node->keys[i]) {
            node->keys[i + 1] = node->keys[i];
            node->values[i + 1] = node->values[i];
            i--;
        }
        i++;
        node->keys[i] = key;
        node->values[i] = value;
        node->count++;
    }

    void relocate_right(BTreeNode<TK, TV>*& node, TK key, TV value, BTreeNode<TK, TV>* right_tree) {
        int i = node->count - 1;
        // se  mueve las keys y children para dejar espacio para la nueva key
        while (i >= 0 && key < node->keys[i]) {
            node->keys[i + 1] = node->keys[i];
            node->values[i + 1] = node->values[i];
            node->children[i + 2] = node->children[i + 1];
            i--;
        }
        i++;
        node->keys[i] = key;
        node->values[i] = value;
        node->children[i + 1] = right_tree;
        node->count++;
    }

    void relocate_left(BTreeNode<TK, TV>*& node, TK key, TV value, BTreeNode<TK, TV>* left_tree) {
        int i = node->count - 1;
        // se  mueve las keys y children para dejar espacio para la nueva key
        while (i >= 0 && key < node->keys[i]) {
            node->keys[i + 1] = node->keys[i];
            node->values[i + 1] = node->values[i];
            node->children[i + 2] = node->children[i + 1];
            i--;
        }
        node->children[i + 2] = node->children[i + 1];
        i++;
        node->keys[i] = key;
        node->values[i] = value;
        node->children[i] = left_tree;
        node->count++;
    }

    BTreeNode<TK, TV>* generate_right_node(BTreeNode<TK, TV>*& node, int from) {
        auto* right_node = new BTreeNode<TK, TV>(M, node->leaf);
        // copiar llaves e hijos desde el nodo original
        int i = from, j = 0;
        while (i < M - 1) // recordar que el nodo esta lleno
        {
            right_node->keys[j] = node->keys[i];
            right_node->values[j] = node->values[i];
            right_node->children[j] = node->children[i];
            i++;
            j++;
        }
        right_node->children[j] = node->children[i];
        right_node->count = j;
        return right_node;
    }

    ExtractionResult* split_par(BTreeNode<TK, TV>*& node, TK key, TV value, BTreeNode<TK, TV>* right_tree = nullptr) {
        // calcular el elemento central
        int m = (M - 1) / 2;
        TK middle_key = node->keys[m];
        TV middle_val = node->values[m];
        // crear nodo derecho desde m+1
        BTreeNode<TK, TV>* right_node = generate_right_node(node, m + 1);
        // actualizar la cantidad de elementos del nodo
        node->count = m;
        // insertar la key en el lado respectivo
        if (key < middle_key)
            relocate_right(node, key, value, right_tree);
        else
            relocate_right(right_node, key, value, right_tree);
        // retornar el elemento central y el nodo derecho
        return new ExtractionResult(middle_key, middle_val, nullptr, right_node);
    }

    ExtractionResult* split_impar(BTreeNode<TK, TV>*& node, TK key, TV value, BTreeNode<TK, TV>* right_tree = nullptr) {
        BTreeNode<TK, TV>* right_node;
        TK middle_key;
        TV middle_val;
        // calcular el elemento central correctamente
        int m = (M - 1) / 2;
        if (key > node->keys[m]) {
            right_node = generate_right_node(node, m + 1);
            middle_key = node->keys[m];
            middle_val = node->values[m];
            node->count = m;
            relocate_right(right_node, key, value, right_tree);
        }
        else {
            m = m - 1;
            right_node = generate_right_node(node, m + 1);
            if (key < node->keys[m]) {
                middle_key = node->keys[m];
                middle_val = node->values[m];
                node->count = m;
                relocate_right(node, key, value, right_tree);
            }
            else { // en caso que la llave a insertar ocupe la mitad
                middle_key = key;
                middle_val = value;
                node->count = m + 1;
                right_node->children[0] = right_tree;
            }
        }
        // retornar el elemento central y el nodo derecho
        return new ExtractionResult(middle_key, middle_val, nullptr, right_node);
    }
};

#endif