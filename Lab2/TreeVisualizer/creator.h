#ifndef CREATOR_H
#define CREATOR_H

//#include "Trees/binarytree.h"
#include "Trees/bplustree.h"
#include "Trees/obst.h"
#include "Trees/rbtree.h"
#include "Trees/splaytree.h"

/*!
    \brief Class which creates different types of trees an returns it(Use factory method)
    \author Stas Dzunza
    \version 1.0
    \date May 2019
*/
class Creator
{
public:
    Creator();

    /*!
     * Enumeration which describes types of trees
     */
    enum TreeType {SimpleTree,RbTree,SplayTree,OBSTTree,BTree,BPlusTree};

    /*!
     * Factory method which returns new tree
     */
    Tree*createTree(TreeType type);
};

#endif // CREATOR_H
