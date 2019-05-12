#ifndef TREE_H
#define TREE_H

#include <vector>
using namespace std;


class Tree
{
public:

       virtual void insert(int) = 0;
       virtual void deleteNode(int) = 0;
       virtual vector<int> getElements()=0;

       virtual void merge(Tree*) = 0;
       virtual Tree* split(int) = 0;

       virtual vector<int> intersection(Tree*) = 0;
       virtual vector<int> intersection(vector<int> v1, vector<int> v2) = 0;
       virtual tuple<bool, int> inclusion(Tree*) = 0;

       virtual void dfs() = 0;
       virtual vector<vector<int>> bfs(int)=0;
       virtual vector<int> diameter()=0;
       virtual void center()=0;

       virtual ~Tree(){}
};

#endif // TREE_H

