#include <iostream>
#include "binary_search_tree.cpp"

int main(){
	binary_search_tree<int> BST;
	bool Flag = true;
	int Node;

	while(Flag){
		std::cout << "\nChoose menu\n1 : search\n2 : insert\n3 : remove\n4 : size\n" << std::endl;
		int Command; std::cin >> Command;
		switch(Command){
			case 1:
				std::cout << "Input Node to Search\n" << std::endl;
				std::cin >> Node;
				if(BST.search(Node) != nullptr){
					std::cout << "There is node\n" << std::endl;
				} else{
					std::cout << "Node doesn't exist\n" << std::endl;
				}
				break;
			case 2:
				std::cout << "Input Node to insert\n" << std::endl;
				std::cin >> Node;
				BST.insert(Node);
				break;
			case 3:
				std::cout << "Input node to remove\n" << std::endl;
				std::cin >> Node;
				if(BST.remove(Node)){
					std::cout << "Node removed\n" << std::endl;
				} else{
					std::cout << "Node doesn't exist\n" << std::endl;
				}
				break;
			case 4:
				std::cout << "Size of tree : " << BST.size() << std::endl << std::endl;
				break;
			default:
				Flag = false;
				std::cout << std::endl << std::endl;
				break;
		}
	}
	return 0;
}
