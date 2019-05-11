#include "rbtree.h"
#include <string>
#include <iostream>
#include <iomanip>
#include <utility>
#include <cstdio>
#include <fstream>
#include <vector>
#include <tuple>
using namespace std;



RBTree::RBTree(const RBTree &tree)
{

    if (tree.root == nullptr) root = nullptr;
    else
    {
        root = new Node(tree.root->key);
        root->color = tree.root->color;

        root->left = RBTree(RBTree(tree.root->left)).root;
        root->right = RBTree(RBTree(tree.root->right)).root;
    }

}

RBTree::RBTree(Node * in)
{
    if (in == nullptr) root = nullptr;
    else
    root = in;
}


void RBTree::insert(int input) {
    Node *p, *q;
    Node *create = new Node(input);
    p = root;
    q = nullptr;
    if (root == nullptr)
    {
        root = create;
        create->father = nullptr;
    }
    else
    {
        while (p != nullptr)
        {
            q = p;
            if (p->key > create->key) p = p->left;
            else if (p->key < create->key) p = p->right;
            else return;
        }
        create->father = q;
        if (q->key < create->key) q->right = create;
        else if (q->key > create->key)q->left = create;
        else return;
    }
    insertFix(create);


}


void RBTree::insertFix(Node *create)
{
    Node *x = create;
    while (x != root && x->father->color == red)
    {
        if (x->father == x->father->father->left) //если отец - левый сын
        {
            Node *uncle = x->father->father->right;
            if ((uncle != nullptr) && (uncle->color == red)) //если дядя - красный
            {
                x->father->color = black;
                uncle->color = black;
                x->father->father->color = red;
                x = x->father->father;
            }
            else
            {
                if (x->father->right == x)  //если х - правый сын
                {
                    x = x->father;
                    rotateLeft(x);
                }
                x->father->color = black;
                x->father->father->color = red;
                rotateRight(x->father->father);
            }
        }
        else  //если отец - правый сын
        {
            Node *uncle = x->father->father->left;
            if ((uncle != nullptr) && (uncle->color == red)) // если дядя - красный
            {
                x->father->color = black;
                uncle->color = black;
                x->father->father->color = red;
                x = x->father->father;
            }
            else  //если дядя - черный
            {
                if (x->father->left == x)
                {
                    x = x->father;
                    rotateRight(x);
                }
                x->father->color = black;
                x->father->father->color = red;
                rotateLeft(x->father->father);
            }
        }
    }
    root->color = black;
}


void RBTree::rotateRight(Node* in)
{
    if (in->left == nullptr)
        return;
    else
    {
        Node *y = in;
        Node *x = y->left;
        Node *b = x->right;
        Node *f = y->father;
        if (f == nullptr)
        {
            x->father = nullptr;
            root = x;
        }
        else
        {
            x->father = f;
            if (f->left == y)
                f->left = x;
            if (f->right == y)
                f->right = x;
        }
        x->right = y;
        y->father = x;
        y->left = b;
        if (b != nullptr)
            b->father = y;
    }
}


void RBTree::rotateLeft(Node* x)
{
    if (x->right == nullptr)
        return;
    else
    {
        Node *y = x->right;
        Node *b = y->left;
        Node *f = x->father;
        if (f == nullptr)
        {
            y->father = nullptr;
            root = y;
        }
        else
        {
            y->father = f;
            if (f->left == x)
                f->left = y;
            if (f->right == x)
                f->right = y;
        }
        y->left = x;
        x->father = y;
        x->right = b;
        if (b != nullptr)
            b->father = x;
    }
}



Node* RBTree::search(int in)
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


int RBTree::blackHeight() {
    Node *p;
    p = root;
    int num = 0;
    while (p != nullptr) {
        if (p->color == black) num++;
        p = p->left;
    }
    return num;
}

int RBTree::blackHeight(Node* node) {
    Node *p;
    p = node;
    int num = 0;
    while (p != nullptr) {
        if (p->color == black) num++;
        p = p->left;
    }
    return num;
}


void ShowMy(Node* node)
{
    if (node->left != nullptr) ShowMy(node->left);
    if (node != nullptr) cout << node->key << " " << node->color << '\n';
    if (node->right != nullptr) ShowMy(node->right);
}

void RBTree::show()
{
    if (root != nullptr) {
        cout << "\n\nRoot: " << root->key << " " << (root->color == black ? "black" : "red") << "\n";
        ShowMy(root);
    }
}


Node* RBTree::successor(Node *p)
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


void RBTree::deleteNode(int x)
{
    if (root == nullptr)
    {
        cout << "\nEmpty Tree.";
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
        cout << "\nDeleted Element: " << p->key;
        cout << "\nColour: ";
        if (p->color == black)
            cout << "Black\n";
        else
            cout << "Red\n";
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
        if (y->color == black)
            deleteFix(q);
        root->color = black;


    }
}

