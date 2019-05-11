#ifndef SPLAYTREE_H
#define SPLAYTREE_H


#include <fstream>
#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <tuple>
#include "binarytree.h"


using namespace std;



class SplayTree : public BinaryTree
{
private:

        void zig(Node* x);

        void zig_zig(Node* x, Node* p, Node* g);

        void zig_zag(Node* x, Node* p, Node* g);

        Node* findMax(Node* x);

        void splay(Node* x);

        void recursive_print(Node* start);

        void recursive_inorder(Node* start);

        void getElementsRecursion(Node *x, vector<int> &elements);

        void getVerticesRecursion(Node *x, vector<tuple<int,Node*>> &vertices);

public:

        SplayTree();

        void show();

        void show_inorder();

        // корень не изменился
        void merge(Tree *t);

        void merge(SplayTree *t);

        Tree* split(int y);

        void insert(int data);

        Node* search(int data);

        void deleteNode(int data);

        vector<int> getElements();

        vector<tuple<int, Node*>> getVertices();

        // списки смежности вершин; вершина представляет из себя пару  ( ключ / значение )
        //vector<vector<tuple<int, int>>> convertToGraph();

        vector<int> intersection(Tree*);
        vector<int> intersection(vector<int> v1, vector<int> v2);
        tuple<bool, int> inclusion();

        void dfs();
        void dfs(int v, vector<vector<tuple<int, int>>> g, vector<bool> &used, vector<int> &path);
        void dfs(int v, vector<vector<tuple<int, string>>> g, vector<bool> &used, vector<int> &path);
        vector<vector<tuple<int,int>>> bfs(tuple<int,int>);
        vector<vector<tuple<int,string>>> bfs(tuple<int,string>);
        vector<vector<tuple<int,int*>>> bfs(tuple<int,int*>);
        void diameter();
        void center();

};

#endif // SPLAYTREE_H
