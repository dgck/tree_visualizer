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



void BinaryTree::insert(int)
{

}

void BinaryTree::deleteNode(int)
{

}

vector<int> BinaryTree::getElements()
{
    vector<int> v;
    return v;
}

void BinaryTree::merge(Tree *)
{

}

Tree *BinaryTree::split(int)
{
    return nullptr;
}

vector<int> BinaryTree::intersection(Tree *)
{
    vector<int> v;
    return v;
}

vector<int> BinaryTree::intersection(vector<int> v1, vector<int> v2)
{
    vector<int> v;
    return v;
}

tuple<bool, int> BinaryTree::inclusion(Tree *)
{
    tuple<bool, int> v;
    return v;
}

void BinaryTree::dfs()
{

}

void BinaryTree::dfs(int v, vector<vector<tuple<int, int> > > g, vector<bool> &used, vector<int> &path)
{

}

void BinaryTree::dfs(int v, vector<vector<tuple<int, string> > > g, vector<bool> &used, vector<int> &path)
{

}

vector<vector<tuple<int, int> > > BinaryTree::bfs(tuple<int, int>)
{
    vector<vector<tuple<int, int> > > v;
    return v;
}

vector<vector<tuple<int, string> > > BinaryTree::bfs(tuple<int, string>)
{
    vector<vector<tuple<int, string> > > v;
    return v;
}

vector<vector<tuple<int, int*>>> BinaryTree::bfs(tuple<int, int *>)
{
    vector<vector<tuple<int, int*> > > v;
    return v;
}

void BinaryTree::diameter()
{

}

void BinaryTree::center()
{

}

vector<vector<tuple<int, int> > > BinaryTree::convertToGraph()
{
    vector<vector<tuple<int, int> > > v;
    return v;
}

vector<tuple<int, Node*>> BinaryTree::getVertices()
{
    vector<tuple<int, Node*>> v;
    return v;
}

void BinaryTree::getVerticesRecursion(Node *x, vector<tuple<int, Node *> > &vertices)
{

}