void RBTree::deleteFix(Node *p)
{
    if (p != nullptr)
    {
        Node *s;
        while (p != root && p->color == black)
        {
            if (p->father->left == p)
            {
                s = p->father->right;
                if (s->color == red)    //если брат - красный
                {
                    s->color = black;     //красим брата в черный
                    p->father->color = red;  //отца - в красный
                    rotateLeft(p->father);
                    s = p->father->right;
                }

                if (s->right->color == black && s->left->color == black)  //если оба ребенка брата черные
                {
                    s->color = red;  //красим брата в красный
                    p = p->father;   //и рассматриваем далее отца верншины
                }
                else
                {
                    if (s->right->color == black) //если правый - черный, левый - красный
                    {
                        s->left->color = black;
                        s->color = red;
                        rotateRight(s);
                        s = p->father->right;
                    }
                    s->color = p->father->color;
                    p->father->color = black;
                    s->right->color = black;
                    rotateLeft(p->father);
                    p = root;
                }
            }
            else
            {
                s = p->father->left;
                if (s->color == red)
                {
                    s->color = red;
                    p->father->color = red;
                    rotateRight(p->father);
                    s = p->father->left;
                }
                if (s->left->color == black && s->right->color == black)
                {
                    s->color = red;
                    p = p->father;
                }
                else
                {
                    if (s->left->color == black)
                    {
                        s->right->color = black;
                        s->color = red;
                        rotateLeft(s);
                        s = p->father->left;
                    }
                    s->color = p->father->color;
                    p->father->color = black;
                    s->left->color = black;
                    rotateRight(p->father);
                    p = root;
                }
            }
        }
        p->color = black;
        root->color = black;
    }
    root->color = black;
}


void RBTree::display(string fileName){
    ofstream fout(fileName);
    fout << "digraph {\n";
    writeToGV(fout, root);
    fout << "}";
    fout.close();
}

void RBTree::writeToGV(ofstream &fout, Node* p)
{
    if (p != nullptr) {
        fout << '"' << p->key << "\" [color=" << (p->color == black ? "black];\n" : "red];\n");
        if (p->left != nullptr) fout << '"' << p->key << "\" -> \"" << p->left->key << "\";\n";
        else
            fout << '"' << p->key << "\" -> \"NULL\";\n";

        if (p->right != nullptr) fout << '"' << p->key << "\" -> \"" << p->right->key << "\";\n";
        else
            fout << '"' << p->key << "\" -> \"NULL\";\n";

    }

    if (p->left != nullptr) {
        writeToGV(fout, p->left);
    }
    if (p->right != nullptr) {
        writeToGV(fout, p->right);
    }

}


void RBTree::inorderBST(Node *ptr) {
    if (ptr == nullptr)
        return;

    inorderBST(ptr->left);
    cout << ptr->key << " " << ptr->color << endl;
    inorderBST(ptr->right);
}

void RBTree::inorder() {
    inorderBST(root);
}

void RBTree::preorderBST(Node *ptr) {
    if (ptr == nullptr)
        return;

    cout << ptr->key << " " << ptr->color << endl;
    preorderBST(ptr->left);
    preorderBST(ptr->right);
}

void RBTree::preorder() {
    preorderBST(root);
    cout << "-------" << endl;
}

Node *RBTree::minValueNode(Node *&node) {

    Node *ptr = node;

    while (ptr->left != nullptr)
        ptr = ptr->left;

    return ptr;
}

Node* RBTree::maxValueNode(Node *&node) {
    Node *ptr = node;

    while (ptr->right != nullptr)
        ptr = ptr->right;

    return ptr;
}


