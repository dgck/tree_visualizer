#ifndef SIMPLETREEALGORITHMS_H
#define SIMPLETREEALGORITHMS_H

#include "treealgorithms.h"

class SimpleTreeAlgorithms:public TreeAlgorithms
{
public:
    SimpleTreeAlgorithms();
    virtual Tree* Merge(Tree*tree1,Tree*tree2) = 0;
    virtual Tree* Inclusion(Tree*tree1,Tree*tree2) = 0;
    virtual Tree* Intersection(Tree*tree1,Tree*tree2) = 0;
};

#endif // SIMPLETREEALGORITHMS_H
