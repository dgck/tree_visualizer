#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <QPixmap>
#include <QImage>
#include <fstream>
#include <thread>
#include <chrono>
#include <QFile>
#include <QTextStream>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),TimePerStep(1000)
{
    ui->setupUi(this);
    overal_number_of_steps = 0;
    index_of_current_step = 0;
    tree = new RBTree;
}

void MainWindow::ShowSequenceOfImages()
{
    index_of_current_step = overal_number_of_steps;

    int new_number_of_steps;
    QFile file("meta.txt");
    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
       QTextStream read(&file);

        read >> new_number_of_steps;
        qDebug()<<new_number_of_steps;
    }
    else{
        new_number_of_steps = 0;
    }
    overal_number_of_steps = new_number_of_steps;

    connect(&timer,&QTimer::timeout,this,[=](){ShowStep(new_number_of_steps,this->index_of_current_step);});
    timer.start(1000);

}

void MainWindow::DrawImage(const string &filename)
{
    QImage *img = new QImage(filename.c_str());
    qDebug()<<filename.c_str();
    QPixmap pix(QPixmap::fromImage(*img));
    int w = pix.width();
    int h = pix.height();
    ui->image->resize(w,h);
    ui->image->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
}

void MainWindow::ShowStep(int new_index, int &current_index)
{
    if(current_index!=new_index)
    {
        string filename = "step_" + QString::number(current_index).toStdString() + ".png";
        DrawImage(filename);
        current_index++;
    }
    else
    {
        timer.stop();
        disconnect(&timer,&QTimer::timeout,this,nullptr);
    }
    if(current_index == new_index)
    {
        current_index--;
        if(timer.isActive())
        {
            timer.stop();
            disconnect(&timer,&QTimer::timeout,this,nullptr);
        }
    }
}

MainWindow::~MainWindow()
{
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
    if(!timer.isActive())
    {
        Node*node = new Node(ui->treeElement->text().toInt());
        tree->insert(node);
        ShowSequenceOfImages();
    }
}

void MainWindow::on_createBtn_clicked()
{

}

void MainWindow::on_prevStep_clicked()
{
    if(!timer.isActive())
    {
        if(index_of_current_step - 1 >= 0)
        {
            string filename = "step_" + QString::number(--index_of_current_step).toStdString() + ".png";
            DrawImage(filename);
        }
    }
}

void MainWindow::on_nextStep_clicked()
{
    if(!timer.isActive())
    {
        if(index_of_current_step + 1 < overal_number_of_steps)
        {
            string filename = "step_" + QString::number(++index_of_current_step).toStdString() + ".png";
            DrawImage(filename);
        }
    }
}

void MainWindow::on_removeBtn_clicked()
{
    if(tree->search(ui->treeElement->text().toInt(),tree->getRoot()))
    {
            Node* f = tree->search(ui->treeElement->text().toInt(),tree->getRoot());
            tree->deleteNode(f);
            ShowSequenceOfImages();
    }
}
