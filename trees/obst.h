#ifndef OBST_H
#define OBST_H
#include <iostream>
#include <stdlib.h>
#include <iomanip>
#include <vector>
#include <string>
#include "binarytree.h"
using namespace std;


class OBST : public BinaryTree
{
    void subTreeShowIn(Node* start);

    void subTreeShowPre(Node* start);

    void generateTree(int **Roots, vector<string> input, vector<int> costs);

    void generateSubTree(int **Roots, vector<string> input, vector<int> costs, Node* &r, int first, int last);

    void WriteToGV(Node* p);

    void Preparation(vector<string>&, vector<int>&);

public:

    OBST();

    // input must be sorted
    OBST(vector<string> input, vector<int> p);

    void FWrite(string fileName);

    void Inorder();

    void Preorder();


};

class OBSTIterator{

protected:

    OBST& tree;
    Node* _Ptr;
    stack<Node*> st;

public:

    OBSTIterator(OBST &s):tree(s), _Ptr(nullptr) {}

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

};

class PreOBSTIterator : public OBSTIterator{

public:

    PreOBSTIterator(OBST &s):OBSTIterator(s){

        if (tree.root == nullptr)
               return;
        _Ptr = tree.root;
        st.push(_Ptr);
    }


    void next(){

        if(st.empty()) return;

        Node* pcur = nullptr;
        pcur = _Ptr = st.top();
        st.pop();
        cout << pcur->data << " " << pcur->frequency << endl;
        if (pcur->right) st.push(pcur->right);
        if (pcur->left) st.push(pcur->left);
    }
};


#endif // OBST_H
