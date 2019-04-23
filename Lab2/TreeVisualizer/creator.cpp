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
            //tree = new BinaryTree;
            break;
        }
        case RbTree:
        {
            tree = new RBTree;
            break;
        }
        case SplayTree:
        {
            //tree = new SplayTree;
            break;
        }
        case OBSTTree:
        {
            //tree = new OBSTTree;
            break;
        }
        case AVLTree:
        {
            //tree = new AVLTree;
            break;
        }
    }
    return tree;
}
