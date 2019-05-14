#include <QApplication>
#include "tree.h"
#include "rbtree.h"
#include <clocale>
#include "bplustree.h"
#include "obst.h"
#include "splaytree.h"

int main(int argc,char*argv[])
{
    setlocale(LC_ALL, "ru");
   // QApplication a(argc, argv);
   // MainWindow w;
   // w.show();

   //Tree* t = new RBTree();
   //Tree* t2 = new RBTree();

    RBTree t;

    t.insert(10);
    t.insert(5);
    t.insert(15);
    t.insert(1);
    t.insert(20);
    t.insert(13);
    t.insert(7);
    t.insert(11);

//    t2->insert(10);
//    t2->insert(5);
//    t2->insert(15);
//    t2->insert(1);
//    t2->insert(24);


//   t->merge(t2);


 /*   Tree*  t= new BplusTree();
    Tree*  t2= new BplusTree();
    t->insert(10);
    t->insert(5);
    t->insert(15);
    t->insert(1);
    t->insert(20);
    t->insert(13);
    t->insert(7);
    t->insert(11);

    t2->insert(10);
    t2->insert(5);
    t2->insert(15);
    t2->insert(1);
    t2->insert(24);

    BplusTree* tr=dynamic_cast<BplusTree*>(t);
    PreIterator i(*tr);
    i.printTreeInterator();      */
/*
    t->dfs();
    vector<int> v=t->intersection(t2);
    cout<<endl;
    for (int i=0;i<v.size();i++) {
        cout<<v[i]<<endl;
    }

    t->diameter();*/

    OBST b;
PreOBSTIterator r(b);
r.printTreeInterator();
   // b.Preparation();

  /*  SplayTree t;
    t.insert(4);
    t.insert(10);
    t.insert(41);
    t.insert(11);
    t.insert(6);
    t.insert(70);
    t.insert(43);
    t.insert(1);
    t.insert(14);
    t.insert(7);
    t.insert(8);
    t.insert(19);
*/
    //t.show_inorder();

    cout << endl << endl << endl;

   // PreSplayIterator psi(t);
  //  PostSplayIterator posi(t);
  //  InSplayIterator isi(t);
   // t.show();
//PreRBIterator e(t);
//e.printTreeInterator();
   // psi.printTreeInterator();
    cout << endl << endl;
  //  posi.printTreeInterator();



       // system("pause");
        return 0;



 //   return a.exec();
}
