#include <iostream>

struct Node {
    
    // members
	int data;
    Node * left;
    Node * right;

    // constructor
    Node(int data) : data(data) { left = right = NULL; }
    Node(int data, Node * left, Node * right) : data(data), left(left), right(right) {}
};

struct Node_AVL : public Node {
    
	// members
    int balance;
    Node_AVL * left;
    Node_AVL * right;
    unsigned int height;

    // constructor
    Node_AVL(int data) : Node(data) { balance = 0; height = 1; left = right = NULL; }
    Node_AVL(int data, Node_AVL * left, Node_AVL * right): Node(data), left(left), right(right) {}
};