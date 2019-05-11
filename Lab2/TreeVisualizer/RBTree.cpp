//
// Created by artyom on 17.02.19.
//

#include "RBTree.h"
#include <iostream>
#include <fstream>
#include <stack>
#include <cstdlib>
#include<QDebug>
#include "TreeAlgorithms/rbtreealgorithms.h"
using namespace std;

RBTree::RBTree() {
    root = new Node;
    root = nullptr;
    algorithms = new RbTreeAlgorithms;
}

Node *RBTree::getRoot() {
    return root;
}

/*
 * This is not used anymore, the tree is printed to an intermediate file
 *
void RBTree::show() {
    stackWrite(-1);
    system("./show_png.sh");
}*/

void RBTree::stackWrite(int local_value) {
    ofstream dotFile;
    string name_str = "gr";
    name_str += std::to_string(local_value);
    name_str += ".dot";
    dotFile.open (name_str);
    dotFile << "digraph {\n";
    //dotFile << "\t" << "a" << " [fillcolor=red style=filled];";

    stack <Node*> st;
    Node* cur = root;
    while (cur || !st.empty()) {
        while (cur) {
            st.push(cur);
            cur = cur -> left;
        }
        cur = st.top();
        st.pop();
        if (cur -> color == 1)
            dotFile << "\t" << cur -> key << " [fillcolor=red style=filled];\n";
        else if (cur -> color == 0)
            dotFile << "\t" << cur -> key << ";\n";
        if (cur -> left) {
            dotFile << "\t" << cur -> key << " -> " << cur -> left -> key << ";\n";

            if (cur -> left -> color == 1)
                dotFile << "\t" << cur -> left -> key << " [fillcolor=red style=filled];\n";
        }
        if (cur -> right) {
            dotFile << "\t" << cur -> key << " -> " << cur -> right -> key << ";\n";

            if (cur -> right -> color == 1)
                dotFile << "\t" << cur -> right -> key << " [ fillcolor = red style=filled];\n";
        }
        cur = cur -> right;
    }

    dotFile << "}\n";
    dotFile.close();

    string comman_str = "";
    comman_str += "..\\TreeVisualizer\\graphviz\\bin\\dot.exe -Tpng " + name_str + " -o step_" + std::to_string(global_value - 1) + ".png";
    qDebug()<<comman_str.c_str();
    //system(comman_str.c_str());

    ofstream out("meta.txt");
    out << global_value;
    out.close();
}

Node* RBTree::search(int key, Node *cur)
{
    if (!cur)
    {
        return nullptr;
    }

    if (cur -> key == key)
    {
        return cur;
    }
    if (cur -> key < key)
    {
        search(key, cur -> right);
    }
    else
    {
        search(key, cur -> left);
    }
}

void RBTree::insert(Node *i) {

    Node* y = nullptr;
    Node* x = root;

    while (x != nullptr) {
        y = x;
        if (i->key < x -> key) {
            x = x -> left;
        } else  {
            x = x -> right;
        }
    }

    i -> parent = y;
    if (y == nullptr) {
        root = i;
    }
    else if (i -> key < y -> key) {
        y -> left = i;
    } else {
        y -> right = i;
    }
    //stackWrite(global_value++);
    insertFixup(i);

}

void RBTree::setRoot(Node *r) {
    root = r;
}

Node *RBTree::getGoodNode(int v) {
    auto goodN = new Node(v);
    return goodN;
}

void RBTree::insertFixup(Node *z) {
    while (z -> parent && z -> parent -> color == 1) {
        if (z -> parent == z -> parent ->parent -> left) {
            Node* y = z -> parent -> parent -> right;
            if (y && y -> color == 1) {
                z -> parent -> color = 0;
                y -> color = 0;
                z -> parent -> parent -> color = 1;
                z = z -> parent -> parent;
                //stackWrite(global_value++);
            } else {
                if (z -> parent -> right == z) {
                    z = z -> parent;
                    leftRotate(z);
                }
                z -> parent -> color = 0;
                z -> parent -> parent -> color = 1;
                rightRotate(z -> parent -> parent);
               // stackWrite(global_value++);
            }
        } else if (z -> parent == z -> parent -> parent -> right) {
            Node* y = z -> parent -> parent -> left;
            if (y && y -> color == 1) {
                z -> parent -> color = 0;
                y -> color = 0;
                z -> parent -> parent -> color = 1;
                z = z -> parent -> parent;
             //   stackWrite(global_value++);
            } else {
                if (z -> parent -> left == z) {
                    z = z -> parent;
                    rightRotate(z);
           //         stackWrite(global_value++);
                }
                z -> parent -> color = 0;
                z -> parent -> parent -> color = 1;
                leftRotate(z -> parent -> parent);
         //       stackWrite(global_value++);
            }
        }
    }
    if (root) {
        root -> color = 0;
    }
}

void RBTree::insert(int key)
{
    Node *new_node = getGoodNode(key);
    insert(new_node);
}

void RBTree::leftRotate(Node *x) {
    if (!x) return;

    Node* y = nullptr;
    if (x -> right) y = x -> right;

    if (y) {
        if (y -> left) {
            y -> left -> parent = x;
            x -> right = y -> left;
        } else {
            x -> right = nullptr;
        }

        if (x -> parent) {
            y -> parent = x -> parent;

            if (x -> parent -> left == x) {
                x -> parent -> left = y;
            } else if (x -> parent -> right == x) {
                x -> parent -> right = y;
            }
        } else {
            // cout << "haha\n";
        }

        x -> parent = y;
        y -> left = x;

        if (x == root) {
            root = y;
        }
    } else {
        return;
    }
}

