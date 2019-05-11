#ifndef OBSTTREEALGORITHMS_H
#define OBSTTREEALGORITHMS_H

#include "treealgorithms.h"

class ObstTreeAlgorithms:public TreeAlgorithms
{
public:
    ObstTreeAlgorithms();
    Tree* Merge(Tree*tree1,Tree*tree2);
    Tree* Inclusion(Tree*tree1,Tree*tree2);
    Tree* Intersection(Tree*tree1,Tree*tree2);
};

#endif // OBSTTREEALGORITHMS_H
