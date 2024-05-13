#pragma once
#include "list_of_selectors.h"
#include "list_of_attributes.h"
#include "css_section.h"

class Section_List {
private:
    struct Node {
        Section tab[8];
        Node* next;
        Node* prev;

        Node() : next(nullptr), prev(nullptr) {}
    };

    Node* head;
    Node* tail;
    int size;

public:
    // konstruktor
    Section_List() : head(nullptr), tail(nullptr), size(0) {}

    // destruktor
    ~Section_List() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    // metody
    void add_section(const Section& section) {
        if (tail == nullptr || size % 8 == 0) {
            Node* new_node = new Node;
            new_node->tab[0] = section;

            if (head == nullptr) {
                head = new_node;
                tail = new_node;
            }
            else {
                tail->next = new_node;
                new_node->prev = tail;
                tail = new_node;
            }
        }
        else {
            tail->tab[size % 8] = section;
        }
        size++;
    }

    void delete_section(int index) {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index out of range");
        }

        Node* current = head;
        int node_index = index / 8;
        int section_index = index % 8;

        for (int i = 0; i < node_index; i++) {
            current = current->next;
        }

        if (section_index == 0) {
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
        }
        else {
            for (int i = section_index; i < 7; i++) {
                current->tab[i] = current->tab[i + 1];
            }
        }

        size--;
    }

    int get_size() const {
        return size;
    }

    Section& operator[](int index) {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index out of range");
        }

        Node* current = head;
        int node_index = index / 8;
        int section_index = index % 8;

        for (int i = 0; i < node_index; i++) {
            current = current->next;
        }

        return current->tab[section_index];
    }

    friend std::ostream& operator<<(std::ostream& os, const Section_List& sections) {
        Node* current = sections.head;
        int index = 0;

        while (current != nullptr) {
            for (int i = 0; i < 8; i++) {
                if (index >= sections.size) {
                    break;
                }

                os << current->tab[i].selectors << current->tab[i].attributes << "\n";
                index++;
            }

            current = current->next;
        }

        return os;
    }
};