void RBTree::join(RBTree rbTree2) {
    if (root == nullptr) { root = rbTree2.root; return; }
    if (rbTree2.root == nullptr) return;
    int temp;
    Node *c, *temp_ptr = nullptr;
    Node *root1 = root;
    Node *root2 = rbTree2.root;
    if (!root1->left && !root1->right) { rbTree2.insert(root1->key); root = rbTree2.root; return; }
    if (!root2->left && !root2->right) { insert(root1->key); return; }
    int initialblackheight1 = blackHeight(root1);
    int initialblackheight2 = blackHeight(root2);
    if (initialblackheight1 > initialblackheight2) {
        c = maxValueNode(root1);
        temp = c->key;
        deleteNode(c->key);
        root1 = root;
    }
    else if (initialblackheight2 > initialblackheight1) {
        c = minValueNode(root2);
        temp = c->key;
        rbTree2.deleteNode(c->key);
        root2 = rbTree2.root;
    }
    else {
        c = minValueNode(root2);
        temp = c->key;
        rbTree2.deleteNode(c->key);
        root2 = rbTree2.root;
        if (initialblackheight1 != blackHeight(root2)) {
            rbTree2.insert(c->key);
            root2 = rbTree2.root;
            c = maxValueNode(root1);
            temp = c->key;
            deleteNode(c->key);
            root1 = root;
        }
    }
    c->color = red;
    int finalblackheight1 = blackHeight(root1);
    int finalblackheight2 = blackHeight(root2);
    if (finalblackheight1 == finalblackheight2) {
        c->left = root1;
        root1->father = c;
        c->right = root2;
        root2->father = c;
        c->color = black;
        c->key = temp;
        root = c;
    }
    else if (finalblackheight2 > finalblackheight1) {
        Node *ptr = root2;
        while (finalblackheight1 != blackHeight(ptr)) {
            temp_ptr = ptr;
            ptr = ptr->left;
        }
        Node *ptr_parent;
        if (ptr == nullptr)
            ptr_parent = temp_ptr;
        else
            ptr_parent = ptr->father;
        c->left = root1;
        if (root1 != nullptr)
            root1->father = c;
        c->right = ptr;
        if (ptr != nullptr)
            ptr->father = c;
        ptr_parent->left = c;
        c->father = ptr_parent;
        if (ptr_parent->color == red) {
            insertFix(c);
        }
        else if (ptr->color == red) {
            insertFix(ptr);
        }
        c->key = temp;
        root = root2;
    }
    else {
        Node *ptr = root1;
        while (finalblackheight2 != blackHeight(ptr)) {
            ptr = ptr->right;
        }
        Node *ptr_parent = ptr->father;
        c->right = root2;
        root2->father = c;
        c->left = ptr;
        ptr->father = c;
        ptr_parent->right = c;
        c->father = ptr_parent;
        if (ptr_parent->color == red) {
            insertFix(c);
        }
        else if (ptr->color == red) {
            insertFix(ptr);
        }
        c->key = temp;
        root = root1;
    }
    return;
}

RBTree* RBTree::splitR(int x) {
    RBTree* t1, *t2;
    Node* k = root;

    while (k != nullptr) {
        if (x == k->key) {
            RBTree tempR(k->right); RBTree tR(tempR); tR.root->father = nullptr;
            t2->join(tR);
            RBTree tempL(k->left); RBTree tL(tempL);
            t1->join(tL);
            break;
        }
        if (x < k->key) {

            RBTree temp(k); RBTree t(temp); t.root->left = nullptr; t.root->father = nullptr;
            t2->join(t);
            if(k->left) k = k->left; else break;
        }
        else{
            RBTree temp(k); RBTree t(temp); t.root->right = nullptr;
            t1->join(t);
            if(k->right) k = k->right; else break;
        }
    }
    if(k!=nullptr && k->key != x) k->key < x ? t1->insert(k->key) : t2->insert(k->key);
    root = t1->root;
    if(root)root->father = nullptr;
    if(t2->root)t2->root->father = nullptr;

    return t2;
}

void RBTree::merge(RBTree t) {

    if (root == nullptr) {
        root = t.root;
        return;
    }
    if (t.root == nullptr)
        return;

    RBTree tL(t), *tR;
    tR = tL.splitR(root->key);
    //tL.insert(root->key);
    //tL.merge(RBTree(root->left));
    //tR.merge(RBTree(root->right));
    tR->join(tL);
    root = tL.root;

}


vector<int> RBTree::getElements() {
    vector<int> v;
    getElem(root, v);
    return v;
}

void RBTree::getElem(Node* node, vector<int>& v) {
    if (node) {
        if (node->left) getElem(node->left, v);
        v.push_back(node->key);
        if (node->right) getElem(node->right, v);
    }
}

void RBTree::getVerticesRecursion(Node *x, vector<tuple<int, Node *> > &vertices)
{
    if (x)
    {
        getVerticesRecursion(x->left, vertices);
        vertices.push_back(make_tuple(0, x));
        getVerticesRecursion(x->right, vertices);
    }
}

RBTree::RBTree()  {
    root=nullptr;
}

vector<tuple<int, Node *> > RBTree::getVertices()
{
    vector<tuple<int, Node*>> v;
    getVerticesRecursion(root, v);
    for (int i = 0; i < v.size(); ++i)
        get<0>(v[i]) = i;
    return v;
}

vector<vector<tuple<int, int> > > RBTree::convertToGraph()
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

            curList.push_back(make_tuple(k, (get<1>(vertices[k]))->key));
        }

        adjacencyLists.push_back(curList);
    }
    return adjacencyLists;
}



void RBTree::merge(Tree *t)
{
    RBTree *rbt=dynamic_cast<RBTree*>(t);
    merge(rbt);

}

Tree *RBTree::split(int k)
{
    Tree* t=dynamic_cast<Tree*>(splitR(k));
    return nullptr;
}

