#ifndef RBTREE_H
#define RBTREE_H
#include "binarytree.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>


using namespace std;
/*
class RBTree : public BinaryTree
{
   private:

    RBTree(Node*);
    void Show(Node*, int);

    Node* Successor(Node*);
    void RotateLeft(Node*);
    void RotateRight(Node*);
    void InsertFix(Node*);
    void DeleteFix(Node*);

    void inorderBST(Node*);
    void preorderBST(Node*);

    void join(RBTree rbTree2);

    void getElem(Node*, vector<int>&);
    void getElementsRecursion(Node *x, vector<int> &elements);

public:
    RBTree();
    RBTree(const RBTree &);

    void WriteToGV(ofstream &, Node*);
    void display(string);
    void Show();

    void inorder();
    void preorder();

    int BlackHeight();
    int BlackHeight(Node*);
    Node* minValueNode(Node*&);
    Node* maxValueNode(Node*&);

    void merge(RBTree rbTree2);
    RBTree* splitR(int);

    vector<vector<tuple<int, int>>> convertToGraph();
    vector<tuple<int, Node*>> getVertices();
    void getVerticesRecursion(Node *x, vector<tuple<int,Node*>> &vertices);





    void stackWrite(int local_value);
    int global_value{0};
    void print_intermediate_steps();




    // Tree interface
public:
    void insert(int);
    void deleteNode(int);
    void merge(Tree *);
    Tree *split(int);
    vector<int> getElements();
};
*/
#endif // RBTREE_H
