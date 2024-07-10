#include<iostream>
#include<algorithm>
enum Error_code {entry_found,entry_inserted, not_present, overflow, duplicate_error, success };

template<class Entry>
struct Binary_node{
    Entry data;
    Binary_node *left;
    Binary_node *right;

    Binary_node();
    Binary_node(const Entry &x);
};

template <class Entry>
Binary_node<Entry>::Binary_node(){
	left = NULL;
	right = NULL;
}

template <class Entry>
Binary_node<Entry>::Binary_node(const Entry &x){
	data = x;
	left = NULL;
	right = NULL;
}

template <class Entry>
class Binary_search_tree{
    public:
    Binary_search_tree();
    ~Binary_search_tree();
    bool empty() const;
    int size() const;
    int height() const;
    int find_height(const Binary_node<Entry>* sub_root) const;
    Error_code insert(const Entry &new_data);
    Error_code search_insert(Binary_node<Entry> *&sub_root,const Entry &new_data);
    Error_code remove_root(Binary_node<Entry>*&sub_root);
    Error_code search_destroy(Binary_node<Entry>*&sub_root,const Entry &target);
    Error_code remove(const Entry &target);

    Error_code pre_order();
    void pre_order_traverse(Binary_node<Entry> *&sub_root);

    protected:
    Binary_node<Entry> *root;
    int count;
};

template<class Entry>
int Binary_search_tree<Entry>::height() const{
    return find_height(root);
}

template<class Entry>
int Binary_search_tree<Entry>::find_height(const Binary_node<Entry>* sub_root) const{
    if(sub_root == nullptr) return -1; // 基本情况：空树的高度为 -1
    return std::max(find_height(sub_root->left), find_height(sub_root->right)) + 1;
}

template<class Entry>
Binary_search_tree<Entry>::~Binary_search_tree(){
    while(root != nullptr){
        remove_root(root);
    }
}

template<class Entry>
Binary_search_tree<Entry>::Binary_search_tree(){
    root = nullptr;
    count = 0;
}

template<class Entry>
bool Binary_search_tree<Entry>::empty()const{
    if(count == 0) return true;
    return false;
}

template<class Entry>
int Binary_search_tree<Entry>::size()const{
    return count;
}

template<class Entry>
Error_code Binary_search_tree<Entry>
::insert(const Entry &new_data){
    Error_code result = search_insert(root,new_data);
    if(result == success) count++;
    return result;
}

template<class Entry>
Error_code Binary_search_tree<Entry>::
search_insert(Binary_node<Entry> *&sub_root,const Entry &new_data){
    if(sub_root == nullptr){
        sub_root = new Binary_node<Entry>(new_data);
        return success;
    }else if(new_data < sub_root->data)
        return search_insert(sub_root->left,new_data);
    else if(new_data > sub_root->data)
        return search_insert(sub_root->right,new_data); 
    else return duplicate_error;    
}

template<class Entry>   
Error_code Binary_search_tree<Entry>::  
remove(const Entry &target){
    Error_code result = search_destroy(root,target);
    if(result == success) count--;  
    return result;
}

template<class Entry>
Error_code Binary_search_tree<Entry>::
search_destroy(Binary_node<Entry>*&sub_root,const Entry &target){
    if(sub_root == nullptr || sub_root->data == target)
        return remove_root(sub_root);
    else if(target < sub_root->data)
        return search_destroy(sub_root->left,target);
    else if(target > sub_root->data)
        return search_destroy(sub_root->right,target);
    
    return not_present; // Add this line to return a value if none of the conditions are met
}

template<class Entry>
Error_code Binary_search_tree<Entry>::
remove_root(Binary_node<Entry> *&sub_root){
    if(sub_root == nullptr) return not_present;
    Binary_node<Entry> *to_delete = sub_root;
    if(sub_root->right == nullptr) sub_root = sub_root->left;
    else if(sub_root->left == nullptr) sub_root = sub_root->right;
    else{
        to_delete = sub_root->left;
        Binary_node<Entry> *parent = sub_root;
        while(to_delete->right != nullptr){
            parent = to_delete;
            to_delete = to_delete->right;
        }
        sub_root->data = to_delete->data;
        if(parent == sub_root) sub_root->left = to_delete->left;
        else parent->right = to_delete->left;
    }
    delete to_delete;
    return success;
}

template<class Entry>
Error_code Binary_search_tree<Entry>::pre_order(){
    if(root == nullptr) return not_present;
    pre_order_traverse(root);
    return success;
}

template<class Entry>
void Binary_search_tree<Entry>::pre_order_traverse(Binary_node<Entry> *&sub_root){
    if(sub_root != nullptr){
        std::cout << sub_root->data << ' ';
        pre_order_traverse(sub_root->left);
        pre_order_traverse(sub_root->right);
    }
}

