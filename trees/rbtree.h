#ifndef RBTREE_H
#define RBTREE_H
#include "binarytree.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>


using namespace std;

class RBTree : public BinaryTree
{
   private:

    RBTree(Node*);
    void show(Node*, int);

    Node* successor(Node*);
    void rotateLeft(Node*);
    void rotateRight(Node*);
    void insertFix(Node*)override;
    void deleteFix(Node*);

    void inorderBST(Node*);
    void preorderBST(Node*);

    void join(RBTree rbTree2);


public:
    RBTree();
    RBTree(const RBTree &);

    void writeToGV(ofstream &, Node*);
    void display(string);
    void show();
    Node *search(int);

    void inorder();
    void preorder();

    int blackHeight();
    int blackHeight(Node*);
    Node* minValueNode(Node*&);
    Node* maxValueNode(Node*&);

    void merge(RBTree* rbTree2);
    RBTree* splitR(int);


    void stackWrite(int local_value);
    int global_value{0};
    void print_intermediate_steps();




    // Tree interface
public:
    void insert(int);
    void deleteNode(int);
    void merge(Tree *);
    Tree *split(int);
};

class RBIterator{

protected:

    RBTree& tree;
    Node* _Ptr;
    stack<Node*> st;

public:

    RBIterator(RBTree &s):tree(s), _Ptr(nullptr) {}

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

class PreRBIterator : public RBIterator{

public:

    PreRBIterator(RBTree &s):RBIterator(s){

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
        cout << pcur->key << (pcur->color ? "black" : "red") << endl;
        if (pcur->right) st.push(pcur->right);
        if (pcur->left) st.push(pcur->left);
    }
};

#endif // RBTREE_H
