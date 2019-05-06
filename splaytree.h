#ifndef SPLAYTREE_H
#define SPLAYTREE_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class Node
{
public:
        int key;
        Node* left;
        Node* right;
        Node* parent;
        Node(int k) : key(k), parent(NULL), left(NULL), right(NULL) {}
};

class SplayTree
{
private:

        void zig(Node* x);

        void zig_zig(Node* x, Node* p, Node* g);

        void zig_zag(Node* x, Node* p, Node* g);

        Node* findMax(Node* x);

        void splay(Node* x);

        void recursive_print(Node* start);

        void recursive_inorder(Node* start);

        void WriteToGV(ofstream &fout, Node* p);

        void getElementsRecursion(Node *x, vector<int> &elements);

public:

        SplayTree() : root(NULL) {}

        Node* root;

        void show();

        void show_inorder();

        // корень не изменился
        void merge(SplayTree *t);

        SplayTree* split(Node* x);

        void insert(int data);

        void FWrite(string fileName);

        Node* search(int data);

        void del(int data);

        vector<int> getElements();
};

#endif // SPLAYTREE_H
