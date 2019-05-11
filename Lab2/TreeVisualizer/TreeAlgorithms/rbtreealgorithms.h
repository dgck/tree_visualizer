#ifndef RBTREEALGORITHMS_H
#define RBTREEALGORITHMS_H

#include "treealgorithms.h"

class RbTreeAlgorithms:public TreeAlgorithms
{
public:
    RbTreeAlgorithms();
    Tree* Merge(Tree*tree1,Tree*tree2);
    Tree* Inclusion(Tree*tree1,Tree*tree2);
    Tree* Intersection(Tree*tree1,Tree*tree2);
};

#endif // RBTREEALGORITHMS_H
