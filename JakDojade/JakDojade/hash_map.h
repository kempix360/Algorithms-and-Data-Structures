#pragma once
#include <iostream>
#include "str.h"

class Hash_Map {
private:
    struct Hash_Node {
        String key;
        int value;
        Hash_Node* next;
        Hash_Node(String key, int value) : key(key), value(value), next(nullptr) {}
    };
    static const size_t size = 20000;
    Hash_Node** hash_array;
    size_t hash_func(const String& str) {
        size_t hash = 5381;
        for (int i = 0; i < str.getLength(); i++) {
            hash = ((hash << 5) + hash) + str[i];
        }
        return hash;
    }

public:
    Hash_Map() : hash_array(new Hash_Node* [size]()) {}
    ~Hash_Map() {
        for (int i = 0; i < size; i++) {
            Hash_Node* current = hash_array[i];
            while (current) {
                Hash_Node* next = current->next;
                delete current;
                current = next;
            }
        }
        delete[] hash_array;
    }

    void put(String key, int value) {
        int index = (int)hash_func(key);
        Hash_Node* node = hash_array[index%size];
        while (node) {
            if (node->key == key) {
                node->value = value;
                return;
            }
            node = node->next;
        }
        Hash_Node* new_node = new Hash_Node(key, value);
        new_node->next = hash_array[index % size];
        hash_array[index % size] = new_node;
    }

    int& get(String key) {
        int index = (int)hash_func(key);
        Hash_Node* node = hash_array[index % size];
        while (node) {
            if (node->key == key) {
                return node->value;
            }
            node = node->next;
        }
        index *= -1;
        return index;
    }

    friend std::ostream& operator<<(std::ostream& os, const Hash_Map& hm) {
        for (int i = 0; i < size; i++) {
            Hash_Node* current = hm.hash_array[i];
            while (current) {
                os << current->key << " : " << current->value << std::endl;
                current = current->next;
            }
        }
        os << std::endl;
        return os;
    }
};
