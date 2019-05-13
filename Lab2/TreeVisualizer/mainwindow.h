#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <creator.h>
#include "Trees/rbtree.h"
#include "imagewriter.h"
#include "Trees/binarytree.h"
#include <QString>

#include "QGVScene.h"

using namespace std;

namespace Ui {
class MainWindow;
}

#include <memory>

class MainWindow : public QMainWindow,  public std::enable_shared_from_this<QMainWindow>
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void DrawImage(const int&w,const int&h,const QPixmap&pix,QLabel*image);

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

private:
    Ui::MainWindow *ui;

    //Factory
    Creator*treeCreator;

    //Bridge between UI and Tree realizations
    Tree*tree1;
    Tree*tree2;

    ImageWriter *writer1;
    ImageWriter *writer2;
    ImageWriter *writer3;//for result image

    QGVScene *m_scene;

};

#endif // MAINWINDOW_H
