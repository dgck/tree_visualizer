#ifndef BINARYTREE_H
#define BINARYTREE_H

#include "tree.h"
#include <vector>

enum colors { red, black };



class BinaryTree:public Tree
{
protected:

    virtual void insertFix(Node*);

private:

    void inorderBST(Node*);
    void preorderBST(Node*);
    void postorderBST(Node*);

public:
    BinaryTree();
    Node* root = nullptr;

    Node* successor(Node *p);
    void insert(int) override;
    void deleteNode(int) override;
    vector<int> getElements() override;
    void merge(Tree *) override;
    Tree* split(int) override;
    Node* search(int);
    Node* search(string);
    Tree* intersection(Tree *) override;
    vector<int> intersection(vector<int> v1, vector<int> v2) override;
    tuple<bool, int> inclusion(Tree*) override;
    void dfs() override;
    vector<vector<int>> bfs(int) override;
    vector<int> diameter() override;
    vector<int> center() override;
    void inorder()override;
    void preorder()override;
    void postorder()override;

    // НОВОЕ
    void bfs_ptr_move();
    std::vector <Node*> get_cur_bfs_vis();
    std::vector <Node*> m_cur_bfs_vis;


    Node* get_root()
    {
        return root;
    }

    void dfs(int v, vector<vector<int>> g, vector<bool> &used, vector<int> &path);
    vector<vector<int > > convertToGraph();
    vector<tuple<int, Node *> > getVertices()/*override*/;
    vector<tuple<int, int> > GetVertices()override;
    void getVerticesRecursion(Node *x, vector<tuple<int, Node *> > &vertices);
    void getVerticesRecursion(Node *x, vector<tuple<int, int> > &vertices);
    void getElementsRecursion(Node *x, vector<int > &vertices);
};

#endif // BINARYTREE_H
