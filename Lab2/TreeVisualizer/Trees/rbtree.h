#ifndef RBTREE_H
#define RBTREE_H
#include "binarytree.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>
#include <stack>

using namespace std;

/*!
 * \brief The RBTree class
 * Self-balancing binary search tree
 * Each node is either red or black.
 * The root is black. This rule is sometimes omitted. Since the root can always be changed from red to black, but not necessarily vice versa, this rule has little effect on analysis.
 * All leaves are black.
 * If a node is red, then both its children are black.
 * Every path from a given node to any of its descendant NIL nodes contains the same number of black nodes.
 */
class RBTree : public BinaryTree
{
    RBTree(Node*);
    Node* successor(Node*);

    /*!
     * \brief rotateLeft
     * \brief rotateRight
     * Changes the structure without interfering with the order of the elements
     * Moves one node up in the tree and one node down
     */
    void rotateLeft(Node*);
    void rotateRight(Node*);

    /*!
     * \brief insertFix
     * \brief deleteFix
     * Restores all tree properties using right and left otation
     */
    void insertFix(Node*)override;
    void deleteFix(Node*);
    void join(RBTree rbTree2);

public:
    RBTree();
    RBTree(const RBTree &);
    void display(string);
    void show();
    Node *search(int);

    /*!
     * \brief blackHeight
     * \return number of black nodes from current node to leaves
     */
    int blackHeight();
    int blackHeight(Node*);

    /*!
     * \brief minValueNode
     * \return node winh minimum key after current
     */
    Node* minValueNode(Node*&);

    /*!
     * \brief maxValueNode
     * \return node winh maximum key after current
     */
    Node* maxValueNode(Node*&);
    void merge(RBTree* rbTree2);
    RBTree* splitR(int);
    void stackWrite(int local_value);
    int global_value{0};
    void print_intermediate_steps();
    // Tree interface
public:
    void insert(int)override;
    void deleteNode(int)override;
    void merge(Tree *)override;
    Tree *split(int)override;
};

/*!
 * \brief The RBIterator class
 * Iterator for tree traversal(preorder, postorder, inorder)
 * Using iterator pattern
 */
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

class PostRBIterator : public RBIterator{

public:

    PostRBIterator(RBTree &s):RBIterator(s){

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

class InRBIterator : public RBIterator {

public:

    InRBIterator(RBTree &s):RBIterator(s){

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


#endif // RBTREE_H
