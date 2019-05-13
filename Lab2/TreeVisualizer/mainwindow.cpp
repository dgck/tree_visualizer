#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QComboBox>
#include <QPushButton>
#include <QDebug>

// trash includes for example purposes only
#include "QGVEdge.h"
#include "QGVNode.h"
#include <stack>
using std::stack;
#include "QGVEdge.h"
#include "QGVNode.h"
#include "QGVGraphRelated/qgvredblacktreescenefactory.h"
#include "Trees/rbtree.h"
#include <memory>
using std::shared_ptr;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    treeCreator = new Creator;

    tree1 = treeCreator->createTree(Creator::TreeType::RbTree);
    tree2 = treeCreator->createTree(Creator::TreeType::RbTree);

    RBTree* tree = new RBTree;
    QGVRedBlackTreeSceneFactory f(tree, this);
    QGVScene* scene = f.construct_scene();
    ui -> secondTree_img -> setScene(scene);
    ui -> secondTree_img -> fitInView(scene -> sceneRect(), Qt::KeepAspectRatio);
    MakeConnects();
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
