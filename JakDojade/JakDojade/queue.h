#pragma once
#include <iostream>

template<typename T>
class Queue {
private:
    struct Node {
        T data;
        Node* next;
        Node(T d) : data(d), next(nullptr) {}
    };
    Node* head;
    Node* tail;
    int count;
public:
    Queue() : head(nullptr), tail(nullptr), count(0) {}
    ~Queue() {
        while (!empty()) {
            pop();
        }
    }
    void push(T val) {
        Node* newNode = new Node(val);
        if (empty()) {
            head = tail = newNode;
        }
        else {
            tail->next = newNode;
            tail = newNode;
        }
        count++;
    }
    T pop() {
        if (empty()) {
            throw "Queue is empty.";
        }
        T val = head->data;
        Node* temp = head;
        head = head->next;
        delete temp;
        count--;
        if (empty()) {
            tail = nullptr;
        }
        return val;
    }
    bool empty() {
        return count == 0;
    }
    int size() {
        return count;
    }
    T front() {
        if (empty()) {
            throw "Queue is empty.";
        }
        return head->data;
    }
    T back() {
        if (empty()) {
            throw "Queue is empty.";
        }
        return tail->data;
    }
};
