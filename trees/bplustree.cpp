#include "bplustree.h"
#include <iostream>
#include <vector>
#include <tuple>
#include <fstream>

using namespace std;

BplusTree::BplusTree()
{
    root = new Node();
}
BplusTree::~BplusTree()
{
}

void BplusTree::splitLeaf(Node *curr) {
    int x, i, j;

    if (T % 2)
    {
        x = (T + 1) / 2;
    }
    else
    {
        x = T / 2;
    }
    Node *right = new Node();
    curr->nElems = x;
    right->nElems = T - x;
    right->parent = curr->parent;

    for (i = x, j = 0; i < T; i++, j++) {
        right->value[j] = curr->value[i];
        curr->value[i] = INT_MAX;
    }
    int item = right->value[0];

    //якщо листок це корінь
    if (curr->parent == nullptr) {
        Node *parentNode = new Node();
        parentNode->parent = nullptr;
        parentNode->nElems = 1;
        parentNode->value[0] = item;
        parentNode->child[0] = curr;
        parentNode->child[1] = right;
        curr->parent = right->parent = parentNode;
        root = parentNode;
        return;
    }
    //якщо розбитий листок це не корінь
    else
    {
        curr = curr->parent;
        Node *newChild = new Node();
        newChild = right;
        for (i = 0; i <= curr->nElems; i++) {
            if (item < curr->value[i]) {
                swap(curr->value[i], item);
            }
        }
        curr->nElems++;
        for (i = 0; i < curr->nElems; i++) {
            if (newChild->value[0] < curr->child[i]->value[0]) {
                swap(curr->child[i], newChild);
            }
        }
        curr->child[i] = newChild;
        for (i = 0; curr->child[i] != nullptr; i++) {
            curr->child[i]->parent = curr;
        }
    }

}

//функція для розбиття нелистового вузла
void BplusTree::splitNonLeaf(Node *curr) {
    int x, i, j;

    x = T / 2;
    Node *right = new Node();
    curr->nElems = x;
    right->nElems = T - x - 1;
    right->parent = curr->parent;

    for (i = x, j = 0; i <= T; i++, j++) {
        right->value[j] = curr->value[i];
        right->child[j] = curr->child[i];
        curr->value[i] = INT_MAX;
        if (i != x)curr->child[i] = nullptr;
    }
    int item = right->value[0];
    memcpy(&right->value, &right->value[1], sizeof(int)*(right->nElems + 1));
    memcpy(&right->child, &right->child[1], sizeof(root)*(right->nElems + 1));

    for (i = 0; curr->child[i] != nullptr; i++) {
        curr->child[i]->parent = curr;
    }
    for (i = 0; right->child[i] != nullptr; i++) {
        right->child[i]->parent = right;
    }

    //якщо розбитий вузол це корінь
    if (curr->parent == nullptr) {
        Node *parentNode = new Node();
        parentNode->parent = nullptr;
        parentNode->nElems = 1;
        parentNode->value[0] = item;
        parentNode->child[0] = curr;
        parentNode->child[1] = right;

        curr->parent = right->parent = parentNode;

        root = parentNode;
        return;
    }
    //якщо розбитий вузол не корінь
    else
    {
        curr = curr->parent;
        Node *newChild = new Node();
        newChild = right;

        for (i = 0; i <= curr->nElems; i++) {
            if (item < curr->value[i]) {
                swap(curr->value[i], item);
            }
        }
        curr->nElems++;
        for (i = 0; i < curr->nElems; i++) {
            if (newChild->value[0] < curr->child[i]->value[0]) {
                swap(curr->child[i], newChild);
            }
        }
        curr->child[i] = newChild;
        for (i = 0; curr->child[i] != nullptr; i++) {
            curr->child[i]->parent = curr;
        }
    }

}

//функція вставки
void BplusTree::insert(int val) {
    insertNode(root, val);
}

void BplusTree::insertNode(Node *curr, int val) {
    for (int i = 0; i <= curr->nElems; i++) {
        if (val < curr->value[i] && curr->child[i] != nullptr) {
            insertNode(curr->child[i], val);
            if (curr->nElems == T)
                splitNonLeaf(curr);
            return;
        }
        else if (val < curr->value[i] && curr->child[i] == nullptr) {
            swap(curr->value[i], val);
            if (i == curr->nElems) {
                curr->nElems++;
                break;
            }
        }
    }

    if (curr->nElems == T) {
        splitLeaf(curr);
    }
}

