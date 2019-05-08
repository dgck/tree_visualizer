#ifndef RBTREEALGORITHMS_H
#define RBTREEALGORITHMS_H

#include "treealgorithms.h"

class RbTreeAlgorithms:public TreeAlgorithms
{
public:
    RbTreeAlgorithms();
    void WriteToGV(Tree*tree)override;
    void CreateImageFromGV(Tree*tree)override;
    Tree* Merge(Tree*tree1,Tree*tree2)override;
};

#endif // RBTREEALGORITHMS_H
