#ifndef SPLAYTREEALGORITHMS_H
#define SPLAYTREEALGORITHMS_H

#include "treealgorithms.h"

class SplayTreeAlgorithms:public TreeAlgorithms
{
public:
    SplayTreeAlgorithms();
    Tree* Merge(Tree*tree1,Tree*tree2);
    Tree* Inclusion(Tree*tree1,Tree*tree2);
    Tree* Intersection(Tree*tree1,Tree*tree2);
};

#endif // SPLAYTREEALGORITHMS_H
