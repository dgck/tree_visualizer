#ifndef BINARYTREE_H
#define BINARYTREE_H

#include "tree.h"

enum colors { red, black };

struct Node{
    Node(int input);
    Node(string data, int cost);

    int key;
    string data;
    Node *father;
    Node *left;
    Node *right;
    int color;
    int frequency;
};

class BinaryTree:public Tree
{
protected:

    virtual void insertFix(Node*);

public:
    BinaryTree();
    Node* root;

    // Tree interface
    void insert(int) override;
    void deleteNode(int) override;
    vector<int> getElements() override;
    void merge(Tree *) override;
    Tree* split(int) override;
    vector<int> intersection(Tree *) override;
    vector<int> intersection(vector<int> v1, vector<int> v2) override;
    tuple<bool, int> inclusion(Tree*) override;
    void dfs() override;
    vector<vector<int>> bfs(int) override;
    vector<int> diameter() override;
    void center() override;

    void dfs(int v, vector<vector<int>> g, vector<bool> &used, vector<int> &path);
    vector<vector<int > > convertToGraph();
    vector<tuple<int, Node *> > getVertices();
    void getVerticesRecursion(Node *x, vector<tuple<int, Node *> > &vertices);
    void getElementsRecursion(Node *x, vector<int > &vertices);
};

#endif // BINARYTREE_H
