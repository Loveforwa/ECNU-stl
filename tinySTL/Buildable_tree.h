#include <iostream>
#include <string>
enum Error_code {not_present, overflow, duplicate_error, success, range_Error}; // Add range_Error enum value

using namespace std;

class Record {
public:
    Record(){}
    Record(const std::string& x) : key(x){}
    Record(const std::string& x, const std::string& y) : key(x), other(y) {}
    std::string the_key() const { return key; }
    std::string get_other() const {return other;}
    friend bool operator==(const Record& x, const Record& y) {
        return x.the_key() == y.the_key();
    }

    friend bool operator>(const Record& x, const Record& y) {
        return x.the_key() > y.the_key();
    }

    friend bool operator<(const Record& x, const Record& y) {
        return x.the_key() < y.the_key();
    }

    friend bool operator<=(const Record& x, const Record& y) {
        return x.the_key() <= y.the_key();
    }

    friend ostream& operator<<(ostream& output, const Record& x) {
        output << x.the_key() << " ";
        return output;
    }

private:
    std::string key;
    std::string other;
};


template <class Record>
class Binary_node {
public:
    Record data;
    Binary_node<Record>* left;
    Binary_node<Record>* right;

    Binary_node(const Record& x) : data(x), left(nullptr), right(nullptr) {}
};

template<class Record>
struct Node {
    Record data;
    Node* next;
    Node();
    Node(Record item, Node* add_on = nullptr);
};

template<class Record>
Node<Record>::Node() {
    next = nullptr;
}

template<class Record>
Node<Record>::Node(Record item, Node* add_on) {
    data = item;
    next = add_on;
}

template<class Record>
class List {
public:
    List();
    ~List();
    List(const List& copy);
    void operator=(const List& copy);
    int size() const;
    bool full() const;
    bool empty() const;
    void clear();
    Error_code insert(int position, const Record& x);
    Error_code remove(int position, Record& x);
    Error_code retrieve(int position, Record& x) const;
    Error_code replace(int position, const Record& x);
    void traverse(void(*visit)(Record& x));

protected:
    int count;
    Node<Record>* head;
    Node<Record>* set_position(int position) const;
};

template<class Record>
Node<Record>* List<Record>::set_position(int position) const {
    Node<Record>* q = head;
    for (int i = 0; i < position; i++) q = q->next;
    return q;
}

template<class Record>
List<Record>::List() {
    count = 0;
    head = nullptr;
}

template<class Record>
List<Record>::~List() {
    Record x;
    while (!empty()) 
        remove(0, x);
}

template<class Record>
List<Record>::List(const List& copy) {
    count = 0;
    head = nullptr;
    Node<Record>* newptr = copy.head;
    while (newptr) {
        insert(size(), newptr->data);
        newptr = newptr->next;
    }
}

template<class Record>
void List<Record>::operator=(const List& copy) {
    Record x;
    if (this == &copy) return;
    while (!empty()) remove(0, x);
    Node<Record>* newptr = copy.head;
    while (newptr) {
        insert(size(), newptr->data);
        newptr = newptr->next;
    }
}

template<class Record>
int List<Record>::size() const {
    return count;
}

template<class Record>
bool List<Record>::full() const {
    Node<Record>* newptr = new Node<Record>();
    if (newptr == nullptr) return true;
    delete newptr;
    return false;
}

template<class Record>
bool List<Record>::empty() const {
    return count == 0;
}

template<class Record>
void List<Record>::clear() {
    Record x;
    remove(0, x);
}

template<class Record>
Error_code List<Record>::insert(int position, const Record& x) {
    if (position < 0 || position > count) return range_Error;
    Node<Record>* newptr, * previous = nullptr, * following;
    if (position > 0) {
        previous = set_position(position - 1);
        following = previous->next;
    }
    else following = head;
    newptr = new Node<Record>(x, following);
    if (newptr == nullptr) return overflow;
    if (position == 0) head = newptr;
    else previous->next = newptr;
    count++;
    return success;
}

template<class Record>
Error_code List<Record>::remove(int position, Record& x) {
    if (position < 0 || position >= count) return range_Error;
    Node<Record>* previous, * following;
    if (position > 0) {
        previous = set_position(position - 1);
        following = previous->next;
        previous->next = following->next;
    }
    else {
        following = head;
        head = head->next;
    }
    x = following->data;
    delete following;
    count--;
    return success;
}

template<class Record>
Error_code List<Record>::retrieve(int position, Record& x) const {
    if (position < 0 || position >= count) return range_Error;
    Node<Record>* newptr = set_position(position);
    x = newptr->data;
    return success;
}

