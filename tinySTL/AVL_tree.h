#include <iostream>
#include <string>

enum Error_code { not_present, overflow, duplicate_error, success };
enum Balance_factor { left_higher, equal_height, right_higher };

using namespace std;

class Record {
public:
    Record() {}
    Record(const string& x) : key(x) {}
    Record(const string& x, const string& y) : key(x), other(y) {}
    string the_key() const { return key; }
    string get_other() const { return other; }

    Record& operator=(const Record& input) {
        key = input.key;
        other = input.other;
        return *this;
    }

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
    
    friend bool operator!=(const Record &x, const Record &y){
        return x.the_key() != y.the_key();
    }

    friend ostream& operator<<(ostream& output, const Record& x) {
        output << x.the_key() << " " << x.get_other();
        return output;
    }

private:
    std::string key;
    std::string other;
};


template <class Record>
struct AVL_node {
    Balance_factor balance;
    Record data;
    AVL_node<Record>* left;
    AVL_node<Record>* right;

    AVL_node(const Record &x);

    void set_balance(Balance_factor b);
    Balance_factor get_balance() const;
};

template <class Record>
AVL_node<Record>::AVL_node(const Record &x) {
    data = x;
    left = nullptr;
    right = nullptr;
    balance = equal_height;
}

template <class Record>
void AVL_node<Record>::set_balance(Balance_factor b) {
    balance = b;
}

template <class Record>
Balance_factor AVL_node<Record>::get_balance() const {
    return balance;
}

template <class Record>
class AVL_tree {
public:
    AVL_tree();
    Error_code insert(const Record &target);
    Error_code remove(Record &old_data);
    Error_code search(Record &target) const;

private:
    Error_code avl_insert(AVL_node<Record>* &sub_root, const Record &target, bool &taller);
    void rotate_left(AVL_node<Record>*& sub_root);
    void rotate_right(AVL_node<Record>*& sub_root);
    void right_balance(AVL_node<Record>*& sub_root);
    void left_balance(AVL_node<Record>*& sub_root);

    Error_code avl_remove(AVL_node<Record>*& sub_root, Record &target, bool &shorter);
    bool right_balance2(AVL_node<Record>*& sub_root);
    bool left_balance2(AVL_node<Record>*& sub_root);

    AVL_node<Record>* root;
};

template <class Record>
AVL_tree<Record>::AVL_tree() {
    root = nullptr;
}

template <class Record>
void AVL_tree<Record>::rotate_left(AVL_node<Record>*& sub_root) {
    if (sub_root == nullptr || sub_root->right == nullptr) return;
    else {
        AVL_node<Record>* right_tree = sub_root->right;
        sub_root->right = right_tree->left;
        right_tree->left = sub_root;
        sub_root = right_tree;
    }
}

template <class Record>
void AVL_tree<Record>::rotate_right(AVL_node<Record>*& sub_root) {
    if (sub_root == nullptr || sub_root->left == nullptr) return;
    else {
        AVL_node<Record>* left_tree = sub_root->left;
        sub_root->left = left_tree->right;
        left_tree->right = sub_root;
        sub_root = left_tree;
    }
}

template <class Record>
void AVL_tree<Record>::right_balance(AVL_node<Record>*& sub_root) {
    AVL_node<Record>* &right_tree = sub_root->right;
    switch (right_tree->get_balance()) {
    case right_higher:
        sub_root->set_balance(equal_height);
        right_tree->set_balance(equal_height);
        rotate_left(sub_root);
        break;
    case equal_height://this situation won't happen
        break;
    case left_higher:
        AVL_node<Record>* sub_tree = right_tree->left;
        switch (sub_tree->get_balance()) {
        case equal_height:
            sub_root->set_balance(equal_height);
            right_tree->set_balance(equal_height);
            break;
        case left_higher:
            sub_root->set_balance(equal_height);
            right_tree->set_balance(right_higher);
            break;
        case right_higher:
            sub_root->set_balance(left_higher);
            right_tree->set_balance(equal_height);
            break;
        }
        sub_tree->set_balance(equal_height);
        rotate_right(right_tree);
        rotate_left(sub_root);
        break;
    }
}

