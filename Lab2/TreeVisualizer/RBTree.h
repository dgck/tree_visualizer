//
// Created by artyom on 17.02.19.
//

#ifndef RED_BLACK_TREE_RBTREE_H
#define RED_BLACK_TREE_RBTREE_H
#include "tree.h"

// 1 red
// 0 black

class RBTree:public Tree {
public:

    RBTree();

    Node* getRoot();
    void setRoot(Node* r);
    Node* getGoodNode(int v);

    void insert(Node* i)override;
    void show();

    void leftRotate(Node* x);
    void rightRotate(Node* x);
    void transplant(Node* x, Node* y);
    void deleteNode(Node* x)override;
    void fixDeletion(Node* x);

private:
    void insertFixup(Node* z);
    void stackWrite();


    Node* root;
};


#endif //RED_BLACK_TREE_RBTREE_H