template<class Record>
Error_code List<Record>::replace(int position, const Record& x) {
    if (position < 0 || position >= count) return range_Error;
    Node<Record>* newptr = set_position(position);
    newptr->data = x;
    return success;
}

template<class Record>
void List<Record>::traverse(void(*visit)(Record& x)) {
    Node<Record>* newptr = head;
    while (newptr) {
        (*visit)(newptr->data);
        newptr = newptr->next;
    }
}


template<class Record>
class Buildable_tree{
    public:
    Error_code build_tree(const List<Record> &supply);
    void build_insert(int count,const Record &new_data,List<Binary_node<Record>*> &last_node);
    Binary_node<Record>* find_root(const List<Binary_node<Record>*>&last_node);
    void connect_trees(const List<Binary_node<Record>*>&last_node);
    string search(const string &target);
    private:
    Binary_node<Record>* root = nullptr;
};

template<class Record>
Error_code Buildable_tree<Record>::build_tree(const List<Record> &supply){
    Error_code ordered_data = success;
    int count = 0;
    Record x,last_x;
    List<Binary_node<Record>*> last_node;
    Binary_node<Record> *none = nullptr;
    last_node.insert(0,none);//所有叶子节点的孩子都是空
    while(supply.retrieve(count,x) == success){
        if(count > 0 && x <= last_x){//判断输入是否是排序好的
            ordered_data = not_present;
            break;
        }
        build_insert(++count,x,last_node);
        last_x = x;
    }
    root = find_root(last_node);
    connect_trees(last_node);
    return ordered_data;
}

template<class Record>
void Buildable_tree<Record>
::build_insert(int count,const Record &new_data,List<Binary_node<Record>*> &last_node){
    int level;
    for (level  = 1; count % 2 == 0; level++)
    {
        count /= 2;//计算下一个node的等级
    }
    Binary_node<Record> *next_node = new Binary_node<Record>(new_data),*parent;//创建节点，和父亲节点
    last_node.retrieve(level-1,next_node->left);//完成next_node左边的连接

    if(last_node.size() <= level) last_node.insert(level,next_node);
    //更新链表，因为链表小于等级，说明这是第一次出现的高级别
    else last_node.replace(level,next_node);//否则 在相应位置完成替换，因为前一个节点已经用过了

    if(last_node.retrieve(level+1,parent) == success && parent->right == nullptr)//如果能够拿到上一级
        parent->right = next_node;//而且上一级的右节点为空，进行连接
}

template<class Record>
Binary_node<Record>* Buildable_tree<Record>::find_root(const List<Binary_node<Record>*>&last_node){
    Binary_node<Record> *high_node;
    last_node.retrieve(last_node.size()-1,high_node);//直接找到我们存储链表中的最后一个，就是root
    return high_node;
}

template<class Record> 
void Buildable_tree<Record>::connect_trees(const List<Binary_node<Record>*>&last_node){
    Binary_node<Record> *high_node,*low_node;
    int high_level = last_node.size()-1,low_level;//开始连接
    while (high_level > 2)
    {
        last_node.retrieve(high_level,high_node);//拿到root -->拿到下面一层
        if(high_node->right != nullptr) high_level--;
        else{
            low_level = high_level;//如果右节点是空
            do{
                last_node.retrieve(--low_level,low_node);
            }while(low_node != nullptr && low_node->data < high_node->data);
            high_node->right = low_node;
            high_level = low_level;
        }
    }
}

template<class Record>
string Buildable_tree<Record>::search(const string &target){
    Binary_node<Record>* ptr = root;
    while(ptr != nullptr){
        if(ptr->data.the_key() < target){
            std::cout << ptr->data;
            ptr = ptr->right;
        }else if(ptr->data.the_key() > target){
            std::cout << ptr->data;
            ptr = ptr->left;
        }else if(ptr->data.the_key() == target){
            std::cout << ptr->data;
            return ptr->data.get_other();
        }
    }
    return "NULL";
}


int main(){
    int t;
    std::cin >> t;
    List<Record> supply;
    for (int i = 0; i < t; i++)
    {
        string key, other;
        std::cin >> key >> other;
        Record temp(key,other);
        supply.insert(i,temp);
    }
    Buildable_tree<Record> tree;
    tree.build_tree(supply);

    string t0,result0;

    std::cin >> t0;
    result0 = tree.search(t0);
    if(result0 == "NULL") std::cout << "NULL" << endl;
    else cout << result0 << endl;

    std::cin >> t0;
    result0 = tree.search(t0);
    if(result0 == "NULL") std::cout << "NULL" << endl;
    else cout << result0 << endl;

}


