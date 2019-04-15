#include <stack>
#include <queue>
#include <cmath>
#include <vector>
#include "Node.hpp"
#include "binarytree.hpp"

class Tree {

protected:

    unsigned int num_of_nodes;
    
public:
    
    virtual unsigned int get_depth() = 0;
};
