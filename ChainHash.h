
#ifndef V1_CHAINHASH_H
#define V1_CHAINHASH_H

#include <algorithm>
#include <stdexcept>
#include <forward_list>
#include <numeric>
#include <vector>

const float max_fill_factor = 0.5;

const int max_collision = 3;

template<typename KeyType, typename ValueType>
struct Entry {
    KeyType key;

    ValueType value;

    size_t hash_code;

    Entry(KeyType key, ValueType value, size_t hashCode) : key(key), value(value), hash_code(hashCode) {};
};

template<typename KeyType, typename ValueType>
class ChainHash {
public:
    std::forward_list<Entry<KeyType, ValueType>>* data_array;

    int capacity;

    int size = 0;

    std::hash<KeyType> get_hash;

public:
    explicit ChainHash(int capacity = 2) : capacity(capacity) {
        data_array = new std::forward_list<Entry<KeyType, ValueType>>[capacity];
    };

    float fill_factor() {
        return double(size) / (capacity * max_collision);
    }

    bool insert(KeyType key, ValueType value) {
        if (fill_factor() >= max_fill_factor) {
            rehashing();
        }

        size_t hash_code = get_hash(key);
        int index = hash_code % capacity;

        data_array[index].push_front(Entry(key, value, hash_code));
        ++size;

        return true;
    }

    std::vector<ValueType> get(KeyType key) {
        size_t hash_code = get_hash(key);
        int index = hash_code % capacity;

        std::vector<ValueType> result;

        if (!data_array[index].empty()) {
            for (auto entry: data_array[index]) {
                if (entry.key == key) {
                    result.push_back(entry.value);
                }
            }

        }

        return result;
    }

    void rehashing() {
        auto new_data_array = new std::forward_list<Entry<KeyType, ValueType>>[capacity * 2];

        for (int i = 0; i < capacity; ++i) {
            for (Entry<KeyType, ValueType>& entry: data_array[i]) {
                int new_index = entry.hash_code % (capacity * 2);
                new_data_array[new_index].push_front(entry);
            }

        }
        delete[] data_array;

        data_array = new_data_array;
        capacity = capacity * 2;
    }

    std::vector<ValueType> operator[](KeyType key) {
        size_t hash_code = get_hash(key);
        int index = hash_code % capacity;

        std::vector<ValueType> result;

        if (!data_array[index].empty()) {
            for (auto entry: data_array[index]) {
                if (entry.key == key) {
                    result.push_back(entry.value);
                }
            }

            return result;
        }

        throw std::invalid_argument("Given key is not found");
    }

    void remove(KeyType key) {
        size_t hash_code = get_hash(key);
        int index = hash_code % capacity;

        if (!data_array[index].empty()) {
            data_array[index].remove_if([key](Entry<KeyType, ValueType> e) { return key == e.key; });
        }
    }

    int bucket_count() {
        return capacity;
    }

    int bucket_size(int i_bucket) {
        return std::distance(data_array[i_bucket].begin(), data_array[i_bucket].end());
    }

    typename std::forward_list<Entry<KeyType, ValueType>>::iterator begin(int i_bucket) {
        return data_array[i_bucket].begin();
    }

    typename std::forward_list<Entry<KeyType, ValueType>>::iterator end(int i_bucket) {
        return data_array[i_bucket].end();
    }

    ~ChainHash() {
        for (int i = 0; i < capacity; ++i) {
            data_array[i].clear();
        }
        delete[] data_array;
    }
};

#endif
