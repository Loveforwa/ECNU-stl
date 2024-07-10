#include <iostream>
//双端队列
//https://en.wikipedia.org/wiki/Double-ended_queue
typedef struct Node {
    char data; // 修改为 char 类型
    Node* next;
    Node* prev;
} Node;

class Deque {
private:
    Node* middle;
    Node* head;
    Node* tail;
    int cnt = 0;
    int size;
public:
    Deque(int n) : size(n),middle(new Node()), head(nullptr), tail(nullptr) {}
    void push_back(int data);
    void push_front(int data);
    void pop_back();
    void pop_front();
    char back(); // 修改返回类型为 char
    char front(); // 修改返回类型为 char
    void Print_dq();
};

void Deque::push_back(int data) {
    Node* newNode = new Node;
    newNode->data = static_cast<char>(data); // 强制转换为 char 类型
    newNode->next = nullptr;

    if (head == nullptr) {
        head = newNode;
        tail = newNode;
        middle->next = head;
        head->prev = middle;
    } else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
    cnt++;
}

void Deque::push_front(int data) {
    Node* newNode = new Node;
    newNode->data = static_cast<char>(data); // 强制转换为 char 类型
    newNode->prev = nullptr;

    if (head == nullptr) {
        head = newNode;
        tail = newNode;
        middle->prev = head;
        head->next = middle;
    } else {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }
    cnt++;
}

void Deque::pop_back() {
    if (head == nullptr)
        return;

    Node* temp = tail;
    if (head == tail) {
        head = nullptr;
        tail = nullptr;
        middle->next = nullptr;
    } else {
        tail = tail->prev;
        tail->next = nullptr;
    }
    cnt--;
    delete temp;
}

void Deque::pop_front() {
    if (head == nullptr)
        return;

    Node* temp = head;
    if (head == tail) {
        head = nullptr;
        tail = nullptr;
        middle->prev = nullptr;
    } else {
        head = head->next;
        head->prev = nullptr;
    }
    cnt--;
    delete temp;
}

char Deque::back() {
    if (tail == nullptr)
        return 0;

    return tail->data;
}

char Deque::front() {
    if (head == nullptr)
        return 0;

    return head->data;
}

void Deque::Print_dq() {
    int printCount = std::min(size, cnt); 
    while (printCount > 0) {
        std::cout << back() << ' '; 
        pop_back(); 
        printCount--;
    }
}

int main(){
    int T;
    char data;
    std::cin >> T;
    Deque dq1(T);
    while ((std::cin >> data ) && data != '\n')
    {
        dq1.push_back(data);
    }
    dq1.Print_dq();
    return 0;
}
