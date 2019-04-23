#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <QPixmap>
#include <QImage>
#include <QFile>
#include <QTextStream>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    tree = new RBTree;

    writer = new ImageWriter;
    connect(writer,&ImageWriter::SendPictureInfo,this,&MainWindow::DrawImage);
}

void MainWindow::DrawImage(const int&w,const int&h,const QPixmap&pix)
{
    ui->image->resize(w,h);
    ui->image->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
}

MainWindow::~MainWindow()
{
    writer->ResetSteps();
    delete ui;  
}

void MainWindow::on_op1Btn_clicked()
{

}

void MainWindow::on_op2Btn_clicked()
{

}

void MainWindow::on_quitBtn_clicked()
{
    QApplication::quit();
}

void MainWindow::on_insertBtn_clicked()
{
    if(!writer->is_writing())
    {
        Node*node = new Node(ui->treeElement->text().toInt());
        tree->insert(node);
        writer->ShowSequenceOfImages();
    }
}

void MainWindow::on_createBtn_clicked()
{

}

void MainWindow::on_prevStep_clicked()
{
    if(!writer->is_writing())
    {
        writer->WritePrevStep();
    }
}

void MainWindow::on_nextStep_clicked()
{
    if(!writer->is_writing())
    {
        writer->WriteNextStep();
    }
}

void MainWindow::on_removeBtn_clicked()
{
    if(tree->search(ui->treeElement->text().toInt(),tree->getRoot()))
    {
        Node* f = tree->search(ui->treeElement->text().toInt(),tree->getRoot());
        tree->deleteNode(f);
        writer->ShowSequenceOfImages();
    }
}

void MainWindow::on_removeTreeBtn_clicked()
{
    if(tree)
    {
        delete tree;
        tree = new RBTree;
        writer->ResetSteps();
        ui->image->setText("There should be tree");
    }
}
