#ifndef TREE_H
#define TREE_H

#include "TreeAlgorithms/treealgorithms.h"

struct Node {
    Node(){}
    Node(int key)
    {
        this->left = nullptr;
        this -> right = nullptr;
        this ->parent = nullptr;
        this -> key = key;
        this -> color = true;
    }
    Node* left, *right , *parent;
    int key;
    bool color;
    int sz;
};

class Tree
{
public:
    virtual Node* getRoot() = 0;
    virtual void insert(Node*) = 0;
    virtual void deleteNode(Node*) = 0;
    virtual Node* search(int key,Node*) = 0;
    virtual ~Tree(){}
protected:
    TreeAlgorithms*algorithms;
};

#endif // TREE_H
