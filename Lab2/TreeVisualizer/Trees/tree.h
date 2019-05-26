#ifndef TREE_H
#define TREE_H

#include <vector>
#include <string>
#include <algorithm>
#include <QGraphicsScene>

using namespace std;

class QGVAbstractTreeSceneFactory;

/*!
 * The (tree) Node struct
 * contains data relevant specially for RB-trees, OBS-trees and
 * the key
 * contains appropriate constuctors
 */
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

/*!
 * The Tree class
 * abstract Tree interface
 * declares all general operations with trees
 */
class Tree
{
public:

       virtual void insert(int) = 0;
       virtual void deleteNode(int) = 0;
        /*!
        * \brief getElements
        * \return sorted vector of all the keys contained
        */
       virtual vector<int> getElements()=0;

        /*!
        * \brief merge
        * merges the parameter-tree with the current tree (this),
        * making the parameter-tree a part of the current tree with the new root
        */
       virtual void merge(Tree*) = 0;
       virtual Tree* split(int) = 0;

        /*!
        * \brief intersection
        * searches for an intersection between the current tree elements
        * and the parameter tree elements
        * if the intersection is empty, returns nullptr
        * \return common elements tree
        */
       virtual Tree* intersection(Tree*) = 0;
        /*!
        * \brief intersection
        * \param v1 first elements vector
        * \param v2 second elements vector
        * \return common elements vector
        */
       virtual vector<int> intersection(vector<int> v1, vector<int> v2) = 0;
        /*!
        * \brief inclusion
        * a set operation; compares elements, not structured trees
        * \return tuple, the first item defines whether the inclusion take place somehow,
        * the second item defines the type of the inclusion (if it takes place)
        */
       virtual tuple<bool, int> inclusion(Tree*) = 0;

        /*!
        * \brief dfs
        * trivial depth-first search algorithm
        */
       virtual void dfs() = 0;
        /*!
        * \brief bfs
        * modified for searching all paths in trees breadth-first search algorithm
        * \return all the paths from the given vertex to the rest of vertexes
        */
       virtual vector<vector<int>> bfs(int)=0;
        /*!
        * \brief diameter
        * \return vetcor of elements of any tree diameter
        */
       virtual vector<int> diameter()=0;
        /*!
        * \brief center
        * \return a group (vector) of vertices that are the center of the tree (one or two vertices always)
        */
       virtual vector<int> center()=0;

       //virtual vector<tuple<int, Node *> > getVertices() = 0;
        /*!
        * \brief GetVertices
        * \return all the contained keys (sorted) with their numbers
        */
       virtual vector<tuple<int,  int> > GetVertices() = 0;
       vector<QGraphicsScene*> getScenes(){return scenes;}
       virtual ~Tree(){}

protected:
    vector<QGraphicsScene*>scenes;
    QGVAbstractTreeSceneFactory*factory;
};

#endif // TREE_H

