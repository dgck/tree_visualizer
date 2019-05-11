#ifndef SIMPLETREEALGORITHMS_H
#define SIMPLETREEALGORITHMS_H

#include "treealgorithms.h"

class SimpleTreeAlgorithms:public TreeAlgorithms
{
public:
    SimpleTreeAlgorithms();
    Tree* Merge(Tree*tree1,Tree*tree2);
    Tree* Inclusion(Tree*tree1,Tree*tree2);
    Tree* Intersection(Tree*tree1,Tree*tree2);
};

#endif // SIMPLETREEALGORITHMS_H
