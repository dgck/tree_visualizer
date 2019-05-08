#ifndef BTREEALGORITHMS_H
#define BTREEALGORITHMS_H

#include "treealgorithms.h"

class BTreeAlgorithms:public TreeAlgorithms
{
public:
    BTreeAlgorithms();
    void WriteToGV(Tree*tree)override;
    void CreateImageFromGV(Tree*tree)override;
    Tree* Merge(Tree*tree1,Tree*tree2)override;
};

#endif // BTREEALGORITHMS_H
