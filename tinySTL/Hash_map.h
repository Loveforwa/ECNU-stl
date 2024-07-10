#include <iostream>
#include "Key.h"
#include "Record.h"
using namespace std;
enum Error_code { not_present, overflow, duplicate_error, success };
const int Hash_size = 1999;
int hash_size;

class Hash_table
{
public:
    void clear();
    Error_code insert(const Record& new_entry);
    Error_code retrieve(const Key& target, Record& found)const;
    Error_code remove(const Key& target, Record& found);
private:
    Record table[Hash_size];
};

int Hash(const Record& new_entry)
{
    return new_entry.the_key() % hash_size;
}

int Hash(const Key& new_entry)
{
    return new_entry.the_key() % hash_size;
}

void Hash_table::clear()
{
    for (int i = 0; i < hash_size; i++) {
        Record tmp;
        table[i] = tmp;
    }
}

Error_code Hash_table::insert(const Record& new_entry)
{
    Error_code result = success;
    int probe_count,//探测次数
        increment,//增量
        probe;//现在的位置码
    probe = Hash(new_entry);
    probe_count = 0;
    increment = 1;
    while (table[probe] != 0
        && table[probe] != -1 
        && table[probe] != new_entry
        && probe_count < (hash_size + 1) / 2) { 
        probe_count++;
        probe = (probe + increment) % hash_size;//平方探测
        increment += 2;
    }
    if (table[probe] == 0) table[probe] = new_entry;
    else if (table[probe] == -1) table[probe] = new_entry;
    else if (table[probe] == new_entry) return duplicate_error;
    else result = overflow;
    return result;
}

Error_code Hash_table::retrieve(const Key& target, Record& found)const
{
    int probe_count, increment, probe;
    probe = Hash(target);
    probe_count = 0;
    increment = 1;
    while (table[probe] != 0 && table[probe].the_key() != target.the_key() && probe_count < (hash_size + 1) / 2) {
        probe_count++;
        cout << probe << ' ';
        probe = (probe + increment) % hash_size;
        increment += 2;
    }
    if (probe_count < (hash_size + 1) / 2) {
        cout << probe << ' ';//找到了之后就出循环了，所以还要输出一遍
    }//这里判断是否出界，没出界就输出
    if (table[probe].the_key() == target.the_key()) {
        found = table[probe];
        return success;
    }
    return not_present;
}

Error_code Hash_table::remove(const Key& target, Record& found)
{
    int probe_count, increment, probe;
    probe = Hash(target);
    probe_count = 0;
    increment = 1;
    while (table[probe] != 0 && table[probe].the_key() != target.the_key() && probe_count < (hash_size + 1) / 2) {
        probe_count++;
        probe = (probe + increment) % hash_size;
        increment += 2;
    }
    if (table[probe].the_key() == target.the_key()) {
        found = table[probe];
        table[probe] == -1;
        return success;
    }
    return not_present;
}
