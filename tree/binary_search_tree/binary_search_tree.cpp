//Implementation of binary search tree
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
