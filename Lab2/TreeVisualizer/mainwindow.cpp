#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QComboBox>
#include <QPushButton>
#include<QDebug>

// trash includes for example purposes only
#include "RBTree.h"
#include "QGVEdge.h"
#include "QGVNode.h"

#include <stack>
using std::stack;


#include "QGVEdge.h"
#include "QGVNode.h"

RBTree* example_tree()
{
    RBTree* res = new RBTree;
    for (int i = 0; i < 5; i++)
        res -> insert(res -> getGoodNode(i));
    return res;
}

/*
void sWrite(RBTree* src, QGVScene *sc) {
    stack <Node*> st;
    Node* cur = src ->root;
    while (cur || !st.empty()) {
        while (cur) {
            st.push(cur);
            cur = cur -> left;
        }
        cur = st.top();
        st.pop();
        if (cur -> color == 1)
        {
            QGVNode* res = sc -> addNode(QString::number(cur -> key));
            res ->setAttribute(QString("fillcolor"), QString("red"));
            res ->setAttribute(QString("style"), QString("filled"));
        }
        else if (cur -> color == 0)
        {
            QGVNode* res = sc -> addNode(QString::number(cur -> key));
        }
        if (cur -> left) {
            QGVNode *parent = sc -> addNode(QString::number(cur -> key));
            QGVNode *son  = sc -> addNode(QString::number(cur -> left -> key));
            sc -> addEdge(parent, son);

            if (cur -> left -> color == 1)
            {
                son->setAttribute(QString("fillcolor"), QString("red"));
            }
        }
        if (cur -> right) {
            QGVNode *parent = sc -> addNode(QString::number(cur -> key));
            QGVNode *son  = sc -> addNode(QString::number(cur -> right -> key));
            sc -> addEdge(parent, son);

            if (cur -> right -> color == 1)
            {
                son->setAttribute(QString("fillcolor"), QString("red"));
            }
        }
        cur = cur -> right;
    }
}
*/

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    auto new_shit = example_tree();
    m_scene = new QGVScene("DEMO", this);
    ui->firstTree_img->setScene(m_scene);

    // graph settings
    m_scene->setGraphAttribute("label", "DEMO");
    m_scene->setGraphAttribute("splines", "true");
    m_scene->setGraphAttribute("rankdir", "TB");
    m_scene->setGraphAttribute("nodesep", "0.4");
    m_scene->setNodeAttribute("shape", "circle");
    m_scene->setNodeAttribute("style", "filled");
    m_scene->setNodeAttribute("fillcolor", "white");
    m_scene->setNodeAttribute("height", "0.4");
    m_scene->setEdgeAttribute("minlen", "0.4");



    QGVNode *n1 = m_scene -> addNode("n1"),
            *n2 = m_scene -> addNode("n2"),
            *n3 = m_scene -> addNode("n3"),
            *n4 = m_scene -> addNode("n4");
    QGVEdge *e1 = m_scene -> addEdge(n1, n2, "a"),
            *e2 = m_scene -> addEdge(n1, n3, "b"),
            *e3 = m_scene -> addEdge(n1, n4, "c");

    m_scene->applyLayout();
    ui -> firstTree_img -> fitInView(m_scene -> sceneRect(), Qt::KeepAspectRatio);
    //ui -> firstTree_img -> fitInView_fixed(m_scene -> sceneRect(), Qt::KeepAspectRatio);

    // trash example end

    //Singleton
    //treeCreator = new Creator;

    //writer1 = new ImageWriter(ui->firstTree_img);
    //writer2 = new ImageWriter(ui->secondTree_img);
    //writer3 = new ImageWriter(ui->resultImg);
   // connect(writer1,&ImageWriter::SendPictureInfo,this,&MainWindow::DrawImage);
    //connect(writer2,&ImageWriter::SendPictureInfo,this,&MainWindow::DrawImage);
    //(writer3,&ImageWriter::SendPictureInfo,this,&MainWindow::DrawImage);

    //tree1 = treeCreator->createTree(Creator::TreeType::RbTree);
    //tree2 = treeCreator->createTree(Creator::TreeType::RbTree);

    //QPalette pal = this->palette();
    //pal.setColor(QPalette::Window, Qt::white);
    //this->setPalette(pal);

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
            Node*node = new Node(ui->insElem1->text().toInt());
            tree1->insert(node);
            writer1->ShowSequenceOfImages();
        }
    }
    else
    {
        if(!writer2->is_writing())
        {
            Node*node = new Node(ui->insElem2->text().toInt());
            tree2->insert(node);
            writer2->ShowSequenceOfImages();
        }
    }

}

void MainWindow::RemoveFromTree()
{
    QPushButton* buttonSender = qobject_cast<QPushButton*>(sender());
    if(buttonSender == ui->remove1BTN)
    {
        if(tree1->search(ui->removeElem1->text().toInt(),tree1->getRoot()))
        {
            Node* f = tree1->search(ui->removeElem1->text().toInt(),tree1->getRoot());
            tree1->deleteNode(f);
            writer1->ShowSequenceOfImages();
        }
    }
    else
    {
        if(tree2->search(ui->removeElem1->text().toInt(),tree2->getRoot()))
        {
            Node* f = tree2->search(ui->removeElem1->text().toInt(),tree2->getRoot());
            tree2->deleteNode(f);
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
