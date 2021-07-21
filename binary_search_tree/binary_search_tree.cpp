/*
* Implementation of binary search tree
*
* 
* binary tree implementation by double linked list
* generic programming by template
*
*
*	struct binary_search_tree_node
*
*		variables:	value => value of the node
*					parent => parent node pointer
*					left_child => left child pointer
*					right_child => right child pointer
*
* 
*
*	class binary_search_tree
*
*		generator:	make new node : lear(=root)
*					set parent to nullptr
*					set all children to nullptr
*
*		variables:	binary_search_tree_node* root => root node
*					binary_search_tree_node* leaf => every last node has leaf node
*
*		functions:	insert => Insert value to bst
*					remove => Delete value from bst. Return false if node doesn't exist.
*
*
*
* created by : gangtaeng_parangvo(GTPV)
*/


#pragma once


//TODO : define operator() for comparison


template<class T>
struct binary_search_tree_node{
	T binary_search_tree_node_value;
	binary_search_tree_node* parent = nullptr;
	binary_search_tree_node* left_child = nullptr;
	binary_search_tree_node* right_child = nullptr;
};


typedef binary_search_tree_node* bst_n_ptr;


template<class T>
class binary_search_tree{
public:
	binary_search_tree();
	void insert(const T& value);
	bool remove(const T& value);
private:
	bst_n_ptr root;
	bst_n_ptr leaf;
};


template<class T>
void binary_search_tree<T>::binary_search_tree(){
	leaf = new binary_search_tree_node;
	leaf.parent = nullptr;
	leaf.left_child = nullptr;
	leaf.right_child = nullptr;
	root = leaf;
}
