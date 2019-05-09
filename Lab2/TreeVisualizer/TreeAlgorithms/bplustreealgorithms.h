#ifndef BPLUSTREEALGORITHMS_H
#define BPLUSTREEALGORITHMS_H

#include "treealgorithms.h"

class BPlusTreeAlgorithms:public TreeAlgorithms
{
public:
    BPlusTreeAlgorithms();
    virtual Tree* Merge(Tree*tree1,Tree*tree2) = 0;
    virtual Tree* Inclusion(Tree*tree1,Tree*tree2) = 0;
    virtual Tree* Intersection(Tree*tree1,Tree*tree2) = 0;
};

#endif // BPLUSTREEALGORITHMS_H
