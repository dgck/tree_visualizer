#ifndef OBST_H
#define OBST_H

#include "binarytree.h"

#include <iostream>
#include <stdlib.h>
#include <iomanip>
#include <vector>
#include <string>
#include <stack>
#include "binarytree.h"

using namespace std;

/*!
 * \brief The OBST class
 * Static optimal binary search tree
 */
class OBST : public BinaryTree
{
    void subTreeShowIn(Node* start);
    void subTreeShowPre(Node* start);
    void generateTree(int **Roots, vector<string> input, vector<int> costs);
    void generateSubTree(int **Roots, vector<string> input, vector<int> costs, Node* &r, int first, int last);
    void Preparation(vector<string>&, vector<int>&);

public:

    /*!
     * \brief OBST
     * builds an optimal binary search tree using sorted input vectors,
     * helper matrixes of mathematical expectations of search costs
     * and roots for all the subtrees
     */
    OBST();

    // input must be sorted
    /*!
     * \brief OBST
     * \param input - vector of words in text
     * \param p - vector of probabilities for appropriate words
     */
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
        cout << pcur->data << endl;
        if (pcur->right) st.push(pcur->right);
        if (pcur->left) st.push(pcur->left);
    }
};


class PostOBSTIterator : public OBSTIterator{

public:

    PostOBSTIterator(OBST &s):OBSTIterator(s){

        if (tree.root == nullptr)
               return;
        _Ptr = tree.root;
        st.push(_Ptr);
    }

    void next() {
           if(st.empty()) return;

           while (!st.empty()) {
               Node* x=st.top();
               bool finishedSubtrees = false;
               if (x->left == _Ptr || x->right == _Ptr)
                   finishedSubtrees=true;
               bool isLeaf = !(x->left || x->right);
               if(finishedSubtrees||isLeaf){
                   st.pop();
                   _Ptr=x;
                   cout<<_Ptr->key<<endl;
                   return;
               }
               else {
                   if (x->right) st.push(x->right);
                   if (x->left) st.push(x->left);
               }

           }
    }
};

class InOBSTIterator : public OBSTIterator {

public:

    InOBSTIterator(OBST &s):OBSTIterator(s){

        if (tree.root == nullptr)
               return;
        _Ptr = tree.root;
        st.push(_Ptr);
    }

    void next() {

        Node* pcur = st.top();
        st.pop();

        while (pcur != nullptr || !st.empty())
        {
            while (pcur != nullptr)
            {
                st.push(pcur);
                pcur = pcur->left;
            }

            pcur = st.top(); st.pop();
            cout << pcur->key << endl;

            pcur = pcur->right;
        }

    }
};
#endif // OBST_H
