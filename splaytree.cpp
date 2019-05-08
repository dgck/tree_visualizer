#include "splaytree.h"
#include "splaytree.h"
#include <stdlib.h>

void SplayTree::zig(Node *x)
{
    Node* p = x->parent;
    if (x == p->left)
    {
        Node* xright = x->right;

        x->parent = NULL;
        x->right = p;

        p->parent = x;
        p->left = xright;
        if (xright != NULL)
            xright->parent = p;
    }
    else
    {
        Node* xleft = x->left;

        x->parent = NULL;
        x->left = p;

        p->parent = x;
        p->right = xleft;
        if (xleft != NULL)
            xleft->parent = p;
    }
}

void SplayTree::zig_zig(Node *x, Node *p, Node *g)
{
    if (x == p->left)
    {
        Node* xright = x->right;
        Node* pright = p->right;

        x->parent = g->parent;
        x->right = p;

        if (x->parent != NULL)
        {
            if (g == x->parent->left)
                x->parent->left = x;
            else
                x->parent->right = x;
        }

        p->parent = x;
        p->left = xright;
        p->right = g;

        g->parent = p;
        g->left = pright;

        if (xright != NULL)
            xright->parent = p;
        if (pright != NULL)
            pright->parent = g;
    }
    else
    {
        Node* xleft = x->left;
        Node* pleft = p->left;

        x->parent = g->parent;
        x->left = p;

        if (x->parent != NULL)
        {
            if (g == x->parent->left)
                x->parent->left = x;
            else
                x->parent->right = x;
        }

        p->parent = x;
        p->left = g;
        p->right = xleft;

        g->parent = p;
        g->right = pleft;

        if (xleft != NULL)
            xleft->parent = p;
        if (pleft != NULL)
            pleft->parent = g;
    }
}

void SplayTree::zig_zag(Node *x, Node *p, Node *g)
{
    if (x == p->right)
    {
        Node* xleft = x->left;
        Node* xright = x->right;

        x->parent = g->parent;
        x->left = p;
        x->right = g;

        if (x->parent != NULL)
        {
            if (g == x->parent->left)
                x->parent->left = x;
            else
                x->parent->right = x;
        }

        p->parent = x;
        g->parent = x;
        p->right = xleft;
        g->left = xright;

        if (xleft != NULL)
            xleft->parent = p;
        if (xright != NULL)
            xright->parent = g;
    }
    else
    {
        Node* xleft = x->left;
        Node* xright = x->right;

        x->parent = g->parent;
        x->left = g;
        x->right = p;

        if (x->parent != NULL)
        {
            if (g == x->parent->left)
                x->parent->left = x;
            else
                x->parent->right = x;
        }

        p->parent = x;
        g->parent = x;
        p->left = xright;
        g->right = xleft;

        if (xleft != NULL)
            xleft->parent = g;
        if (xright != NULL)
            xright->parent = p;
    }
}

Node *SplayTree::findMax(Node *x)
{
    if (!x) return NULL;
    Node* p = x;
    while (p->right != NULL)
        p = p->right;
    return p;
}

void SplayTree::splay(Node *x)
{
    while (x->parent != NULL)
    {
        Node* p = x->parent;
        Node* g = p->parent;
        if (g == NULL)
            zig(x);
        else if (((g->left == p) && (p->left == x)) || ((g->right == p) && (p->right == x)))
            zig_zig(x, p, g);
        else
            zig_zag(x, p, g);
    }
    root = x;
}

void SplayTree::recursive_print(Node *start)
{
    if (start)
    {
        recursive_print(start->left);
        cout << start->key << endl;
        recursive_print(start->right);
    }
}

void SplayTree::recursive_inorder(Node *start)
{
    if (start)
    {
        cout << "Key: " << start->key << "\tParent: ";
        if (start->parent)
            cout << start->parent->key;
        else
            cout << "ROOT";
        cout << endl;

        recursive_inorder(start->left);
        recursive_inorder(start->right);
    }
}

void SplayTree::WriteToGV(ofstream &fout, Node *p)
{
    if (p != NULL)
    {
        fout << '"' << p->key << "\";";
        if (p->left != NULL) fout << '"' << p->key << "\" -> \"" << p->left->key << "\";\n";
        if (p->right != NULL) fout << '"' << p->key << "\" -> \"" << p->right->key << "\";\n";
    }

    if (p->left != NULL)
        WriteToGV(fout, p->left);

    if (p->right != NULL)
        WriteToGV(fout, p->right);

}

