#include "obst.h"
#include <fstream>
#include <stdlib.h>
#include <cstdlib>
#include <vector>
#include <string>
using namespace std;


template<typename T>
void OBST<T>::subTreeShowIn(Node<T> *start)
{
    if (start)
    {
        subTreeShowIn(start->left);
        cout << start->key << endl;
        subTreeShowIn(start->right);
    }
}

template<typename T>
void OBST<T>::subTreeShowPre(Node<T> *start)
{
    if (start)
    {
        cout << start->key << endl;
        subTreeShowPre(start->left);
        subTreeShowPre(start->right);
    }
}

template<typename T>
void OBST<T>::generateTree(int **Roots, vector<T> input, vector<int> costs)
{
    int n = input.size();

    generateSubTree(Roots, input, costs, root, 1, n);

}

template<typename T>
void OBST<T>::generateSubTree(int **Roots, vector<T> input, vector<int> costs, Node<T> *&r, int first, int last)
{
    int k = Roots[first][last];
    r = new Node<T>(input[k - 1], costs[k]);
    if (k - 1 >= first)
        generateSubTree(Roots, input, costs, r->left, first, k - 1);
    if (last >= k + 1)
        generateSubTree(Roots, input, costs, r->right, k + 1, last);

}

template<typename T>
void OBST<T>::WriteToGV(Node<T> *p)
{
    ofstream fout("test.gv", ios::app);
    if (p != NULL)
    {
        fout << "\"" << p->key << " : " << p->frequency << "\";";
        if (p->left != NULL) fout << '"' << p->key << " : " << p->frequency << "\" -> \"" << p->left->key << " : " << p->left->frequency << "\";\n";
        if (p->right != NULL) fout << '"' << p->key << " : " << p->frequency << "\" -> \"" << p->right->key << " : " << p->right->frequency << "\";\n";
    }
    fout.close();
    if (p->left != NULL)
        WriteToGV( p->left);

    if (p->right != NULL)
        WriteToGV( p->right);

}

template<typename T>
OBST<T>::OBST(vector<T> input, vector<int> p)
{
    int n = input.size();
    int** Costs = new int*[n + 2];
    int** Roots = new int*[n + 2];
    for (int i = 0; i < n + 2; ++i)
    {
        Costs[i] = new int[n + 2];
        Roots[i] = new int[n + 2];
    }

    for (int i = 1; i <= n; ++i)
    {
        Costs[i][i - 1] = 0;
        Costs[i][i] = p[i];
        Roots[i][i] = i;
    }

    Costs[n + 1][n] = 0;
    for (int d = 1; d <= n - 1; ++d)
    {
        for (int i = 1; i <= n - d; ++i)
        {
            int j = i + d;
            int minval = INT_MAX;
            int kmin;
            for (int k = i; k <= j; ++k)
                if (Costs[i][k - 1] + Costs[k + 1][j] < minval)
                {
                    minval = Costs[i][k - 1] + Costs[k + 1][j];
                    kmin = k;
                }
            Roots[i][j] = kmin;
            int sum = p[i];
            for (int s = i + 1; s <= j; ++s)
                sum += p[s];
            Costs[i][j] = minval + sum;
        }
    }

    //ShowMatrixes(Costs, Roots, n);

    generateTree(Roots, input, p);

    cout << "Average search cost multiplied by 10: " << Costs[1][n] << endl;

}

template<typename T>
void OBST<T>::FWrite(string fileName)
{
    ofstream fout(fileName);
    fout << "digraph {\n";
    fout.close();
    WriteToGV(root);
    ofstream fou(fileName, ios::app);
    fou << "}";
    fou.close();
}

template<typename T>
void OBST<T>::Inorder()
{
    subTreeShowIn(root);
}

template<typename T>
void OBST<T>::Preorder()
{
    subTreeShowPre(root);
}
