#include "AVL_Tree.hpp"

unsigned int AVL_Tree::get_depth() {
	return ceil(log(num_of_nodes));
}

std::vector<int> AVL_Tree::get_level_order_data() {
	std::queue<Node_AVL *> TreeQueue;
	std::vector<int> result;
	TreeQueue.push(root);

	while (!TreeQueue.empty()) {
		Node_AVL * tmp_node = TreeQueue.front();
		
		if (!tmp_node) { 
			result.push_back(null); 
			TreeQueue.pop(); 
		} else {
			result.push_back(tmp_node->data);
			TreeQueue.pop();
			TreeQueue.push(tmp_node->left);	
			TreeQueue.push(tmp_node->right);
		}
	}
	return result;
}


//---------------------------
// 		adding methods
//---------------------------
void AVL_Tree::add_node(int data) {
	root = add_node_recursively(root, data);
}

void AVL_Tree::add_node(Node_AVL * node) {
	root = add_node_recursively(root, node->data);
}

Node_AVL * AVL_Tree::add_node_recursively(Node_AVL * root, int data) {
	
	if (!root) {
		Node_AVL * tmp_node = new Node_AVL(data);
		num_of_nodes++;
		return tmp_node;
	}
	
	if (data < root->data)
		root->left = add_node_recursively(root->left, data);
	else if (data > root->data)
		root->right = add_node_recursively(root->right, data);
	else
		return root;

	root->height = max(get_height(root->left), get_height(root->right)) + 1;

	int node_balance = get_balance(root);

	// left left rotation
	if (node_balance > 1 && data < root->left->data)
		return right_rotate(root);

	// right right rotation
	if (node_balance < -1 && data > root->right->data)
		return left_rotate(root);

	// left right rotation
	if (node_balance > 1 && data > root->left->data) {
		root->left = left_rotate(root->left);
		return right_rotate(root);
	}

	// right left rotation
	if (node_balance < -1 && data < root->right->data) {
		root->right = right_rotate(root->right);
		return left_rotate(root);
	}

	return root;
}




//---------------------------
// 	   removing methods
//---------------------------
void AVL_Tree::remove_node(int data) {
	root = remove_node_recursively(root, data);
}

void AVL_Tree::remove_node(Node_AVL * node) {
	root = remove_node_recursively(root, node->data);
}

Node_AVL * AVL_Tree::remove_node_recursively(Node_AVL * root, int data) {

	if (root == NULL) return root;

	if (data < root->data)
		root->left = remove_node_recursively(root->left, data);
	else if (data > root->data)
		root->right = remove_node_recursively(root->right, data);
	else {
		
		if (!root->left || !root->right) {
			Node_AVL * tmp_node = (root->left)? root->left : root->right;

			if (!tmp_node) {
				tmp_node = root;
				root = NULL;
			} else *root = *tmp_node;

			delete(tmp_node);
			num_of_nodes--;
		} else {
			Node_AVL * tmp_node = min_data_node(root->right);

			root->data = tmp_node->data;

			root->right = remove_node_recursively(root->right, tmp_node->data);
		}
	}

	if (root == NULL) return root;

	root->height = max(get_height(root->left), get_height(root->right)) + 1;

	int node_balance = get_balance(root);

	// left left rotation
	if (node_balance > 1 && get_balance(root->left) >= 0)
		return right_rotate(root);

	// right right rotation
	if (node_balance < -1 && get_balance(root->right) <= 0)
		return left_rotate(root);

	// left right rotation
	if (node_balance > 1 && get_balance(root->left) < 0) {
		root->left = left_rotate(root->left);
		return right_rotate(root);
	}

	// right left rotation
	if (node_balance < -1 && get_balance(root->right) > 0) {
		root->right = right_rotate(root->right);
		return left_rotate(root);
	}

	return root;
}

Node_AVL * AVL_Tree::min_data_node(Node_AVL * root) {
	Node_AVL * iterator = root;
	
	while (iterator->left) 
		iterator = iterator->left;
	
	return iterator;
}




//---------------------------
// 	   utility methods
//---------------------------
unsigned int AVL_Tree::get_height(Node_AVL * root) {
	if (!root) return 0;
	return root->height;
}

int AVL_Tree::get_balance(Node_AVL * root) {
	if (!root) return 0;
	return get_height(root->left) - get_height(root->right);
}

Node_AVL * AVL_Tree::left_rotate(Node_AVL * root) {
	Node_AVL * tmp_node = root->right;
	Node_AVL * tmp_left = tmp_node->left;

	tmp_node->left  = root;
	root->right 	= tmp_left;

	root->height 	 = max(get_height(root->left), get_height(root->right)) + 1;
	tmp_node->height = max(get_height(tmp_node->left), get_height(tmp_node->right)) + 1;

	return tmp_node;
}

Node_AVL * AVL_Tree::right_rotate(Node_AVL * root) {
	Node_AVL * tmp_node  = root->left;
	Node_AVL * tmp_right = tmp_node->right;

	tmp_node->right = root;
	root->left = tmp_right;

	root->height = max(get_height(root->left), get_height(root->right)) + 1;
	tmp_node->height = max(get_height(tmp_node->left), get_height(tmp_node->right)) + 1;

	return tmp_node;
}




//---------------------------
// 	   displaying methods
//---------------------------
void AVL_Tree::display_inorder() {
	std::stack<Node_AVL *> TreeStack;
	Node_AVL * iterator = root;
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

void AVL_Tree::display_preorder() {
	std::stack<Node_AVL *> TreeStack;
	Node_AVL * iterator = root, * tmp_node;
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

void AVL_Tree::display_postorder() {
	std::stack<Node_AVL *> TreeStack1;
	std::stack<Node_AVL *> TreeStack2;
	Node_AVL * iterator = root, * tmp_node;
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