void SplayTree::getElementsRecursion(Node *x, vector<int> &elements)
{
    if (x)
    {
        getElementsRecursion(x->left, elements);
        elements.push_back(x->key);
        getElementsRecursion(x->right, elements);
    }
}

void SplayTree::show()
{
    recursive_print(root);
}

void SplayTree::show_inorder()
{
    recursive_inorder(root);
}

void SplayTree::merge(SplayTree *t)
{
    if (root)
        splay(findMax(root));
    else
    {
        root = t->root;
        return;
    }
    root->right = t->root;
    t->root->parent = root;
}

SplayTree *SplayTree::split(Node *x)
{
    splay(x);
    SplayTree *t = new SplayTree();
    t->root = x->left;
    x->left = NULL;
    return t;
}

void SplayTree::insert(int data)
{
    Node* n = new Node(data);

    Node *tempR = root, *temp = NULL;

    while (tempR != NULL)
    {
        temp = tempR;

        if (n->key < tempR->key)
            tempR = tempR->left;
        else
            tempR = tempR->right;
    }

    n->parent = temp;

    if (temp == NULL)
        root = n;
    else if (n->key < temp->key)
        temp->left = n;
    else
        temp->right = n;

    splay(n);
}

void SplayTree::FWrite(string fileName)
{
    ofstream fout(fileName);
    fout << "digraph {\n";
    WriteToGV(fout, root);
    fout << "}";
    fout.close();
}

Node *SplayTree::search(int data)
{
    Node* n = new Node(data);
    Node* p = root;

    while (p && (n->key != p->key))
    {
        if (n->key < p->key)
            p = p->left;
        else
            p = p->right;
    }
    if (p && (p->key == n->key))
    {
        splay(p);
        return p;
    }
    return NULL;
}

void SplayTree::del(int data)
{
    Node* deleted = search(data);
    if (!deleted) return;

    splay(deleted);
    SplayTree t;
    t.root = deleted->right;
    root = deleted->left;
    merge(&t);
}

vector<int> SplayTree::getElements()
{
    vector<int> elements;
    getElementsRecursion(root, elements);
    return elements;
}

void SplayTree::getVerticesRecursion(Node *x, vector<tuple<int, Node *> > &vertices)
{
    if (x)
    {
        getVerticesRecursion(x->left, vertices);
        vertices.push_back(make_tuple(0, x));
        getVerticesRecursion(x->right, vertices);
    }
}

vector<tuple<int, Node *> > SplayTree::getVertices()
{
    vector<tuple<int, Node*>> v;
    getVerticesRecursion(root, v);
    for (int i = 0; i < v.size(); ++i)
        get<0>(v[i]) = i;
    return v;
}

vector<vector<tuple<int, int> > > SplayTree::convertToGraph()
{
    vector<vector<tuple<int, int>>> adjacencyLists;
    vector<tuple<int, Node*>> vertices = getVertices();
    for (int i = 0; i < vertices.size(); ++i)
    {
        vector<tuple<int, int>> curList;
        curList.push_back(make_tuple(i, (get<1>(vertices[i]))->key));

        int k;

        if (get<1>(vertices[i])->left)
        {
            for (int j = 0; j < vertices.size(); ++j)
            {
                if (get<1>(vertices[i])->left == get<1>(vertices[j]))
                {
                    k = j;
                    break;
                }
            }

            curList.push_back(make_tuple(k, (get<1>(vertices[k]))->key));
        }

        if (get<1>(vertices[i])->right)
        {
            for (int j = 0; j < vertices.size(); ++j)
            {
                if (get<1>(vertices[i])->right == get<1>(vertices[j]))
                {
                    k = j;
                    break;
                }
            }

            curList.push_back(make_tuple(k, (get<1>(vertices[k]))->key));
        }

        if (get<1>(vertices[i])->parent)
        {
            for (int j = 0; j < vertices.size(); ++j)
            {
                if (get<1>(vertices[i])->parent == get<1>(vertices[j]))
                {
                    k = j;
                    break;
                }
            }

            curList.push_back(make_tuple(k, (get<1>(vertices[k]))->key));
        }

        adjacencyLists.push_back(curList);
    }
    return adjacencyLists;
}
