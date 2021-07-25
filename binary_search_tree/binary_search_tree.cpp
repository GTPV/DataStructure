/*
* Implementation of binary search tree
*
* 
* binary tree implementation by double linked list
* generic programming by template
* TODO tree balancing
*
*
*	struct binary_search_tree_node
*
*		variables:
*				value => value of the node
*				parent => parent node pointer
*				left_child => left child pointer
*				right_child => right child pointer
*
* 
*
*	class binary_search_tree
*
*		generator:
*				make new node : leaf(=root)
*				set parent to nullptr
*				set all children to nullptr
*
*		variables:
*				binary_search_tree_node* root => root node
*				binary_search_tree_node* leaf => leaf node(parent, left_child, right_child : all nullptr)
*				unsigned long long _size => size of bst(number of nodes in bst)
*
*		functions:
*				insert => Insert value to bst
*				remove => Delete value from bst. Return false if node doesn't exist.
*				search => Search value node, return node pointer. Return nullptr if node doesn't exist.
*				size => Return _size
*				_transplant => link before's parent to after. nothing to do with both's children
*				_minimum => return minimum-value-node in (temp_root-root subtree including temp_root)
*				_maximum => return maximum-value-node in (temp_root-root subtree including temp_root)
*				_comparison_function => fuction to compare value
*
*
*
* created by : gangtaeng_parangvo(GTPV)
*/


#pragma once
#define PRINT
#ifdef PRINT
	#include <iostream>
	#include <vector>
	#define PASS(x) x
#else
	#define PASS(x)
#endif




template <class T>
struct binary_search_tree_node{
	T value;
	binary_search_tree_node* parent = nullptr;
	binary_search_tree_node* left_child = nullptr;
	binary_search_tree_node* right_child = nullptr;
};


template<class T>
bool _first_less_than_second(const T& _first, const T& _second){
	return _first < _second;
}


template <class T>
class binary_search_tree{
public:
	binary_search_tree();
	binary_search_tree(bool (*cmp)(T&, T&));
	binary_search_tree_node<T>* search(const T& _value);
	void insert(const T& _value);
	bool remove(const T& _value);
	unsigned long long size(void);
	PASS(void print(void);)
	PASS(void preorder(binary_search_tree_node<T>* _temp_root, std::vector<std::vector<binary_search_tree_node<T>*>>& _array, int _temp_root_index);)
private:
	binary_search_tree_node<T>* root;
	binary_search_tree_node<T>* leaf;
	unsigned long long _size;
	void _transplant(binary_search_tree_node<T>* _before, binary_search_tree_node<T>* _after);
	bool (*_comparison_function)(const T&, const T&);
	binary_search_tree_node<T>* _minimum(binary_search_tree_node<T>* _temp_root);
	binary_search_tree_node<T>* _maximum(binary_search_tree_node<T>* _temp_root);
};


template <class T>
binary_search_tree<T>::binary_search_tree(){
	leaf = new binary_search_tree_node<T>;
	leaf->parent = nullptr;
	leaf->left_child = nullptr;
	leaf->right_child = nullptr;
	root = leaf;
	_size = 0;
	_comparison_function = _first_less_than_second;
}

template <class T>
binary_search_tree<T>::binary_search_tree(bool (*cmp)(T&, T&)){
	leaf = new binary_search_tree_node<T>;
	leaf->parent = nullptr;
	leaf->left_child = nullptr;
	leaf->right_child = nullptr;
	root = leaf;
	_size = 0;
	_comparison_function = cmp;
}

template <class T>
binary_search_tree_node<T>* binary_search_tree<T>::search(const T& _value){
	binary_search_tree_node<T>* _node_to_check = root;

	while(_node_to_check != nullptr && _node_to_check->value != _value){
		if(_comparison_function(_value, _node_to_check->value)){
			_node_to_check = _node_to_check->left_child;
		} else{
			_node_to_check = _node_to_check->right_child;
		}
	}

	return _node_to_check;
}

