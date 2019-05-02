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
            tree = new RBTree;
            break;
        }
        case RbTree:
        {
            tree = new RBTree;
            break;
        }
        case SplayTree:
        {
            tree = new RBTree;
            break;
        }
        case OBSTTree:
        {
            tree = new RBTree;
            break;
        }
        case BTree:
        {
            tree = new RBTree;
            break;
        }
        case BPlusTree:
        {
            tree = new RBTree;
            break;
        }
    }
    return tree;
}
