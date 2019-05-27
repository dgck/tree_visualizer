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

/*!
 * The (Bplustree) Node struct
 * contains arrays of keys and children
 * number of keys varies from t-1 to 2t-1
 * number of children varies from t to 2t
 * the keys
 * contains appropriate constuctors
 */
struct BNode
{
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

/*!
 * \brief The BplusTree class
 * Search tree with high degree of branching
 * Values ​​stored in leaves
 * All leaves are located at the same depth
 */
class BplusTree:public Tree
{
    int T = 4; //степінь [t = t + 1]

    /*!
     * \brief splitLeaf
     * divides the node with the number of children more than 2t
     */
    void splitLeaf(BNode *curr);
    void splitNonLeaf(BNode *curr);

    void insertNode(BNode* curr, int val);

    /*!
     * \brief redistributeCell
     * redistributes keys between two neighboring nodes
     */
    void redistributeCell(BNode *left, BNode *right, bool isLeaf, int posOfLeftBlock, int isCurBlock);
    void mergeCell(BNode *left, BNode *right, bool isLeaf, int posOfRightBlock);
    void deleteNode(BNode *curr, int value, int currPos);
    void getElem(vector <BNode*> Nodes, vector<int>& v);
    void getVerticesRecursion(BNode *, vector<tuple<int, BNode *>> &);


    vector<tuple<int, BNode *>> getVertices();

    /*!
    * \brief GetVertices
    * \return all the contained keys (sorted) with their numbers
    */
    vector<tuple<int, int> > GetVertices()override;

    /*!
    * \brief bfs
    * modified for searching all paths in trees breadth-first search algorithm
    * \return all the paths from the given vertex to the rest of vertexes
    */
    void dfs(int v, vector<vector<int>> g, vector<bool> &used, vector<int> &path);
    bool search(BNode*, int);

public:
    BNode* root;
    BplusTree();
    ~BplusTree()override;
    BNode* getRoot() { return root; }

    /*!
        * \brief convertToGraph
        * \return adjacency lists of the tree (graph)
        */
    vector<vector<int>> convertToGraph();

    bool search(int);

    // Tree interface
    void insert(int val)override;
    void deleteNode(int val)override;

    /*!
    * \brief getElements
    * \return sorted vector of all the keys contained
    */
    vector<int> getElements()override;
    void merge(Tree *) override;
    Tree *split(int) override;

    /*!
    * \brief intersection
    * searches for an intersection between the current tree elements
    * and the parameter tree elements
    * if the intersection is empty, returns nullptr
    * \return common elements tree
    */
    Tree* intersection(Tree *) override;

    /*!
    * \brief intersection
    * \param v1 first elements vector
    * \param v2 second elements vector
    * \return common elements vector
    */
    vector<int> intersection(vector<int> v1, vector<int> v2) override;

    /*!
    * \brief inclusion
    * a set operation; compares elements, not structured trees
    * \return tuple, the first item defines whether the inclusion take place somehow,
    * the second item defines the type of the inclusion (if it takes place)
    */
    tuple<bool, int> inclusion(Tree*) override;

    /*!
    * \brief dfs
    * trivial depth-first search algorithm
    */
    void dfs() override;
    vector<vector<int> > bfs(int) override;

    /*!
    * \brief diameter
    * \return vetcor of elements of any tree diameter
    */
    vector<int> diameter() override;

    /*!
    * \brief center
    * \return a group (vector) of vertices that are the center of the tree (one or two vertices always)
    */
    vector<int> center() override;

    void inorder()override;
    void preorder()override;
    void postorder()override;
};


/*!
 * \brief The BplusIterator class
 * Iterator for tree traversal(preorder, postorder)
 * Using iterator pattern
 */
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
