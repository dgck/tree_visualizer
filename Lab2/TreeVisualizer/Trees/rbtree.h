#ifndef RBTREE_H
#define RBTREE_H
#include "binarytree.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>

using namespace std;

class RBTree : public BinaryTree
{
    RBTree(Node*);
    void show(Node*, int);
    Node* successor(Node*);
    void rotateLeft(Node*);
    void rotateRight(Node*);
    void insertFix(Node*)override;
    void deleteFix(Node*);
    void inorderBST(Node*);
    void preorderBST(Node*);
    void join(RBTree rbTree2);

public:
    RBTree();
    RBTree(const RBTree &);
    void display(string);
    void show();
    Node *search(int);
    void inorder();
    void preorder();
    int blackHeight();
    int blackHeight(Node*);
    Node* minValueNode(Node*&);
    Node* maxValueNode(Node*&);
    void merge(RBTree* rbTree2);
    RBTree* splitR(int);
    void stackWrite(int local_value);
    int global_value{0};
    void print_intermediate_steps();
    // Tree interface
public:
    void insert(int);
    void deleteNode(int);
    void merge(Tree *);
    Tree *split(int);
};
#endif // RBTREE_H
