#ifndef BTREEALGORITHMS_H
#define BTREEALGORITHMS_H

#include "treealgorithms.h"

class BTreeAlgorithms:public TreeAlgorithms
{
public:
    BTreeAlgorithms();
    virtual Tree* Merge(Tree*tree1,Tree*tree2) = 0;
    virtual Tree* Inclusion(Tree*tree1,Tree*tree2) = 0;
    virtual Tree* Intersection(Tree*tree1,Tree*tree2) = 0;
};

#endif // BTREEALGORITHMS_H
