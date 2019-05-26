#include "rbtree.h"
#include <string>
#include <iostream>
#include <iomanip>
#include <utility>
#include <cstdio>
#include <fstream>
#include <vector>
#include <tuple>
#include "QGVGraphRelated/qgvredblacktreescenefactory.h"
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
    BinaryTree::insert(input);
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
    scenes.push_back(factory->get_scene());
    factory = new QGVRebBlackSceneFactory(this);
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
    scenes.push_back(factory->get_scene());
    factory = new QGVRebBlackSceneFactory(this);
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
    scenes.push_back(factory->get_scene());
    factory = new QGVRebBlackSceneFactory(this);
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
    vector<int> e = rbTree2.getElements();
    int temp;
    Node *c, *temp_ptr = nullptr;
    Node *root1 = root;
    Node *root2 = rbTree2.root;
    for (size_t i = 0; i < e.size(); ++i) { insert(e[i]);}
    if(root != nullptr) return;
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
    scenes.push_back(factory->get_scene());
    factory = new QGVRebBlackSceneFactory(this);
    return;
}

RBTree* RBTree::splitR(int x) {

    RBTree *t1, *t2;

    Node* k = root;

    while (k && (k->left || k->right))
    {
        cout << k->key << endl;
        if (x == k->key)
        {
            t2->join(RBTree(RBTree(k->right)));
            t1->join(RBTree(RBTree(k->left)));
            break;
        }
        if (x < k->key)
        {
            cout << "BEFORE join <" << endl;
            t2->join(RBTree(k->right));
            cout << "AFTER join <" << endl;
            k = k->left;
        }
        else
        {
            cout << "Copy\n";
            RBTree(k).show();
            t1->join(RBTree(RBTree(k->left)));

            k = k->right;
        }

        cout << "T1" << endl;
        if (t1) t1->show();

        cout << endl;
        cout << "T2" << endl;
        if(t2) t2->show();

        cout << "----------\n\n";
    }

    (k && k->key)<x?t1->insert(k->key):t2->insert(k->key);

    root = t1->root;
    show();
    return  t2;
}

void RBTree::merge(RBTree* t) {

    cout<<"merge";
    if (root == nullptr) {
        root = t->root;
        return;
    }
    if (t->root == nullptr)
        return;

    join(*t);
}



RBTree::RBTree()  {
    root=nullptr;
    factory = new QGVRebBlackSceneFactory (this);
}

void RBTree::merge(Tree *t)
{
    RBTree *rbt=dynamic_cast<RBTree*>(t);
    merge(rbt);
    show();
}

Tree *RBTree::split(int k)
{
    return nullptr;
}



