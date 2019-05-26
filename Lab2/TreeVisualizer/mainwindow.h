#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <creator.h>
#include "Trees/rbtree.h"
#include "imagewriter.h"
#include "Trees/binarytree.h"
#include <QString>

using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void DrawImage(QGraphicsView*view,QGraphicsScene*scene);

    void MakeConnects();

    void InsertInTree();

    void RemoveFromTree();

    void DeleteTree();

    void PrevStep();

    void NextStep();

    void on_treeType_cb_currentIndexChanged(int index);
    \
    void HideButtonsforBTree(bool shouldHide);

    void MergeTrees();

    void FindIntersetion();

    void CheckInclusion();

    void FindDiametr();

    void FindCenter();

private:
    Ui::MainWindow *ui;

    //Factory
    Creator*treeCreator;

    //Bridge between UI and Tree realizations
    Tree*tree1;
    Tree*tree2;
    Tree*result_tree;


    ImageWriter *writer1;
    ImageWriter *writer2;
    ImageWriter *writer3;//for result image
};

#endif // MAINWINDOW_H
