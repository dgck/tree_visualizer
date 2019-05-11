#ifndef BINARYTREE_H
#define BINARYTREE_H

#include "tree.h"


enum colors { red, black };

class Node{
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
    void insert(int) override;
    void deleteNode(int) override;
    vector<int> getElements() override;
    void merge(Tree *) override;
    Tree* split(int) override;
    vector<int> intersection(Tree *) override;
    vector<int> intersection(vector<int> v1, vector<int> v2) override;
    tuple<bool, int> inclusion(Tree*) override;
    void dfs() override;

    void dfs(int v, vector<vector<tuple<int, int>>> g, vector<bool> &used, vector<int> &path);
    void dfs(int v, vector<vector<tuple<int, string>>> g, vector<bool> &used, vector<int> &path);

    vector<vector<tuple<int, int>>> bfs(tuple<int, int>) override;
    vector<vector<tuple<int, string>>> bfs(tuple<int, string>) override;
    vector<vector<tuple<int, int*>>> bfs(tuple<int, int*>) override;

    void diameter() override;
    void center() override;

    vector<vector<tuple<int, int> > > convertToGraph();
    vector<tuple<int, Node *> > getVertices();
    void getVerticesRecursion(Node *x, vector<tuple<int, Node *> > &vertices);


   /* void insert(int);
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
    void getVerticesRecursion(TNode *x, vector<tuple<int, TNode *> > &vertices);*/
};

#endif // BINARYTREE_H
