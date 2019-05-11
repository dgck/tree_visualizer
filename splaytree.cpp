#include "splaytree.h"

void SplayTree::zig(Node *x)
{
    Node* p = x->father;
    if (x == p->left)
    {
        Node* xright = x->right;

        x->father = nullptr;
        x->right = p;

        p->father = x;
        p->left = xright;
        if (xright != nullptr)
            xright->father = p;
    }
    else
    {
        Node* xleft = x->left;

        x->father = nullptr;
        x->left = p;

        p->father = x;
        p->right = xleft;
        if (xleft != nullptr)
            xleft->father = p;
    }
}

void SplayTree::zig_zig(Node *x, Node *p, Node *g)
{
    if (x == p->left)
    {
        Node* xright = x->right;
        Node* pright = p->right;

        x->father = g->father;
        x->right = p;

        if (x->father != nullptr)
        {
            if (g == x->father->left)
                x->father->left = x;
            else
                x->father->right = x;
        }

        p->father = x;
        p->left = xright;
        p->right = g;

        g->father = p;
        g->left = pright;

        if (xright != nullptr)
            xright->father = p;
        if (pright != nullptr)
            pright->father = g;
    }
    else
    {
        Node* xleft = x->left;
        Node* pleft = p->left;

        x->father = g->father;
        x->left = p;

        if (x->father != nullptr)
        {
            if (g == x->father->left)
                x->father->left = x;
            else
                x->father->right = x;
        }

        p->father = x;
        p->left = g;
        p->right = xleft;

        g->father = p;
        g->right = pleft;

        if (xleft != nullptr)
            xleft->father = p;
        if (pleft != nullptr)
            pleft->father = g;
    }
}

void SplayTree::zig_zag(Node *x, Node *p, Node *g)
{
    if (x == p->right)
    {
        Node* xleft = x->left;
        Node* xright = x->right;

        x->father = g->father;
        x->left = p;
        x->right = g;

        if (x->father != nullptr)
        {
            if (g == x->father->left)
                x->father->left = x;
            else
                x->father->right = x;
        }

        p->father = x;
        g->father = x;
        p->right = xleft;
        g->left = xright;

        if (xleft != nullptr)
            xleft->father = p;
        if (xright != nullptr)
            xright->father = g;
    }
    else
    {
        Node* xleft = x->left;
        Node* xright = x->right;

        x->father = g->father;
        x->left = g;
        x->right = p;

        if (x->father != nullptr)
        {
            if (g == x->father->left)
                x->father->left = x;
            else
                x->father->right = x;
        }

        p->father = x;
        g->father = x;
        p->left = xright;
        g->right = xleft;

        if (xleft != nullptr)
            xleft->father = g;
        if (xright != nullptr)
            xright->father = p;
    }
}

Node *SplayTree::findMax(Node *x)
{
    if (!x) return nullptr;
    Node* p = x;
    while (p->right != nullptr)
        p = p->right;
    return p;
}

void SplayTree::splay(Node *x)
{
    while (x->father != nullptr)
    {
        Node* p = x->father;
        Node* g = p->father;
        if (g == nullptr)
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
        if (start->father)
            cout << start->father->key;
        else
            cout << "ROOT";
        cout << endl;

        recursive_inorder(start->left);
        recursive_inorder(start->right);
    }
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

void SplayTree::merge(Tree *t)
{
    SplayTree* t1 = dynamic_cast<SplayTree*>(t);
    merge(t1);
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
    t->root->father = root;
}

Tree* SplayTree::split(int y)
{
    Node* x = new Node(y);
    splay(x);
    SplayTree *t = new SplayTree();
    t->root = x->left;
    x->left = nullptr;
    Tree* t1 = dynamic_cast<Tree*>(t);
    return t1;
}

void SplayTree::insert(int data)
{
    Node* n = new Node(data);

    Node *tempR = root, *temp = nullptr;

    while (tempR != nullptr)
    {
        temp = tempR;

        if (n->key < tempR->key)
            tempR = tempR->left;
        else
            tempR = tempR->right;
    }

    n->father = temp;

    if (temp == nullptr)
        root = n;
    else if (n->key < temp->key)
        temp->left = n;
    else
        temp->right = n;

    splay(n);
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
    return nullptr;
}

void SplayTree::deleteNode(int data)
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

SplayTree::SplayTree()
{
    root = nullptr;
}

vector<tuple<int, Node *> > SplayTree::getVertices()
{
    vector<tuple<int, Node*>> v;
    getVerticesRecursion(root, v);
    for (int i = 0; i < v.size(); ++i)
        get<0>(v[i]) = i;
    return v;
}

vector<int> SplayTree::intersection(Tree *)
{
    return vector<int>(0);
}

vector<int> SplayTree::intersection(vector<int> v1, vector<int> v2)
{
    return vector<int>(0);
}

tuple<bool, int> SplayTree::inclusion()
{
    return make_tuple(false, 0);
}

void SplayTree::dfs()
{

}

void SplayTree::dfs(int v, vector<vector<tuple<int, int> > > g, vector<bool> &used, vector<int> &path)
{

}

void SplayTree::dfs(int v, vector<vector<tuple<int, string> > > g, vector<bool> &used, vector<int> &path)
{

}

vector<vector<tuple<int, int> > > SplayTree::bfs(tuple<int, int>)
{
    vector<vector<tuple<int, int> > > v;
    return v;
}

vector<vector<tuple<int, string> > > SplayTree::bfs(tuple<int, string>)
{
    vector<vector<tuple<int, string> > > v;
    return v;
}

vector<vector<tuple<int, int *> > > SplayTree::bfs(tuple<int, int *>)
{
    vector<vector<tuple<int, int *> > > v;
    return v;
}

void SplayTree::diameter()
{

}

void SplayTree::center()
{

}

/*vector<vector<tuple<int, int> > > SplayTree::convertToGraph()
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
*/
