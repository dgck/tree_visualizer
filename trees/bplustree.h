#ifndef BPLUSTREE_H
#define BPLUSTREE_H
#include <iostream>
#include <vector>
#include <string>
#include "tree.h"

using namespace std;
const int MAX = 50;

struct BNode {
    int nElems;
    BNode *parent;
    int value[MAX];
    BNode *child[MAX];
    BNode() {
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
    void splitLeaf(BNode *curr);
    void splitNonLeaf(BNode *curr);
    void insertNode(BNode* curr, int val);
    void redistributeCell(BNode *left, BNode *right, bool isLeaf, int posOfLeftBlock, int isCurBlock);
    void mergeCell(BNode *left, BNode *right, bool isLeaf, int posOfRightBlock);
    void deleteNode(BNode *curr, int value, int currPos);
    void getElem(vector <BNode*> Nodes, vector<int>& v);
    void graphvizRec(vector <BNode*> Nodes);
    void getVerticesRecursion(BNode *, vector<tuple<int, BNode *>> &);
    vector<tuple<int, BNode *>> getVertices();
    void dfs(int v, vector<vector<int>> g, vector<bool> &used, vector<int> &path);


public:
    BNode* root;

    BplusTree();
    ~BplusTree()override;

    BNode* getRoot() { return root; }
    vector<vector<int>> convertToGraph();
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
    vector<vector<int> > bfs(int) override;
    vector<int> diameter() override;
    void center() override;
};



#endif // BPLUSTREE_H
