#ifndef TREE_H
#define TREE_H

#include <vector>
using namespace std;


class TNode {
    protected:
   TNode();
};

class Tree
{
public:
    TNode* root;
    virtual void insert(int) = 0;
    virtual void deleteNode(int) = 0;
    virtual vector<int> getElements()=0;

    virtual void merge(Tree*) = 0;
    virtual Tree* split(int) = 0;

    virtual vector<int> intersection(Tree*) = 0;
    virtual vector<int> intersection(vector<int> v1, vector<int> v2) = 0;
    virtual tuple<bool, int> inclusion() = 0;

    virtual void dfs() = 0;
    virtual void dfs(int v,vector<vector<tuple<int, int>>> g, vector<bool>& used, vector<int>& path)=0;
    virtual vector<vector<tuple<int,TNode*>>> bfs()=0;
    //path, center, diameter

    virtual vector<vector<tuple<int, int>>> convertToGraph()=0;
    virtual vector<tuple<int, TNode *>> getVertices()=0;
    virtual void getVerticesRecursion(TNode *x, vector<tuple<int, TNode *> > &vertices) = 0;

    virtual ~Tree(){}
};

#endif // TREE_H

