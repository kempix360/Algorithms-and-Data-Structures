#pragma once
#include <iostream>
#include "Vec.h"

class CSS {
private:
    struct Node {
        Vector selectors;
        Vector attributes;
        Vector values;
        Node* next;
        Node* prev;

        Node() : next(nullptr), prev(nullptr) {}
    };

    Node* head;
    Node* tail;
    int size;

public:
    // konstruktory
    CSS() : head(nullptr), tail(nullptr), size(0) {}

    // destruktor
    ~CSS() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    // metody
    void add_section(Vector selectors, Vector attributes, Vector values) {
        Node* new_node = new Node;
        new_node->selectors = selectors;
        new_node->attributes = attributes;
        new_node->values = values;

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

    Vector& get_selectors(int index) {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index out of range");
        }
        Node* current = head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }
        return current->selectors;
    }

    Vector& get_attributes(int index) {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index out of range");
        }
        Node* current = head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }
        return current->attributes;
    }

    Vector& get_values(int index) {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index out of range");
        }
        Node* current = head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }
        return current->values;
    }

    int get_size() const {
        return size;
    }
};

