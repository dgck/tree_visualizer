#ifndef SIMPLETREEALGORITHMS_H
#define SIMPLETREEALGORITHMS_H

#include "treealgorithms.h"

class SimpleTreeAlgorithms:public TreeAlgorithms
{
public:
    SimpleTreeAlgorithms();
    void WriteToGV(Tree*tree)override;
    void CreateImageFromGV(Tree*tree)override;
    Tree* Merge(Tree*tree1,Tree*tree2)override;
};

#endif // SIMPLETREEALGORITHMS_H
