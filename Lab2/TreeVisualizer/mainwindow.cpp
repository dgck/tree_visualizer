#include "mainwindow.h"
#include "ui_mainwindow.h"

// trash includes for example purposes only
#include "QGVEdge.h"
#include "QGVNode.h"

#include "QGVGraphRelated/qgvredblacktreescenefactory.h"
#include "QGVGraphRelated/qgvbinarytreescenefactory.h"
#include "QGVGraphRelated/qgvbtreescenefactory.h"
#include "Trees/rbtree.h"
#include "graphviz/gvc.h"
#include "graphviz/cgraph.h"
#include "graphviz/cdt.h"

#include <QComboBox>
#include <QPushButton>
#include <QDebug>
#include <QGVSubGraph.h>

#include <memory>
#include <stack>
using std::stack;

using std::shared_ptr;

/*
Тесты:
создать дерево красно-черное через фабрику
создать бинарное
создать б
*/

/*
    известные баги
    - при попытке создать record-shaped node рантайм если у нее одно поле
*/


/*
 * как рисовать record-shaped nodes
 *
m_scene = new QGVScene("scene", this);
QGVNode *node1 = m_scene -> addNode(" <f0> name1|name2"),
        *node2 = m_scene -> addNode("name2| <f1> name2");
node1 -> setAttribute("shape", "record");
node2 -> setAttribute("shape", "record");
QGVEdge *e1 = m_scene -> addEdge(node1, node2);
e1 -> setAttribute("headport", "f1");
e1 -> setAttribute("tailport", "f1");
m_scene -> applyLayout();
*/


/*

Как создавать дерево через фабрику

(дерево типа Т)

auto tree = treeCreator->createTree(Creator::TreeType::RbTree);
... операции с деревом

создать фабрику - в данном случае вместо T пишем redblacktree
QGVRebBlackSceneFactory factory(dynamic_cast<T*>(tree1), this);

получить сцену и вставить ее на место
m_scene = factory.get_scene();
ui->firstTree_img->setScene(m_scene);
ui -> firstTree_img -> fitInView_fixed(m_scene -> sceneRect(), Qt::KeepAspectRatio);

*/

/* как создавать б дерево
    m_scene = new QGVScene("name", this);

    // узлы
    QGVNode* node = m_scene -> addNode("name | name | name | name |name | name | <f3> name "),
            *node2 = m_scene -> addNode("<f0> one|<f1> two");
    node -> setAttribute("shape", "record");
    node2 -> setAttribute("shape", "record");

    // ребра
    QGVEdge* e1 = m_scene -> addEdge(node, node2),
            * e2 = m_scene -> addEdge(node, node2);
    e1 -> setAttribute("headport", "f0");
    e2 -> setAttribute("headport", "f1");
    e1 -> setAttribute("tailport", "f3");
    m_scene -> applyLayout();
*/

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    treeCreator = new Creator;

    tree1 = treeCreator->createTree(Creator::TreeType::BPlusTree);
    tree2 = treeCreator->createTree(Creator::TreeType::BPlusTree);

    tree1 -> insert(1);
    tree1 -> insert(2);
    tree1 -> insert(3);
    tree1 -> insert(4);
    tree1 -> insert(5);
    tree1 -> insert(6);
    tree1 -> insert(7);
    tree1 -> insert(8);


    QGVBTreeSceneFactory factory(dynamic_cast<BplusTree*>(tree1), this);
    m_scene = factory.get_scene();

    /*
    m_scene = new QGVScene("scene", this);
    QGVNode *node1 = m_scene -> addNode(" <f0> name1|name2"),
            *node2 = m_scene -> addNode("name2| <f1> name2");
    node1 -> setAttribute("shape", "record");
    node2 -> setAttribute("shape", "record");
    QGVEdge *e1 = m_scene -> addEdge(node1, node2);
    e1 -> setAttribute("headport", "f1");
    e1 -> setAttribute("tailport", "f0");
    m_scene -> applyLayout();
    */

    ui->firstTree_img->setScene(m_scene);
    ui -> firstTree_img -> fitInView_fixed(m_scene -> sceneRect(), Qt::KeepAspectRatio);

    //MakeConnects();
}

void MainWindow::DrawImage(const int&w,const int&h,const QPixmap&pix,QLabel*image)
{
    image->resize(w,h);
    image->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
}

void MainWindow::MakeConnects()
{
    connect(ui->insert1BTN,&QPushButton::clicked,this,&MainWindow::InsertInTree);
    connect(ui->insert2BTN,&QPushButton::clicked,this,&MainWindow::InsertInTree);

    connect(ui->remove1BTN,&QPushButton::clicked,this,&MainWindow::RemoveFromTree);
    connect(ui->remove2BTN,&QPushButton::clicked,this,&MainWindow::RemoveFromTree);

    connect(ui->delete1TreeBTN,&QPushButton::clicked,this,&MainWindow::DeleteTree);
    connect(ui->delete2TreeBTN,&QPushButton::clicked,this,&MainWindow::DeleteTree);

    connect(ui->prev1,&QPushButton::clicked,this,&MainWindow::PrevStep);
    connect(ui->prev2,&QPushButton::clicked,this,&MainWindow::PrevStep);

    connect(ui->next1,&QPushButton::clicked,this,&MainWindow::NextStep);
    connect(ui->next2,&QPushButton::clicked,this,&MainWindow::NextStep);

    connect(ui->mergeBTN,&QPushButton::clicked,this,&MainWindow::MergeTrees);
    connect(ui->intersectionBTN,&QPushButton::clicked,this,&MainWindow::FindIntersetion);
    connect(ui->inclusionBTN,&QPushButton::clicked,this,&MainWindow::CheckInclusion);

    ui->resultImg->setVisible(false);
    ui->prev3->setVisible(false);
    ui->next3->setVisible(false);
}

