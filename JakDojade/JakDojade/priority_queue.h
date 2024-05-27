#pragma once
#include <iostream>
#include "vec.h"

template<typename T, typename P = int>
class Priority_Queue {
private:
    struct Node {
        T data;
        P priority;
        Node() : data(T()), priority(P()) {}
        Node(T d, P p) : data(d), priority(p) {}
    };
    Vector<Node> heap;

    void heapify_up(int idx) {
        if (idx == 0) {
            return;
        }
        int parent_idx = (idx - 1) / 2;
        if (heap[idx].priority < heap[parent_idx].priority) {
            Node temp(heap[idx].data, heap[idx].priority);
            heap[idx].data = heap[parent_idx].data;
            heap[idx].priority = heap[parent_idx].priority;
            heap[parent_idx].data = temp.data;
            heap[parent_idx].priority = temp.priority;
            heapify_up(parent_idx);
        }
    }

    void heapify_down(int idx) {
        int left_child_idx = 2 * idx + 1;
        int right_child_idx = 2 * idx + 2;
        int smallest_child_idx = idx;

        if (left_child_idx < heap.getSize() && heap[left_child_idx].priority < heap[smallest_child_idx].priority) {
            smallest_child_idx = left_child_idx;
        }

        if (right_child_idx < heap.getSize() && heap[right_child_idx].priority < heap[smallest_child_idx].priority) {
            smallest_child_idx = right_child_idx;
        }

        if (smallest_child_idx != idx) {
            Node temp(heap[idx].data, heap[idx].priority);
            heap[idx].data = heap[smallest_child_idx].data;
            heap[idx].priority = heap[smallest_child_idx].priority;
            heap[smallest_child_idx].data = temp.data;
            heap[smallest_child_idx].priority = temp.priority;
            heapify_down(smallest_child_idx);
        }
    }

public:
    Priority_Queue() {}

    void push(T val, P priority) {
        Node node(val, priority);
        heap.push_back(node);
        heapify_up(heap.getSize() - 1);
    }

    T pop() {
        if (empty()) {
            throw "Queue is empty.";
        }

        T val = heap[0].data;
        heap[0] = heap[heap.getSize() - 1];
        heap.pop_back();
        heapify_down(0);
        return val;
    }

    bool empty() {
        return heap.empty();
    }

    int size() {
        return heap.getSize();
    }

    T front() {
        if (empty()) {
            throw "Queue is empty.";
        }
        return heap[0].data;
    }
};