void RBTree::rightRotate(Node *x) {
    if (!x) return;

    Node* y = nullptr;
    if (x -> left) y = x -> left;

    if (y) {
        if (y -> right) {
            y -> right -> parent = x;
            x -> left = y -> right;
        } else {
            x -> left = nullptr;
        }

        if (x -> parent) {
            y -> parent = x -> parent;

            if (x -> parent -> left == x) {
                x -> parent -> left = y;
            } else if (x -> parent -> right == x) {
                x -> parent -> right = y;
            }
        } else {
            // cout << "haha\n";
        }

        x -> parent = y;
        y -> right = x;

        if (x == root) {
            root = y;
        }
    } else {
        return;
    }
}

void RBTree::transplant(Node *x, Node *y) {
    if (!x) return;
    if (root == x) {
        x -> parent = nullptr;
    }

    if (x -> parent == nullptr) {
        root = y;
    } else if (x -> parent -> left == x)  {
        x -> parent -> left = y;
    } else if (x -> parent -> right == x) {
        x -> parent -> right = y;
    }

    if (y) y -> parent = x -> parent;
}

Node* treeMinimum(Node* z) {
    Node* res = nullptr;
    while (z) {
        res = z;
        z = z -> left;
    }
    return res;
}

void RBTree::deleteNode(Node *z) {
    if (!z) return;
    Node* nil = nullptr;
    Node* y = z;
    Node* x;
    bool original = y -> color;
    if (z -> left == nullptr) {
        x = z -> right;
        if (!x) {
            nil = new Node;
            nil->color = 0;
            nil->parent = z->parent;
        }
        transplant(z, z -> right);
       // stackWrite(global_value++);
    } else if (z -> right == nullptr) {
        x = z -> left;
        if (!x) {
            nil = new Node;
            nil->color = 0;
            nil->parent = z->parent;
        }
        transplant(z, z -> left);
        //stackWrite(global_value++);
    } else {
        Node* y = treeMinimum(z -> right);
        original = y -> color;
        x = y -> right;

        bool ff = false;
        if (y -> parent == z) {
            if (x)
                x -> parent = y;
                //stackWrite(global_value++);
            else {

                ff = true;
                nil = new Node;
                nil -> color = 0;
            //    stackWrite(global_value++);
            }

        }
        else {

            if (! (y -> right)) {
                nil = new Node;
                nil -> color = 0;
                nil -> parent = y -> parent;
          //      stackWrite(global_value++);
            }

            transplant(y, y -> right);
            y -> right = z -> right;
            y -> right -> parent = y;
        //    stackWrite(global_value++);
        }
        y -> left = z -> left;
        y -> left -> parent = y;
        y -> color = z -> color;
        transplant(z, y);
        if (ff) {
            nil -> parent = y -> parent;
        }
      //  stackWrite(global_value++);
    }

    if (original == 0) {


        if (nil) {
            fixDeletion(nil);
        } else if (x) {
            fixDeletion (x);
        }
    }
}

void RBTree::fixDeletion(Node *x) {

    while (x != root && x -> color == 0) {
        if (x == x -> parent -> left) {
            Node* w = x -> parent -> right;
            if (w && w -> color == 1) {
                w -> color = 0;
                x -> parent -> color = 1;
                leftRotate(x -> parent);
                w = x -> parent -> right;
      //          stackWrite(global_value++);
            }
            if ((w && w -> left && w -> left -> color == 0 && w -> right && w -> right -> color == 0)
                || (w && !(w -> left) && !(w -> right))){
                w -> color = 1;
                x = x -> parent;
        //        stackWrite(global_value++);
            }
            else if ((w && w -> right -> color == 0) || (w && !(w -> right))) {
                if (w -> left)
                    w -> left -> color = 0;
                w -> color = 1;
                rightRotate(w);
                w = x -> parent -> right;
          //      stackWrite(global_value++);
            }

            if (w) w -> color = x -> parent -> color;
            x -> parent -> color = 0;
            if (w && w -> right) w -> right -> color = 0;
            leftRotate(x -> parent);
            x = root;
            //stackWrite(global_value++);
        } else {
            Node* w = x -> parent -> left;
            if (w && w -> color == 1) {
                w -> color = 0;
                x -> parent -> color = 1;
                rightRotate(x -> parent);
                w = x -> parent -> left;
              //  stackWrite(global_value++);
            }
            if ((w && w -> right && w -> right -> color == 0 && w -> left && w -> left -> color == 0)
                || (w && !(w -> right) && !(w -> left))
                || (w && !(w -> right) && w -> left && w -> left -> color == 0)
                || (w && !(w -> left) && w -> right && w -> right -> color == 0)){
                w -> color = 1;
                x = x -> parent;
                //stackWrite(global_value++);
            }
            else if ((w && w -> left -> color == 0) || (w && !(w -> left))) {
                if (w -> right)
                    w -> right -> color = 0;
                w -> color = 1;
                leftRotate(w);
                w = x -> parent -> left;
                //stackWrite(global_value++);
            }

            if (w) w -> color = x -> parent -> color;
            x -> parent -> color = 0;
            if (w && w -> left) w -> left -> color = 0;
            rightRotate(x -> parent);
            x = root;
            //stackWrite(global_value++);
        }
    }
    x -> color = 0;
    //stackWrite(global_value++);
}
