#ifndef BPLUSTREE_H
#define BPLUSTREE_H

#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include "tree.h"

#include <numeric>

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
            value[i] = std::numeric_limits <int>::max();
            child[i] = nullptr;
        }
    }
};

class BplusTree:public Tree
{
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

    // Tree interface
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


class BplusIterator{
public:
    BplusIterator(BplusTree &bt):tree(bt), _Ptr(nullptr) {}
    int val()
    {
        return _Ptr->value[0];
    }

    bool IsDone() const
    {
        return st.empty();
    }

    virtual void next() = 0;

    void printTreeInterator()
    {
        while(!IsDone())
            next();
    }
protected:
    BplusTree &tree;
    BNode *_Ptr;
    stack<BNode*> st;

};

class PostIterator : public BplusIterator
{
public:
    PostIterator(BplusTree &bt):BplusIterator(bt){
        _Ptr = tree.root;
         st.push(_Ptr);
    }

    void next()
    {
        if(st.empty()) return;
        while (!st.empty()) {
            BNode* next=st.top();
            bool finishedSubtrees = false;
            for (int i=0;i<=next->nElems;i++) {
                if(next->child[i]==_Ptr) {finishedSubtrees=true; break;}
            }
            bool isLeaf = (next->child[0]==nullptr);
            if(finishedSubtrees||isLeaf){
                st.pop();
                _Ptr=next;
                cout<<"return"<<_Ptr->nElems<<endl;
                return;
            }
            else {
                for (int i=next->nElems;i>=0;i--) {
                    if(next->child[i]!=nullptr) {st.push(next->child[i]);}
                }
            }
        }
    }
};

class PreIterator : public BplusIterator
{
public:
    PreIterator(BplusTree &bt):BplusIterator(bt){
        if (tree.root == nullptr)
               return;
        _Ptr = tree.root;
         st.push(_Ptr);
    }


    void next(){

        if(st.empty()) return;

        while (!st.empty())
        {
            BNode *next = st.top();
            cout<<"return"<<next->nElems<<endl;
            st.pop();

            for (int i=next->nElems;i>=0;i--) {
                if(next->child[i]!=nullptr) {st.push(next->child[i]);}
            }
            return;
         }
    }

};
#endif // BPLUSTREE_H
