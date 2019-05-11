#include "binarytree.h"
#include <tuple>



Node::Node(int input)
{
    key = input;
    left = nullptr;
    right = nullptr;
    father = nullptr;
    color = red;

}

Node::Node(string data, int cost){

    this->data = data;
    frequency = cost;
    left = nullptr;
    right = nullptr;
    father = nullptr;
    color = red;
}

BinaryTree::BinaryTree()
{

}

void BinaryTree::insert(int)
{
}

void BinaryTree::deleteNode(int)
{
}

vector<int> BinaryTree::getElements()
{
}

void BinaryTree::merge(Tree *)
{
}

Tree *BinaryTree::split(Tree *)
{
}

vector<int> BinaryTree::intersection(Tree *)
{
}

vector<int> BinaryTree::intersection(vector<int> v1, vector<int> v2)
{
}

tuple<bool, int> BinaryTree::inclusion()
{
}

void BinaryTree::dfs()
{
}

void BinaryTree::dfs(int v, vector<vector<tuple<int, int> > > g, vector<bool> &used, vector<int> &path)
{
}

vector<vector<tuple<int, TNode *> > > BinaryTree::bfs()
{
}

vector<vector<tuple<int, int> > > BinaryTree::convertToGraph()
{
}

vector<tuple<int, TNode *> > BinaryTree::getVertices()
{
}

void BinaryTree::getVerticesRecursion(TNode *x, vector<tuple<int, TNode *> > &vertices)
{
}
