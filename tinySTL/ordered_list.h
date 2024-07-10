#include "standard_list.h"
struct node{
    int data;
    node *next = nullptr;
    node(int n):data(n){}
};
//enum Error_code {overflow,underflow,error};

class Ordered_list:public list{
    public:
    void insert(int data);
    void insert(int pos,int data);
    void replace(int pos,int data);
    //forgetful version
    bool recursive_binary_1(Ordered_list &list,int target,int bottom,int top,int &pos);
    bool binary_search_1(Ordered_list &list,int target,int &pos);
    //regular version
    bool recursive_binary_2(Ordered_list &list,int target,int bottom,int top,int &pos);
    bool binary_search_2(Ordered_list &list,int target,int &pos);
};

void Ordered_list::insert(int data){
    int s = size();
    int pos = 0;
    for (; pos < s; pos++){
        int temp_data = retrieve(pos);
        if(data < temp_data) break;
    }
    return list::insert(pos,data);
}

void Ordered_list::insert(int pos,int data){
    int temp_data;
    if(pos > 0){
        temp_data = retrieve(pos-1);
        if(data < temp_data) return;
    }
    if(pos < size()){
        temp_data = retrieve(pos);
        if(data > temp_data) return;
    }
    return list::insert(pos,data);
}

void Ordered_list::replace(int pos,int data){
    if(pos < 0 || pos > size() - 1) return;
    int temp_data;
    if(pos > 0){
        temp_data = retrieve(pos - 1);
        if(data < temp_data) return;
    }
    if(pos < size() - 1){
        temp_data = retrieve(pos + 1);
        if(data > temp_data) return;
    }
    list::replace(pos,data);
}

bool Ordered_list::recursive_binary_1(Ordered_list &list,int target,int bottom,int top,int &pos){
    int temp_data;
    if(bottom < top){
        int mid = (bottom + top) / 2;
        temp_data = list.retrieve(mid);
        if(target > temp_data) return recursive_binary_1(list,target,mid+1,bottom,pos);
        else return recursive_binary_1(list,target,bottom,mid,pos);

    }else if(top < bottom) return false;

    else{
        pos = bottom;
        temp_data = list.retrieve(bottom);
        if(temp_data == target) return true;
        else return false;
    }
}

bool Ordered_list::binary_search_1(Ordered_list &list,int target,int &pos){
    int temp_data;
    int bottom = 0,top = size() - 1;

    while(bottom < top){
        int mid = (bottom + top)/2;
        temp_data = list.retrieve(pos);
        if(temp_data < target) bottom = mid + 1;
        else top = mid;
    }

    if(top < bottom) return false;

    else{
        pos = bottom;
        temp_data = list.retrieve(pos);
        if(temp_data == target) return true;
        else return false;
    }
}

bool Ordered_list::recursive_binary_2(Ordered_list &list,int target,int bottom,int top,int &pos){
    int temp_data;
    if(bottom < top){
        int mid = (bottom + top)/2;
        temp_data = list.retrieve(mid);
        if(temp_data == target) {
            pos = mid;
            return true;
        }
        if(target > temp_data) return recursive_binary_2(list,target,mid + 1, top, pos);
        else return recursive_binary_2(list,target,bottom,mid, pos);
    }else return false;
}

bool Ordered_list::binary_search_2(Ordered_list &list,int target,int &pos){
    int temp_data;
    int bottom = 0, top = size() - 1;
    while(bottom <= top){
        pos = (bottom + top) / 2;
        temp_data = list.retrieve(pos);
        if(temp_data == target) return true;
        if(temp_data < target) bottom = pos + 1;
        else top = pos - 1;
    }
    return false;
}