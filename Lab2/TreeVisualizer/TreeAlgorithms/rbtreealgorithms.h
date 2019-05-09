#ifndef RBTREEALGORITHMS_H
#define RBTREEALGORITHMS_H

#include "treealgorithms.h"

class RbTreeAlgorithms:public TreeAlgorithms
{
public:
    RbTreeAlgorithms();
    virtual Tree* Merge(Tree*tree1,Tree*tree2) = 0;
    virtual Tree* Inclusion(Tree*tree1,Tree*tree2) = 0;
    virtual Tree* Intersection(Tree*tree1,Tree*tree2) = 0;
};

#endif // RBTREEALGORITHMS_H
