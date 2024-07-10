#include<iostream>

#define SIZE 10
template<class entry_node>
class queue{
    private:
    entry_node Q[SIZE];
    entry_node front = -1,rear = -1;
    bool isempty() { return (front == -1 && rear == -1); }
    bool isfull() { return ((rear + 1) % SIZE == front); }

    public:
    queue(const queue& other) {
        std::copy(std::begin(other.Q), std::end(other.Q), std::begin(Q));
        front = other.front;
        rear = other.rear;
    }
    queue& operator=(const queue& other) {
        if (this != &other) {
            std::copy(std::begin(other.Q), std::end(other.Q), std::begin(Q));
            front = other.front;
            rear = other.rear;
        }
        return *this;
    }
    void Enqueue(entry_node data); 
    void dequeue();
    entry_node Front();
    int size();
    void Print();
};

template<class entry_node>
void queue<entry_node>::Enqueue(entry_node data){
    if(isempty()){
        front = rear = 0;
        Q[front] = data;
    }else if(isfull()){
        std::cerr << "the queue is full!"<< std::endl;
    }else{
        rear = (rear + 1) % SIZE;
        Q[rear] = data;
    }
}

template<class entry_node>
void queue<entry_node>::dequeue(){
    if(isempty()){std::cerr << "the queue is empty!"<< std::endl;}
    else if(front == rear){
        front = rear = -1;
    }else {
        front = (front + 1 ) % SIZE;
    }
}

template<class entry_node>
entry_node queue<entry_node>::Front(){
    if(isempty()){std::cerr << "the queue is empty!"<<std::endl;return INT_MIN;}
    else{
        return Q[front];
    }
}
template<class entry_node>
int queue<entry_node>::size(){
    if (isempty()) return 0;
    if (rear >= front) {
        return rear - front + 1;
    } else {
        return SIZE - front + rear + 1;
    }
}
template<class entry_node>
void queue<entry_node>::Print() {
    if(isempty()) {
        std::cout << "Queue is empty\n";
        return;
    }
    std::cout << "Queue: ";
    for(int i = front; i != rear; i = (i + 1) % SIZE) {
        std::cout << Q[i] << " ";
    }
    std::cout << Q[rear] << std::endl;
}