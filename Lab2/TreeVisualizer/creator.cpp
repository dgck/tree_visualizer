#include "creator.h"

Creator::Creator()
{

}

Tree *Creator::createTree(Creator::TreeType type)
{
    Tree*tree;
    switch (type)
    {
        case SimpleTree:
        {
            tree = new BinaryTree;
            break;
        }
        case RbTree:
        {
            tree = new RBTree;
            break;
        }
        case SplayTree:
        {
            tree = new BinaryTree;//error with splay tree
            break;
        }
        case OBSTTree:
        {
            tree = new OBST;
            break;
        }
        case BTree:
        {
            tree = new BplusTree;
            break;
        }
        case BPlusTree:
        {
            tree = new BplusTree;
            break;
        }
    }
    return tree;
}
