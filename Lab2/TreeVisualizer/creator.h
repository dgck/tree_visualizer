#ifndef CREATOR_H
#define CREATOR_H

#include "RBTree.h"

class Creator
{
public:
    Creator();

    enum TreeType {SimpleTree,RbTree,SplayTree,OBSTTree,BTree,BPlusTree};

    //factory method
    Tree*createTree(TreeType type);
};

#endif // CREATOR_H
