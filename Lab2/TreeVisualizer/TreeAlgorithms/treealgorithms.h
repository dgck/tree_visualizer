#ifndef TREEALGORITHMS_H
#define TREEALGORITHMS_H

class Tree;

class TreeAlgorithms
{
public:
    TreeAlgorithms();
    virtual Tree* Merge(Tree*tree1,Tree*tree2) = 0;
    virtual Tree* Inclusion(Tree*tree1,Tree*tree2) = 0;
    virtual Tree* Intersection(Tree*tree1,Tree*tree2) = 0;
    /*and other operations*/
};

#endif // TREEALGORITHMS_H
