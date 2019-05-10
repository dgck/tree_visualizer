#ifndef OBST_H
#define OBST_H
#include <iostream>
#include <stdlib.h>
#include <iomanip>
#include <vector>
#include <string>
using namespace std;

template <typename T>
class Node
{
public:

    T key;
    int frequency;
    Node<T> *left, *right;

    Node(T data, int cost) : key(data), frequency(cost), left(NULL), right(NULL) {}
};

void ShowMatrixes(int** M, /*int** W, */int** Root, int n)
{
    cout << "Matrix e:\n";
    for (int i = 1; i < n + 2; ++i)
    {
        for (int j = 0; j < n + 1; ++j)
            cout << setw(13) << M[i][j] << " ";
        cout << endl;
    }
    cout << endl;

    cout << endl;
    cout << "Matrix root:\n";
    for (int i = 1; i < n + 1; ++i)
    {
        for (int j = 1; j < n + 1; ++j)
            cout << setw(13) << Root[i][j] << " ";
        cout << endl;
    }
    cout << endl << endl;
}

template <typename T>
class OBST
{
    Node<T>* root;

    void subTreeShowIn(Node<T>* start);

    void subTreeShowPre(Node<T>* start);

    void generateTree(int **Roots, vector<T> input, vector<int> costs);

    void generateSubTree(int **Roots, vector<T> input, vector<int> costs, Node<T>* &r, int first, int last);

    void WriteToGV( Node<T>* p);

public:

    OBST() : root(NULL) {}

    // input must be sorted
    OBST(vector<T> input, vector<int> p);

    void FWrite(string fileName);

    void Inorder();

    void Preorder();
};



#endif // OBST_H
