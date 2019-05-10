#ifndef RBTREE_H
#define RBTREE_H
#include "tree.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>


using namespace std;

class RBTree : public Tree
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
    void getVerticesRecursion(Node *x, vector<tuple<int,Node*>> &vertices);

public:
    Node *root;
    RBTree() :root(nullptr) {}
    RBTree(const RBTree &);

    void WriteToGV(ofstream &, Node*);
    void display(string);

    void Show();
    Node* getRoot()override;
    void insert(int input)override;
    void deleteNode(int)override;
    Node* search(int)override;

    void inorder();
    void preorder();

    int BlackHeight();
    int BlackHeight(Node*);
    Node* minValueNode(Node*&);
    Node* maxValueNode(Node*&);

    void merge(RBTree rbTree2);
    RBTree split(int);
    vector<int> getElements()override;

    vector<tuple<int, Node*>> getVertices();

    // списки смежности вершин; вершина представляет из себя пару  ( ключ / значение )
    vector<vector<tuple<int, int>>> convertToGraph()override;




    void stackWrite(int local_value);
    int global_value{0};
    void print_intermediate_steps();

};

#endif // RBTREE_H
