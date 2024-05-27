#pragma once
#include <iostream>

template <typename T>

class Vector {
private:
    T* array;
    int size;
    int capacity;

public:
    Vector() : array(nullptr), size(0), capacity(0) {}
    Vector(int size) : array(nullptr), size(size), capacity(size) {
        array = new T[size];
    }
    Vector(const Vector& other) : array(nullptr), size(other.size), capacity(other.capacity) {
        array = new T[capacity];
        for (int i = 0; i < size; i++) {
            array[i] = other.array[i];
        }
    }
    ~Vector() {
        delete[] array;
    }

    void push_back(const T& element) {
        if (size == capacity) {
            reserve(size == 0 ? 1 : size * 2);
        }
        array[size++] = element;
    }

    void pop_back() {
        if (size > 0) {
            size--;
        }
    }

    void clear() {
        delete[] array;
        size = 0;
        capacity = 0;
        array = nullptr;
    }

    bool empty() const {
        return size == 0;
    }

    void remove(int index) {
        if (index >= 0 && index < size) {
            for (int i = index; i < size - 1; i++) {
                array[i] = array[i + 1];
            }
            size--;
        }
    }

    T& operator[](int i) {
        return array[i];
    }

    Vector& operator=(const Vector& other) {
        if (this != &other) {
            T* newArray = new T[other.capacity];
            for (int i = 0; i < other.size; i++) {
                newArray[i] = other.array[i];
            }
            delete[] array;
            array = newArray;
            size = other.size;
            capacity = other.capacity;
        }
        return *this;
    }

    int getSize() const {
        return size;
    }

    int getCapacity() const {
        return capacity;
    }

    void reserve(int newCapacity) {
        if (newCapacity > capacity) {
            T* newArray = new T[newCapacity];
            for (int i = 0; i < size; i++) {
                newArray[i] = array[i];
            }
            delete[] array;
            array = newArray;
            capacity = newCapacity;
        }
    }

    friend std::ostream& operator<<(std::ostream& os, const Vector& v) {
        for (int i = 0; i < v.size; i++) {
            os << v.array[i];
        }
        os << std::endl;
        return os;
    }
};
