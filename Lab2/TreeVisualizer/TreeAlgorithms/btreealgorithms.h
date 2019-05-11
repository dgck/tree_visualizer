#ifndef BTREEALGORITHMS_H
#define BTREEALGORITHMS_H

#include "treealgorithms.h"

class BTreeAlgorithms:public TreeAlgorithms
{
public:
    BTreeAlgorithms();
    Tree* Merge(Tree*tree1,Tree*tree2);
    Tree* Inclusion(Tree*tree1,Tree*tree2);
    Tree* Intersection(Tree*tree1,Tree*tree2);
};

#endif // BTREEALGORITHMS_H