template <class T>
void binary_search_tree<T>::insert(const T& _value){
	binary_search_tree_node<T>* _node_to_insert = new binary_search_tree_node<T>;
	_node_to_insert->value = _value;
	_node_to_insert->parent = nullptr;
	_node_to_insert->left_child = leaf;
	_node_to_insert->right_child = leaf;

	if(search(_value) != nullptr) return;

	binary_search_tree_node<T>* _where_to_insert = this->root, *_where_to_insert_parent = nullptr;

	while(_where_to_insert != leaf){
		_where_to_insert_parent = _where_to_insert;
		if(_comparison_function(_value, _where_to_insert->value)){
			_where_to_insert = _where_to_insert->left_child;
		} else{
			_where_to_insert = _where_to_insert->right_child;
		}
	}

	_node_to_insert->parent = _where_to_insert_parent;

	if(_node_to_insert->parent == nullptr){
		root = _node_to_insert;
	} else if(_comparison_function(_node_to_insert->parent->value, _node_to_insert->value)){
		_node_to_insert->parent->right_child = _node_to_insert;
	} else{
		_node_to_insert->parent->left_child = _node_to_insert;
	}

	_size += 1;
}

template <class T>
bool binary_search_tree<T>::remove(const T& _value){
	binary_search_tree_node<T>* _node_to_remove = search(_value);

	if(_node_to_remove == nullptr){
		return false;
	} else{
		binary_search_tree_node<T>* _node_to_replace;

		if(_node_to_remove->left_child == leaf){
			_transplant(_node_to_remove, _node_to_remove->right_child);
		} else if(_node_to_remove->right_child == leaf){
			_transplant(_node_to_remove, _node_to_remove->left_child);
		} else{
			_node_to_replace = _minimum(_node_to_remove->right_child);
			if(_node_to_replace->parent != _node_to_remove){
				_transplant(_node_to_replace, _node_to_replace->right_child);
				_node_to_replace->right_child = _node_to_remove->right_child;
				_transplant(_node_to_remove, _node_to_replace);
				_node_to_replace->left_child = _node_to_remove->left_child;
				_node_to_replace->left_child->parent = _node_to_replace;
				_node_to_replace->right_child->parent = _node_to_replace;
			} else{
				_transplant(_node_to_remove, _node_to_replace);
				_node_to_replace->left_child = _node_to_remove->left_child;
				_node_to_remove->left_child->parent = _node_to_replace;
			}
		}
		delete _node_to_remove;
		_size -= 1;
		return true;
	}
}

template <class T>
unsigned long long binary_search_tree<T>::size(void){
	return _size;
}

PASS(template <class T>)
PASS(void binary_search_tree<T>::print(void){
	if(_size == 0){
		return;
	} else{
		std::vector<std::vector<binary_search_tree_node<T>*>> _binary_search_tree_array(_size+1);
		preorder(this->root, _binary_search_tree_array, 0);

		for(int _depth = 0; _depth < _size+1; _depth++){
			for(auto _node_to_print : _binary_search_tree_array[_depth]){
				if(_node_to_print == leaf){
					std::cout << " null ";
				} else if(_node_to_print == root){
					std::cout << " " << _node_to_print->value << " ";
				} else{
					std::cout << " (" << _node_to_print->parent->value << ")" << _node_to_print->value << " ";
				}
			}
			std::cout << std::endl;
		}
	}
})

PASS(template <class T>)
PASS(void binary_search_tree<T>::preorder(binary_search_tree_node<T>* _temp_root, std::vector<std::vector<binary_search_tree_node<T>*>>& _array, int _temp_root_depth){
	_array[_temp_root_depth].push_back(_temp_root);
	if(_temp_root == leaf){
		return;
	} else{
		preorder(_temp_root->left_child, _array, _temp_root_depth+1);
		preorder(_temp_root->right_child, _array, _temp_root_depth+ 1);
	}
})

template <class T>
void binary_search_tree<T>::_transplant(binary_search_tree_node<T>* _before, binary_search_tree_node<T>* _after){
	if(_before->parent == nullptr){
		root = _after;
	} else if(_before == _before->parent->left_child){
		_before->parent->left_child = _after;
	} else{
		_before->parent->right_child = _after;
	}

	_after->parent = _before->parent;
}

template <class T>
binary_search_tree_node<T>* binary_search_tree<T>::_minimum(binary_search_tree_node<T>* _temp_root){
	while(_temp_root->left_child != leaf){
		_temp_root = _temp_root->left_child;
	}
	return _temp_root;
}

template <class T>
binary_search_tree_node<T>* binary_search_tree<T>::_maximum(binary_search_tree_node<T>* _temp_root){
	while(_temp_root->right_child != leaf){
		_temp_root = _temp_root->right_child;
	}
	return _temp_root;
}
