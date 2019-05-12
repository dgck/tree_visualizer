#include "obst.h"
#include "obst.h"
#include <fstream>
#include <stdlib.h>
#include <cstdlib>
#include <vector>
#include <string>

using namespace std;

void Sort(vector<string> &a)
{
  string temp;
  int n = a.size();
  for (int i = 0; i < n; ++i)
    for (int j = n - 1; j > i; --j)
      if (a[j - 1] > a[j])
      {
        temp = a[j - 1];
        a[j - 1] = a[j];
        a[j] = temp;
      }
}

string readText()
{
 string text;
          text="In computer science, an optimal binary search tree (Optimal BST), sometimes called a weight-balanced binary tree,";
          text+="is a binary search tree which provides the smallest possible search time (or expected search time) for a given sequence of accesses";
          text+="(or access probabilities). Optimal BSTs are generally divided into two types: static and dynamic.\n";
          text+="In the static optimality problem, the tree cannot be modified after it has been constructed.";
          text+="In this case, there exists some particular layout of the nodes of the tree which provides the smallest expected search ";
          text+="time for the given access probabilities. Various algorithms exist to construct or approximate the statically optimal";
          text+="tree given the information on the access probabilities of the elements.\n";
          text+="In the dynamic optimality problem, the tree can be modified at any time, typically by permitting tree rotations.";
          text+="The tree is considered to have a cursor starting at the root which it can move or use to perform modifications.";
          text+="In this case, there exists some minimal-cost sequence of these operations which causes the cursor to visit every node";
          text+="in the target access sequence in order. The splay tree is conjectured to have a constant competitive ratio compared to the";
          text+="dynamically optimal tree in all cases, though this has not yet been proven.\n";
  return text;
}

void removeChars(string &text)
{
  string newText = "";
  for (unsigned int i = 0; i < text.length(); ++i)
    if (!(text[i] == ')' || text[i] == '(' || text[i] == '.' || text[i] == ',' || text[i] == ':'))
      newText += text[i];
  text = newText;
}

void OBST::subTreeShowIn(Node *start)
{
    if (start)
    {
        subTreeShowIn(start->left);
        cout << start->key << endl;
        subTreeShowIn(start->right);
    }
}

void OBST::subTreeShowPre(Node *start)
{
    if (start)
    {
        cout << start->key << endl;
        subTreeShowPre(start->left);
        subTreeShowPre(start->right);
    }
}

void OBST::generateTree(int **Roots, vector<string> input, vector<int> costs)
{
    int n = input.size();

    generateSubTree(Roots, input, costs, root, 1, n);

}

void OBST::generateSubTree(int **Roots, vector<string> input, vector<int> costs, Node *&r, int first, int last)
{
    int k = Roots[first][last];
    r = new Node(input[k - 1], costs[k]);
    if (k - 1 >= first)
        generateSubTree(Roots, input, costs, r->left, first, k - 1);
    if (last >= k + 1)
        generateSubTree(Roots, input, costs, r->right, k + 1, last);

}

void OBST::WriteToGV(Node *p)
{
    ofstream fout("test.gv", ios::app);
    if (p != NULL)
    {
        fout << "\"" << p->data << " : " << p->frequency << "\";";
        if (p->left != NULL) fout << '"' << p->data << " : " << p->frequency << "\" -> \"" << p->left->data << " : " << p->left->frequency << "\";\n";
        if (p->right != NULL) fout << '"' << p->data << " : " << p->frequency << "\" -> \"" << p->right->data << " : " << p->right->frequency << "\";\n";
    }
    fout.close();
    if (p->left != NULL)
        WriteToGV( p->left);

    if (p->right != NULL)
        WriteToGV( p->right);

}

void OBST::Preparation(vector<string> &uwords, vector<int> &frequencies)
{
    string text = readText();
    removeChars(text);

    vector<string> words;

    int l = 0;
    for (int i = 0; i < text.length(); ++i)
    {
      if (text[i] == ' ' || text[i] == '\n' || text[i] == '\t')
      {
        if (text.substr(l, i - l) == " ")
          ++i;
        else
        {
          words.push_back(text.substr(l, i - l));
          l = i + 1;
        }
      }
    }
    Sort(words);
     vector<string> temp;

     for (int i = 0; i < words.size(); ++i)
       if (words[i] != " ")
         temp.push_back(words[i]);
     words = temp;
     for (int i = 0; i < temp.size(); ++i)
       cout << temp[i] << " x ";

     uwords.push_back(words[0]);
     frequencies.push_back(0);   frequencies.push_back(0);
     int cur = 1;

     for (int i = 0; i < words.size(); i++)
       if (words[i] == uwords.back())
         frequencies[cur]++;
       else{
         uwords.push_back(words[i]);
         frequencies.push_back(0);
         cur++;
         i--;
       }

     for (int i = 1; i < frequencies.size(); ++i)
       cout <<uwords[i-1] <<'-'<< frequencies[i] << endl;

}

OBST::OBST()
{
    vector<string> uwords;
    vector<int> frequencies;
    Preparation(uwords, frequencies);
       this->root=OBST(uwords,frequencies).root;
       FWrite("test.gv");
}

OBST::OBST(vector<string> input, vector<int> p)
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

void OBST::FWrite(string fileName)
{
    ofstream fout(fileName);
    fout << "digraph {\n";
    fout.close();
    WriteToGV(root);
    ofstream fou(fileName, ios::app);
    fou << "}";
    fou.close();
}

void OBST::Inorder()
{
    subTreeShowIn(root);
}

void OBST::Preorder()
{
    subTreeShowPre(root);
}


