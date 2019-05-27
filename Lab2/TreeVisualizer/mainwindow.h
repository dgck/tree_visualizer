#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <creator.h>
#include "Trees/rbtree.h"
#include "imagewriter.h"
#include "Trees/binarytree.h"
#include <QString>
#include <memory>
#include "QGVCore/QGVScene.h"


using namespace std;

namespace Ui {
class MainWindow;
}


/*!
    \brief Main class where is visualizer
    \author Stas Dzundza
    \version 1.0
    \date May 2019

    This class controls all processes in a program. He receives scenes from image writer and sets these scenes on the QGraphicsView window.
    He contains all of the control components
*/
class MainWindow : public QMainWindow,  public std::enable_shared_from_this<QMainWindow>
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    /*!
     * Method which receives scene from ImageWriter and sets it on the QGraphicsView
     */
    void DrawImage(QCGView*view,QGraphicsScene*scene);

    /*!
     * Method which connects all buttons on the window with their responding methods
     */
    void MakeConnects();

    /*!
     * Method which invokes after pressing insert button
     * After inserting he invokes ImageWriter method and receive QGraphics scene from ImageWriter
     */
    void InsertInTree();

    /*!
     * Method which invokes after pressing delete button
     * After deleting he invokes ImageWriter method and receive QGraphics scene from ImageWriter
     */
    void RemoveFromTree();

    /*!
     * Method which invokes after pressing delete tree button
     * After deleting he clears QGraphicsView
     */
    void DeleteTree();
\
    /*!
     * Method which invokes after pressing < button
     * He invokes ImageWriter method and receive previous QGraphics scene from ImageWriter
     */
    void PrevStep();

    /*!
     * Method which invokes after pressing > button
     * He invokes ImageWriter method and receive next QGraphics scene from ImageWriter
     */
    void NextStep();

    /*!
     * Method which invokes when user changes type of the tree
     * He changes type of the tree and clears scenes
     */
    void on_treeType_cb_currentIndexChanged(int index);

    /*!
     * Method which hide some buttons when user choose b+ tree
     */
    void HideButtonsforBTree(bool shouldHide);

    /*!
     * Method which invokes after pressing merge button
     * After merging he invokes ImageWriter method and receive QGraphics scene from ImageWriter
     */
    void MergeTrees();

    /*!
     * Method which invokes after pressing Intersection button
     * After finding he invokes ImageWriter method and receive QGraphics scene from ImageWriter
     */
    void FindIntersetion();

    /*!
     * Method which invokes after pressing Inclusion button
     * After checking he invokes QMessageBox window and shows result
     */
    void CheckInclusion();

    /*!
     * Method which invokes after pressing Diametr button
     * After finding diametr he invokes ImageWriter method and receive QGraphics scene from ImageWriter
     */
    void FindDiametr();

    /*!
     * Method which invokes after pressing Center button
     * After finding center he invokes ImageWriter method and receive QGraphics scene from ImageWriter
     */
    void FindCenter();

    /*!
     * Method which invokes after pressing Do button
     * He looks,what type of traversal ic choosed and do it.
     * After that he invokes ImageWriter method and receive QGraphics scene from ImageWriter
     */
    void Traversal();

    void BFS();

    void DFS();

    void on_SetTime_clicked();

private:
    Ui::MainWindow *ui;

    Creator*treeCreator;///< factory which creates trees

    Tree*tree1;///< Bridge between UI and Tree realizations
    Tree*tree2;///< Bridge between UI and Tree realizations
    Tree*result_tree;///< Bridge between UI and Tree realizations


    ImageWriter *writer1;///< object of Image writer class which every time returns QGraphicsScene
    ImageWriter *writer2;///< object of Image writer class which every time returns QGraphicsScene
    ImageWriter *writer3;///< object of Image writer class which every time returns QGraphicsScene

    QGVScene *m_scene;

    bool isTraversal = false;///< A variable which tell us about type of process in tree
    bool isBfsDfs = false;

};

#endif // MAINWINDOW_H
