#ifndef BINARYTREE_H
#define BINARYTREE_H

#include "tree.h"


enum colors { red, black };

class Node{
public:
    int key;
    string data;
    Node *father;
    Node *left;
    Node *right;
    int color;
    int frequency;


    Node(int input);
    Node(string data, int cost);

};

class BinaryTree:public Tree
{
protected:

    virtual void insertFix(Node*);

public:
    BinaryTree();

    Node* root;


    // Tree interface
public:
    void insert(int) override;
    void deleteNode(int) override;
    vector<int> getElements() override;
    void merge(Tree *) override;
    Tree* split(int) override;
    vector<int> intersection(Tree *) override;
    vector<int> intersection(vector<int> v1, vector<int> v2) override;
    tuple<bool, int> inclusion(Tree*) override;
    void dfs() override;

    void dfs(int v, vector<vector<int>> g, vector<bool> &used, vector<int> &path);

    vector<vector<int>> bfs(int) override;

    vector<int> diameter() override;
    void center() override;

    vector<vector<int > > convertToGraph();
    vector<tuple<int, Node *> > getVertices();
    void getVerticesRecursion(Node *x, vector<tuple<int, Node *> > &vertices);
    void getElementsRecursion(Node *x, vector<int > &vertices);

};
/*
class BinaryIterator {

public:
        BinaryIterator(BinaryTree &bt):tree(bt), _Ptr(nullptr) {}

        bool IsDone() const
        {
            return _Ptr == NULL;
        }
        virtual void First() = 0;
        virtual void operator++() = 0;

protected:
        BinaryTree &tree;
        Node *_Ptr;
};

class SplayIterator : public BinaryIterator{
    //SplayIterator()
        int& operator*()
        {
            return _Ptr->key;
        }
};

class OBSTIterator : public BinaryIterator{
        string& operator*()
        {
            return _Ptr->data;
        }
};

class PreSplayIterator : public SplayIterator{

};

class PostSplayIterator : public SplayIterator{

};

class InSplayIterator : public SplayIterator{

    InSplayIterator(BinaryTree &root):SplayIterator(root){}
        void First()
        {
            _Ptr = tree.GetRoot();
            while(!IsDone())
            {
                mst.push(_Ptr);
                if(_Ptr->leftchild == NULL)
                {
                    operator++();
                    return ;
                }
                _Ptr = _Ptr->leftchild;
            }
        }
        void operator++()
        {
            typename BinaryTree<T>::BinaryTreeNode* pcur = NULL;
            if(mst.empty())
            {
                _Ptr = NULL;
                return ;
            }

            pcur = _Ptr = mst.top(); mst.pop();
            pcur = pcur->rightchild;
            while(pcur != NULL)
            {
                mst.push(pcur);
                pcur = pcur->leftchild;
            }
        }
    private:
        stack<typename BinaryTree<T>::BinaryTreeNode*> mst;
};

class PreOBSTIterator : public OBSTIterator{

};

class PostOBSTIterator : public OBSTIterator{

};

class InOBSTIterator : public OBSTIterator{

};*/
#endif // BINARYTREE_H
