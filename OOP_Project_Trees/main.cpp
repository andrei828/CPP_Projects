#include "AVL_Tree.hpp"
#include <fstream>

std::istream& operator >> (std::istream& in, AVL_Tree *& tree) {
	int num_of_nodes, data; in >> num_of_nodes;

	if (num_of_nodes > 0) {
		in >> data;
		if (!tree) tree = new AVL_Tree(data);
		
		for (int i = 1; i < num_of_nodes; i++) {
			in >> data; tree->add_node(data);
		}
	}	

	return in;
}

int main() {
	std::ifstream fin("input.txt", std::ifstream::in);
    AVL_Tree * z = NULL;
    
    // reading and printing data
	fin >> z;
    z->display_inorder();
    
    // displaying png
    std::vector<int> print_tree = z->get_level_order_data();
    TreeNode *root = makeTree(print_tree);
	try {
		showTree(root);
		delTree(root);
	} catch (const std::exception& ex) {
		std::cout << ex.what() << std::endl;
	}
}
