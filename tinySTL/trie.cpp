#include <iostream>
#include <cstring>
#include <string>

enum Error_code { not_present, overflow, underflow, duplicate_error, success };

using namespace std;

const int num_chars = 28;
string letters;

class Record {
public:
    Record(string s, string con) : str(s), content(con) {}
    string the_con();
    string the_str();
    char str_pos(int position);
private:
    string str;
    string content;
};

char Record::str_pos(int position) {
    return str[position];
}

string Record::the_str() {
    return str;
}

string Record::the_con() {
    return content;
}

int alpha_order(char c) {
    if (c == ' ' || c == '\0') return 0;
    if ('a' <= c && c <= 'z') return c - 'a' + 1;
    if ('A' <= c && c <= 'Z') return c - 'A' + 1;
    return 27;
}

string call_pos(char c) {
    for (int i = 0; i < letters.size(); i++) {
        if (c == letters[i]) {
            return to_string(i) + " "; 
        }
    }
    return "";
}

struct Trie_node {
    Record* data;
    Trie_node* branch[num_chars];

    Trie_node();
};

Trie_node::Trie_node() {
    data = nullptr;
    for (int i = 0; i < num_chars; i++) {
        branch[i] = nullptr;
    }
}

class Trie {
public:
    Error_code insert(Record &new_entry);
    Trie_node* trie_search(string &target, string &path);
    void remove(string &target);
    void traverse();

    Trie() : root(nullptr) {}
    Trie_node* root;
private:
    void traverse_recursive(Trie_node* node);
};

Error_code Trie::insert(Record &new_entry) {
    Error_code result = success;
    if (root == nullptr) root = new Trie_node;
    int position = 0;
    char next_char;
    Trie_node* location = root;
    while (location != nullptr && (next_char = new_entry.str_pos(position)) != '\0') {
        int next_position = alpha_order(next_char) - 1;
        if (location->branch[next_position] == nullptr) {
            location->branch[next_position] = new Trie_node;
        }
        location = location->branch[next_position];
        position++;
    }
    if (location->data != nullptr) result = duplicate_error;
    location->data = new Record(new_entry);
    result = success;
    return result;
}

Trie_node* Trie::trie_search(string &target, string &path) {
    int position = 0;
    char next_char;
    path = "";
    Trie_node *location = root;
    while (location != nullptr && (next_char = target[position]) != '\0') {
        path += call_pos(next_char);
        location = location->branch[alpha_order(next_char) - 1];
        position++;
    }
    if (location != nullptr && location->data != nullptr) {
        path += location->data->the_str() + " " + location->data->the_con() + "\n";
        return location;
    }else {
        path += "NULL\n";
    }
    return nullptr;
}

void Trie::remove(string &target) {
    string path;
    Trie_node* node_to_remove = trie_search(target, path);
    if (node_to_remove != nullptr && node_to_remove->data != nullptr) {
        delete node_to_remove->data; 
        node_to_remove->data = nullptr;
        
    }
}

void Trie::traverse() {
    traverse_recursive(root);
}

void Trie::traverse_recursive(Trie_node* node) {
    if(node->data != nullptr) cout << node->data->the_str() << " ";

    if (node == nullptr) return;

    for (int i = 0; i < num_chars; i++) {
        if (node->branch[i] != nullptr) {
            traverse_recursive(node->branch[i]);
        }
    }
}

int main() {
    int key_size, insert_num, del_num;
    cin >> key_size >> insert_num >> del_num;
    char ch;

    for (int i = 0; i < key_size; i++) {
        cin >> ch;
        letters.push_back(ch);
    }

    Trie my_trie;

    for (int i = 0; i < insert_num; i++) {
        string s1, s2;
        cin >> s1 >> s2;
        Record temp(s1, s2);
        if(my_trie.insert(temp) == success) continue;
    }

    for (int i = 0; i < del_num; i++) {
        string s3;
        cin >> s3;
        my_trie.remove(s3);
    }

    string se1, se2, path;

    cin >> se1 >> se2;

    my_trie.trie_search(se1, path);
    cout << path;

    my_trie.trie_search(se2, path);
    cout << path;

    my_trie.traverse();

    return 0;
}
