#include "BST.hpp"
#define TRUE 1

unsigned int BST::get_depth() {
	std::queue<Node *> TreeQueue;
	Node * iterator = root, * tmp_node;
   	if (!iterator) return 0;

   	TreeQueue.push(iterator);
   	int height = 0;

   	while (TRUE) {
   		int NodesInQueue = TreeQueue.size();
   		if (NodesInQueue == 0) return height;

   		height++;

   		while (NodesInQueue > 0) {
   			tmp_node = TreeQueue.front();
   			TreeQueue.pop();

   			if (tmp_node->left)  TreeQueue.push(tmp_node->left);
   			if (tmp_node->right) TreeQueue.push(tmp_node->right);
   			NodesInQueue--;
   		}
   	}
}




//---------------------------
// 		adding methods
//---------------------------
void BST::add_node(Node * node) {
    	
	Node * iterator = root;

	while ((node->data <= iterator->data && iterator->left) ||
		   (node->data  > iterator->data && iterator->right)) {

		while (node->data <= iterator->data && iterator->left)
			iterator = iterator->left;

		while (node->data  > iterator->data && iterator->right)
			iterator = iterator->right;
	}

	if (node->data <= iterator->data) iterator->left = node;
	else iterator->right = node;
}

void BST::add_node(int data) {
	Node * tmp_node = new Node(data, NULL, NULL);
	add_node(tmp_node);
}




//---------------------------
// 	   removing methods
//---------------------------
void BST::remove_node(int data) { 
	this->root = remove_node_recursively(root, data); 
}

void BST::remove_node(Node * node) { 
	this->remove_node_recursively(root, node); 
}

Node * BST::remove_node_recursively(Node * root, int data) {
	if (root == NULL) return NULL;

	if (data < root->data) 
		root->left = remove_node_recursively(root->left, data);
	else if (data > root->data)
		root->right = remove_node_recursively(root->right, data);
	else {
		
		if (root->left == NULL) {
			Node * tmp_node = root->right;
			delete root;
			return tmp_node;

		} else if (root->right == NULL) {
			Node * tmp_node = root->left;
			delete root;
			return tmp_node;
		}

		Node * tmp_node = min_data_node(root->right);

		root->data = tmp_node->data;

		root->right = remove_node_recursively(root->right, tmp_node->data);
	}
	return root;
}


Node * BST::min_data_node(Node * root) {
	Node * iterator = root;
	
	while (iterator->left) 
		iterator = iterator->left;
	
	return iterator;
}





//---------------------------
// 	   displaying methods
//---------------------------
void BST::display_inorder() {
	std::stack<Node *> TreeStack;
	Node * iterator = root;
	std::cout << "Inorder: ";
	while (iterator || !TreeStack.empty()) {

		while (iterator) {
			TreeStack.push(iterator);
			iterator = iterator->left;
		}

		iterator = TreeStack.top();
		TreeStack.pop();

		std::cout << iterator->data << ' ';
		iterator = iterator->right;
	}
	std::cout << std::endl;
}

void BST::display_preorder() {
	std::stack<Node *> TreeStack;
	Node * iterator = root, * tmp_node;
	std::cout << "Preorder: ";
	if (iterator == NULL) return;

	TreeStack.push(iterator);
	
	while (!TreeStack.empty()) {
		tmp_node = TreeStack.top();
		TreeStack.pop();

		std::cout << tmp_node->data << ' ';

		if (tmp_node->left)  TreeStack.push(tmp_node->left);
		if (tmp_node->right) TreeStack.push(tmp_node->right);
	}
	std::cout << std::endl;
}

void BST::display_postorder() {
	std::stack<Node *> TreeStack1;
	std::stack<Node *> TreeStack2;
	Node * iterator = root, * tmp_node;
	std::cout << "Postorder: ";
	
	TreeStack1.push(iterator);
	
	while (!TreeStack1.empty()) {
		tmp_node = TreeStack1.top();
		TreeStack1.pop();
		TreeStack2.push(tmp_node);

		if (tmp_node->left)  TreeStack1.push(tmp_node->left);
		if (tmp_node->right) TreeStack1.push(tmp_node->right);
	}

	while (!TreeStack2.empty()) {
		tmp_node = TreeStack2.top();
		TreeStack2.pop();
		std::cout << tmp_node->data << ' ';
	}
	std::cout << std::endl;
}













