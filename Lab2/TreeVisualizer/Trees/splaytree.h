#ifndef SPLAYTREE_H
#define SPLAYTREE_H

#include <fstream>
#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <tuple>
#include "binarytree.h"

using namespace std;

class SplayTree : public BinaryTree
{
        void zig(Node* x);
        void zig_zig(Node* x, Node* p, Node* g);
        void zig_zag(Node* x, Node* p, Node* g);
        Node* findMax(Node* x);
        void splay(Node* x);
        void recursive_print(Node* start);
        void recursive_inorder(Node* start);
public:

        SplayTree();
        void show();
        void show_inorder();
        // корень не изменился
        void merge(Tree *t)override;
        void merge(SplayTree *t);
        Tree* split(int y)override;
        void insert(int data)override;
        Node* search(int data);
        void deleteNode(int data)override;
        void insertFix(Node* x)override;
};

#endif // SPLAYTREE_H