template <class Record>
void AVL_tree<Record>::left_balance(AVL_node<Record>* &sub_root) {
    AVL_node<Record>* &left_tree = sub_root->left;
    switch (left_tree->get_balance()) {
    case left_higher:
        sub_root->set_balance(equal_height);
        left_tree->set_balance(equal_height);
        rotate_right(sub_root);
        break;
    case equal_height:
        break;
    case right_higher:
        AVL_node<Record>* sub_tree = left_tree->right;
        switch (sub_tree->get_balance()) {
        case equal_height:
            sub_root->set_balance(equal_height);
            left_tree->set_balance(equal_height);
            break;
        case right_higher:
            sub_root->set_balance(equal_height);
            left_tree->set_balance(left_higher);
            break;
        case left_higher:
            sub_root->set_balance(right_higher);
            left_tree->set_balance(equal_height);
            break;
        }
        sub_tree->set_balance(equal_height);
        rotate_left(left_tree);
        rotate_right(sub_root);
        break;
    }
}

template <class Record>
Error_code AVL_tree<Record>::avl_insert(AVL_node<Record>*& sub_root, const Record &target, bool &taller) {
    Error_code result = success;
    if (sub_root == nullptr) {
        sub_root = new AVL_node<Record>(target);
        taller = true;
    }
    else if (target == sub_root->data) {
        result = duplicate_error;
        taller = false;
    }
    else if (target < sub_root->data) {
        result = avl_insert(sub_root->left, target, taller);
        if (taller == true) {
            switch (sub_root->get_balance()) {
            case left_higher:
                left_balance(sub_root);
                taller = false;
                break;
            case equal_height:
                sub_root->set_balance(left_higher);
                break;
            case right_higher:
                sub_root->set_balance(equal_height);
                taller = false;
                break;
            }
        }
    }
    else {
        result = avl_insert(sub_root->right, target, taller);
        if (taller == true) {
            switch (sub_root->get_balance()) {
            case left_higher:
                sub_root->set_balance(equal_height);
                taller = false;
                break;  // Missing break added here
            case equal_height:
                sub_root->set_balance(right_higher);
                break;
            case right_higher:
                right_balance(sub_root);
                taller = false;
                break;
            }
        }
    }
    return result;
}


template <class Record>
Error_code AVL_tree<Record>::insert(const Record &target) {
    bool taller;
    return avl_insert(root, target, taller);
}

template <class Record>
bool AVL_tree<Record>::right_balance2(AVL_node<Record>* &sub_root){
    bool shorter;
    AVL_node<Record>* &right_tree = sub_root->right;
    switch (right_tree->get_balance()){
    case right_higher:
        sub_root->set_balance(equal_height);
        right_tree->set_balance(equal_height);
        rotate_left(sub_root);
        shorter = true;
        break;
    case equal_height:
        right_tree->set_balance(left_higher);
        rotate_left(sub_root);
        shorter = false;
        break;
    case left_higher:
        AVL_node<Record> *sub_tree = right_tree->left;
		switch (sub_tree->get_balance()) {
		case equal_height:
			sub_root->set_balance(equal_height);
			right_tree->set_balance(equal_height); 
			break;
		case left_higher:
			sub_root->set_balance(equal_height);
			right_tree->set_balance(right_higher); 
			break;
        case right_higher:
			sub_root->set_balance(left_higher);
			right_tree->set_balance(equal_height); 
			break;
		} 
		sub_tree->set_balance(equal_height);
		rotate_right(right_tree);
		rotate_left(sub_root); 
		shorter = true;
		break;
    }
    return shorter;
}

