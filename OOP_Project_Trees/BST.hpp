#include "Tree.hpp"

class BST : public Tree {
    
    Node * root;
    
public:
    
    unsigned int get_depth();
    BST(Node * root) : root(root) {}
    BST(int data) { root = new Node(data); }
    
	//---------------------------
	// 	   displaying methods
	//---------------------------
    void display_inorder();
    void display_preorder();
    void display_postorder();

    //---------------------------
	// 		adding methods
	//---------------------------
    void add_node(int data);
    void add_node(Node * node);

    //---------------------------
	// 	   removing methods
	//---------------------------
    void remove_node(int data);
    void remove_node(Node * node);
    Node * min_data_node(Node * root);
    Node * remove_node_recursively(Node * root, int data);
};







