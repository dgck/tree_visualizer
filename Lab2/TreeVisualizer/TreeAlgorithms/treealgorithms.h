#ifndef TREEALGORITHMS_H
#define TREEALGORITHMS_H

#include "tree.h"

class TreeAlgorithms
{
public:
    TreeAlgorithms();
    virtual void WriteToGV(Tree*tree) = 0;
    virtual void CreateImageFromGV(Tree*tree) = 0;
    virtual Tree* Merge(Tree*tree1,Tree*tree2) = 0;
    /*and other operations*/
};

#endif // TREEALGORITHMS_H
