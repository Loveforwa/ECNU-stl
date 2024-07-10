#include<iostream>
#include<list>
#include<cstring>
#include <algorithm>
class String{
    public:
    String(){
        entries = new char[1];
        entries[0] = '\0';
        length = 0;
    }
    ~String(){
        delete entries;
    }
    String(const char *copy);
    String(const String &copy);
    String(std::list<char> &copy);
    void operator=(const String &copy);
    const char* c_str() const;
    protected:
    char *entries;
    int length;
};

bool operator == (const String &rst, const String &second);
bool operator > (const String &rst, const String &second);
bool operator < (const String &rst, const String &second);
bool operator >= (const String &rst, const String &second);
bool operator <= (const String &rst, const String &second);
bool operator != (const String &rst, const String &second);

void strcat(String &add_to, const String &add_on){
    const char *c_first = add_on.c_str();
    const char *c_second = add_on.c_str();
    char *copy = new char[strlen(c_first)+strlen(c_second)+1];
    strcpy(copy,c_first);
    std::strcat(copy,c_second);
    add_to = copy;
    delete[] copy;
}
            
void strncpy(String &to,const String &from,int n){
    const char *c_from = from.c_str();
    char *copy = new char[n+1];
    strncpy(copy, c_from, n);
    copy[n] = '\0';
    to = copy;
}




String::String(const char *copy){
    length = strlen(copy);
    entries = new char[length + 1];
    strcpy(entries,copy);
}

String::String(const String &copy){
    this->length = copy.length;
    entries = new char[length + 1];
    memcpy(this->entries,copy.entries,length + 1);
}

String::String(std::list<char> &copy){
    length = copy.size();
    entries = new char[length + 1];
    int i = 0;
    for(char ch : copy){
        entries[i] = ch;
        i++; 
    }
    entries[length] = '\0';
}

void String::operator=(const String &copy){
    if(this == &copy) return;
    delete[] entries;
    this->length = copy.length;
    entries = new char[length + 1];
    memcpy(this->entries, copy.entries, length + 1);
}

const char* String::c_str()const{
    return (const char*)entries;
}

String read_in(std::istream &input) {
    std::list<char> temp;
    char c;
    while ((c = input.peek()) != EOF && c != '\n' && c != ' ') {
        temp.push_back(c);
        input.get(); 
    }
    if (!temp.empty()) {
        return String(temp);
    } else {
        return String();
    }
}

void write(String &s){
    std::cout << s.c_str();
}
