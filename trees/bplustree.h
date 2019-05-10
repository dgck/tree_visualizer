#ifndef BPLUSTREE_H
#define BPLUSTREE_H
#include <iostream>
#include <vector>
#include <string>

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

class BplusTree
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


public:
    Node* root;

    BplusTree();
    ~BplusTree();

    void insert(int val);
    void deleteNode(int val);
    Node* getRoot() { return root; }
    vector<int> getElements();
    vector<vector<tuple<int, Node*>>> convertToGraph();

    void graphviz(vector <Node*> Nodes);

};



#endif // BPLUSTREE_H
