#include <iostream>
#include <string>
using namespace std;

enum Error_code { success, not_present, overflow, duplicate_error };

template<class Record, int order>
struct B_node {
    int count;
    Record data[order - 1];
    B_node<Record, order> *branch[order];
    B_node() : count(0) {
        for (int i = 0; i < order; i++) {
            branch[i] = nullptr;
        }
    }
};

template <class Record, int order>
class B_tree {
public:
    B_tree() : root(nullptr) {}
    Error_code search_tree(Record &target);
    Error_code insert(const Record &new_entry);
private:
    B_node<Record, order> *root; // root pointer 
    Error_code push_down(B_node<Record, order> *current,
        const Record &new_entry, Record &median,
        B_node<Record, order> *&right_branch);

    void push_in(B_node<Record, order> *current, const Record &entry,
        B_node<Record, order> *right_branch, int position);

    void split_node(B_node<Record, order> *current, const Record &extra_entry,
        B_node<Record, order> *extra_branch, int position, B_node<Record, order> *&right_half, Record &median);

    Error_code search_node(B_node<Record, order> *current, const Record &target, int &position);
    Error_code recursive_search_tree(B_node<Record, order> *current, Record &target);
};

template<class Record, int order>
void B_tree<Record, order>::split_node(B_node<Record, order> *current, const Record &extra_entry,
    B_node<Record, order> *extra_branch, int position, B_node<Record, order> *&right_half, Record &median) {
    right_half = new B_node<Record, order>;
    int mid = order / 2;
    if (position <= mid) {
        for (int i = mid; i < order - 1; i++) {
            right_half->data[i - mid] = current->data[i];
            right_half->branch[i + 1 - mid] = current->branch[i + 1];
        }
        current->count = mid;
        right_half->count = order - 1 - mid;
        push_in(current, extra_entry, extra_branch, position);
    }
    else {
        mid++;
        for (int i = mid; i < order - 1; i++) {
            right_half->data[i - mid] = current->data[i];
            right_half->branch[i + 1 - mid] = current->branch[i + 1];
        }
        current->count = mid;
        right_half->count = order - 1 - mid;
        push_in(right_half, extra_entry, extra_branch, position - mid);
    }
    median = current->data[current->count - 1];
    right_half->branch[0] = current->branch[current->count];
    current->count--;
}

template<class Record, int order>
void B_tree<Record, order>::push_in(B_node<Record, order> *current,
    const Record &entry, B_node<Record, order> *right_branch, int position) {
    for (int i = current->count; i > position; i--) {
        current->data[i] = current->data[i - 1];
        current->branch[i + 1] = current->branch[i];
    }
    current->data[position] = entry;
    current->branch[position + 1] = right_branch;
    current->count++;
}

template<class Record, int order>
Error_code B_tree<Record, order>::push_down(B_node<Record, order> *current,
    const Record &new_entry, Record &median, B_node<Record, order> *&right_branch) {
    Error_code result;
    int position;
    if (current == nullptr) {//抵达了叶子节点，准备插入
        median = new_entry;
        right_branch = nullptr;
        result = overflow;
    }
    else {
        if (search_node(current, new_entry, position) == success)
            result = duplicate_error;
        else {
            Record extra_entry;
            B_node<Record, order> *extra_branch;
            result = push_down(current->branch[position], new_entry, extra_entry, extra_branch);
            if (result == overflow) {
                if (current->count < order - 1) {
                    result = success;
                    push_in(current, extra_entry, extra_branch, position);
                }
                else {
                    split_node(current, extra_entry, extra_branch, position, right_branch, median);
                    result = overflow;
                }
            }
        }
    }
    return result;
}

template<class Record, int order>
Error_code B_tree<Record, order>::insert(const Record &new_entry) {
    Record median;
    B_node<Record, order> *right_branch, *new_root;
    Error_code result = push_down(root, new_entry, median, right_branch);
    if (result == overflow) {
        new_root = new B_node<Record, order>;
        //Most Vexing Parse 声明对象而不是函数声明，不加括号
        new_root->count = 1;
        new_root->data[0] = median;
        new_root->branch[0] = root;
        new_root->branch[1] = right_branch;
        root = new_root;
        result = success;
    }
    return result;
}

template<class Record, int order>
Error_code B_tree<Record, order>::search_node(B_node<Record, order> *current, const Record &target, int &position) {
    position = 0;//start from the left
    while (position < current->count && target > current->data[position])
        position++;//search one by one 
    if (position < current->count && target == current->data[position])
        return success;//if find 
    else return not_present;//else return bigger position to find pointer
}

template<class Record, int order>
Error_code B_tree<Record, order>::recursive_search_tree(B_node<Record, order> *current, Record &target) {
    Error_code result = not_present;
    int position;
    if (current != nullptr) {
        result = search_node(current, target, position);
        if (result == not_present)
            result = recursive_search_tree(current->branch[position], target);
        else target = current->data[position];//target是引用
    }
    return result;
}

template<class Record, int order>
Error_code B_tree<Record, order>::search_tree(Record &target) {
    return recursive_search_tree(root, target);
}

int main() {
    B_tree<int, 4> tree;

    // 插入一些数据
    int entries[] = { 10, 20, 5, 6, 12, 30, 7, 17 };
    for (int entry : entries) {
        tree.insert(entry);
    }

    // 搜索数据
    int targets[] = { 6, 15, 17, 10 };
    for (int target : targets) {
        Error_code result = tree.search_tree(target);
        if (result == success) {
            cout << "Found: " << target << endl;
        }
        else {
            cout << "Not Found: " << target << endl;
        }
    }

    return 0;
}
