#ifndef BPLUSTREE_H
#define BPLUSTREE_H
#include <iostream>
#include <vector>
#include <string>
#include "tree.h"

using namespace std;
const int MAX = 50;

struct Node {
    int nElems;
    Node *parent;
    int value[MAX];
    Node *child[MAX];
    Node() {
        nElems = 0;
        parent = nullptr;
        for (int i = 0; i < MAX; i++) {
            value[i] = INT_MAX;
            child[i] = nullptr;
        }
    }
};

class BplusTree:public Tree
{

private:
    int T = 4; //степінь [t = t + 1]
    void splitLeaf(Node *curr);
    void splitNonLeaf(Node *curr);
    void insertNode(Node* curr, int val);
    void redistributeCell(Node *left, Node *right, bool isLeaf, int posOfLeftBlock, int isCurBlock);
    void mergeCell(Node *left, Node *right, bool isLeaf, int posOfRightBlock);
    void deleteNode(Node *curr, int value, int currPos);
    void getElem(vector <Node*> Nodes, vector<int>& v);
    void graphvizRec(vector <Node*> Nodes);
    void getVerticesRecursion(Node *, vector<tuple<int, Node *>> &);
    vector<tuple<int, Node *>> getVertices();
    void dfs(int v, vector<vector<tuple<int, Node*>>> g, vector<bool> &used, vector<int> &path);


public:
    Node* root;

    BplusTree();
    ~BplusTree()override;

    Node* getRoot() { return root; }
    vector<vector<tuple<int, Node*>>> convertToGraph();
    void graphviz();


    // Tree interface
public:
    void insert(int val)override;
    void deleteNode(int val)override;
    vector<int> getElements()override;
    void merge(Tree *) override;
    Tree *split(int) override;
    vector<int> intersection(Tree *) override;
    vector<int> intersection(vector<int> v1, vector<int> v2) override;
    tuple<bool, int> inclusion(Tree*) override;
    void dfs() override;
    vector<vector<tuple<int, int> > > bfs(tuple<int, int>) override;
    vector<vector<tuple<int, string> > > bfs(tuple<int, string>) override;
    vector<vector<tuple<int, int *> > > bfs(tuple<int, int *>) override;
    void diameter() override;
    void center() override;
};



#endif // BPLUSTREE_H
