#ifndef TREE_H
#define TREE_H

#include <vector>
using namespace std;

enum colors { red, black };
struct Node {
public:
    int key;
    Node *father;
    Node *left;
    Node *right;
    int color;

    Node(int input)
    {
        key = input;
        left = nullptr;
        right = nullptr;
        father = nullptr;
        color = red;

    }
};

class Tree
{
public:

    virtual Node* getRoot() = 0;
    virtual void insert(int) = 0;
    virtual void deleteNode(int) = 0;
    virtual Node* search(int key) = 0;
    virtual vector<int> getElements()=0;
    virtual vector<vector<tuple<int, int>>> convertToGraph()=0;
   // virtual int bfs();
   // virtual int dfs();
    virtual ~Tree(){}
};

#endif // TREE_H

