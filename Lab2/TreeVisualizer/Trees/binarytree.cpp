#include "binarytree.h"
#include <tuple>
#include <queue>
#include "QGVGraphRelated/qgvbinarytreescenefactory.h"
#include "QGVGraphRelated/qgvredblacktreescenefactory.h"
#include "Trees/rbtree.h"

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



void BinaryTree::insertFix(Node *)
{
}

BinaryTree::BinaryTree()
{
    factory = new QGVBinaryTreeSceneFactory(this);
}

void BinaryTree::insert(int data)
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

        n->father = temp;

        if (temp == NULL)
            root = n;
        else if (n->key < temp->key)
            temp->left = n;
        else
            temp->right = n;

        scenes.push_back(factory->get_scene());
        if (dynamic_cast <RBTree*>(this))
        {
            factory = new QGVRebBlackSceneFactory (this);
        }
        else factory = new QGVBinaryTreeSceneFactory(this);
        insertFix(n);

}

Node* BinaryTree::successor(Node *p)
{
    Node *y = nullptr;
    if (p->left != nullptr)
    {
        y = p->left;
        while (y->right != nullptr)
            y = y->right;
    }
    else
    {
        y = p->right;
        while (y->left != nullptr)
            y = y->left;
    }
    return y;
}

void BinaryTree::deleteNode(int x)
{
    if (root == nullptr)
    {
        return;
    }
    Node *p;
    p = root;
    Node *y = nullptr;
    Node *q = nullptr;
    int found = 0;
    while (p != nullptr && found == 0)
    {
        if (p->key == x)
            found = 1;
        if (found == 0)
        {
            if (p->key < x)
                p = p->right;
            else
                p = p->left;
        }
    }

    if (found == 0)return;
    else
    {
        if (p->left == nullptr || p->right == nullptr)
            y = p;
        else
            y = successor(p);
        if (y->left != nullptr)
            q = y->left;
        else
        {
            if (y->right != nullptr)
                q = y->right;
            else
                q = nullptr;
        }
        if (q != nullptr)
            q->father = y->father;
        if (y->father == nullptr)
            root = q;
        else
        {
            if (y == y->father->left)
                y->father->left = q;
            else
                y->father->right = q;
        }
        if (y != p)
        {
            p->color = y->color;
            p->key = y->key;
        }
    }

    scenes.push_back(factory->get_scene());
    factory = new QGVBinaryTreeSceneFactory(this);
}

vector<int> BinaryTree::getElements()
{
    vector<int> elements;
    getElementsRecursion(root, elements);
    return elements;
}

void BinaryTree::merge(Tree *)
{

}

Tree *BinaryTree::split(int)
{
    return nullptr;
}

Node *BinaryTree::search(int in)
{
       Node *t;
        t = root;
        while (t != nullptr)
        {
            if (t->key == in)   break;
            if (in > t->key)    t = t->right;
            else if (in < t->key)    t = t->left;
        }
        if (t == nullptr)
            return nullptr;
        else if (t->key == in)
            return t;
        return nullptr;

}

Node *BinaryTree::search(string in)
{
    Node *t;
     t = root;
     while (t != nullptr)
     {
         if (t->data == in)   break;
         if (in > t->data)    t = t->right;
         else if (in < t->data)    t = t->left;
     }
     if (t == nullptr)
         return nullptr;
     else if (t->data == in)
         return t;
     return nullptr;
}

Tree* BinaryTree::intersection(Tree *t2)
{
    vector<int> v1=getElements(), v2=t2->getElements(), inters;
    inters = intersection(v1,v2);
    Tree*t = new BinaryTree;
    for(auto el:inters)
    {
        t->insert(el);
    }
    return t;
}


vector<int> BinaryTree::intersection(vector<int> v1, vector<int> v2)
{
    vector<int> inters;
    for (int i=0;i<v1.size();i++)
        if(find(v2.begin(), v2.end(), v1[i]) != v2.end())
            inters.push_back(v1[i]);
    return inters;
}

tuple<bool, int> BinaryTree::inclusion(Tree* t2)
{
    vector<int> v1=getElements(), v2=t2->getElements(), inters;
    inters = intersection(v1,v2);
    if(v1.size()==v2.size()&& v2.size()==inters.size())
        return make_tuple(true,0); //trees are equal
    if(v1.size()<v2.size()&& v1.size()==inters.size())
        return make_tuple(true,1); //second tree includes first
    if(v1.size()>v2.size()&& v2.size()==inters.size())
        return make_tuple(true,2); //first tree includes second
    return make_tuple(false, 0);
}

void BinaryTree::dfs()
{
    vector<vector<int>> adj = convertToGraph();
    vector<bool> used(adj.size(), false);
    vector<int> path;
    dfs (0, adj, used, path);
}

void BinaryTree::dfs(int v, vector<vector<int>> g, vector<bool> &used, vector<int> &path){
    used[v] = true;
    path.push_back(v);
    for(int i=0; i<g[v].size(); i++){
        if (!used[g[v][i]]) dfs(g[v][i], g, used,path);
    }
}

