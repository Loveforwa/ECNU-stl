#include <iostream>

template<typename entry_mode>
class Link_list {
private:
    struct Node{
        entry_mode data;
        Node* next = nullptr;
        Node(entry_mode n) : data(n) {};
    };
    Node* head = nullptr;
public:
    Link_list(){}
    ~Link_list(){clear();}
    Link_list(const Link_list &p){
        clear();
        Node *temp01 = p.head;
        Node *temp02 = head;
        while (temp01 != nullptr){
            Insertat_tail(temp01->data);
            //爽！这样能保证插入顺序和数据在链表中的排列顺序一致
            temp01 = temp01->next;
        }
    }
    Link_list& operator=(const Link_list &p){//返回引用，保证正确复制
        if(this != &p){
            clear();
            Node *temp = p.head;
            while (temp != nullptr)
            {
                Insertat_tail(temp->data);
                temp = temp->next;
            }
            return *this;
        }
        return *this;
    }

    void Insertat_head(entry_mode data);
    void Insertat_tail(entry_mode data);
    void Insert_to_certain(entry_mode data, entry_mode n);
    void Deleteat_node(entry_mode n);
    void Delete_certain_node(entry_mode data);
    entry_mode size();
    void clear();
    void reverse();
    void Print();
};

template<typename entry_mode>
void Link_list<entry_mode>::Insertat_head(entry_mode data) {
    Node* newnode = new Node(data);
    if (head == nullptr)
        head = newnode;
    else {
        newnode->next = head;
        head = newnode;
    }
}

template<typename entry_mode>
void Link_list<entry_mode>::Insertat_tail(entry_mode data) {
    Node* newnode = new Node(data);
    if (head == nullptr)
        head = newnode;
    else {
        Node* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newnode;
    }
}

template<typename entry_mode>
void Link_list<entry_mode>::Insert_to_certain(entry_mode data, entry_mode n) {
    if (n < 0) {
        std::cerr << "Error! n can't be less than 0" << std::endl;
        return;
    }
    Node* newnode = new Node(data);
    if (head == nullptr) {
        if (n == 0) {
            head = newnode;
        }
        else {
            std::cerr << "Error! List is empty" << std::endl;
        }
    }
    else {
        if (n == 0) {
            newnode->next = head;
            head = newnode;
        }
        else {
            Node* temp = head;
            for (entry_mode i = 0; i < n - 1; i++) {
                if (temp->next == nullptr) {
                    std::cerr << "Error! Index out of range" << std::endl;
                    return;
                }
                temp = temp->next;
            }
            newnode->next = temp->next;
            temp->next = newnode;
        }
    }
}

template<typename entry_mode>
void Link_list<entry_mode>::Deleteat_node(entry_mode n){
    if(n < 0){std::cerr << "Error ! n can't lesser than 0" << std::endl;return;}
    Node *temp01 = head;
    Node *temp02 = nullptr;
    if (n == 0){
        head = head->next;
        delete temp01;
    }else{
        for (entry_mode i = 0; i < n; i++)
        {
            temp02 = temp01;
            temp01 = temp01->next;
        }
        temp02->next = temp01->next;
        delete temp01;
    }
}

template<typename entry_mode>
void Link_list<entry_mode>::Delete_certain_node(entry_mode data) {
    if (head == nullptr) {std::cerr << "Error! List is empty" << std::endl;return;}
    bool deleted = false;
    Node* temp = head;
    while (temp != nullptr) {
        if (temp->data == data) {
            Node* toDelete = temp;
            temp = temp->next; 
            if (toDelete == head) {
                head = temp;
            } else {
                Node* prev = head;
                while (prev->next != toDelete) {
                    prev = prev->next;
                }
                prev->next = temp;
            }
            delete toDelete;
            deleted = true; 
        } else {
            temp = temp->next; 
        }
    }

    if (!deleted) { 
        std::cerr << "Error! Data not found" << std::endl;
    }
}


template<typename entry_mode>
entry_mode Link_list<entry_mode>::size() {
    entry_mode count = 0;
    Node* temp = head;
    while (temp != nullptr) {
        count++;
        temp = temp->next;
    }
    return count;
}

template<typename entry_mode>
void Link_list<entry_mode>::clear() {
    Node* temp = head;
    while (temp != nullptr) {
        Node* toDelete = temp;
        temp = temp->next;
        delete toDelete;
    }
    head = nullptr;
}

template<typename entry_mode>
void Link_list<entry_mode>::reverse() {
    if (head == nullptr || head->next == nullptr)
        return;

    Node* prev = nullptr;
    Node* current = head;
    Node* nextNode = nullptr;

    while (current != nullptr) {
        nextNode = current->next;
        current->next = prev;
        prev = current;
        current = nextNode;
    }
    head = prev;
}

template<typename entry_mode>
void Link_list<entry_mode>::Print(){
    if(head == nullptr){std::cout << "Linklist is empty" << std::endl;return;}
    for (Node *temp = head; temp != nullptr;temp = temp->next){
    std::cout << temp->data << ' ' ;
    }
    std::cout << std::endl;
}