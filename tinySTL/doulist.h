#include <iostream>
#include <string>
class List {
private:
    struct Node {
        std::string name;
        int data;
        Node* prev = nullptr;
        Node* next = nullptr;
        Node(int n,std::string N):data(n),name(N),prev(nullptr), next(nullptr) {}
    };

    Node* head = nullptr;
    Node* tail = nullptr;
    int count = 0;
    int max = 0;
    Node* get_pos(int pos);

public:
    void insert(int pos, int data,std::string name);
    void print();

    ~List();
};

List::Node* List::get_pos(int pos) {
    if (pos < 0 || pos >= count) {
        return nullptr;
    }

    Node* temp = head;
    for (int i = 0; i < pos; i++) {
        temp = temp->next;
    }

    return temp;
}

void List::insert(int pos, int data,std::string na) {
    if (pos < 0 || pos > count) {
        std::cerr << "Invalid position" << std::endl;
        return;
    }
    Node* newNode = new Node(data,na);
    if (pos == 0) {
        newNode->next = head;
        if(head != nullptr)
            head->prev = newNode;
        head = newNode;
        if (count == 0) {
            tail = newNode;
            max = data;
        }
    } else {
        Node* prevNode = get_pos(pos - 1);
        newNode->next = prevNode->next;
        newNode->prev = prevNode;
        if (prevNode->next != nullptr) {
            prevNode->next->prev = newNode;
        } else {
            tail = newNode;
        }
        prevNode->next = newNode;
    }
    if(data > max) max = data;
    count++;
}

void List::print() {
    if (head == nullptr) {
        return;
    }
    Node* temp = head;
    while (temp != nullptr) {
        if (temp->data == max) {
            std::cout << temp->name << std::endl;
        }
        temp = temp->next;
    }
}


List::~List() {
    Node* current = head;
    while (current != nullptr) {
        Node* nextNode = current->next;
        delete current;
        current = nextNode;
    }
}

int main() {
    List test;
    std::string Name;
    int t,index;
    std::cin >> t;
    for (int i = 0; i < t; i++)
    {
        std::cin >> Name >> index;
        test.insert(i,index,Name);
    }
    test.print();
}
