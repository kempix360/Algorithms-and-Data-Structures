#pragma once
#include <iostream>

class String{
private:
    char* data;
    int size;

public:
    // Konstruktory
    String() : data(nullptr), size(0) {}
    String(const char* str)
    {
        if (str != nullptr)
        {
            size = strlen(str);
            data = new char[size + 1];
            for (int i = 0; i < size + 1; i++)
            {
                data[i] = str[i];
            }
            data[size] = '\0';
        }
        else
        {
            data = nullptr;
            size = 0;
        }
    }
    String(const String& other) : size(other.size) {
        data = new char[size];
        for (int i = 0; i < size; ++i) {
            data[i] = other.data[i];
        }
        data[size - 1] = '\0';
    }

    // Destruktor
    ~String() {
        if (data != nullptr)
            delete[] data;
        data = nullptr;
        size = 0;
    }

    // Przypisanie
    String& operator=(const String& other) {
        if (data != nullptr)
            delete[] data;
        size = other.size;
        data = new char[size];
        for (int i = 0; i < size; ++i) {
            data[i] = other.data[i];
        }
        data[size] = '\0';
        return *this;
    }
    String& operator=(char* str) {
        if (data != nullptr)
            delete[] data;
        size = 0;
        while (str[size] != '\0') {
            ++size;
        }
        data = new char[size];
        for (int i = 0; i < size; ++i) {
            data[i] = str[i];
        }
        data[size-1] = '\0';
        return *this;
    }


    // Dostêp do elementów
    char& operator[](int index) {
        return data[index];
    }
    const char& operator[](int index) const {
        return data[index];
    }

    // Metody
    int getLength() const {
        return size;
    }
    const char* getString() const {
        return data;
    }
    void append(const char* str) {
        int new_size = 0;
        while (str[new_size] != '\0') {
            ++new_size;
        }
        char* new_data = new char[size + new_size + 1];
        for (int i = 0; i < size; ++i) {
            new_data[i] = data[i];
        }
        for (int i = 0; i < new_size; ++i) {
            new_data[size + i] = str[i];
        }
        new_data[size + new_size] = '\0';
        delete[] data;
        data = new_data;
        size += new_size;
    }
    void clear() {
        if (data != nullptr)
            delete[] data;
        data = nullptr;
        size = 0;
    }

    void removewhitespaceend() {
        if (size <= 0)
            return;
        char* new_data = new char[size];
        int counter = 0;
        for (int i = size - 2; i >= 0; i--)
        {
            if (data[i] == ' ' || data[i] == '\n')
                counter++;
            else
                break;
          
        }
        for (int i = 0; i < size-counter-1; i++)
        {
            new_data[i] = data[i];
        }
        new_data[size-counter-1] = '\0';
        delete[] data;
        data = new_data;
        size = size-counter-1;

    }
    void remove_last_char() {
        if (size <= 0) return;
        char* new_data = new char[size];

        for (int i = 0; i < size-1; i++)
        {
            new_data[i] = data[i];
        }
        new_data[size-1] = '\0';
        delete[] data;
        data = new_data;
        size--;
    }


    void remove_char(char c) {
        if (size <= 0) return;
        char* new_data = new char[size];

        int j = 0;
        for (int i = 0; i < size; i++)
        {
            if (data[i] != c) {
                new_data[j] = data[i];
                j++;
            }
        }
        new_data[j-1] = '\0';
        delete[] data;
        data = new_data;
        size = j;
    }

    // Operatory
    friend String operator+(const String& lhs, const String& rhs) {
        String result;
        result.size = lhs.size + rhs.size;
        result.data = new char[result.size + 1];
        char* ptr = result.data;
        for (int i = 0; i < lhs.size; ++i) {
            *ptr++ = lhs.data[i];
        }
        for (int i = 0; i < rhs.size; ++i) {
            *ptr++ = rhs.data[i];
        }
        *ptr = '\0';
        return result;
    }

    friend bool operator==(const String& lhs, const String& rhs) {
        if (lhs.size != rhs.size) {
            return false;
        }
        for (int i = 0; i < lhs.size; ++i) {
            if (lhs.data[i] != rhs.data[i]) {
                return false;
            }
        }
        return true;
    }
    friend bool operator!=(const String& lhs, const String& rhs) {
        return !(lhs == rhs);
    }

    friend std::ostream& operator<<(std::ostream& os, const String& str) {
        os << str.data;
        return os;
    };

    friend std::istream& operator>>(std::istream& is, String& str) {
        char buffer[256];
        is >> buffer;
        str.clear();
        str.append(buffer);
        return is;
    };

    bool CommandSection() {
        int n = size - 3;
        for (int i = 0; i < n; i++) {
            if (data[i] == '?' && data[i + 1] == '?' && data[i + 2] == '?' && data[i + 3] == '?') {
                std::cout << "Poczatek sekcji komend" << std::endl;
                delete[] data;
                data = nullptr;
                return true;
            }
        }
        return false;
    }

    bool cssSection() {
        int n = size - 3;
        for (int i = 0; i < n; i++) {
            if (data[i] == '*' && data[i + 1] == '*' && data[i + 2] == '*' && data[i + 3] == '*') {
                std::cout << "Poczatek sekcji css" << std::endl;
                delete[] data;
                data = nullptr;
                return true;
            }
        }
        return false;
    }
};
