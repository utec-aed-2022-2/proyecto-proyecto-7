#ifndef CIRCULARARRAY_H
#define CIRCULARARRAY_H

#include <algorithm>
#include <iostream>
#include <string>
#include <type_traits>

template<class T>
class CircularArray {
private:
    T* array;

    int capacity;

    int back;

    int front;

    int next(int index) {
        return (index + 1) % capacity;

    }

    int prev(int index) {
        return (index == 0) ? capacity - 1 : index - 1;
    }

public:
    CircularArray() {
        array = new T[1];
        capacity = 1;
        front = -1;
        back = -1;
    }

    explicit CircularArray(int _capacity) {
        if (_capacity <= 0) {
            throw std::invalid_argument("Cannot create array with given capacity.");
        }
        array = new T[_capacity];
        capacity = _capacity;
        front = -1;
        back = -1;
    }

    void push_front(T data) {
        if (prev(front) == back) {
            T* new_array = new T[capacity * 2];
            for (int i = 0; i < capacity; ++i) {
                new_array[i] = (*this)[i];
            }
            delete[] array;
            array = new_array;
            capacity = capacity * 2;
            front = 0;
            back = (capacity / 2) - 1;
        }

        if (front == -1) {
            front = next(front);
            array[front] = data;
        }
        else {
            array[prev(front)] = data;
            front = prev(front);
        }
        if (back == -1) {
            back = front;
        }
    }

    void push_back(T data) {
        if (next(back) == front) {
            T* new_array = new T[capacity * 2];
            for (int i = 0; i < capacity; ++i) {
                new_array[i] = (*this)[i];
            }
            delete[] array;
            array = new_array;
            capacity = capacity * 2;
            front = 0;
            back = (capacity / 2) - 1;
        }
        array[next(back)] = data;
        back = next(back);
        if (front == -1) {
            front = next(front);
        }
    }

    void insert(T data, int pos) {
        if (pos >= this->size() || pos < 0) {
            throw std::invalid_argument("Can not access given index");
        }

        if (this->size() == capacity) {
            T* new_array = new T[capacity * 2];
            for (int i = 0; i < capacity; ++i) {
                new_array[i] = (*this)[i];
            }
            delete[] array;
            array = new_array;
            capacity *= 2;
            front = 0;
            back = (capacity / 2) - 1;
        }
        back = next(back);

        T* new_array = new T[capacity];
        for (int i = 0; i < pos; ++i) {
            new_array[i] = (*this)[i];
        }
        new_array[pos] = data;
        for (int i = pos + 1; i < this->size(); ++i) {
            new_array[i] = (*this)[i - 1];
        }
        delete[] array;
        array = new_array;
    }

    T pop_front() {
        if (this->size() == 0) {
            throw std::invalid_argument("Internal array is empty. No data to show.");
        }
        T tmp = array[front];
        if (this->size() == 1) {
            front = -1;
            back = -1;
        }
        else {
            front = next(front);
        }
        return tmp;
    }

    T pop_back() {
        if (this->size() == 0) {
            throw std::invalid_argument("Internal array is empty. No data to show.");
        }
        T tmp = array[back];
        if (this->size() == 1) {
            front = -1;
            back = -1;
        }
        else {
            back = prev(back);
        }
        return tmp;
    }

    bool is_full() {
        if (next(back) == front) {
            return true;
        }
        return false;
    }

    bool is_empty() {
        if (this->size() == 0) {
            return true;
        }
        return false;
    }

    int size() {
        if (back == -1 && front == -1) {
            return 0;
        }
        if (back == front) {
            return 1;
        }
        else {
            return front < back ? (back - front + 1) : (capacity - front + back + 1);
        }
    }

    void clear() {
        delete[] array;
        array = new T[capacity];
        front = -1;
        back = -1;
    }

    T& operator[](int index) {
        return array[(index + front) % capacity];
    }

    virtual ~CircularArray() {
        delete[] array;
    }
};

#endif