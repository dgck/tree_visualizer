#ifndef SPLAYTREEALGORITHMS_H
#define SPLAYTREEALGORITHMS_H

#include "treealgorithms.h"

class SplayTreeAlgorithms:public TreeAlgorithms
{
public:
    SplayTreeAlgorithms();
    virtual Tree* Merge(Tree*tree1,Tree*tree2) = 0;
    virtual Tree* Inclusion(Tree*tree1,Tree*tree2) = 0;
    virtual Tree* Intersection(Tree*tree1,Tree*tree2) = 0;
};

#endif // SPLAYTREEALGORITHMS_H
