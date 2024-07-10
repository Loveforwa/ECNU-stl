#include <iostream>
using namespace std;

enum Error_code { underflow, overflow, success };

template<class Record>
class Node
{
public:
    Record data;
    Node* next;
    Node();
    Node(Record item, Node* add_on = NULL);
};

template<class Record>
class MyLinkedStack
{
public:
    MyLinkedStack();
    MyLinkedStack(const MyLinkedStack& original);// 拷贝构造函数
    bool empty() const;
    Error_code push(const Record item);
    Error_code pop();
    Error_code top(Record& item) const;
    void operator=(const MyLinkedStack& original);// 等号重载
    ~MyLinkedStack();// 析构函数
protected:
    Node<Record>* top_node;
};

// Node 类成员函数的定义
template<class Record>
Node<Record>::Node() {
    next = NULL;
}

template<class Record>
Node<Record>::Node(Record item, Node* add_on) {
    data = item;
    next = add_on;
}


template<class Record>
MyLinkedStack<Record>::MyLinkedStack() {
    top_node = NULL;
}

template<class Record>
MyLinkedStack<Record>::MyLinkedStack(const MyLinkedStack& original) {
    Node<Record>* new_copy, * original_node = original.top_node;
    if (original_node == NULL)
        top_node = NULL;
    else {
        new_copy = new Node<Record>(original_node->data);
        top_node = new_copy;
        while (original_node->next != NULL) {
            original_node = original_node->next;
            new_copy->next = new Node<Record>(original_node->data);
            new_copy = new_copy->next;
        }
    }
}

template<class Record>
bool MyLinkedStack<Record>::empty() const {
    return top_node == NULL;
}

template<class Record>
Error_code MyLinkedStack<Record>::push(const Record item) {
    Node<Record>* new_ptr = new Node<Record>(item, top_node);
    if (new_ptr == NULL) return overflow;
    top_node = new_ptr;
    return success;
}

template<class Record>
Error_code MyLinkedStack<Record>::pop() {
    if (top_node == NULL) return underflow;
    Node<Record>* old_ptr = top_node;
    top_node = top_node->next;
    delete old_ptr;
    return success;
}

template<class Record>
Error_code MyLinkedStack<Record>::top(Record& item) const {
    if (empty()) {
        return underflow;
    }
    item = top_node->data;
    return success;
}

template<class Record>
void MyLinkedStack<Record>::operator=(const MyLinkedStack& original) {
    if (this == &original) return;// 如果两个相等，什么都不做
    while (!empty())
        pop();// 删除原来的 stack
    Node<Record>* new_top, * new_copy, * original_node = original.top_node;
    if (original_node == NULL) new_top = NULL;
    else {
        new_copy = new_top = new Node<Record>(original_node->data);
        while (original_node->next != NULL) {
            original_node = original_node->next;
            new_copy->next = new Node<Record>(original_node->data);
            new_copy = new_copy->next;
        }
    }
    top_node = new_top;
}

template<class Record>
MyLinkedStack<Record>::~MyLinkedStack() {
    while (!empty())
        pop();
}
