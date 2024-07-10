#include "search_tree.h"

template<class Record>
class Splay_tree:public Binary_search_tree<Record>{
    public:
    Error_code splay(const Record &target);

    private:
    void link_right(Binary_node<Record>* &current,Binary_node<Record>* &first_large);
    void link_left(Binary_node<Record>* &current,Binary_node<Record>* &last_small);
    void rotate_right(Binary_node<Record>* &current);
    void rotate_left(Binary_node<Record>* &current);
};


template<class Record>
void Splay_tree<Record>::link_right(Binary_node<Record>* &current,Binary_node<Record>* &first_large){
    first_large->left = current;
    first_large = current;
    current = current->left;
}

template<class Record>
void Splay_tree<Record>::link_left(Binary_node<Record>* &current,
    Binary_node<Record>* &last_small){
    last_small->right = current;
    last_small = current;
    current = current->right;
}

template<class Record>
void Splay_tree<Record>::rotate_right(Binary_node<Record>* &current){
    Binary_node<Record>* left_tree = current->left;
    current->left = left_tree->right;
    left_tree->right = current;
    current = left_tree;
}

template <class Record>
void Splay_tree<Record> :: rotate_left(Binary_node<Record> * &current){
    Binary_node<Record> *right_tree = current->right;
	current->right = right_tree->left;
	right_tree->left = current;
	current = right_tree;
}

template <class Record>
Error_code Splay_tree<Record>::splay(const Record &target){
    Binary_node<Record>* dummy = new Binary_node<Record>;
    Binary_node<Record>*child,last_small = dummy,first_large = dummy, current = this->root;

    while(current != nullptr && current->data != target){
        if(target < current->data){
            child = current->left;
            if(child == nullptr || target == child->data)
                link_right(current,first_large);
            else if(target < child->data){
                rotate_right(current);
                link_right(current,first_large);
            }else{
                link_right(current,first_large);
                link_left(current,last_small);
            }
        }else {
            child = current->right;
            if(child == nullptr || target == child->data)
                link_left(current,last_small);
            else if(target > child->data){
                rotate_left(current);
                link_left(current,last_small);
            }else{
                link_left(current,last_small);
                link_right(current,first_large);
            }
        }
        Error_code resuError_code result;
        if(current == nullptr){
            current = new Binary_node<Record>(target);
            result = entry_inserted;
            last_small->right = first_large->left = nullptr;
        }else {
            result = entry_found;
            last_small->right = current->left;
            first_large->left = current->right;
        }
        this->root = current;
        this->root->right = dummy->left;
        this->root->left = dummy->right;
        delete dummy;
        return result;Error_code result;
        if(current == nullptr){
            current = new Binary_node<Record>(target);
            result = entry_inserted;
            last_small->right = first_large->left = nullptr;
        }else {
            result = entry_found;
            last_small->right = current->left;
            first_large->left = current->right;
        }
        this->root = current;
        this->root->right = dummy->left;
        this->root->left = dummy->right;
        delete dummy;
        return result;Error_code result;
        if(current == nullptr){
            current = new Binary_node<Record>(target);
            result = entry_inserted;
            last_small->right = first_large->left = nullptr;
        }else {
            result = entry_found;
            last_small->right = current->left;
            first_large->left = current->right;
        }
        this->root = current;
        this->root->right = dummy->left;
        this->root->left = dummy->right;
        delete dummy;
        return result;Error_code result;
        if(current == nullptr){
            current = new Binary_node<Record>(target);
            result = entry_inserted;
            last_small->right = first_large->left = nullptr;
        }else {
            result = entry_found;
            last_small->right = current->left;
            first_large->left = current->right;
        }
        this->root = current;
        this->root->right = dummy->left;
        this->root->left = dummy->right;
        delete dummy;
        return result;
        if(current == nullptr){
            current = new Binary_node<Record>(target);
            result = entry_inserted;
            last_small->right = first_large->left = nullptr;
        }else {
            result = entry_found;
            last_small->right = current->left;
            first_large->left = current->right;
        }
        this->root = current;
        this->root->right = dummy->left;
        this->root->left = dummy->right;
        delete dummy;
        return result;
    }
}