#include <stack>
#include <queue>
#include "Node.hpp"

class Tree {

protected:

    unsigned int num_of_nodes;
    
public:
    
    virtual unsigned int get_depth() = 0;
};
