#pragma once
#include <iostream>
#include "Vec.h"
#include "Str.h"
#include "Attribute_struct.h"

class List_of_Attributes {
private:
    struct Node {
        Attribute attribute;
        Node* next;
        Node* prev;

        Node() : next(nullptr), prev(nullptr) {}
    };

    Node* head;
    Node* tail;
    int size;

public:
    // konstruktory
    List_of_Attributes() : head(nullptr), tail(nullptr), size(0) {}

    // destruktor
    ~List_of_Attributes() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    // metody
    void add_section(String name, String value) {
        Attribute a;
        a.name = name;
        a.value = value;
        Node* new_node = new Node;
        new_node->attribute = a;

        if (head == nullptr) {
            head = new_node;
            tail = new_node;
        }
        else {
            tail->next = new_node;
            new_node->prev = tail;
            tail = new_node;
        }
        size++;
    }

    void delete_section(int index) {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index out of range");
        }

        Node* current = head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }

        if (current == head) {
            head = head->next;
        }
        else if (current == tail) {
            tail = tail->prev;
        }

        if (current->prev != nullptr) {
            current->prev->next = current->next;
        }
        if (current->next != nullptr) {
            current->next->prev = current->prev;
        }

        delete current;
        size--;
    }

    Attribute& get_attribute(int index) {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index out of range");
        }
        Node* current = head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }
        return current->attribute;
    }

    int get_size() const {
        return size;
    }
};
