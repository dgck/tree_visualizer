#ifndef BINARYTREE_H
#define BINARYTREE_H

#include "tree.h"


enum colors { red, black };

class Node:public TNode{
public:
    int key;
    string data;
    Node *father;
    Node *left;
    Node *right;
    int color;
    int frequency;


    Node(int input);
    Node(string data, int cost);

};

class BinaryTree:public Tree
{
public:
    BinaryTree();

    Node* root;


    // Tree interface
public:
    void insert(int);
    void deleteNode(int);
    vector<int> getElements();
    void merge(Tree*);
    Tree *split(int);
    vector<int> intersection(Tree *);
    vector<int> intersection(vector<int> v1, vector<int> v2);
    tuple<bool, int> inclusion();
    void dfs();
    void dfs(int v, vector<vector<tuple<int, int> > > g, vector<bool> &used, vector<int> &path);
    vector<vector<tuple<int, TNode *> > > bfs();
    vector<vector<tuple<int, int> > > convertToGraph();
    vector<tuple<int, TNode *> > getVertices();
    void getVerticesRecursion(TNode *x, vector<tuple<int, TNode *> > &vertices);
};

#endif // BINARYTREE_H
