#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <iostream>
#include "List.h"

using namespace std;

template<class Record>
class priority_queue {
public:
    priority_queue();
    ~priority_queue();
    priority_queue(const priority_queue& copy);
    void operator=(const priority_queue& copy);
    bool empty() const;
    int size() const;
    const Record& top() const;
    void push(const Record& x);
    void pop();

private:
    MyList<Record> heap;

    // Private helper functions
    void build_heap();
    void sift_down(int start, int end);
};

template<class Record>
priority_queue<Record>::priority_queue() {
    build_heap();
}

template<class Record>
priority_queue<Record>::~priority_queue() {
    heap.clear();
}

template<class Record>
priority_queue<Record>::priority_queue(const priority_queue& copy) {
    heap = copy.heap;
}

template<class Record>
void priority_queue<Record>::operator=(const priority_queue& copy) {
    if (this != &copy) {
        heap = copy.heap;
    }
}

template<class Record>
bool priority_queue<Record>::empty() const {
    return heap.empty();
}

template<class Record>
int priority_queue<Record>::size() const {
    return heap.size();
}

template<class Record>
const Record& priority_queue<Record>::top() const {
    if (!empty())
        return heap.retrieve(0);
    else
        throw underflow_error("priority_queue is empty");
}

template<class Record>
void priority_queue<Record>::push(const Record& x) {
    heap.insert(heap.size(), x);
    int pos = heap.size() - 1;
    while (pos > 0) {
        int parent = (pos - 1) / 2;
        if (heap.retrieve(parent) >= heap.retrieve(pos))
            break;
        heap.swap(parent, pos);
        pos = parent;
    }
}

template<class Record>
void priority_queue<Record>::pop() {
    if (!empty()) {
        heap.swap(0, heap.size() - 1);
        Record x;
        heap.remove(heap.size() - 1, x);
        sift_down(0, heap.size());
    } else {
        throw underflow_error("priority_queue is empty");
    }
}

template<class Record>
void priority_queue<Record>::build_heap() {
    for (int i = heap.size() / 2 - 1; i >= 0; i--) {
        sift_down(i, heap.size());
    }
}

template<class Record>
void priority_queue<Record>::sift_down(int start, int end) {
    int root = start;
    while (root * 2 + 1 < end) {
        int child = root * 2 + 1;
        if (child + 1 < end && heap.retrieve(child) < heap.retrieve(child + 1))
            child++;
        if (heap.retrieve(root) >= heap.retrieve(child))
            return;
        heap.swap(root, child);
        root = child;
    }
}

#endif 
