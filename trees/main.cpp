#include <QApplication>
#include "tree.h"
#include "rbtree.h"
#include "treealgorithms.h"
#include <clocale>

int main()
{
    setlocale(LC_ALL, "ru");
   // QApplication a(argc, argv);
   // MainWindow w;
   // w.show();

   RBTree t;
    t.insert(10);
    t.insert(5);
    t.insert(15);
    t.insert(1);
    t.insert(20);
    t.insert(13);
    t.insert(7);
    t.insert(11);
t.display("Test.gv");

vector<vector<tuple<int,int>>> al = t.convertToGraph();
    cout << endl;
    for (int i = 0; i < al.size(); ++i)
    {
        for (int j = 0; j < al[i].size(); ++j)
            cout << get<0>(al[i][j]) << " " << get<1>(al[i][j]) << "| ";
        cout << endl;
    }

    TreeAlgorithms alg;
    alg.dsf(t);


        system("pause");
        return 0;



 //   return a.exec();
}
