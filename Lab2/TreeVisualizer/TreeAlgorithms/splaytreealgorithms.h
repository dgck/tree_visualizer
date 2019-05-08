#ifndef SPLAYTREEALGORITHMS_H
#define SPLAYTREEALGORITHMS_H

#include "treealgorithms.h"

class SplayTreeAlgorithms:public TreeAlgorithms
{
public:
    SplayTreeAlgorithms();
    void WriteToGV(Tree*tree)override;
    void CreateImageFromGV(Tree*tree)override;
    Tree* Merge(Tree*tree1,Tree*tree2)override;
};

#endif // SPLAYTREEALGORITHMS_H
