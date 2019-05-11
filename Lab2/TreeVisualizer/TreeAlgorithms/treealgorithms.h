#ifndef TREEALGORITHMS_H
#define TREEALGORITHMS_H

class Tree;

class TreeAlgorithms
{
public:
    TreeAlgorithms();
    Tree* Merge(Tree*tree1,Tree*tree2);
    Tree* Inclusion(Tree*tree1,Tree*tree2);
    Tree* Intersection(Tree*tree1,Tree*tree2);
    /*and other operations*/
};

#endif // TREEALGORITHMS_H
