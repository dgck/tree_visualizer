#ifndef OBSTTREEALGORITHMS_H
#define OBSTTREEALGORITHMS_H

#include "treealgorithms.h"

class ObstTreeAlgorithms:public TreeAlgorithms
{
public:
    ObstTreeAlgorithms();
    void WriteToGV(Tree*tree)override;
    void CreateImageFromGV(Tree*tree)override;
    Tree* Merge(Tree*tree1,Tree*tree2)override;
};

#endif // OBSTTREEALGORITHMS_H