vector<vector<int>> BinaryTree::bfs(int vertex)
{
        vector<vector<int>> graph = convertToGraph();
        int graphSize = graph.size();
        vector<vector<int>> routes(graphSize);

        queue<int> q;
        q.push(vertex);
        vector<bool> visited(graphSize);
        visited[vertex] = true;
        vector<int> d(graphSize), p(graphSize);
        p[vertex] = -1;


        while (!q.empty())
        {
                int v = q.front();
                q.pop();

                for (int i = 0; i < graph[v].size(); ++i)
                {
                        int to = graph[v][i];
                        if (!visited[to])
                        {
                                visited[to] = true;
                                q.push(to);

                                d[to] = d[v] + 1;
                                p[to] = v;
                        }
                }
        }

        for (int j = 0; j < graphSize; ++j)
        {

                int to = graph[j][0];
                vector<int> path;
                for (int v = to; v != -1; v = p[v])
                        path.push_back(v);
                reverse(path.begin(), path.end());
                //cout << "Path to " << j << endl;
                //for (size_t i = 0; i < path.size(); ++i)
                //        cout << path[i] << " ";
                //cout << endl;

                for (size_t i = 0; i < path.size(); ++i)
                        for (int k = 0; k < graphSize; ++k)
                        {
                                if (path[i] == graph[k][0])
                                {
                                        int t = path[i];
                                        // восстанавливаем путь к вершине под номером j
                                        routes[j].push_back(t);
                                }
                        }
        }


        return routes;
}

vector<int> BinaryTree::diameter()
{
        vector<vector<int>> graph = convertToGraph();
        vector<int> path;
        int n = getElements().size();

        vector<vector<int>> routesV = bfs(graph[0][0]);

        int max = -1;
        int maxIndex = -1;

        for (int i = 0; i < routesV.size(); ++i)
        {
                int cur = routesV[i].size();
                if (cur > max)
                {
                        max = cur;
                        maxIndex = i;
                }
        }

        // нашли вершину u - самую далекую от v; она хранится в graph[maxIndex][0]
        if (maxIndex == -1) return routesV[0];
        vector<vector<int>> routesU = bfs(graph[maxIndex][0]);

        max = maxIndex = -1;

        for (int i = 0; i < routesU.size(); ++i)
        {
                int cur = routesU[i].size();
                if (cur > max)
                {
                        max = cur;
                        maxIndex = i;
                }
        }

        return routesU[maxIndex];
}

vector<int> BinaryTree::center()
{
    vector<int> c;
            vector<int> d = diameter();
            if (d.size() % 2 == 1)
                    c.push_back(d[d.size() / 2]);
            else
            {
                    c.push_back(d[d.size() / 2]);
                    c.push_back(d[d.size() / 2 - 1]);
            }
    return c;
}

vector<vector<int > > BinaryTree::convertToGraph()
{
    vector<vector<int>> adjacencyLists;
    vector<tuple<int, Node*>> vertices = getVertices();
    for (int i = 0; i < vertices.size(); ++i)
    {
        vector<int> curList;
        curList.push_back(i);

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

            curList.push_back(k);
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

            curList.push_back(k);
        }

        if (get<1>(vertices[i])->father)
        {
            for (int j = 0; j < vertices.size(); ++j)
            {
                if (get<1>(vertices[i])->father == get<1>(vertices[j]))
                {
                    k = j;
                    break;
                }
            }

            curList.push_back(k);
        }

        adjacencyLists.push_back(curList);
    }
    return adjacencyLists;
}

vector<tuple<int, Node*>> BinaryTree::getVertices()
{
    vector<tuple<int, Node*>> v;
    getVerticesRecursion(root, v);
    for (int i = 0; i < v.size(); ++i)
        get<0>(v[i]) = i;
    return v;
}

vector<tuple<int, int> > BinaryTree::GetVertices()
{
    vector<tuple<int, int>> v;
    getVerticesRecursion(root, v);
    for (int i = 0; i < v.size(); ++i)
        get<0>(v[i]) = i;
    return v;
}

void BinaryTree::getVerticesRecursion(Node *x, vector<tuple<int, Node *> > &vertices)
{
    if (x)
    {
        getVerticesRecursion(x->left, vertices);
        vertices.push_back(make_tuple(0, x));
        getVerticesRecursion(x->right, vertices);
    }
}

void BinaryTree::getVerticesRecursion(Node *x, vector<tuple<int, int> > &vertices)
{
    if (x)
    {
        getVerticesRecursion(x->left, vertices);
        vertices.push_back(make_tuple(0, x->key));
        getVerticesRecursion(x->right, vertices);
    }
}

void BinaryTree::getElementsRecursion(Node *x, vector<int> &elements)
{
    if (x)
    {
        getElementsRecursion(x->left, elements);
        elements.push_back(x->key);
        getElementsRecursion(x->right, elements);
    }
}

void BinaryTree::inorderBST(Node *ptr) {
    if (ptr == nullptr)
        return;

    inorderBST(ptr->left);
    cout << ptr->key << " " << ptr->color << endl;
    inorderBST(ptr->right);
}

void BinaryTree::inorder() {
    inorderBST(root);
}

void BinaryTree::preorderBST(Node *ptr) {
    if (ptr == nullptr)
        return;

    cout << ptr->key << " " << ptr->color << endl;
    preorderBST(ptr->left);
    preorderBST(ptr->right);
}

void BinaryTree::preorder() {
    preorderBST(root);
    cout << "-------" << endl;
}

void BinaryTree::postorderBST(Node *ptr) {
    if (ptr == nullptr)
        return;
    postorderBST(ptr->left);
    postorderBST(ptr->right);
    cout << ptr->key << " " << ptr->color << endl;
}

void BinaryTree::postorder() {
    postorderBST(root);
    cout << "-------" << endl;
}


