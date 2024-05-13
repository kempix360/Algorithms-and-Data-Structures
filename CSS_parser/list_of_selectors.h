#pragma once
#include <iostream>
#include "Vec.h"
#include "Str.h"

class List_of_Selectors {
private:
    struct Node {
        String selector;
        Node* next;
        Node* prev;

        Node() : next(nullptr), prev(nullptr) {}
    };

    Node* head;
    Node* tail;
    int size;

public:
    // konstruktory
    List_of_Selectors() : head(nullptr), tail(nullptr), size(0) {}

    // destruktor
    ~List_of_Selectors() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    // metody
    void add_section(String s) {
        Node* new_node = new Node;
        new_node->selector = s;

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

    String& get_selector(int index) {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index out of range");
        }
        Node* current = head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }
        return current->selector;
    }

    int get_size() const {
        return size;
    }
    String& operator[](int index) {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index out of range");
        }
        Node* current = head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }
        return current->selector;
    }


    friend std::ostream& operator<<(std::ostream& os, const List_of_Selectors& selectors) {
        Node* current = selectors.head;
        while (current != nullptr) {
            os << current->selector << "\n";
            current = current->next;
        }
        return os;
    }
};
