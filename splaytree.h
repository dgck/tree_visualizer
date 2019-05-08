#ifndef SPLAYTREE_H
#define SPLAYTREE_H

#include <fstream>
#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <tuple>

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

        void getVerticesRecursion(Node *x, vector<tuple<int,Node*>> &vertices);

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

        vector<tuple<int, Node*>> getVertices();

        // списки смежности вершин; вершина представляет из себя пару  ( ключ / значение )
        vector<vector<tuple<int, int>>> convertToGraph();

};

// convertToGraph() demonstration WITHOUT repetitive elements
void demo1()
{
        SplayTree t;

        srand(time(NULL));

        for (int i = 0; i < 15; ++i)
                t.insert(rand() % 50 + 1);

        t.show_inorder();

        cout << endl << endl;

        vector<int> e = t.getElements();
        for (int i = 0; i < e.size(); ++i)
                cout << e[i] << " ";
        cout << endl;

        vector<tuple<int, Node*>> v = t.getVertices();

        for (int i = 0; i < v.size(); ++i)
                cout << get<0>(v[i]) << " " << get<1>(v[i])->key << "| ";

        cout << "\n\n\n\n";

        vector<vector<tuple<int, int>>> al = t.convertToGraph();

        for (int i = 0; i < al.size(); ++i)
        {
                for (int j = 0; j < al[i].size(); ++j)
                        cout << get<0>(al[i][j]) << " " << get<1>(al[i][j]) << "| ";
                cout << endl;
        }
}

// convertToGraph() demonstration WITH repetitive elements
void demo2()
{
        SplayTree t;

        srand(time(NULL));

        for (int i = 0; i < 10; ++i)
                t.insert(rand() % 50 + 1);

        t.insert(7);
        t.insert(7);
        t.insert(7);
        t.insert(-9);
        t.insert(-9);

        t.show_inorder();

        cout << endl << endl;

        vector<int> e = t.getElements();
        for (int i = 0; i < e.size(); ++i)
                cout << e[i] << " ";
        cout << endl;

        vector<tuple<int, Node*>> v = t.getVertices();

        for (int i = 0; i < v.size(); ++i)
                cout << get<0>(v[i]) << " " << get<1>(v[i])->key << "| ";

        cout << "\n\n\n\n";

        vector<vector<tuple<int, int>>> al = t.convertToGraph();

        for (int i = 0; i < al.size(); ++i)
        {
                for (int j = 0; j < al[i].size(); ++j)
                        cout << get<0>(al[i][j]) << " " << get<1>(al[i][j]) << "| ";
                cout << endl;
        }
}

#endif // SPLAYTREE_H
