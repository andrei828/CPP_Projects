#include "Tree.hpp"
#include "cmath"

class AVL_Tree: public Tree {
    
    Node_AVL * root;
    
public:	
    
    unsigned int get_depth();
    AVL_Tree(Node_AVL * root) : root(root) {}
    AVL_Tree(int data) { root = new Node_AVL(data); }

    //---------------------------
	// 	   displaying methods
	//---------------------------
    void display_inorder();
    void display_preorder();
    void display_postorder();

 	//---------------------------
	// 	   utility methods
	//---------------------------
   	int get_balance(Node_AVL * root);
   	Node_AVL * left_rotate(Node_AVL * root);
    Node_AVL * right_rotate(Node_AVL * root);
    unsigned int get_height(Node_AVL * root);
    int max(int a, int b) { return (a > b)? a : b; }

    //---------------------------
	// 		adding methods
	//---------------------------
    void add_node(int data);
    void add_node(Node_AVL * node);
    Node_AVL * add_node_recursively(Node_AVL * root, int data);

    //---------------------------
	// 	   removing methods
	//---------------------------
    void remove_node(int data);
    void remove_node(Node_AVL * node);
    Node_AVL * min_data_node(Node_AVL * root);
    Node_AVL * remove_node_recursively(Node_AVL * root, int data);
   
};








