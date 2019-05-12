#ifndef CREATOR_H
#define CREATOR_H

//#include "Trees/binarytree.h"
#include "Trees/bplustree.h"
#include "Trees/obst.h"
#include "Trees/rbtree.h"
#include "Trees/splaytree.h"

class Creator
{
public:
    Creator();

    enum TreeType {SimpleTree,RbTree,SplayTree,OBSTTree,BTree,BPlusTree};

    //factory method
    Tree*createTree(TreeType type);
};

#endif // CREATOR_H
