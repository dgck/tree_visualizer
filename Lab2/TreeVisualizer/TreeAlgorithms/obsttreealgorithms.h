#ifndef OBSTTREEALGORITHMS_H
#define OBSTTREEALGORITHMS_H

#include "treealgorithms.h"

class ObstTreeAlgorithms:public TreeAlgorithms
{
public:
    ObstTreeAlgorithms();
    virtual Tree* Merge(Tree*tree1,Tree*tree2) = 0;
    virtual Tree* Inclusion(Tree*tree1,Tree*tree2) = 0;
    virtual Tree* Intersection(Tree*tree1,Tree*tree2) = 0;
};

#endif // OBSTTREEALGORITHMS_H