void MainWindow::InsertInTree()
{
    QPushButton* buttonSender = qobject_cast<QPushButton*>(sender());
    if(buttonSender == ui->insert1BTN)
    {
        if(!writer1->is_writing())
        {
            tree1->insert(ui->insElem1->text().toInt());
            writer1->ShowSequenceOfImages();
        }
    }
    else
    {
        if(!writer2->is_writing())
        {
            tree2->insert(ui->insElem2->text().toInt());
            writer2->ShowSequenceOfImages();
        }
    }

}

void MainWindow::RemoveFromTree()
{
    QPushButton* buttonSender = qobject_cast<QPushButton*>(sender());
    if(buttonSender == ui->remove1BTN)
    {
        //if(tree1->find(ui->removeElem1->text().toInt(),tree1->getRoot()))
        {
            tree1->deleteNode(ui->removeElem1->text().toInt());
            writer1->ShowSequenceOfImages();
        }
    }
    else
    {
        //if(tree2->search(ui->removeElem1->text().toInt(),tree2->getRoot()))
        {
            tree2->deleteNode(ui->removeElem2->text().toInt());
            writer2->ShowSequenceOfImages();
        }
    }

}

void MainWindow::DeleteTree()
{
    QPushButton* buttonSender = qobject_cast<QPushButton*>(sender());
    if(buttonSender == ui->delete1TreeBTN)
    {
        if(tree1)
        {
            delete tree1;
            tree1 = treeCreator->createTree(Creator::RbTree);
            writer1->ResetSteps();
           // ui->firstTree_img->setText("First tree");
        }
    }
    else
    {
        if(tree2)
        {
            delete tree2;
            tree2 = treeCreator->createTree(Creator::RbTree);
            writer2->ResetSteps();
            //ui->secondTree_img->setText("Second tree");
        }
    }
}

void MainWindow::PrevStep()
{
    QPushButton* buttonSender = qobject_cast<QPushButton*>(sender());
    if(buttonSender == ui->prev1)
    {
        if(!writer1->is_writing())
        {
            writer1->WritePrevStep();
        }
    }
    else
    {
        if(!writer2->is_writing())
        {
            writer2->WritePrevStep();
        }
    }
}

void MainWindow::NextStep()
{
    QPushButton* buttonSender = qobject_cast<QPushButton*>(sender());
    if(buttonSender == ui->next1)
    {
        if(!writer1->is_writing())
        {
            writer1->WriteNextStep();
        }
    }
    else
    {
        if(!writer2->is_writing())
        {
            writer2->WriteNextStep();
        }
    }
}

MainWindow::~MainWindow()
{
    //writer1->ResetSteps();
    //writer2->ResetSteps();
    delete ui;
}


void MainWindow::on_treeType_cb_currentIndexChanged(int index)
{
    delete tree1;
    delete tree2;
    //writer1->ResetSteps();
    //writer2->ResetSteps();
    //ui->firstTree_img->setText("First tree");
    //ui->secondTree_img->setText("Second tree");

    switch (index)
    {
        case 0:
            tree1 = treeCreator->createTree(Creator::TreeType::SimpleTree);
            tree2 = treeCreator->createTree(Creator::TreeType::SimpleTree);
            HideButtonsforBTree(false);
            break;
        case 1:
            tree1 = treeCreator->createTree(Creator::TreeType::RbTree);
            tree2 = treeCreator->createTree(Creator::TreeType::RbTree);
            HideButtonsforBTree(false);
            break;
        case 2:
            tree1 = treeCreator->createTree(Creator::TreeType::SplayTree);
            tree2 = treeCreator->createTree(Creator::TreeType::SplayTree);
            HideButtonsforBTree(false);
            break;
        case 3:
            tree1 = treeCreator->createTree(Creator::TreeType::OBSTTree);
            tree2 = treeCreator->createTree(Creator::TreeType::OBSTTree);
            HideButtonsforBTree(false);
            break;
        case 4:
            tree1 = treeCreator->createTree(Creator::TreeType::BTree);
            tree2 = treeCreator->createTree(Creator::TreeType::BTree);
            HideButtonsforBTree(true);
            break;
        case 5:
            tree1 = treeCreator->createTree(Creator::TreeType::BPlusTree);
            tree2 = treeCreator->createTree(Creator::TreeType::BPlusTree);
            HideButtonsforBTree(true);
            break;
    }
}

void MainWindow::HideButtonsforBTree(bool shouldHide)
{
    ui->diametr1BTN->setEnabled(!shouldHide);
    ui->diametr2BTN->setEnabled(!shouldHide);
    ui->Center1BTN->setEnabled(!shouldHide);
    ui->Center2BTN->setEnabled(!shouldHide);
    ui->order1BTN->setEnabled(!shouldHide);
    ui->order2BTN->setEnabled(!shouldHide);
    ui->order_cb1->setEnabled(!shouldHide);
    ui->order_cb2->setEnabled(!shouldHide);
    ui->findPath1BTN->setEnabled(!shouldHide);
    ui->findPath2BTN->setEnabled(!shouldHide);
    ui->from1->setEnabled(!shouldHide);
    ui->to1->setEnabled(!shouldHide);
    ui->from2->setEnabled(!shouldHide);
    ui->to2->setEnabled(!shouldHide);
    ui->mergeBTN->setEnabled(!shouldHide);
    ui->intersectionBTN->setEnabled(!shouldHide);
    ui->inclusionBTN->setEnabled(!shouldHide);

}

void MainWindow::MergeTrees()
{

}

void MainWindow::FindIntersetion()
{

}

void MainWindow::CheckInclusion()
{

}
