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
    // konstruktor
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
    void add_attribute(String name, String value) {
        Node* new_node = new Node;
        new_node->attribute.name = name;
        new_node->attribute.value = value;

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
    void add_name(String& name) {
        Node* new_node = new Node;
        new_node->attribute.name = name;

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

    void add_value(String& value) {
        if (tail == nullptr) {
            throw std::out_of_range("No name added yet");
        }

        if (value == nullptr) {
            throw std::invalid_argument("Value is null");
        }

        tail->attribute.value = value;
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

    int get_size() const {
        return size;
    }

    Attribute& operator[](int index) {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index out of range");
        }
        Node* current = head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }
        return current->attribute;
    }

    friend std::ostream& operator<<(std::ostream& os, const List_of_Attributes& attributes) {
        Node* current = attributes.head;
        while (current != nullptr) {
            os << current->attribute.name << ": " << current->attribute.value << "\n";
            current = current->next;
        }
        return os;
    }

    void print_attribute(int index) const {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index out of range");
        }
        Node* current = head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }
        std::cout << current->attribute.name << ": " << current->attribute.value << "\n";
    }



};