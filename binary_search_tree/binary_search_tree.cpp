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
*				binary_search_tree_node* leaf => every last node has leaf node
*
*		functions:
*				insert => Insert value to bst
*				remove => Delete value from bst. Return false if node doesn't exist.
*				search => Search value node, return node pointer. Return nullptr if node doesn't exist.
*				_transplant => before-root-subtree <<(transplant)<< after-root-subtree
*				_minimum => return minimum-value-node in (temp_root-root subtree including temp_root)
*				_maximum => return maximum-value-node in (temp_root-root subtree including temp_root)
*				_comparison_function => fuction to compare value
*
*
*
* created by : gangtaeng_parangvo(GTPV)
*/


#pragma once




template <class T>
struct binary_search_tree_node{
	T value;
	binary_search_tree_node* parent = nullptr;
	binary_search_tree_node* left_child = nullptr;
	binary_search_tree_node* right_child = nullptr;
};


typedef binary_search_tree_node* bst_n_ptr;

template<class T>
bool _first_less_than_second(const T& _first, const T& _second){
	return _first < _second;
}


template <class T>
class binary_search_tree{
public:
	binary_search_tree();
	bst_n_ptr search(const T& _value);
	void insert(const T& _value);
	bool remove(const T& _value);
private:
	bst_n_ptr root;
	bst_n_ptr leaf;
	void _transplant(bst_n_ptr _before, bst_n_ptr _after);
	bool (*_comparison_function)(const T&, const T&);
	bst_n_ptr _minimum_from_right(bst_n_ptr _temp_root);
	bst_n_ptr _maximum_from_left(bst_n_ptr _temp_root);
};


template <class T>
binary_search_tree<T>::binary_search_tree(){
	leaf = new binary_search_tree_node;
	leaf.parent = nullptr;
	leaf.left_child = nullptr;
	leaf.right_child = nullptr;
	root = leaf;
	_comparison_function = _first_less_than_second;
}

template <class T>
binary_search_tree<T>::binary_search_tree(bool (*cmp)(T&, T&)){
	leaf = new binary_search_tree_node;
	leaf.parent = nullptr;
	leaf.left_child = nullptr;
	leaf.right_child = nullptr;
	root = leaf;
	_comparison_function = cmp;
}

template <class T>
bst_n_ptr binary_search_tree<T>::search(const T& _value){
	bst_n_ptr _node_to_check = root;

	while(_node_to_check != nullptr && _node_to_check->value != _value){
		if(_comparison_function(_value, _node_to_check->value)){
			_node_to_check = _node_to_check->left_child;
		} else{
			_node_to_check = _node_to_check->right_child;
		}
	}

	return node_to_check;
}

template <class T>
void binary_search_tree<T>::insert(const T& _value){
	bst_n_ptr _node_to_insert = new binary_search_tree_node();
	_node_to_insert->value = _value;
	_node_to_insert->parent = nullptr;
	_node_to_insert->left_child = leaf;
	_node_to_insert->right_child = leaf;

	if(search(value) != nullptr) return;

	bst_n_ptr _where_to_insert = this->root;

	while(_where_to_insert != leaf){
		if(_comparison_function(value, _where_to_insert->value)){
			_where_to_insert = _where_to_insert->left_child;
		} else{
			_where_to_insert = _where_to_insert->right_child;
		}
	}

	_node_to_insert->parent = _where_to_insert->parent;

	if(_node_to_insert->parent == nullptr){
		root = _node_to_insert;
	} else if(_comparison_function(_node_to_insert->parent->value, _node_to_insert->value)){
		_node_to_insert->parent->right_child = _node_to_insert;
	} else{
		_node_to_insert->parent->left_child = _node_to_insert;
	}
}

template <class T>
bool binary_search_tree<T>::remove(const T& value){
	bst_n_ptr _node_to_remove = search(value);

	if(_node_to_remove == nullptr){
		return false;
	} else{
		bst_n_ptr _node_to_replace;

		if(_node_to_remove->left_child == leaf){
			transplant(_node_to_remove, _node_to_remove->right_child);
		} else if(_node_to_remove->right_child == leaf){
			transplant(_node_to_remove, _node_to_remove->left_child);
		} else{
			_node_to_replace = _minimum(_node_to_remove->right_child);
			if(_node_to_replace->parent != _node_to_remove){
				transplant(_node_to_replace, _node_to_replace->right_child);
				_node_to_replace->right_child = _node_to_remove->right_child;
				transplant(_node_to_remove, _node_to_replace);
				_node_to_replace->left_child = _node_to_remove->left_child;
				_node_to_replace->left_child->parent = _node_to_replace;
				_node_to_replace->right_child->parent = _node_to_replace;
			} else{
				transplant(_node_to_remove, _node_to_replace);
				_node_to_replace->left_child = _node_to_remove->left_child;
				_node_to_remove->left_child->parent = _node_to_replace;
			}
		}
		delete _node_to_remove;
		return true;
}

template <class T>
void binary_search_tree<T>::_transplant(bst_n_ptr _before, bst_n_ptr _after){
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
bst_n_ptr binary_search_tree<T>::_minimum(bst_n_ptr _temp_root){
	while(_temp_root->left_child != leaf){
		_temp_root = _temp_root->left_child;
	}
	return _temp_root;
}

template <class T>
bst_n_ptr binary_search_tree<T>::_maximum(bst_n_ptr _temp_root){
	while(_temp_root->right_child != leaf){
		_temp_root = _temp_root->right_child;
	}
	return _temp_root;
}