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

vector<vector<tuple<int, Node*>>> BFS(vector<vector<tuple<int, Node*>>> graph, tuple<int, Node*> vertex, int graphSize)
{
        vector<vector<tuple<int, Node*>>> routes(graphSize);

        queue<int> q;
        q.push(get<0>(vertex));
        vector<bool> visited(graphSize);
        visited[get<0>(vertex)] = true;
        vector<int> d(graphSize), p(graphSize);
        p[get<0>(vertex)] = -1;


        while (!q.empty())
        {
                int v = q.front();
                q.pop();

                for (int i = 0; i < graph[v].size(); ++i)
                {
                        int to = get<0>(graph[v][i]);
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

                int to = get<0>(graph[j][0]);
                vector<int> path;
                for (int v = to; v != -1; v = p[v])
                        path.push_back(v);
                reverse(path.begin(), path.end());
                cout << "Path to " << j << endl;
                for (size_t i = 0; i < path.size(); ++i)
                        cout << path[i] << " ";
                cout << endl;

                for (size_t i = 0; i < path.size(); ++i)
                        for (int k = 0; k < graphSize; ++k)
                        {
                                if (path[i] == get<0>(graph[k][0]))
                                {
                                        tuple<int, Node*> t = make_tuple(path[i], get<1>(graph[k][0]));
                                        // восстанавливаем путь к вершине под номером j
                                        routes[j].push_back(t);
                                }
                        }
        }


        return routes;
}

vector<tuple<int, Node*>> diameter(SplayTree t)
{
        vector<vector<tuple<int, Node*>>> graph = t.convertToGraph();
        vector<tuple<int, Node*>> path;
        int n = t.getElements().size();

        vector<vector<tuple<int, Node*>>> routesV = BFS(graph, graph[0][0], n);

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
        vector<vector<tuple<int, Node*>>> routesU = BFS(graph, graph[maxIndex][0], n);

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

vector<tuple<int, Node*>> pathBetween(vector<vector<tuple<int, Node*>>> graph, tuple<int, Node*> v, tuple<int, Node*> u)
{
        vector<vector<tuple<int, Node*>>> pathesToV = BFS(graph, v, graph.size());
        return pathesToV[get<0>(u)];
}

#endif // SPLAYTREE_H
