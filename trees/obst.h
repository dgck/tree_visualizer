#ifndef OBST_H
#define OBST_H
#include <iostream>
#include <stdlib.h>
#include <iomanip>
#include <vector>
#include <string>
#include "binarytree.h"
using namespace std;


class OBST : public BinaryTree
{
    void subTreeShowIn(Node* start);

    void subTreeShowPre(Node* start);

    void generateTree(int **Roots, vector<string> input, vector<int> costs);

    void generateSubTree(int **Roots, vector<string> input, vector<int> costs, Node* &r, int first, int last);

    void WriteToGV(Node* p);

    void Preparation(vector<string>&, vector<int>&);

public:

    OBST();

    // input must be sorted
    OBST(vector<string> input, vector<int> p);

    void FWrite(string fileName);

    void Inorder();

    void Preorder();


};



#endif // OBST_H
