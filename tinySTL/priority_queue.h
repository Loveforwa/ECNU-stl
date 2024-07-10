#include<iostream>

template <class Record>
class priority_queue {
public:
    priority_queue(size_t n) : size(n), cpa(new Record[size]), current_size(0) {}
    push(Record element);

    void push(const Record& element);
    void pop();
    bool empty() const;

private:
    size_t size;
    size_t *cpa;
    size_t current_size;

    void heapify_down(int i);
    void heapify_up(int i);
};


template <class Record>
void priority_queue<Record>::push(const Record& element) {
    if (current_size == size) {
        throw std::overflow_error("Priority queue is full");
    }

    cpa[current_size] = element;
    heapify_up(current_size);
    current_size++;
}

template <class Record>
void priority_queue<Record>::pop() {
    if (current_size == 0) {
        throw std::underflow_error("Priority queue is empty");
    }

    cpa[0] = cpa[current_size - 1];
    current_size--;
    heapify_down(0);
}

template <class Record>
bool priority_queue<Record>::empty() const {
    return current_size == 0;
}

template <class Record>
void priority_queue<Record>::heapify_down(int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < current_size && cpa[left] > cpa[largest]) {
        largest = left;
    }

    if (right < current_size && cpa[right] > cpa[largest]) {
        largest = right;
    }

    if (largest != i) {
        std::swap(cpa[i], cpa[largest]);
        heapify_down(largest);
    }
}

template <class Record>
void priority_queue<Record>::heapify_up(int i) {
    if (i == 0) return;

    int parent = (i - 1) / 2;

    if (cpa[i] > cpa[parent]) {
        std::swap(cpa[i], cpa[parent]);
        heapify_up(parent);
    }
}


