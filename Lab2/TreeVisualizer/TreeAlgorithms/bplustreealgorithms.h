#ifndef BPLUSTREEALGORITHMS_H
#define BPLUSTREEALGORITHMS_H

#include "treealgorithms.h"

class BPlusTreeAlgorithms:public TreeAlgorithms
{
public:
    BPlusTreeAlgorithms();
    void WriteToGV(Tree*tree)override;
    void CreateImageFromGV(Tree*tree)override;
    Tree* Merge(Tree*tree1,Tree*tree2)override;
};

#endif // BPLUSTREEALGORITHMS_H