template<class Record>
bool AVL_tree<Record>::left_balance2(AVL_node<Record>* &sub_root){
    bool shorter;
    AVL_node<Record>* &left_tree = sub_root->left;
    switch (left_tree->get_balance())
    {
    case left_higher:
        sub_root->set_balance(equal_height);
        left_tree->set_balance(equal_height);
        rotate_right(sub_root);
        shorter = true;
        break;
    case equal_height:
        left_tree->set_balance(right_higher);
        rotate_right(sub_root);
        shorter = false;
        break;
    case right_higher:
        AVL_node<Record>* sub_tree = left_tree->right;
        switch (sub_tree->get_balance())
        {
        case equal_height:
            sub_root->set_balance(equal_height);
            left_tree->set_balance(equal_height);
            break;
        case right_higher:
            sub_root->set_balance(equal_height);
            left_tree->set_balance(left_higher);
            break;
        case left_higher:
            sub_root->set_balance(right_higher);
            left_tree->set_balance(equal_height);
            break;
        }
        sub_tree->set_balance(equal_height);
        rotate_left(left_tree);
        rotate_right(sub_root);
        shorter = true;
        break;
    }
    return shorter;
}

template <class Record>
Error_code AVL_tree<Record>::avl_remove(AVL_node<Record>* &sub_root,
Record &target,bool &shorter){
    Error_code result = success;
    Record sub_record = Record("");
    if(sub_root == nullptr){
        shorter = false;
        return not_present;
    }else if(target == sub_root->data){
        AVL_node<Record>* to_delete = sub_root;
        if(sub_root->right == nullptr){
            sub_root = sub_root->left;
            shorter = true;
            delete to_delete;
            return success;
        }else if(sub_root->left == nullptr){
            sub_root = sub_root->right;
            shorter = true;
            delete to_delete;
            return success;
        }else{
            to_delete = sub_root->left;
            AVL_node<Record>* parent = sub_root;
            while(to_delete->right != nullptr){
                parent = to_delete;
                to_delete = to_delete->right;
            }
            target = to_delete->data;
            sub_record = target;
        }
    }

    if(target < sub_root->data){
        result = avl_remove(sub_root->left, target, shorter);
        if(sub_record != Record("")) sub_root->data = sub_record;
        if(shorter == true){
            switch(sub_root->get_balance()){
            case left_higher:
                sub_root->set_balance(equal_height);
                break;
            case equal_height:
                sub_root->set_balance(right_higher);
                shorter = false;
                break;
            case right_higher:
                shorter = right_balance2(sub_root);
                break;
            }
        }
    }

    if (target > sub_root->data) { 
		result = avl_remove(sub_root->right, target, shorter);
		if(sub_record != Record("")) sub_root->data = sub_record; 
		if (shorter == true){
            switch (sub_root->get_balance()) { 
            case left_higher:
                shorter = left_balance2(sub_root);
                break;
            case equal_height:
                sub_root->set_balance(left_higher);
                shorter = false;
                break;
            case right_higher:
                sub_root->set_balance(equal_height);
                break;
            }  
        }
	} 
	return result;
}

template <class Record>
Error_code AVL_tree<Record>::remove(Record &target){
    bool shorter = true;
    return avl_remove(root, target, shorter);
}

template<class Record>
Error_code AVL_tree<Record>::search(Record &target) const {
    AVL_node<Record> *current = root;
    while(current != nullptr && current->data != target){
        cout << current->data.the_key() << " ";
        if(target < current->data){
            current = current->left;
        }else if(target > current->data){
            current = current->right;
        }
    }
    if(current == nullptr){
        cout << "NULL" << endl;
        return not_present;
    }else{
        cout << current->data << endl;
        target = current->data;
        return success;
    }
}


int main() {
    AVL_tree<Record> MyTree;
    int t;
    cin >> t;
    string key, other;
    for (int i = 0; i < t; i++)
    {
        cin >> key >> other;
        Record temp(key, other);
        MyTree.insert(temp);
    }

    cin >> t;
    for (int i = 0; i < t; i++)
    {
        cin >> key;
        Record temp(key);
        MyTree.remove(temp);
    }

    string key1, key2;
    cin >> key1;
    Record temp1(key1);
    MyTree.search(temp1);

    cin >> key2;
    Record temp2(key2);
    MyTree.search(temp2);

    return 0;
}
