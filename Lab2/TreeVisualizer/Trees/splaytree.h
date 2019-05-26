#ifndef SPLAYTREE_H
#define SPLAYTREE_H

#include <fstream>
#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <tuple>
#include <stack>
#include "binarytree.h"

using namespace std;

class SplayTree : public BinaryTree
{
        void zig(Node* x);
        void zig_zig(Node* x, Node* p, Node* g);
        void zig_zag(Node* x, Node* p, Node* g);
        Node* findMax(Node* x);
        void splay(Node* x);
        void recursive_print(Node* start);
        void recursive_inorder(Node* start);
public:

        SplayTree();
        void show();
        void show_inorder();
        // корень не изменился
        void merge(Tree *t)override;
        void merge(SplayTree *t);
        Tree* split(int y)override;
        void insert(int data)override;
        Node* search(int data);
        void deleteNode(int data)override;
        void insertFix(Node* x)override;
};

class SplayIterator{

protected:

    SplayTree& tree;
    Node* _Ptr;
    stack<Node*> st;

public:

    SplayIterator(SplayTree &s):tree(s), _Ptr(nullptr) {}

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

class PreSplayIterator : public SplayIterator{

public:

    PreSplayIterator(SplayTree &s):SplayIterator(s){

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
        cout << pcur->key << endl;
        if (pcur->right) st.push(pcur->right);
        if (pcur->left) st.push(pcur->left);
    }
};

class PostSplayIterator : public SplayIterator{

public:

    PostSplayIterator(SplayTree &s):SplayIterator(s){

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

class InSplayIterator : public SplayIterator {

public:

    InSplayIterator(SplayTree &s):SplayIterator(s){

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

#endif // SPLAYTREE_H
