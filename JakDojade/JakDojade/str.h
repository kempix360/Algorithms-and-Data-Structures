#pragma once
#include <iostream>

class String {
private:
    char* data;
    int size;
    int capacity;
    void resize(int new_capacity) {
        if (new_capacity <= capacity) return;
        char* new_data = new char[new_capacity + 1];
        for (int i = 0; i < size; ++i) {
            new_data[i] = data[i];
        }
        delete[] data;
        data = new_data;
        capacity = new_capacity;
    }
public:
    String() : data(nullptr), size(0), capacity(0) {}
    String(const char* str)
    {
        if (str != nullptr)
        {
            size = strlen(str);
            capacity = size;
            data = new char[size + 1];
            for (int i = 0; i < size + 1; i++)
            {
                data[i] = str[i];
            }
        }
        else
        {
            data = nullptr;
            size = 0;
            capacity = 0;
        }
    }

    String(const String& other) : size(other.size), capacity(other.capacity) {
        data = new char[capacity + 1];
        for (int i = 0; i < size + 1; ++i) {
            data[i] = other.data[i];
        }
    }

    ~String() {
        if (data != nullptr)
            delete[] data;
        data = nullptr;
        size = 0;
        capacity = 0;
    }

    String& operator=(const String& other) {
        if (this == &other) return *this;
        resize(other.size);
        size = other.size;
        for (int i = 0; i < size + 1; ++i) {
            data[i] = other.data[i];
        }
        return *this;
    }

    char& operator[](int index) {
        return data[index];
    }

    const char& operator[](int index) const {
        return data[index];
    }

    int getLength() const {
        return size;
    }

    const char* getString() const {
        return data;
    }

    void append_char(char c) {
        if (size >= capacity) {
            resize(capacity * 2 + 1);
        }
        data[size] = c;
        ++size;
        data[size] = '\0';
    }

    void clear() {
        if (data != nullptr)
            delete[] data;
        data = nullptr;
        size = 0;
        capacity = 0;
    }
    void remove_char(char c) {
        int index = 0;
        for (int i = 0; i < size; ++i) {
            if (data[i] != c) {
                data[index] = data[i];
                ++index;
            }
        }
        data[index] = '\0';
        size = index;
    }

    bool operator==(const String& other) const {
        if (size != other.size) return false;
        for (int i = 0; i < size; ++i) {
            if (data[i] != other.data[i]) {
                return false;
            }
        }
        return true;
    }

    bool operator!=(const String& other) const {
        return !(*this == other);
    }

    friend std::ostream& operator<<(std::ostream& os, const String& str) {
        os << str.data;
        return os;
    }
    friend std::istream& operator>>(std::istream& is, String& str) {
        char buffer[1024];
        is >> buffer;
        str = buffer;
        return is;
    }
};