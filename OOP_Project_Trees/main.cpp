//#include "BST.hpp"
#include "AVL_Tree.hpp"
int main() {
 
   // Node_AVL * a = new Node_AVL(5, NULL, NULL);

	Node_AVL * tmp = new Node_AVL(10);
    AVL_Tree * z = new AVL_Tree(tmp);
    z->add_node(12);
    z->add_node(5);
    z->add_node(7);
    z->display_inorder();
    std::cout << z->get_depth();
}
