#ifndef TREE_H
#define TREE_H

#include <vector>
#include <string>
#include <algorithm>
#include <QGraphicsScene>

using namespace std;

class QGVAbstractTreeSceneFactory;

struct Node {
    Node(int input);
    Node(string data, int cost);

    int key;
    string data;
    Node *father;
    Node *left;
    Node *right;
    int color;
    int frequency;

    int get_key()
    {
        return key;
    }

    Node* get_parent()
    {
        return father;
    }

    Node* get_left()
    {
        return left;
    }

    Node* get_right ()
    {
        return right;
    }

    bool get_is_black()
    {
        return color == 0;
    }
};

class Tree
{
public:

       virtual void insert(int) = 0;
       virtual void deleteNode(int) = 0;
       virtual vector<int> getElements()=0;

       virtual void merge(Tree*) = 0;
       virtual Tree* split(int) = 0;

       virtual Tree* intersection(Tree*) = 0;
       virtual vector<int> intersection(vector<int> v1, vector<int> v2) = 0;
       virtual tuple<bool, int> inclusion(Tree*) = 0;

       virtual void dfs() = 0;
       virtual vector<vector<int>> bfs(int)=0;
       virtual vector<int> diameter()=0;
       virtual vector<int> center()=0;

       //virtual vector<tuple<int, Node *> > getVertices() = 0;
       virtual vector<tuple<int,  int> > GetVertices() = 0;
       vector<QGraphicsScene*> getScenes(){return scenes;}
       virtual ~Tree(){}

protected:
    vector<QGraphicsScene*>scenes;
    QGVAbstractTreeSceneFactory*factory;
};

#endif // TREE_H