//операція перерозроділу вузлів
void BplusTree::redistributeCell(Node *left, Node *right, bool isLeaf, int posOfLeftBlock, int isCurBlock) {

    int PrevRightFirstVal = right->value[0];
    if (isCurBlock == 0) {
        if (!isLeaf) {
            left->value[left->nElems] = left->parent->value[posOfLeftBlock];
            left->child[left->nElems + 1] = right->child[0];
            left->nElems++;
            left->parent->value[posOfLeftBlock] = right->value[0];
            memcpy(&right->value[0], &right->value[1], sizeof(int)*(right->nElems + 1));
            memcpy(&right->child[0], &right->child[1], sizeof(root)*(right->nElems + 1));
            right->nElems--;

        }
        else
        {
            left->value[left->nElems] = right->value[0];
            left->nElems++;
            memcpy(&right->value[0], &right->value[1], sizeof(int)*(right->nElems + 1));
            right->nElems--;
            left->parent->value[posOfLeftBlock] = right->value[0];
        }
    }
    else {

        if (!isLeaf) {
            memcpy(&right->value[1], &right->value[0], sizeof(int)*(right->nElems + 1));
            memcpy(&right->child[1], &right->child[0], sizeof(root)*(right->nElems + 1));
            right->value[0] = left->parent->value[posOfLeftBlock];
            right->child[0] = left->child[left->nElems];

            right->nElems++;
            left->parent->value[posOfLeftBlock] = left->value[left->nElems - 1];
            left->value[left->nElems - 1] = INT_MAX;
            left->child[left->nElems] = nullptr;
            left->nElems--;
        }
        else
        {
            memcpy(&right->value[1], &right->value[0], sizeof(int)*(right->nElems + 1));
            right->value[0] = left->value[left->nElems - 1];
            right->nElems++;

            left->value[left->nElems - 1] = INT_MAX;
            left->nElems--;

            left->parent->value[posOfLeftBlock] = right->value[0];
        }
    }
}

//операція злиття вузлів
void BplusTree::mergeCell(Node *left, Node *right, bool isLeaf, int posOfRightBlock) {

    if (!isLeaf) {

        left->value[left->nElems] = left->parent->value[posOfRightBlock - 1];
        left->nElems++;
    }
    memcpy(&left->value[left->nElems], &right->value[0], sizeof(int)*(right->nElems + 1));
    memcpy(&left->child[left->nElems], &right->child[0], sizeof(root)*(right->nElems + 1));
    left->nElems += right->nElems;
    memcpy(&left->parent->value[posOfRightBlock - 1], &left->parent->value[posOfRightBlock], sizeof(int)*(left->parent->nElems + 1));
    memcpy(&left->parent->child[posOfRightBlock], &left->parent->child[posOfRightBlock + 1], sizeof(root)*(left->parent->nElems + 1));

    left->parent->nElems--;
    for (int i = 0; left->child[i] != nullptr; i++) {
        left->child[i]->parent = left;
    }
}

bool dataFound;

//видалення елемента
void BplusTree::deleteNode(int val) {
    deleteNode(root, val, 0);
}

