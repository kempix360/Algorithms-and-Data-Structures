#pragma once
#include <iostream>
#include "Str.h"

class Vector {
private:
    String* arr;
    int size;
    int capacity;

public:
    // konstruktory
    Vector() {
        size = 0;
        capacity = 16;
        arr = new String [capacity];
    }

    Vector(int initial_size) {
        arr = new String [initial_size];
        size = 0;
        capacity = initial_size;
    }

    // destruktor
    ~Vector() {
        if (arr!=nullptr)
            delete[] arr;
        arr = nullptr;
    }

    // metody
    int getSize() const {
        return size;
    }

    int getCapacity() const {
        return capacity;
    }

    void clear() {
        delete[] arr;
        size = 0;
        capacity = 16;
        arr = new String[capacity];
    }

    Vector& operator=(const Vector& other) {
        if (this == &other) {
            return *this;
        }
        delete[] arr;
        arr = new String[other.capacity];
        size = other.size;
        capacity = other.capacity;
        for (int i = 0; i < size; i++) {
            *(arr + i) = *(other.arr + i);
            //arr[i] = other.arr[i];
        }
        return *this;
    }

    void push_back(const String& element) {
        if (size >= capacity) {
            capacity *= 2;
            String* new_arr = new String[capacity];
            for (int i = 0; i < size; i++) {
                //new_arr[i] = arr[i];
                *(new_arr + i) = *(arr + i);
            }
            delete[] arr;
            arr = new_arr;
        }
        //arr[size] = element;
        *(arr + size) = element;
        size++;
    }


    const String& operator[](int index) const {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index out of range");
        }
        return *(arr+index);
    }

    friend std::ostream& operator<<(std::ostream& os, const Vector& vec) {
        for (int i = 0; i < vec.getSize(); i++) {
            os << vec[i] << std::endl;
        }
        return os;
    }

};

