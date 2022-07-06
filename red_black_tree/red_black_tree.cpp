/*
* Implementation of red_black_tree
*
*
* red_black_tree implementation by double linked list
* generic programming by template
*
*
***************************************************************************************************
*       class red_black_tree_node
*
*               variables:
*                           value => value of the node
*                           color => color of node by enum : red or black
*                           parent => parent node pointer
*                           left_child => left child node pointer
*                           right_child => right child node pointer
*
*
***************************************************************************************************
*       class red_black_tree
*
*               consturctor:
*                           make new node : leaf(=root) -> set parent && children to nullptr
*
*
*               variables:
*
*                   public:
*                           no public variable
*
*                   private:
*                           red_black_tree_node* root => root node
*                           red_black_tree_node* leaf => leaf node : parent==left_child==right_child==nullptr
*                           unsigned long long _size => size of red_black_tree(number of nodes)
*
*
*               functions:
*
*                   public:
*                           search => Return node pointer whose value is _value. If node with _value doesn't exist, return nullptr.
*                           insert => Insert node with _value to RBtree.
*                           remove => Remove node whose value is _value. If successfully removed a node, return true. Otherwise if node with _value doesn't exist, return false.
*                           size => Return _size.
*
*
*
***************************************************************************************************

*
*
*
*
*
*
*/
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
    std::function<bool(const T&, const T&)> _comparison_function;
};

template <class T>
red_black_tree<T>::red_black_tree(){
    leaf = new red_black_tree_node<T>;
    leaf->color = black;
    leaf->parent = nullptr;
    leaf->left_child = nullptr;
    leaf->right_child = nullptr;
    root = leaf;
    _size = 0;
    _comparison_function = _first_less_than_second;
}

template <class T>
red_black_tree<T>::red_black_tree(std::function<bool(const T&, const T&)> cmp){
    leaf = new red_black_tree_node<T>;
    leaf->color = black;
    leaf->parent = nullptr;
    leaf->left_child = nullptr;
    leaf->right_child = nullptr;
    root = leaf;
    _size = 0;
    _comparison_function = cmp;
}

template <class T>
red_black_tree_node<T>* red_black_tree<T>::search(const T& _value){
    red_black_tree_node<T>* _node_to_return = root;

    while(_node_to_return != nullptr && _node_to_return->value != _value){
        if(_comparison_function(_value, _node_to_return->value)){
            _node_to_return = _node_to_return->left_child;
        } else{
            _node_to_return = _node_to_return->right_child;
        }
    }

    return _node_to_return;
}

template <class T>
void red_black_tree<T>::insert(const T& _value){
}

template <class T>
bool red_black_tree<T>::remove(const T& _value){
}

template <class T>
unsigned long long red_black_tree<T>::size(void){
    return _size;
}