void BplusTree::deleteNode(Node *curr, int value, int currPos) {

    bool isLeaf;
    if (curr->child[0] == nullptr)
    {
        isLeaf = true;
    }
    else
    {
        isLeaf = false;
    }
    int prevLeftMostVal = curr->value[0];

    for (int i = 0; dataFound == false && i <= curr->nElems; i++) {
        if (value < curr->value[i] && curr->child[i] != nullptr) {
            deleteNode(curr->child[i], value, i);
        }
        else if (value == curr->value[i] && curr->child[i] == nullptr) {
            memcpy(&curr->value[i], &curr->value[i + 1], sizeof(int)*(curr->nElems + 1));
            curr->nElems--;
            dataFound = true;
            break;
        }
    }

    if (curr->parent == nullptr && curr->child[0] == nullptr) {
        return;
    }

    if (curr->parent == nullptr && curr->child[0] != nullptr && curr->nElems == 0) {
        root = curr->child[0];
        root->parent = nullptr;
        return;
    }

    if (curr->parent != nullptr) {
        for (int i = 0; i < curr->parent->nElems; i++) {
            if (curr == curr->parent->child[i]) {
                currPos = i;
                break;
            }
        }
    }

    if (isLeaf && curr->parent != nullptr) {
        if (currPos == 0) {
            Node *right = new Node();

            right = curr->parent->child[1];
            if (right != nullptr && right->nElems > (T + 1) / 2) {

                redistributeCell(curr, right, isLeaf, 0, 0);
            }
            else if (right != nullptr && curr->nElems + right->nElems < T) {
                mergeCell(curr, right, isLeaf, 1);
            }
        }
        else
        {
            Node *left = new Node();
            Node *right = new Node();

            left = curr->parent->child[currPos - 1];

            right = curr->parent->child[currPos + 1];

            if (left != nullptr && left->nElems > (T + 1) / 2) {
                redistributeCell(left, curr, isLeaf, currPos - 1, 1);
            }
            else if (right != nullptr && right->nElems > (T + 1) / 2) {
                redistributeCell(curr, right, isLeaf, currPos, 0);
            }
            else if (left != nullptr && curr->nElems + left->nElems < T) {
                mergeCell(left, curr, isLeaf, currPos);
            }
            else if (right != nullptr && curr->nElems + right->nElems < T) {
                mergeCell(curr, right, isLeaf, currPos + 1);
            }
        }
    }
    else if (!isLeaf && curr->parent != nullptr)
    {
        if (currPos == 0) {
            Node *right = new Node();
            right = curr->parent->child[1];

            if (right != nullptr && right->nElems - 1 >= ceil((T - 1) / 2)) {
                redistributeCell(curr, right, isLeaf, 0, 0);
            }
            else if (right != nullptr && curr->nElems + right->nElems < T - 1) {
                mergeCell(curr, right, isLeaf, 1);
            }
        }
        else
        {
            Node *left = new Node();
            Node *right = new Node();


            left = curr->parent->child[currPos - 1];

            right = curr->parent->child[currPos + 1];

            if (left != nullptr && left->nElems - 1 >= ceil((T - 1) / 2)) {
                redistributeCell(left, curr, isLeaf, currPos - 1, 1);
            }
            else if (right != nullptr && right->nElems - 1 >= ceil((T - 1) / 2)) {
                redistributeCell(curr, right, isLeaf, currPos, 0);
            }
            else if (left != nullptr && curr->nElems + left->nElems < T - 1) {
                mergeCell(left, curr, isLeaf, currPos);
            }
            else if (right != nullptr && curr->nElems + right->nElems < T - 1) {
                mergeCell(curr, right, isLeaf, currPos + 1);
            }
        }

    }
    Node *temp = new Node();
    temp = curr->parent;
    while (temp != nullptr) {
        for (int i = 0; i < temp->nElems; i++) {
            if (temp->value[i] == prevLeftMostVal) {
                temp->value[i] = curr->value[0];
                break;
            }
        }
        temp = temp->parent;
    }

}

void BplusTree::graphviz(vector <Node*> Nodes)
{
    FILE *f = nullptr;
    errno_t err = fopen_s(&f, "graphviz.dat", "w");
    fputs("digraph G{\n", f);
    fclose(f);
    graphvizRec(Nodes);
    err = fopen_s(&f, "graphviz.dat", "a");
    fputc('}', f);
    fclose(f);
}

