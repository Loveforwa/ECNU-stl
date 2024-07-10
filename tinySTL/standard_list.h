#include<iostream>

class list{
    public:
    struct node{
        int data;
        node *next = nullptr;
        node(int n):data(n){}
    };
    node* get_pos(int pos);
    virtual void insert(int pos,int data);
    void remove(int pos);
    int retrieve(int pos);
    virtual void replace(int pos,int data);
    void traverse();
    int size();
    void print();
    private:
    node *head = nullptr;  
    int count = 0;
};

list::node* list::get_pos(int pos) {
    if (pos < 0 || pos > count) {
        return nullptr;
    }
    node* temp = head;
    for (int i = 0; i < pos; i++) {
        temp = temp->next;
    }
    return temp;
}

void list::insert(int pos, int data) {
    if (pos < 0 || pos > count) return;
    node* newNode = new node(data);
    if (pos == 0) {
        newNode->next = head;
        head = newNode;
    } else {
        node* prevNode = get_pos(pos - 1);
        newNode->next = prevNode->next;
        prevNode->next = newNode;
    }
    count++;
}

void list::remove(int pos){
    if(pos < 0 || pos >= count) return;
    if(pos == 0){
        node *temp = head;
        head = head->next;
        delete temp;
    }else{
        node *prevNode = get_pos(pos - 1);
        node *currentNode = get_pos(pos);
        prevNode->next = currentNode->next;
        delete currentNode;
    }
    count--;
}

int list::retrieve(int pos){
    if (pos < 0 || pos > count) return -1;
    node *temp = get_pos(pos);
    int val = temp->data;
    delete temp;
    return val;
}

void list::replace(int pos, int data){
    if (pos < 0 || pos >= count) return;
    node *temp = get_pos(pos);
    temp->data = data;
}

void list::traverse(){
    node *temp = head;
    while(temp != nullptr){
        std::cout << temp->data << ' ';
        temp = temp->next;
    }
}

int list::size(){
    return count;
}

void list::print(){
    traverse();
}

