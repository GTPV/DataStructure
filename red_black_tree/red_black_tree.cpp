#pragma once
#include <functional>

enum COLOR = {red, black};

template <class T>
bool _first_less_than_second(const T& _first, const T& _second){
    return _first < _second;
}

template <class T>
class red_black_tree_node{
public:
    T value;
    COLOR color;
    red_black_tree_node* parent = nullptr;
    red_black_tree_node* left_child = nullptr;
    red_black_tree_node* right_child = nullptr;
};

template <class T>
class red_black_tree{
public:
    red_black_tree();
    red_black_tree(std::function<bool(const T&, const T&)> cmp);

    red_black_tree_node<T>* search(const T& _value);
    void insert(const T& _value);
    bool remove(const T& _value);

    unsigned long long size(void);
private:
    red_black_tree_node<T>* root;
    red_black_tree_node<T>* leaf;
    
    unsigned long long _size;
    bool (*comparison_function)(const T&, const T&);
};

template <class T>
red_black_tree<T>::red_black_tree(){
}

template <class T>
red_black_tree<T>::red_black_tree(std::function<bool(const T&, const T&)> cmp){
}

template <class T>
red_black_tree_node<T>* red_black_tree<T>::search(const T& _value){
}

template <class T>
void red_black_tree<T>::insert(const T& _value){
}

template <class T>
bool red_black_tree<T>::remove(const T& _value){
}

template <class T>
unsigned long long red_black_tree<T>::size(void){
}