void BplusTree::graphvizRec(vector <Node*> Nodes)
{
    vector <Node*> newCells;
    for (int i = 0; i < Nodes.size(); i++) {
        Node *curr = Nodes[i];



        FILE *f = nullptr;
        errno_t err = fopen_s(&f, "graphviz.dat", "a");
        string str = "\"";
        str += "[|";
        int j;
        for (j = 0; j < curr->nElems; j++) {  //проходимо синів, виводимо значення і зберігаєм всіх дітей
            str += to_string(curr->value[j]);
            str += "|";
            if (curr->child[j] != nullptr)
            {
                newCells.push_back(curr->child[j]);

            }

        }
        if (curr->value[j] == INT_MAX && curr->child[j] != nullptr)
            newCells.push_back(curr->child[j]);

        str += "]\"";
        for (j = 0; j < curr->nElems; j++)
        {
            if (curr->child[j] != nullptr)
            {
                string str2 = "\"[|";
                for (int k = 0; k < curr->child[j]->nElems; ++k)
                {

                    str2 += to_string(curr->child[j]->value[k]);
                    str2 += "|";
                }
                str2 += "]\"";
                fputs(str.c_str(), f);
                fputs("->", f);
                fputs(str2.c_str(), f);
                fputs(";\n", f);
            }
        }
        if (curr->child[j] != nullptr)
        {
            string str2 = "\"[|";
            for (int k = 0; k < curr->child[j]->nElems; ++k)
            {

                str2 += to_string(curr->child[j]->value[k]);
                str2 += "|";
            }
            str2 += "]\"";
            fputs(str.c_str(), f);
            fputs("->", f);
            fputs(str2.c_str(), f);
            fputs(";\n", f);
        }

        fclose(f);


    }

    if (newCells.size() == 0) { //якщо немає більше синів, закінчуєм рекурсію

        puts("");
        puts("");
        Nodes.clear();
    }
    else {                    //інакше відправляєм синів до рекурсії
        puts("");
        puts("");
        Nodes.clear();
        graphvizRec(newCells);
    }
}


vector<int> BplusTree::getElements() {
    vector<int> v;
    vector<Node*> t = { root };
    getElem(t, v);
    return v;
}

void BplusTree::getElem(vector <Node*> Nodes, vector<int>& v) {


    vector <Node*> newCells;
    for (int i = 0; i < Nodes.size(); i++) {
        Node *curr = Nodes[i];


        int j;
        if (curr->child[0] == nullptr) {
            for (j = 0; j < MAX; j++) {  //проходимо синів, виводимо значення і зберігаєм всіх дітей
                if (curr->value[j] != INT_MAX) v.push_back(curr->value[j]);
            }
        }
        else
            for (j = 0; j < curr->nElems; j++) {  //проходимо синів, виводимо значення і зберігаєм всіх дітей

                if (curr->child[j] != nullptr)
                    newCells.push_back(curr->child[j]);
            }
        if (curr->value[j] == INT_MAX && curr->child[j] != nullptr)
            newCells.push_back(curr->child[j]);


    }

    if (newCells.size() == 0) { //якщо немає більше синів, закінчуєм рекурсію

        Nodes.clear();
    }
    else {                    //інакше відправляєм синів до рекурсії
        Nodes.clear();
        getElem(newCells, v);
    }
}

void BplusTree::getVerticesRecursion(Node *x, vector<tuple<int, Node *> > &vertices)
{
    if (x)
    {
        vertices.push_back(make_tuple(0, x));
        for(int i=0; i<=x->nElems;i++)
        getVerticesRecursion(x->child[i], vertices);
    }
}

vector<tuple<int, Node *>> BplusTree::getVertices()
{
    vector<tuple<int, Node*>> v;
    getVerticesRecursion(root, v);
    for (int i = 0; i < v.size(); ++i)
        get<0>(v[i]) = i;
    return v;
}

vector<vector<tuple<int, Node*>>> BplusTree::convertToGraph()
{
    vector<vector<tuple<int, Node*>>> adjacencyLists;
    vector<tuple<int, Node*>> vertices = getVertices();
    for (int i = 0; i < vertices.size(); ++i)
    {
        vector<tuple<int, Node*>> curList;
        curList.push_back(make_tuple(i, get<1>(vertices[i])));

        int k;

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

            curList.push_back(make_tuple(k, get<1>(vertices[k])));
        }

        for (int l = 0; l <= get<1>(vertices[i])->nElems; ++l)
        {
            if (get<1>(vertices[i])->child[l])
            {
                for (int j = 0; j < vertices.size(); ++j)
                {
                    if (get<1>(vertices[i])->child[l] == get<1>(vertices[j]))
                    {
                        k = j;
                        break;
                    }
                }
                curList.push_back(make_tuple(k, get<1>(vertices[k])));
            }
        }

        adjacencyLists.push_back(curList);
    }
    return adjacencyLists;
}
